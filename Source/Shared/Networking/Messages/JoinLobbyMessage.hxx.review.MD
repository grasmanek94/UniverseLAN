# Fresh review — JoinLobbyMessage.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read all 36 lines.

## Inspection notes
- Dual request/response DTO carries request ID, lobby ID, enter result and optional full snapshot. Defaults are failure and null; overloads initialize all fields.
- Server looks up the authoritative lobby and derives the joining member from peer state. Client uses the returned snapshot, with a placeholder fallback if success lacks one.
- Request-side response fields are still decoded before authentication even though the server replaces them. Direction-specific DTOs would reduce that unnecessary attack surface.
- Joinability is not enforced by Server's current Join handler; the wire message itself cannot enforce it. Snapshot size can prevent a reply after membership mutation (BASE-NET-006).

## Result
No independent field-layout defect. Server admission handoff and transport budget findings are recorded separately; no execution performed.
