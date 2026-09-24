# Fresh baseline review: Storage.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Entire current file read, lines 1–340; baseline diff empty. Windows static review; tests/builds not run.

## File-specific inspection

- Traced all synchronous file wrappers through `SharedFileUtils` and filesystem entries, including filename/index conversion, offset reads, deletion, sharing, cache close, upload workers, and response listeners.
- Inspected latest SDK `IStorage.h`, server share/request handlers, message schemas, registrar request tracking/unregister, and normal `InterfaceInstances::reset` order.
- Completed `jthread`s are moved into a local collection and joined outside the worker-container mutex. The worker does not acquire that mutex, so the destructor's current lock/clear is not, by itself, a demonstrated lock cycle. Explicit reset destroys storage before the client and registrar; automatic global destruction is a separate CORE lifetime concern.
- Shared helpers check null data/name/container pointers and bounds; raw pointers in the wrappers do not establish a missing null guard without following those helpers. Error logging rather than SDK error-state propagation remains a limitation. `GalaxyDLL::GetError()` always returns null, a CORE dependency rather than a new duplicated finding here.
- Dependency handoff: `filesystem_entry::write` truncates before writing and checks state before implicit close; `unlink` drops its cache entry even on filesystem removal failure. These affect local storage reliability in addition to cloud findings BASE-STORAGE-001/002 and belong in the UTIL/NET integration review.
- Windows time handoff: `GetFileTimestamp` delegates to `SharedFileUtils::GetTimestamp`, which clamps `file_clock` epoch seconds to `UINT32_MAX`; `filesystem_entry::get_timestamp` does not convert to system/Unix time. With MSVC's Windows file-time epoch this is not a usable contemporary Unix timestamp. The old cloud branch also directly narrows that value. Root is in Shared_NoVer; no second STORAGE finding ID is assigned.
- `Host/Storage.cxx` tests binary/offset roundtrip, close/count/index, invalid IDs, and server policy denials. It uses a nonempty file and same-user share/download, so it cannot reveal wrong remote ownership or empty-file rejection. Tests were inspected only.

## Findings

### [BASE-STORAGE-013] FileShare registers its listener after returning control to the caller

- **Severity:** High
- **Confidence:** High
- **Category:** Concurrency / Memory Safety
- **Location:** `Source/Client/Impl/Storage.cxx:171–196`, worker launch and `AddRequestListener`.
- **Affected scope:** File-share versions with specific listeners; cancellation immediately after `FileShare`.

**Evidence:** The worker generates its request ID and registers the captured raw listener at lines 177–180. `FileShare` can return after launching the thread and recording its worker, before those statements run. Registrar unregistration only erases existing request/global entries. SDK `IListenerRegistrar.h:156–165` promises cancellation of all pending calls.

**Failure mechanism:** Worker execution is delayed by scheduling. The game calls `FileShare`, then unregisters and destroys its listener. There is no request entry yet to remove. The worker resumes and registers the stale pointer, sends a valid share, and the response handler pops and invokes it at lines 314–328. A game leaving its upload screen immediately after starting a share can follow this sequence.

**Impact:** Use-after-free at completion despite the game following the cancellation contract. This registration window is distinct from CORE's already-queued `NotifyAll` cancellation issue.

**Possible solutions:** Generate/register the request before thread launch; represent pending operations with cancellable lifetime tokens; or use a common operation queue with synchronous admission.

**Recommended resolution:** Create the request record synchronously before exposing the pending operation to cancellation. Let the worker retain the request ID/token rather than the listener pointer, and roll back on thread creation/read/send failure. Ensure unregister-versus-dispatch is coordinated by the registrar.

**Verification:** Pause the worker before registration with a barrier, unregister/destroy the listener on the caller thread, resume, and pump the server reply under Windows ASan. Require no callback to the removed listener. Also verify listener cleanup when starting the worker fails.

### [BASE-STORAGE-014] Downloaded files are always attributed to the downloading user

- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness / API contract
- **Location:** `Source/Client/Impl/Storage.cxx:245–249`, `GetSharedFileOwner`.
- **Affected scope:** Files uploaded by another LAN participant and downloaded successfully.

**Evidence:** The method ignores `sharedFileID` and returns `config->GetApiGalaxyID()`. SDK `IStorage.h:244–252` requires the owner of that downloaded shared file. `FileShareMessage`, `FileRequestMessage`, and the inspected server persistence path do not retain uploader identity in the file record or reply.

**Failure mechanism:** User A uploads a nonempty file with an unused name. User B downloads its returned ID and asks for its owner. B gets B's own ID, not A's. This meets the API download precondition and does not rely on invalid IDs or unsupported remote services.

**Impact:** Incorrect attribution and owner-specific UI/game behavior. No security boundary or privilege escalation is asserted; any game authorization relying on this value needs separate analysis.

**Possible solutions:** Store authenticated uploader identity server-side and return it with file metadata; encode an owner mapping in a backward-compatible response extension; or return an explicit unsupported/unknown result rather than a false local owner where compatible.

**Recommended resolution:** Persist the uploader ID from the authenticated server peer, transport it in the response, cache it by shared ID, and return that field. Plan wire/persistence version compatibility and migration for existing records.

**Verification:** Use two distinct local test users. A uploads, B downloads, and both must observe A as owner. Repeat after server restart and verify behavior for legacy records without an owner. Existing same-user roundtrip is an inadequate oracle.

### [BASE-STORAGE-015] Valid empty shared files are treated as failed downloads

- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness / protocol result modeling
- **Location:** `Source/Client/Impl/Storage.cxx:275–305`, `FileDownloaded`.
- **Affected scope:** Zero-byte shared files, including marker/empty-state files created by `FileWrite`.

**Evidence:** Success handling is guarded by `data->data.size() > 0`. The SDK has no nonempty-file precondition. The server can return a found file with its filename and an empty vector (`ServerHandlers.cxx:488–503`), while the request schema has no explicit found/result field.

**Failure mechanism:** Create a zero-byte local file with a valid nonnull data pointer and size zero, share it, then download its nonzero shared ID. The server's file entry can exist and be read as empty, but the client bypasses cache creation and reports failure. Empty payload currently also represents policy denial/not-found, so changing only the `> 0` comparison would incorrectly turn failures into successes.

**Impact:** Empty files cannot participate in the shared-storage abstraction, and their valid IDs are unusable to downloading games.

**Possible solutions:** Add an explicit response status and data length; use a distinct result message; or define a compatible validity field backed by server checks.

**Recommended resolution:** Carry success/failure independently of payload size, accept successful empty files, and preserve denial/not-found behavior. Make zero-length writes well-defined even when a vector's `data()` is null. Coordinate message and server changes with NET/SERVER.

**Verification:** Test zero-, one-, and multi-byte downloads alongside policy denial and missing IDs. For successful empty files require one success callback, size/read count zero, correct name/owner, and consistent enumeration/close behavior.

### [BASE-STORAGE-016] FileShare cannot distinguish failed source reads from successful empty uploads

- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness / error handling
- **Location:** `Source/Client/Impl/Storage.cxx:160–193`, `FileShare` worker.
- **Affected scope:** Sharing a local file that exists but cannot be read, or whose worker throws before submission.

**Evidence:** The worker constructs `FileShareMessage` directly from `sfu->Read(...)`. Shared's vector read returns `{}` for open/read errors; no status reaches the caller. The earlier `Exists` check establishes neither read permission nor stable contents. Catch blocks print diagnostics but do not pop the request or deliver failure. The server assigns a share ID and replies even when its write fails, strengthening the need for end-to-end status.

**Failure mechanism:** Keep an existing nonempty local file visible while a Windows sharing handle prevents opening it for reading. `Exists` succeeds, `Read` returns empty, and an empty upload is sent. The normal nonzero-ID response leads to `OnFileShareSuccess`. Alternatively, a read allocation/serialization exception after registration leaves the operation without a terminal callback and retains its request record until later cancellation.

**Impact:** A share can represent none of the intended content while appearing successful, or the caller can wait indefinitely after a worker failure. The original local file is not necessarily lost, so this is rated Medium.

**Possible solutions:** Introduce a result-bearing read API; validate a complete immutable source snapshot before submission; or stream with explicit source failure reporting. Checking for an empty vector alone would wrongly reject legitimate empty files.

**Recommended resolution:** Preserve read status separately from data, abort failed uploads locally, and guarantee cleanup plus one failure completion on every worker exception. Require the server to acknowledge actual persistence, coordinating its separate ownership. Avoid manufacturing success merely from a nonzero ID.

**Verification:** Deny source read sharing while allowing attribute queries and assert no share request is sent and one failure arrives. Inject a post-registration worker exception and check the request is retired. Keep an empty-file success control after BASE-STORAGE-015 is fixed.

## Source-first re-review addendum — 2026-09-24

Read `Storage.cxx:1-340` and `Storage.hxx:1-274` completely before comparing baseline findings. BASE-STORAGE-013/014/015 remain supported. All overloads in `SharedFileUtils` and the filesystem entries, server handlers, three sharing schemas, request tracking, network dispatch, and both explicit and implicit lifetime orders were traced. Source matches `b30e8387`; no execution was performed.

- Worker compaction first moves out the completed worker, then moves the final element into an empty/moved-from slot. It does not replace a still-running jthread at that slot. The captured shared completion flag remains owned by the lambda even though `Worker::finished` is destroyed before `Worker::thread`.
- Explicit reset stops the transport, joins Storage workers while `client`, registrar and `sfu` still exist, then destroys dependencies (`UniverseLAN.cxx:91-133`). Upload workers do not take the worker-list mutex. Do not infer a deadlock merely from `clear()` under that mutex. Implicit `InterfaceInstances` member destruction destroys registrar before Storage and still requires CORE reconciliation.
- `FileUploaded` re-reads the local source when populating its cache (`Storage.cxx:319-328`), so a changed local source can differ from the upload packet. This alone is **not** counted as a confirmed supported shared-read defect: SDK `IStorage.h:213-265` requires a successful `DownloadSharedFile` first, which normally rewrites that cache from the server. A failed convenience-cache copy likewise does not by itself refute successful server-side sharing. Server non-persistence with a success ID remains BASE-SERVER-007.
- Buffer reads return `gcount()` and do not compute `offset + size`; zero/null guards are in Shared. Invalid IDs/indices return empty results through checked lookups. Negative values converted by the application to these unsigned parameters do not independently establish a library overflow.

### BASE-STORAGE-016 — ADDENDUM CORRECTION: silent submission/drop paths also omit completion

- **Disposition:** Retained and expanded under the existing source/submission failure ID; no new STORAGE finding for another lost-terminal-result path.
- **Severity:** Medium (unchanged)
- **Confidence:** High
- **Category:** Correctness / asynchronous error handling
- **Location:** `Source/Client/Impl/Storage.cxx:171-196,215-221`; `Source/Shared/Networking/Networking.hxx:143-153`; `Networking.cxx:123-131`.
- **Affected scope:** File-share submission/allocation/transport failure, notably successfully read shared files above the transport's packet limit; analogous pending download requests.

**Evidence:** `SendAsync` can return false on packet allocation failure, but its callers discard the result. Its true result means serialization and queue admission, not successful sending. Later `DispatchQueuedPackets` destroys packets when native Send returns nonzero without notifying the pending request. The actual vendor contract is a 32-MiB maximum packet (`Source/Vendor/Enet++/include/enet6/enetpp.hxx:79`; `Source/Vendor/Enet-IPv6/include/enet6/enet.h:222`); `peer.c:114-117` rejects oversized packets even before fragmentation. Shared-file bytes plus protocol fields form one serialized packet (`FileShareMessage.hxx:9-16`).

**Failure mechanism:** A valid nonempty 33-MiB local file can be read and serialized successfully, and its worker can set `finished=true`. Native dispatch rejects the oversized packet; the server never receives an upload to answer. The specific request remains registered and neither success nor failure reaches the game. Ordinary connection loss after queue admission has a similar missing result path. Checking only the worker's catch blocks or `SendAsync` boolean is therefore insufficient. No unsupported >UINT32_MAX file, malformed app input, or memory exhaustion is necessary for the 33-MiB case.

**Impact:** A normal sharing operation can hang with retained listener/request state. This corrects the baseline's narrower emphasis on source-read errors and exceptions. BASE-NET-006 already documents transport-cap failure for growing snapshots; the shared-file use should be coordinated rather than independently recounted in NET.

**Possible solutions:** Propagate send rejection/cancellation to an operation token; preflight the actual serialized limit and fail explicitly; or introduce bounded chunked file transfer with aggregate completion and a deadline.

**Recommended resolution:** Guarantee exactly one terminal result across read, serialization, queue admission, native send, connection retirement and server persistence. Register synchronously (013), roll back failed admission, and use operation IDs rather than retaining the worker's raw listener. Bounded chunking is preferable if large saves are supported; an explicit limit failure is safer than silent loss.

**Verification:** Proposed healthy-server cases just below/above the serialized 32-MiB threshold, a 33-MiB source, injected `SendAsync=false`, and disconnect after admission. Require successful bytes or one failure plus no pending request; worker completion alone is not the oracle. Keep source-read denial, empty-file, and cancellation cases. No transfer or test was run.
