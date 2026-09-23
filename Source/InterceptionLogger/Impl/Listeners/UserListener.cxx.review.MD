# Fresh baseline review — Impl/Listeners/UserListener.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–159. Static Windows review; shallow serious-defect scope.

## Checked
- Read every auth/session/state/data/ticket/token/OpenID callback and its feature gate.
- Other specific completion callbacks use the proxy epilogue as their last statement. Global observer instances have null targets and only trace.
- Distinguished callbacks that are actually used as specific operation proxies from global-only observer classes; did not classify all empty observer callbacks as dropped game events.

## BASE-INTERCEPT-004 — Specific authentication listeners never receive successful sign-in

- **Severity:** High
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/InterceptionLogger/Impl/Listeners/UserListener.cxx:27–30`; compare failure forwarding at 32–40.
- **Affected scope:** Non-null per-operation IAuthListener arguments, introduced by `USER_SIGNIN_LISTENERS` (1.121.3 onward), including client and game-server sign-in forms.

**Evidence and failure mechanism:** UserImpl wraps non-null auth listeners using `AuthListener::encapsulate`. The real SDK therefore sees only the proxy. `AuthListener::OnAuthSuccess` constructs a Trace and returns, never calling `target->OnAuthSuccess` and never running proxy cleanup. By contrast, OnAuthFailure uses the forwarding macro. SDK `1.152.11/galaxy/IUser.h:33–36,365–380,382–397` promises the success response to the optional supplied listener; `GalaxyApi.h:99–103` says specific listeners are unregistered after their event.

**Impact:** Successfully authenticated games waiting on that callback can remain in login/loading indefinitely. Successful attempts also leave proxy allocations/registry entries until explicit cancellation (or indefinitely if it never occurs). Separately globally registered game listeners are passed directly through and are not necessarily affected.

**Possible fixes:** Forward successful completion with the common lifetime protocol, or use an explicit auth-proxy class with correctly defined terminal events.

**Recommended resolution:** Deliver OnAuthSuccess to non-null targets and retire the specific proxy through a corrected ownership protocol (BASE-INTERCEPT-002/003). Keep target-null global observers alive. OnAuthLost is also trace-only, but do not extend specific-listener lifetime beyond the SDK's single-event contract merely to receive later loss notifications.

**Verification:** Fake SDK returns auth success to a supplied specific listener; require exactly one game callback and one proxy retirement. Exercise failure, null listener, global listener, callback self-unregister and server auth. Proposed only.
