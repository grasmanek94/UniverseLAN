# `virtual void OnNotificationReceived(NotificationID notificationID, uint32_t typeLength, uint32_t contentSize) = 0;`

## Declaration and applicability

- Header: `IUtils.h`
- Exact declaration/signature:
```cpp
virtual void OnNotificationReceived(NotificationID notificationID, uint32_t typeLength, uint32_t contentSize) = 0;
```
- Observed snapshot availability: 1.95.0, 1.99.0, 1.100.2, 1.104.2, 1.104.3, 1.104.4, 1.106.0, 1.109.0, 1.112.2, 1.113.1, 1.113.3, 1.114.9, 1.121.2, 1.124.0, 1.125.2, 1.126.1, 1.127.0, 1.128.3, 1.130.0, 1.131.3, 1.132.1, 1.133.0, 1.133.6, 1.134.8, 1.134.9, 1.134.10, 1.135.0, 1.138.0, 1.139.2, 1.139.5, 1.139.6, 1.139.9, 1.140.0, 1.142.0, 1.144.1, 1.148.1, 1.148.2, 1.148.3, 1.148.5, 1.148.6, 1.148.7, 1.148.11, 1.148.14, 1.149.0, 1.150.0, 1.151.0, 1.152.1, 1.152.2, 1.152.6, 1.152.9, 1.152.11.
- Relevant build matrix gate: GALAXY_BUILD_FEATURE_HAS_IUTILS.
- Existing coverage: fixture- and runtime-blocked through `RegisterForNotification`; no callback delivery is observed. See [header coverage](HEADER_COVERAGE.md).

## Fact boundary

- Documented fact: callback parameters supply a notification ID and type/content lengths.
- Characterization required: delivery, multiplicity, ordering, and all parameter values. Do not promote observations to SDK guarantees.

## Expected observations

- A controlled public notification source is absent, and current registration forms exit before trace output in both lanes.
- Do not infer no-delivery or callback behavior from the blocked registration attempts.

## Public-SDK-only plan

1. Do not construct a notification listener in the current runtime form.
2. First provide a controlled public notification source and resolve the registration pre-trace exit in both lanes.
3. Never manufacture an ID, type, length, payload, or callback event.

## Result placeholders

- UniverseLAN server + 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized listener result: `<documented facts and characterization observations>`.
- Official GOG 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized listener result: `<documented facts and characterization observations>`.
## Verdict and next step

- `[ ] Pass` `[ ] Fail` `[x] Not-run`
- Least-feasible next step: provide a controlled notification fixture after resolving registration. Do not classify a difference or modify implementation code from the current blocker.
