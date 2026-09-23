# Fresh review — P2PNetworkPacketMessage.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read all 36 lines.

## Inspection notes
- ID is destination on client send and authenticated sender/lobby on server relay. Channel is explicitly uint8, send type is SDK enum, payload is owned bytes.
- Pointer constructor copies only when non-null; null plus nonzero length becomes an empty packet rather than pointer arithmetic on null. Actual API validation remains caller responsibility.
- Server direct-user relay checks shared active-lobby membership and overwrites sender. Lobby-target relay follows a different branch lacking an equivalent source-membership check; recorded as a SERVER handoff.
- Reliability enum selection is translated to ENet flags; unsupported enum values fall through to default flags, not arbitrary memory indexing.

## Result
No independent constructor/serialization defect established. Unbounded decoding/queues are BASE-NET-001/007 and relay authorization is handler policy.
