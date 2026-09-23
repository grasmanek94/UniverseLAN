# Fresh baseline review: CloudStorage.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Windows focus. Entire current file read, lines 1–649; assigned-source diff against baseline was empty. Fresh static inspection; no previous report consulted and no build or runtime reproduction performed.

## File-specific inspection

- Traced both upload and download overloads, metadata-only retrieval, callback-scoped enumeration, deletion, savegame grouping, and both hash overloads.
- Contract context: `Source/DLLs/1.152.11/galaxy/ICloudStorage.h`, legacy metadata methods in `1.148.11/galaxy/ICloudStorage.h`, and the feature boundaries in `Source/galaxy_sdk_features.cmake` (cloud 1.148.6; timestamp 1.148.7; hash getter 1.148.11; savegame 1.148.14; hashing 1.148.15).
- Followed `SharedFileUtils`, filesystem container/entry/metadata implementations, `ConstHash.hxx`, registrar notification templates, `DelayRunner`, and `GalaxyDLL::ProcessData`.
- Bounds checks precede indexed vector access. Buffered downloads reject undersized buffers. Streaming downloads retain the subcontainer and copy container/name strings; ordinary deferred notification strings are copied by `NotificationParamScopeExtender`. These are useful protections, but do not establish snapshot or listener lifetime safety.
- The FNV loop consistently carries its state across chunks and includes embedded NUL bytes. The SDK excerpt does not establish a particular hash algorithm; no claim that it mandates MD5 is made. Decimal FNV output versus the documented hexadecimal getter representation requires compatibility validation in addition to the definite missing-hash defect below.
- Cloud operations are local filesystem emulation. Whole-volume quota values, blocking upload work, 256-byte filename scratch storage, and a shared callback cache are architectural limits. No remote cloud confidentiality or service-authorization guarantee is inferred.

## Findings

### [BASE-STORAGE-001] Failed replacement uploads destroy the previous save

- **Severity:** High
- **Confidence:** High — mechanically evident failure path, not runtime-reproduced.
- **Category:** Correctness / data loss
- **Location:** `Source/Client/Impl/CloudStorage.cxx:374–417,488–505`, `PutFile` overloads.
- **Affected scope:** Existing cloud files; all cloud-enabled versions, including Windows.

**Evidence:** Streaming `PutFile` opens the live file with `out | trunc | binary` at line 386 before invoking `readFunc`. A negative read return reports failure and returns without restoring the previous contents. Buffered `PutFile` calls `filesystem_entry::write`, which likewise opens the destination with truncation (`filesystem_container_entry.cxx:291–308`).

**Failure mechanism:** Save a valid file A, then replace it through a callback that returns one chunk and subsequently `-1` (for example, a failed source-file read). A has already been truncated; the failure leaves only the prefix of B. A read error on the first call leaves an empty file. Disk-full failure during a buffered replacement has the same destructive exposure. No crash or malicious input is required.

**Impact:** The last usable save can be lost even though the game receives a failed-upload callback. Reporting failure alone cannot recover A. Metadata can still describe A while the bytes contain a fragment of B.

**Possible solutions:** Stage uploads in a separate file; keep a backup and rollback; or maintain versioned objects with a committed-generation marker. Buffering the entire upload first prevents source-callback failures but does not solve destination-write failure.

**Recommended resolution:** Stage data and metadata beside the destination, verify successful write/flush/close, then commit with a Windows-compatible replacement strategy. Preserve the previous committed generation until both components are recoverable; clean abandoned staging files after failure.

**Verification:** Start with known A; inject read failure before and after the first chunk, destination disk-full, and metadata failure. Require exactly one failure notification and byte-for-byte preservation of A and its metadata after reopening the container. Proposed tests, not executed.

### [BASE-STORAGE-002] Filesystem failures are converted into successful cloud operations

- **Severity:** High
- **Confidence:** High — explicit ignored results and ambiguous read results.
- **Category:** Correctness / error handling
- **Location:** `Source/Client/Impl/CloudStorage.cxx:162–200,244–267,404–456,539–544,575–580`.
- **Affected scope:** Cloud downloads, streaming uploads, metadata persistence, and deletion.

**Evidence:** The streaming upload never checks `file_stream` after writes or explicitly verifies close. Both uploads discard `save_metadata()`'s boolean. Downloads accept `read()`'s empty vector or zero count as successful content. `DeleteFile` discards `unlink()`'s boolean. The Shared entry implementation returns empty/zero on open failure and false on failed removal or metadata serialization.

**Failure mechanism:** On Windows, a nonempty file can pass existence checks while an incompatible sharing handle prevents opening it for read. The buffer overload then reports success with zero bytes; the callback overload supplies empty data and can report success. A full volume can fail a streaming write after open, yet the read callback reaches EOF and success is queued. A read-only file or delete-denying handle makes unlink fail, but deletion is still acknowledged. Metadata directory write denial similarly leaves a successful upload without persisted savegame/hash information.

**Impact:** Games can accept incomplete downloads, assume saves are durable, or remove local recovery copies following a false success. Failed unlink also interacts with the Shared layer's unconditional cache removal; that root needs coordination with UTIL.

**Possible solutions:** Return typed I/O results carrying status and byte count; check all existing booleans plus stream flush/close; or centralize transaction completion in the filesystem layer.

**Recommended resolution:** Define success only after all required data and metadata operations complete. Distinguish a valid empty file from failed reads, translate errors to the available failure reasons, and preserve deletion cache state on failed removal. Implement together with BASE-STORAGE-001; checking results alone does not restore overwritten data.

**Verification:** Use a disposable Windows test directory and deny read/delete sharing separately; deny metadata writes; inject short writes and close failures. Assert failure rather than success and verify disk/cache agreement after restarting. Include a genuinely empty file as a success control.

### [BASE-STORAGE-005] Conditional deletion ignores the expected hash

- **Severity:** High
- **Confidence:** High
- **Category:** Correctness / data loss
- **Location:** `Source/Client/Impl/CloudStorage.cxx:549–580`, `DeleteFile`.
- **Affected scope:** Hash-enabled cloud API versions; stale-save conflict handling.

**Evidence:** `expectedHash` is never examined. The TODO at line 575 is followed directly by `file_entry->unlink()`. SDK `ICloudStorage.h:469–482` explicitly says the parameter prevents deletion when the file changed in the meantime, and declares `FAILURE_REASON_CONFLICT` at line 194.

**Failure mechanism:** A game records hash H1, later uploads replacement H2 to the same name, then cleans up the earlier version using `DeleteFile(..., H1)`. The current H2 file is deleted. This can happen sequentially in one process; no multi-client cloud service is necessary.

**Impact:** Newer saves are deleted by an operation expressly guarded against that outcome.

**Possible solutions:** Compare reliable stored content hashes; recompute hashes before deleting; or associate version/generation identities with each object and compare under a transaction lock.

**Recommended resolution:** Implement compare-and-delete atomically with respect to writes, using the content/hash contract fixed by BASE-STORAGE-004. On mismatch, return conflict without changing bytes, metadata, or indexes. Continue supporting unconditional deletion when the optional guard is absent.

**Verification:** Put A with H1, replace with B/H2, attempt deletion with H1, then verify conflict and intact B. Matching H2 must delete; absent guard must retain documented unconditional behavior. Also test a writer interleaving between comparison and deletion.

### [BASE-STORAGE-009] Deferred cloud listeners survive explicit unregistration

- **Severity:** High
- **Confidence:** High
- **Category:** Memory Safety / asynchronous lifetime
- **Location:** `Source/Client/Impl/CloudStorage.cxx:152–202`, deferred `GetFile`; queued `NotifyAll` completions throughout this file.
- **Affected scope:** Callers cancelling a cloud operation and destroying its listener before the next `ProcessData`.

**Evidence:** Streaming download captures the raw listener in a `DelayRunner` lambda and invokes `NotifyAllNow(listener, ...)`. No request token is registered. `ListenerRegistrar.cxx:50–68` removes only global registrations and request-helper entries. SDK `IListenerRegistrar.h:156–165` promises unregistration from all pending asynchronous calls. The generic `NotifyAll` queue similarly retains raw specific listeners (`ListenerRegistrar.hxx:309–322`).

**Failure mechanism:** Issue `GetFile` with a heap listener, explicitly unregister that listener, destroy it, and then pump events. Keep the write callback and its user data alive to isolate the listener issue. The queued task still reaches the listener's virtual function. This is a single-threaded cancellation sequence, not a race requiring concurrent destruction.

**Impact:** Use-after-free when a load dialog or game state cancels an outstanding operation. Generic queued completions affect additional interfaces and should be deduplicated with the CORE registrar review.

**Possible solutions:** Use registrar-managed cancellable request records; queue a registration generation/token rather than a raw listener; or maintain explicit cancellable cloud operation objects.

**Recommended resolution:** Register pending operations synchronously and resolve their listener only at dispatch, respecting unregistration. Direct cloud lambdas must join that mechanism even after generic `NotifyAll` is fixed. Preserve delivery to still-registered global listeners according to the SDK contract.

**Verification:** Cancel and destroy listeners before pumping each cloud operation, then pump under Windows ASan. Assert no callback to removed listeners, no invalid access, and one callback to an uncancelled control. Test both direct streaming lambdas and ordinary queued success/failure completions.

### [BASE-STORAGE-003] Streaming callback return contracts are not honored

- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness / API contract
- **Location:** `Source/Client/Impl/CloudStorage.cxx:162–169,399–402,613–615`.
- **Affected scope:** Callback download, callback upload, and callback hash calculation.

**Evidence:** `GetFile` treats every nonnegative `writeFunc` result as complete success, irrespective of bytes accepted. `PutFile` and `CalculateHash` ignore `rewindFunc`'s return. SDK `ICloudStorage.h:265–273,343–353` defines the former as a byte count and the latter as zero on success/nonzero on error.

**Failure mechanism:** A sink accepts only part of a chunk, or returns zero because it cannot make progress, and the rest is discarded. A source fails to rewind from EOF, returns zero on its next read, and the upload succeeds as an empty file; hash calculation likewise hashes the wrong stream position. These are documented failure signals, not invalid pointers supplied by the game.

**Impact:** Truncated downloads, empty replacements, or hashes of incomplete content despite successful completion. BASE-STORAGE-001 makes the failed-rewind upload especially destructive.

**Possible solutions:** Retry remaining sink bytes when partial writes are supported, or fail a short result; stop immediately on failed rewind. Use bounded chunks compatible with the SDK's signed `int` callback size.

**Recommended resolution:** Validate rewind before modifying the live object. Require all bytes to be consumed (with bounded progress checks) and deliver the corresponding failure instead of success. Apply the same rewind policy to hashing and upload.

**Verification:** Use callbacks that accept half a chunk, zero bytes, or `-1`, and rewind callbacks that return nonzero with the cursor at EOF. Check exact delivered bytes, terminal result, and preservation of the old save. Also compare buffer and streaming hashes across different chunk boundaries.

### [BASE-STORAGE-004] Omitted hashes remain placeholders or stale values

- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness / API contract
- **Location:** `Source/Client/Impl/CloudStorage.cxx:108–125,445–449,533–537,602–645`.
- **Affected scope:** Hash-enabled `PutFile` and `GetFileHashByIndex`.

**Evidence:** Upload only sets `HASH` when `hash` is nonnull. It never invokes either calculation path. A null hash on a new file yields `DEFAULT_HASH`; an empty string is stored literally; overwriting with null preserves any old hash. SDK `ICloudStorage.h:374,406` explicitly requires internal calculation for null or empty supplied hashes.

**Failure mechanism:** Perform a default-argument upload and list it: the returned hash does not identify the content. Upload A with an explicit H1, overwrite with B omitting the hash, and H1 remains. This is reachable using the normal API defaults.

**Impact:** Change detection and conflict resolution can treat different saves as identical or continuously re-upload unchanged data. A future fix to conditional deletion remains unsafe if it trusts this stale metadata.

**Possible solutions:** Compute and persist a content hash during every upload lacking an explicit one; recompute on enumeration; or store a validated versioned hash record alongside the committed bytes.

**Recommended resolution:** Share a single content-hash implementation between `CalculateHash` and both uploads, treating null and empty identically and replacing stale metadata. Validate the actual Galaxy algorithm/encoding with known vectors before asserting interoperability; the inspected header alone does not specify MD5.

**Verification:** For both upload overloads, compare the enumerated hash with `CalculateHash` for the same binary payload. Repeat with null, empty, and explicit hash, overwrite with different bytes, and reopen the container. Test vectors must include embedded NULs and multiple callback chunk sizes. Existing `Host/CloudStorage.cxx` supplies a fixed hash and misses this behavior.

### [BASE-STORAGE-006] Closing a savegame does not advance its identity

- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Client/Impl/CloudStorage.cxx:24–31,583–597`.
- **Affected scope:** Savegame-enabled cloud versions; ordinary sequential grouping.

**Evidence:** Grouped writes return `unique_savegame_id_counter.load()` without incrementing it. `OpenSavegame` only sets the progress flag false; `CloseSavegame` only sets it true. The first subsequent ungrouped write uses `fetch_add(1)`'s old value. SDK `ICloudStorage.h:484–496` promises new savegame grouping and different IDs after close.

**Failure mechanism:** `Open; Put A; Close; Open; Put B; Close` gives A and B the same ID. Even `Open; Put A; Close; Put B` reuses A's ID for B. Neither sequence requires concurrency or timestamp collision.

**Impact:** Separate saves can be grouped as one generation by game save browsers, synchronization, or retention logic.

**Possible solutions:** Allocate a fresh identity on group open or advance the sequence at close; use a separate active-group identity and per-object identity generator.

**Recommended resolution:** Model a group explicitly and allocate a fresh ID for each group and each ungrouped write. Synchronize the group flag and identity together; an atomic counter alone does not protect the plain boolean or the compound invariant. Define nested-open behavior and restart uniqueness separately.

**Verification:** Check equality within one group, inequality across two consecutive groups, and inequality for the first ungrouped write after close. Test no intervening sleep. Later validate cross-session uniqueness rather than relying solely on second-resolution wall time.

### [BASE-STORAGE-007] Callback-scoped lists and metadata are overwritten before delivery

- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness / asynchronous state
- **Location:** `Source/Client/Impl/CloudStorage.cxx:47–60,63–125,244–267,293–340`.
- **Affected scope:** Multiple outstanding list requests; legacy metadata-index getters with buffered/metadata-only requests.

**Evidence:** `GetFileList` immediately overwrites the single `container_file_list`, then queues only count/quota arguments. Buffered `GetFile` and `GetFileMetadata` similarly overwrite `last_metadata_request` before queueing their completion. Getters read those members, not request-specific state. SDK contracts make these getters valid in the respective completion callback.

**Failure mechanism:** Queue a list for container A (two files), then one for B (one file), and only then call `ProcessData`. A's callback gets count 2 but its getters read B; index 1 returns the bounds-failure value. For legacy metadata, queue two files with different tags: the first callback reads the second file's tags. Locks do not fix this single-threaded sequencing error.

**Impact:** Wrong names, hashes, sizes, or tags can be associated with a container/save; a valid callback index can appear absent.

**Possible solutions:** Capture a complete result snapshot in each queued operation; serialize request execution and callback delivery; or maintain callback-local context stacks.

**Recommended resolution:** Publish each request's immutable snapshot only for the duration of its callback, with restoration for nested/reentrant operations. Capture values rather than only mutable entry pointers when timestamp/hash consistency matters.

**Verification:** Queue two containers before pumping and enumerate all reported indexes in both callbacks. Repeat with legacy metadata calls and with a callback starting another request before finishing its current enumeration. Require each callback to observe its own result.

### [BASE-STORAGE-008] Missing savegame metadata throws through download APIs

- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness / exception handling
- **Location:** `Source/Client/Impl/CloudStorage.cxx:253–255,301–303`.
- **Affected scope:** Buffer downloads and metadata-only reads in savegame-enabled versions.

**Evidence:** Both paths use `std::stol(file_entry->get_metadata(SaveGameTypeKey))` without a default or catch. The entry getter defaults to an empty string. By contrast, streaming download uses default `"0"` and catches conversion errors at lines 181–186. Metadata is stored separately and its save failure is ignored by uploads.

**Failure mechanism:** Successfully write the data file while metadata creation is denied, then restart with readable data and absent metadata. The container loads the file with an empty metadata map. `GetFileMetadata` or buffered `GetFile` calls `stol("")`, throwing instead of returning a listener result. Older cloud entries without savegame fields are another migration path; arbitrary archive corruption is not required.

**Impact:** An otherwise readable save cannot be loaded through these overloads; an uncaught exception can terminate the game. Streaming and buffer behavior diverge.

**Possible solutions:** Default missing fields to undefined; use nonthrowing checked conversion; or reject invalid metadata through the failure callback.

**Recommended resolution:** Centralize savegame metadata decoding for all three methods. Define absence as the SDK's undefined type when backward-compatible, validate enum range, and report actual corruption consistently without allowing conversion exceptions across the API boundary.

**Verification:** Reopen files with absent fields, empty/nonnumeric/out-of-range type strings, and a valid type. Compare all download/metadata overloads and assert one terminal callback with no escaping conversion exception.
