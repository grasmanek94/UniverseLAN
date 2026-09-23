# Fresh review — LobbyMemberStateChangeMessage.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read all 30 lines.

## Inspection notes
- Lobby ID, member ID and state enum are serialized in fixed order; defaults denote disconnected rather than an uninitialized state.
- Server emits notifications from authenticated join/leave processing; its handler ignores client-supplied notifications after authentication. Client updates local membership through Matchmaking.
- SDK enum values are not validated by cereal. Treating any frame with a known class ID as trusted state requires a trusted server and schema agreement.

## Result
No independent schema-local defect established. Lifecycle retirement omission is BASE-NET-003 at the ENet event boundary, not this application message.
