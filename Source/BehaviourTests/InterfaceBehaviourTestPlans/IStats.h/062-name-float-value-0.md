# `virtual void SetStatFloat(const char* name, float value) = 0;`

## Declaration and applicability

- Header: `IStats.h`
- Exact declaration/signature:
```cpp
virtual void SetStatFloat(const char* name, float value) = 0;
```
- Observed snapshot availability: 1.57.0, 1.60.0, 1.61.0, 1.64.0, 1.66.0, 1.67.0, 1.68.0, 1.69.0, 1.70.0, 1.72.0, 1.73.0, 1.74.0, 1.75.0, 1.76.0, 1.77.0, 1.80.0, 1.87.0, 1.92.0, 1.95.0, 1.99.0, 1.100.2, 1.104.2, 1.104.3, 1.104.4, 1.106.0, 1.109.0, 1.112.2, 1.113.1, 1.113.3, 1.114.9, 1.121.2, 1.124.0, 1.125.2, 1.126.1, 1.127.0, 1.128.3, 1.130.0, 1.131.3, 1.132.1, 1.133.0, 1.133.6, 1.134.8, 1.134.9, 1.134.10, 1.135.0, 1.138.0, 1.139.2, 1.139.5, 1.139.6, 1.139.9, 1.140.0, 1.142.0, 1.144.1, 1.148.1, 1.148.2, 1.148.3, 1.148.5, 1.148.6, 1.148.7, 1.148.11, 1.148.14, 1.149.0, 1.150.0, 1.151.0, 1.152.1, 1.152.2, 1.152.6, 1.152.9, 1.152.11.
- Relevant build matrix gate: No dedicated feature gate; compile only where this exact declaration is present.
- Existing coverage: No grounded existing coverage identified in `Source/BehaviourTests/COVERAGE.md`.

## Fact boundary

- Documented fact: the selected public header declares the signature above. Any adjacent header precondition, return description, or callback statement may be asserted verbatim.
- Characterization required: result values, error category, callback delivery/count/order/thread, timing, cross-client visibility, pointer lifetime, and behavior for inputs not explicitly documented. Do not promote these observations to SDK guarantees.

## Expected observations

- Observe public state before and after `SetStatFloat`, one repeated/idempotency characterization, and cleanup/reversal only where the API exposes it.
- A successful scheduling/result value, callback timing, propagation, or repetition is not assumed unless documented.

## Public-SDK-only plan

1. Establish a legal public target, snapshot the relevant public pre-state, invoke `SetStatFloat` once, and record its immediate result/error plus any documented terminal listener.
2. Reissue the same legal mutation only as characterization; compare public pre/post state without assuming idempotency or propagation timing.
3. Use the documented inverse, leave, close, delete, or shutdown path when available. Bound pumping, destroy listeners before shutdown, and redact all temporary values.

## Result placeholders

- UniverseLAN server + 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized mutation result: `<documented facts and characterization observations>`.
- Official GOG 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized mutation result: `<documented facts and characterization observations>`.
## Verdict and next step

- `[ ] Pass` `[ ] Fail` `[x] Not-run`
- Least-feasible next step: run the smallest valid `SetStatFloat` probe in both lanes, then add only the documented boundary or lifecycle observation needed to explain a difference.
