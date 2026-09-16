# `virtual const char* GetRichPresenceKeyByIndex(uint32_t index, GalaxyID userID = GalaxyID()) = 0;`

## Declaration and applicability

- Header: `IFriends.h`
- Exact declaration/signature:
```cpp
virtual const char* GetRichPresenceKeyByIndex(uint32_t index, GalaxyID userID = GalaxyID()) = 0;
```
- Observed snapshot availability: 1.148.2, 1.148.3, 1.148.5, 1.148.6, 1.148.7, 1.148.11, 1.148.14, 1.149.0, 1.150.0, 1.151.0, 1.152.1, 1.152.2, 1.152.6, 1.152.9, 1.152.11.
- Relevant build matrix gate: No dedicated feature gate; compile only where this exact declaration is present.
- Existing coverage: No grounded existing coverage identified in `Source/BehaviourTests/COVERAGE.md`.

## Fact boundary

- Documented fact: the selected public header declares the signature above. Any adjacent header precondition, return description, or callback statement may be asserted verbatim.
- Characterization required: result values, error category, callback delivery/count/order/thread, timing, cross-client visibility, pointer lifetime, and behavior for inputs not explicitly documented. Do not promote these observations to SDK guarantees.

## Expected observations

- Constructor/default field values, explicit field effects, copy/value lifetime, and use by the documented lifecycle call are separate observations.
- No option interpretation beyond the header's parameter and field documentation is expected.

## Public-SDK-only plan

1. Establish self and explicit-peer rich-presence records where public setup permits, then call `GetRichPresenceKeyByIndex` with the default `GalaxyID()` and each explicit `GalaxyID`.
2. Query in-range and out-of-range indexes separately for each target; record returned-key lifetime and values only as documented.
3. Treat the default-target relation as characterization and complete ordinary shutdown cleanup.

## Result placeholders

- UniverseLAN server + 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized options result: `<documented facts and characterization observations>`.
- Official GOG 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized options result: `<documented facts and characterization observations>`.
## Verdict and next step

- `[ ] Pass` `[ ] Fail` `[x] Not-run`
- Least-feasible next step: run the smallest valid `GalaxyID` probe in both lanes, then add only the documented boundary or lifecycle observation needed to explain a difference.
