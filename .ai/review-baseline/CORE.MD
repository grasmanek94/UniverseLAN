# CORE — fresh full baseline review

## Executive summary

Baseline: **`b30e83872c0006e8240c8b4f565da5351bf10080`**. Windows/MSVC and the Galaxy DLL replacement contract are the focus.

**Completed: 30/30 owned implementation/build files read in full, with 30 new sibling `<file>.review.MD` reports. Remaining owned paths: none.** This notebook is the 31st CORE review artifact. Findings were derived from the current implementation and SDK/caller evidence; superseded review findings were not consulted or copied.

**10 unique confirmed findings: 3 High, 5 Medium, 2 Low; all High confidence from static evidence.** “Confirmed” means the failure mechanism is established in source, not runtime-reproduced. Categories: Memory Safety 3; Correctness 4; API/ABI 2; Concurrency 1. No Critical finding is claimed.

The strongest issues are callback lifetime failures: queued specific callbacks survive unregistration, global snapshots outlive unregister/delete operations, and callback-time shutdown destroys the active pump. Fix these before treating callback-driven lifecycle behavior as dependable. Next address the initialization error boundary and game-server role selection. The implementation has useful explicit reset ordering, atomic worker termination, version-specific interface compilation, and owned callback-string payloads, but these do not provide an invocation-lifetime protocol.

This review does **not** establish overall release readiness or binary compatibility of every SDK version. No build, runtime test, sanitizer, analyzer, benchmark, DLL loading, or packet exchange was performed.

## Exact owned-file coverage

Each row was read from line 1 through the stated final line. Every source path has a newly created report at that **exact path plus `.review.MD`**. Cross-file defects use one unique ID, even when a directly affected sidecar contains its own full local defect section. A no-finding report is a scoped observation, not proof of correctness.

### Source/Client root — 14 files

| Reviewed path | Full line range |
| --- | --- |
| `Source/Client/Client.cxx` | 1–83 |
| `Source/Client/Client.hxx` | 1–41 |
| `Source/Client/ClientNetworkHandlers.cxx` | 1–281 |
| `Source/Client/CMakeLists.txt` | 1–25 |
| `Source/Client/Factory.cxx` | 1–259 |
| `Source/Client/GalaxyApi.cxx` | 1–130 |
| `Source/Client/GalaxyApiFactory.cxx` | 1–212 |
| `Source/Client/GalaxyDLL.cxx` | 1–190 |
| `Source/Client/GalaxyDLL.hxx` | 1–50 |
| `Source/Client/GalaxyGameServerApi.cxx` | 1–65 |
| `Source/Client/UniverseGameServer.cxx` | 1–123 |
| `Source/Client/UniverseGameServer.hxx` | 1–37 |
| `Source/Client/UniverseLAN.cxx` | 1–135 |
| `Source/Client/UniverseLAN.hxx` | 1–137 |

### Assigned Source/Client/Impl — 11 files

| Reviewed path | Full line range |
| --- | --- |
| `Source/Client/Impl/Errors.cxx` | 1–36 |
| `Source/Client/Impl/Errors.hxx` | 1–107 |
| `Source/Client/Impl/GalaxyThread.cxx` | 1–89 |
| `Source/Client/Impl/GalaxyThread.hxx` | 1–75 |
| `Source/Client/Impl/InitOptionsFactory.hxx` | 1–49 |
| `Source/Client/Impl/InitOptionsModern.cxx` | 1–65 |
| `Source/Client/Impl/InitOptionsModern.hxx` | 1–62 |
| `Source/Client/Impl/ListenerRegistrar.cxx` | 1–239 |
| `Source/Client/Impl/ListenerRegistrar.hxx` | 1–418 |
| `Source/Client/Impl/Logger.cxx` | 1–119 |
| `Source/Client/Impl/Logger.hxx` | 1–95 |

### All Source/Client_NoVer — 5 files

| Reviewed path | Full line range |
| --- | --- |
| `Source/Client_NoVer/CMakeLists.txt` | 1–13 |
| `Source/Client_NoVer/Impl/DelayRunner.cxx` | 1–17 |
| `Source/Client_NoVer/Impl/DelayRunner.hxx` | 1–29 |
| `Source/Client_NoVer/Impl/NotificationParamScopeExtender.cxx` | 1–34 |
| `Source/Client_NoVer/Impl/NotificationParamScopeExtender.hxx` | 1–72 |

The Git inventory and filesystem inventory reconcile to **14 + 11 + 5 = 30**. No additional owned `.cmake` or `.txt` input exists under Client_NoVer beyond the listed CMakeLists.txt. Other reviewers' sidecar filenames appeared during final inventory; their contents were not used, edited, or counted as CORE coverage.

## Confirmed finding index

Canonical reports below contain evidence, failure mechanism, impact, possible solutions, recommendation, verification proposal, severity, confidence, category, and source location.

| ID | Severity / confidence | Category | Important evidence and canonical report |
| --- | --- | --- | --- |
| BASE-CORE-001 | High / High | Memory Safety | `NotifyAll` binds a specific raw listener; `Unregister` cannot cancel that queued pointer. A self-user information request followed by unregister/delete and a pump dereferences freed memory. [ListenerRegistrar.hxx](../../Source/Client/Impl/ListenerRegistrar.hxx.review.MD), lines 231–269, 309–331. |
| BASE-CORE-002 | High / High | Memory Safety | Global dispatch copies raw pointers, unlocks, and invokes the snapshot. Callback A can unregister/delete later callback B without removing it from that snapshot. [ListenerRegistrar.cxx](../../Source/Client/Impl/ListenerRegistrar.cxx.review.MD), lines 88–117, 137–147, 169–237. |
| BASE-CORE-003 | High / High | Memory Safety | Callback-time reset deletes the active Client/DelayRunner; dispatch then resumes on destroyed member queues. [UniverseLAN.cxx](../../Source/Client/UniverseLAN.cxx.review.MD), lines 91–134; also a full local section in [DelayRunner.cxx](../../Source/Client_NoVer/Impl/DelayRunner.cxx.review.MD), lines 7–11. |
| BASE-CORE-004 | Medium / High | Correctness | Game-server init omits `is_gameserver=true`. From 1.135.0 the returned networking instance is Client-role, and direct member replies carry user identity rather than the intended lobby identity. [UniverseGameServer.cxx](../../Source/Client/UniverseGameServer.cxx.review.MD), lines 25–28, 74–80. |
| BASE-CORE-005 | Medium / High | API/ABI | DNS/ENet init failure escapes as `std::runtime_error`; GetError always returns null and legacy exception flags are lost. [GalaxyDLL.cxx](../../Source/Client/GalaxyDLL.cxx.review.MD), lines 35–47, 183–185. Full local manifestations also appear in GalaxyApiFactory.cxx, InitOptionsModern.cxx, and UniverseGameServer.cxx sidecars. |
| BASE-CORE-006 | Medium / High | Correctness | Init captures `std::cout` before work and releases only on success; failed init retains output in a string buffer even after shutdown. [GalaxyDLL.cxx](../../Source/Client/GalaxyDLL.cxx.review.MD), lines 24, 35–47, 60. |
| BASE-CORE-007 | Low / High | API/ABI | GetInstance allocates even in later factory SDKs that require a null result before CreateInstance. Verified contract difference between 1.57.0 and 1.64.0/1.114.9. [GalaxyApiFactory.cxx](../../Source/Client/GalaxyApiFactory.cxx.review.MD), lines 166–174. |
| BASE-CORE-008 | Medium / High | Correctness | Wrapper destructor detaches unconditionally after Join/Detach, throwing through a nonthrowing destructor and terminating. **No current production caller found; dormant wrapper, not ordinary Client teardown.** [GalaxyThread.cxx](../../Source/Client/Impl/GalaxyThread.cxx.review.MD), lines 25–58. |
| BASE-CORE-009 | Low / High | Correctness | Logger writes `iLen+1` bytes as a string, including the terminator on every record. [Logger.cxx](../../Source/Client/Impl/Logger.cxx.review.MD), lines 69–79. |
| BASE-CORE-010 | Medium / High | Concurrency | Unlocked stream-state read can race with a failed insertion setting stream state under the mutex. Requires concurrent callers plus an I/O failure. [Logger.cxx](../../Source/Client/Impl/Logger.cxx.review.MD), lines 62–79. |

## Architecture and lifecycle observations

1. **ABI adapters and version selection.** Old SDKs use GalaxyFactory/IGalaxy; newer SDKs use exported free functions. They converge on internal entry points and an InterfaceInstances graph. CMake selects versioned SDK headers and capability macros, preserving source-level interface signatures. Internal InitOptions normalization avoids reinterpreting public structs. Actual decorated names, ordinals, vtable layouts, x86 stack behavior, and cross-CRT exception behavior remain untested.
2. **Ownership graph.** Client and game server own distinct InterfaceInstances graphs. Most implementation objects borrow the graph and registrar. Explicit reset stops ENet first, destroys custom-networking channels while the registrar/queue still exist, then removes callbacks and helpers. The implicit member-destruction order differs, and repeated/concurrent initialization is not protected by a state machine.
3. **Execution model.** The ENet worker services transport and pushes queued events. The application pump processes network events and then drains delayed callbacks. Custom WebSocket workers also enqueue callbacks. Concurrent queues protect queue operations, not callback pointees, graph lifetime, pump serialization, or the registration-to-invocation transition.
4. **String lifetime is stronger than listener lifetime.** The scope extender owns copied `const char*` payloads and preserves null versus empty. Raw listener pointers remain borrowed. Cancellation must invalidate stable registration records and coordinate in-flight invocations; merely owning the callable does not own its targets.
5. **Shutdown needs dispatch awareness.** Null checks before a pump do not keep objects alive inside it. A lifecycle guard must cover both queues and all interface/registrar users; defer graph destruction on same-thread shutdown rather than waiting on the active callback.
6. **Stored options versus implemented hooks.** Allocator/thread-factory/bind options are copied, but inspected Client startup uses ordinary allocations, std::thread, and project configuration. No current call into the supplied thread factory was found. These are integration gaps, not a proven allocator mismatch or a quantified compatibility failure. ShutdownEx's static-preservation details also remain unresolved.
7. **Shared process facilities.** The two runtimes still share tracing/console facilities and configuration mechanisms. Separate graph ownership alone does not prove simultaneous client/game-server isolation. Configuration identity and implicit DLL unload are follow-up scenarios.
8. **Build boundaries.** A versioned static client links versioned shared/SDK dependencies and common no-version helpers. The no-version sources contain no SDK layouts. Root CMake supplies C++20. Factory.cxx's unity exclusion addresses its interaction with old SDK header-local wrappers. Broad source globs include documentation but no actual build defect was established here.

## Dependency and contract tracing actually performed

These are **context**, not additional first-party coverage claims:

- Full reads of `Source/Shared/Networking/Networking.{cxx,hxx}` and `Source/Vendor/Enet++/src/enetpp.cxx` for connect failure, worker queues, event dispatch, packet cleanup, and disconnect/destruction.
- Full reads of `Source/Client/Impl/Networking.cxx`, `Apps.cxx`, and `CustomNetworking.cxx`; focused portions of `Friends.cxx` (1–140) and `User.cxx` (1–120). These established concrete notification producers and packet-role effects; the rest of those subsystems belongs to other assignments.
- `Source/Server/ServerHandlers.cxx:290–459` for server/peer packet identity and routing.
- Full reads of `Source/Shared_NoVer/ConcurrentQueue.hxx` and `ConsoleCoutRedirector.{cxx,hxx}` for Windows queue choice and output-capture lifetime.
- SDK 1.57.0 IGalaxy/GalaxyFactory; 1.64.0 GalaxyFactory; 1.114.9 GalaxyFactory/GalaxyExport, IGalaxy initialization declarations, and GalaxyApi wrapper section; 1.152.11 GalaxyApi, GalaxyGameServerApi, InitOptions, ShutdownOptions, IListenerRegistrar, GalaxyThread, GalaxyAllocator, ILogger, Errors, GalaxyExport, and GalaxyExceptionHelper.
- Root and Source CMake, `Source/Shared/CMakeLists.txt`, DLL CMake/version-feature includes, `Source/galaxy_sdk_features.cmake`, and `Source/Vendor/galaxy.cmake` for target linkage, feature boundaries, SDK export definitions, and C++20.
- `Source/SystemTests/Host/Apps.cxx` read in full plus targeted SystemTests symbol searches. The inspected DLC test covers global/specific successful delivery but does not exercise unregister-before-pump. This was not a full audit of the test suite or a proof that no other relevant test exists.

No production configuration values, credential files, private keys, binaries, or game-test-result logs were read. No unsupported service behavior or intentional LAN trust setting was classified as an exploitable defect.

## Actual verification and execution limits

Executed read-only terminal commands from `C:\Development\AI\UL`:

```powershell
git --no-optional-locks ls-files -- Source/Client Source/Client_NoVer
git --no-optional-locks diff b30e83872c0006e8240c8b4f565da5351bf10080 -- Source/Client Source/Client_NoVer ':(exclude)*.review.MD'
```

- The inventory command succeeded and supplied the tracked-file list used for ownership reconciliation.
- The baseline diff was executed before report creation and again after all source-side reports existed; both produced **no output**. Thus the tracked Client/Client_NoVer implementation inputs inspected match the requested baseline, including current working-tree changes.
- Dedicated Read/Glob/Grep tools were used for complete owned-file reads, caller/contract tracing, and final report-path reconciliation. Report additions/updates used only `apply_patch`. Some speculative path lookups returned “not found”; those paths were not credited as inspected.
- All 30 owned sidecars were found in the final filesystem inventory. This notebook records all remaining-path status explicitly: **none**.
- No source edit, build/configure, executable test, sanitizer, analyzer, benchmark, Git write, branch change, commit, or secret access was performed. No external web research was needed; contracts came from repository SDK headers.
- Windows runtime/compiler focus; Linux/alternative-compiler guards were considered statically only. Only the named representative SDK headers and feature definitions were traced; this is not a compiled all-version ABI matrix.

## Verification priorities and remediation sequence

1. **Callback lifetime:** cancellable registration tokens, unregister/delete during delivery, specific cancellation before a pump, address reuse, and concurrent unregister barriers. Cover both immediate-local and network completions, then Windows ASan/page-heap integration.
2. **Runtime lifecycle:** callback-time client/game-server shutdown, stop further dispatch, safe deferred teardown, reinit, partial init, concurrent API/lifecycle policy, and controlled DLL unload outside loader-lock-sensitive cleanup.
3. **SDK boundary:** synthetic DNS/ENet failures, legacy exception flags, modern thread-local GetError semantics, error reset/lifetime, and stdout restoration. Pair normalization and boundary fixes.
4. **Game-server routing:** direct member-ID and lobby-ID sends from a dedicated server; assert lobby sender identity on modern SDKs and preserve the old server-networking branch.
5. **Local fixes:** joined/detached thread-wrapper deletion, log byte output, and concurrent log writes with injected I/O failure. The dormant thread wrapper should be repaired before wiring in custom-thread support.
6. **Broader validation once authorized:** representative x86/x64 builds spanning factory, early-modern, server-networking removal, thread-factory introduction, and latest SDK; inspect symbols/vtables and run focused regressions. Build/CI, full server/parser security, and performance conclusions remain outside this CORE-only static result.
