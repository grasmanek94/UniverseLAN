# `static IGalaxy* CreateInstance();`

## Declaration and applicability

- Header: `GalaxyFactory.h`
- Exact declaration/signature:
```cpp
static IGalaxy* CreateInstance();
```
- Observed snapshot availability: 1.57.0, 1.60.0, 1.61.0, 1.64.0, 1.66.0.
- Relevant build matrix gate: GALAXY_BUILD_FEATURE_HAS_IGALAXY.
- Existing coverage: No grounded existing coverage identified in `Source/BehaviourTests/COVERAGE.md`.

## Fact boundary

- Documented fact: the selected public header declares the signature above. Any adjacent header precondition, return description, or callback statement may be asserted verbatim.
- Characterization required: result values, error category, callback delivery/count/order/thread, timing, cross-client visibility, pointer lifetime, and behavior for inputs not explicitly documented. Do not promote these observations to SDK guarantees.

## Expected observations

- Lifecycle state before/after `CreateInstance`, repeated-call characterization, public accessor availability, listener lifetime, and cleanup are recorded separately.
- Initialization/shutdown outcome, factory singleton identity, and callback timing are not assumed beyond header text.

## Public-SDK-only plan

1. From the documented pre-state, invoke `CreateInstance` with valid options/credentials supplied outside retained artifacts; immediately inspect only public error/state/accessor relations.
2. Exercise documented repeated, partial-init, or pre/post-lifecycle forms as characterization. For accessors/factories, compare only pointer identity/availability permitted by their public documentation.
3. Pump public processing where documented, destroy self-registering listeners, invoke the matching public shutdown/reset path, and verify the documented post-state without implementation inspection.

## Result placeholders

- UniverseLAN server + 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized lifecycle result: `<documented facts and characterization observations>`.
- Official GOG 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized lifecycle result: `<documented facts and characterization observations>`.
## Verdict and next step

- `[ ] Pass` `[ ] Fail` `[x] Not-run`
- Least-feasible next step: run the smallest valid `CreateInstance` probe in both lanes, then add only the documented boundary or lifecycle observation needed to explain a difference.
