# `virtual const char* GetCurrentGameLanguageCode(ProductID productID = 0) = 0;`

## Declaration and applicability

- Header: `IApps.h`
- Exact declaration/signature:
```cpp
virtual const char* GetCurrentGameLanguageCode(ProductID productID = 0) = 0;
```
- Observed snapshot availability: 1.151.0, 1.152.1, 1.152.2, 1.152.6, 1.152.9, 1.152.11.
- Relevant build matrix gate: GALAXY_BUILD_FEATURE_HAS_IAPPS_LANGUAGECODE.
- Existing coverage: two `current-game-language-code` x64 `1.152.11` two-lane characterizations on 2026-09-16 recorded a repeatable immediate-error candidate difference; no strict contract is registered.

## Fact boundary

- Documented fact: default product ID `0` means the base game and the returned code consists of ISO-639 language and ISO-3166 country codes, for example `en-US`.
- Characterization required: nullability, exact code text, immediate error category, and pointer lifetime. Do not promote observations to SDK guarantees.

## Expected observations

- Two runs retained only `IApps` availability, non-nullability, the documented five-character shape relation, and immediate error category.
- Both lanes returned a non-null documented-shape result for both profiles; official reported `runtime-error` and UniverseLAN no error. This is a candidate difference only.

## Public-SDK-only plan

1. After successful sign-in, call the method once with default base-game ID, inspect the immediate result only for non-nullability and documented shape, then inspect `GetError()`.
2. Retain no code text or pointer. Do not infer pointer lifetime from this probe.
3. Characterize an independently justified public lifecycle form before deciding whether any narrow strict contract is warranted.

## Result placeholders

- UniverseLAN server + 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; non-null documented-shape result and no error in two characterizations.
- Official GOG 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; non-null documented-shape result and `runtime-error` in two characterizations.
## Verdict and next step

- `[ ] Pass` `[ ] Fail` `[x] Not-run`
- Least-feasible next step: characterize one independent public lifecycle form. Do not classify a defect or modify implementation code from immediate-error evidence alone.
