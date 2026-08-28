# Review: `Source/Shared/Networking/Messages`

## Scope

The 33 message headers are small wire-format value types. The handler
execution model is important: `RunNetworking()` queues ENet events and
`ProcessEvents()` later invokes handlers, normally from `ProcessData()`. The
messages are therefore not themselves evidence that handlers run on the ENet
worker, but their fields still cross the network trust boundary and must be
validated.

## Verified findings

### High — network-controlled collection sizes are not bounded

`Networking.hxx` deserializes message archives directly from peer-controlled
bytes. Several message fields contain strings, vectors, maps, or nested message
objects, and no per-message or archive-wide size budget is enforced before
allocation. A peer can send a structurally valid packet with extreme lengths
and exhaust memory or monopolize deserialization.

**Suggested fix:** impose explicit limits for every variable-length field,
reject oversized archives before allocation, and test malformed/truncated
packets as well as large valid packets.

### Medium — request/response fields are lost or initialized incorrectly

- `RequestChatRoomMessagesMessage::serialize()` omits `oldest_message`, so the
  requested history boundary is not preserved on the wire.
- Its `{ nullptr }` initializer creates a one-element vector containing a null
  `shared_ptr`, not an empty response vector.
- `RequestLobbyListMessage::serialize()` omits `error`, so a response failure
  is deserialized as the default success value.
- `RequestSpecificUserDataMessage` accepts a `RequestType` but initializes
  `type` to `RequestTypeUserData` instead of the argument.
- Feature-off `LeaveLobbyMessage` leaves its fallback `bool reason`
  uninitialized, so a default message can serialize indeterminate data.

**Suggested fix:** make constructors initialize from their parameters, include
all protocol fields in `serialize()`, use `{}` for empty containers, and give
fallback fields deterministic values.

### Medium — null payloads can invoke undefined behavior

`P2PNetworkPacketMessage` constructs a range from `data` to `data +
data_length` without validating `data`. A null pointer is invalid for pointer
arithmetic even when the length is zero; a non-zero length is also an invalid
buffer contract.

**Suggested fix:** reject null buffers before constructing the vector, or
represent an empty payload without pointer arithmetic and validate non-empty
payloads at every API boundary.

### Medium — handler/API error paths are not explicit

Unknown `RequestSpecificUserDataMessage::type` values fall through without a
compatibility error, and the handler layer does not consistently expose
unsupported protocol values to callers. This can make SDK/version mismatches
look like successful no-ops.

**Suggested fix:** log and return a documented unsupported result for unknown
types, while retaining forward-compatible handling where the Galaxy contract
requires it.

## Related state and lifetime findings

The message types expose mutable public state, so they are only safe to share
without locks when ownership and mutation are controlled by the caller. The
state they update has separate findings in `ChatRoom.cxx`, `Lobby.cxx`,
`LobbyManager.cxx`, and `ClientNetworkHandlers.cxx`: chat/lobby histories have
no retention cap, deletion writes an empty value instead of erasing a key, and
`GetLobbies()` exposes an internal map reference. Those are state-container
issues, not a claim that every message handler runs concurrently.

## Recommended order

1. Bound archive allocations and validate payload pointers.
2. Correct the omitted/defaulted protocol fields and feature-off initialization.
3. Make unsupported request values observable and add round-trip tests for every
   message type.
