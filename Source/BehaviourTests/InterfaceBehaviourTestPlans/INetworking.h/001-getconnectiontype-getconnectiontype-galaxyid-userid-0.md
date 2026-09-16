# `virtual ConnectionType GetConnectionType(GalaxyID userID) = 0;`

## Declaration and applicability

- Header: `INetworking.h`
- Exact declaration/signature:
```cpp
virtual ConnectionType GetConnectionType(GalaxyID userID) = 0;
```
- Observed snapshot availability: 1.114.9, 1.121.2, 1.124.0, 1.125.2, 1.126.1, 1.127.0, 1.128.3, 1.130.0, 1.131.3, 1.132.1, 1.133.0, 1.133.6, 1.134.8, 1.134.9, 1.134.10, 1.135.0, 1.138.0, 1.139.2, 1.139.5, 1.139.6, 1.139.9, 1.140.0, 1.142.0, 1.144.1, 1.148.1, 1.148.2, 1.148.3, 1.148.5, 1.148.6, 1.148.7, 1.148.11, 1.148.14, 1.149.0, 1.150.0, 1.151.0, 1.152.1, 1.152.2, 1.152.6, 1.152.9, 1.152.11.
- Relevant build matrix gate: GALAXY_BUILD_FEATURE_HAS_CONNECTION_TYPE.
- Existing coverage: Implemented as a public observation in `Simple/bidirectional-reliable-p2p-poll-read`; live evidence remains pending.

## Fact boundary

- Documented fact: the selected public header declares the signature above. Any adjacent header precondition, return description, or callback statement may be asserted verbatim.
- Characterization required: result values, error category, callback delivery/count/order/thread, timing, cross-client visibility, pointer lifetime, and behavior for inputs not explicitly documented. Do not promote these observations to SDK guarantees.

## Expected observations

- Initial, valid, and documented invalid/state calls are distinct observations; do not assign a result where the header does not specify one.
- For index, size, buffer, pointer, or copy forms, record in-range/out-of-range, zero/exact/undersized buffer, and documented owner/lifetime relations only when the signature supports them.

## Public-SDK-only plan

1. Reuse the listener-free two-member public-lobby poll/read topology after public membership confirms a valid self and peer user relation.
2. Call `GetConnectionType(self)` and require only the header-documented `CONNECTION_TYPE_DIRECT` relation. Record the peer enum as sanitized `none`, `direct`, or `proxy` characterization context without assuming a cross-lane routing value.
3. Keep the existing synchronized reliable send, polling/read, and terminal lobby cleanup unchanged. Do not introduce a networking listener, opaque ID, payload, or timing assertion.

## Result placeholders

- UniverseLAN server + 2 clients: `[x] Pass` `[ ] Fail`; 2026-09-16 focused `Simple/bidirectional-reliable-p2p-poll-read` matched the self-direct relation for both host roles.
- Official GOG 2 clients: `[x] Pass` `[ ] Fail`; the same focused comparison established the documented self-direct relation for both host roles. Peer routing was retained only as sanitized diagnostic context.
## Verdict and next step

- `[x] Pass` `[ ] Fail` `[ ] Not-run`
- Next step: rerun this listener-free probe when changing peer setup or SDK version; retain peer routing as diagnostic unless repeatable official evidence justifies more.
