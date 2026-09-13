# Found Defects

## Resolved

### Chat send acknowledgement reports failure after delivery

Status: fixed and validated by
`universelan-system-chat-room-message-delivery-x64-1.139.2`.

The server success path stored and broadcast the created message but replied to
the sender with a null message, which the client maps to
`OnChatRoomMessageSendFailure`. It now acknowledges the created message on the
success path; the failure path remains null. The regression SystemTest verifies
the sender success callback and receiver delivery.

### x86 disk-space clamping did not compile

Status: fixed and validated by the `1.139.2` x86 SystemTests.

The disk-space helpers passed `uint64_t` values and `size_t` limits to
`std::min`, which leaves template argument deduction ambiguous on x86 MSVC.
The limits now use `uint64_t` before the checked `uint32_t` narrowing in
[`SharedFileUtils.cxx`](../Shared/SharedFileUtils.cxx).
