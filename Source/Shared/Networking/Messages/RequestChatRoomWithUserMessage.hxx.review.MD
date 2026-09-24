# Fresh review — RequestChatRoomWithUserMessage.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read all 31 lines and ICHAT guard.

## Inspection notes
- Request ID, target user ID and nullable room snapshot are initialized. Null response represents absent target; client checks before dereferencing.
- Server creates two-member relation before notifying either participant and reuses a two-member room when found. Same request ID/target field is sent to both participants, so recipient-specific listener semantics need API/SERVER review.
- Incoming request still decodes a room pointer graph the server does not use. Full response snapshot includes all chat history, covered by BASE-NET-001/006 respectively.

## Result
No independent constructor/field-order defect. Self-chat and stale one-member room semantics are open caller-policy questions, not asserted security defects.

## Second-read evidence addendum

The previously open recipient-correlation question is now **ADD-NET-004 (Medium, High confidence, Correctness)**, fully documented in `RequestChatRoomMessagesMessage.hxx.review.MD`; this reference adds no separate count. `ServerHandlers.cxx:222-242` sends both participants the requester's ID and target-user field; `Chat.cxx:47-69` treats either copy as a local request result. The target therefore sees itself as interlocutor and can lose a colliding pending room listener. Use recipient-specific notifications distinct from request replies and verify with aligned process-local IDs.

This schema's unused incoming room graph also supplies the precise cyclic-ownership rejection case added to **BASE-NET-001** in `Networking.hxx.review.MD`. Null checks after successful decoding cannot release a cycle created before a truncated archive throws. Both additions were traced through the actual cereal pointer registry and Client/Server consumers, not inferred from shared_ptr syntax alone.
