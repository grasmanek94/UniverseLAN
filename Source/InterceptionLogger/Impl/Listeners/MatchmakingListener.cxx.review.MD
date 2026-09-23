# Fresh baseline review — Impl/Listeners/MatchmakingListener.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–225. Static Windows review; shallow serious-defect scope.

## Checked
- Read both list/leave overloads and all created/entered/data/member/owner/message callback bodies.
- Matched listener creation in MatchmakingImpl, proxy last-statement cleanup and enum/flag formatting.
- Cross-checked SDK 1.125.2 and 1.132.1 IMatchmaking declarations and fallback enum definitions in Shared/GalaxyVersionedTypes.hxx.

## BASE-INTERCEPT-006 — Wrong feature guard suppresses legacy list/leave completions

- **Severity:** High
- **Confidence:** High
- **Category:** API/ABI
- **Location:** `Source/InterceptionLogger/Impl/Listeners/MatchmakingListener.cxx:25–47,74–97`.
- **Affected scope:** Specific lobby-list callbacks from 1.125.0 until the 1.129.0 result-enum transition; specific lobby-leave callbacks from 1.125.0 until the 1.133.0 reason-enum transition.

**Evidence and failure mechanism:** The bool overloads forward only under `!GALAXY_BUILD_FEATURE_LOBBY_LISTENERS`; enum overloads forward under the opposite condition. That feature means operation-specific listener arguments exist, not that callback result types changed. SDK 1.125.2 `IMatchmaking.h:103,182` still invokes bool overloads; SDK 1.132.1 has enum OnLobbyList but bool OnLobbyLeft. The feature matrix distinguishes these transitions explicitly. During the affected windows, requests wrap the game listener, then the actual SDK-invoked bool callback only traces and returns. The enum overload may compile because fallback enums exist and convert to bool, but it is not the method the SDK dispatches.

**Impact:** Pending matchmaking/list/leave state machines never receive completion through the supplied listener. Proxies also remain in the registry instead of being retired. Globally registered game listeners that bypass these wrappers may still receive notifications.

**Possible fixes:** Guard each implementation by the actual result/reason feature, or compile only the matching override for each SDK.

**Recommended resolution:** Use `HAS_IMATCHMAKING_LOBBY_LIST_RESULT` and `HAS_IMATCHMAKING_LOBBY_LEAVE_REASON` for their respective overloads, with `override` on active signatures. Keep all actual callbacks forwarding and cleanup-capable.

**Verification:** Dispatch through SDK base interfaces with headers for 1.125.2, 1.128.3, 1.132.1 and 1.133.0; require exactly one original callback and proxy retirement for list and leave success/failure cases. Proposed only.
