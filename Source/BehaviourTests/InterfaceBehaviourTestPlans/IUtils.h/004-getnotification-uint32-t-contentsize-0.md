# `virtual uint32_t GetNotification(NotificationID notificationID, bool& consumable, char* type, uint32_t typeLength, void* content, uint32_t contentSize) = 0;`

## Declaration and applicability

- Header: `IUtils.h`
- Exact declaration/signature:
```cpp
virtual uint32_t GetNotification(NotificationID notificationID, bool& consumable, char* type, uint32_t typeLength, void* content, uint32_t contentSize) = 0;
```
- Observed snapshot availability: 1.130.0, 1.131.3, 1.132.1, 1.133.0, 1.133.6, 1.134.8, 1.134.9, 1.134.10, 1.135.0, 1.138.0, 1.139.2, 1.139.5, 1.139.6, 1.139.9, 1.140.0, 1.142.0, 1.144.1, 1.148.1, 1.148.2, 1.148.3, 1.148.5, 1.148.6, 1.148.7, 1.148.11, 1.148.14, 1.149.0, 1.150.0, 1.151.0, 1.152.1, 1.152.2, 1.152.6, 1.152.9, 1.152.11.
- Relevant build matrix gate: GALAXY_BUILD_FEATURE_HAS_IUTILS.
- Existing coverage: fixture- and runtime-blocked through `RegisterForNotification`; no notification ID may be manufactured. See [header coverage](HEADER_COVERAGE.md).

## Fact boundary

- Documented fact: the selected overload consumes a notification ID and caller-provided type/content buffers.
- Characterization required: every result and buffer relation. Do not promote observations to SDK guarantees.

## Expected observations

- A valid ID and buffer lengths must come from a genuine public notification callback. Current legal registration forms exit before trace output in both lanes.
- Do not use arbitrary IDs, buffer sizes, or payload data as substitutes.

## Public-SDK-only plan

1. Do not invoke this method until a controlled public notification source provides an ID and lengths.
2. First resolve the current pre-trace registration exit in both lanes.
3. Retain no notification type, ID, payload, or buffer contents.

## Result placeholders

- UniverseLAN server + 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized query result: `<documented facts and characterization observations>`.
- Official GOG 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized query result: `<documented facts and characterization observations>`.
## Verdict and next step

- `[ ] Pass` `[ ] Fail` `[x] Not-run`
- Least-feasible next step: provide a controlled notification fixture after resolving registration. Do not classify a difference or modify implementation code from the current blocker.
