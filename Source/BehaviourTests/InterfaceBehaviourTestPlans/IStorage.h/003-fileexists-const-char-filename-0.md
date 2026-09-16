# `virtual bool FileExists(const char* fileName) = 0;`

## Declaration and applicability

- Header: `IStorage.h`
- Exact declaration/signature:
```cpp
virtual bool FileExists(const char* fileName) = 0;
```
- Observed snapshot availability: 1.99.0, 1.100.2, 1.104.2, 1.104.3, 1.104.4, 1.106.0, 1.109.0, 1.112.2, 1.113.1, 1.113.3, 1.114.9, 1.121.2, 1.124.0, 1.125.2, 1.126.1, 1.127.0, 1.128.3, 1.130.0, 1.131.3, 1.132.1, 1.133.0, 1.133.6, 1.134.8, 1.134.9, 1.134.10, 1.135.0, 1.138.0, 1.139.2, 1.139.5, 1.139.6, 1.139.9, 1.140.0, 1.142.0, 1.144.1, 1.148.1, 1.148.2, 1.148.3, 1.148.5, 1.148.6, 1.148.7, 1.148.11, 1.148.14, 1.149.0, 1.150.0, 1.151.0, 1.152.1, 1.152.2, 1.152.6, 1.152.9, 1.152.11.
- Relevant build matrix gate: GALAXY_BUILD_FEATURE_HAS_ISTORAGE.
- Existing coverage: two `storage-file-exists` x64 `1.152.11` two-lane characterizations on 2026-09-16 matched a fresh-path absence relation; no strict contract is registered. See [header coverage](HEADER_COVERAGE.md).

## Fact boundary

- Documented fact: the selected header returns whether the given relative-path file exists.
- Characterization required: immediate error category and behavior for a path not created by the application. Do not promote observations to SDK guarantees.

## Expected observations

- Two runs queried one fresh portable relative path per isolated host without creating it. Both lanes reported available storage, absent path, and no error for both profiles.
- The path itself is never retained. This is a repeatable characterization, not a general file-system or storage contract.

## Public-SDK-only plan

1. After successful sign-in, call the method once on a fresh portable relative path generated in memory and never written.
2. Retain only storage availability, existence, and immediate error category; never retain the path.
3. Require an isolated fixture before probing a known existing path or combining this method with any mutating storage call.

## Result placeholders

- UniverseLAN server + 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; available, absent, and no error in two characterizations.
- Official GOG 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; available, absent, and no error in two characterizations.
## Verdict and next step

- `[ ] Pass` `[ ] Fail` `[x] Not-run`
- Least-feasible next step: create an isolated storage fixture before testing a known existing path. Do not classify a defect or modify implementation code from fresh-path evidence alone.
