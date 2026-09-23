# UTIL — fresh Shared_NoVer baseline review

## Executive summary

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080` in `C:\Development\AI\UL`. **40/40 assigned inputs read in full; 40 new adjacent `.review.MD` reports created.** This is an independent full-file review, not a delta/old-finding confirmation. Review instructions: `PLAN.MD`, `.ai/SKILLS/CppReviewer.md`, and applicable scope context from `.ai/ai-instructions-review.txt`.

**15 confirmed finding records: 1 High, 12 Medium, 2 Low; plus 1 informational latent issue (015).** Reconciliation established that no current SDK directory enables RED. Categories of confirmed records: Correctness 13, Concurrency 1, Memory Safety 1. Repeated full sections for BASE-UTIL-012 describe one root cause. After the static review, the coordinator reproduced 001, 006 and 007 against the built baseline; see `VERIFICATION.MD`.

The strongest risk is lock coverage that violates supported scalar/Copy API concurrency. Persistence and Windows filename/time semantics have several concrete reliability failures. Small owning-value helpers, guarded platform selection, bounded string copies and ordinary stream/packet lifetimes are generally straightforward. Fix synchronization and filesystem completion/error handling before relying on this layer for concurrent save/share workloads; this review is not release certification.

## Exact assigned-input coverage

Every row means the **entire baseline-matching file was read**, including inactive branches. Each has a new sidecar formed by appending `.review.MD`. A dash means no independent finding was assigned to that file, not proof of correctness. Header notes cross-reference implementation findings where applicable. No `.cmake` file exists in this 40-input inventory; the sole manifest is CMakeLists.txt.

| # | Exact repository-relative path | Lines read | Finding sections |
|---:|---|---:|---|
| 1 | `Source/Shared_NoVer/AchievementData.cxx` | 100 | — |
| 2 | `Source/Shared_NoVer/AchievementData.hxx` | 43 | — |
| 3 | `Source/Shared_NoVer/AchievementsAndStatsContainer.cxx` | 172 | 002, 003 |
| 4 | `Source/Shared_NoVer/AchievementsAndStatsContainer.hxx` | 105 | 001 |
| 5 | `Source/Shared_NoVer/CMakeLists.txt` | 30 | 015 (shared root cause) |
| 6 | `Source/Shared_NoVer/ConcurrentQueue.hxx` | 14 | — |
| 7 | `Source/Shared_NoVer/ConcurrentQueueUnsupported.hxx` | 80 | — |
| 8 | `Source/Shared_NoVer/ConsoleCoutRedirector.cxx` | 57 | — |
| 9 | `Source/Shared_NoVer/ConsoleCoutRedirector.hxx` | 55 | — |
| 10 | `Source/Shared_NoVer/ConstHash.hxx` | 43 | — |
| 11 | `Source/Shared_NoVer/ContainerGetByIndex.hxx` | 65 | — |
| 12 | `Source/Shared_NoVer/CustomConsole.cxx` | 73 | — |
| 13 | `Source/Shared_NoVer/CustomConsole.hxx` | 5 | — |
| 14 | `Source/Shared_NoVer/DefaultConfigFiles.cxx` | 259 | — |
| 15 | `Source/Shared_NoVer/DefaultConfigFiles.hxx` | 10 | — |
| 16 | `Source/Shared_NoVer/EnvUtils.cxx` | 66 | — |
| 17 | `Source/Shared_NoVer/EnvUtils.hxx` | 13 | — |
| 18 | `Source/Shared_NoVer/GlobalUniqueID.cxx` | 14 | — |
| 19 | `Source/Shared_NoVer/GlobalUniqueID.hxx` | 16 | — |
| 20 | `Source/Shared_NoVer/MachineInfo.cxx` | 691 | 013, 014 |
| 21 | `Source/Shared_NoVer/MachineInfo.hxx` | 56 | — |
| 22 | `Source/Shared_NoVer/MemoryInputBuffer.cxx` | 22 | — |
| 23 | `Source/Shared_NoVer/MemoryInputBuffer.hxx` | 14 | — |
| 24 | `Source/Shared_NoVer/MemoryInputStream.cxx` | 31 | — |
| 25 | `Source/Shared_NoVer/MemoryInputStream.hxx` | 28 | — |
| 26 | `Source/Shared_NoVer/Networking/MessageUniqueID.cxx` | 23 | — |
| 27 | `Source/Shared_NoVer/Networking/MessageUniqueID.hxx` | 28 | — |
| 28 | `Source/Shared_NoVer/Networking/SendableEventMessage.hxx` | 32 | — |
| 29 | `Source/Shared_NoVer/PreprocessorControlIf.hxx` | 10 | — |
| 30 | `Source/Shared_NoVer/SafeStringCopy.hxx` | 131 | — |
| 31 | `Source/Shared_NoVer/SharedLibUtils.cxx` | 186 | 015 |
| 32 | `Source/Shared_NoVer/SharedLibUtils.hxx` | 29 | — |
| 33 | `Source/Shared_NoVer/filesystem_container/filesystem_container.cxx` | 463 | 004, 005, 011, 012, 016 |
| 34 | `Source/Shared_NoVer/filesystem_container/filesystem_container.hxx` | 90 | — |
| 35 | `Source/Shared_NoVer/filesystem_container/filesystem_container_entry.cxx` | 397 | 006–010 |
| 36 | `Source/Shared_NoVer/filesystem_container/filesystem_container_entry.hxx` | 89 | — |
| 37 | `Source/Shared_NoVer/filesystem_container/filesystem_container_metadata.cxx` | 162 | — |
| 38 | `Source/Shared_NoVer/filesystem_container/filesystem_container_metadata.hxx` | 86 | — |
| 39 | `Source/Shared_NoVer/filesystem_container/filesystem_container_utils.cxx` | 216 | 012 (shared root cause) |
| 40 | `Source/Shared_NoVer/filesystem_container/filesystem_container_utils.hxx` | 30 | — |

## Finding index

Full evidence, mechanism/impact, alternatives, recommended fix and proposed verification are in the named adjacent sidecars. All IDs below have prefix `BASE-UTIL-`.

| ID | Severity / category | Finding | Primary source location |
|---|---|---|---|
| BASE-UTIL-001 | Medium / Correctness | Input archive loads PlayTime into a discarded temporary | `AchievementsAndStatsContainer.hxx:51-55` |
| BASE-UTIL-002 | High / Concurrency | Escaped protected values and unlocked snapshot copying race supported API calls | `AchievementsAndStatsContainer.cxx:14-19,57-83,109-117,138-146` |
| BASE-UTIL-003 | Medium / Correctness | Adjustable/remote wall clocks corrupt elapsed play time | `AchievementsAndStatsContainer.cxx:25-30` |
| BASE-UTIL-004 | Medium / Correctness | Distinct case-sensitive keys alias one Windows file | `filesystem_container/filesystem_container.cxx:78-135,144-200` |
| BASE-UTIL-005 | Medium / Correctness | Failed creation/metadata persistence still publishes indexed entries | `filesystem_container/filesystem_container.cxx:123-135,174-204` |
| BASE-UTIL-006 | Medium / Correctness | Failed deletion still unregisters surviving data and clears metadata | `filesystem_container/filesystem_container_entry.cxx:91-112` |
| BASE-UTIL-007 | Medium / Correctness | MSVC file-clock epoch exposed as Unix time | `filesystem_container/filesystem_container_entry.cxx:188-195` |
| BASE-UTIL-008 | Medium / Correctness | Success returned before buffered write/close errors are observed | `filesystem_container/filesystem_container_entry.cxx:291-308,351-371` |
| BASE-UTIL-009 | Medium / Correctness | Copy rollback deletes pre-existing destination data/metadata | `filesystem_container/filesystem_container_entry.cxx:150-176` |
| BASE-UTIL-010 | Medium / Correctness | Short whole-file read returns zero padding as data | `filesystem_container/filesystem_container_entry.cxx:238-269` |
| BASE-UTIL-011 | Medium / Correctness | Dot container names alias parent/named-root namespaces | `filesystem_container/filesystem_container.cxx:434-459` |
| BASE-UTIL-012 | Medium / Correctness | Canonical relative enumeration duplicates link targets in index | `filesystem_container/filesystem_container.cxx:29-42`; utils `56-64` |
| BASE-UTIL-013 | Medium / Correctness | Last computer-name character discarded before name-based hashing | `MachineInfo.cxx:511-523` |
| BASE-UTIL-014 | Low / Memory Safety | Unchecked MAC output HeapAlloc is dereferenced | `MachineInfo.cxx:97-105` |
| BASE-UTIL-015 | Informational / Build | Latent RED basename selection; no current version activates the branch | `SharedLibUtils.cxx:99-118`; `CMakeLists.txt:3-13` |
| BASE-UTIL-016 | Low / Correctness | Failed space query appears as huge capacity/zero use | `filesystem_container/filesystem_container.cxx:365-381` |

## Architecture and traced contracts

### Filesystem ownership, indexing and error paths

`SharedFileUtils` owns shared root containers for local/shared/cloud/avatar data. Parents own named/nameless cloud subcontainers. Containers own entries through name/ID/index maps; entries retain a raw reverse parent association and cached paths. Index methods check bounds; removal swaps the last item into the removed slot and updates its cached index. Multi-map operations use deadlock-avoiding `std::lock`. Metadata map methods use recursive locks and value-returning snapshots.

Traced Storage's synchronous read/write/delete, FileShare's jthread whole-file read, download publication and shared close; CloudStorage list snapshots, buffer/callback reads/writes and delete; server authenticated share/request handlers; SharedFileUtils copy helpers. Normal parent lifetime was checked through `InterfaceInstances` member/reset order: sfu is retained, cloud/storage users are destroyed first, deferred cloud reads capture a subcontainer owner, and transport workers stop. **No reachable parent use-after-free is claimed.**

Limits: membership locks do not make file bytes or composite metadata atomic; vector snapshots keep entries alive but stat/access calls see current disk state. No rollback transaction spans files, metadata and indexes. Canonical containment checks are good initial checks, not handle-based confinement against subsequent local junction/symlink replacement. Case aliases and startup link identities need one common policy. IStorage excludes special/restricted platform names and backslashes; prohibited device-name experiments are not treated as current compliant SDK defects. Dot cloud names are considered separately because the inspected cloud interface accepts a container name without that relative-path precondition.

### Stats, IDs, hashes and streams

SDK `1.139.2/galaxy/GalaxyApi.h:279-283` establishes general thread safety with pointer-return exceptions. BASE-UTIL-002 uses scalar and Copy APIs plus live snapshot construction, not retained pointers outside their documented lifetime. ProcessData drives application handlers; the transport worker does not directly dispatch these stats callbacks. Copying an atomic counter does not protect four maps/BootTime.

Cereal input forwarding was read to prove BASE-UTIL-001, including the arithmetic loader. Stats union bit persistence is MSVC-oriented and lacks explicit type tagging; no Linux-runtime defect is inferred. GlobalUniqueID and MessageUniqueID are independent atomic runtime namespaces, not restart-stable or cryptographic IDs. FNV constants/byte handling were checked; iterative hashing handles cloud payloads, and the recursive challenge data caller uses eight bytes. Class IDs use a deliberate length seed and must remain wire-compatible.

MemoryInputStream owns buffer/stream objects but borrows bytes. In Networking, Cereal finishes using those bytes before the packet destruction guard runs; stream destruction precedes buffer destruction. No expired-span or packet-lifetime violation was established. SafeStringCopy checks capacities and states its non-overlap/NUL preconditions; locks must protect its sources in Copy callers.

### Platform and build boundaries

MachineInfo separates discovered-path availability from stored paths, dynamically grows module path buffers, releases registry handles and normal known-folder allocations, and has explicit appdata/environment fallbacks. Remaining limits include fallback writability, registry value validation, exception-safe raw OS allocations, MAC selection stability and process-scoped debug lock ownership. The successful debug-ID handle is deliberately kept open; it is not reacquired on each call. Module-unload release semantics are unspecified.

Common no-version helpers reduce repeated per-SDK compilation, but BASE-UTIL-015 violates that boundary by preprocessing a version-specific basename inside the shared object. Root CMake establishes C++20; system libraries and Windows declarations are guarded. MSVC PPL is the Windows queue, with an explicitly unsupported alternative for other Windows compilers. Console binding/cout redirection is process-wide startup policy without general concurrent logging or retry guarantees. Default INI values and parser fallback differences were checked; published LAN authentication/configuration defaults are not labelled an exploit.

## Dependencies and caller context actually inspected

Context reads/searches were targeted; these paths are **not additional full-review claims**:
- `Source/Shared/SharedFileUtils.{cxx,hxx}`, `GalaxyUserData.hxx`, `IniData.cxx` (relevant configuration/load/save/reset ranges), `Lobby.cxx` (index contracts).
- `Source/Client/Impl/{Storage,CloudStorage,Stats}.cxx`, `CloudStorage.hxx`, relevant User/Friends/Matchmaking methods; Client, ClientNetworkHandlers, GalaxyDLL, UniverseLAN ownership/dispatch code.
- `Source/Server/ServerHandlers.cxx` user-snapshot and share/request ranges; server and client ID/hash call-site searches.
- `Source/Shared/Networking/Networking.{cxx,hxx}`, UserHelloDataMessage and RequestSpecificUserDataMessage headers; Client_NoVer DelayRunner; interceptor loader-construction methods.
- Root/Source CMake, versioned Shared/interceptor/DLL wiring, Tracer system linkage, and the RED feature definition.
- SDK `1.139.2` GalaxyApi/IStorage contracts and `1.152.11` cloud name contract; Cereal 1.3.2 input dispatch, portable arithmetic loading and map adapter context. SDK/vendor code is contract context only.
- Existing unit-test source for stats, filesystem container/entry/utils/metadata, index helpers, MachineInfo, SharedLibUtils, memory buffer/stream; ID/hash test assertions were searched. Existing SystemTests cloud roundtrip was read. No existing findings/logs were reused.

## Testing, security, performance and portability assessment

- Existing tests cover successful value access, basic persistence, bounds, normalization, file sharing/removal, explicit metadata timestamps and local cloud roundtrips. Follow-up inspection confirmed that `UserHelloDataMessageTests.cxx` and `RequestSpecificUserDataMessageTests.cxx` already assert nonzero play-time preservation through serialization; the immediate gap there is execution/enforcement, not missing assertions. The initial coverage statement was too broad. Focused coverage remains missing for failed delete/create/flush, physical file epochs, concurrent Copy APIs, case/link aliasing and hypothetical RED mixed-version loading. See [TEST-COVERAGE-GAPS.MD](TEST-COVERAGE-GAPS.MD).
- No tests, builds, sanitizer runs, analyzers, DLL loads, storage mutations or live configuration generation were performed. Every verification paragraph is proposed work.
- No performance measurements: map-by-index is linear; recursive string hashes/capture buffers and full-file vectors have size-dependent costs. These are architectural limits, not benchmark claims.
- No remote exploit is asserted from LAN trust, trusted PE loading, local reparse manipulation or prohibited SDK lifetimes. Windows case/clock/resource contracts were reviewed directly. Linux code was read only as incidental conditional context; no Linux-runtime findings or execution.

## Actual execution and artifact reconciliation

Read-only Git commands, run in the repository:
1. `git ls-tree -r --name-only b30e83872c0006e8240c8b4f565da5351bf10080 -- Source/Shared_NoVer` — returned exactly the 40 paths above.
2. `git diff b30e83872c0006e8240c8b4f565da5351bf10080 -- Source/Shared_NoVer ':(exclude)*.review.MD'` — empty; repeated with `--exit-code` after report creation, also empty/successful.
3. `git -c core.quotePath=false ls-files --others --exclude-standard -- Source/Shared_NoVer .ai/review-baseline/UTIL.MD` — confirmed newly created adjacent report paths (notebook added subsequently).
4. PowerShell `Compare-Object` of the Git baseline inventory with `.review.MD` appended versus `git ls-files --others --exclude-standard -- Source/Shared_NoVer` — **BaselineInputs 40, NewSidecars 40, CoverageDifferences 0**.
5. `rg --no-filename --only-matching '^### BASE-UTIL-[0-9]{3}' Source/Shared_NoVer -g '*.review.MD' | Sort-Object -Unique` — exactly BASE-UTIL-001 through BASE-UTIL-016. `rg --count-matches '^Baseline:' Source/Shared_NoVer -g '*.review.MD'` — one baseline marker in each of the 40 reports.

Dedicated read/glob/grep tools provided complete assigned-file reads, caller/contract searches and report inspection. Initial sidecar glob was empty; final sidecar inventory contained all 40 expected reports. All edits were made with `apply_patch` and are confined to those sidecars plus this notebook. No production or Git state writes were performed. Credentials and superseded finding reports were not consulted.

Two Microsoft references were fetched to confirm platform contracts:
- https://learn.microsoft.com/en-us/cpp/standard-library/file-clock-class?view=msvc-170 — MSVC's 1601 file-clock epoch and to_utc/clock_cast conversion.
- https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-getcomputernamea — successful output count excludes the terminator.

## Remediation sequence and incomplete list

1. Repair complete-operation/snapshot lock coverage (002) and archive counter storage (001). Design clock-duration semantics (003) before changing the wire format.
2. Introduce checked completion and transactional publication/removal/copy (005, 006, 008–010); retain recoverable old state on failure.
3. Unify Windows name/link/subcontainer identities (004, 011, 012), convert physical timestamps (007), and report space errors (016).
4. Correct machine-name extraction/output allocation (013, 014) and inject version-aware loader names (015).
5. Add focused regression/fault-injection cases from each finding; coordinate caller-layer callback/error propagation with STORAGE/NET/BUILD owners.

**Incomplete assigned reads/reports: none (0/40).** Pending validation: all proposed runtime/fault/concurrency tests, compile/generator checks, and mixed-version interceptor loading. Context files outside the assignment were traced selectively and are not claimed exhaustively reviewed. No finding-free report is proof of correctness.
