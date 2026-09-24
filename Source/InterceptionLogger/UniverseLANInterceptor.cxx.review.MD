# Fresh baseline review — UniverseLANInterceptor.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–350. Static Windows review; shallow serious-defect scope.

## Checked
- Read every factory/non-factory resolver and wrapper construction, retained init-options storage, config override, trace initialization and reset operation.
- Traced resolution through `Shared_NoVer/SharedLibUtils.cxx`: absent or ambiguous matches throw; no unchecked null function-pointer result is returned.
- Compared factory and game-server availability against feature definitions, SDK headers and representative x64 export manifests. Legacy factory initialization does not preserve every InitOptions field, and the real factory reset function is never invoked; these remain broader compatibility/lifecycle validation items.
- Reset destroys listener-bearing wrappers. Its placement after real shutdown is BASE-INTERCEPT-001 at the callers; merely clearing callbacks here does not detach listeners early enough.

## BASE-INTERCEPT-007 — Required export resolution ignores factory and game-server version boundaries

- **Severity:** High
- **Confidence:** High
- **Category:** API/ABI
- **Location:** `Source/InterceptionLogger/UniverseLANInterceptor.cxx:133–140,263–264,283–284`.
- **Affected scope:** Early factory versions 1.57.0–1.61.0; game-server versions with general Utils/Telemetry but without their game-server counterparts.

**Evidence:** Early SDK `1.57.0` and `1.61.0` x64 export manifests contain `GetInstance` and `Reset`, not `CreateInstance`/`ResetInstance`. The 1.57.0 factory header documents create-on-GetInstance and declares Reset. This file nevertheless resolves CreateInstance and ResetInstance unconditionally. For game servers it requests GameServerUtils under `HAS_IUTILS`, and GameServerTelemetry under `HAS_ITELEMETRY`. `galaxy_sdk_features.cmake` separately places game-server Utils at 1.133.0 and game-server Telemetry at 1.134.9–1.134.10 and 1.136.0 onward. SDK 1.125.2's game-server header/export manifest lacks GameServerUtils; SDK 1.134.8's lacks GameServerTelemetry.

**Failure mechanism:** `SharedLibUtils::get_function_match` throws when the required symbol is absent. Early factory initialization fails before creating the real instance. Older game-server initialization fails after real Init has already run and wrappers have partly been installed. The unused factory-reset callable still participates in mandatory resolution and can therefore abort initialization.

**Impact:** Normal startup is impossible for affected supported SDK configurations with the corresponding real DLL export surface. A partially initialized game-server session may escape as a C++ exception, while client init swallows it (BASE-INTERCEPT-008).

**Possible fixes:** Gate every resolver by the actual SDK interface/export feature, or use explicit version-specific resolver descriptors. Do not fall back from a game-server interface to a client interface with a different owner.

**Recommended resolution:** For early factories use the documented GetInstance/Reset pair; for game-server optional interfaces use `HAS_GAMESERVER_UTILS`/`HAS_GAMESERVERTELEMETRY`. Resolve the required surface before committing initialization where possible.

**Verification:** Without credentials, a symbol-only fake DLL/export map can validate 1.57.0, 1.61.0, 1.67.0, 1.125.2, 1.133.0, 1.134.8, 1.134.9, 1.135.x and 1.136.x boundaries on x86/x64. Require no resolution of nonexistent optional exports and deterministic rollback on true missing required exports. No DLL or build was executed.

## Follow-up review addendum — 2026-09-24

Reread the complete source, lines 1–350. Baseline conclusions are preserved; the additions below use separate accounting for new mechanisms and existing BASE IDs for extensions.

### ADD-INTERCEPT-002 — Legacy InitOptions is forwarded through an overload that cannot carry its settings

- **Severity:** Medium
- **Confidence:** High
- **Category:** API/ABI
- **Location:** `Source/InterceptionLogger/UniverseLANInterceptor.cxx:145–166`; `Impl/InitOptionsModern.cxx:10–33,148–176`; incoming route at `GalaxyApiFactory.cxx:32–35` and `GalaxyDLL.cxx:66–69`.
- **Affected scope:** Supported factory SDKs with `HAS_INITOPTIONS`, i.e. the feature intersection 1.82.0–1.114.9; available examples 1.87.0 and 1.114.9. Caller-supplied legacy configuration/peer paths and exception policy.

**Evidence**

SDK `Source/DLLs/1.87.0/galaxy/IGalaxy.h:35–60,85–111` and `1.114.9/galaxy/IGalaxy.h:38–63,93–129` define InitOptions containing `galaxyPeerPath`, `configFilePath`, and `const bool throwExceptions`, and expose `Init(const InitOptions&)`. SDK `1.114.9/galaxy/GalaxyApi.h:312–320` calls that overload. The interceptor instead selects it only under `HAS_INITOPTIONS_MODERN`, inside `HAS_IGALAXY`. Those features cannot overlap: `Source/galaxy_sdk_features.cmake:11,76,118` ends the factory range at 1.114.9 and starts modern options at 1.120.0.

The actual factory branch calls string-based Init or InitLocal. Neither accepts configFilePath. The options-taking conversion sets `local_init=false`, so with key overrides disabled even a supplied peer path is omitted by the string-based Init call. It also initializes `throwExceptions=false` and copies the supplied value only under `!HAS_INITOPTIONS`, which is false for precisely these SDK options.

**Failure mechanism**

A valid `Init(InitOptions{..., peerPath, true, configPath})` reaches the interceptor's options overload, is copied into InitOptionsModern, and is then reduced to `(clientID, clientSecret, false)` in the normal branch. A requested config directory is never passed to the native SDK; the local peer selection is lost; the requested exception policy is changed. The preserved strings' C++ lifetime is sufficient, but their values never reach the matching SDK overload.

**Impact**

Games relying on a non-default SDK configuration or local peer location can initialize against different settings or fail initialization only when intercepted. Callers requesting throwing behavior instead get the non-throwing mode. These are direct argument/overload mismatches; no specific vendor crash or installation layout was executed.

**Possible solutions**

Forward a faithfully reconstructed legacy InitOptions to the matching native overload, or keep distinct legacy/modern option adapters selected by the exact SDK type. String-only legacy calls can retain their own routes.

**Recommended resolution**

Use `HAS_INITOPTIONS` to select the available factory options overload, preserve every supported field, and construct the SDK's const exception-policy member with the supplied value. Changing the branch alone is insufficient: `GetInitOptionsImpl()` currently constructs the legacy SDK object using its default exception policy. Preserve the distinction between an empty peer path and an explicitly requested local path instead of inferring it from unrelated override settings.

**Verification**

Proposed only: a recording fake IGalaxy for 1.87.0 and 1.114.9 must receive the options overload and exact synthetic path/boolean values for both exception modes, empty/explicit peer paths and default/non-default config paths. Cover string Init and InitLocal as regressions, then a modern options SDK. Inspect constructor arguments as well as forwarded calls. No build/test was run. Same ID in the conversion sidecar; counted once. This promotes a previously uncounted compatibility observation, not another occurrence of missing-export BASE-INTERCEPT-007.

### BASE-INTERCEPT-008 — Addendum: non-throwing Init errors can also be overwritten by wrapper setup

- **Severity:** Medium, retained for the existing finding
- **Confidence:** High for call ordering and documented error reset; no native failure injection performed
- **Category:** Correctness
- **Location:** `Source/InterceptionLogger/UniverseLANInterceptor.cxx:166–225,240–284`; `ListenersContainer.cxx:18–19`; public observation at `GalaxyDLL.cxx:175–180`.
- **Affected scope:** Partial native initialization that reports an error without throwing and still permits subsequent interface/registrar setup, including client and game-server construction.

**Evidence**

SDK `1.152.11/galaxy/GalaxyApi.h:77–85` says API calls reset the last stored error, and lines 335–338 explicitly permit partial initialization. `GalaxyGameServerApi.h:78–81` has the corresponding partial-init contract. After real Init returns at line 241, this implementation makes more native calls, including `IListenerRegistrar::Register` from wrapper constructors, before the application can query GetError. No original error is copied or pinned. The legacy branch's diagnostic HasError query is likewise after constructor registrations, not immediately after real Init.

**Failure mechanism**

Native Init records error E and returns a partially usable SDK. A subsequent successful observer registration resets E. Initialization then returns normally and GetError reads the later native error state, which can be null. Alternatively, a setup error replaces E with an unrelated error. This is a concrete additional way the existing initialization/error-state defect presents; it does not require std::exception to be thrown or config to be null.

**Impact**

The game can lose the original reason for degraded startup and miss its documented fallback path. The factory manager defect ADD-INTERCEPT-001 additionally hides ordinary post-startup errors through a different entry point; it is not needed for this sequence on modern SDKs.

**Possible solutions**

Snapshot native error information immediately after Init, or arrange internal setup behind an error-preserving facade. A raw native error pointer is insufficient if later calls invalidate/replace its storage.

**Recommended resolution**

Include the original native error in BASE-INTERCEPT-008's explicit partial-initialization state and preserve it through internal calls. Respect useful partial functionality rather than treating every native Init error as proof that every interface is unusable. Keep cleanup safe at each completed stage.

**Verification**

Proposed only: fake native Init returns error E plus usable registrars; Register clears the native error. Immediately after intercepted Init, public GetError must still expose E and required shutdown must work. Repeat with Register setting a different error, client/server sessions and throwing/non-throwing factory modes. This extends BASE-INTERCEPT-008 and adds no new count.
