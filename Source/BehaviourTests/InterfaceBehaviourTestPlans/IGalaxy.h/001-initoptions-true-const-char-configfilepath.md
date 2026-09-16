# `InitOptions(const char* _clientID, const char* _clientSecret, const char* _galaxyPeerPath = "", bool _throwExceptions = true, const char* _configFilePath = ".")`

## Declaration and applicability

- Header: `IGalaxy.h`
- Exact declaration/signature:
```cpp
InitOptions(const char* _clientID, const char* _clientSecret, const char* _galaxyPeerPath = "", bool _throwExceptions = true, const char* _configFilePath = ".")
```
- Observed snapshot availability: 1.87.0, 1.92.0, 1.95.0, 1.99.0, 1.100.2, 1.104.2, 1.104.3, 1.104.4, 1.106.0, 1.109.0, 1.112.2, 1.113.1, 1.113.3, 1.114.9.
- Relevant build matrix gate: GALAXY_BUILD_FEATURE_HAS_IGALAXY.
- Existing coverage: No grounded existing coverage identified in `Source/BehaviourTests/COVERAGE.md`.

## Fact boundary

- Documented fact: the selected public header declares the signature above. Any adjacent header precondition, return description, or callback statement may be asserted verbatim.
- Characterization required: result values, error category, callback delivery/count/order/thread, timing, cross-client visibility, pointer lifetime, and behavior for inputs not explicitly documented. Do not promote these observations to SDK guarantees.

## Expected observations

- Constructor/default field values, explicit field effects, copy/value lifetime, and use by the documented lifecycle call are separate observations.
- No option interpretation beyond the header's parameter and field documentation is expected.

## Public-SDK-only plan

1. Construct `InitOptions` with defaults and with one documented explicit field at a time; inspect only public fields/value semantics exposed by the struct or class.
2. Pass each legal form to its documented consuming lifecycle call, then characterize any observable public state/error effect without assuming a backend outcome.
3. Keep caller-owned strings, allocator/thread callbacks, and options alive for the documented lifetime; destroy listeners and perform normal shutdown cleanup.

## Result placeholders

- UniverseLAN server + 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized options result: `<documented facts and characterization observations>`.
- Official GOG 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized options result: `<documented facts and characterization observations>`.
## Verdict and next step

- `[ ] Pass` `[ ] Fail` `[x] Not-run`
- Least-feasible next step: run the smallest valid `InitOptions` probe in both lanes, then add only the documented boundary or lifecycle observation needed to explain a difference.
