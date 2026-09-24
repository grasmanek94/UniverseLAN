# Fresh baseline review: filesystem_container_entry.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Entire file read independently (397 lines). Static review followed by coordinator runtime reproduction of BASE-UTIL-006/007; the other proposed verification cases remain unexecuted.

## Checked
- Traced portable/legacy metadata loading and stream rewind, shared-ID preservation on copy, data/metadata open/copy/write/delete failures, partial reads, physical versus metadata clocks, cache-index updates, and parent callbacks.
- Streams own their handles; path operations use error_code or catch filesystem exceptions. Destructor does not dereference the raw parent. SharedFileUtils and cloud parents remain owned in traced normal operation/teardown; no parent use-after-free claim.
- No entry-wide I/O lock exists. FileShare has a real background read worker while FileWrite can run on the caller thread; membership snapshots do not snapshot bytes. Metadata maps lock internally, but their locks do not make a complete file operation transactional.
- Metadata loading tries the legacy archive after portable failure, then throws if both fail; corrupt metadata can abort container initialization. This recovery limit is relevant to persistence fixes below.

## Findings

### BASE-UTIL-006 — A failed delete still forgets the surviving file and its metadata
- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Shared_NoVer/filesystem_container/filesystem_container_entry.cxx:91-112`, `unlink`
- **Affected scope:** Storage deletion/shared close/cloud deletion on Windows.

**Evidence / mechanism:** A sharing violation, read-only attribute, or ACL can make removal of the data file fail. The function continues deleting metadata, unconditionally removes the entry from its parent maps/index, and resets its in-memory metadata. Returning false does not undo those mutations. Later `get(name)` sees an existing file but no map entry and asserts in Debug or returns null in Release.

**Impact:** A failed deletion makes a still-present file inaccessible through the current container, can lose its shared ID/user metadata, and changes enumerated count. Standard Windows handle-sharing failures suffice; no prohibited object lifetime is involved.

**Possible fixes:** Leave registration intact when data deletion fails; use a transactional tombstone/recovery protocol if data and metadata must be removed together; reconcile known partial deletion states explicitly.

**Recommended fix:** Delete/confirm absence of the data file first, preserving registration and metadata on failure. Only detach/reset once the data deletion has committed, and surface metadata cleanup failure distinctly.

**Verification:** The coordinator executed this case on MSVC x64 Debug against the built baseline. A handle allowing read/write but not FILE_SHARE_DELETE caused `unlink()` to return false; the file still existed while `get_file_count()` became zero. This reproduces the failed-delete/index divergence. See `.ai/review-baseline/VERIFICATION.MD`. Retry behavior after a fix remains proposed validation.

### BASE-UTIL-007 — Filesystem clock seconds are exposed as Unix timestamps
- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Shared_NoVer/filesystem_container/filesystem_container_entry.cxx:188-195`, `get_timestamp`
- **Affected scope:** Storage timestamps and cloud SDK versions using physical file time.

**Evidence / mechanism:** `last_write_time(...).time_since_epoch()` is divided by seconds without converting clock epochs. MSVC file_clock starts at 1601-01-01, not the Unix epoch. `SharedFileUtils::GetTimestamp:256-281` clamps that result to UINT32_MAX for ordinary current dates; older cloud paths narrow it directly. CloudStorage's timestamp contract explicitly says Unix timestamp.

**Impact:** File changes receive constant saturated or incorrectly wrapped timestamps, breaking timestamp comparison and synchronization decisions. Metadata timestamp methods use system-clock Unix seconds and are a separate, correct representation.

**Possible fixes:** C++20 `clock_cast<system_clock>` before duration conversion, or a well-tested platform conversion if the supported standard library lacks clock_cast.

**Recommended fix:** Convert to system_clock and only then convert/range-check seconds. Avoid assuming file_clock has `to_sys`: Microsoft's implementation uses to_utc/from_utc. Reference consulted: https://learn.microsoft.com/en-us/cpp/standard-library/file-clock-class?view=msvc-170 .

**Verification:** The coordinator set the physical write time to Unix second 1700000000 using C++20 clock conversion. The actual baseline entry getter returned 13344473600 on MSVC x64 Debug. This reproduces the epoch error. Public DLL timestamp paths and x86 remain statically traced, not executed. See `.ai/review-baseline/VERIFICATION.MD`.

### BASE-UTIL-008 — Write success is decided before buffered data is closed
- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Shared_NoVer/filesystem_container/filesystem_container_entry.cxx:291-308,351-371`
- **Affected scope:** Data writes and metadata persistence, including CloudStorage buffer PutFile and downloaded shared files.

**Evidence / mechanism:** Both functions return `fstream.good()` while the stream is still open. A small write can remain in the stream buffer. The return value is evaluated before destruction flushes/closes the file, and destructor-time flush failure cannot change it. Cereal writes through the streambuf; successful serialization likewise does not prove the final close succeeded.

**Impact:** Disk-full/device errors detected during flush/close can be reported as success, leaving incomplete data or a corrupt truncated metadata archive. This is ordinary completion error handling, not a demand that every write be power-loss durable.

**Possible fixes:** Explicitly flush/close and inspect status; use an error-reporting file abstraction; for preservation of old data, write a temporary and replace after successful completion.

**Recommended fix:** Close explicitly and reject any write/flush/close error. Persist metadata via a completed temporary plus replacement so a failure does not destroy the previous archive. Propagate the result to callers (some cloud callers currently ignore it).

**Verification:** Fault-inject a close/flush failure after a buffered short write and verify false/error propagation. For metadata, confirm the previous archive remains readable after failure. Not run.

### BASE-UTIL-009 — Copy rollback deletes a destination that existed before the operation
- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Shared_NoVer/filesystem_container/filesystem_container_entry.cxx:150-176`, `copy_to(filesystem_entry&)`
- **Affected scope:** Copying local/shared entries with metadata and an existing destination.

**Evidence / mechanism:** Data is copied with overwrite_existing before metadata copying. If data succeeds but metadata fails (missing/unreadable source metadata or denied destination metadata), rollback removes the destination data file rather than restoring its previous contents. The reverse branch can remove existing metadata after data copying failed. Destination registration is not rolled back. SharedFileUtils copy helpers can supply existing destination entries.

**Impact:** A reported copy failure destroys previously valid destination data/metadata and leaves stale indexed state. This requires an I/O/metadata failure and an existing destination; normal successful copying is not alleged to erase data.

**Possible fixes:** Stage both artifacts then commit with backups/recovery; alternatively forbid overwriting existing destinations, which changes behavior.

**Recommended fix:** Use staging files and a defined two-artifact commit/rollback protocol. Roll back only artifacts created by the current operation, preserving the original destination and shared ID if commit fails.

**Verification:** Populate a destination, make the source metadata unavailable while data remains readable, and copy. Failure must preserve original destination bytes, metadata and index membership. Repeat with metadata success/data failure. Not run.

### BASE-UTIL-010 — A short read returns zero padding as file contents
- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Shared_NoVer/filesystem_container/filesystem_container_entry.cxx:238-269`, vector `read`
- **Affected scope:** Background file sharing and cloud/shared whole-file reads.

**Evidence / mechanism:** The vector is resized to the initial tellg size. A shorter read sets failbit and eofbit, but `if (!data_stream && !data_stream.eof())` accepts that state. The vector is never reduced to gcount. If FileShare's worker measures N bytes and a subsequent FileWrite truncates the same file before its read, it returns N bytes with a zero-initialized tail, or entirely zeros if the new length is zero. The caller serializes that vector as valid contents.

**Impact:** A normal asynchronous upload racing a save can send padded/corrupt data instead of either a coherent file version or an explicit failure. No external filesystem editor is required.

**Possible fixes:** Fail on any incomplete exact-size read; return only gcount with an explicit partial-read contract; or synchronize reads with replacement writes to obtain stable snapshots.

**Recommended fix:** Require the promised byte count and propagate an error distinguishable from a legitimate empty file; use per-entry snapshot/replace synchronization for sharing concurrent with save writes.

**Verification:** Pause after tellg, truncate via FileWrite, resume, and assert no zero-padded success is emitted. Also cover empty files and seek/read errors. Not run.

## Thorough re-review addendum — b30e8387 (2026-09-24)

### Existing-ID corrections, refinements and dispositions

- **BASE-UTIL-006 — retained, Medium / High confidence / Correctness.** The reported failed-delete behavior is unchanged. Add a separate verification case where data removal succeeds but metadata removal fails: unregister/reset leaves an orphan archive capable of being loaded on later recreation. ADD-UTIL-001 (container implementation sidecar) covers success-only stale-removal schedules and their identity/index consequences, not another OS-error instance. Preserving the old entry on failure is necessary but does not by itself fix that new concurrency finding.
- **BASE-UTIL-007 — retained, Medium / High confidence / Correctness; scope clarified.** Physical time at lines 188-195 still needs file-clock to system-clock conversion on MSVC. `HAS_ICLOUDSTORAGE_PUTFILE_TIMESTAMP` starts at 1.148.7 (`Source/galaxy_sdk_features.cmake:215`): earlier cloud paths use physical time, later ones use metadata time. Metadata timestamp storage has the correct epoch for normal nonnegative SDK timestamps; that statement does not imply arbitrary negative `int64_t` timestamps or signed/unsigned conversions are universally valid. SDK callers supply `uint32_t`, so that theoretical negative-value case is not another confirmed production finding. The baseline's historical reproduction remains historical, not a test run in this pass.
- **BASE-UTIL-008 — retained, Medium / High confidence / Correctness.** Checking `good()` before stream destruction misses buffered completion errors. Also, opening the live archive with truncation destroys its previous version before serialization succeeds; the original temporary/replace recommendation remains necessary. ADD-UTIL-003 below concerns overlapping successful serializers, which explicit flush/close checks alone cannot fix. No second generic disk-full finding is counted.
- **BASE-UTIL-009 — retained, Medium / High confidence / Correctness; rollback coverage corrected/expanded.** The original two-copy rollback finding is sound. The third phase is also significant: when both copies succeed but `notify_copy_done` fails its final `save_metadata`, lines 164-166 never enter the rollback at 167-173. It has already assigned destination maps and may have installed the source's on-disk share ID at line 161 before trying to save the destination ID. A failure can leave new data, changed in-memory metadata and a wrong/truncated disk archive. Thus a complete fix must stage/commit the destination metadata representation, not merely back up the two `copy_file` operations. Proposed verification adds a failure specifically at final destination metadata save and checks bytes, ID, attributes and membership against the pre-copy snapshot. This remains one BASE ID.
- **BASE-UTIL-010 — retained, Medium / High confidence / Correctness.** EOF after a shrink remains accepted without resizing to `gcount`, so the old-size vector contains zero padding. `read(char*,...)` instead returns the actual `gcount`; do not claim both overloads zero-pad. ADD-UTIL-005 below is a different, no-concurrency x86 size-wrap mechanism. Neither requires a new broad "all reads fail" finding.

### ADD-UTIL-003 — Per-map locks do not serialize concurrent writes to the same metadata archive

- **Severity:** Medium
- **Confidence:** High
- **Category:** Concurrency
- **Location:** `Source/Shared_NoVer/filesystem_container/filesystem_container_entry.cxx:351-371` (`save_metadata`), `22-54` (reload); `filesystem_container_metadata.hxx:27-32,65-72` (separately locked map serialization).
- **Affected scope:** Concurrent Windows cloud puts/metadata saves on the same entry. Production route: `Client/Impl/CloudStorage.cxx:488-540` and callback upload `374-452`; file entries are returned after container lookup locks have been released.

**Evidence:** Each save opens a separate truncating fstream on the same final pathname before Cereal takes either metadata-map lock. The outer archive has no save/entry mutex. Cereal serializes share ID, then user map, then system map. Map locks protect the map while traversing it, not the file handle, stream buffers, archive lifetime, or a whole metadata snapshot. The copy assignment of an individual metadata map correctly uses `std::lock`; that is counterevidence to alleging an unlocked map copy, but does not serialize these saves.

**Version/reachability qualification:** The large, variable user-map schedule below has a concrete current SDK route through `HAS_ICLOUDSTORAGE_METADATAIDX_FUNCS` (feature interval 1.148.6–1.148.12, with 1.148.11 present). `1.148.11/galaxy/ICloudStorage.h:362-430` accepts equally sized NULL-terminated metadata key/value arrays and states no aggregate byte cap there; `CloudStorage.cxx:507-514` copies their strings. This does not depend on oversized invalid hashes in newer SDKs. The no-save-lock defect is common code, but not every small same-size concurrent archive necessarily ends up unreadable; record lengths and write timing determine that symptom.

**Failure mechanism / interleaving:** T1 opens the archive and serializes a large user-map snapshot A, large enough to send some bytes to its handle while retaining a final buffer. After T1 releases the user-map mutex and before it finishes the archive, T2 changes that map to a different, larger serialized layout B, opens/truncates the same file, writes a complete B archive and closes it. T1 then resumes writing its system map and pending tail at T1's own file offsets. Choose differing string lengths so this tail overwrites the middle of B; the resulting file can contain B's lengths/header with A's payload/system bytes. Ordinary Windows CRT shared opens permit concurrent streams here. Both saves can report success and both closes can succeed. Even without an invalid byte layout, user/system fields can come from different logical updates because no common snapshot is taken.

**Impact:** Lost or mismatched attributes and potentially unreadable metadata after otherwise successful calls. On restart, portable load followed by legacy fallback can throw from the entry constructor, aborting container initialization. The trigger is same-entry concurrency, not simulated media failure, and no remote filesystem attacker is required.

**Possible solutions:** Serialize all same-entry metadata mutations/snapshot and persistence under one operation lock; or snapshot under a common metadata lock, write unique temporary archives and commit under a versioned save lock. A unique temporary prevents byte interleaving but still needs ordering/version rules to avoid committing an older snapshot over a newer one.

**Recommended resolution:** Introduce a complete-entry transaction/snapshot policy coordinated with ADD-UTIL-001's membership locks. Produce one owned metadata record, finish/check a unique temporary, then atomically replace under a coherent commit policy. Do not hold a map lock while acquiring a container lock in an order that can invert create/share/remove. Coordinate caller-side file bytes, timestamp/hash and savegame fields if they must describe the same file version.

**Verification:** Force the schedule above with two metadata payloads exceeding the stream buffer and different key/value lengths. Verify every resulting archive loads and equals a committed complete snapshot, including ID/user/system fields; interpose a reload while saves run. Repeat after explicit flush/close checks to show those checks alone are insufficient. Current tests exercise sequential map access and one save/reload only. All concurrency verification is proposed, not run.

### ADD-UTIL-004 — Successful copy can leave obsolete attributes or the source share ID on disk

- **Severity:** Informational (latent helper defect; no current production route identified)
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Shared_NoVer/filesystem_container/filesystem_container_entry.cxx:135-147,150-176`; `filesystem_container_metadata.cxx:151-157` (`empty`).
- **Affected scope:** The compiled entry-to-entry copy utility when the destination's final metadata is empty (share ID zero, both maps empty). `Shared/SharedFileUtils.cxx:331-347` exposes this direction through `CopyFromSharedToLocal`; no current production invocation was found. Reconciliation excludes this dormant route from current confirmed-defect totals.

**Evidence:** `notify_copy_done` copies only the two maps, deliberately preserving the destination share ID. It then treats `metadata.empty()` as successful persistence without saving or deleting the existing archive. Earlier `copy_to` either skips archive copying when the source metadata is empty or copies the source archive verbatim when it is nonempty.

**Failure mechanism:**

1. Destination D is unshared and has previously saved user attributes. Source S has no metadata. Data copy succeeds, physical archive copy is skipped, and notification clears D's maps. D is now empty, so saving is skipped as well. Copy returns true; reloading D resurrects its pre-copy attributes from the untouched archive.
2. S is shared but has no user/system attributes; its archive contains only the nonzero share ID and empty maps. Copy to unshared D copies this archive, keeps D's in-memory ID zero, then skips saving because D is empty. The live destination reports ID zero, while restart loads S's ID and registers D as shared. No I/O failure or overlap is necessary.

**Impact:** Successful utility copies disagree with their own persistent metadata and can change sharing identity at restart. This is separate from BASE-UTIL-009's failed-copy rollback. Normal local-to-shared copying keeps a nonzero destination ID and therefore executes the save; that active path does not demonstrate this particular empty-state bug.

**Possible solutions:** Always serialize the final destination metadata, including an empty record; or remove any destination archive when the final metadata is empty, with checked completion and rollback. Avoid copying the source archive only to overwrite its identity later.

**Recommended resolution:** Construct the final destination record with its intended ID, then persist that exact record as part of the copy transaction. Include deletion/empty state in the transaction rather than treating emptiness as evidence that nothing needs changing.

**Verification:** Copy a metadata-free source onto an unshared destination with saved attributes, and a share-ID-only source onto a new unshared destination. Assert success, compare live metadata/ID with a reconstructed container, and require equality in both cases. Also retain the existing successful local-to-shared test as counterevidence/regression coverage. Proposed only.

### ADD-UTIL-005 — Windows x86 silently narrows large on-disk sizes before checking or reading them

- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Shared_NoVer/filesystem_container/filesystem_container_entry.cxx:223-230` (`get_size`), `248-269` (whole-file `read`); `filesystem_container_entry.hxx:54-60` (size-return/API widths).
- **Affected scope:** Supported Windows x86 builds reading files of at least 4 GiB. Root `CMakeLists.txt:46-51` explicitly selects x86/x64. Such files can be present from a 64-bit instance or be produced in bounded chunks by cloud callback PutFile (`Client/Impl/CloudStorage.cxx:386-409`), which has no total-length guard.

**Evidence:** `file_size` and the stream position can represent a 64-bit file size, but both are cast directly to 32-bit `size_t` on x86. The vector read then requests only the already-truncated vector size. `SharedFileUtils::GetSize:228-253` clamps after this narrowing, so its UINT32_MAX bound cannot recover the true size. Cloud's buffer-size check similarly uses the narrowed getter (`CloudStorage.cxx:236-244`).

**Failure mechanism:** For a file of `0x1_0000_0008` bytes, x86 `get_size()` returns 8 and vector `read()` allocates and reads only eight bytes. The stream remains good: the requested small read completed, so this is not BASE-UTIL-010's accepted EOF/zero-padding case. At exactly 4 GiB, the reported size/vector length becomes zero. A small cloud buffer can pass the full-file capacity check and receive only a prefix as a successful operation.

**Impact:** Silent truncation/misreporting of large saved data without needing a correspondingly large memory allocation, file shrink, or OS failure. This is a conditional large-file/x86 defect, not a claim that ordinary 32-bit SDK buffer lengths overflow MSVC's 64-bit stream offsets/counts.

**Possible solutions:** Keep a wide checked size in the utility and reject values beyond the consumer's limits; or provide chunked reads with an explicit 64-bit total. Validate vector maximum size, size_t and streamsize before conversion/allocation. Enforce any chosen SDK file-size limit before upload/publication too.

**Recommended resolution:** Carry `uintmax_t`/`uint64_t` through stat and range checks, return explicit oversize/error status instead of a wrapped success, and narrow only after proving representability. Coordinate callback/API-width behavior with STORAGE rather than merely saturating a value that is then used as a buffer-safety check.

**Verification:** On Windows x86, use a sparse file of exactly 4 GiB and 4 GiB + 8 with a known prefix, and require an oversize result or complete supported streaming behavior. Confirm no zero/eight-byte whole-file success; check the cloud buffer guard. Contrast x64 and ordinary small files, and inspect boundary sizes without allocating multi-gigabyte vectors. No probe/build/test was performed.
