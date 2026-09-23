# Fresh review — Challenge.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–22. Static review.

## Inspection notes
- Followed `Prepare` into `KeyChallengeMessage::challenge/response`: the protocol sends `key XOR random` and expects the FNV-1a hash of the decoded random value. This is shared LAN-key agreement, not GOG account authentication.
- The expressions returning references from temporary messages are copied during the same full expression; no dangling-reference use was found at these assignments.
- `Validate` sets `completed` on challenge equality before identity registration. The actual server immediately resets rejected transports, so this flag alone does **not** demonstrate that a duplicate-ID peer can continue sending authorized operations.
- The missing application cleanup on that rejection is confirmed as **BASE-SERVER-001**, fully described in `ServerHandlers.cxx.review.MD`. The effective-key console disclosure is **BASE-SERVER-016** in `Server.cxx.review.MD`.

## Result
No additional independent defect. Cryptographic strength of the intentionally lightweight LAN protocol is not represented as a reproduced compromise.
