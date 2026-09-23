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
