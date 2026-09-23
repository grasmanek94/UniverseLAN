# Fresh review — CreateLobbyMessage.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read all 33 lines.

## Inspection notes
- Request ID, type, capacity, joinable and topology are all initialized and serialized in matching order. Topology fallback keeps the field present on older SDKs.
- Server derives owner from authenticated peer, not from this payload. It forwards enum/capacity values into LobbyManager with no range checks; zero capacity can coexist with the constructor-added owner, and modern SDK documents a 250-member limit.
- Structural serialization cannot enforce admission policy; malformed enum/bool and numeric validation belong to decode/handler boundaries. No standalone serializer defect is inferred from a passive DTO.

## Result
No independent message-local defect. Server-side capacity validation is a concrete handoff in NET.MD; schema/version admission is BASE-NET-005.
