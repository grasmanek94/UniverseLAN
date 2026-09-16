# `virtual void GetCurrentGameLanguageCodeCopy(char* buffer, uint32_t bufferLength, ProductID productID = 0) = 0;`

## Declaration and applicability

- Header: `IApps.h`
- Exact declaration/signature:
```cpp
virtual void GetCurrentGameLanguageCodeCopy(char* buffer, uint32_t bufferLength, ProductID productID = 0) = 0;
```
- Observed snapshot availability: 1.151.0, 1.152.1, 1.152.2, 1.152.6, 1.152.9, 1.152.11.
- Relevant build matrix gate: GALAXY_BUILD_FEATURE_HAS_IAPPS.
- Existing coverage: two `current-game-language-code-copy` x64 `1.152.11` two-lane characterizations on 2026-09-16 recorded a repeatable candidate difference for transient one-byte and 256-byte non-null buffers; no strict contract is registered.

## Fact boundary

- Documented fact: `buffer` is an output buffer, `bufferLength` is its size, default product ID `0` means the base game, and the code consists of ISO-639 language and ISO-3166 country codes.
- Characterization required: capacity, truncation, termination, error category, and exact code text. Do not promote observations to SDK guarantees.

## Expected observations

- Both lanes were probed with only one-byte and 256-byte non-null sentinel-filled buffers. Null and zero-length forms were intentionally excluded because the header does not define them.
- Official GOG twice reported `runtime-error` and left both buffers unchanged; UniverseLAN twice reported no error and changed/terminated both. The bounded UniverseLAN form had the documented code shape. This is a candidate difference for those forms, not a general copy guarantee.

## Public-SDK-only plan

1. After successful sign-in, call the method once per selected non-null buffer form with default base-game ID and inspect `GetError()` immediately after each call.
2. Retain only changed/terminated/documented-shape booleans and error categories, then clear transient buffers before trace emission.
3. Do not use null, zero-length, canary, overflow, or title/DLC-ID forms. Characterize another independently justified non-null form before deciding whether any narrow strict contract is warranted.

## Result placeholders

- UniverseLAN server + 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; no error plus changed/terminated buffers in two characterizations.
- Official GOG 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; `runtime-error` plus unchanged buffers in two characterizations.
## Verdict and next step

- `[ ] Pass` `[ ] Fail` `[x] Not-run`
- Least-feasible next step: characterize one additional independently justified non-null buffer form. Do not classify a defect, register a strict test, or modify implementation code from the current two-form evidence.
