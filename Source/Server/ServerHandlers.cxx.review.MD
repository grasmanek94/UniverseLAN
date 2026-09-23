# Fresh review — ServerHandlers.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–1054. Static Windows-focused review.

## Inspection notes
- Traced challenge arithmetic, duplicate-ID admission, hello/stat snapshots, user/rich-presence changes, chat room creation/history/send/leave, both P2P routes, file policies/persistence, all lobby operations and disconnect cleanup.
- Protected handlers return on failed authentication. EventConnect/EventDisconnect are not wire-message dispatch cases in `Messages.hxx`; a forged application message cannot directly invoke these lifecycle handlers.
- User snapshots copy the full stats container and server-bound identity; `Send` serializes synchronously, so reusing `member_data` across the loop does not send all peers the final iteration's data.
- Lobby data edits enforce ownership; member data rewrites the member ID and `Lobby::SetMemberData` checks membership; lobby messages and chat reads/sends check membership. Direct user-addressed P2P requires an active shared lobby on both peers.
- Ordinary owner leave removes the departing member before choosing a successor, updates server ownership, and sends owner-change before leave notification. FCM/STAR close removes remaining peers' lobby references and the manager entry. The live keys view is not invalidated by those peer-map removals. The server packet supplied by a client cannot set owner directly.
- Chat history cursor/limit behavior is implemented in the shared room; lack of offline durable chat or invitation-account services is not independently classified as a severe defect.
- Timeout-driven slot reuse is **BASE-SERVER-002** in `Server.cxx.review.MD`.

### [BASE-SERVER-001] Rejected authentication resets transport without releasing application peer state

- **Severity:** Medium
- **Confidence:** High
- **Category:** Memory Safety
- **Location:** `Source/Server/ServerHandlers.cxx:77–130`, especially line 129; replacement attachment at lines 40–45.
- **Affected scope:** Wrong-key, invalid-ID and duplicate-ID connection attempts.

**Evidence.** Failure calls only `connection.Disconnect(peer)`. `Enet++/src/enetpp.cxx:132–135` uses `enet_peer_disconnect_now` and reset; `Enet-IPv6/src/peer.c:506–536` explicitly produces no local disconnect event. Data deletion and set removal exist only in the server EventDisconnect path / Mapper::Disconnect. ENet reset does not free application `data`.

**Failure mechanism.** Rejection leaves Data and set entries until a sweep. If the slot is reused first, EventConnect clears the old pointer, then allocates a new Data, permanently losing the previous allocation. Repeated failed handshakes reuse transport slots and can repeat this leak; the connection limit therefore does not bound accumulated Data allocations.

**Impact.** Unauthenticated connection churn causes persistent heap growth; stale entries also complicate lifecycle accounting. This does not prove challenge-completed peers can send after rejection: the transport is immediately reset and its queued commands are discarded.

**Alternatives / recommendation.** Route every forced rejection through a single idempotent application-cleanup-then-transport-reset operation, as the sweeps already do. A Mapper-owned RAII registry is an alternative but still must remove memberships and identity records before reuse. Commit admission state only after identity registration succeeds.

**Verification.** Repeatedly reject and reconnect on one ENet slot faster than the 60-second sweep. Track Data construction/destruction and set membership; verify bounded allocations and preservation of an already-authenticated duplicate-ID user's state.

### [BASE-SERVER-003] Join accepts lobbies explicitly marked non-joinable

- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Server/ServerHandlers.cxx:543–578`, particularly line 559.
- **Affected scope:** Lobby admission after creation with joinable=false or successful SetLobbyJoinable(false).

**Evidence.** The only admission-state check is `IsFull()`; `!IsJoinable()` is commented out. `SetLobbyJoinable` at lines 748–763 updates and acknowledges the flag. SDK `1.152.11/galaxy/IMatchmaking.h:648–654` says no user can join a non-joinable lobby even with empty slots.

**Failure mechanism.** An ordinary client holding a lobby ID issues JoinLobby after the owner closes admission. The server adds it and returns success because capacity remains. `Lobby::AddMember` only inserts membership and does not enforce joinability.

**Impact.** Games cannot reliably freeze their participant set when a match begins. This is an implemented flag with a concrete violated contract, independent of optional private/invitation service semantics.

**Alternatives / recommendation.** Enforce joinability authoritatively immediately before membership insertion and use the supported failure result. If a compatibility workaround is needed for a particular game, make it an explicit policy rather than globally acknowledging an unenforced setting. Also align list visibility with policy.

**Verification.** Owner creates a non-full lobby, a second client caches its ID, owner disables joining and receives success, then second client attempts to join. Require failure, unchanged membership and no entered notification; reenabling should permit joining.

### [BASE-SERVER-004] Lobby-addressed P2P bypasses shared-lobby authorization

- **Severity:** Medium
- **Confidence:** High
- **Category:** Security
- **Location:** `Source/Server/ServerHandlers.cxx:397–427`, contrasted with lines 435–447.
- **Affected scope:** Authenticated clients sending to a lobby owner/game-server interface.

**Evidence.** The lobby-ID branch checks only lobby existence and owner mapping before forwarding. It never checks `lobby->IsMember(pd->id)` or the sender's active lobby reference. The SDK's INetworking contract (`1.152.11/galaxy/INetworking.h:125–144`) limits communication to users in the same lobby and describes lobby-ID routing to the owner. The public client SendP2PPacket queues this message without a membership gate.

**Failure mechanism.** A logged-in outsider, or a user that has left, sends a packet to a known lobby ID. The server stamps its real user ID and forwards it to the owner despite failing the user-addressed route's admission rule.

**Impact.** Unexpected game traffic reaches an owner from users outside the authorized participant set. This is an authenticated LAN isolation defect, not remote code execution or a claim of Internet account compromise.

**Alternatives / recommendation.** Apply the active-lobby/membership invariant to the lobby-addressed branch before forwarding. Preserve host-to-lobby legacy behavior for legitimate owners. If pre-join traffic is desired, define a separate explicit route/contract.

**Verification.** With owner, member and outsider, verify legitimate lobby-directed packets arrive but outsider and post-leave packets do not; test SDK variants with and without IServerNetworking.

### [BASE-SERVER-005] Rejected lobby property changes echo the rejected value instead of authoritative state

- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Server/ServerHandlers.cxx:703–729,748–797`, `BoilerplateHandleLobbyDataUpdate` and its rollback lambdas.
- **Affected scope:** Non-owner SetLobbyJoinable / SetLobbyMaxMembers / SetLobbyType calls.

**Evidence.** The helper accepts `rollback_data` but never invokes it, and sends the unchanged request on failure. Client handlers always copy the reply's property into their cache before inspecting `success` (`Client/Impl/Matchmaking.cxx:469–502,668–698`, analogous type handler). The client optimistically changes its cache before sending.

**Failure mechanism.** A non-owner tries a different value. Server authorization correctly rejects it, but the reply contains that proposed value; the caller receives failure while continuing to observe the rejected state locally.

**Impact.** Local lobby state diverges from the server and other participants, affecting capacity/joinability/type decisions after a failed operation. Server ownership authorization itself is intact.

**Alternatives / recommendation.** For existing lobbies, invoke rollback before failure responses. For nonexistent lobbies, use a failure response that does not fabricate cached state. An alternative is for clients to defer mutation until success or request an authoritative refresh; reconcile both sides' failure contract.

**Verification.** Non-owner proposes changes to all three properties. Require failure callbacks and unchanged authoritative values in its cache and the owner's cache. Include nonexistent-lobby requests.

### [BASE-SERVER-006] Shared-file counter is never created in a fresh server store

- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Server/ServerHandlers.cxx:464–466`; startup consumer `Source/Server/Server.cxx:96–101`.
- **Affected scope:** Optional server file sharing across restart.

**Evidence.** The counter is written through `sfu.Open(shared, "shared-id.counter", out|trunc)`. `SharedFileUtils.cxx:74–85` calls `container->get`, returning an unopened stream when the entry does not exist; it never creates an entry. The fresh server has counter 1. Shared metadata is reloaded on startup by `filesystem_container.cxx:29–42`.

**Failure mechanism.** First uploads obtain IDs 2,3,... but the attempted counter writes do nothing. Restart leaves the counter at 1 while existing shared IDs remain registered. The next upload reuses 2. A different filename conflicts; the same filename can reopen and overwrite the object represented by the old ID.

**Impact.** Non-unique durable IDs, failed uploads, or changed data behind an existing shared handle after a normal restart. This is bounded optional-service persistence, not a core matchmaking outage.

**Alternatives / recommendation.** Create the counter entry explicitly, check and durably commit writes, validate startup text, and choose a next ID above all loaded share IDs. Deriving the high-water mark from metadata avoids trusting a missing/stale counter; use a wide checked counter with an explicit exhaustion policy.

**Verification.** Fresh store: upload two names, restart, upload a third and then repeat an old name. Confirm strictly new IDs and preservation of old content; exercise missing/truncated counter and write failure. Existing same-process roundtrip tests do not cover this.

### [BASE-SERVER-007] Upload returns a success ID even when storage creation or writing fails

- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Server/ServerHandlers.cxx:464–476`.
- **Affected scope:** Optional shared-file upload errors, including repeated filenames.

**Evidence.** `fsrm` receives a nonzero ID before `create_shared`/write; both failures only print a message, then line 476 sends that same response. Client `StorageImpl::FileUploaded` treats nonzero IDs as success (`Client/Impl/Storage.cxx:319–335`). Container `create_shared` rejects a previously shared filename with a different ID (`filesystem_container.cxx:174–182`) and asserts in Debug.

**Failure mechanism.** Upload a name, then upload it again, or cause a genuine disk-write failure. The server allocates an ID without establishing its data. Release returns success; the repeated-name Debug path can assert before that reply. Two users uploading the same common filename encounter the same global-name collision.

**Impact.** Callers publish unusable handles or believe data was shared when it was not. Severity remains Medium for this optional subsystem; the Debug assertion is not claimed as an unconditional Release crash.

**Alternatives / recommendation.** Return the existing zero-ID failure convention when persistence fails and rollback incomplete entries. Define repeated-name semantics explicitly: immutable per-ID objects (preserving display names) or a documented update operation. Avoid sending success until data and metadata are committed.

**Verification.** Repeat a filename from one and two users and inject create/write failures. Each success ID must download the intended bytes from a fresh client; failures must produce exactly one failure callback and no dangling entry.

### [BASE-SERVER-008] Chat notifications reuse another request's correlation ID

- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Server/ServerHandlers.cxx:222–242,284–293`.
- **Affected scope:** Concurrent chat-room lookup/history requests across clients.

**Evidence.** A room response initialized with the requester's `request_id` and target `id` is sent unchanged to both participants. Live-message history notifications likewise carry the sender's request ID. IDs originate from a per-process counter starting at 1 (`Shared_NoVer/Networking/MessageUniqueID.cxx`). Recipient handlers pop a pending listener using that ID (`Client/Impl/Chat.cxx:50–51,111–113`) before dispatching notifications.

**Failure mechanism.** A and B can have equal local request numbers. A's unsolicited response to B can consume B's room-lookup listener or a live notification can consume B's history listener. The actual response then has no specific listener. The room notification to B also reports B's own ID as its interlocutor rather than A.

**Impact.** Wrong request completion, lost expected callbacks and incorrect peer identification during normal concurrent chat activity. Sequential requester-only tests do not expose this.

**Alternatives / recommendation.** Send correlated replies solely to the requesting connection. Publish recipient-specific unsolicited notifications with reserved ID zero (or a distinct notification message) and the correct other-user identity. Separate live delivery from history-retrieval completion.

**Verification.** Arrange equal pending request IDs on two peers; issue crossed room requests and overlap a history request with an incoming send. Each specific callback must fire once for its own request and unsolicited notifications must leave pending requests intact.

### [BASE-SERVER-019] Transport broadcasts deliver protected state changes to peers that have not authenticated

- **Severity:** Medium
- **Confidence:** High
- **Category:** Security
- **Location:** `Source/Server/ServerHandlers.cxx:199–210,703–735,923–957` (also online-status broadcasts at 68,96).
- **Affected scope:** A connecting peer awaiting the LAN-key challenge response.

**Evidence.** `REQUIRES_AUTHENTICATION` checks the sender, but updates use `connection.Broadcast`. Its ENet broadcast implementations select all transport-CONNECTED peers, without consulting `challenge.completed` (`Vendor/Enet-IPv6/src/host.c:306–321`; `Vendor/Enet++/src/enetpp_helpers.cxx:8–28`). Peers are transport-connected while present in `unauthenticated_peers`.

**Failure mechanism.** A peer connects and withholds the challenge response. For up to the authentication timeout, it receives other users' data/rich-presence changes and lobby-property/online notifications. Reconnecting repeats the window without knowing the configured key.

**Impact.** Bypasses the key gate for the broadcast portion of live state. It does not grant mutating operations or guarantee disclosure of full user snapshots. In an intentionally open/default-key LAN, the incremental confidentiality impact is smaller.

**Alternatives / recommendation.** Centralize application broadcasts over authenticated, identity-linked recipients; retain pre-auth sends only for handshake/ping protocol needs. If the state is deliberately public, document that narrower authentication contract explicitly rather than relying on transport connection state.

**Verification.** Keep one raw client in challenge-pending state while authenticated peers update data, presence and lobby properties. Require no protected notifications before admission and correct delivery afterward.
