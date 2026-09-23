# STORAGE — fresh full baseline review

## Executive summary

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Observed HEAD: `40265aed370464569e873692ef5d53fbdb12679b`. Windows runtime/build focus; static review only. All **14 assigned source/header files (5,203 lines)** were read completely and each has a newly authored `<filename>.review.MD` sidecar. No superseded report was consulted.

**23 unique findings: 8 High, 15 Medium; no Critical/Low findings.** All have high evidence confidence under the concrete conditions stated in their sections. “Confirmed” here means established by inspected code and contracts, not runtime-reproduced. Primary categories: 18 correctness/API/error-handling findings, 3 concurrency findings, 2 asynchronous memory-safety findings. Mixed-category sections explain their additional impacts.

Principal risks are destructive cloud replacement, false I/O success, ignored conditional-delete hashes, cancellation-related stale listeners, and unlocked access to mutable cached data. Several defects are reachable with normal single-threaded API sequences; concurrency findings explicitly require the documented interleavings. Prioritize save preservation and cancellable listener ownership before treating this storage surface as reliable for irreplaceable game progress.

The facade has useful version separation, bounded copies, checked enumeration, joining worker ownership, and real happy-path SystemTests. It is nevertheless local/LAN emulation with unsupported leaderboards, overlay, images, and third-party identity/service semantics. Those limits are distinguished from defects in operations it actually implements.

## Exact assigned coverage

Every path below was read from first line through EOF, including all current feature-guarded text. The adjacent report filename is exactly the path plus `.review.MD`. Header references do not duplicate finding counts.

| Reviewed path | Lines read | Canonical findings / disposition |
|---|---:|---|
| `Source/Client/Impl/Apps.cxx` | 1–133 | No independent finding; configuration/registrar/auth dependencies documented |
| `Source/Client/Impl/Apps.hxx` | 1–94 | No declaration-only finding; signature/lifetime/Init-limit notes |
| `Source/Client/Impl/CloudStorage.cxx` | 1–649 | BASE-STORAGE-001 through 009 |
| `Source/Client/Impl/CloudStorage.hxx` | 1–366 | Contract/state design notes; links to implementation findings |
| `Source/Client/Impl/Stats.cxx` | 1–504 | BASE-STORAGE-010 through 012 |
| `Source/Client/Impl/Stats.hxx` | 1–640 | Full stat/achievement/leaderboard surface and guard inspection |
| `Source/Client/Impl/Storage.cxx` | 1–340 | BASE-STORAGE-013 through 016 |
| `Source/Client/Impl/Storage.hxx` | 1–274 | Worker lifetime, ownership, path, callback and buffer contracts |
| `Source/Client/Impl/Telemetry.cxx` | 1–211 | BASE-STORAGE-021, 023 |
| `Source/Client/Impl/Telemetry.hxx` | 1–232 | Null array names, sink state, feature and callback contracts |
| `Source/Client/Impl/User.cxx` | 1–673 | BASE-STORAGE-017 through 020, 022 |
| `Source/Client/Impl/User.hxx` | 1–814 | All auth variants, defaults, state and data/token contracts |
| `Source/Client/Impl/Utils.cxx` | 1–97 | No independent finding; stub reachability and state limits documented |
| `Source/Client/Impl/Utils.hxx` | 1–176 | Version aliases, output/precondition and overlay/state contracts |

Assigned coverage is complete. Context inspection does not expand ownership to SDK, Shared, Server, CORE, or SystemTests sidecars. No-file-local-finding reports are scoped observations, not proofs of correctness.

## Finding index

Canonical detail links below contain severity, confidence, category, location, affected scope, evidence, failure mechanism, impact, possible solutions, recommended resolution, and proposed verification.

### High priority

- **BASE-STORAGE-001 — High / Correctness:** Failed cloud replacement truncates the previous save before the source/destination can succeed. Ordinary callback read failure or disk-full. [CloudStorage.cxx](../../Source/Client/Impl/CloudStorage.cxx.review.MD)
- **BASE-STORAGE-002 — High / Correctness:** Cloud read/write/metadata/delete errors become success; Windows denied-sharing and full-volume paths supplied. [CloudStorage.cxx](../../Source/Client/Impl/CloudStorage.cxx.review.MD)
- **BASE-STORAGE-005 — High / Correctness:** `expectedHash` is ignored, deleting a newer save on a stale guarded request. Sequential reproduction specified. [CloudStorage.cxx](../../Source/Client/Impl/CloudStorage.cxx.review.MD)
- **BASE-STORAGE-009 — High / Memory Safety:** Deferred cloud operation invokes a listener after explicit unregister/destruction. Direct cloud lambda plus CORE queue dependency distinguished. [CloudStorage.cxx](../../Source/Client/Impl/CloudStorage.cxx.review.MD)
- **BASE-STORAGE-012 — High / Concurrency:** Numeric/achievement operations use borrowed state after releasing locks; remote refresh can invalidate it. Requires concurrent supported API use. [Stats.cxx](../../Source/Client/Impl/Stats.cxx.review.MD)
- **BASE-STORAGE-013 — High / Concurrency:** File-share worker registers a raw listener after caller cancellation can already have completed. Deterministic delayed-worker interleaving specified. [Storage.cxx](../../Source/Client/Impl/Storage.cxx.review.MD)
- **BASE-STORAGE-017 — High / Memory Safety:** Private pending-auth listener set survives registrar unregistration and later calls freed listeners. [User.cxx](../../Source/Client/Impl/User.cxx.review.MD)
- **BASE-STORAGE-022 — High / Concurrency:** Thread-safe `GetUserDataCopy` copies an unlocked mutable string; concurrent live update/map replacement can invalidate it. [User.cxx](../../Source/Client/Impl/User.cxx.review.MD)

### Medium priority

- **BASE-STORAGE-003 — Medium / Correctness:** Cloud transfer ignores short sink writes and failed rewind signals. [CloudStorage.cxx](../../Source/Client/Impl/CloudStorage.cxx.review.MD)
- **BASE-STORAGE-004 — Medium / Correctness:** Default/empty upload hash is not calculated; overwrite can retain stale hash. Exact hash algorithm compatibility remains a separate validation question. [CloudStorage.cxx](../../Source/Client/Impl/CloudStorage.cxx.review.MD)
- **BASE-STORAGE-006 — Medium / Correctness:** Consecutive savegame groups and the first post-close file reuse an ID. [CloudStorage.cxx](../../Source/Client/Impl/CloudStorage.cxx.review.MD)
- **BASE-STORAGE-007 — Medium / Correctness:** Later requests replace callback-scoped list/metadata state before earlier callbacks run. [CloudStorage.cxx](../../Source/Client/Impl/CloudStorage.cxx.review.MD)
- **BASE-STORAGE-008 — Medium / Correctness:** Missing savegame metadata throws through buffered/metadata-only retrieval, reachable after separate metadata persistence failure. [CloudStorage.cxx](../../Source/Client/Impl/CloudStorage.cxx.review.MD)
- **BASE-STORAGE-010 — Medium / Correctness:** Average-rate updates sum per-interval rates, so splitting equal-rate intervals changes the answer. [Stats.cxx](../../Source/Client/Impl/Stats.cxx.review.MD)
- **BASE-STORAGE-011 — Medium / Correctness:** Store/reset always report success despite Shared INI failure; dirty flags can be lost before a retry. [Stats.cxx](../../Source/Client/Impl/Stats.cxx.review.MD)
- **BASE-STORAGE-014 — Medium / Correctness:** A remote uploader's file is attributed to the downloader. Requires a normal two-user share/download. [Storage.cxx](../../Source/Client/Impl/Storage.cxx.review.MD)
- **BASE-STORAGE-015 — Medium / Correctness:** Successful empty shared files cannot be distinguished from failure and are rejected. [Storage.cxx](../../Source/Client/Impl/Storage.cxx.review.MD)
- **BASE-STORAGE-016 — Medium / Correctness:** File-share source-read failure can become an empty successful upload; worker exceptions omit completion/cleanup. [Storage.cxx](../../Source/Client/Impl/Storage.cxx.review.MD)
- **BASE-STORAGE-018 — Medium / Correctness:** Sign-out emits auth-lost while runtime queries remain signed-in/logged-on and pending work remains live. [User.cxx](../../Source/Client/Impl/User.cxx.review.MD)
- **BASE-STORAGE-019 — Medium / Correctness:** Explicit sign-in timeout is ignored; absent server acceptance leaves the operation pending indefinitely. [User.cxx](../../Source/Client/Impl/User.cxx.review.MD)
- **BASE-STORAGE-020 — Medium / Correctness:** Null/default authorization-code listener suppresses operation; PlayFab specific listeners miss even unsupported-operation failures. [User.cxx](../../Source/Client/Impl/User.cxx.review.MD)
- **BASE-STORAGE-021 — Medium / Correctness:** SDK-valid null array names are inserted as C-strings into telemetry streams. MSVC diagnostic/stream-state behavior is not claimed universally identical. [Telemetry.cxx](../../Source/Client/Impl/Telemetry.cxx.review.MD)
- **BASE-STORAGE-023 — Medium / Correctness:** Unopened default telemetry stream is mistaken for a working sink; first event can report success and later events failure when storage is disabled. [Telemetry.cxx](../../Source/Client/Impl/Telemetry.cxx.review.MD)

## Architecture, strengths, and limits

Flow: SDK versioned facade → `InterfaceInstances` dependencies → configuration/user caches and `SharedFileUtils` → filesystem containers/entries or network messages → response handlers → registrar/`DelayRunner` → callbacks on `ProcessData`.

**Positive evidence:** Feature guards localize ABI changes. Callback argument strings are copied by the notification extender. Cloud enumeration and Shared index lookup check bounds. Bounded copies handle destination null/zero capacity and termination. User objects use shared ownership and self-ID normalization. Shared container maps and metadata fields have locking. File-share workers use joining ownership and completed workers are joined outside the worker-list lock. Normal explicit reset preserves worker dependencies. Binary and offset storage roundtrips, restart persistence, propagation, and policy-denial SystemTests provide useful foundations.

**Limits:** Locking container lookup does not protect escaped references. The public async facade often does its I/O synchronously and queues only a result, while keeping callback-only data in mutable singleton caches. Listener lifetime is split among direct queue captures, request maps, private auth sets, and worker captures. Persistence status is lost at multiple layers; data and metadata are separate nontransactional files. Shared wire messages lack explicit empty-file success and owner metadata. Authentication mixes configured identity with runtime connectivity. These are current reliability/testability costs, not style objections to facades or raw pointers in general.

**Leaderboard assessment:** All current definition, lookup, retrieval, and score-update methods report failure. No ranking container, comparator, successful entry callback, or index calculation exists. Getter preconditions cannot be satisfied by this implementation. Ordering/range/force-update/details contracts were inspected, but no unsupported off-by-one or sort-direction finding was manufactured. Implementing leaderboards is a capability project, not a correction to an existing sort algorithm.

**Other capability boundaries:** Cloud storage is local; telemetry is a local call trace; Apps uses configured DLC/language; tokens/tickets simulate identity; images/notifications/overlay are stubs. No claim is made that configured LAN trust is itself a vulnerability, or that these interfaces provide real third-party service compatibility.

## Dependencies and integration handoffs

- **CORE:** Generic queued specific-listener cancellation overlaps the mechanism in 009. Preserve the direct cloud lambda, late worker admission (013), and private auth set (017) cases when deduplicating; fixing one registrar path does not fix all. Inspect automatic global destruction as well as explicit reset, partial-Init Apps availability, and missing SDK error-state propagation.
- **NET:** `IniData` save-result/dirty handling is the dependency for 011 and User writes. DLC map mutation synchronization and local user initialization are context. Share/request result and owner metadata changes for 014–016 need coordinated wire evolution.
- **UTIL:** Filesystem write/close status, transactional replacement, failed-unlink cache removal, and separate metadata consistency support 001/002/008/016. Borrowed stat/user-data references support 012/022. Windows timestamp conversion is a root-level handoff: `filesystem_entry::get_timestamp` uses raw file-clock epoch seconds; the Storage caller clamps that to 32 bits, and the oldest Cloud getter narrows directly. No duplicate STORAGE ID assigned for that Shared root.
- **SERVER:** Share handling returns a newly allocated ID even after storage failure; download messages lack explicit status and uploader identity. Client findings 014–016 require coordinated server remediation rather than an isolated payload-size workaround.
- **BUILD/coordinator:** Feature boundaries were inspected textually. No ABI, compiler, sanitizer, or linker results are asserted. Preserve compatibility while introducing internal result/state types.

## Context actually inspected

The following were dependency/contract context, not additional assigned sidecar coverage.

**Completely read context files:**

- `Source/Shared/SharedFileUtils.cxx`, `Source/Shared/SharedFileUtils.hxx`.
- `Source/Shared_NoVer/filesystem_container/filesystem_container.cxx`, `filesystem_container_entry.cxx`, `filesystem_container_entry.hxx`, `filesystem_container_metadata.cxx`, `filesystem_container_utils.cxx` (all under that same directory).
- `Source/Shared_NoVer/AchievementsAndStatsContainer.cxx`, `AchievementsAndStatsContainer.hxx`, `AchievementData.cxx`, `ConstHash.hxx`, `SafeStringCopy.hxx`, `ContainerGetByIndex.hxx` (all under `Source/Shared_NoVer/`).
- `Source/Shared/Networking/Messages/FileRequestMessage.hxx`, `FileShareMessage.hxx`, `RequestSpecificUserDataMessage.hxx` (same directory).
- `Source/Client/Impl/ListenerRegistrar.cxx`, `ListenerRegistrar.hxx`; `Source/Client_NoVer/Impl/DelayRunner.cxx`, `NotificationParamScopeExtender.hxx`.
- `Source/Client/UniverseLAN.cxx`, `UniverseLAN.hxx`, `Client.cxx`, `ClientNetworkHandlers.cxx`.
- `Source/SystemTests/Host/Apps.cxx`, `CloudStorage.cxx`, `Stats.cxx`, `Storage.cxx`, `Telemetry.cxx`, `UserData.cxx`, `Utils.cxx` (same directory).
- SDK context under `Source/DLLs/1.152.11/galaxy/`: `IApps.h`, `ICloudStorage.h`, `IStorage.h`, `ITelemetry.h`, `IUtils.h`.

**Partial/targeted context, explicitly not claimed fully reviewed:**

- `Source/Shared/IniData.cxx`: 400–494 and 620–980; targeted search for local-user allocation at 605 and relevant getters/defaults/save methods. `Source/Shared/IniData.hxx`: searched relevant accessor/save declarations only.
- `Source/Server/ServerHandlers.cxx`: 176–220 and 450–524; targeted handler-name lookup.
- `Source/Client/GalaxyDLL.cxx`: 155–186 (`ProcessData` and error/accessor context); related lifecycle/accessor searches.
- `Source/Client/Impl/Friends.cxx`: 165–234 (avatar producer and nearby APIs).
- `Source/galaxy_sdk_features.cmake`: targeted cloud, sign-out, OpenID, authorization-code and timeout boundaries; not a build-manifest review.
- SDK `Source/DLLs/1.152.11/galaxy/IStats.h`: 377–897; `IUser.h`: 315–861; `IListenerRegistrar.h`: 140–242; `GalaxyApi.h`: 280–344. Related thread-safety/contract searches were scoped to SDK headers.
- SDK `Source/DLLs/1.148.11/galaxy/ICloudStorage.h`: 255–414 (legacy metadata/callback/upload contracts).
- Instructions read: `.ai/review-baseline/PLAN.MD`, `.ai/SKILLS/CppReviewer.md`, `.ai/ai-instructions-review.txt`. `AGENTS.md` glob found none under this repository. Current user/plan constraints governed over older branch/build suggestions.

## Actual execution and limits

Executed read-only Git checks in `C:\Development\AI\UL`:

1. `git status --short`: observed preexisting staged removals of superseded sidecars and the review-baseline directory. These were not modified through Git.
2. `git rev-parse HEAD`: returned the merge SHA stated above.
3. `git diff b30e83872c0006e8240c8b4f565da5351bf10080 --` followed by the 14 explicit assigned `.cxx/.hxx` paths: empty output.
4. `git diff --exit-code b30e83872c0006e8240c8b4f565da5351bf10080 -- Source ':(exclude)**/*.review.MD'`: success, empty output. Current Source inputs inspected as context also match baseline.

Final artifact validation also completed:

- Glob `{Apps,CloudStorage,Stats,Storage,Telemetry,User,Utils}.{cxx,hxx}.review.MD` returned exactly the 14 assigned sidecars.
- `rg -n` restricted to those filenames enumerated all 23 full finding headings and their severity lines: 8 High, 15 Medium, IDs 001–023 without gaps or duplicate full sections.
- `rg --count-matches` checked the finding heading, five metadata fields, and six required detail labels. Totals were CloudStorage 108, Stats 36, Storage 48, Telemetry 24, User 60: exactly 12 structural elements per finding, 276 overall. Header/no-finding sidecars correctly add no duplicated defect sections.
- Repeated the Source baseline diff after report creation: success, empty output. A path-scoped `git status --short` showed the preexisting staged old-report deletions plus the 14 new untracked sidecars and new `STORAGE.MD`; no staging or other Git write was performed.

Dedicated read/glob/grep tools supplied the textual inspection and line references. All report edits used `apply_patch`. No production edits, builds, test runs, sanitizer runs, Git writes, branch changes, commits, pushes, or credential-file access occurred. Proposed verification in sidecars is future work, not execution evidence.

Static coverage does not establish timing/frequency in shipped games, exact vendor hash vectors, all Windows filesystem edge behavior, or every SDK version's ABI. Linux guard text was visible during source reads; no Linux build/runtime work was performed. Repository-wide CI/build ownership remains with the coordinator. No benchmark or exploitability claim is made.

## Verification/remediation roadmap

1. **Preserve data:** transactional cloud replacement and reliable data/metadata/read/delete results (001/002/008), then consistent hashing and atomic guarded deletion (004/005). Include Windows read-only, sharing-denied, full-volume, and retry-after-failure cases.
2. **Make async lifetime explicit:** one cancellable operation model spanning registrar queue, direct cloud tasks, workers and auth pending state (009/013/017). Validate cancellation before dispatch and late replies with Windows ASan.
3. **Repair state/data consistency:** locked snapshots for stats/user copies (012/022), independent per-callback cloud snapshots (007), new group identity on every save boundary (006), and actual sign-out/deadline/listener routing (018–020).
4. **Close correctness gaps:** persistence retry/dirty-state results and weighted average-rate data (010/011); sharing status/owner/empty support (014–016); legal telemetry array names and explicit disabled/open/error state (021/023).
5. **Focused regression work:** extend the inspected SystemTests with multiple pending cloud requests, consecutive groups, implicit hashes, stale deletes, short callbacks, two-user ownership, empty files, cancelled listeners, failed saves and concurrent cache updates. Current happy-path tests are valuable but do not validate these paths.

Completion claim is limited to the 14-file STORAGE assignment and its fresh reports. Full-repository reconciliation and dependency deduplication remain coordinator work.
