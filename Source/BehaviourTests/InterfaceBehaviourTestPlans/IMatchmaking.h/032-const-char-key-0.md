# `virtual void DeleteLobbyMemberData(GalaxyID lobbyID, const char* key) = 0;`

## Declaration and applicability

- Header: `IMatchmaking.h`
- Exact declaration/signature:
```cpp
virtual void DeleteLobbyMemberData(GalaxyID lobbyID, const char* key) = 0;
```
- Observed snapshot availability: 1.57.0, 1.60.0, 1.61.0, 1.64.0, 1.66.0, 1.67.0, 1.68.0, 1.69.0, 1.70.0, 1.72.0, 1.73.0, 1.74.0, 1.75.0, 1.76.0, 1.77.0, 1.80.0, 1.87.0, 1.92.0, 1.95.0, 1.99.0, 1.100.2, 1.104.2, 1.104.3, 1.104.4, 1.106.0, 1.109.0, 1.112.2, 1.113.1, 1.113.3, 1.114.9, 1.121.2, 1.124.0.
- Relevant build matrix gate: No dedicated feature gate; compile only where this exact declaration is present.
- Existing coverage: No grounded existing coverage identified in `Source/BehaviourTests/COVERAGE.md`.

## Fact boundary

- Documented fact: the selected public header declares the signature above. Any adjacent header precondition, return description, or callback statement may be asserted verbatim.
- Characterization required: result values, error category, callback delivery/count/order/thread, timing, cross-client visibility, pointer lifetime, and behavior for inputs not explicitly documented. Do not promote these observations to SDK guarantees.

## Expected observations

- Observe public state before and after `DeleteLobbyMemberData`, one repeated/idempotency characterization, and cleanup/reversal only where the API exposes it.
- A successful scheduling/result value, callback timing, propagation, or repetition is not assumed unless documented.

## Public-SDK-only plan

1. Establish a legal public target, snapshot the relevant public pre-state, invoke `DeleteLobbyMemberData` once, and record its immediate result/error plus any documented terminal listener.
2. Reissue the same legal mutation only as characterization; compare public pre/post state without assuming idempotency or propagation timing.
3. Use the documented inverse, leave, close, delete, or shutdown path when available. Bound pumping, destroy listeners before shutdown, and redact all temporary values.

## Result placeholders

- UniverseLAN server + 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized mutation result: `<documented facts and characterization observations>`.
- Official GOG 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized mutation result: `<documented facts and characterization observations>`.
## Verdict and next step

- `[ ] Pass` `[ ] Fail` `[x] Not-run`
- Least-feasible next step: run the smallest valid `DeleteLobbyMemberData` probe in both lanes, then add only the documented boundary or lifecycle observation needed to explain a difference.
