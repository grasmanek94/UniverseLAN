# Fresh review — EventDisconnect.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read all 12 lines.

## Inspection notes
- Local marker, not a received wire message; no payload/serializer or owning resource.
- Server handler retires lobbies/chat/user data and mapper state. Client handler clears connection/auth status.
- The actual vendor has an additional timeout-disconnect event that must map to this retirement flow. The omission is in dispatch, not in this empty class (BASE-NET-003).

## Result
No independent marker-type defect. Static Windows lifecycle trace only.
