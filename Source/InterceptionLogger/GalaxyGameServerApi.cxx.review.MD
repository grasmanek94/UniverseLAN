# Fresh baseline review — GalaxyGameServerApi.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–66. Static Windows review; shallow serious-defect scope.

## Checked
- Read the static game-server owner, all exported forwarding functions and game-server/telemetry/shutdown feature guards.
- Cross-checked `ShutdownOptions` and the distinct extended shutdown declaration in SDK 1.152.11.
- Older game-server interface availability is handled incorrectly in the dynamic initialization layer; see BASE-INTERCEPT-007 at `UniverseLANInterceptor.cxx`.

## BASE-INTERCEPT-010 — ShutdownGameServerEx drops its options and calls ordinary shutdown

- **Severity:** Medium
- **Confidence:** High
- **Category:** API/ABI
- **Location:** `Source/InterceptionLogger/GalaxyGameServerApi.cxx:24–28`.
- **Affected scope:** Versions with `HAS_SHUTDOWNOPTIONS` (1.151.0 onward).

**Evidence and failure mechanism:** The exported function receives `shutdownOptions` but calls `gameserver.ShutdownGameServer()` without them. The correct `UniverseGameServer::ShutdownGameServerEx` implementation already exists and invokes `real_shutdown_ex(shutdownOptions)`. SDK `1.152.11/galaxy/ShutdownOptions.h:26–33` defines `preserveStaticObjects` specifically for consecutive initialization.

**Impact:** A caller explicitly preserving static SDK objects instead takes the ordinary destructive shutdown path. This defeats the requested lifetime policy and can break integrations relying on consecutive initialization. A concrete vendor crash from that difference has not been established.

**Possible fixes:** Forward to the extended method, or deliberately translate every supported option with equivalent semantics.

**Recommended resolution:** Call `gameserver.ShutdownGameServerEx(shutdownOptions)` and address pre-shutdown listener detachment separately (BASE-INTERCEPT-001).

**Verification:** A stub real SDK should record exactly one extended-shutdown call and the original true/false `preserveStaticObjects` value. Then exercise shutdown/reinit with the real SDK. Proposed, not executed.
