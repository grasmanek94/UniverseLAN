# `virtual uint32_t GetDownloadedSharedFileCount() = 0;`

## Declaration and applicability

- Header: `IStorage.h`
- Exact declaration/signature:
```cpp
virtual uint32_t GetDownloadedSharedFileCount() = 0;
```
- Observed snapshot availability: 1.92.0, 1.95.0, 1.99.0, 1.100.2, 1.104.2, 1.104.3, 1.104.4, 1.106.0, 1.109.0, 1.112.2, 1.113.1, 1.113.3, 1.114.9, 1.121.2, 1.124.0, 1.125.2, 1.126.1, 1.127.0, 1.128.3, 1.130.0, 1.131.3, 1.132.1, 1.133.0, 1.133.6, 1.134.8, 1.134.9, 1.134.10, 1.135.0, 1.138.0, 1.139.2, 1.139.5, 1.139.6, 1.139.9, 1.140.0, 1.142.0, 1.144.1, 1.148.1, 1.148.2, 1.148.3, 1.148.5, 1.148.6, 1.148.7, 1.148.11, 1.148.14, 1.149.0, 1.150.0, 1.151.0, 1.152.1, 1.152.2, 1.152.6, 1.152.9, 1.152.11.
- Relevant build matrix gate: GALAXY_BUILD_FEATURE_HAS_ISTORAGE.
- Existing coverage: `storage-downloaded-shared-file-count` passed its first x64 `1.152.11` two-lane comparison on 2026-09-16 (1.19 seconds).

## Fact boundary

- Documented fact: the selected public header declares the signature above. Any adjacent header precondition, return description, or callback statement may be asserted verbatim.
- Characterization required: result values, error category, callback delivery/count/order/thread, timing, cross-client visibility, pointer lifetime, and behavior for inputs not explicitly documented. Do not promote these observations to SDK guarantees.

## Expected observations

- Initial, valid, and documented invalid/state calls are distinct observations; do not assign a result where the header does not specify one.
- For index, size, buffer, pointer, or copy forms, record in-range/out-of-range, zero/exact/undersized buffer, and documented owner/lifetime relations only when the signature supports them.

## Public-SDK-only plan

1. After sign-in and before any shared-file operation, call `GetDownloadedSharedFileCount` once in each isolated host.
2. Require public `Storage()` availability and zero open downloaded shared files in both lanes. Do not issue download, close, read, write, delete, share, synchronization, or enumeration calls.
3. Retain only the availability and initial-zero relations; never retain shared-file IDs, names, content, counts, credentials, or runtime data.

## Result placeholders

- UniverseLAN server + 2 clients: `[ ] Not-run` `[x] Pass` `[ ] Fail`; storage available with no open downloaded shared files.
- Official GOG 2 clients: `[ ] Not-run` `[x] Pass` `[ ] Fail`; storage available with no open downloaded shared files.
## Verdict and next step

- `[x] Pass` `[ ] Fail` `[ ] Not-run`
- Evidence: focused two-lane CTest passed in 1.19 seconds on 2026-09-16 with no product difference observed.
