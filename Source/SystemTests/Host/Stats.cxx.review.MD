# Fresh review — Host/Stats.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–216. Static review.

## Inspection notes
- Reviewed stats retrieve/store listener identities, integer/float/achievement persistence writer and reader, and cross-peer stats/achievement/user-data propagation.
- Durable reader checks nonzero unlock time, exact finite float and bit representation. Runner serializes hosts sharing identity/persistence group; writer initial-state checks avoid accepting a dirty preseeded result.
- Propagation uses a rich-presence barrier after store, then performs actual remote requests and checks the retrieved values. Shared networking uses one reliable channel and immediate server serialization for these messages, supporting the stated request-order premise for the local provider.
- The durable writer exits via `_Exit` after the store callback; this exercises store-completion durability across process lifetime, not clean Shutdown flushing or server restart.
- Mixed state snapshots were traced through UserHelloDataMessage and RequestSpecificUserDataMessage; the server copies complete containers. No loop/shared_ptr snapshot alias was found.

## Result
No independent confirmed defect. Offline/stale snapshot, concurrent update and abrupt server identity cleanup coverage remains limited.
