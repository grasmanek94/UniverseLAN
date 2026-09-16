# `virtual bool IsUserDataAvailable(GalaxyID userID = GalaxyID()) = 0;`

## Declaration and applicability

- Header: `IUser.h`
- Exact declaration/signature:
```cpp
virtual bool IsUserDataAvailable(GalaxyID userID = GalaxyID()) = 0;
```
- Observed snapshot availability: 1.113.3, 1.114.9, 1.121.2, 1.124.0, 1.125.2, 1.126.1, 1.127.0, 1.128.3, 1.130.0, 1.131.3, 1.132.1, 1.133.0, 1.133.6, 1.134.8, 1.134.9, 1.134.10, 1.135.0, 1.138.0, 1.139.2, 1.139.5, 1.139.6, 1.139.9, 1.140.0, 1.142.0, 1.144.1, 1.148.1, 1.148.2, 1.148.3, 1.148.5, 1.148.6, 1.148.7, 1.148.11, 1.148.14, 1.149.0, 1.150.0, 1.151.0, 1.152.1, 1.152.2, 1.152.6, 1.152.9, 1.152.11.
- Relevant build matrix gate: No dedicated feature gate; compile only where this exact declaration is present.
- Existing coverage: runtime-blocked in a key-free default-self 2026-09-16 two-lane attempt, which exited before trace output. No behavior result is classified. See [header coverage](HEADER_COVERAGE.md).

## Fact boundary

- Documented fact: user data must first be retrieved with `RequestUserData()`, and default `GalaxyID()` targets own data.
- Characterization required: callback delivery, immediate error category, and availability value. Do not promote observations to SDK guarantees.

## Expected observations

- Use only default-self request/availability forms after successful sign-in.
- Retain only API availability, bounded callback terminal/self relation, availability, and immediate error category.

## Public-SDK-only plan

1. Construct a per-operation `ISpecificUserDataListener`, call `RequestUserData()` with default `GalaxyID()`, and pump to a bounded deadline.
2. Only after callback completion, call `IsUserDataAvailable()` with default `GalaxyID()` and compare callback user to public self without retaining either ID.
3. Do not use explicit peer IDs, keys, values, counts, global listeners, or mutations; destroy the listener before shutdown.

## Result placeholders

- UniverseLAN server + 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized options result: `<documented facts and characterization observations>`.
- Official GOG 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized options result: `<documented facts and characterization observations>`.
## Verdict and next step

- `[ ] Pass` `[ ] Fail` `[x] Not-run`
- Least-feasible next step: run the key-free default-self request/availability probe in both lanes. Do not infer key, value, count, peer, or mutation semantics.
