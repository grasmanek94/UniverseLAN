# `virtual void RegisterForNotification(const char* type) = 0;`

## Declaration and applicability

- Header: `IUtils.h`
- Exact declaration/signature:
```cpp
virtual void RegisterForNotification(const char* type) = 0;
```
- Observed snapshot availability: 1.75.0, 1.76.0, 1.77.0, 1.80.0, 1.87.0, 1.92.0, 1.95.0, 1.99.0, 1.100.2, 1.104.2, 1.104.3, 1.104.4, 1.106.0, 1.109.0, 1.112.2, 1.113.1, 1.113.3, 1.114.9, 1.121.2, 1.124.0, 1.125.2, 1.126.1, 1.127.0, 1.128.3, 1.130.0, 1.131.3, 1.132.1, 1.133.0, 1.133.6, 1.134.8, 1.134.9, 1.134.10, 1.135.0, 1.138.0, 1.139.2, 1.139.5, 1.139.6, 1.139.9, 1.140.0, 1.142.0, 1.144.1, 1.148.1, 1.148.2, 1.148.3, 1.148.5, 1.148.6, 1.148.7, 1.148.11, 1.148.14, 1.149.0, 1.150.0, 1.151.0, 1.152.1, 1.152.2, 1.152.6, 1.152.9, 1.152.11.
- Relevant build matrix gate: GALAXY_BUILD_FEATURE_HAS_IUTILS.
- Existing coverage: runtime-blocked in two 2026-09-16 two-lane attempts. Both global-listener and registration-only public probe forms exited before trace output; no behavior result is classified. See [header coverage](HEADER_COVERAGE.md).

## Fact boundary

- Documented fact: types beginning with `__` are reserved and cannot be used.
- Characterization required: registration result, error category, listener behavior, and delivery. Do not promote observations to SDK guarantees.

## Expected observations

- A generated legal non-reserved type was attempted without retaining its text. Both the registration-only and listener forms exited before trace output in both lanes.
- This is an execution blocker, not a delivery result or implementation defect.

## Public-SDK-only plan

1. Do not automatically invoke the method in the current environment.
2. First provide a controlled public notification source and a runtime form that produces a trace in both lanes.
3. Do not manufacture notification IDs or infer callback delivery from registration.

## Result placeholders

- UniverseLAN server + 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized query result: `<documented facts and characterization observations>`.
- Official GOG 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized query result: `<documented facts and characterization observations>`.
## Verdict and next step

- `[ ] Pass` `[ ] Fail` `[x] Not-run`
- Least-feasible next step: resolve the pre-trace runtime exit with an independently controlled notification fixture. Do not classify a difference or modify implementation code from the current blocked attempts.
