# `virtual void AddRequestLobbyListNumericalFilter(const char* keyToMatch, int32_t valueToMatch, LobbyComparisonType comparisonType) = 0;`

## Declaration and applicability

- Header: `IMatchmaking.h`
- Exact declaration/signature:
```cpp
virtual void AddRequestLobbyListNumericalFilter(const char* keyToMatch, int32_t valueToMatch, LobbyComparisonType comparisonType) = 0;
```
- Observed snapshot availability: 1.57.0, 1.60.0, 1.61.0, 1.64.0, 1.66.0, 1.67.0, 1.68.0, 1.69.0, 1.70.0, 1.72.0, 1.73.0, 1.74.0, 1.75.0, 1.76.0, 1.77.0, 1.80.0, 1.87.0, 1.92.0, 1.95.0, 1.99.0, 1.100.2, 1.104.2, 1.104.3, 1.104.4, 1.106.0, 1.109.0, 1.112.2, 1.113.1, 1.113.3, 1.114.9, 1.121.2, 1.124.0, 1.125.2, 1.126.1, 1.127.0, 1.128.3, 1.130.0, 1.131.3, 1.132.1, 1.133.0, 1.133.6, 1.134.8, 1.134.9, 1.134.10, 1.135.0, 1.138.0, 1.139.2, 1.139.5, 1.139.6, 1.139.9, 1.140.0, 1.142.0, 1.144.1, 1.148.1, 1.148.2, 1.148.3, 1.148.5, 1.148.6, 1.148.7, 1.148.11, 1.148.14, 1.149.0, 1.150.0, 1.151.0, 1.152.1, 1.152.2, 1.152.6, 1.152.9, 1.152.11.
- Relevant build matrix gate: No dedicated feature gate; compile only where this exact declaration is present.
- Existing coverage: `Simple/public-lobby-numerical-filtering` passed its first live x64 `1.152.11` two-lane run on 2026-09-16 (9.76 seconds).

## Fact boundary

- Documented fact: the selected public header declares the signature above. Any adjacent header precondition, return description, or callback statement may be asserted verbatim.
- Characterization required: result values, error category, callback delivery/count/order/thread, timing, cross-client visibility, pointer lifetime, and behavior for inputs not explicitly documented. Do not promote these observations to SDK guarantees.

## Expected observations

- Observe public state before and after `AddRequestLobbyListNumericalFilter`, one repeated/idempotency characterization, and cleanup/reversal only where the API exposes it.
- A successful scheduling/result value, callback timing, propagation, or repetition is not assumed unless documented.

## Public-SDK-only plan

1. User1 sequentially creates two temporary public capacity-two FCM lobbies nonjoinable, writes fixed distinct numerical properties and one shared token-derived run marker, then makes each joinable only after configuration completes.
2. User2 applies `AddRequestLobbyListNumericalFilter(..., LOBBY_COMPARISON_TYPE_EQUAL)` with the target numerical property plus the shared run-marker string filter. It retrieves and privately classifies callback-local candidates, selects and joins only the numerical target, verifies public two-member/non-self-owner state, then leaves.
3. Require target appearance, numerical predicate match, absence of the run-owned numerical nonmatch, target-only selection/join, and cleanup in both lanes. Retain the unmatched boolean and bounded list retries as diagnostic context, excluding them from cross-lane equality. Never retain numeric values, marker/token values, IDs, counts, indexes, timestamps, or runtime data.

## Result placeholders

- UniverseLAN server + 2 clients: `[ ] Not-run` `[x] Pass` `[ ] Fail`; matched strict comparison on 2026-09-16.
- Official GOG 2 clients: `[ ] Not-run` `[x] Pass` `[ ] Fail`; matched strict comparison on 2026-09-16.
## Verdict and next step

- `[x] Pass` `[ ] Fail` `[ ] Not-run`
- Evidence: opt-in two-lane CTest passed in 9.76 seconds on 2026-09-16; no product difference was observed.
