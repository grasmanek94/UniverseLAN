# Fresh baseline review — GalaxyApiFactory.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–224. Static Windows review; shallow serious-defect scope.

## Checked
- Read every `GalaxyImpl` virtual forwarder, both legacy string-based initialization routes, reset-name and calling-convention guards, and error-manager shim.
- Compared factory creation/query semantics with SDK `1.57.0` and `1.67.0/galaxy/GalaxyFactory.h`, and inline callers in `1.67.0/galaxy/GalaxyApi.h`.
- `ErrorManager::GetLastError` always returns null; actual real-factory reset/error-manager integration and legacy option fidelity require further validation. No binary ABI validation was performed.

## BASE-INTERCEPT-009 — GetInstance creates an object where the newer factory contract requires a null query

- **Severity:** Medium
- **Confidence:** High
- **Category:** API/ABI
- **Location:** `Source/InterceptionLogger/GalaxyApiFactory.cxx:178–185`, `GalaxyFactory::GetInstance`; downstream `GalaxyDLL.cxx:72–77,164–165`.
- **Affected scope:** Factory versions after the factory-semantics transition (feature boundary 1.62.0), through 1.114.9; confirmed contract example 1.67.0. The old 1.57.0 create-on-query contract is different.

**Evidence and failure mechanism:** `GetInstance` unconditionally allocates `GalaxyImpl` if `instance` is null. SDK 1.67.0 `GalaxyFactory.h:32–39` requires null before creation. Its `GalaxyApi.h:266–289` deliberately makes `Shutdown` and `ProcessData` no-ops when that query is null. The interceptor defeats the guard: before initialization, or after a prior shutdown/reset, those inline calls reach empty `real_shutdown`/`real_process_data` functions and throw `std::bad_function_call`.

**Impact:** Valid repeated cleanup or pre-init pumping can raise an unexpected exception and terminate an uncaught caller. This is not an allegation that all SDK versions permit arbitrary post-shutdown interface use; the cited inline helpers explicitly handle this state.

**Possible fixes:** Version-gate query semantics, or introduce a factory state abstraction shared by the query/create/reset operations.

**Recommended resolution:** Preserve create-on-query only for the older SDK contract; newer `GetInstance` should return `instance` without allocation, and `CreateInstance` should own creation.

**Verification:** With 1.67.0 and 1.114.9 headers, call `ProcessData`/`Shutdown` before Init and call Shutdown twice after a successful session; require no allocation or exception on the null-instance paths. Also check the 1.57.0 lazy-creation behavior. Proposed, not executed.

## Follow-up review addendum — 2026-09-24

Reread the complete source, lines 1–224, at the unchanged production baseline. The baseline sections above are preserved.

### ADD-INTERCEPT-001 — The factory error-manager stub makes public GetError always succeed

- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/InterceptionLogger/GalaxyApiFactory.cxx:155–169,188–197`; native manager acquisition at `UniverseLANInterceptor.cxx:134–142`.
- **Affected scope:** Factory SDKs with `HAS_IERRORMANAGER`, within the factory range ending at 1.114.9; concrete supported examples 1.64.0, 1.67.0 and 1.114.9. Ordinary API errors after successful initialization are affected, not just failed Init.

**Evidence**

`ErrorManager::GetLastError()` unconditionally returns `nullptr`. The exported factory returns this stub. SDK `Source/DLLs/1.67.0/galaxy/GalaxyApi.h:380–386` implements the application's public, inline `galaxy::api::GetError()` as `GalaxyFactory::GetErrorManager()->GetLastError()`. The same route is present in `1.114.9/galaxy/GalaxyApi.h:533–540` and in the 1.64.0 header. The SDK manager contract is `1.67.0/galaxy/Errors.h:90–106`. Although initialization obtains `real_ierror_manager`, this stub never consults it. `GalaxyImpl::GetError()` and `GalaxyDLL.cxx`'s error wrapper are a different route and cannot repair the SDK inline function.

**Failure mechanism**

Initialize successfully in non-throwing mode, then let a native API operation record an ordinary runtime error. Immediately call the public SDK `GetError()`, without an intervening API operation. It calls the interceptor's stub and returns null regardless of the native error. This does not depend on the erroneous create-on-query behavior in BASE-INTERCEPT-009 or an initialization exception in BASE-INTERCEPT-008. Older inline Init helpers also consult this manager to decide whether to reset the factory (`1.67.0/galaxy/GalaxyApi.h:228–259`).

**Impact**

Games using the documented non-throwing error channel lose all synchronous error reporting through this public entry point. Recovery/fallback decisions and success checks become wrong even after normal startup. Async failure callbacks are a separate channel and are not alleged to disappear because of this stub.

**Possible solutions**

Forward the manager to the real factory's error manager, or provide a compatible error facade that includes both native and interceptor-generated errors and preserves the SDK's error lifetime/thread semantics.

**Recommended resolution**

Connect the exported factory manager to the real error source and define its behavior before initialization and after reset. Keep the public inline GetError route and direct IGalaxy GetError route consistent. Do not merely change the modern free-function adapter, which these clients do not call.

**Verification**

Proposed only: use the actual 1.67.0 and 1.114.9 inline headers with a fake native factory. After successful non-throwing Init, make a forwarded operation set a synthetic runtime error; require public GetError to return that error immediately, then clear it with a successful operation and require null. Check direct IGalaxy access, independent threads where supported, and the old Init-helper reset branch. No build, test or native DLL execution was performed. This promotes the baseline's uncounted error-manager observation into one new finding.
