# `virtual void RequestUserStatsAndAchievements(GalaxyID userID = GalaxyID(), IUserStatsAndAchievementsRetrieveListener* const listener = NULL) = 0;`

## Declaration and applicability

- Header: `IStats.h`
- Exact declaration/signature:
```cpp
virtual void RequestUserStatsAndAchievements(GalaxyID userID = GalaxyID(), IUserStatsAndAchievementsRetrieveListener* const listener = NULL) = 0;
```
- Observed snapshot availability: 1.125.2, 1.126.1, 1.127.0, 1.128.3, 1.130.0, 1.131.3, 1.132.1, 1.133.0, 1.133.6, 1.134.8, 1.134.9, 1.134.10, 1.135.0, 1.138.0, 1.139.2, 1.139.5, 1.139.6, 1.139.9, 1.140.0, 1.142.0, 1.144.1, 1.148.1, 1.148.2, 1.148.3, 1.148.5, 1.148.6, 1.148.7, 1.148.11, 1.148.14, 1.149.0, 1.150.0, 1.151.0, 1.152.1, 1.152.2, 1.152.6, 1.152.9, 1.152.11.
- Relevant build matrix gate: No dedicated feature gate; compile only where this exact declaration is present.
- Existing coverage: `stats-retrieve-self-callback` passed its first x64 `1.152.11` two-lane comparison on 2026-09-16 (1.37 seconds). The separate count characterization remains configuration-dependent.

## Fact boundary

- Documented fact: the selected public header declares the signature above. Any adjacent header precondition, return description, or callback statement may be asserted verbatim.
- Characterization required: result values, error category, callback delivery/count/order/thread, timing, cross-client visibility, pointer lifetime, and behavior for inputs not explicitly documented. Do not promote these observations to SDK guarantees.

## Expected observations

- Constructor/default field values, explicit field effects, copy/value lifetime, and use by the documented lifecycle call are separate observations.
- No option interpretation beyond the header's parameter and field documentation is expected.

## Public-SDK-only plan

1. Call `RequestUserStatsAndAchievements` once omitting both default `GalaxyID()` and listener, then with an explicit `GalaxyID` and retained `IUserStatsAndAchievementsRetrieveListener`.
2. Pump the public processing API to a bounded deadline; compare terminal callback and public retrieval observations without assuming delivery or the default-target relation.
3. Keep the listener alive through completion, then unregister/destroy it and complete ordinary shutdown cleanup.

## Result placeholders

- UniverseLAN server + 2 clients: `[ ] Not-run` `[x] Pass` `[ ] Fail`; successful default-self retrieval with callback user equal to public self.
- Official GOG 2 clients: `[ ] Not-run` `[x] Pass` `[ ] Fail`; successful default-self retrieval with callback user equal to public self.
## Verdict and next step

- `[x] Pass` `[ ] Fail` `[ ] Not-run`
- Evidence: two matching characterizations followed by the focused two-lane CTest pass on 2026-09-16. Catalog contents are excluded; a later title-fixture probe may compare only symbolic unlocked-state relations.
