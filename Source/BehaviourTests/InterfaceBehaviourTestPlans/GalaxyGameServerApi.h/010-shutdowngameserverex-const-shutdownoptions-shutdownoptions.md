# `GALAXY_DLL_EXPORT void GALAXY_CALLTYPE ShutdownGameServerEx(const ShutdownOptions& shutdownOptions);`

## Declaration and applicability

- Header: `GalaxyGameServerApi.h`
- Exact declaration/signature:
```cpp
GALAXY_DLL_EXPORT void GALAXY_CALLTYPE ShutdownGameServerEx(const ShutdownOptions& shutdownOptions);
```
- Observed snapshot availability: 1.151.0, 1.152.1, 1.152.2, 1.152.6, 1.152.9, 1.152.11.
- Relevant build matrix gate: GALAXY_BUILD_FEATURE_HAS_SHUTDOWNOPTIONS.
- Existing coverage: No grounded existing coverage identified in `Source/BehaviourTests/COVERAGE.md`.

## Fact boundary

- Documented fact: the selected public header declares the signature above. Any adjacent header precondition, return description, or callback statement may be asserted verbatim.
- Characterization required: result values, error category, callback delivery/count/order/thread, timing, cross-client visibility, pointer lifetime, and behavior for inputs not explicitly documented. Do not promote these observations to SDK guarantees.

## Expected observations

- Lifecycle state before/after `ShutdownGameServerEx`, repeated-call characterization, public accessor availability, listener lifetime, and cleanup are recorded separately.
- Initialization/shutdown outcome, factory singleton identity, and callback timing are not assumed beyond header text.

## Public-SDK-only plan

1. From the documented pre-state, invoke `ShutdownGameServerEx` with valid options/credentials supplied outside retained artifacts; immediately inspect only public error/state/accessor relations.
2. Exercise documented repeated, partial-init, or pre/post-lifecycle forms as characterization. For accessors/factories, compare only pointer identity/availability permitted by their public documentation.
3. Pump public processing where documented, destroy self-registering listeners, invoke the matching public shutdown/reset path, and verify the documented post-state without implementation inspection.

## Result placeholders

- UniverseLAN server + 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized lifecycle result: `<documented facts and characterization observations>`.
- Official GOG 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized lifecycle result: `<documented facts and characterization observations>`.
## Verdict and next step

- `[ ] Pass` `[ ] Fail` `[x] Not-run`
- Least-feasible next step: run the smallest valid `ShutdownGameServerEx` probe in both lanes, then add only the documented boundary or lifecycle observation needed to explain a difference.
