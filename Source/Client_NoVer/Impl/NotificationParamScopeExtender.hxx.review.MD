# Fresh baseline review — NotificationParamScopeExtender.hxx

- Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`.
- Coverage: entire file, lines 1–72; static template/caller review.

## Specific checked notes

- Examined both identity adapters and both lifetime-extension overloads, including `remove_cvref_t`, forwarding references, and the exact `const char*` constraint.
- In the registrar, arguments are first taken by value and then moved into `bind_front`; owned extenders remain stored in the callable, while member-function pointers, IDs/enums, and object pointers are forwarded/stored by value.
- `const char*` callback payloads from local data and WebSocket connection strings are copied; conversion occurs while the queued callable is executing.
- The generic overload intentionally forwards mutable `char*` and all other pointers. The warning comment correctly identifies the narrower contract. No concrete reviewed caller with a dangling mutable-character buffer was established, so no speculative data-pointer finding is added.
- Raw listener pointers also follow that generic path. Their cancellation defect is in the registrar protocol (`BASE-CORE-001`), not an expectation that this string adapter own arbitrary interface objects.

## Findings and limits

No independent template or ownership defect confirmed. C++20 requirements are supplied by root CMake. No compile-time template matrix, sanitizer run, or arbitrary-pointer lifetime proof was performed.
