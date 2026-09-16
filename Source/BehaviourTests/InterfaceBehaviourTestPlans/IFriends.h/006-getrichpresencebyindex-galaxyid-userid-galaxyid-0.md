# `virtual bool GetRichPresenceByIndex(uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength, GalaxyID userID = GalaxyID()) = 0;`

## Declaration and applicability

- Header: `IFriends.h`
- Exact declaration/signature:
```cpp
virtual bool GetRichPresenceByIndex(uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength, GalaxyID userID = GalaxyID()) = 0;
```
- Observed snapshot availability: 1.74.0, 1.75.0, 1.76.0, 1.77.0, 1.80.0, 1.87.0, 1.92.0, 1.95.0, 1.99.0, 1.100.2, 1.104.2, 1.104.3, 1.104.4, 1.106.0, 1.109.0, 1.112.2, 1.113.1, 1.113.3, 1.114.9, 1.121.2, 1.124.0, 1.125.2, 1.126.1.
- Relevant build matrix gate: No dedicated feature gate; compile only where this exact declaration is present.
- Existing coverage: No grounded existing coverage identified in `Source/BehaviourTests/COVERAGE.md`.

## Fact boundary

- Documented fact: the selected public header declares the signature above. Any adjacent header precondition, return description, or callback statement may be asserted verbatim.
- Characterization required: result values, error category, callback delivery/count/order/thread, timing, cross-client visibility, pointer lifetime, and behavior for inputs not explicitly documented. Do not promote these observations to SDK guarantees.

## Expected observations

- Constructor/default field values, explicit field effects, copy/value lifetime, and use by the documented lifecycle call are separate observations.
- No option interpretation beyond the header's parameter and field documentation is expected.

## Public-SDK-only plan

1. Establish self and explicit-peer rich-presence records where public setup permits, then call `GetRichPresenceByIndex` with the default `GalaxyID()` and each explicit `GalaxyID`.
2. Query index and key/value buffer boundaries separately for each target; record return value and copied fields without assuming the undocumented default-target relation.
3. Retain buffers through each call and complete ordinary shutdown cleanup.

## Result placeholders

- UniverseLAN server + 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized options result: `<documented facts and characterization observations>`.
- Official GOG 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized options result: `<documented facts and characterization observations>`.
## Verdict and next step

- `[ ] Pass` `[ ] Fail` `[x] Not-run`
- Least-feasible next step: run the smallest valid `GalaxyID` probe in both lanes, then add only the documented boundary or lifecycle observation needed to explain a difference.
