# `virtual const char* GetCurrentGameLanguage(ProductID productID = 0) = 0;`

## Declaration and applicability

- Header: `IApps.h`
- Exact declaration/signature:
```cpp
virtual const char* GetCurrentGameLanguage(ProductID productID = 0) = 0;
```
- Observed snapshot availability: 1.92.0, 1.95.0, 1.99.0, 1.100.2, 1.104.2, 1.104.3, 1.104.4, 1.106.0, 1.109.0, 1.112.2, 1.113.1, 1.113.3, 1.114.9, 1.121.2, 1.124.0, 1.125.2, 1.126.1, 1.127.0, 1.128.3, 1.130.0, 1.131.3, 1.132.1, 1.133.0, 1.133.6, 1.134.8, 1.134.9, 1.134.10, 1.135.0, 1.138.0, 1.139.2, 1.139.5, 1.139.6, 1.139.9, 1.140.0, 1.142.0, 1.144.1, 1.148.1, 1.148.2, 1.148.3, 1.148.5, 1.148.6, 1.148.7, 1.148.11, 1.148.14, 1.149.0, 1.150.0, 1.151.0, 1.152.1, 1.152.2, 1.152.6, 1.152.9, 1.152.11.
- Relevant build matrix gate: GALAXY_BUILD_FEATURE_HAS_GETCURRENTGAMELANGUAGE.
- Existing coverage: `Simple/current-game-language` passed two characterizations and its first x64 `1.152.11` two-lane comparison on 2026-09-16 (1.21 seconds).

## Fact boundary

- Documented fact: product ID `0` means the base game and the returned language name is lowercase.
- Characterization required: pointer lifetime, exact language text, nullability, cross-lane text equality, and behavior for inputs not explicitly documented. Do not promote these observations to SDK guarantees.

## Expected observations

- The two-lane probe records only `IApps` availability, non-null result, and absence of ASCII uppercase characters. It does not retain the language text or pointer.
- Both official and UniverseLAN profiles satisfied those sanitized relations in two characterizations and the first focused comparison.

## Public-SDK-only plan

1. After successful sign-in, call `GetCurrentGameLanguage()` once with the default base-game product ID in each isolated host.
2. Retain only availability, nullability, and the documented lowercase-property relation; discard the returned text and pointer immediately.
3. Keep `GetCurrentGameLanguageCopy` and `GetCurrentGameLanguageCode` as separate API plans; do not infer their buffer or value semantics here.

## Result placeholders

- UniverseLAN server + 2 clients: `[ ] Not-run` `[x] Pass` `[ ] Fail`; `IApps` available, result non-null, no ASCII uppercase retained.
- Official GOG 2 clients: `[ ] Not-run` `[x] Pass` `[ ] Fail`; `IApps` available, result non-null, no ASCII uppercase retained.
## Verdict and next step

- `[x] Pass` `[ ] Fail` `[ ] Not-run`
- Least-feasible next step: characterize `GetCurrentGameLanguageCopy` separately with only documented buffer forms and no retained language text.
