# `virtual uint32_t GetFileCount() = 0;`

## Declaration and applicability

- Header: `IStorage.h`
- Exact declaration/signature:
```cpp
virtual uint32_t GetFileCount() = 0;
```
- Observed snapshot availability: 1.92.0, 1.95.0, 1.99.0, 1.100.2, 1.104.2, 1.104.3, 1.104.4, 1.106.0, 1.109.0, 1.112.2, 1.113.1, 1.113.3, 1.114.9, 1.121.2, 1.124.0, 1.125.2, 1.126.1, 1.127.0, 1.128.3, 1.130.0, 1.131.3, 1.132.1, 1.133.0, 1.133.6, 1.134.8, 1.134.9, 1.134.10, 1.135.0, 1.138.0, 1.139.2, 1.139.5, 1.139.6, 1.139.9, 1.140.0, 1.142.0, 1.144.1, 1.148.1, 1.148.2, 1.148.3, 1.148.5, 1.148.6, 1.148.7, 1.148.11, 1.148.14, 1.149.0, 1.150.0, 1.151.0, 1.152.1, 1.152.2, 1.152.6, 1.152.9, 1.152.11.
- Relevant build matrix gate: GALAXY_BUILD_FEATURE_HAS_ISTORAGE.
- Existing coverage: two `storage-file-count` x64 `1.152.11` two-lane characterizations on 2026-09-16 recorded a repeatable storage-state candidate difference; no strict contract is registered.

## Fact boundary

- Documented fact: the selected header returns the number of files in storage.
- Characterization required: the count and immediate error category. Do not promote observations to SDK guarantees.

## Expected observations

- Two runs retained only storage availability, a zero/nonzero count relation, and immediate error category.
- Official had a nonzero relation and UniverseLAN an empty relation for both profiles, with no error in either lane. This is storage-state candidate evidence only.

## Public-SDK-only plan

1. After successful sign-in and before any storage operation, call the method once and inspect `GetError()` immediately.
2. Retain only zero/nonzero, never the count or any file identity/content.
3. Treat the result as storage state unless an independently controlled public fixture establishes comparable contents.

## Result placeholders

- UniverseLAN server + 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; empty relation and no error in two characterizations.
- Official GOG 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; nonzero relation and no error in two characterizations.
## Verdict and next step

- `[ ] Pass` `[ ] Fail` `[x] Not-run`
- Least-feasible next step: provide an independently controlled storage fixture before testing enumeration or comparing count. Do not classify this candidate as a defect or modify implementation code.
