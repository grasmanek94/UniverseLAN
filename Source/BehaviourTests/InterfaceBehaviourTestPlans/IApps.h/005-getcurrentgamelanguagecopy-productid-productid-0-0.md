# `virtual void GetCurrentGameLanguageCopy(char* buffer, uint32_t bufferLength, ProductID productID = 0) = 0;`

## Declaration and applicability

- Header: `IApps.h`
- Exact declaration/signature:
```cpp
virtual void GetCurrentGameLanguageCopy(char* buffer, uint32_t bufferLength, ProductID productID = 0) = 0;
```
- Observed snapshot availability: 1.92.0, 1.95.0, 1.99.0, 1.100.2, 1.104.2, 1.104.3, 1.104.4, 1.106.0, 1.109.0, 1.112.2, 1.113.1, 1.113.3, 1.114.9, 1.121.2, 1.124.0, 1.125.2, 1.126.1, 1.127.0, 1.128.3, 1.130.0, 1.131.3, 1.132.1, 1.133.0, 1.133.6, 1.134.8, 1.134.9, 1.134.10, 1.135.0, 1.138.0, 1.139.2, 1.139.5, 1.139.6, 1.139.9, 1.140.0, 1.142.0, 1.144.1, 1.148.1, 1.148.2, 1.148.3, 1.148.5, 1.148.6, 1.148.7, 1.148.11, 1.148.14, 1.149.0, 1.150.0, 1.151.0, 1.152.1, 1.152.2, 1.152.6, 1.152.9, 1.152.11.
- Relevant build matrix gate: GALAXY_BUILD_FEATURE_HAS_IAPPS.
- Existing coverage: two `current-game-language-copy` x64 `1.152.11` two-lane characterizations on 2026-09-16 recorded a repeatable candidate difference for transient one-byte and 256-byte non-null buffers; no strict contract is registered.

## Fact boundary

- Documented fact: `buffer` is an output buffer, `bufferLength` is its size, default product ID `0` means the base game, and the language name is lowercase.
- Characterization required: nullability, zero-length behavior, capacity, truncation, termination, pointer/buffer lifetime, error category, and exact language text. Do not promote observations to SDK guarantees.

## Expected observations

- Both lanes were probed with only one-byte and 256-byte non-null sentinel-filled buffers. Null and zero-length forms were intentionally excluded because the header does not define them.
- Official GOG twice reported `runtime-error` and left both buffers unchanged; UniverseLAN twice reported no error and changed/terminated both. This is a candidate difference for those forms, not a general copy guarantee.

## Public-SDK-only plan

1. After successful sign-in, call the method once per selected non-null buffer form with the default base-game product ID and inspect `GetError()` immediately after each call.
2. Retain only changed/terminated/lowercase-property booleans and error categories, then clear the transient buffers before trace emission.
3. Do not use null, zero-length, canary, overflow, or title/DLC-ID forms. Characterize another independently justified non-null form before deciding whether any narrow strict contract is warranted.

## Result placeholders

- UniverseLAN server + 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; no error plus changed/terminated buffers in two characterizations.
- Official GOG 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; `runtime-error` plus unchanged buffers in two characterizations.
## Verdict and next step

- `[ ] Pass` `[ ] Fail` `[x] Not-run`
- Least-feasible next step: characterize one additional independently justified non-null buffer form. Do not classify a defect, register a strict test, or modify implementation code from the current two-form evidence.
