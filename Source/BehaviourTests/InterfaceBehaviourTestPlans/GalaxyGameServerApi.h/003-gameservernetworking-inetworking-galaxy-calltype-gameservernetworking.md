# `GALAXY_DLL_EXPORT INetworking* GALAXY_CALLTYPE GameServerNetworking();`

## Declaration and applicability

- Header: `GalaxyGameServerApi.h`
- Exact declaration/signature:
```cpp
GALAXY_DLL_EXPORT INetworking* GALAXY_CALLTYPE GameServerNetworking();
```
- Observed snapshot availability: 1.121.2, 1.124.0, 1.125.2, 1.126.1, 1.127.0, 1.128.3, 1.130.0, 1.131.3, 1.132.1, 1.133.0, 1.133.6, 1.134.8, 1.134.9, 1.134.10, 1.135.0, 1.138.0, 1.139.2, 1.139.5, 1.139.6, 1.139.9, 1.140.0, 1.142.0, 1.144.1, 1.148.1, 1.148.2, 1.148.3, 1.148.5, 1.148.6, 1.148.7, 1.148.11, 1.148.14, 1.149.0, 1.150.0, 1.151.0, 1.152.1, 1.152.2, 1.152.6, 1.152.9, 1.152.11.
- Relevant build matrix gate: GALAXY_BUILD_FEATURE_GAME_SERVER_API.
- Existing coverage: No grounded existing coverage identified in `Source/BehaviourTests/COVERAGE.md`.

## Fact boundary

- Documented fact: the selected public header declares the signature above. Any adjacent header precondition, return description, or callback statement may be asserted verbatim.
- Characterization required: result values, error category, callback delivery/count/order/thread, timing, cross-client visibility, pointer lifetime, and behavior for inputs not explicitly documented. Do not promote these observations to SDK guarantees.

## Expected observations

- Lifecycle state before/after `GameServerNetworking`, repeated-call characterization, public accessor availability, listener lifetime, and cleanup are recorded separately.
- Initialization/shutdown outcome, factory singleton identity, and callback timing are not assumed beyond header text.

## Public-SDK-only plan

1. From the documented pre-state, invoke `GameServerNetworking` with valid options/credentials supplied outside retained artifacts; immediately inspect only public error/state/accessor relations.
2. Exercise documented repeated, partial-init, or pre/post-lifecycle forms as characterization. For accessors/factories, compare only pointer identity/availability permitted by their public documentation.
3. Pump public processing where documented, destroy self-registering listeners, invoke the matching public shutdown/reset path, and verify the documented post-state without implementation inspection.

## Result placeholders

- UniverseLAN server + 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized lifecycle result: `<documented facts and characterization observations>`.
- Official GOG 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized lifecycle result: `<documented facts and characterization observations>`.
## Verdict and next step

- `[ ] Pass` `[ ] Fail` `[x] Not-run`
- Least-feasible next step: run the smallest valid `GameServerNetworking` probe in both lanes, then add only the documented boundary or lifecycle observation needed to explain a difference.
