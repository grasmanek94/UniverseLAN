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
