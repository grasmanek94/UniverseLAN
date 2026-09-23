# Fresh review — Tracer.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–94. Static review.

## Inspection notes
- Inspected mask values, constructor overload resolution, source_location defaults, noncopyable scope ownership, logger accessors and formatting forwarding.
- Noncopyability prevents duplicated Exit calls from copied scopes. Each object caches its enabled decision so changing the global toggle during a scope does not alone unbalance depth.
- `write_all` is static and checks the global tracing flag, not an individual Trace mask. Callers needing mask filtering must use `has_flags`; no instance-specific filtering contract is asserted by this API.
- Exposing stream accessors permits bypassing synchronized writes; concrete bypasses in this implementation are **BASE-SERVER-010** in `Tracer.cxx.review.MD`.

## Result
No independent header finding. Stream/thread use and initialization behavior are assessed in the implementation sidecar.
