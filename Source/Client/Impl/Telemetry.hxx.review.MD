# Fresh baseline review: Telemetry.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Entire file read, lines 1–232. Windows static review; no execution.

## File-specific inspection

- Checked every parameter-building declaration, null-name documentation, nesting/clear contracts, sampling feature guard, send result/listener contract, anonymous-send variant, and visit-ID API against the latest SDK and implementation.
- The nullable `name` contract applies to all six `Add*Param` declarations, not merely string values. BASE-STORAGE-021 in `Telemetry.cxx.review.MD` covers the invalid C-string insertion reached by those legitimate inputs.
- Private state has a mutex, output stream, atomic event counter, and visit string, but no explicit enabled/initialized sink state. BASE-STORAGE-023 explains why testing `operator bool` on that stream is insufficient to implement the configured disabled path.
- No parameter tree or sampling state is represented in the class; the current backend records calls textually. This explains its limits without asserting interoperability with a remote event service.
- The recursive mutex makes visit-ID copy/reset mutually exclusive while they execute; the pointer-returning visit method returns an internal string pointer after unlocking. Callers retaining it through a reset need a clarified lifetime policy. No pointer invalidation claim is made for a simple immediate single-thread read.
- Atomic counter use protects numeric event-ID allocation, not all stream checks or logical multi-call event construction. Lock coverage and enabled-state handling require validation in implementation.
- Specific listener lifetime relies on registrar behavior; deferred string payload lifetime is extended by the notification helper. These are separate ownership concerns.

## Findings disposition

No extra declaration-only defect counted. Canonical full sections are BASE-STORAGE-021 and BASE-STORAGE-023 in `Telemetry.cxx.review.MD`. Proposed verification: anonymous array elements, enabled/disabled first-use behavior, failed writes, callback correctness, and concurrent stream access. Static inspection alone does not establish durability or thread safety.
