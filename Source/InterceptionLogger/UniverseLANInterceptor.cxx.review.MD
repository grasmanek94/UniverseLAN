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
