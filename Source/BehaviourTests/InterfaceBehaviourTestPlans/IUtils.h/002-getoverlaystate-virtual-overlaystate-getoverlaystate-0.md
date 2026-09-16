# `virtual OverlayState GetOverlayState() = 0;`

## Declaration and applicability

- Header: `IUtils.h`
- Exact declaration/signature:
```cpp
virtual OverlayState GetOverlayState() = 0;
```
- Observed snapshot availability: 1.104.2, 1.104.3, 1.104.4, 1.106.0, 1.109.0, 1.112.2, 1.113.1, 1.113.3, 1.114.9, 1.121.2, 1.124.0, 1.125.2, 1.126.1, 1.127.0, 1.128.3, 1.130.0, 1.131.3, 1.132.1, 1.133.0, 1.133.6, 1.134.8, 1.134.9, 1.134.10, 1.135.0, 1.138.0, 1.139.2, 1.139.5, 1.139.6, 1.139.9, 1.140.0, 1.142.0, 1.144.1, 1.148.1, 1.148.2, 1.148.3, 1.148.5, 1.148.6, 1.148.7, 1.148.11, 1.148.14, 1.149.0, 1.150.0, 1.151.0, 1.152.1, 1.152.2, 1.152.6, 1.152.9, 1.152.11.
- Relevant build matrix gate: GALAXY_BUILD_FEATURE_HAS_IUTILS.
- Existing coverage: two `overlay-state` x64 `1.152.11` two-lane characterizations on 2026-09-16 recorded a repeatable environment-dependent candidate difference; no strict contract is registered.

## Fact boundary

- Documented fact: the selected header defines the five returned overlay states and states that successful initialization depends on user enablement and successful injection.
- Characterization required: current enum value and immediate error category. Do not promote observations to SDK guarantees.

## Expected observations

- Two runs retained only `IUtils` availability, a documented enum category, and immediate error category.
- Official reported `undefined` and UniverseLAN `disabled` for both profiles, with no error in either lane. This is an environment-dependent candidate only.

## Public-SDK-only plan

1. After successful sign-in, call the method once and normalize only to the documented enum category, then inspect `GetError()` immediately.
2. Do not invoke visibility, display, or notification-control methods unless their documented overlay-initialization precondition is established.
3. Treat overlay state as environment configuration unless an independently controlled public fixture demonstrates otherwise.

## Result placeholders

- UniverseLAN server + 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; `disabled` and no error in two characterizations.
- Official GOG 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; `undefined` and no error in two characterizations.
## Verdict and next step

- `[ ] Pass` `[ ] Fail` `[x] Not-run`
- Least-feasible next step: obtain an independently controlled overlay-initialization fixture before testing APIs that require initialization. Do not classify this candidate as a defect or modify implementation code.
