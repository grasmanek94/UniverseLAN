# INTERCEPT — fresh baseline review notebook

## Executive summary

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`.

**Coverage: 73/73 assigned inputs read completely; 73 new per-file sidecars created.** Inventory: 37 `.cxx`, 35 `.hxx`, 1 `.txt` (CMakeLists), 0 `.cmake`. No incomplete source-file coverage. This was the requested shallow serious-defect scan, not exhaustive behavioral or ABI verification.

**11 confirmed finding records: 6 High, 5 Medium.** Reconciliation rates 001 Medium for the proven teardown-contract violation; a native registrar use-after-free remains a conditional High impact. All records have High confidence in the cited mechanism, not in an unexecuted vendor failure mode. No Critical findings. Repeated descriptions share IDs and count once.

The highest risks are callback/cancellation ownership, shutdown against an expired real registrar, lost authentication/matchmaking completions, unbounded output tracing, and initialization that requests exports absent from the selected SDK generation. The code has useful null-preserving proxy construction and bounded string helpers, but those do not make its ownership/extent handling safe. Fix lifecycle and dispatch before treating the interceptor as transparent diagnostic instrumentation.

## Scope and method

- Followed this directory's PLAN.MD, `.ai/SKILLS/CppReviewer.md`, the active user constraints and relevant scope exclusions in `.ai/ai-instructions-review.txt`.
- Independently read every assigned input from the working tree, then traced local callers, shared loader/trace helpers and selected vendor SDK contracts. Superseded reports were not opened or consulted. File-specific notes and full finding sections live in adjacent `<filename>.review.MD` files.
- Windows x86/x64 runtime/ABI focus. Non-Windows guards were read statically; Linux was not built or run.
- Wrote only InterceptionLogger sidecars and this notebook using `apply_patch`. No production edits, builds, tests, analyzers, sanitizer runs, real-DLL loads, credential access, Git index updates, commits or branch changes were performed.
- A no-independent-finding report is a scoped result. Shared findings are referenced from dependent consumers rather than counted again. Below-threshold observations and unproven concerns are distinguished from the 11-finding index below.

## Architecture and important flows

1. **Export adapters:** `GalaxyApi.cxx` provides the modern free-function ABI; `GalaxyApiFactory.cxx` provides older IGalaxy/GalaxyFactory wrappers. `IGalaxyFix.cxx` emits compatibility definitions. Game-server exports own a separate UniverseGameServer instance.
2. **Session owner:** `GalaxyDLL.cxx` owns the client InterfaceInstances. Each InterfaceInstances retains config/init strings, real entry-point functions, and unique_ptr API wrappers. Game-server initialization reuses the same construction routine with a domain flag.
3. **Dynamic loading:** `Shared_NoVer/SharedLibUtils` locates the RealGalaxy DLL, inventories Windows exports and resolves name substrings. Missing/ambiguous exports throw. The interceptor chooses which symbols to require; incorrect version gates therefore abort initialization rather than merely disabling an optional API.
4. **API forwarding:** Impl classes call getter functions for the real SDK interfaces and trace inputs/results. They register null-target global observation listeners with a borrowed real registrar. Some configuration options deliberately override authentication/DLC behavior.
5. **Specific callbacks:** Non-null per-operation listeners are replaced by heap proxies. A process-wide map relates proxy to original listener; a second set marks proxies protected while calling game code. Callback epilogues remove mappings and delete themselves. Cancellation takes raw pointers out of the map and unregisters/deletes them. Neither ownership pins nor registrar identity accompany those records.
6. **Teardown:** Real Shutdown currently runs before wrapper destruction/unregistration. This violates the SDK lifetime order. The proxy registry is not owned/drained by a session. Explicit reset also recreates tracing configuration; process-static destruction has further ordering dependencies on the real DLL and tracer.
7. **Build:** CMake creates a version-specific static interceptor library linked with common-shared code and disables unity inclusion for these sources. Feature definitions select SDK signatures/export availability. The only assigned build manifest was read, not configured.

### Supported positive observations

- `encapsulate(nullptr)` preserves optional listener omission. Global observation listeners have null targets and do not self-delete in the proxy macro.
- `pop_proxies_from_real` uses an erase-safe iterator loop. A single callback's same-thread self-unregister is explicitly protected during the target invocation. These are limited positives, not evidence of cross-thread lifetime safety.
- Most nullable strings use an annotation helper; bounded copy-buffer tracing uses `memchr` with a capacity limit. `GetLobbyMessage` additionally clamps to returned length and capacity before payload inspection.
- Binary custom-networking/storage buffers and Steam ticket inputs are normally logged as addresses/sizes rather than decoded speculatively.
- The shared resolver rejects missing/ambiguous symbols with exceptions instead of returning unchecked null entry points.

## Unique finding index

Paths below are repository-relative. Full evidence, mechanism, impact, possible fixes, recommended resolution and proposed verification are in each named sidecar.

- **BASE-INTERCEPT-001 | Medium | API/ABI | High confidence:** Internal global observers are unregistered after real SDK shutdown. Locations: `Source/InterceptionLogger/GalaxyDLL.cxx:72–86`, `Source/InterceptionLogger/UniverseGameServer.cxx:39–54`. Full reports: both corresponding `.review.MD` files. The lifetime-contract violation is confirmed. Native registrar destruction is not established; a resulting use-after-free is a conditional High impact, not a reproduced crash.
- **BASE-INTERCEPT-002 | High | Concurrency | High confidence:** Callback completion and cancellation can both delete one proxy. Locations: `Source/InterceptionLogger/Impl/ListenerRegistrar.cxx:43–48`, `Impl/Listeners/ProxifySingleShotListener.cxx:18–37,74–91`, `.hxx:56–64`. Full reports: all three corresponding sidecars. The recorded barrier interleaving needs no application-listener destruction or vendor race.
- **BASE-INTERCEPT-003 | High | Memory Safety | High confidence:** Global target-only cancellation deletes another session's still-registered proxy. Locations: `Source/InterceptionLogger/Impl/ListenerRegistrar.cxx:43–48`, `Impl/Listeners/ProxifySingleShotListener.cxx:11–29`, `.hxx:16–20,43–50`. Full reports: the same three responsible-file sidecars. Reusing one specific lobby-created listener for client and server suffices; concurrency is unnecessary.
- **BASE-INTERCEPT-004 | High | Correctness | High confidence:** AuthListener::OnAuthSuccess only traces, so supplied auth listeners never receive success and successful proxies are not retired. Location/report: `Source/InterceptionLogger/Impl/Listeners/UserListener.cxx:27–30` and its sidecar. Global game listeners passed directly to Register are a distinct route.
- **BASE-INTERCEPT-005 | High | Memory Safety | High confidence:** Packet/details tracing treats full object-size outputs as readable destination extents, ignoring destination capacity on documented truncation paths. Locations/reports: `Source/InterceptionLogger/Impl/Networking.cxx:83–89,115–121`, `Source/InterceptionLogger/Impl/Stats.cxx:525–550` and their sidecars. Real DLL output-size behavior was not executed; the SDK contracts permit truncation and distinguish buffer capacity from object size.
- **BASE-INTERCEPT-006 | High | API/ABI | High confidence:** Callback forwarding is gated by operation-listener availability instead of callback result-type transitions. Location/report: `Source/InterceptionLogger/Impl/Listeners/MatchmakingListener.cxx:25–47,74–97` and its sidecar. Specific list callbacks disappear during 1.125.x–pre-1.129.0; leave callbacks during 1.125.x–pre-1.133.0.
- **BASE-INTERCEPT-007 | High | API/ABI | High confidence:** Initialization requires exports absent from older factory/game-server SDK surfaces. Location/report: `Source/InterceptionLogger/UniverseLANInterceptor.cxx:133–140,263–264,283–284` and its sidecar. Early GetInstance/Reset factories and later game-server Utils/Telemetry boundaries are grouped as one resolver-versioning root cause.
- **BASE-INTERCEPT-008 | Medium | Correctness | High confidence:** Client Init swallows exceptions, reports no wrapper error when none was installed and leaves empty callables that fail during required cleanup. Location/report: `Source/InterceptionLogger/GalaxyDLL.cxx:37–59,72–77,164–180` and its sidecar. Missing-DLL/export and early construction failure paths were traced statically.
- **BASE-INTERCEPT-009 | Medium | API/ABI | High confidence:** Newer factory GetInstance erroneously creates an instance; SDK inline null-state guards for Shutdown/ProcessData are defeated and empty callbacks throw. Location/report: `Source/InterceptionLogger/GalaxyApiFactory.cxx:178–185` and its sidecar. Old 1.57.0 create-on-query semantics must be preserved separately.
- **BASE-INTERCEPT-010 | Medium | API/ABI | High confidence:** Exported ShutdownGameServerEx drops preserveStaticObjects by calling ordinary shutdown. Location/report: `Source/InterceptionLogger/GalaxyGameServerApi.cxx:24–28` and its sidecar. The class's correct extended-shutdown forwarder exists but is bypassed.
- **BASE-INTERCEPT-011 | Medium | Security | High confidence:** Token/key/code inputs and results are persisted verbatim by enabled call tracing. Location/report: `Source/InterceptionLogger/Impl/User.cxx:205–206,244–245,703–727,760–782,793–795,835–856` and its sidecar. Actual disclosure requires access to diagnostic artifacts; no credentials, unauthorized reader or compromise were observed.

Category counts: Memory Safety 2; Concurrency 1; Correctness 2; API/ABI 5; Security 1. Total 11. Severity counts are per unique ID, not per report section.

## Exact reviewed input inventory

Every path below was read in full and has a new adjacent `.review.MD` sidecar. The list is the 73-input inventory, not a sample. README.MD is not an assigned extension and is not counted.

1. `Source/InterceptionLogger/CMakeLists.txt`
2. `Source/InterceptionLogger/GalaxyApi.cxx`
3. `Source/InterceptionLogger/GalaxyApiFactory.cxx`
4. `Source/InterceptionLogger/GalaxyDLL.cxx`
5. `Source/InterceptionLogger/GalaxyDLL.hxx`
6. `Source/InterceptionLogger/GalaxyFunctional.hxx`
7. `Source/InterceptionLogger/GalaxyGameServerApi.cxx`
8. `Source/InterceptionLogger/IGalaxyFix.cxx`
9. `Source/InterceptionLogger/Impl/Apps.cxx`
10. `Source/InterceptionLogger/Impl/Apps.hxx`
11. `Source/InterceptionLogger/Impl/Chat.cxx`
12. `Source/InterceptionLogger/Impl/Chat.hxx`
13. `Source/InterceptionLogger/Impl/CloudStorage.cxx`
14. `Source/InterceptionLogger/Impl/CloudStorage.hxx`
15. `Source/InterceptionLogger/Impl/CustomNetworking.cxx`
16. `Source/InterceptionLogger/Impl/CustomNetworking.hxx`
17. `Source/InterceptionLogger/Impl/Errors.cxx`
18. `Source/InterceptionLogger/Impl/Errors.hxx`
19. `Source/InterceptionLogger/Impl/Friends.cxx`
20. `Source/InterceptionLogger/Impl/Friends.hxx`
21. `Source/InterceptionLogger/Impl/InitOptionsFactory.hxx`
22. `Source/InterceptionLogger/Impl/InitOptionsModern.cxx`
23. `Source/InterceptionLogger/Impl/InitOptionsModern.hxx`
24. `Source/InterceptionLogger/Impl/ListenerRegistrar.cxx`
25. `Source/InterceptionLogger/Impl/ListenerRegistrar.hxx`
26. `Source/InterceptionLogger/Impl/Listeners/AppsListener.cxx`
27. `Source/InterceptionLogger/Impl/Listeners/AppsListener.hxx`
28. `Source/InterceptionLogger/Impl/Listeners/ChatListener.cxx`
29. `Source/InterceptionLogger/Impl/Listeners/ChatListener.hxx`
30. `Source/InterceptionLogger/Impl/Listeners/CloudStorageListener.cxx`
31. `Source/InterceptionLogger/Impl/Listeners/CloudStorageListener.hxx`
32. `Source/InterceptionLogger/Impl/Listeners/CustomNetworkingListener.cxx`
33. `Source/InterceptionLogger/Impl/Listeners/CustomNetworkingListener.hxx`
34. `Source/InterceptionLogger/Impl/Listeners/FriendsListener.cxx`
35. `Source/InterceptionLogger/Impl/Listeners/FriendsListener.hxx`
36. `Source/InterceptionLogger/Impl/Listeners/MatchmakingListener.cxx`
37. `Source/InterceptionLogger/Impl/Listeners/MatchmakingListener.hxx`
38. `Source/InterceptionLogger/Impl/Listeners/NetworkingListener.cxx`
39. `Source/InterceptionLogger/Impl/Listeners/NetworkingListener.hxx`
40. `Source/InterceptionLogger/Impl/Listeners/ProxifySingleShotListener.cxx`
41. `Source/InterceptionLogger/Impl/Listeners/ProxifySingleShotListener.hxx`
42. `Source/InterceptionLogger/Impl/Listeners/StatsListener.cxx`
43. `Source/InterceptionLogger/Impl/Listeners/StatsListener.hxx`
44. `Source/InterceptionLogger/Impl/Listeners/StorageListener.cxx`
45. `Source/InterceptionLogger/Impl/Listeners/StorageListener.hxx`
46. `Source/InterceptionLogger/Impl/Listeners/TelemetryListener.cxx`
47. `Source/InterceptionLogger/Impl/Listeners/TelemetryListener.hxx`
48. `Source/InterceptionLogger/Impl/Listeners/UserListener.cxx`
49. `Source/InterceptionLogger/Impl/Listeners/UserListener.hxx`
50. `Source/InterceptionLogger/Impl/Listeners/UtilsListener.cxx`
51. `Source/InterceptionLogger/Impl/Listeners/UtilsListener.hxx`
52. `Source/InterceptionLogger/Impl/Logger.cxx`
53. `Source/InterceptionLogger/Impl/Logger.hxx`
54. `Source/InterceptionLogger/Impl/Matchmaking.cxx`
55. `Source/InterceptionLogger/Impl/Matchmaking.hxx`
56. `Source/InterceptionLogger/Impl/Networking.cxx`
57. `Source/InterceptionLogger/Impl/Networking.hxx`
58. `Source/InterceptionLogger/Impl/Stats.cxx`
59. `Source/InterceptionLogger/Impl/Stats.hxx`
60. `Source/InterceptionLogger/Impl/Storage.cxx`
61. `Source/InterceptionLogger/Impl/Storage.hxx`
62. `Source/InterceptionLogger/Impl/Telemetry.cxx`
63. `Source/InterceptionLogger/Impl/Telemetry.hxx`
64. `Source/InterceptionLogger/Impl/User.cxx`
65. `Source/InterceptionLogger/Impl/User.hxx`
66. `Source/InterceptionLogger/Impl/Utils.cxx`
67. `Source/InterceptionLogger/Impl/Utils.hxx`
68. `Source/InterceptionLogger/ListenersContainer.cxx`
69. `Source/InterceptionLogger/ListenersContainer.hxx`
70. `Source/InterceptionLogger/UniverseGameServer.cxx`
71. `Source/InterceptionLogger/UniverseGameServer.hxx`
72. `Source/InterceptionLogger/UniverseLANInterceptor.cxx`
73. `Source/InterceptionLogger/UniverseLANInterceptor.hxx`

## Contract/dependency cross-checks

These are context dependencies, not extra first-party coverage claims:

- Fully read `Source/galaxy_sdk_features.cmake`, `Source/Shared/GalaxyVersionedTypes.hxx`, `Source/Shared_NoVer/SharedLibUtils.cxx/.hxx`, `Source/Shared_NoVer/SafeStringCopy.hxx`, `Source/Tracer/Tracer.hxx`; inspected Trace.cxx's flag/output sink region.
- SDK 1.152.11: fully read IListenerRegistrar.h, INetworking.h, IApps.h, ShutdownOptions.h and GalaxyGameServerApi.h. Read relevant GalaxyApi.h error/listener/thread/lifecycle sections, IUser.h auth/refresh-token contracts and IStats.h details/truncation sections.
- SDK 1.57.0: read GalaxyFactory.h/GalaxyExport.h and inline lifecycle callers from GalaxyApi.h; read 1.57.0 and 1.61.0 x64 export manifests. The old factory surface does not match unconditional CreateInstance/ResetInstance lookup.
- SDK 1.67.0: read GalaxyFactory.h and inline Init/Shutdown/ProcessData/getter paths in GalaxyApi.h to establish null-query factory semantics and error/reset behavior.
- SDK 1.114.9: fully read IGalaxy.h for legacy InitOptions and virtual interface context.
- SDK 1.125.2: read IMatchmaking.h callback declarations, fully read GalaxyGameServerApi.h and x64 export manifest. SDK 1.132.1: inspected actual OnLobbyList/OnLobbyLeft declarations. These distinguish listener-argument introduction from callback enum changes.
- SDK 1.134.8: fully read GalaxyGameServerApi.h and x64 export manifest to establish absence of game-server telemetry despite general telemetry support.
- No vendor implementation source or old review report was used as proof. Export manifests are repository ABI evidence; matching real binaries were not loaded or disassembled.

## Actual execution and reconciliation

Working directory for all terminal commands: `C:\Development\AI\UL`.

1. `git diff b30e83872c0006e8240c8b4f565da5351bf10080 -- Source/InterceptionLogger` — no output; assigned implementation/build inputs match baseline.
2. `git ls-files Source/InterceptionLogger` — established the tracked input inventory (README excluded by extension).
3. `git ls-files Source/InterceptionLogger | Where-Object { $_ -match '\.(cxx|hxx|cmake|txt)$' } | Group-Object { [System.IO.Path]::GetExtension($_) } | Format-Table Name,Count` — returned `.txt 1`, `.cxx 37`, `.hxx 35`.
4. Dedicated Read/Glob/Grep tools — all 73 complete input reads, targeted SDK/context reads, and sidecar existence reconciliation. Before writing, no InterceptionLogger sidecars or INTERCEPT.MD existed in the working tree.
5. `git diff --exit-code b30e83872c0006e8240c8b4f565da5351bf10080 -- Source/InterceptionLogger` after report creation — exit 0/no output; no tracked production changes.
6. `git --no-optional-locks status --short -- Source/InterceptionLogger .ai/review-baseline/INTERCEPT.MD` — showed prior staged removal of superseded sidecars plus the newly created untracked replacements. This pass did not alter the index or inspect superseded report contents.
7. PowerShell reconciliation using `git ls-files`, `rg --files-with-matches` on fresh baseline markers, extraction of numbered notebook paths, and two `Compare-Object` comparisons — **TrackedInputs 73, NotebookPaths 73, FreshSidecars 73; both comparisons empty**. This checked exact path sets, not only matching counts.
8. Dedicated Grep found **17 full local finding sections representing 11 unique IDs**. A simple `rg --no-ignore --count` query against the notebook returned **11** for the unique index. An earlier stricter shell-pattern query returned no matches; the dedicated search and simple count supplied the reconciliation evidence.

No build/test/analyzer result is claimed. All verification sections describe work to execute after remediation, not experiments performed in this pass.

## Limits, unresolved questions and below-threshold observations

- Complete file reading is not exhaustive runtime coverage. No real SDK dispatch, callback exception/reentrancy experiment, race stress test, sanitizer, ABI/vtable comparison or version build matrix ran, as requested.
- The proxy race and cross-session failure have concrete static sequences. Nested callbacks on the same proxy and game callbacks throwing through the SDK need additional contract/runtime evidence before separate findings; the current protection set is not a nesting count and cleanup is manual.
- ListenersContainer erases allocations without deleting them: a small per-session leak was recorded in its sidecars, below the serious-only finding threshold. Pending proxies with no terminal callback and process-exit ordering also need broader lifecycle validation.
- IGalaxyFix locally redeclares classes differently from SDK definitions. ODR/export/vtable risks are noted, but a concrete bad live virtual-dispatch path was not established. Early-vs-modern InitOptions forwarding, missing factory error-manager/reset integration and platform-specific interface additions also need deeper compatibility work.
- Void/failed output calls can leave scalars or buffer tails without a valid produced value. Several trace paths inspect them anyway; small/binary notification/message outputs need targeted error/extent tests. Only the independently supported packet/details capacity-overread root cause is a High finding here.
- Apps' forced ownership callback is synchronous, and its listener/returned-language null contracts need targeted validation. The SDK does not mark that particular listener optional, so a null-listener crash was not claimed merely from other APIs' defaults.
- Logger formatting-error lengths and stream-state checks outside its writer mutex deserve stress/failure tests; no separate severe ordinary-input failure was established at this depth.
- Security assessment is limited to traced authentication material and memory disclosure mechanisms. No credential file, credential environment variable value, account or service was accessed; no exploit or compromised account is claimed.
- Performance/CI/build assessment was shallow: observed recurring trace formatting/I/O and the local CMake target/feature dependency; no benchmarks or CI checks were executed. Windows loader assumptions do not establish Linux support.

## Recommended remediation and validation order

1. **Ownership/lifecycle:** Fix 002 and 003 together with owner-aware pinned proxy records; preserve same-thread self-unregister. Add pre-shutdown detachment for 001, including partial initialization and per-session cleanup.
2. **Reliable dispatch/startup:** Restore auth success forwarding (004), correct callback enum guards (006), and gate required exports by exact SDK availability (007). Make failed-init/error state explicit (008) and fix newer factory null-query semantics (009).
3. **Trace/option transparency:** Bound output inspection by verified readable extents (005), forward ShutdownGameServerEx options (010), and redact authentication material in every trace sink (011).
4. **Focused Windows verification:** Use credential-free fake SDKs and barrier-controlled callbacks for ownership; guard-page/ASan truncated buffers for tracing; x86/x64 SDK boundary builds/export tests and real-DLL lifecycle smoke tests when permitted. Only then broaden to deeper ABI/legacy-option and diagnostic failure-path review.
