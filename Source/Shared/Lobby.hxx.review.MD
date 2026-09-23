# Fresh review — Lobby.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read all 125 lines; Windows static review.

## Inspection notes
- Checked every serialized field, ID/hash use, owner/member representation, data index types and the borrowed members view. No internal mutex: server relies on its single event loop; client callers must hold their owning Matchmaking lock.
- `user_data` doubles as membership; whole-member-data replacement is therefore a membership operation. Owner, capacity, topology and joinability are independently assignable, so server admission must enforce invariants.
- The serializer uses fixed-width counts/IDs but SDK enums and native bool. Byte-order conversion is provided by cereal, while SDK schema compatibility belongs to the transport handshake.

### [BASE-NET-006] Unbounded message history is embedded in routine room/lobby snapshots
- **Severity:** Medium
- **Confidence:** High
- **Category:** Performance
- **Location:** `Source/Shared/Lobby.hxx:48-59`; `Lobby.cxx:232-250`; parallel chat storage in `ChatRoom.hxx:23,57-60` and `ChatRoom.cxx:72-104`.
- **Affected scope:** Windows server room storage and client/server lobby-list, join, data and chat-room snapshots.

**Evidence / failure mechanism:** Every lobby message is retained in `messages` with no removal or byte budget. The ordinary Lobby serializer includes that entire map. `ServerHandlers.cxx:537-540,577-580,628-630` serializes full lobby objects for lists, joins and data, and hello synchronization also sends them. ChatRoom similarly retains and serializes its full message vector; requesting an existing room serializes all history even though a separate paged-history request exists. ENet rejects a packet over 32 MiB.

**Reproduction conditions:** Keep a lobby alive while a member sends 1,024 messages of 32,768 bytes (or equivalent accumulated payload); individual messages fit the transport. Request the lobby list, data, or join afterward. History alone reaches 32 MiB and framing exceeds the cap. A list can also cross the cap through multiple smaller lobbies. Re-requesting a long-lived chat room has the analogous path.

**Impact:** Memory/serialization work grows with session lifetime; routine replies eventually stop being deliverable. A server join can already have changed membership before its oversized reply fails. Failed single-peer replies additionally leak through BASE-NET-004, but this history design would remain broken even after that leak is fixed.

**Alternatives / recommended resolution:** Separate discovery/current-state DTOs from history. Page history with explicit byte/count budgets, retaining it in a bounded or persistent store according to the SDK contract; do not silently evict messages callers are promised they can retrieve. Limit serialized response size before allocating a full output packet, and make state-changing operations handle send failure.

**Verification:** On Windows accumulate history beyond 32 MiB across one and several rooms. Assert bounded discovery/join response size, successful paging, correct message IDs/order and explicit failures instead of silent membership divergence. Profile retained memory and serialization work. Not executed here.
