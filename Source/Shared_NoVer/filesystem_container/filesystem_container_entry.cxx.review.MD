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
