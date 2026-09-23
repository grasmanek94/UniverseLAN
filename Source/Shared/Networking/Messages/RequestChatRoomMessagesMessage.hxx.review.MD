# Fresh review — RequestChatRoomMessagesMessage.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read all 36 lines and feature guard.

## Inspection notes
- Request ID, room ID, limit, exclusive oldest reference and vector of shared messages are initialized in all four constructors. Response overloads either preserve reference explicitly or intentionally default it to zero.
- Server requires room membership before retrieving history. `ChatRoom::GetMessages` returns an empty vector for an unknown reference and caps slicing arithmetic.
- Limit zero means all matching history and there is no byte budget; history growth is BASE-NET-006. Null vector elements are legal to cereal, while Client Chat dereferences them; API-owner validation handoff recorded in NET.MD.
- Live-message notifications share this schema with request replies, requiring careful listener correlation by consumers.

## Result
No independent field-initialization defect counted. Structural parse success is not proof of message-graph validity.
