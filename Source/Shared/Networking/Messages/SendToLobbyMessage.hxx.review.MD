# Fresh review — SendToLobbyMessage.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read all 31 lines.

## Inspection notes
- Carries lobby ID and a value-owned Lobby::Message (ID, sender, binary-safe string). Defaults zero-initialize nested scalar fields.
- Server requires actual membership and replaces both sender and message ID; client cannot claim another lobby sender through those fields on the normal path.
- Client construction supplies explicit byte length, and Lobby::GetMsg uses binary copying, preserving embedded nulls. Variable string length still needs decode budgeting before handlers.

## Result
No independent field/ownership defect established. Unbounded retained messages and full-snapshot consequences are BASE-NET-006; no packet-size compliance test was run.
