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

## Thorough re-review addendum — b30e8387 (2026-09-24)

All 40 assigned production inputs were reread before the baseline findings. The source comparison with `b30e83872c0006e8240c8b4f565da5351bf10080` is empty. The following sections preserve the original findings and distinguish fresh mechanisms from their consequences. Verification below is proposed, not executed.

### Existing-ID dispositions and evidence refinements

- **BASE-UTIL-004 — retained, Medium / High confidence / Correctness.** Case identity also affects `named_subcontainers:450-459`: `Saves` and `saves` get independent objects and locks for one ordinary Windows directory. The filename encoder preserves ASCII case. A case-folded map alone needs a corresponding physical-name and restart policy; the initial containment check is not an identity policy. Windows directories explicitly configured as case-sensitive are counterevidence to a universal alias claim. Device names/trailing dots are not needed to establish this finding.
- **BASE-UTIL-005 — retained, Medium / High confidence / Correctness.** The shared-ID constructor itself attempts an unchecked save (`filesystem_container_entry.cxx:59-64`) before the caller creates data; the later saves at lines 189/202 are unchecked too. Merely moving the map inserts after `create_empty_file_if_not_exist()` cannot fix this because that function returns no status. ADD-UTIL-006 identifies a deterministic, valid-name cause of metadata failure; it is separate from the already counted failure-publication policy.
- **BASE-UTIL-011 — retained, Medium / High confidence / Correctness.** `..` aliases the parent root and `.` the named-container root because dots are unescaped, but encoded slashes prevent using this example as arbitrary multi-level traversal. The SDK cloud container parameter is a name (`1.152.11/galaxy/ICloudStorage.h:215-223`); the IStorage portable-relative-file precondition does not establish that dot cloud-container names are forbidden. Keep the bounded namespace-confusion claim.
- **BASE-UTIL-012 — retained, Medium / High confidence / Correctness.** Startup ignores the result of both map emplacements while always pushing the vector. The ordinary swap/pop fast path checks the cached index against pointer identity and has a slow-path fallback; it is not intrinsically out-of-bounds. Duplicate startup objects and stale-object removal violate the identity invariant before that algorithm runs. The original link example remains conditional on a locally present in-root Windows link; ADD-UTIL-001 supplies a different, link-free concurrent trigger.
- **BASE-UTIL-016 — retained, Low / High confidence / Correctness.** Unchecked `space` sentinels remain reporting defects. `capacity - available` also includes space unavailable to the caller and other files on the volume; deciding whether an API wants volume use or container quota is a caller-contract question, not another failure-sentinel finding. Proposed check: compare checked values on a normal volume and after root removal.

### ADD-UTIL-001 — Stale lookups and retired entries can delete newly created files and detach the wrong index object

- **Severity:** High
- **Confidence:** High
- **Category:** Concurrency
- **Location:** `Source/Shared_NoVer/filesystem_container/filesystem_container.cxx:78-104` (`get(path)`), `113-136` (`get_or_create`), `287-351` (`remove(entry,...)`); `filesystem_container_entry.cxx:91-112` (`unlink`); associated state `filesystem_container_entry.hxx:21-29` and `filesystem_container_metadata.hxx:65-72`.
- **Affected scope:** Concurrent Windows Storage/cloud existence, deletion, recreation and shared-file close/download operations. SDK thread-safety context: `Source/DLLs/1.139.2/galaxy/GalaxyApi.h:279-283`; production adapters: `Shared/SharedFileUtils.cxx:102-169`, `Client/Impl/Storage.cxx:76-101,257-260,275-295`.

**Evidence:** `get(path)` samples filesystem existence before taking the filename mutex and later acts on that old result by calling `unlink()` on whatever object the map now contains. Unlink removes by cached pathname before asking the parent to unregister. Parent removal erases name/ID keys without checking which object they now identify, whereas vector removal requires the original pointer. Shared pointers preserve object lifetime, not membership generation or file identity.

**Failure mechanism / exact interleavings:**

1. Initially `p` is absent. T1 (`FileExists`/`get`) samples `exists=false` at line 84 and pauses. T2 completes `get_or_create(p)` and writes valid new data. T1 resumes, finds T2's new entry under the mutex, then uses its stale `false` to call that entry's `unlink`. An existence query deletes the new data and metadata. All filesystem operations can succeed; there is no external filesystem editor or I/O failure.
2. Initially entry E owns `p`. Two concurrent removals have already obtained E. T2 completes E's unlink, clearing its cache index and removing its membership. T3 creates replacement F at `p` and writes new data. T1 resumes E's unlink: E's cached path deletes F's file; `filename_to_entry.erase(p)` erases F's registration. Neither E's cleared index nor a scan of the vector can find E, because the vector contains F. Debug asserts at line 351; Release retains F in the vector after erasing the name. If F is shared, E's reset share ID can additionally leave F's ID map entry behind.
3. The same missing operation boundary affects sharing: removal snapshots `share_id` at line 293 before acquiring membership locks, while promotion sets it at line 188 and unlink resets it after parent removal has released its locks (`entry:110`). Promotion between the snapshot and erasure can leave an ID registration orphaned. A getter that has released its lookup lock can also read this plain `uint64_t` concurrently with reset; the metadata-map mutexes do not protect that field.

**Impact:** Supported concurrent calls can lose a newly saved file, crash a Debug process, and leave name/share-ID/count/index views inconsistent. This is stronger than BASE-UTIL-006's failed-delete case: success-only schedules suffice, and a nominally read-only query can be destructive.

**Possible solutions:** Serialize the full lookup/create/delete/promote transaction per logical key; or use generation-checked entries plus handle/file identity and a coordinated membership commit. Conditional map erasure by pointer is necessary defensive work but insufficient if the old entry already deleted the replacement's pathname.

**Recommended resolution:** Define a consistent operation-lock/entry-state protocol spanning existence validation, file mutation, `share_id` changes and all three membership structures. Revalidate the same entry generation before deleting bytes, make retired entry operations fail without touching replacements, and erase maps only when they still point to that entry. Establish lock order before adding entry locks to methods that call back into the container. Keep ordinary vector/index operations under `mtx_fs_entry_index`; do not misdiagnose their guarded cache access as a separate race.

**Verification:** Use barriers at line 84 and between the public remove lookup and E's unlink to force schedules 1 and 2. Assert the new payload survives, no assertion fires, and filename count, vector size, each cached index and ID-to-entry roundtrip agree. Force promotion between line 293 and membership locking and require no orphan ID. Run both Debug and Release, with valid portable names and successful OS calls. Static trace only in this pass.

### ADD-UTIL-002 — Filename uniqueness rejects distinct legitimate shared-file IDs

- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Shared_NoVer/filesystem_container/filesystem_container.cxx:144-204`, especially `174-182`; `filesystem_container.hxx:33-34`; `filesystem_container_entry.cxx:22-26` (physical path derived only from name).
- **Affected scope:** Repeated FileShare uploads and shared-file downloads with distinct IDs but the same portable filename; Windows client/server configurations enabling file sharing.

**Evidence:** `create_shared` accepts an existing identical `(name, ID)` and can promote an unshared name, but rejects an already shared name for every different ID. `Server/ServerHandlers.cxx:464-476` allocates a new ID for every upload, including a repeat upload of the same filename. `Client/Impl/Storage.cxx:287-304` registers downloads with the received name and ID. The SDK exposes downloads/read/close by SharedFileID, not a global filename uniqueness precondition (`1.139.2/galaxy/IStorage.h:193-291`).

**Failure mechanism:** Successfully share `save.dat` as ID S1. Share updated `save.dat` again: the server issues S2, but the name already maps to an entry with S1. The second creation hits the false assertion `entry->get_share_id() == 0` in Debug and returns null in Release, despite no disk error. The analogous client cache rejects receiving two different shared objects both named `save.dat`. Distinct users using the same common save filename have the same collision. The server's current unconditional success response amplifies this condition; that response handling is a separate SERVER-owner responsibility.

**Impact:** Ordinary repeat sharing cannot store the new snapshot; subsequent retrieval by the advertised new ID fails. Debug can terminate on a normal collision. Distinct share objects cannot coexist in the cache. This is not the case-only alias in BASE-UTIL-004 and not unchecked persistence from BASE-UTIL-005.

**Possible solutions:** Give shared objects opaque ID-based physical keys and a secondary, potentially non-unique logical-name index; or deliberately replace/reuse shares under an explicit API policy coordinated with the ID producer. Simply changing an entry's ID discards the old ID's meaning and does not support independent snapshots.

**Recommended resolution:** Separate ordinary filename-keyed local storage from ID-keyed shared-object storage. Preserve original filename as metadata, allow independent IDs for equal names, and define any name-only convenience lookup's ambiguity behavior. Coordinate publication/failure callbacks with SERVER/STORAGE and migrate the existing on-disk layout.

**Verification:** Create S1/S2 for the same name with different bytes, require each ID to retrieve its own bytes, close one and retain the other, then restart and repeat lookups. Exercise repeat FileShare and two authenticated uploaders with the same filename. Check that failure is never announced as success by the caller. None executed.

### ADD-UTIL-006 — Appending `.metadata` creates file/directory collisions for otherwise valid data paths

- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Shared_NoVer/filesystem_container/filesystem_container.cxx:247-255` (`get_path_metadata` overloads); `filesystem_container_entry.cxx:25-26,351-359` (metadata path/open).
- **Affected scope:** Metadata and share-ID persistence for nested Storage/shared/cloud names on Windows; no special platform name, case alias, symlink, malformed archive or concurrent call is required.

**Evidence:** Data paths preserve the encoded directory tree, while metadata adds `.metadata` to the last component in another tree. Both `save` and `save.metadata/part` are ordinary portable logical filenames and can coexist as `files/save` and `files/save.metadata/part`.

**Failure mechanism:** Persist metadata for `save`: it creates the regular file `metadata/save.metadata`. Persist metadata for `save.metadata/part`: it needs that same path to be a directory containing `part.metadata`. The second archive cannot be created: path validation may reject the non-directory ancestor earlier, or directory creation/open fails when reached. Reversing the creation order makes the directory first and prevents the first entry's archive from being opened as a file. Encoding the original names does not help because `.` is deliberately retained. If execution reaches the unchecked save, `create_shared` can publish the second ID anyway (BASE-UTIL-005), but checking its errors alone still cannot make both legitimate entries persist in this layout.

**Impact:** Two valid data names cannot both retain metadata/share IDs: an operation is rejected/throws during path setup or retains bytes without durable attributes when the later save fails. This is an incompatible namespace mapping, a new cause rather than another generic report about ignoring an I/O error.

**Possible solutions:** Store per-entry records under an opaque full-key encoding/hash with collision verification; use a tree where each logical component is always a directory and data/metadata occupy reserved encoded child slots; or combine metadata into a transactional catalog. Reserving every `.metadata` directory in the public API changes accepted-name behavior and requires an explicit compatibility decision.

**Recommended resolution:** Adopt a prefix-conflict-free metadata key mapping and a migration strategy, then apply BASE-UTIL-005/008's checked publication. Maintain consistent case, share-ID and logical-path identity rules across the new mapping.

**Verification:** Persist different metadata and IDs for `save` and `save.metadata/part` in both orders on a normal writable Windows directory. Reload and require both complete records, independent contents, IDs and counts. Include multiple nested `.metadata` components. This is a proposed deterministic check; no filesystem probe was executed.
