# `virtual void RequestUserData(GalaxyID userID = GalaxyID(), ISpecificUserDataListener* const listener = NULL) = 0;`

## Declaration and applicability

- Header: `IUser.h`
- Exact declaration/signature:
```cpp
virtual void RequestUserData(GalaxyID userID = GalaxyID(), ISpecificUserDataListener* const listener = NULL) = 0;
```
- Observed snapshot availability: 1.134.10, 1.139.2, 1.139.5, 1.139.6, 1.139.9, 1.140.0, 1.142.0, 1.144.1, 1.148.1, 1.148.2, 1.148.3, 1.148.5, 1.148.6, 1.148.7, 1.148.11, 1.148.14, 1.149.0, 1.150.0, 1.151.0, 1.152.1, 1.152.2, 1.152.6, 1.152.9, 1.152.11.
- Relevant build matrix gate: GALAXY_BUILD_FEATURE_USER_DATA_LISTENERS.
- Existing coverage: No grounded existing coverage identified in `Source/BehaviourTests/COVERAGE.md`.

## Fact boundary

- Documented fact: the selected public header declares the signature above. Any adjacent header precondition, return description, or callback statement may be asserted verbatim.
- Characterization required: result values, error category, callback delivery/count/order/thread, timing, cross-client visibility, pointer lifetime, and behavior for inputs not explicitly documented. Do not promote these observations to SDK guarantees.

## Expected observations

- Constructor/default field values, explicit field effects, copy/value lifetime, and use by the documented lifecycle call are separate observations.
- No option interpretation beyond the header's parameter and field documentation is expected.

## Public-SDK-only plan

1. Call `RequestUserData` once omitting both default `GalaxyID()` and listener, then with an explicit `GalaxyID` and retained `ISpecificUserDataListener`.
2. Pump the public processing API to a bounded deadline; compare terminal callback and public data observations without assuming delivery or the default-target relation.
3. Keep the listener alive through completion, then unregister/destroy it and complete ordinary shutdown cleanup.

## Result placeholders

- UniverseLAN server + 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized options result: `<documented facts and characterization observations>`.
- Official GOG 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized options result: `<documented facts and characterization observations>`.
## Verdict and next step

- `[ ] Pass` `[ ] Fail` `[x] Not-run`
- Least-feasible next step: run the smallest valid `GalaxyID` probe in both lanes, then add only the documented boundary or lifecycle observation needed to explain a difference.
