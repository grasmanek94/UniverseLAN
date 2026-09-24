# Fresh baseline review — Impl/Apps.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–141. Static Windows review; shallow serious-defect scope.

## Checked
- Read DLC installation/ownership override paths, language/code getters and copy-buffer tracing; checked ownership-listener construction and feature guards.
- Compared IsDlcOwned with SDK 1.152.11 IApps: it requires an explicitly supplied listener and documents an asynchronous response. The forced-DLC path calls it synchronously and dereferences it directly; a permitted null-listener contract or concrete unsafe game reentrancy was not established, so neither was promoted to a confirmed crash finding.
- Language copy traces use the capacity-bounded helper. Direct language pointers are formatted without null annotation; SDK null-return behavior remains unverified.

## Result
No independent serious defect confirmed at this depth. Shared listener shutdown/proxy lifetime findings apply through the common infrastructure. Validate forced-DLC callback scheduling and null/error returns before asserting full transparency.

## Follow-up review addendum — 2026-09-24

Reread all 141 lines and the supported SDK's application and callback contracts. The null-listener crash hypothesis remains unconfirmed. The scheduling violation below is established independently of nullability or a native crash.

### ADD-INTERCEPT-003 — Forced DLC ownership calls the application inline instead of during ProcessData

- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/InterceptionLogger/Impl/Apps.cxx:121–136`; override supplied at `UniverseLANInterceptor.cxx:197,268`.
- **Affected scope:** `HAS_IAPPS_ISDLCOWNED` (1.152.2 onward), with GetEnableAllDLC/force_dlc_check enabled and a valid supplied listener.

**Evidence**

The forced branch directly executes `listener->OnDlcCheckSuccess(productID, true)` before IsDlcOwned returns. SDK `Source/DLLs/1.152.11/galaxy/IApps.h:83–92` specifies an asynchronous response. Its `GalaxyApi.h:99–106` states that listeners run during ProcessData. This contract supplies evidence missing from a bare observation that the branch is synchronous. The selected ownership result may intentionally be overridden; the public callback scheduling contract still exists.

**Failure mechanism**

On one thread, a caller submits the ownership check, finishes installing its pending-operation state after the request returns, and later pumps ProcessData. This ordering is valid under the SDK contract. The interceptor instead invokes the completion inside submission. A completion handler can therefore run before pending state is installed; for example it marks the request complete, after which submission overwrites the state to pending. No later completion is queued to resolve that state. The same branch can reenter caller code on the submission thread even if callbacks are normally confined to another pump thread.

**Impact**

The configuration override introduces unexpected reentrancy and can strand an ownership-dependent loading/entitlement state machine. A concrete use-after-free in an unspecified game is not asserted. The finding is Medium because it requires the override and an ordering-sensitive caller, not merely use of IsDlcOwned.

**Possible solutions**

Queue a synthetic ownership completion for the normal callback pump with cancellation/lifetime tracking, or arrange the forced result through an asynchronous proxy on the native completion route.

**Recommended resolution**

Preserve delivery during ProcessData and the SDK's listener cancellation semantics when producing the synthetic result. Integrate its lifetime with the corrected proxy protocol rather than capturing a naked listener in an untracked deferred lambda. Do not infer that null is allowed: this API has no optional-listener default or explicit nullable contract in the inspected SDK.

**Verification**

Proposed only: use a valid synthetic listener and enabled override; assert zero callbacks before IsDlcOwned returns, zero before pumping, exactly one callback during the pump and correct product/result. Install pending state after submission to exercise the legal ordering above. Unregister before pumping and require no call, then cover disabled override. No build, test or account operation was run. This promotes the baseline's uncounted scheduling observation; it is not a new null-pointer-crash claim.
