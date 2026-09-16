# `virtual void RequestFriendInvitationList() = 0;`

## Declaration and applicability

- Header: `IFriends.h`
- Exact declaration/signature:
```cpp
virtual void RequestFriendInvitationList() = 0;
```
- Observed snapshot availability: 1.104.3, 1.104.4, 1.106.0, 1.109.0, 1.112.2, 1.113.1, 1.113.3, 1.114.9, 1.121.2, 1.124.0, 1.125.2.
- Relevant build matrix gate: No dedicated feature gate; compile only where this exact declaration is present.
- Existing coverage: No grounded existing coverage identified in `Source/BehaviourTests/COVERAGE.md`.

## Fact boundary

- Documented fact: the selected public header declares the signature above. Any adjacent header precondition, return description, or callback statement may be asserted verbatim.
- Characterization required: result values, error category, callback delivery/count/order/thread, timing, cross-client visibility, pointer lifetime, and behavior for inputs not explicitly documented. Do not promote these observations to SDK guarantees.

## Expected observations

- `RequestFriendInvitationList` is treated as an asynchronous request when the signature/header supplies a listener or later public state; the terminal callback/result/state and bounded timeout are separate observations.
- No success, failure reason, callback count, or ordering is predicted unless the header documents it.

## Public-SDK-only plan

1. Register the specific/global listener before invoking `RequestFriendInvitationList`, establish a causal two-client readiness gate when a peer is involved, and record the immediate public result/error.
2. Pump only the public processing API to a bounded deadline; record one or more terminal callback arguments, terminal public state, and timeout as separate normalized observations.
3. Repeat only documented boundary/invalid/state forms, characterize duplicates/order without asserting them, destroy listeners before shutdown, and clean up any temporary public object.

## Result placeholders

- UniverseLAN server + 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized async result: `<documented facts and characterization observations>`.
- Official GOG 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized async result: `<documented facts and characterization observations>`.
## Verdict and next step

- `[ ] Pass` `[ ] Fail` `[x] Not-run`
- Least-feasible next step: run the smallest valid `RequestFriendInvitationList` probe in both lanes, then add only the documented boundary or lifecycle observation needed to explain a difference.
