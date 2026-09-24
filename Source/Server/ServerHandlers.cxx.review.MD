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

## Follow-up addendum — 2026-09-24

Fresh full read of lines 1–1054 preceded comparison with this preserved report. Baseline source remains `b30e83872c0006e8240c8b4f565da5351bf10080`. Verification below is proposed, not executed. The exact 43-input ledger and all baseline dispositions are in `.ai/review-addendum/SERVER.MD`.

### [ADD-SERVER-001] Shared-file names overlap internal startup-counter storage

- **Severity:** High
- **Confidence:** High (mechanically traced; not runtime-reproduced)
- **Category:** Correctness
- **Location:** `Source/Server/ServerHandlers.cxx:455–476`; `Source/Server/Server.hxx:43–44`; `Source/Server/Server.cxx:96–101`; `Source/Server/Main.cxx:33`.
- **Affected scope:** Authenticated uploads when server upload policy is enabled and the counter entry is absent, including the ordinary fresh-store state. The shipped server-config generator enables uploads (`Source/Shared_NoVer/DefaultConfigFiles.cxx:231–246`).

**Evidence.** `FileShareMessage.filename` is client-controlled. The handler uses the same `sfu.shared` namespace both for its internal `shared-id.counter` and for `create_shared(fsrm.filename, fsrm.id)`. `SharedFileUtils::Open` uses non-creating `get` (`Source/Shared/SharedFileUtils.cxx:74–85`). `filesystem_container::create_shared` creates a missing name without reserving the counter name (`Source/Shared_NoVer/filesystem_container/filesystem_container.cxx:144–204`); `filesystem_entry::write` persists the supplied bytes (`filesystem_container_entry.cxx:291–314`). On the next construction, the server reads that entry and calls uncaught `std::stoul`.

**Failure mechanism.** The user-file and administrative-counter paths resolve into one container namespace. A valid shared filename can therefore become the entry later interpreted as numeric administrative state. The preceding lookup-only counter open does not create an absent counter; subsequent ordinary file creation can occupy that path. On a later initialization, nonnumeric file contents make `std::stoul` throw through the startup boundary. This follows from path ownership and parsing behavior; no network exercise was performed.

**Impact.** A collision between legitimate user-file storage and internal state can prevent backend initialization until the stored state is repaired. Later counter writes can change the outcome. Keep user content and administrative records in separate namespaces and recover invalid state explicitly.

**Possible solutions.** Reserve internal names after Windows-equivalent normalization; store administrative state outside the public shared-file container; or derive a checked high-water mark from committed metadata without a user-addressable counter. Merely fixing BASE-SERVER-006's missing creation leaves the namespace trust boundary unsafe.

**Recommended resolution.** Separate control state from uploaded objects, validate complete numeric parsing/range at startup, and recover a missing/corrupt counter from committed IDs. Retain authoritative success/failure handling from BASE-SERVER-007. An exact-string blacklist alone is insufficient for case/alias variants.

**Verification.** Proposed local unit-level checks: administrative path resolution is disjoint from permitted user-file names; counter loading handles absent, invalid and truncated values; ID recovery preserves existing metadata. No upload, live-service probe, restart test or counter fixture was executed in this pass.

### [ADD-SERVER-002] Lobby snapshot payloads do not match the recipient's API view

- **Severity:** Medium
- **Confidence:** High (wire contents and recipient selection are explicit)
- **Category:** Correctness
- **Location:** `Source/Server/ServerHandlers.cxx:171–173,532–540,613–630`; serialization at `Source/Shared/Lobby.hxx:49–60` and retention at `Source/Shared/Lobby.cxx:232–245`.
- **Affected scope:** Any authenticated newcomer, outsider or former member while another lobby remains alive; hello synchronization, lobby enumeration and direct lobby-data requests.

**Evidence.** Hello sends every full `Lobby`; list replies copy the entire manager map; direct data replies attach the full lobby after checking existence only. All three serialize `user_data` (the membership map) and `messages` as well as ordinary metadata. Live `SendToLobbyMessage`, in contrast, checks membership and sends only to members (lines 640–655). SDK `Source/DLLs/1.152.11/galaxy/IMatchmaking.h:620–626` restricts member enumeration to members; lines 890–903 describe member-directed messages; lines 575–586 say messages cease to be reachable after leaving. Lines 673–684 expressly permit nonmember metadata refresh: the defect is the additional member/history payload, not that refresh itself.

**Failure mechanism.** A and B exchange lobby messages. Authenticated C has never joined, but its normal hello already receives the complete history and member keys. C can repeat `RequestLobbyListMessage` or `RequestLobbyDataMessage` to refresh that history. Similarly, a departed B can reacquire it while A keeps the lobby alive. Serialization exposes the data before any client-side UI/filter policy; the current client also retains full list snapshots (`Client/Impl/Matchmaking.cxx:257–259`) and reads messages from `lobby_list` (`1099–1109`). No forged owner, claimed sender or bypass of the live-send membership gate is required.

**Impact.** Cross-lobby disclosure of member communication and membership within a shared-key LAN deployment. This does not establish secrecy for publicly queryable metadata, user stats or arbitrary server files. BASE-SERVER-019 concerns unauthenticated broadcast recipients; this finding persists after that fix and even for a small, public lobby. BASE-NET-006's snapshot-size problem is a separate consequence of retaining whole histories.

**Possible solutions.** Introduce a bounded public lobby-summary DTO and separate authorized member/history messages, or construct recipient-specific sanitized snapshots. Client-only filtering cannot revoke bytes already delivered. Removing history from every snapshot needs an explicit decision about legitimate join/reconnect history behavior.

**Recommended resolution.** Apply the same recipient policy to hello, list and direct-data paths; omit historical member messages and member-only enumeration from nonmember responses. Preserve supported nonmember metadata retrieval. Coordinate wire-schema changes with NET and client cache changes with API.

**Verification.** Proposed local serialization/handler fixture: construct a lobby and compare the permitted fields in member versus nonmember response objects. Ordinary public metadata refresh must remain available, while member-specific fields follow the documented view. No wire-level or live-service test was executed.

### [BASE-SERVER-003] Addendum — admission contract and discovery counterevidence

- **Disposition:** Retain Medium / High confidence / Correctness; refine scope under this existing admission-policy ID.
- **Location/evidence:** `ServerHandlers.cxx:543–578` and `Shared/Lobby.cxx:101–103` still admit solely by capacity/duplicate membership. However, `Client/Impl/Matchmaking.cxx:244–254` already excludes `!IsJoinable()` from the normal filtered API list. The baseline recommendation to align visibility must not imply the normal client currently lists nonjoinable lobbies. Raw snapshot delivery remains broader (ADD-SERVER-002).
- **Additional contract evidence:** SDK `1.152.11/galaxy/IMatchmaking.h:22–29,453–457` defines private lobbies as invite-only and friends-only lobbies as absent from lobby search. The server's join path does not inspect type or invitations; list publication and the client's list filter do not inspect type either. `InvitationMessage` carries an opaque connection string, and the server merely forwards it at 1026–1040; it creates no lobby invitation authorization record. A joinable, non-full private lobby therefore accepts an uninvited authenticated user holding its ID. This is further unenforced admission policy under this ID, not a second count for the same join gate. It does not assume GOG account/friend services exist on the LAN backend.
- **Mechanism/impact:** Correct client filtering cannot prevent cached-ID joins; private/type settings likewise fail to protect the advertised participant boundary. Owner/membership checks on subsequent mutations remain effective.
- **Options/recommendation:** Centralize authoritative admission and discovery policy, including joinability and supported type/invite rules. If open-LAN compatibility intentionally overrides SDK privacy, make the policy explicit rather than acknowledging a private setting as though enforced. Keep nonmember metadata refresh supported.
- **Verification:** In addition to the original cached-ID nonjoinable case, try a never-invited peer against a joinable private lobby and test friends-only search results. Verify that a normal client already hides nonjoinable entries, then check the server gate independently. Proposed only.

### [BASE-SERVER-008] Addendum — correlation collisions are listener-type scoped

- **Disposition:** Retain Medium / High confidence / Correctness; clarify the exact collision and SDK gates.
- **Location/evidence:** The two fan-outs remain at `ServerHandlers.cxx:222–242,284–293`; client consumption is `Client/Impl/Chat.cxx:47–79,108–165`. `Client/Impl/ListenerRegistrar.hxx:334–367` indexes request helpers by `T::GetListenerType()` before request ID. Equal IDs in unrelated listener interfaces do not by themselves consume one another or prove a wrong-vtable call.
- **Mechanism/impact:** A peer's pending **room-retrieve** request can collide with the foreign room reply; its pending **history-retrieve** request can collide with another participant's live send notification. Specific-listener loss applies where those specific APIs exist (`HAS_ICHAT_ROOMLISTENERS`, and history also `HAS_ICHATROOMMESSAGERETRIEVELISTENER`). The wrong interlocutor ID and unsolicited global completion remain separate observable symptoms on applicable legacy chat APIs. Rich-presence replies check self ID before popping a listener (`Friends.cxx:402–439`), and invitations do not pop the recipient's request map (`689–697`), so copying a numeric field into those messages is not equivalent evidence.
- **Options/recommendation:** Retain requester-only correlated replies plus zero-ID/distinct recipient notifications. Enforce both recipient and response-kind association rather than relying only on globally increasing numbers.
- **Verification:** Use matching IDs within the same receiving listener type for both original collision cases; add a different-listener-type control that must remain untouched. Test supported early/global and modern/specific chat interfaces separately. Proposed only.

### Retained baseline evidence — BASE-SERVER-001 / 004 / 005 / 006 / 007 / 019

- **001:** Re-read vendor `enet_peer_disconnect_now`'s no-local-event contract (`peer.c:506–536`) and reset body (`389–443`). Rejection leaks on pre-sweep reuse as reported; `completed=true` followed by immediate reset is not proof of accepted post-rejection traffic.
- **004:** SDK `INetworking.h:125–144` explicitly covers same-lobby communication and lobby-addressed routing. The sender ID is overwritten at 421, but membership remains unchecked. Direct user routing at 435–447 and owner-only server routing at 339–363 are counterevidence to a blanket relay-spoofing claim.
- **005:** The rollback lambda remains unused. Actual client failure consumers update their cached property before checking success (`Matchmaking.cxx:469–502,586–617,668–698`). SDK setter declarations do not promise that a rejected operation applies. Existing-lobby rollback and nonexistent-lobby error handling both need deliberate responses; no owner-write bypass is inferred.
- **006:** Fresh `get` cannot create the counter, and reloaded share metadata retains IDs; retain the original restart collision. ADD-SERVER-001 concerns the distinct public/control namespace collision, not another missing-counter count.
- **007:** Repeated names are rejected by `create_shared` when already assigned another ID, and the server still sends the new nonzero ID. The repeated-name assertion is Debug-only. Complete write/close/metadata commit checks require UTIL/STORAGE coordination; a stream's pre-close `good()` is not a durability guarantee.
- **019:** Both vendored broadcast implementations select transport-connected recipients only. Pre-auth peers receive live broadcasts, not the authenticated hello/list snapshots in ADD-SERVER-002. Sender authentication does not authorize recipients.

### Additional fresh boundary notes (not new IDs)

`SetUserData`, rich presence, invitations, lobby messages and user-directed P2P overwrite sender identity; chat creates a fresh message with authenticated sender/server time/ID. Client-provided lobby/room response objects are replaced or ignored, not adopted into the authoritative graphs. Lobby-member data sets `member_id=pd->id`, then the model rejects nonmembers. Unknown rich-presence actions can retain supplied `success`, but identity is still overwritten and clients do not apply an unknown action: this is a validation gap, not proven cross-user modification. File download denial/miss echoes caller data only to that caller; successful reads replace bytes/name. The container bounds paths, with throwing rejection already covered by BASE-NET-002; this review does not claim arbitrary filesystem read/write. Shared-file downloads are not documented as owner-only. Ordinary lobby leave/removal, migration, closure and chat membership retirement preserve the graphs; stale-generation failures remain BASE-SERVER-002.
