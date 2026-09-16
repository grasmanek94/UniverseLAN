# `virtual uint32_t GetAchievementsNumber() = 0;`

## Declaration and applicability

- Header: `IStats.h`
- Exact declaration/signature:
```cpp
virtual uint32_t GetAchievementsNumber() = 0;
```
- Observed snapshot availability: 1.152.11.
- Relevant build matrix gate: No dedicated feature gate; compile only where this exact declaration is present.
- Existing coverage: `stats-retrieve-achievements-number` characterization calls the method after successful retrieval but discards its catalog-derived return value. Achievement catalog contents are title configuration, not lane-comparison evidence.

## Fact boundary

- Documented fact: the selected public header declares the signature above. Any adjacent header precondition, return description, or callback statement may be asserted verbatim.
- Characterization required: result values, error category, callback delivery/count/order/thread, timing, cross-client visibility, pointer lifetime, and behavior for inputs not explicitly documented. Do not promote these observations to SDK guarantees.

## Expected observations

- Initial, valid, and documented invalid/state calls are distinct observations; do not assign a result where the header does not specify one.
- For index, size, buffer, pointer, or copy forms, record in-range/out-of-range, zero/exact/undersized buffer, and documented owner/lifetime relations only when the signature supports them.

## Public-SDK-only plan

1. Establish the documented prerequisite state in both lanes, then call `GetAchievementsNumber` initially and after one valid public transition; record only its return/error and public state relation.
2. Where its parameters expose an index, size, buffer, pointer, or copy, run documented boundary forms and retain no raw data. Mark unsupported invalid forms as characterization rather than expected behavior.
3. Repeat public queries around callback pumping only when their source operation is asynchronous; retain/copy results only for the lifetime stated by the header and complete ordinary listener/shutdown cleanup.

## Result placeholders

- UniverseLAN server + 2 clients: `[ ] Not-run` `[x] Pass` `[ ] Fail`; successful self retrieval followed by the query; its return value is excluded.
- Official GOG 2 clients: `[ ] Not-run` `[x] Pass` `[ ] Fail`; successful self retrieval followed by the query; its return value is excluded.
## Verdict and next step

- `[x] Pass` `[ ] Fail` `[ ] Not-run`
- Least-feasible next step: with title-provided known achievement keys, add a read-only symbolic unlocked-state relation. Do not compare catalog count, names, descriptions, or other title data.
