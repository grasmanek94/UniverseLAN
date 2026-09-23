# Fresh baseline review — ListenersContainer.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–32. Static Windows review; shallow serious-defect scope.

## Checked
- Read `AddListener<T>` allocation, type-aware registration and the pointer/type map. Normal construction uses observer listeners with null forwarding targets, not one-shot proxy objects.
- Checked ownership against the destructor implementation: raw allocations are not freed when entries are erased; allocation/registration exceptions also lack a transactional RAII owner. The small per-session leak is below this serious-only scan's reporting threshold.
- `registrar` is a borrowed real-SDK object, so declaration/member lifetime cannot make post-SDK-shutdown unregister safe (BASE-INTERCEPT-001 at shutdown callers).

## Result
No additional independent serious defect confirmed in this header. Suggested ownership cleanup is not a substitute for fixing the confirmed teardown order.
