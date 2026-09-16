# `virtual uint32_t GetChatRoomMessageByIndex(uint32_t index, ChatRoomID& chatRoomID, ChatMessageID& messageID, GalaxyID& senderID, uint32_t& sendTime, char* buffer, uint32_t bufferLength) = 0;`

## Declaration and applicability

- Header: `IChat.h`
- Exact declaration/signature:
```cpp
virtual uint32_t GetChatRoomMessageByIndex(uint32_t index, ChatRoomID& chatRoomID, ChatMessageID& messageID, GalaxyID& senderID, uint32_t& sendTime, char* buffer, uint32_t bufferLength) = 0;
```
- Observed snapshot availability: 1.104.3.
- Relevant build matrix gate: GALAXY_BUILD_FEATURE_HAS_ICHAT_ROOMID_IN_INDEX.
- Existing coverage: No grounded existing coverage identified: `Source/BehaviourTests/COVERAGE.md` does not directly name this exact `IChat::GetChatRoomMessageByIndex` overload.

## Fact boundary

- Documented fact: the selected public header declares the signature above. Any adjacent header precondition, return description, or callback statement may be asserted verbatim.
- Characterization required: result values, error category, callback delivery/count/order/thread, timing, cross-client visibility, pointer lifetime, and behavior for inputs not explicitly documented. Do not promote these observations to SDK guarantees.

## Expected observations

- Availability, callback-local peek/read, buffer boundary, sender/channel/index relation, and consumption after read/pop are distinct observations when this signature supports them.
- A peek is not treated as consuming, and delivery is never inferred from scheduling alone.

## Public-SDK-only plan

1. Arm the documented listener before sending one bounded opaque public payload, or use the documented polling path without a listener; synchronize sender/receiver with a causal gate.
2. At availability/callback, perform only the read/peek/pop form declared by `GetChatRoomMessageByIndex`, using documented exact/undersized boundaries. Record success, symbolic sender/channel/message relation, and whether a subsequent availability query changes.
3. Do not mix listener-mode and polling-mode semantics. Destroy listeners, leave/close temporary public state, and shut down within bounded cleanup.

## Result placeholders

- UniverseLAN server + 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized message-read result: `<documented facts and characterization observations>`.
- Official GOG 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized message-read result: `<documented facts and characterization observations>`.
## Verdict and next step

- `[ ] Pass` `[ ] Fail` `[x] Not-run`
- Least-feasible next step: run the smallest valid `GetChatRoomMessageByIndex` probe in both lanes, then add only the documented boundary or lifecycle observation needed to explain a difference.
