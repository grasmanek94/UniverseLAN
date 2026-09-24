# INTERCEPT — full-file follow-up review

## Executive summary

Production baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Working HEAD inspected: `48cea8c6c48fa41fddd348a0119129cc5643fc8b`. Review date: 2026-09-24.

**All 73 assigned inputs were reread completely: 37 `.cxx`, 35 `.hxx`, one `.txt`, zero `.cmake`; zero unfinished files.** This remains the requested shallow serious-C++-defect review. Full reading includes declarations, comments and inactive feature branches; it does not imply an executed version/ABI matrix.

**Three new findings, all Medium / High confidence:** public factory error reporting is stubbed to success; legacy InitOptions loses supported fields/policy; forced DLC ownership changes asynchronous callback delivery to inline reentrancy. Four full ADD sections in responsible sidecars represent three unique IDs because the options defect has two responsible source files.

**All 11 baseline IDs retained: six High, five Medium.** Existing-ID addenda refine module/address/lifetime claims and extend error-state and output-extent evidence. Combined owner accounting is **14 unique findings: six High, eight Medium, zero Critical**. New categories: Correctness 2, API/ABI 1. Combined categories: Memory Safety 2, Concurrency 1, Correctness 4, API/ABI 6, Security 1. These are owner-local counts for coordinator reconciliation, not a new repository-wide total.

The interceptor's main risks remain its callback retirement protocol, incomplete forwarding/error fidelity and observing output beyond the produced extent. Its null-preserving encapsulation, adjusted typed listener conversions and several bounded-buffer paths are useful positives. Restore those core contracts before relying on it as transparent diagnostic instrumentation.

## Scope, method and actual execution

- Followed `.ai/SKILLS/CppReviewer.md` and `.ai/review-addendum/PLAN.MD`. Read all assigned source/header/build inputs before the deliberate comparison with `.ai/review-baseline/INTERCEPT.MD` and its responsible sidecars.
- Used dedicated Read/Glob/Grep for inspection. Initial read-only Git checks established HEAD and working status. A broad baseline diff also surfaced existing sidecar additions, so it was unsuitable as a source-only comparison; the subsequent extension-restricted diff returned no source differences.
- Source comparison executed from `C:\Development\AI\UL`:

  ```text
  git diff --name-only b30e83872c0006e8240c8b4f565da5351bf10080 -- ':(glob)Source/InterceptionLogger/**/*.cxx' ':(glob)Source/InterceptionLogger/**/*.hxx' ':(glob)Source/InterceptionLogger/**/*.cmake' ':(glob)Source/InterceptionLogger/**/*.txt'
  ```

  Result: no output. The inspected inputs match the requested baseline.
- Windows x86/x64 semantics are the focus. SDK headers/export manifests and shared loader/trace helpers were read as dependency/contract context. No native DLL load, build, test, sanitizer, ABI/layout experiment, benchmark or analyzer execution was performed. Verification sections are proposals only.
- Edits use apply_patch and are confined to this owner notebook and eight existing InterceptionLogger sidecars. No production-file changes, Git staging/commits/branch changes, credential files or credential environment values were involved. Other owners' artifacts were not edited.

## Architecture and ownership assessment

1. **Adapters and per-session state.** Modern exports forward to one static client InterfaceInstances. Factory SDKs expose a GalaxyFactory/GalaxyImpl shim over that same client owner. Game-server exports own a distinct UniverseGameServer/InterfaceInstances. Separate factory objects are not evidence of independently supported native peers: the SDK factory is explicitly a singleton (`1.67.0/galaxy/GalaxyFactory.h:23–25`).
2. **Actual Windows modules.** `Shared_NoVer/SharedLibUtils.cxx:90–139` inventories and LoadLibraryA-loads the prefix-selected `RealGalaxy[64].dll` once per linked singleton and FreeLibrary-releases its handle at singleton destruction. `Shared_NoVer`, common-shared and the interception library are STATIC targets linked into the final interceptor DLL (`Source/DLLs/CMakeLists.txt:153–163`). There is no separately demonstrated helper DLL/process-global registry shared by all independently loaded interceptor versions. Windows may share the same native HMODULE when names/paths resolve to the same image; that does not merge the interceptors' C++ state. No particular native registrar/vtable module or vendor-internal peer-library lifetime was guessed.
3. **Forwarding and observation.** Impl wrappers retain real getter callables and a borrowed real registrar, then register hidden null-target observers. Most APIs forward arguments unchanged. Changing the call sequence still matters: internal Register calls can overwrite the native last-error state after Init, and the legacy factory's public inline GetError takes a different route from GalaxyImpl::GetError.
4. **Specific callbacks and cancellation.** Encapsulation allocates a distinct proxy per non-null supplied operation listener. One map per interceptor module records proxy to adjusted IGalaxyListener subobject; a separately locked set temporarily blocks cancellation deletion while calling the target. Missing ownership pins cause BASE-002. Missing session/registrar identity causes BASE-003 even with serialized calls. A valid multi-interface game listener normally has different adjusted base addresses, so it does not establish a cross-type collision by itself.
5. **Teardown and partial state.** Native Shutdown precedes hidden observer unregistration. BASE-001 remains Medium for the documented ordering violation; native object destruction is conditional. Reset clears stored std::functions and wrappers but has no session-owned proxy drain. Cancellation, completion and shutdown need one coherent ownership protocol, including partial initialization. Unexpected callback throws and same-proxy recursive delivery require SDK behavior evidence before claiming further crashes.
6. **Feature selection.** The feature builder implements inclusive ranges and unions repeated feature names: an enabled earlier interval is not disabled by a later nonmatching interval. That supports the disjoint telemetry/listener ranges. Local consumers still choose some wrong features (BASE-006/007); the impossible `HAS_IGALAXY && HAS_INITOPTIONS_MODERN` intersection also explains ADD-002. Inactive RED/game-service-platform branches have no corresponding supported SDK directory in the inspected inventory and were not turned into runtime findings.

## New finding index

Full sections include severity, confidence, category, locations, scope, evidence, mechanism, impact, possible solutions, recommended resolution and proposed verification.

- **ADD-INTERCEPT-001 | Medium | Correctness | High confidence:** Factory `ErrorManager::GetLastError()` always returns null. SDK inline public GetError calls that stub, so ordinary synchronous errors disappear even after successful initialization. Source: `Source/InterceptionLogger/GalaxyApiFactory.cxx:155–169,188–197`. Full report: `Source/InterceptionLogger/GalaxyApiFactory.cxx.review.MD`. Distinct from failed-init BASE-008 and factory-query BASE-009.
- **ADD-INTERCEPT-002 | Medium | API/ABI | High confidence:** Legacy options-taking Init is reduced to string Init/InitLocal, omitting configFilePath and normally peer selection; the conversion also drops the requested throwExceptions value. The guarded modern-options factory branch is unreachable for supported features. Sources: `Source/InterceptionLogger/UniverseLANInterceptor.cxx:145–166`, `Impl/InitOptionsModern.cxx:10–33,148–176`. Full reports: both corresponding `.review.MD` files. Same unique ID for both sites.
- **ADD-INTERCEPT-003 | Medium | Correctness | High confidence:** Enabled forced-DLC checks directly call a valid listener during IsDlcOwned submission, although the SDK documents an asynchronous response delivered during ProcessData. This can consume completion before pending state is installed and leave the caller waiting permanently. Source: `Source/InterceptionLogger/Impl/Apps.cxx:121–136`. Full report: `Source/InterceptionLogger/Impl/Apps.cxx.review.MD`. No null-listener or unspecified game-crash claim.

## Status of every baseline ID

| Baseline ID | Status / rating | Fresh comparison and disposition |
| --- | --- | --- |
| BASE-INTERCEPT-001 | Retained; Medium | Real shutdown still precedes hidden Unregister. Native lifetime-dependent High impact stays conditional. Addendum in `GalaxyDLL.cxx.review.MD` follows the actual LoadLibrary/FreeLibrary owner and distinguishes native object lifetime from HMODULE lifetime. The already reconciled Medium rating is not a new downgrade. |
| BASE-INTERCEPT-002 | Retained; High | Callback return can delete a proxy already extracted by cancellation. Addendum in `Impl/Listeners/ProxifySingleShotListener.hxx.review.MD` preserves the concrete interleaving and distinguishes normal self-unregister from unverified same-proxy recursion/escaping throws. |
| BASE-INTERCEPT-003 | Retained; High; scope clarified | Same typed listener in client/server still loses the other session's proxy. Addendum in `Impl/ListenerRegistrar.cxx.review.MD` narrows "process-wide" to sessions sharing one interceptor module and records correct multiple-inheritance base adjustment. No new cross-type ID. |
| BASE-INTERCEPT-004 | Retained; High | Auth success remains trace-only while UserImpl submits AuthListener proxies. SDK IUser success/optional-listener contract rechecked. Global game listeners bypass this proxy route; OnAuthLost is not evidence of a second promised specific completion. |
| BASE-INTERCEPT-005 | Retained; High; evidence extended | Packet/detail tracing still ignores destination capacity on documented truncation paths. `Impl/Utils.cxx.review.MD` adds successful binary-notification tail logging under the same ID: Medium bounded-disclosure instance, not another High allocation overread. Native packet/detail reported-size behavior remains unexecuted. |
| BASE-INTERCEPT-006 | Retained; High | 1.125.2 still declares bool list/leave callbacks; 1.132.1 declares enum list but bool leave. The source gates forwarding with operation-listener availability instead of those transitions. Existing sidecar remedy remains appropriate. |
| BASE-INTERCEPT-007 | Retained; High | Early factory headers/manifests and older game-server headers/manifests still contradict required resolver symbols. Disjoint feature ranges were checked as unions, not treated as last-assignment wins. Missing resolver matches throw; there is no demonstrated null native entry-point result. |
| BASE-INTERCEPT-008 | Retained; Medium; evidence extended | Swallowed client Init exceptions and empty std::function cleanup remain. Full addendum in `UniverseLANInterceptor.cxx.review.MD` also traces non-throwing partial-init error loss through later successful Register calls. Factory runtime GetError's independent stub is ADD-001. |
| BASE-INTERCEPT-009 | Retained; Medium | 1.67.0/1.114.9 SDK inline null guards for pre-init/repeated Shutdown and ProcessData are defeated by create-on-query GetInstance. The oldest 1.57.0 factory explicitly has create-on-query semantics and must remain separately gated. |
| BASE-INTERCEPT-010 | Retained; Medium | Exported ShutdownGameServerEx still calls ordinary shutdown. SDK ShutdownOptions::preserveStaticObjects and the correct unused class forwarder were reread; options are dropped, not merely logged incorrectly. |
| BASE-INTERCEPT-011 | Retained; Medium | Source still formats authentication token/key/code contents; Trace writes them to file/optional console sinks. Synthetic-data-only validation remains appropriate. No credential content or actual unauthorized log reader was inspected. |

No baseline ID was removed, silently rewritten, duplicated as an ADD ID, or re-rated in this pass. Prior uncounted observations promoted to ADD-001/002/003 remain visible in their preserved baseline sidecars. Coordinator disposition is requested for the BASE-003 scope wording and the two existing-ID evidence extensions.

## Exact full-file coverage and fresh inspection notes

Each row records an actual complete read, not grep-only or equivalent-file sampling. Every numbered path is repository-relative. "Shared" notes refer to the already indexed baseline mechanisms and add no count.

| # | Input | Full lines read | Fresh inspection notes |
| --- | --- | --- | --- |
| 1 | `Source/InterceptionLogger/CMakeLists.txt` | 1–31 | STATIC per-version target, common-shared dependency, unity exclusion; module identity checked. |
| 2 | `Source/InterceptionLogger/GalaxyApi.cxx` | 1–133 | Modern exports, optional interface gates, const-reference Init/Shutdown forwarding and load adapter. |
| 3 | `Source/InterceptionLogger/GalaxyApiFactory.cxx` | 1–224 | All virtual forwards and factory state; public manager route proves ADD-001; BASE-009 retained. |
| 4 | `Source/InterceptionLogger/GalaxyDLL.cxx` | 1–190 | All lifecycle/getters/error/load paths; BASE-001/008 and actual HMODULE owner traced. |
| 5 | `Source/InterceptionLogger/GalaxyDLL.hxx` | 1–51 | Lifecycle const-reference types, feature declarations and getter signatures match implemented routes. |
| 6 | `Source/InterceptionLogger/GalaxyFunctional.hxx` | 1–15 | std::function signature-to-pointer extraction; no reference-erasing result storage here. |
| 7 | `Source/InterceptionLogger/GalaxyGameServerApi.cxx` | 1–66 | Separate static server owner, every export; BASE-010 drops extended options. |
| 8 | `Source/InterceptionLogger/IGalaxyFix.cxx` | 1–329 | Complete compatibility redeclarations/throwing copy paths; ODR/vtable concern lacks a proven bad live dispatch. |
| 9 | `Source/InterceptionLogger/Impl/Apps.cxx` | 1–141 | All ownership/language routes; ADD-003 scheduling; null listener/language hypotheses bounded by actual SDK contract. |
| 10 | `Source/InterceptionLogger/Impl/Apps.hxx` | 1–103 | Required ownership-listener signature and language/copy gates; no optional null default invented. |
| 11 | `Source/InterceptionLogger/Impl/Chat.cxx` | 1–217 | Room/history/send proxy types, chat output refs and callback-scoped reads; capacity-bounded text. |
| 12 | `Source/InterceptionLogger/Impl/Chat.hxx` | 1–187 | RoomID/messageType signature transitions, output refs and listener defaults matched to bodies. |
| 13 | `Source/InterceptionLogger/Impl/CloudStorage.cxx` | 1–431 | Every overload, metadata terminators, timestamps, hashes and read/write/rewind callback+userParam forwarding. |
| 14 | `Source/InterceptionLogger/Impl/CloudStorage.hxx` | 1–427 | Full metadata/savegame overload matrix and caller buffer lifetimes; callbacks remain SDK function-pointer types. |
| 15 | `Source/InterceptionLogger/Impl/CustomNetworking.cxx` | 1–141 | Open/close proxy pairing and all binary data forwards; logger does not invoke function callbacks. |
| 16 | `Source/InterceptionLogger/Impl/CustomNetworking.hxx` | 1–126 | Buffer sizes, connection IDs, listener defaults and feature gates matched. |
| 17 | `Source/InterceptionLogger/Impl/Errors.cxx` | 1–61 | Each accessor re-queries native GetError; no stable error snapshot; stale-pointer behavior needs SDK lifetime evidence. |
| 18 | `Source/InterceptionLogger/Impl/Errors.hxx` | 1–60 | Native const IError getter type, virtual methods and wrapper ownership; distinct from factory manager. |
| 19 | `Source/InterceptionLogger/Impl/Friends.cxx` | 1–833 | All social/rich-presence/invitation/user routes, flags, buffer outputs and specific-proxy argument order. |
| 20 | `Source/InterceptionLogger/Impl/Friends.hxx` | 1–619 | Complete scalar/ID types, avatar aliases and bool/void transition; no returned-reference local found. |
| 21 | `Source/InterceptionLogger/Impl/InitOptionsFactory.hxx` | 1–52 | Pre-options synthetic structure and borrowed pointer fields; used through owning modern adapter. |
| 22 | `Source/InterceptionLogger/Impl/InitOptionsModern.cxx` | 1–188 | Every setter/getter/constructor and reconstruction; ADD-002 policy and downstream overload mismatch. |
| 23 | `Source/InterceptionLogger/Impl/InitOptionsModern.hxx` | 1–98 | Owned optional strings, allocator/thread-factory pointer types and selected SDK options alias. |
| 24 | `Source/InterceptionLogger/Impl/ListenerRegistrar.cxx` | 1–54 | Raw cancellation vector, native calls and delete step; BASE-002/003; adjusted interface address counterevidence. |
| 25 | `Source/InterceptionLogger/Impl/ListenerRegistrar.hxx` | 1–68 | ListenerType/uint32 transition and unregister-all-pending contract; borrowed getter declaration. |
| 26 | `Source/InterceptionLogger/Impl/Listeners/AppsListener.cxx` | 1–45 | Success/failure forwarded values correct; misleading userID/chatRoomID labels are below serious threshold. |
| 27 | `Source/InterceptionLogger/Impl/Listeners/AppsListener.hxx` | 1–24 | Ownership callback types and encapsulation target matched; no callable null wrapper introduced. |
| 28 | `Source/InterceptionLogger/Impl/Listeners/ChatListener.cxx` | 1–110 | Every room/send/history success/failure and count/index/timestamp argument forwarded in order. |
| 29 | `Source/InterceptionLogger/Impl/Listeners/ChatListener.hxx` | 1–51 | All callback signatures, count widths and target pairings matched. |
| 30 | `Source/InterceptionLogger/Impl/Listeners/CloudStorageListener.cxx` | 1–140 | Metadata/savegame callback transitions, borrowed strings and all failure arguments forwarded. |
| 31 | `Source/InterceptionLogger/Impl/Listeners/CloudStorageListener.hxx` | 1–55 | Full four-listener family, feature-selected success signature and correct typed targets. |
| 32 | `Source/InterceptionLogger/Impl/Listeners/CustomNetworkingListener.cxx` | 1–70 | Connection string/ID, close reason and data size forwarding; common terminal macro placement. |
| 33 | `Source/InterceptionLogger/Impl/Listeners/CustomNetworkingListener.hxx` | 1–38 | All three inheritance/target pairings and callback parameter types matched. |
| 34 | `Source/InterceptionLogger/Impl/Listeners/FriendsListener.cxx` | 1–362 | Full success/failure/unsolicited callbacks, flags and userSpecifier/ID order checked. |
| 35 | `Source/InterceptionLogger/Impl/Listeners/FriendsListener.hxx` | 1–183 | Every feature-conditioned listener class/target pairing and callback declaration matched. |
| 36 | `Source/InterceptionLogger/Impl/Listeners/MatchmakingListener.cxx` | 1–225 | All const GalaxyID reference callbacks; BASE-006 bool/enum guards independently checked. |
| 37 | `Source/InterceptionLogger/Impl/Listeners/MatchmakingListener.hxx` | 1–108 | Both list/leave overloads, separate created/entered interfaces and reference signatures. |
| 38 | `Source/InterceptionLogger/Impl/Listeners/NetworkingListener.cxx` | 1–48 | Packet observer is trace-only and not registered by wrapper; NAT observer forwarding. |
| 39 | `Source/InterceptionLogger/Impl/Listeners/NetworkingListener.hxx` | 1–26 | Packet-size/channel and NAT declarations; no operation-specific packet proxy route. |
| 40 | `Source/InterceptionLogger/Impl/Listeners/ProxifySingleShotListener.cxx` | 1–92 | All map/set operations, erase iteration and separate-lock deletion protocol; cancellation overlap. |
| 41 | `Source/InterceptionLogger/Impl/Listeners/ProxifySingleShotListener.hxx` | 1–68 | Null-preserving typed conversion; shared owner omission; normal/throwing/reentrant retirement paths. |
| 42 | `Source/InterceptionLogger/Impl/Listeners/StatsListener.cxx` | 1–202 | Every stat/leaderboard/time callback; achievement-progress observer has no supplied target route. |
| 43 | `Source/InterceptionLogger/Impl/Listeners/StatsListener.hxx` | 1–85 | Scores/ranks/IDs, enum types and target pairings; old SDK time-listener type-tag question recorded below. |
| 44 | `Source/InterceptionLogger/Impl/Listeners/StorageListener.cxx` | 1–70 | Filename/shared-ID success ordering and failure values; no retained file data. |
| 45 | `Source/InterceptionLogger/Impl/Listeners/StorageListener.hxx` | 1–30 | Both shared-file listener signatures/targets under the correct storage feature. |
| 46 | `Source/InterceptionLogger/Impl/Listeners/TelemetryListener.cxx` | 1–47 | Event type/index/failure forwarding and null-annotated borrowed string logging. |
| 47 | `Source/InterceptionLogger/Impl/Listeners/TelemetryListener.hxx` | 1–21 | Telemetry target type and callback widths; session ownership absent in common infrastructure. |
| 48 | `Source/InterceptionLogger/Impl/Listeners/UserListener.cxx` | 1–159 | All auth/session/data/ticket/token/OpenID callbacks; BASE-004 success omission remains. |
| 49 | `Source/InterceptionLogger/Impl/Listeners/UserListener.hxx` | 1–98 | All callback declarations and exact listener target types; observer-only callbacks distinguished. |
| 50 | `Source/InterceptionLogger/Impl/Listeners/UtilsListener.cxx` | 1–74 | Overlay/notification/service state metadata forwarding; no payload access in callback itself. |
| 51 | `Source/InterceptionLogger/Impl/Listeners/UtilsListener.hxx` | 1–55 | Legacy notification-ID alias and feature-gated listener signatures matched. |
| 52 | `Source/InterceptionLogger/Impl/Logger.cxx` | 1–122 | All variadic severity methods, va_copy/end, allocation, stream checks/locking and destruction. |
| 53 | `Source/InterceptionLogger/Impl/Logger.hxx` | 1–96 | Variadic overrides, owned stream/mutex, borrowed config; pre-lock stream-state caveat remains. |
| 54 | `Source/InterceptionLogger/Impl/Matchmaking.cxx` | 1–782 | Every lobby/filter/data/member/message route; separate created/entered proxies; bounded successful message trace. |
| 55 | `Source/InterceptionLogger/Impl/Matchmaking.hxx` | 1–573 | Complete listener/return/pointer-type version transitions and callback-scoped data contracts. |
| 56 | `Source/InterceptionLogger/Impl/Networking.cxx` | 1–213 | All send/peek/read/availability/pop/NAT/connection paths; BASE-005 output extents; disabled packet observer intentional. |
| 57 | `Source/InterceptionLogger/Impl/Networking.hxx` | 1–215 | Capacity versus message size, sender refs, channel defaults and packet-consumption contract. |
| 58 | `Source/InterceptionLogger/Impl/Stats.cxx` | 1–748 | All stat/achievement/leaderboard/time/name/count routes; details extent and enum input-reference branches. |
| 59 | `Source/InterceptionLogger/Impl/Stats.hxx` | 1–629 | Complete interface including const enum-reference/value transition and output capacities. |
| 60 | `Source/InterceptionLogger/Impl/Storage.cxx` | 1–338 | All file/local/shared forwards and specific-listener gates; binary outputs logged as addresses/sizes. |
| 61 | `Source/InterceptionLogger/Impl/Storage.hxx` | 1–235 | Full local/shared API, offsets/counts, lifetime contracts and synchronization feature. |
| 62 | `Source/InterceptionLogger/Impl/Telemetry.cxx` | 1–194 | All scalar/object/array builders, null array names, send proxies, sampling and visit-ID paths. |
| 63 | `Source/InterceptionLogger/Impl/Telemetry.hxx` | 1–222 | Full types/defaults/feature transitions, borrowed strings and event listener contracts. |
| 64 | `Source/InterceptionLogger/Impl/User.cxx` | 1–865 | Every sign-in variant, callback gate, data/ticket/token/OpenID route; BASE-011 source-only credential tracing evidence. |
| 65 | `Source/InterceptionLogger/Impl/User.hxx` | 1–788 | Full sign-in renames, ticket constness, listener defaults, output refs and token/precondition contracts. |
| 66 | `Source/InterceptionLogger/Impl/Utils.cxx` | 1–179 | Every image/notification/overlay/service route; BASE-005 successful binary-output tail extension. |
| 67 | `Source/InterceptionLogger/Impl/Utils.hxx` | 1–175 | Output refs and aliases, notification written-length contract and feature-matched declarations. |
| 68 | `Source/InterceptionLogger/ListenersContainer.cxx` | 1–29 | Borrowed registrar, unregister order and erase loop; observer allocations remain leaked below threshold. |
| 69 | `Source/InterceptionLogger/ListenersContainer.hxx` | 1–32 | Typed registration/base conversion, raw allocation and failure ownership; no global target proxying here. |
| 70 | `Source/InterceptionLogger/UniverseGameServer.cxx` | 1–109 | Separate session, all getters/pump and both shutdown methods; correct extended method bypassed by export. |
| 71 | `Source/InterceptionLogger/UniverseGameServer.hxx` | 1–42 | Per-server owner, const-reference options and general versus server-specific feature gates. |
| 72 | `Source/InterceptionLogger/UniverseLANInterceptor.cxx` | 1–350 | Every resolver/wrapper/init/reset branch; ADD-002 and BASE-008 extension; shared-client/server construction traced. |
| 73 | `Source/InterceptionLogger/UniverseLANInterceptor.hxx` | 1–107 | All callable signatures/member lifetimes/feature owners; actual static/value-initialized instances considered. |

README.MD is outside the assigned extension set and is not counted. Dependency/context reads below add no assigned coverage.

## Contract cross-checks, counterevidence and remaining uncertainties

- **SDK error routes:** Read 1.67.0 GalaxyFactory.h/Errors.h and inline Init/Shutdown/ProcessData/GetError; 1.114.9 IGalaxy.h in full and its options/GetError inline routes. The latter establishes the legacy options bug and the separate public manager route. Modern GalaxyApi.h, IListenerRegistrar.h and GalaxyGameServerApi.h were read in full for partial initialization, error resets, thread safety, callbacks and registrar domains.
- **Signatures, references and callback parameters:** All 73 input declarations/bodies were matched manually, including bool/void branches, enum-by-value/const-reference inputs, output references, callback string/ID ordering and CloudStorage overloads. SDK contract slices and cross-version signature searches supplemented the full first-party reads. Searches with capped results were not treated as complete SDK ABI coverage. No additional confirmed dropped reference, swapped callback parameter or returned local-reference defect was established. AppsListener's wrong textual labels are a minor diagnostic issue, not another serious finding.
- **Null function callbacks:** CloudStorage forwards SDK WriteFunc, ReadFunc and RewindFunc unchanged, including userParam; it neither invokes them for logging nor synthesizes a nonempty std::function around null. SDK 1.152.11 ICloudStorage.h:265–353 was inspected. A null native callback crash cannot be assigned to this wrapper without a permitted-null contract and an interceptor-introduced invocation. Stored lifecycle std::functions can be empty after failed/reset state, which is already BASE-008/009. SharedLibUtils rejects missing functions by throwing. Apps' required listener is not made optional by other APIs' defaults; direct language getters' null-on-error behavior is not established.
- **Cancellation/completion/reentrant throw lifetime:** BASE-002's two-thread sequence remains independent of native cancellation locking because the stale-pointer window begins before the native Unregister call. Normal same-thread self-unregister is protected. A callback throw bypasses manual cleanup, but the native escaping-exception policy is unknown. Reusing a target allocates another proxy; one-shot semantics do not prove repeated/nested delivery of one proxy. These questions remain uncounted and have targeted proposed verification in the proxy addendum.
- **Multiple inheritance:** Modern SDK type-aware bases are non-virtual. Encapsulation and correctly typed Unregister preserve the interface subobject adjustment. Do not use a wrong-branch cast or most-derived void pointer as evidence of a valid caller failure. Cross-session reuse of the same subobject still proves BASE-003.
- **Version gates:** Fully read galaxy_sdk_features.cmake and GalaxyVersionedTypes.hxx. Confirmed early factory GetInstance/Reset surface using 1.57.0 factory header and 1.57.0/1.61.0 x64 manifests; rechecked 1.125.2 and 1.134.8 game-server headers/manifests and 1.125.2/1.132.1 list/leave declarations. The range helper unions repeated intervals correctly. General telemetry/Utils availability is not server-export availability. Manifests are repository evidence, not a fresh native-binary export dump.
- **Old SDK anomaly:** The 1.73.0 and 1.75.0 IStats headers tag IUserTimePlayedRetrieveListener as LEADERBOARD_RETRIEVE, while 1.76.0 uses USER_TIME_PLAYED_RETRIEVE; callback signatures themselves agree. This dependency-tag anomaly warrants native/SDK-specific validation of auto-observer registration. It is not a new first-party runtime crash finding based on a guessed dispatcher implementation.
- **Output tracing:** Fully read SafeStringCopy.hxx and modern INetworking.h; inspected the SDK IStats details/truncation and IUtils notification contracts. BASE-005 includes both allocation-capacity bounds and produced-length bounds. Uninitialized scalar logging after failed void APIs, ordinary string-copy unwritten tails and direct language null returns need explicit native output/error behavior before further crash claims. Binary notification tail disclosure uses an already initialized reusable buffer and successful output, so it does not rely on those uncertainties.
- **Native/module lifetime and multi-instance sharing:** Read SharedLibUtils.cxx/.hxx and the static/shared CMake link chain. No vendor-internal module ownership, post-Shutdown registrar validity, remaining Windows load references or simultaneous different-version support was presumed. Per-DLL loader state is fixed after first use; changing a prefix later does not redirect that singleton. Real factory reset remains unused, but the native singleton can remain valid after Shutdown; a leak/UAF was not inferred from omission alone.
- **Other low-threshold observations:** Hidden observer allocations are erased without delete; proxy submission exceptions/no terminal events can leave allocations; Logger's formatting-error length and pre-lock stream-state checks need focused failure/concurrency validation. These remain outside the new serious-finding count. IGalaxyFix's divergent redeclaration is an ODR concern without an established bad live vtable call in this pass.
- **Security, performance, build and CI:** Source-only token disclosure and output-extent evidence were reviewed, with no secret values accessed. Trace.hxx and Trace.cxx:210–389 confirm formatting, flag gates and file/console sinks. Per-call formatting/I/O is observable but unbenchmarked. The assigned CMake manifest and contextual linkage/features were read; configuration, CI, test executables and platform builds were not run.

## Recommended resolution and proposed verification order

1. Repair BASE-002/003 together using owner-aware pinned proxy records; retain correct adjusted interface identities and same-thread self-unregister. Detach owned registrations before native shutdown for BASE-001.
2. Correct callback result-type guards and auth success delivery (BASE-004/006), resolver features (BASE-007), and factory query/error/options fidelity (BASE-008/009, ADD-001/002). Snapshot partial-init errors before any subsequent native setup call can replace them.
3. Bound every logged output by a verified produced span (BASE-005), preserve game-server shutdown options (BASE-010), redact credential material (BASE-011), and defer forced-DLC completion to the documented pump (ADD-003).
4. When execution is authorized, use recording fake SDKs with actual supported headers: barriers/destruction counters for cancellation; distinct interface offsets and client/server domains; synthetic error snapshots and option values; written-length/tail-marker and guarded truncation buffers; callback timing/cancellation assertions. Establish native exception and registrar/module lifetime behavior separately rather than making the fake enforce an assumed vendor behavior.

No proposed check above has been reported as executed. The review is complete for the assigned full-file, shallow serious-defect scope; the listed native/ABI uncertainties remain explicit.

## Executed artifact reconciliation

- Final `git --no-optional-locks rev-parse HEAD` still returned `48cea8c6c48fa41fddd348a0119129cc5643fc8b`.
- Extension-restricted `git --no-optional-locks diff --exit-code b30e83872c0006e8240c8b4f565da5351bf10080 -- ...` returned no output: assigned production inputs remain unchanged.
- `git --no-optional-locks diff --check 48cea8c6c48fa41fddd348a0119129cc5643fc8b -- Source/InterceptionLogger` returned no whitespace errors.
- `git --no-optional-locks diff --numstat 48cea8c6c48fa41fddd348a0119129cc5643fc8b -- Source/InterceptionLogger` showed exactly eight sidecars, **300 inserted lines and zero deleted lines**. Baseline sections are preserved. The new owner notebook is an additional untracked report.
- PowerShell reconciliation of extension-filtered `git ls-files` with the notebook's exact path rows extracted by `rg --only-matching --pcre2` returned **TrackedInputs 73, CoverageRows 73, UniqueCoverage 73, PathDifferences 0**.
- `rg --no-ignore --count '^-.*ADD-INTERCEPT-00[123].*Medium' .ai/review-addendum/INTERCEPT.MD` returned **3**; the baseline-status-row count returned **11**. An earlier stricter ADD-index expression returned no matches and was replaced by the successful expression. Dedicated Grep independently found four full ADD headings representing the three unique IDs.
- Final owner-scoped status showed the eight intended modified sidecars plus `.ai/review-addendum/INTERCEPT.MD`. Unrelated review changes were visible in repository-wide status; this owner made no edits to them. These checks reconcile review artifacts and source preservation; they are not build/test or native-runtime verification.
