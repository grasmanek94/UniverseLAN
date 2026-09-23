# Fresh review — RequestLobbyListMessage.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read all 28 lines.

## Inspection notes
- Dual request/response DTO includes a map of tagged lobby IDs to nullable shared models, plus request ID/error. All constructors initialize each field.
- Server replaces request map and resets error; client filters locally, checks null map values and skips nonjoinable lobbies.
- Whole-map serialization lacks paging. History inside each lobby amplifies response size even for discovery, covered by BASE-NET-006 rather than counting every enclosing schema separately.

## Result
No independent constructor/layout defect. Request-side map decoding before policy is part of BASE-NET-001. Visibility/private-lobby policy belongs to server/API review.
