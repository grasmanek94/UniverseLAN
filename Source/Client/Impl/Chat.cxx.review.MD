# Chat.cxx — fresh baseline review

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Windows-focused static review; all 400 lines read. No build or runtime test executed.

## File-specific inspection

Reviewed room creation/reuse, request-listener registration and completion, send acknowledgement, live/history message delivery, duplicate suppression, callback-local indexing, member enumeration and unread/read accounting. Traced `ClientNetworkHandlers.cxx`, `Server/ServerHandlers.cxx:214-299`, Shared chat objects and message serialization, `MessageUniqueID`, and the listener registrar. Contract reference: `Source/DLLs/1.152.11/galaxy/IChat.h`.

The response owns its message vector throughout ordinary synchronous callbacks. Cached messages are copied, and history insertion compares message IDs before increasing the cached message count. Sending copies message text before returning. The full-message-length return from `GetChatRoomMessageByIndex` is consistent with the SDK's “actual message size” contract even when the destination is truncated. Out-of-range indexing and calling that getter outside its documented callback scope are not treated as supported-input crashes. The remaining borrowed-view lifetime question is documented separately in `Chat.hxx.review.MD` as BASE-API-018, an informational investigation.

## Findings

### [BASE-API-001] Live chat notifications can complete an unrelated history request

- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Client/Impl/Chat.cxx:108-148`, `RequestChatRoomMessagesProcessed`.
- **Affected scope:** Chat SDK versions with history retrieval listeners; per-operation misdelivery additionally requires operation-specific listeners.

**Evidence.** The handler unconditionally pops an `IChatRoomMessagesRetrieveListener` using `data->request_id` and calls `OnChatRoomMessagesRetrieveSuccess`, followed by `OnChatRoomMessagesReceived`. `Source/Server/ServerHandlers.cxx:245-260` sends history responses in `RequestChatRoomMessagesMessage`; lines 284-294 also use that same message for live fan-out, carrying the sender's send-request ID. `Source/Shared/Networking/Messages/RequestChatRoomMessagesMessage.hxx:16-25` contains no response/event discriminator. `Source/Shared_NoVer/Networking/MessageUniqueID.cxx:8-21` allocates IDs from a process-local counter starting at one. The SDK distinguishes history-request responses (`IChat.h:154-185,216-231`) from new-message notifications (`126-143,233-251`).

**Failure mechanism.** Even without an outstanding history request, every live message generates a history-success notification for globally registered retrieval listeners. More seriously, recipient B can have a pending history request numbered N while sender A sends a live message numbered N. If A's notification reaches B before the history response, B pops its history listener and completes it with the live batch (possibly from another room). The actual history response then has no operation-specific listener. This requires neither malformed packets nor malicious peers.

**Impact.** History pagination receives the wrong batch or room, completes prematurely, and loses its actual completion. Global retrieval listeners observe successes for operations never requested.

**Alternatives / recommended resolution.** Prefer separate live-event and history-response message types, or an explicit serialized message kind with response IDs meaningful only to the requester. Track outstanding history requests including room identity even when no operation-specific listener was supplied. Deliver retrieval callbacks only for matched history responses; deliver live notifications through the live path. Merely checking for a non-null popped listener would break legitimate global-listener requests and does not solve cross-process ID collisions.

**Verification.** Register a global history listener, receive a live message without requesting history, and expect no history completion. Then coordinate two clients so a live send and the recipient's pending history request share an ID; deliver the live event first, including a different-room case. Verify exactly one history completion with the requested room/batch and one independent live notification. Not executed.
