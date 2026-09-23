# Fresh baseline review: filesystem_container.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Entire file read independently (463 lines). Static Windows review; no runtime reproduction.

## Checked
- Traced initial scan, decoded names, filename/share-ID maps, cached vector indices, swap-and-pop removal, stale lookup cleanup, create/share/copy publication, disk-space calls, and named/nameless subcontainers.
- Multi-container locks use deferred `std::lock`; index access has bounds checks; file-list snapshots own entry shared_ptrs. A list snapshot freezes membership, not contents/stat/metadata.
- Traced SharedFileUtils, Storage FileWrite/FileShare/download/close, CloudStorage operations, and authenticated server file handlers. Container parents are retained through SharedFileUtils/subcontainer ownership in these callers; no reachable parent use-after-free is asserted.
- Canonical component checks block ordinary traversal and existing outward symlinks. They do not pin paths against later local reparse-point replacement. This is recorded as a trust/TOCTOU limit rather than a demonstrated remote exploit.

## Findings

### BASE-UTIL-004 — Case-sensitive map keys alias the same Windows file
- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Shared_NoVer/filesystem_container/filesystem_container.cxx:78-104,113-135,144-200`
- **Affected scope:** Storage/cloud/share operations on ordinary case-insensitive Windows directories.

**Evidence / mechanism:** `sanitize_relative_path` normalizes separators and dot components but not Windows filename identity. `std::map<path,...>` compares spelling, while the physical encoded names retain ASCII case. Write `Save.bin`, then look up `save.bin`: the filesystem says it exists, the map misses, and line 92 asserts in Debug or returns null in Release. Creating both spellings inserts two entries for one physical file; either write replaces the other's bytes. A case-varied shared name can likewise obtain a separate ID for the same data.

**Impact:** Inconsistent existence/read results, duplicate counts/IDs, unintended overwrite, and stale entries after removal. Both spellings are individually portable names; the finding does not rely on forbidden Windows device names.

**Possible fixes:** Adopt a consistent Windows-equivalent key policy; or encode logical names injectively into physical filenames (including case), with an explicit case-sensitive logical API. Merely lowercasing ASCII misses broader Windows identity rules.

**Recommended fix:** Decide the logical name contract, implement one key/physical-name normalization policy everywhere, and reconcile/migrate existing aliases. Reject ambiguous aliases rather than silently registering a second entry. Apply the same decision to subcontainer maps.

**Verification:** Write/read/delete/share `Save.bin` and `save.bin`, restart, and check map count, index list, and ID mappings agree. Include directory-component case and Windows case-sensitive-directory configuration. Not run.

### BASE-UTIL-005 — Failed creation or metadata persistence is published as a live entry
- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Shared_NoVer/filesystem_container/filesystem_container.cxx:123-135,174-204`; entry `create_empty_file_if_not_exist:374-384`
- **Affected scope:** Storage creation and shared-file registration under filesystem errors.

**Evidence / mechanism:** Empty-file creation returns void and ignores mkdir/open failures. get_or_create inserts the entry into both indexes regardless. create_shared also publishes a share ID and ignores save_metadata's boolean. In a traversable/readable directory whose ACL denies file creation, path validation can succeed but file creation fails, producing a non-null indexed object for a file never created. If data succeeds but metadata fails, the shared ID exists only in memory and is lost at restart.

**Impact:** Ghost file counts/list entries after a failed write; callers' null checks cannot detect creation failure; non-durable share IDs and disk/cache disagreement. `StorageImpl::FileDownloaded` can fail its data write after publication; CloudStorage's failure path does not remove the ghost entry.

**Possible fixes:** Make creation return a status/error, defer publication until persistence succeeds, or roll back new registrations. For promoting an existing file to shared, retain its old metadata until a successful commit.

**Recommended fix:** Stage the operation, propagate creation and metadata errors, and update all indexes only after successful file/metadata creation. Preserve pre-existing entries on failure. Coordinate with BASE-UTIL-008's close checks.

**Verification:** In a readable/traversable parent, deny file/subdirectory creation; separately deny only metadata writes. Check null/error result, unchanged count/index, and restart consistency. Also exercise malformed parent paths, which may fail earlier during path validation. Not run.

### BASE-UTIL-011 — Dot subcontainer names collapse namespace boundaries
- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Shared_NoVer/filesystem_container/filesystem_container.cxx:434-459`
- **Affected scope:** Named cloud subcontainers.

**Evidence / mechanism:** `filename_encode_with_slashes` leaves `.` and `..` unchanged, then the string is appended as a filesystem component without validation. `get_subcontainer("..")` constructs `basepath/named_containers/..`, which normalizes to the parent container's base. It nevertheless creates a second container object with independent maps/locks for that same data/metadata directory. `"."` selects the named-containers directory itself. CloudStorage passes the container name directly into this API; the inspected cloud contract treats it as a name, not a relative navigation path.

**Impact:** Logical containers can alias parent storage; two caches can disagree about the same files and mutate them independently. This is bounded namespace confusion, not a claim of arbitrary traversal outside the configured storage root (slashes are encoded).

**Possible fixes:** Reject dot-only names, or reversibly encode them into ordinary components; a fully opaque component encoding also addresses other Windows aliases.

**Recommended fix:** Encode every accepted container name into one non-special, unique component and enforce strict containment beneath `named_containers`. Define migration for any existing dot-name data.

**Verification:** Exercise `null`, empty, `.`, `..`, normal names and encoded slash/percent names; assert distinct intended roots and independent file lists across restart. Not run.

### BASE-UTIL-012 — Symlink resolution during enumeration creates duplicate index entries
- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Shared_NoVer/filesystem_container/filesystem_container.cxx:29-42`; `filesystem_container_utils.cxx:56-64`
- **Affected scope:** Startup scan with an in-root Windows file symlink/alias.

**Evidence / mechanism:** The listing helper uses `std::filesystem::relative`, which weakly canonicalizes its arguments. With `files/a.bin` and `files/link.bin` pointing to it, both can be returned as `a.bin`. The constructor creates two entry objects, ignores the second map emplace failure, and pushes both into `fs_entry_index`. Removing the registered entry removes only one vector element, leaving count/name/ID enumeration inconsistent.

**Impact:** Duplicate or stale file-list entries and count/index divergence. Setup requires a local symlink-capable environment, not a remote-created link. An outward link can also make scanning fail containment; that is a startup-policy limit, not used as an exploit claim.

**Possible fixes:** Define a symlink policy and enumerate lexical relative names, or deduplicate resolved identities. In either case, publish into the index only if map insertion succeeded.

**Recommended fix:** Explicitly skip unsupported reparse/symlink entries, or preserve supported link identities intentionally; drive the index from successful canonical-key insertions. Keep startup and runtime identity policies consistent with BASE-UTIL-004.

**Verification:** Create one real file and an in-root Windows file symlink; reconstruct, enumerate, remove, and re-enumerate. Assert map/list counts and cache indices remain consistent. Also cover duplicate decoded names. Not run.

### BASE-UTIL-016 — Space-query failures become huge valid-looking capacities
- **Severity:** Low
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Shared_NoVer/filesystem_container/filesystem_container.cxx:365-381`
- **Affected scope:** SharedFileUtils disk-space adapters and cloud file-list capacity reporting.

**Evidence / mechanism:** Each function ignores the `error_code` from `std::filesystem::space`. Failed queries return `uintmax_t(-1)` for uncomputed fields; capacity/available are returned as enormous values, while subtracting two failure sentinels can report zero used. SharedFileUtils clamps the large values to UINT32_MAX, hiding the error as a plausible maximum quota.

**Impact:** A removed/unavailable storage location reports misleading capacity/usage instead of a failure or explicit unknown value. Low severity because this is reporting rather than direct file corruption.

**Possible fixes:** Return a result containing status and space_info, throw a translated storage error, or use a documented conservative sentinel.

**Recommended fix:** Obtain one checked space_info snapshot and propagate query failure to the API layer; do not interpret sentinel arithmetic as capacity data.

**Verification:** Query after removing the container root and on an unavailable location; verify failure reporting, then verify normal capacity/available/used values come from one successful query. Not run.
