# `virtual void PopP2PPacket(uint8_t channel = 0) = 0;`

## Declaration and applicability

- Header: `INetworking.h`
- Exact declaration/signature:
```cpp
virtual void PopP2PPacket(uint8_t channel = 0) = 0;
```
- Observed snapshot availability: 1.57.0, 1.60.0, 1.61.0, 1.64.0, 1.66.0, 1.67.0, 1.68.0, 1.69.0, 1.70.0, 1.72.0, 1.73.0, 1.74.0, 1.75.0, 1.76.0, 1.77.0, 1.80.0, 1.87.0, 1.92.0, 1.95.0, 1.99.0, 1.100.2, 1.104.2, 1.104.3, 1.104.4, 1.106.0, 1.109.0, 1.112.2, 1.113.1, 1.113.3, 1.114.9, 1.121.2, 1.124.0, 1.125.2, 1.126.1, 1.127.0, 1.128.3, 1.130.0, 1.131.3, 1.132.1, 1.133.0, 1.133.6, 1.134.8, 1.134.9, 1.134.10, 1.135.0, 1.138.0, 1.139.2, 1.139.5, 1.139.6, 1.139.9, 1.140.0, 1.142.0, 1.144.1, 1.148.1, 1.148.2, 1.148.3, 1.148.5, 1.148.6, 1.148.7, 1.148.11, 1.148.14, 1.149.0, 1.150.0, 1.151.0, 1.152.1, 1.152.2, 1.152.6, 1.152.9, 1.152.11.
- Relevant build matrix gate: No dedicated feature gate; compile only where this exact declaration is present.
- Existing coverage: No grounded existing coverage identified in `Source/BehaviourTests/COVERAGE.md`.

## Fact boundary

- Documented fact: the selected public header declares the signature above. Any adjacent header precondition, return description, or callback statement may be asserted verbatim.
- Characterization required: result values, error category, callback delivery/count/order/thread, timing, cross-client visibility, pointer lifetime, and behavior for inputs not explicitly documented. Do not promote these observations to SDK guarantees.

## Expected observations

- Initial, valid, and documented invalid/state calls are distinct observations; do not assign a result where the header does not specify one.
- For index, size, buffer, pointer, or copy forms, record in-range/out-of-range, zero/exact/undersized buffer, and documented owner/lifetime relations only when the signature supports them.

## Public-SDK-only plan

1. Establish the documented prerequisite state in both lanes, then call `PopP2PPacket` initially and after one valid public transition; record only its return/error and public state relation.
2. Where its parameters expose an index, size, buffer, pointer, or copy, run documented boundary forms and retain no raw data. Mark unsupported invalid forms as characterization rather than expected behavior.
3. Repeat public queries around callback pumping only when their source operation is asynchronous; retain/copy results only for the lifetime stated by the header and complete ordinary listener/shutdown cleanup.

## Result placeholders

- UniverseLAN server + 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized query result: `<documented facts and characterization observations>`.
- Official GOG 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized query result: `<documented facts and characterization observations>`.
## Verdict and next step

- `[ ] Pass` `[ ] Fail` `[x] Not-run`
- Least-feasible next step: run the smallest valid `PopP2PPacket` probe in both lanes, then add only the documented boundary or lifecycle observation needed to explain a difference.
