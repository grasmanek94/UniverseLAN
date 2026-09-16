# `virtual void RequestNatTypeDetection() = 0;`

## Declaration and applicability

- Header: `INetworking.h`
- Exact declaration/signature:
```cpp
virtual void RequestNatTypeDetection() = 0;
```
- Observed snapshot availability: 1.113.1, 1.113.3, 1.114.9, 1.121.2, 1.124.0, 1.125.2, 1.126.1, 1.127.0, 1.128.3, 1.130.0, 1.131.3, 1.132.1, 1.133.0, 1.133.6, 1.134.8, 1.134.9, 1.134.10, 1.135.0, 1.138.0, 1.139.2, 1.139.5, 1.139.6, 1.139.9, 1.140.0, 1.142.0, 1.144.1, 1.148.1, 1.148.2, 1.148.3, 1.148.5, 1.148.6, 1.148.7, 1.148.11, 1.148.14, 1.149.0, 1.150.0, 1.151.0, 1.152.1, 1.152.2, 1.152.6, 1.152.9, 1.152.11.
- Relevant build matrix gate: No dedicated feature gate; compile only where this exact declaration is present.
- Existing coverage: No grounded existing coverage identified in `Source/BehaviourTests/COVERAGE.md`.

## Fact boundary

- Documented fact: the selected public header declares the signature above. Any adjacent header precondition, return description, or callback statement may be asserted verbatim.
- Characterization required: result values, error category, callback delivery/count/order/thread, timing, cross-client visibility, pointer lifetime, and behavior for inputs not explicitly documented. Do not promote these observations to SDK guarantees.

## Expected observations

- `RequestNatTypeDetection` is treated as an asynchronous request when the signature/header supplies a listener or later public state; the terminal callback/result/state and bounded timeout are separate observations.
- No success, failure reason, callback count, or ordering is predicted unless the header documents it.

## Public-SDK-only plan

1. Register the specific/global listener before invoking `RequestNatTypeDetection`, establish a causal two-client readiness gate when a peer is involved, and record the immediate public result/error.
2. Pump only the public processing API to a bounded deadline; record one or more terminal callback arguments, terminal public state, and timeout as separate normalized observations.
3. Repeat only documented boundary/invalid/state forms, characterize duplicates/order without asserting them, destroy listeners before shutdown, and clean up any temporary public object.

## Result placeholders

- UniverseLAN server + 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized async result: `<documented facts and characterization observations>`.
- Official GOG 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized async result: `<documented facts and characterization observations>`.
## Verdict and next step

- `[ ] Pass` `[ ] Fail` `[x] Not-run`
- Least-feasible next step: run the smallest valid `RequestNatTypeDetection` probe in both lanes, then add only the documented boundary or lifecycle observation needed to explain a difference.
