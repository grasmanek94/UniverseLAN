# Fresh review — KeyChallengeMessage.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read all 78 lines, including protocol comments.

## Inspection notes
- Wire order is challenge/response integer then claimed GalaxyID; both constructors initialize both fields. `challenge` XORs a key hash and nonce; `response` hashes the recovered nonce's native eight-byte representation.
- Traced server Prepare/Validate, seeded PRNG, acceptance/mapping, client response and duplicate-ID rejection. Server-side immediate-disconnect cleanup needs separate owner attention, recorded in NET.MD.
- FNV/XOR is an admission convention, not authenticated encryption; the response does not bind the ID or schema version. Windows x86/x64 are little-endian, so native-byte response hashing agrees there. Cross-endian authentication would not be repaired merely by cereal's numeric byte swapping; no big-endian deployment finding is claimed.
- Default shared key and self-selected IDs are assessed under intentional trusted-LAN semantics. No captured traffic, production config or credentials were consulted; no cryptographic exploit is asserted without a stronger threat model.

## Result
No independent Windows schema-local defect established. Recommend documenting the trust model and using standard keyed authentication if private-key hostile-network admission is a product requirement. Compatibility gating is BASE-NET-005.
