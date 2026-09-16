# `virtual uint32_t GetNotification(NotificationID notificationID, char* type, uint32_t typeLength, void* content, uint32_t contentSize) = 0;`

## Declaration and applicability

- Header: `IUtils.h`
- Exact declaration/signature:
```cpp
virtual uint32_t GetNotification(NotificationID notificationID, char* type, uint32_t typeLength, void* content, uint32_t contentSize) = 0;
```
- Observed snapshot availability: 1.95.0, 1.99.0, 1.100.2, 1.104.2, 1.104.3, 1.104.4, 1.106.0, 1.109.0, 1.112.2, 1.113.1, 1.113.3, 1.114.9, 1.121.2, 1.124.0, 1.125.2, 1.126.1, 1.127.0, 1.128.3.
- Relevant build matrix gate: GALAXY_BUILD_FEATURE_HAS_IUTILS.
- Existing coverage: No grounded existing coverage identified in `Source/BehaviourTests/COVERAGE.md`.

## Fact boundary

- Documented fact: the selected public header declares the signature above. Any adjacent header precondition, return description, or callback statement may be asserted verbatim.
- Characterization required: result values, error category, callback delivery/count/order/thread, timing, cross-client visibility, pointer lifetime, and behavior for inputs not explicitly documented. Do not promote these observations to SDK guarantees.

## Expected observations

- Initial, valid, and documented invalid/state calls are distinct observations; do not assign a result where the header does not specify one.
- For index, size, buffer, pointer, or copy forms, record in-range/out-of-range, zero/exact/undersized buffer, and documented owner/lifetime relations only when the signature supports them.

## Public-SDK-only plan

1. Register the notification type through `RegisterForNotification`, connect a `GlobalNotificationListener`, and retain the `OnNotificationReceived(NotificationID, typeLength, contentSize)` callback ID and lengths.
2. In that callback, call this exact `GetNotification(NotificationID, char*, uint32_t, void*, uint32_t)` overload with buffers related to callback `typeLength` and `contentSize`; record copied lengths.
3. Delivery remains infeasible absent a public event source. Do not manufacture an ID; record registration and no-delivery as the bounded result, then destroy the listener before shutdown.

## Result placeholders

- UniverseLAN server + 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized query result: `<documented facts and characterization observations>`.
- Official GOG 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized query result: `<documented facts and characterization observations>`.
## Verdict and next step

- `[ ] Pass` `[ ] Fail` `[x] Not-run`
- Least-feasible next step: run the smallest valid `GetNotification` probe in both lanes, then add only the documented boundary or lifecycle observation needed to explain a difference.
