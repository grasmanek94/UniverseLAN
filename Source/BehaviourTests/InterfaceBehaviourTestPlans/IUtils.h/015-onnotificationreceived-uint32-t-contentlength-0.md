# `virtual void OnNotificationReceived(uint32_t notificationID, uint32_t typeLength, uint32_t contentLength) = 0;`

## Declaration and applicability

- Header: `IUtils.h`
- Exact declaration/signature:
```cpp
virtual void OnNotificationReceived(uint32_t notificationID, uint32_t typeLength, uint32_t contentLength) = 0;
```
- Observed snapshot availability: 1.75.0, 1.76.0, 1.77.0, 1.80.0, 1.87.0.
- Relevant build matrix gate: GALAXY_BUILD_FEATURE_HAS_IUTILS.
- Existing coverage: No grounded existing coverage identified in `Source/BehaviourTests/COVERAGE.md`.

## Fact boundary

- Documented fact: the selected public header declares the signature above. Any adjacent header precondition, return description, or callback statement may be asserted verbatim.
- Characterization required: result values, error category, callback delivery/count/order/thread, timing, cross-client visibility, pointer lifetime, and behavior for inputs not explicitly documented. Do not promote these observations to SDK guarantees.

## Expected observations

- Registration before the trigger, callback argument relations, multiplicity, same-interface order, destruction, and absence after destruction are independently recorded.
- Delivery, cross-host timing, and cross-interface ordering remain characterization unless the header documents them.

## Public-SDK-only plan

1. Register a type through `RegisterForNotification` and connect the version-matching notification listener; on `OnNotificationReceived(uint32_t, typeLength, contentLength)`, retain only the ID and lengths.
2. Consume that callback ID immediately with the matching `GetNotification(uint32_t, ..., contentLength)` overload and buffers sized from the callback relation.
3. Delivery remains infeasible absent a public event source. Record bounded no-delivery rather than manufacture an event, then destroy the listener before shutdown.

## Result placeholders

- UniverseLAN server + 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized listener result: `<documented facts and characterization observations>`.
- Official GOG 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized listener result: `<documented facts and characterization observations>`.
## Verdict and next step

- `[ ] Pass` `[ ] Fail` `[x] Not-run`
- Least-feasible next step: run the smallest valid `OnNotificationReceived` probe in both lanes, then add only the documented boundary or lifecycle observation needed to explain a difference.
