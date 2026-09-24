# UTIL — thorough Shared_NoVer re-review addendum

## Executive summary

**Production baseline:** `b30e83872c0006e8240c8b4f565da5351bf10080` (`b30e8387`), repository `C:\Development\AI\UL`. **40/40 assigned inputs reread completely; no unfinished production reads.** All 40 were read before opening the existing UTIL findings. The scoped source diff against the baseline is empty. Instructions consulted: `.ai/SKILLS/CppReviewer.md`, this directory's `PLAN.MD`, and scope context in `.ai/ai-instructions-review.txt`, with the current request's exclusions taking precedence.

**Six new confirmed utility findings:** **1 High, 4 Medium, 1 Low**, all High confidence; categories **2 Concurrency, 4 Correctness**. Full evidence, exact locations, mechanisms/interleavings, impact, options, recommendation and proposed verification were appended to the responsible existing sidecars. New IDs are ADD-UTIL-001 through ADD-UTIL-006. The Low item has an explicitly limited current call path.

**All 16 old IDs have dispositions below:** 15 confirmed defects retained and BASE-UTIL-015 retained as **Informational**, as already reconciled. No old finding was silently removed, renumbered, rewritten or counted again. Combined UTIL accounting is **21 confirmed defects: 2 High, 16 Medium, 3 Low**, plus **1 informational observation**. Confirmed categories: **17 Correctness, 3 Concurrency, 1 Memory Safety**. These are owner-local counts; cross-component caller consequences are handoffs, not extra UTIL IDs.

The most consequential new result is that ordinary successful concurrent calls can destroy a newly saved file: a stale existence query invokes unlink on a newly published entry, and a delayed removal can erase a replacement's map registration while leaving its vector entry. There are also deterministic namespace failures that cannot be repaired merely by checking generic I/O errors. Existing per-map locking and atomic ID counters are useful, but neither provides a whole entry/snapshot/persistence transaction.

Important corrections/refinements include **existing nonzero play-time serialization assertions**, the exact modular-clock symptom, cloud physical-versus-metadata time feature gates, and copy failure after the final destination-metadata rewrite. The re-review does not establish release readiness; its recommended first step is coordinated operation-level synchronization and identity/persistence design, followed by the focused Windows validation specified in the sidecars.

## Scope, method and limitations

- Assignment is exactly **16 `.cxx`, 23 `.hxx`, 1 `.txt`, 0 `.cmake`** inputs below `Source/Shared_NoVer`. The `.txt` is `CMakeLists.txt`. Inactive conditional branches were read to understand source structure; this is a Windows-focused static review, not a Linux-runtime review.
- Source-first sequence: read the skill/plan, enumerate the assignment, read all 40 files end to end, then read `.ai/review-baseline/UTIL.MD` and the relevant existing sidecars. Fresh caller, dependency-contract and test-context tracing followed. No old review was used as a substitute for reading an assigned implementation.
- Test trees remain excluded as implementation-review targets. **All 21 Shared_NoVer unit-test sources listed by their manifest were read as context**, along with relevant message/helper/SharedFileUtils tests and the SystemTests cloud roundtrip. Their assertions inform coverage and counterevidence; they do not increase the 40-file implementation count and no defects are filed against excluded test code.
- SDK/vendor reads were limited to contracts and Cereal semantics. Other production files were traced selectively as caller/ownership/build context, not claimed fully reviewed under UTIL. Other owners' reports were not edited.
- **No build, configure, test, sanitizer, analyzer, live identity/registry/environment lookup, DLL load or filesystem reproduction was executed.** All new verification procedures are proposals. The earlier coordinator reproductions recorded in the preserved baseline for 001/006/007 are prior evidence, not work performed in this pass.
- All report edits used `apply_patch`. Production inputs and the baseline notebook were not edited; no Git mutation or credential-file access occurred. Public source templates were inspected as required source, not live configuration/credential material.

## Exact per-file coverage and fresh notes

Every row represents an entire file read, including its final line. `BASE`/`ADD` numbers refer to UTIL IDs. No row means proof of defect-freedom. Findings and follow-up notes are also organized by flow below.

| # | Exact repository-relative input | Lines read | Fresh inspection notes / disposition |
|---:|---|---:|---|
| 1 | `Source/Shared_NoVer/AchievementData.cxx` | 1–100 | All defaults/setters/getters and dirty changes checked. `SetUnlockTimeNow` uses system-clock seconds narrowed to the SDK's uint32 field; no present-date overflow claim. Concurrent access belongs to enclosing-container BASE-002. |
| 2 | `Source/Shared_NoVer/AchievementData.hxx` | 1–43 | Archive contains six persistent fields, deliberately not local Dirty state. Borrowed name/description references require outer ownership/locking; no separate retained-pointer allegation. |
| 3 | `Source/Shared_NoVer/AchievementsAndStatsContainer.cxx` | 1–172 | Unlocked copy versus eight-lock assignment; escaped-reference reads, achievement writes, BootTime access and modular elapsed arithmetic traced. BASE-002/003 retained with explicit schedules/counterevidence. |
| 4 | `Source/Shared_NoVer/AchievementsAndStatsContainer.hxx` | 1–105 | Atomic input temporary loss mechanically retraced through Cereal; four callback mutexes do not lock serialization. BASE-001 retained; actual Binary roundtrip assertions documented. Union bit representation is MSVC-oriented, not a new Linux finding. |
| 5 | `Source/Shared_NoVer/CMakeLists.txt` | 1–30 | Common static target, PUBLIC dependencies/includes, PRIVATE Win7 definitions, root C++20/x86 context and transitive imagehlp checked. BASE-015 remains informational; Markdown glob inclusion alone is not a compiler failure. |
| 6 | `Source/Shared_NoVer/ConcurrentQueue.hxx` | 1–14 | `_WIN32 && _MSC_VER` selects PPL; unsupported fallback is not the normal Windows/MSVC implementation. TBB guard read without runtime assessment. |
| 7 | `Source/Shared_NoVer/ConcurrentQueueUnsupported.hxx` | 1–80 | Both pushes/pops and empty are mutex-protected; copies/moves deleted. Emplace's returned reference outlives its lock and needs caller lifetime discipline. No observed production MSVC path or unsupported-caller defect manufactured. |
| 8 | `Source/Shared_NoVer/ConsoleCoutRedirector.cxx` | 1–57 | Capture/release changes process-global cout buffer; heap singleton retains buffer lifetime. Tee release replays accumulated output; startup caller uses capture, not tee. Error-exit cleanup remains a caller/lifecycle concern. |
| 9 | `Source/Shared_NoVer/ConsoleCoutRedirector.hxx` | 1–55 | EOF conversion and both sink calls inspected; first-sink failure short-circuits second sink/flush. No current production tee call established; successful two-sink test exists. |
| 10 | `Source/Shared_NoVer/ConstHash.hxx` | 1–43 | FNV byte unsignedness, constants, seeds, recursion and loop checked. Cloud data uses iterative hashing; traced recursive challenge input is eight bytes. No cryptographic-identity or measured-performance promise inferred. |
| 11 | `Source/Shared_NoVer/ContainerGetByIndex.hxx` | 1–65 | Bounds precede iterator advance; value results copy; iterator result follows caller lifetime. Forced-zero key requires the intended present-key invariant; absent-zero lookup explicitly returns end in current tests. |
| 12 | `Source/Shared_NoVer/CustomConsole.cxx` | 1–73 | Allocation, std-handle rebinding, static enabled flag and saved window procedure checked. Startup policy lacks general retry/concurrent-call guarantees; no SetWindowLong subclass or leaked acquired window handle is claimed. |
| 13 | `Source/Shared_NoVer/CustomConsole.hxx` | 1–5 | One console-enable declaration; implementation/caller policy supplies behavior. No independent ABI finding. |
| 14 | `Source/Shared_NoVer/DefaultConfigFiles.cxx` | 1–259 | All three embedded templates and mkdir/truncating write paths read. Void writer/error reporting is a known reliability limit; no duplicate general I/O ID. Published defaults are not treated as accessed live credentials. |
| 15 | `Source/Shared_NoVer/DefaultConfigFiles.hxx` | 1–10 | Three path-based creation declarations; no ownership escape. Existing template generation test supplies basic success context. |
| 16 | `Source/Shared_NoVer/EnvUtils.cxx` | 1–66 | Narrow/wide two-pass getenv_s buffer sizing, second-call status and NUL exclusion checked. Changed/missing value returns empty on failure rather than consuming the resized required length unchecked. |
| 17 | `Source/Shared_NoVer/EnvUtils.hxx` | 1–13 | Windows-only wide overload, owning string results and game-data-prefix declaration checked. No live environment values read. |
| 18 | `Source/Shared_NoVer/GlobalUniqueID.cxx` | 1–14 | Atomic fetch_add gives runtime uniqueness within this linked counter instance; no restart-stable/cross-process or cryptographic promise. No realistic exhaustion claim. |
| 19 | `Source/Shared_NoVer/GlobalUniqueID.hxx` | 1–16 | Construction/destruction disabled and static generator exposed. Thread-safety declaration agrees with atomic implementation. |
| 20 | `Source/Shared_NoVer/MachineInfo.cxx` | 1–691 | Windows adapter allocations, module/registry/known-folder/debug handles, JSON/path fallbacks and name counts traced. BASE-013/014 retained; bounded process-lease handle is not a per-call leak. |
| 21 | `Source/Shared_NoVer/MachineInfo.hxx` | 1–56 | KnownPath initialized states, owning returned values and per-instance path/identity members checked. External resource ownership resides in implementation. |
| 22 | `Source/Shared_NoVer/MemoryInputBuffer.cxx` | 1–22 | Empty/null avoids pointer arithmetic; nonempty borrowed span configures get area. Input-only const_cast is required by streambuf interface; no write-through demonstrated. |
| 23 | `Source/Shared_NoVer/MemoryInputBuffer.hxx` | 1–14 | Final streambuf wrapper owns no payload. Borrowed lifetime traced to synchronous Cereal consumption before packet destruction. |
| 24 | `Source/Shared_NoVer/MemoryInputStream.cxx` | 1–31 | Null void pointer normalized to empty span; stream bound to member buffer; no invalid nonnull range assumed valid. |
| 25 | `Source/Shared_NoVer/MemoryInputStream.hxx` | 1–28 | Declaration order makes stream destruction precede buffer destruction. Returned stream reference must not escape owner; current packet decode finishes within scope. |
| 26 | `Source/Shared_NoVer/Networking/MessageUniqueID.cxx` | 1–23 | Generated constructors/get share one atomic counter; explicit-ID constructor intentionally preserves a supplied correlation ID. Independent GlobalUniqueID namespace is not an accidental alias finding. |
| 27 | `Source/Shared_NoVer/Networking/MessageUniqueID.hxx` | 1–28 | Explicit ID serialization/load and runtime-generation API checked; response IDs are not required to consume new counter values. |
| 28 | `Source/Shared_NoVer/Networking/SendableEventMessage.hxx` | 1–32 | Archive adapters and macro hashing checked: `sizeof(className string)` is a seed to 32-bit const_hash, widened to uint64. Existing test encodes this convention; changing it silently would change the wire ID. |
| 29 | `Source/Shared_NoVer/PreprocessorControlIf.hxx` | 1–10 | Two-step concatenation expands 0/1 condition before selecting branch; no claim of arbitrary expression support. Compile-time assertions exist in context test. |
| 30 | `Source/Shared_NoVer/SafeStringCopy.hxx` | 1–131 | Null/zero guards, terminator capacity, binary lengths, bounded memchr and hex sizing checked. min occurs before uint32 copy-size narrowing. Overlap/NUL/range preconditions remain caller responsibilities. |
| 31 | `Source/Shared_NoVer/SharedLibUtils.cxx` | 1–186 | Export mapping cleanup, singleton initialization, real-module ownership, exact/substring lookup and basename gates traced. BASE-015 informational; trusted-PE/relative-load assumptions recorded without an unproven exploit. |
| 32 | `Source/Shared_NoVer/SharedLibUtils.hxx` | 1–29 | Function-pointer template constraint and lookup API checked. Calling convention remains explicit in the caller type; no concrete mismatched target type established. |
| 33 | `Source/Shared_NoVer/filesystem_container/filesystem_container.cxx` | 1–463 | All scan/lookup/create/share/copy/remove/index/subcontainer/quota paths traced. BASE-004/005/011/012/016 retained; ADD-001/002/006 fully recorded here. |
| 34 | `Source/Shared_NoVer/filesystem_container/filesystem_container.hxx` | 1–90 | Filename/ID/vector/subcontainer mutex ownership and private callback paths mapped. Shared_ptr snapshots own entries, not fixed disk state. One-key-one-ID design and missing whole-operation lock verified. |
| 35 | `Source/Shared_NoVer/filesystem_container/filesystem_container_entry.cxx` | 1–397 | Both archives, all copy phases, buffered completion, unlink, clocks, size/offset conversions, metadata and cache access read. BASE-006–010 retained/refined; ADD-003/004/005 fully recorded here. |
| 36 | `Source/Shared_NoVer/filesystem_container/filesystem_container_entry.hxx` | 1–89 | Raw reverse parent/cached path/optional index, public mutators and size_t API checked. Actual parent retention traced; no unsupported UAF claim. Ordinary cache mutations come from locked container paths. |
| 37 | `Source/Shared_NoVer/filesystem_container/filesystem_container_metadata.cxx` | 1–162 | Owning snapshots and two-map-object assignment locking are sound within scope. Share ID reset/empty and two independent maps are not atomic entry state; support ADD-001/003/004 without duplicate IDs. |
| 38 | `Source/Shared_NoVer/filesystem_container/filesystem_container_metadata.hxx` | 1–86 | Map archive locks versus unlocked outer ID/user/system sequence checked. Supports complete-record/persistence ADD-003; callbacks returning references are not shown misused by current metadata callers. |
| 39 | `Source/Shared_NoVer/filesystem_container/filesystem_container_utils.cxx` | 1–216 | Encoder/decoder, lexical versus canonical paths, component-prefix check, relative enumeration and system-clock helper checked. BASE-012 retained; reparse TOCTOU/local trust boundary qualified. |
| 40 | `Source/Shared_NoVer/filesystem_container/filesystem_container_utils.hxx` | 1–30 | All overloads matched with implementation. Header overstates weak canonicalization in sanitize_path; entry callers separately check containment. No standalone style-only finding. |

**Incomplete assigned files: none (0/40).** There were no equivalent-file shortcuts in this pass.

## New findings index and exact sidecar ownership

Full sections are adjacent to production implementations; those sections are authoritative for complete finding fields.

| ID | Severity / confidence / category | Concrete trigger and effect | Full finding sidecar |
|---|---|---|---|
| ADD-UTIL-001 | High / High / Concurrency | Existence sampled before concurrent creation; or two removals retain E while another call creates F. Query deletes F; stale removal erases F's map but cannot remove E from the vector. Promotion/reset adds share-ID mismatch/race. | `Source/Shared_NoVer/filesystem_container/filesystem_container.cxx.review.MD` |
| ADD-UTIL-002 | Medium / High / Correctness | Repeat sharing or receiving distinct IDs for `save.dat` hits the existing nonzero-ID name assertion/rejection. Shared storage is keyed by filename as well as ID and cannot retain independent same-name objects. | `Source/Shared_NoVer/filesystem_container/filesystem_container.cxx.review.MD` |
| ADD-UTIL-003 | Medium / High / Concurrency | Two successful same-entry saves open/truncate one final archive and write different-length records at independent offsets. Per-map serialization locks cannot prevent mixed archives or whole-record skew. | `Source/Shared_NoVer/filesystem_container/filesystem_container_entry.cxx.review.MD` |
| ADD-UTIL-004 | Low / High / Correctness | Copy to a final empty-metadata/unshared destination skips persistence. Old attributes or a copied source share ID remain on disk despite success. Current active local-to-shared path avoids this condition; no production call to reverse helper found. | `Source/Shared_NoVer/filesystem_container/filesystem_container_entry.cxx.review.MD` |
| ADD-UTIL-005 | Medium / High / Correctness | On Windows x86, 4 GiB + 8 narrows to size_t 8 before stat/whole-file read checks, producing a successful eight-byte prefix. Can originate from streamed/cloud or pre-existing 64-bit data. | `Source/Shared_NoVer/filesystem_container/filesystem_container_entry.cxx.review.MD` |
| ADD-UTIL-006 | Medium / High / Correctness | `save` and `save.metadata/part` can coexist as data but require `metadata/save.metadata` to be both a file and directory. Path setup or metadata persistence necessarily fails for one. | `Source/Shared_NoVer/filesystem_container/filesystem_container.cxx.review.MD` |

### Why these are not duplicate generic I/O findings

- ADD-001 has successful OS calls and a destructive existence query; BASE-006 starts with failed deletion. Fixing error handling alone cannot fix entry generation identity.
- ADD-002 fails before any new I/O because of an incompatible key invariant; BASE-004 concerns different case spellings aliasing one Windows file, and BASE-005 concerns publishing after failed persistence.
- ADD-003 permits both serializers and closes to succeed; BASE-008 concerns errors detected only at completion. Both may benefit from temporary files, but same-entry snapshot and commit ordering are additionally required.
- ADD-004 returns success in sequential utility copying; BASE-009 is failure rollback. The low rating explicitly accounts for the presently uncalled shared-to-local helper.
- ADD-005 is width loss before the I/O request; BASE-010 is accepting an incomplete request after a file shrinks. The buffer read overload's actual gcount is counterevidence to generalized padding claims.
- ADD-006 is a deterministic prefix conflict between valid logical names. Checked error propagation (BASE-005/008) exposes the conflict but cannot make both metadata records representable in the current layout.

## Every baseline ID: disposition, corrections and counterevidence

Severity and confidence here refer to the retained conclusion, not a newly counted finding. All confidence values remain High. Full original fields remain in the baseline sidecars; appended sections explicitly label refinements.

| Old ID | Disposition / severity | Fresh evidence, correction or counterevidence | Responsible implementation/header |
|---|---|---|---|
| BASE-UTIL-001 | Retain / Medium | Cereal really writes the `PlayTime.load()` temporary. **Nonzero serialization assertions already exist in both populated message tests**, using Binary archives; PortableBinary is the production network path. This is not a compile failure or an absent-test finding. | `AchievementsAndStatsContainer.hxx:51-55` |
| BASE-UTIL-002 | Retain / High | Supported scalar/Copy callers read after helper locks release; snapshot copy is unlocked. Eight-lock assignment is itself guarded, recursive self-acquisition is not proven deadlock, and unordered_map rehash does not itself invalidate element references. BootTime's unlocked getter also matters. | `AchievementsAndStatsContainer.cxx:14-19,25-30,33-54,57-83,109-117,138-146` |
| BASE-UTIL-003 | Retain / Medium | Adjustable/foreign BootTime remains wrong for duration. **Negative deltas may decrease a nonzero base or wrap huge, depending on final modular addition**; not every negative delta necessarily produces a huge final number. Steady local duration plus duration snapshots remains recommended. | `AchievementsAndStatsContainer.cxx:10,21-30,50-51` |
| BASE-UTIL-004 | Retain / Medium | Ordinary Windows case aliases remain; same issue affects named subcontainer objects/locks. Case-sensitive directory mode is an explicit exception. Restricted device/trailing-dot names are not needed as evidence. | `filesystem_container/filesystem_container.cxx:78-135,144-200,434-459` |
| BASE-UTIL-005 | Retain / Medium | Void creation and unchecked constructor/caller metadata saves still publish ghosts/non-durable IDs. Check the constructor's early save as well as lines 189/202. ADD-006 is a new deterministic failure cause, not a re-count of publication errors. | `filesystem_container/filesystem_container.cxx:123-135,174-204`; entry `59-64,374-384` |
| BASE-UTIL-006 | Retain / Medium | Failed data deletion still unregisters and clears metadata; metadata-only removal failure can leave an orphan archive. Successful stale-object schedules now belong to ADD-001. Historical reproduction preserved; none rerun. | `filesystem_container/filesystem_container_entry.cxx:91-112` |
| BASE-UTIL-007 | Retain / Medium | MSVC file time is not Unix time. **Cloud physical-time exposure precedes timestamp feature 1.148.7**; later cloud uses metadata time, while Storage still uses physical time. Ordinary metadata timestamps have the correct epoch, not a universal signed/range guarantee. | `filesystem_container/filesystem_container_entry.cxx:188-205`; cloud `92-105` |
| BASE-UTIL-008 | Retain / Medium | good() before close still misses completion failures; truncating live metadata can destroy its old version. Same-file concurrent successful writers are ADD-003. Do not count another general disk-full instance. | `filesystem_container/filesystem_container_entry.cxx:291-308,351-371` |
| BASE-UTIL-009 | Retain / Medium | Original pre-existing-destination rollback is sound. **Final notify_copy_done/save failure also has no rollback** after both copies succeed, and source-ID bytes may already be installed. Stage the destination's final representation and verify all three phases. | `filesystem_container/filesystem_container_entry.cxx:135-176` |
| BASE-UTIL-010 | Retain / Medium | Whole-file shrink produces accepted EOF and zero tail. Buffer overload returns gcount and is not the same padding bug. ADD-005 covers separate x86 pre-read narrowing. | `filesystem_container/filesystem_container_entry.cxx:238-289` |
| BASE-UTIL-011 | Retain / Medium | Dot subcontainer names alias parent/named root; encoded slash limits the demonstrated escape. Cloud name contract is different from the IStorage relative-file portability precondition. | `filesystem_container/filesystem_container.cxx:434-459` |
| BASE-UTIL-012 | Retain / Medium | Canonical relative listing loses link identity and ignored emplace failure duplicates the vector. Cache swap/pop validates pointer/index; do not blame guarded fast-path access itself. Local link capability required. Count shared utility/container sections once. | `filesystem_container/filesystem_container.cxx:29-42`; utils `56-64` |
| BASE-UTIL-013 | Retain / Medium | GetComputerName successful count excludes NUL; subtracting one truncates before configured name hashing. GetUserName convention differs; MAC-default IDs are counterevidence to universal impact. | `MachineInfo.cxx:511-523` |
| BASE-UTIL-014 | Retain / Low | Only output HeapAlloc is unchecked before copy. Earlier buffer checks/free paths exist. Allocation-failure trigger remains low-likelihood with a mechanically definite null write. | `MachineInfo.cxx:97-105` |
| BASE-UTIL-015 | Retain / **Informational** | No current DLL directory enables 1.149.12–1.149.16 RED interval. Common-object feature mismatch remains latent integration debt. Singleton initialization and transitive imagehlp undermine unrelated loader-race/linker guesses. Count outside confirmed defects. | `SharedLibUtils.cxx:99-118`; `CMakeLists.txt:3-13` |
| BASE-UTIL-016 | Retain / Low | Error-code sentinel is still returned as enormous capacity/zero subtraction result. Separate quota-versus-volume semantics need caller policy, not another sentinel ID. | `filesystem_container/filesystem_container.cxx:365-381` |

Paths in the last column are relative to `Source/Shared_NoVer` except the explicitly identified cloud caller. **Old IDs withdrawn: 0; old severity changes: 0; old IDs duplicated into new IDs: 0.** The four bold corrections/clarifications above (001, 003, 007, 009) are highlighted substantive report refinements; other rows supply retained evidence and scope qualifications.

## Fresh flow notes and architecture assessment

### Filesystem keys, share IDs, membership and cache indices

Containers maintain a filename map, a share-ID map, and a vector with per-entry cached indices. SharedFileUtils owns the root containers; parents own cloud subcontainers; entries own cached paths but keep a raw reverse parent. A useful invariant is that each live entry has one intended physical identity, one successful filename registration, at most its intended share registration(s), and exactly one matching vector/index slot. The fresh trace checks that invariant across every operation:

| Operation | What is protected | Where the invariant can fail |
|---|---|---|
| Startup scan | Construction is not concurrently published in the traced owner | Canonical listing duplicates logical targets and inserts unconditionally into vector; loaded duplicate IDs are also not validated. BASE-012 is the demonstrated local-link case. |
| get(name) | Only map lookup under filename mutex | Disk existence predates the lock; destructive cleanup can target a newer object. ADD-001. |
| get(ID) | Map lookup under share-ID mutex, then entry existence check | Returned shared_ptr can be retired before subsequent I/O/cleanup; object lifetime does not preserve membership. ADD-001 operation boundary applies. |
| get_or_create | Filename and vector multi-lock | Creation status ignored (BASE-005); existing stale entry can be reused while external-to-these-lock entry operations run. An orphan archive can also restore an ID without this path publishing an ID map entry. This latter partial-failure consequence is not a new ID. |
| create_shared | Filename, vector and share-ID multi-lock | Current strict one-filename/one-ID policy rejects normal independent shared IDs (ADD-002); failed saves still publish (BASE-005); promotion's ID field needs the same entry lifecycle protocol as unlink (ADD-001). |
| notify_file_copied | Membership multi-lock, selected by an entry ID read | Existing-name fast return cannot reconcile an arbitrary retired/copied object. Save and file copy happened outside membership locking. Treat current-entry identity and ID snapshot as part of ADD-001 remediation. |
| unlink / parent remove | File removals precede membership lock; parent locks vector/name and conditionally ID | Failed I/O already covered by BASE-006; stale generation/key erasure and reset after unlock covered by ADD-001. |
| Index lookup / snapshot | Vector mutex, bounds checks; snapshot owns shared_ptrs | Snapshot freezes membership only, not bytes, metadata, timestamps or parent lifetime. Guarded ordinary cache updates are not standalone data races. |

Actual parent retention was checked through `Client/UniverseLAN.hxx:50-96` and `UniverseLAN.cxx:18-25,83-133`: sfu is retained across reset and declared before users, and storage workers are joined by their owner. Deferred cloud reads capture a subcontainer shared_ptr (`CloudStorage.cxx:140-162`). No reachable parent UAF is asserted from the raw pointer alone. External stale entry **membership**, in contrast, is demonstrated using valid overlapping operations while all parent/entry objects stay alive.

### Copy rollback and metadata atomicity

The copy procedure has at least three persistence stages: overwrite data, copy the source's serialized metadata if source metadata is nonempty, then assign the two destination maps and persist the destination's intended ID. The first two failure branches can delete old destination artifacts (BASE-009); failure in the third never executes those branches. A transaction must preserve the pre-copy destination or publish an intentional complete new version, not merely remove the latest successfully copied artifact.

Emptiness is not absence on disk: source metadata can be absent while destination's obsolete archive remains, and source-share-ID-only metadata can be copied into an unshared destination. ADD-004 supplies two sequential success counterexamples. Its current exposure is limited: only the generic reverse helper exposes that direction, and no production invocation was found; active local-to-shared copying keeps destination metadata nonempty via its assigned ID.

Each metadata map's get/serialize/assignment lock is useful. None serializes the truncating file streams or captures ID/user/system as one record. ADD-003 gives a two-writer schedule that remains broken after implementing explicit close checks for BASE-008. Separate temp files plus replace avoid byte interleaving but need snapshot version/commit ordering as well; otherwise an older snapshot can replace a newer one. File content, metadata hash/timestamp, membership and callback publication need a common caller/utility policy. `file_entry_metadata_container::get_vector` is the correct paired owning snapshot used by cloud; separate key/value getter ordering was not claimed broken in a current caller.

The variable, large user-metadata schedule has an active version gate: `HAS_ICLOUDSTORAGE_METADATAIDX_FUNCS` spans 1.148.6–1.148.12, and 1.148.11's SDK accepts optional NULL-terminated key/value arrays (`ICloudStorage.h:362-430`) without an aggregate byte cap in that contract. Newer small records do not necessarily tear on every overlap; no universal corrupt-on-any-save claim is made.

### Windows paths, canonicalization and encoding

- `sanitize_relative_path` is lexical normalization plus preferred separators; it does not force a path to be relative. `sanitize_path` makes it absolute but does not weakly canonicalize, despite the header comment.
- Actual sandbox checking separately weakly canonicalizes base and candidate, then compares path components with both ends. This handles sibling-prefix and ordinary traversal cases correctly. It does not make case-sensitive `std::filesystem::path` map keys equivalent to ordinary Windows physical identity (BASE-004).
- The function returns a lexical/cached pathname rather than a pinned validated handle. Existing outward links are ordinarily rejected; local replacement of an ancestor reparse point after validation remains a TOCTOU limit. Remote uploads were not shown capable of creating a junction/symlink. Do not promote that deployment assumption into a reproduced remote exploit.
- Startup `relative(entry, root)` resolves links, which supplies BASE-012's index duplication. A reparse policy must decide whether to skip links, preserve their names, or deduplicate targets and must align creation, scan and removal.
- Escaping percent/reserved bytes does not encode all possible Windows identities. IStorage requires portable UTF-8 relative names without backslashes (`1.139.2/galaxy/IStorage.h:116-120`), so invalid caller/device-name examples are not new defects. By contrast, case-varied portable names (BASE-004), cloud dot container names (BASE-011), and `save` plus `save.metadata/part` (ADD-006) have specific supported/bounded mechanisms.

### Read/write narrowing, time, stats snapshots and atomics

- `read(char*, length, offset)` checks null/zero, seeks then returns actual gcount. Normal uint32 SDK lengths/offsets fit MSVC's wide stream counts/offsets; no unsupported 2-GiB signed-int claim is made. Whole-file read is different: it narrows a wide stream position to size_t before reading (ADD-005), and accepts EOF without resizing after a shrink (BASE-010).
- Writing through the raw pointer overload checks stream open and current status but not close; vector empty-data behavior is not confused with arbitrary nonempty buffer safety. Cloud callback writing uses bounded 2048-byte chunks but has no total-size rejection, so large on-disk files need a deliberate utility/API policy.
- Physical `file_clock` seconds and system-clock Unix seconds remain distinct on MSVC. Microsoft's documented file-clock epoch is 1601, with `to_utc/from_utc`; use `clock_cast<system_clock>` rather than assume `to_sys` exists. Cloud's timestamp feature changes which getter is used, but Storage still exposes physical time.
- PlayTime is an atomic scalar, yet loading a temporary from it does not deserialize into the atomic. There are actual nonzero roundtrip tests. The copy constructor and map read wrappers still violate supported scalar/Copy/snapshot concurrency (BASE-002), while assignment's eight-lock algorithm is a positive implementation detail.
- BootTime remains a transported adjustable system-clock anchor; unsigned final arithmetic can either reduce or wrap totals. A monotonic local anchor and duration snapshot are a separate design change from repairing serialization. Numeric width and wire compatibility must be planned together.

### Platform resources, loader, console, IDs and queues

- MachineInfo checks its first adapter allocations but not the final output allocation (BASE-014), and truncates successful computer names (BASE-013). Normal registry and known-folder release paths exist. A borrowed module handle with UNCHANGED_REFCOUNT must not be freed; dynamic module-name buffer growth is appropriate. Debug-ID exclusive open is a deliberately retained bounded process lease, not a new handle on every call. DLL unload/reload release policy is an unanswered contract question, not a demonstrated UAF.
- SharedLibUtils maps exports, unmaps on ordinary C++ exceptions, and populates its name vector during function-local static initialization. Subsequent matching pointers refer to stable strings. Trusted PE assumptions, relative module search and cross-module ImageHlp serialization deserve targeted deployment validation, but no malicious remote PE route or normal pointer-after-unload path was established. RED naming remains dormant in the current SDK set.
- Console capture/rebinding is process-global startup policy. `GalaxyDLL.cxx:24-60` uses capture then release after initialization; init exceptions bypass caller release. That caller cleanup is not relabeled as a new utility implementation defect. Tee failure short-circuiting, duplicate replay and unsupported concurrent cout-buffer mutation are noted boundaries; no active production tee call was found. A saved WNDPROC is not evidence of an installed subclass needing restoration.
- GlobalUniqueID and MessageUniqueID correctly use atomic counters for runtime-generated IDs; explicit message IDs are expected for correlations. Counts are not cryptographic or restart-persistent. FNV recursion, loop usage and class-ID seed semantics were checked with current tests/callers; no measurable performance result is claimed.
- MSVC uses PPL, not the fallback queue. The fallback protects queue operations but its emplace reference is only as stable as subsequent queue activity. No affected production use was established. `empty` is a snapshot, not synchronization of a later pop; current helpers use try_pop results.

## Actual tests inspected as context

### Serialization correction: existing assertions and their archive type

`UserHelloDataMessageTests.cxx:13-28` and `RequestSpecificUserDataMessageTests.cxx:16-33` both set PlayTime to 12 and expect 12 after roundtrip, alongside stats/user/rich-presence checks. `MessageSerializationTestUtils.hxx:11-23` uses Binary archives. The message constructors route through the unlocked container copy; production networking uses PortableBinary archives. `UnitTests/Versioned.cmake:6-22` discovers those message tests when the test targets are enabled. Therefore the immediate need is to execute/enforce the **existing** checks and supplement with the production archive and prepopulated input-object case. This pass cannot report a pass/fail result.

### Coverage observations, not a review of excluded test implementations

| Context source(s) | Assertions actually present | Focused additional validation relevant to this pass |
|---|---|---|
| `Source/UnitTests/Shared_NoVer/AchievementsAndStatsContainerTests.cxx`; `AchievementDataTests.cxx` | Sequential map access, achievement defaults/dirty state, copy construction, configured play-time lower bound | Supported scalar/Copy interleavings and coherent snapshots; deterministic clocks |
| `Source/UnitTests/Shared_NoVer/filesystem_container/filesystem_containerTests.cxx` | Create/write/read, promote to share 77, remove, reuse ID with another filename | Replacement generations, simultaneous name/ID/index invariants, same-name independent IDs |
| `Source/UnitTests/Shared_NoVer/filesystem_container/filesystem_container_entryTests.cxx` | Save/reload attributes and explicit timestamp; set/clear cache index | All copy phases, empty-state metadata restart, concurrent archive save, x86 wide-size rejection |
| `Source/UnitTests/Shared_NoVer/filesystem_container/filesystem_container_metadataTests.cxx` | Defaults, numeric parse fallback and reset | Whole-record/ID snapshots, not just individual map safety |
| `Source/UnitTests/Shared_NoVer/filesystem_container/filesystem_container_utilsTests.cxx` | Valid percent escaping, ordinary traversal rejection, lexical normalization and epoch helper | Windows case/link identities and prefix-conflicting metadata names |
| `Source/UnitTests/Shared/SharedFileUtilsTests.cxx` | Local-to-shared bytes/ID success, ranged read, remove, invalid arguments and missing-source no-publication | Repeat same-name IDs; reverse/unshared metadata copy; fault and concurrency paths |
| `Source/SystemTests/Host/CloudStorage.cxx:99-124` | 13-byte embedded-NUL put/list/metadata/get roundtrip with explicit timestamp/hash and savegame attributes | Same-file concurrent puts, restart persistence, capacity/error propagation and large-file handling |
| `Source/UnitTests/Shared_NoVer/MachineInfoTests.cxx`; `SharedLibUtilsTests.cxx` | Process/path consistency; reject empty symbol queries before load | Name counts/output allocation failure, future RED variant loading |
| Remaining listed Shared_NoVer tests | Hash constants/embedded NULs, index bounds/forced key, ID progression, input-stream bytes/EOF, safe-copy bounds, queue FIFO, tee dual output, macros, default templates and environment helper behavior | No absent-all-tests claim; these are not runtime concurrency/resource fault coverage |

All 21 manifest-listed Shared_NoVer test sources were read. Additional exact test-context paths are `Source/UnitTests/Shared/Networking/{UserHelloDataMessageTests.cxx,RequestSpecificUserDataMessageTests.cxx,MessageSerializationTestUtils.hxx}`, `Source/UnitTests/Shared/SharedFileUtilsTests.cxx`, and `Source/SystemTests/Host/CloudStorage.cxx`. Test manifests read: `Source/UnitTests/CMakeLists.txt`, `Source/UnitTests/Versioned.cmake`. Root test options default OFF (`CMakeLists.txt:14-29`); source/discovery does not prove execution in an existing build. CI files are outside this owner/scope and no enforcement claim is inferred from them.

## Caller, contract and dependency context actually used

These are targeted context reads/searches and do not expand the 40-input full-review claim:

- `Source/Shared/SharedFileUtils.{cxx,hxx}`: roots, lookup/read/write/remove adapters, clamping and copy destinations; `Source/Shared/Lobby.cxx:133-148` for forced-index use.
- `Source/Client/Impl/Storage.cxx`: worker read, ordinary file APIs, upload copy, download create/write and shared close; `Source/Client/Impl/CloudStorage.cxx:1-640`: list snapshots, buffer/callback get/put, metadata persistence, feature-gated clocks and delete.
- `Source/Client/Impl/Stats.cxx:20-164`, `User.cxx:322-391`, `Friends.cxx:455-514`: actual supported scalar/Copy/mutation/snapshot callers; targeted IniData stat/play-time save/load searches.
- `Source/Client/UniverseLAN.{cxx,hxx}`, `GalaxyDLL.cxx:1-105`, `ClientNetworkHandlers.cxx:55-114`: parent lifetime, startup console policy and hello snapshots.
- `Source/Server/ServerHandlers.cxx:455-510`: fresh ID allocation, shared-file creation and request lookup; this identifies cross-owner error-callback consequences without editing SERVER evidence.
- `Source/Shared/Networking/Networking.cxx:15-96`, `Networking.hxx:20-111`, complete `Messages/{UserHelloDataMessage,RequestSpecificUserDataMessage}.hxx`: packet guard/borrowed buffer lifetime and serialization ownership. KeyChallenge recursive-hash size was searched as context.
- SDK `Source/DLLs/1.139.2/galaxy/GalaxyApi.h:279-283`, `IStorage.h:113-291`, `1.148.11/galaxy/ICloudStorage.h:355-436`, and `1.152.11/galaxy/ICloudStorage.h:1-500`: thread-safety, portable file names, shared-ID APIs, cloud metadata/name/chunk and timestamp contracts. SDK headers were not reviewed as first-party implementation.
- Bundled `Source/Vendor/cereal-1.3.2/include/cereal/cereal.hpp:720-874` and `archives/portable_binary.hpp:255-334`: input forwarding and arithmetic mutation. Nested vendor implementation is contract context only.
- Root CMake, `Source/DLLs/CMakeLists.txt:1-85`, actual DLL directory inventory, feature-definition matches, and `Source/Tracer/CMakeLists.txt`: standards, x86 support, version gates and loader linkage.

Microsoft references fetched for this pass:

- <https://learn.microsoft.com/en-us/cpp/standard-library/file-clock-class?view=msvc-170> — 1601 epoch and clock conversion interface.
- <https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-getcomputernamea> — successful output count excludes NUL.

## Remediation and proposed Windows verification sequence

1. **Identity and concurrency first:** address ADD-001 and BASE-002 with explicit operation/snapshot lock boundaries. Force the recorded schedules; verify all entry maps, vector slots and cached indices agree. A global mutex is a possible simple starting point, but stream/callback ownership and lock order must be deliberate.
2. **Persistence transaction:** address ADD-003 plus BASE-005/006/008/009, preserving old data on failure and serializing final destination metadata. Add the ADD-004 successful-empty-state restart cases. A two-artifact file+metadata commit needs a recovery rule; atomic replacement of one archive is not by itself atomic replacement of both artifacts.
3. **Representation/namespace decisions:** solve ADD-002/006 with ID-keyed shared storage and a prefix-conflict-free metadata layout, aligned with BASE-004/011/012 Windows case/link/container policy. Plan migration before changing encoded keys and stored identities.
4. **Numeric/time semantics:** reject or stream oversize x86 files before narrowing (ADD-005), enforce actual read lengths (BASE-010), convert file clocks (BASE-007), store loaded PlayTime (BASE-001), and separate duration from wall clocks (BASE-003). Keep wire order/type compatibility explicit.
5. **Run existing tests and targeted checks:** especially the already written nonzero Binary message roundtrips, then equivalent PortableBinary and prepopulated cases; barrier-driven concurrency, Windows sparse-file boundaries, valid metadata-name conflicts and each copy failure phase. Retain success tests as regression/counterevidence. Machine name/allocation and space-query failures are smaller focused follow-ups (BASE-013/014/016).

Open decisions: supported maximum file size and callback chunk behavior; coexistence/update policy for repeated share IDs/names; local filesystem/reparse trust; intended process-versus-DLL debug-lease lifetime; transactional data/metadata publication semantics. No additional speculative finding is counted while those contracts remain unresolved.

## Execution and artifact record

Dedicated read/glob/grep tools performed inventory, complete production reads and targeted context/sidecar inspection. The read-only production comparison executed successfully with no output:

```text
git diff --exit-code b30e83872c0006e8240c8b4f565da5351bf10080 -- ":(glob)Source/Shared_NoVer/**/*.cxx" ":(glob)Source/Shared_NoVer/**/*.hxx" ":(glob)Source/Shared_NoVer/**/*.cmake" ":(glob)Source/Shared_NoVer/**/*.txt"
```

Report changes for this pass are this new notebook and append-only addenda in **10 owned sidecars**: `AchievementsAndStatsContainer.{cxx,hxx}.review.MD`, `CMakeLists.txt.review.MD`, `MachineInfo.cxx.review.MD`, `SharedLibUtils.cxx.review.MD`, and `filesystem_container/{filesystem_container.cxx,filesystem_container_entry.cxx,filesystem_container_metadata.cxx,filesystem_container_metadata.hxx,filesystem_container_utils.cxx}.review.MD`, all beneath `Source/Shared_NoVer`. Six full ADD sections occur once each in the two responsible implementation sidecars. Supporting references and old-ID refinements do not increase the count.

Read-only artifact checks completed:

- Compared the coverage-table paths with `git ls-tree -r --name-only b30e83872c0006e8240c8b4f565da5351bf10080 -- Source/Shared_NoVer`, filtered to the four assigned extensions: **BaselineInputs 40, CoverageRows 40, UniqueCoverageRows 40, CoverageDifferences 0**.
- Counted full `^### ADD-UTIL-[0-9]{3}` headings with `rg --no-ignore` in owned sidecars: **6 sections, 6 unique IDs**. Counted the notebook's baseline disposition rows: **16 rows, 16 unique IDs**.
- `git diff --numstat -- Source/Shared_NoVer .ai/review-addendum/UTIL.MD` confirmed **10 modified sidecars, additions only, zero deleted lines**; read-only `git --no-optional-locks status --short` additionally showed this notebook as new. `git diff --check` returned no errors for tracked changes. The production-only baseline diff was repeated and remained empty.
- Audit-command correction: the first coverage extraction used lookahead without PCRE2 and failed; rerunning with `--pcre2` produced the 40/40 result above. The initial recursive heading scan honored ignore rules and returned no matches; explicit `--no-ignore` produced the six verified headings. Neither initial result was used as evidence of absent coverage/findings.

**Completion:** 40/40 full source reads, 16/16 old dispositions, 6 new full finding records, 0 unfinished assigned files. New runtime verification remains unexecuted by instruction. This completion statement describes review coverage and artifacts, not absence of additional defects.
