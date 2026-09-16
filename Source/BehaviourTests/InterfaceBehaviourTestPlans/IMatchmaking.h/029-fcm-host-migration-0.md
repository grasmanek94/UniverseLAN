# `virtual void CreateLobby(LobbyType lobbyType, uint32_t maxMembers, bool joinable = true, LobbyTopologyType lobbyTopologyType = LOBBY_TOPOLOGY_TYPE_FCM_HOST_MIGRATION) = 0;`

## Declaration and applicability

- Header: `IMatchmaking.h`
- Exact declaration/signature:
```cpp
virtual void CreateLobby(LobbyType lobbyType, uint32_t maxMembers, bool joinable = true, LobbyTopologyType lobbyTopologyType = LOBBY_TOPOLOGY_TYPE_FCM_HOST_MIGRATION) = 0;
```
- Observed snapshot availability: 1.80.0.
- Relevant build matrix gate: No dedicated feature gate; compile only where this exact declaration is present.
- Existing coverage: Grounded existing coverage: `Source/BehaviourTests/COVERAGE.md` describes scenarios using public `IMatchmaking::CreateLobby`.

## Fact boundary

- Documented fact: the selected public header declares the signature above. Any adjacent header precondition, return description, or callback statement may be asserted verbatim.
- Characterization required: result values, error category, callback delivery/count/order/thread, timing, cross-client visibility, pointer lifetime, and behavior for inputs not explicitly documented. Do not promote these observations to SDK guarantees.

## Expected observations

- `CreateLobby` is treated as an asynchronous request when the signature/header supplies a listener or later public state; the terminal callback/result/state and bounded timeout are separate observations.
- No success, failure reason, callback count, or ordering is predicted unless the header documents it.

## Public-SDK-only plan

1. Register the specific/global listener before invoking `CreateLobby`, establish a causal two-client readiness gate when a peer is involved, and record the immediate public result/error.
2. Pump only the public processing API to a bounded deadline; record one or more terminal callback arguments, terminal public state, and timeout as separate normalized observations.
3. Repeat only documented boundary/invalid/state forms, characterize duplicates/order without asserting them, destroy listeners before shutdown, and clean up any temporary public object.

## Result placeholders

- UniverseLAN server + 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized async result: `<documented facts and characterization observations>`.
- Official GOG 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized async result: `<documented facts and characterization observations>`.
## Verdict and next step

- `[ ] Pass` `[ ] Fail` `[x] Not-run`
- Least-feasible next step: run the smallest valid `CreateLobby` probe in both lanes, then add only the documented boundary or lifecycle observation needed to explain a difference.
