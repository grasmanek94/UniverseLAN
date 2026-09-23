# Fresh review — Peer.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–136. Static review.

## Inspection notes
- Traced `ENetPeer::data` ownership from `Mapper::Connect`/`new Data` to `Mapper::Disconnect`/delete and `Data::~Data` map erasure.
- The GalaxyID map stores a reusable ENet slot pointer, and `Get(id)` dereferences the slot's **current** data. There is no generation or ID-equality check. Correctness therefore depends on complete cleanup before every slot reuse: **BASE-SERVER-002** in `Server.cxx.review.MD` demonstrates the violated invariant.
- Failed challenge cleanup is **BASE-SERVER-001** in `ServerHandlers.cxx.review.MD`; a subsequent connect clears the old pointer before allocation, leaking the previous Data.
- Duplicate IDs are rejected by `map.emplace`; ordinary destruction of an unlinked ID-zero Data does not erase another valid identity. Lobby map add/remove and steady-clock activity accounting were inspected.
- `Get(peer)` asserts a non-null attachment even though some callers defensively test its result. Normal connected/disconnect paths were traced rather than labeling the assertion itself a vulnerability.

## Result
No additional independent finding beyond the lifecycle defects linked above. Server shutdown does not explicitly sweep remaining raw Data objects; the executable's ordinary lifetime ends with process termination, so this is recorded as an ownership limitation rather than a separate high-severity leak.
