# `virtual ~ICloudStorage()`

## Declaration and applicability

- Header: `ICloudStorage.h`
- Exact declaration/signature:
```cpp
virtual ~ICloudStorage()
```
- Observed snapshot availability: 1.148.6, 1.148.7, 1.148.11, 1.148.14, 1.149.0, 1.150.0, 1.151.0, 1.152.1, 1.152.2, 1.152.6, 1.152.9, 1.152.11.
- Relevant build matrix gate: GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE.
- Existing coverage: No grounded existing coverage identified in `Source/BehaviourTests/COVERAGE.md`.

## Fact boundary

- Documented fact: the selected public header declares the signature above. Any adjacent header precondition, return description, or callback statement may be asserted verbatim.
- Characterization required: result values, error category, callback delivery/count/order/thread, timing, cross-client visibility, pointer lifetime, and behavior for inputs not explicitly documented. Do not promote these observations to SDK guarantees.

## Expected observations

- Initial, valid, and documented invalid/state calls are distinct observations; do not assign a result where the header does not specify one.
- For index, size, buffer, pointer, or copy forms, record in-range/out-of-range, zero/exact/undersized buffer, and documented owner/lifetime relations only when the signature supports them.

## Public-SDK-only plan

1. Obtain the interface only through its documented accessor, finish or bound public operations, then use SDK shutdown; do not call `~ICloudStorage` directly.
2. Where its parameters expose an index, size, buffer, pointer, or copy, run documented boundary forms and retain no raw data. Mark unsupported invalid forms as characterization rather than expected behavior.
3. Repeat public queries around callback pumping only when their source operation is asynchronous; retain/copy results only for the lifetime stated by the header and complete ordinary listener/shutdown cleanup.

## Result placeholders

- UniverseLAN server + 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized query result: `<documented facts and characterization observations>`.
- Official GOG 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized query result: `<documented facts and characterization observations>`.
## Verdict and next step

- `[ ] Pass` `[ ] Fail` `[x] Not-run`
- Least-feasible next step: observe the smallest documented accessor/shutdown lifecycle in both lanes, then add only the boundary observation needed to explain a difference.
