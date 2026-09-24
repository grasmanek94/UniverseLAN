# API — thorough source-first follow-up

## Executive summary

**Completed: 10/10 assigned files, 4,614 lines reread in full, including all feature branches. Four new independent findings: 1 High, 3 Medium.** Existing 17 confirmed BASE findings are retained with the explicit qualifications below; BASE-API-018 remains one informational investigation. Proposed combined API accounting is **21 confirmed findings: 3 High, 17 Medium, 1 Low**, plus that investigation. Categories: Correctness 10, API/ABI 7, Concurrency 2, Memory Safety 2. New findings are static, high-confidence source/contract conclusions, not runtime reproductions. The coordinator retains cross-owner/final accounting authority.

The principal additions are a same-thread use-after-free during presence deletion and a version-gated wrong-listener P2P delivery path. Also found: default self-presence callbacks publish an invalid ID, and mixed immediate/deferred lobby notifications invert ordered events. Chat room-creation fan-out broadens BASE-API-001, without another ID. BASE-API-008 gains explicit legacy private-lobby evidence; BASE-API-009 loses an invalid nonmember-owner test oracle, not its valid structural-refresh evidence. Existing serious Copy-getter and cancellation defects remain actionable.

Recommended sequence: repair presence argument ownership and the two retained High findings, then listener routing and ordered lobby delivery. Consolidate lifecycle fixes and validate against targeted Windows/version-specific cases. This is a complete assigned-source reread, not a correctness or release sign-off.

## Scope, method and environment

- Workspace: `C:\Development\AI\UL`; inspected HEAD `48cea8c6c48fa41fddd348a0119129cc5643fc8b`; requested production baseline `b30e83872c0006e8240c8b4f565da5351bf10080`.
- Read mandatory `.ai/SKILLS/CppReviewer.md` and `.ai/review-addendum/PLAN.MD`. Repository `AGENTS.md` search returned no matches. This assignment was performed directly, without delegates.
- Read all ten implementation/header files first, then followed Shared/Server/registrar ownership and event flow, then compared `.ai/review-baseline/API.MD` and all ten owned sidecars in full. Continued SDK/version/dependency checks to challenge both fresh hypotheses and every BASE-API-001–018 conclusion.
- Read-only Git comparison of the ten source inputs was empty. A broader comparison including existing review sidecars returned 1; repeating the contextual comparison with `:(glob,exclude)**/*.review.MD` returned 0. The latter covered Client, Client_NoVer, Shared, Shared_NoVer, Server, DLL SDK trees, SystemTests, `galaxy_sdk_features.cmake`, and IXWebSocket 12.0.1. That initial nonzero result is not reported as a production-source difference.
- Windows x86/x64 and the Windows 32-bit `long` data model are the focus. SDK/vendor files are contract context, not new owned review targets. No production edits, builds, tests, native-SDK experiments, sanitizer/analyzer runs, Git mutations, credential reads or external socket/web probes performed. Every proposed verification remains unexecuted.
- Final documentation check: `README.MD:13-47,60-76` describes a beta LAN/direct-IP wrapper and excludes games whose actual multiplayer uses other services. It expressly forbids mixing client/Server SDK versions and recommends matching architectures. All proposed multi-process cases assume a matching SDK and architecture; no finding relies on mixed-version wire incompatibility. Avatar/overlay/persistent GOG services and NAT/ping approximations remain capability limitations, not new defects.
- Writes use `apply_patch` only: append to ten API-owned sidecars and create this notebook. Original report text and `.ai/review-baseline/API.MD` are preserved.

## Exact per-file coverage

Every row means a fresh beginning-to-end read, not a grep-only check or a claim inherited from the baseline notebook. There are **no unfinished assigned files**.

| Exact source path | Exact coverage | Fresh inspection result / owning sidecar |
| --- | --- | --- |
| `Source/Client/Impl/Chat.cxx` | 1–400, complete | Room/history/send correlation, deduplication, borrowed callback batch, member/read counts. BASE-API-001 expanded to room-creation fan-out. [Sidecar](../../Source/Client/Impl/Chat.cxx.review.MD). |
| `Source/Client/Impl/Chat.hxx` | 1–198, complete | All room-ID/type/listener feature branches and getter scopes. BASE-API-018 remains informational. [Sidecar](../../Source/Client/Impl/Chat.hxx.review.MD). |
| `Source/Client/Impl/Friends.cxx` | 1–699, complete | Persona snapshots and copies, online friendship, null deletion, key/value lifetimes, self selectors, invitation captures. ADD-API-001/002; BASE-API-002–005 retained/qualified. [Sidecar](../../Source/Client/Impl/Friends.cxx.review.MD). |
| `Source/Client/Impl/Friends.hxx` | 1–644, complete | Every conditional override/default/return adapter, pointer/copy contracts, peer-set locking. No independent header-only defect. [Sidecar](../../Source/Client/Impl/Friends.hxx.review.MD). |
| `Source/Client/Impl/Matchmaking.cxx` | 1–1,159, complete | Create/list/filter/join/leave, all setters/getters, messages, membership/migration, iterator invalidation. ADD-API-003; BASE-API-006–012 reconciled. [Sidecar](../../Source/Client/Impl/Matchmaking.cxx.review.MD). |
| `Source/Client/Impl/Matchmaking.hxx` | 1–638, complete | Three cache maps, per-request filters, callback/ownership/error-output contracts, char/void and bool/void gates. No independent header-only ID. [Sidecar](../../Source/Client/Impl/Matchmaking.hxx.review.MD). |
| `Source/Client/Impl/Networking.cxx` | 1–170, complete | Reliability/scheduling, separate receive queues, Peek/Read/Pop, callback mode, sizes, interface dispatch. ADD-API-004; BASE-API-013/014 retained. [Sidecar](../../Source/Client/Impl/Networking.cxx.review.MD). |
| `Source/Client/Impl/Networking.hxx` | 1–245, complete | 256-channel bounds, shared packet lifetime, API preconditions, receiving roles and optional surface. No independent header-only ID. [Sidecar](../../Source/Client/Impl/Networking.hxx.review.MD). |
| `Source/Client/Impl/CustomNetworking.cxx` | 1–295, complete | Worker publication, cancellation, close arbitration, cleanup/stop/join, buffer operations, startup/callback exceptions. BASE-API-015–017 retained/expanded; no duplicate ID. [Sidecar](../../Source/Client/Impl/CustomNetworking.cxx.review.MD). |
| `Source/Client/Impl/CustomNetworking.hxx` | 1–166, complete | Channel member destruction order, shared/raw/atomic roles, ConnectionID ABI and byte-stream contract. No independent header-only ID. [Sidecar](../../Source/Client/Impl/CustomNetworking.hxx.review.MD). |

## New finding index

Full evidence, mechanism, alternatives, recommended fix and proposed verification are appended to the linked owned implementation sidecars.

| ID | Severity / confidence | Category | Finding |
| --- | --- | --- | --- |
| ADD-API-001 | High / High | Memory Safety | `DeleteRichPresence(GetRichPresenceKeyByIndex(0))` erases the owning map node, then rereads its freed key to build the network request. SDK 1.148.2+ direct-key reproducer. |
| ADD-API-002 | Medium / High | API/ABI | Default `RequestRichPresence()` resolves zero as local for storage but emits the invalid zero selector as the callback's user identity. |
| ADD-API-003 | Medium / High | Correctness | Deferred membership/ownership notifications are overtaken by later synchronous lobby-data/message/leave events; callback-visible cache state advances past the announced transition. |
| ADD-API-004 | Medium / High | Correctness | SDK 1.57.0–1.134.10 legacy server receive queue dispatches `INetworkingListener` instead of `IServerNetworkingListener`; the wrong callback can cause auto-pop and silent loss. |

ADD-API-001 is an ingress-alias invalidation bug, not BASE-API-002's concurrent getter-copy race. ADD-API-004 reproduces on an empty queue, so it is not BASE-API-013's backlog mismatch. ADD-API-003 does not require disconnection, recursive pumping, or a concurrent application thread. ADD-API-002 uses the SDK's actual default argument rather than invalidating a caller for arbitrary zero IDs.

## Explicit disposition of every existing API ID

No previous section has been silently replaced. “Retained” means the source and inspected contract still support the stated defect; it does not mean dynamically reproduced. Additions below do not increment the new-root-cause count.

| Existing ID | Disposition | Evidence, correction or boundary established in this pass |
| --- | --- | --- |
| BASE-API-001 | Retain Medium; expand | History/live packets still share process-local request IDs without an event discriminator. Room creation also fans the requester's response to its target (`ServerHandlers.cxx:222,236-242`), consuming the target's unrelated pending listener on collision and reporting the target itself as interlocutor. Full extension appended to Chat sidecar. |
| BASE-API-002 | Retain High; expand synchronization scope | Persona copies/availability escape map-level synchronization; presence references escape the container lock before copying. Include availability flag with the per-user policy. Indexed presence copies hold the correct container lock and are counterevidence to an all-getters claim. |
| BASE-API-003 | Retain Medium | Successful list enumeration is backed by reachable peers; `IsFriend` always returns false. Intentional LAN friendship is sufficient to demonstrate this internal inconsistency. |
| BASE-API-004 | Retain Medium | Null is a documented removal request; normalization to empty plus ACTION_SET retains/inserts a key at client, Server and peers. Do not confuse null with an arbitrary invalid pointer. |
| BASE-API-005 | Retain Medium; expand validation | Full hello data is dispatched as User data, never setting Friends availability/notifying persona. Friend-list and existing-lobby-member paths still omit automatic retrieval. Add startup peer-snapshot readiness and later actual nickname-change publication to the same retrieval/publication work; no immutable multi-call snapshot promise invented. |
| BASE-API-006 | Retain Medium | Near filter code is disabled until placeholder version 9.999.0; even enabling it supplies no ranking. No extra ID for unspecified multi-near ties/priority or malformed numeric conversion. |
| BASE-API-007 | Retain Medium | No-argument pre-1.82 search explicitly requires excluding full lobbies but sets `allow_full=true`. Modern explicit allow-full must remain supported. |
| BASE-API-008 | Retain Medium; expand | Missing type predicate exposes friends-only lobbies under the modern enum. SDK 1.57.0 additionally explicitly omits private lobbies from listing (`IMatchmaking.h:286-290`): same missing predicate, same ID. No LAN security-boundary claim. |
| BASE-API-009 | Retain Medium; correct test oracle | Existing snapshots refresh only properties/member map, omitting structural fields. Capacity/type/joinability are valid nonmember-after-refresh oracles. Modern owner return is expressly valid only to members (`IMatchmaking.h:879-887`); remove the baseline's nonmember-owner assertion from supported-path verification. |
| BASE-API-010 | Retain Medium; narrow generalization | Structural rejection echoes optimistic values; Server rollback callable is unused. Ordinary lobby-property rejection does supply authoritative property data, so not every setter has this failure. Use valid issuance followed by ownership loss where a setter has an ownership precondition. |
| BASE-API-011 | Retain Medium | Missing lobby branches leave output unchanged despite the explicit empty-string error contract. Zero-capacity/null-destination helper tolerance is not proof that every SDK accepts every null input. |
| BASE-API-012 | Retain Medium | Disconnect updates User/Utils but never invalidates joined lobbies/Friends peer state. Server removes membership and reconnect hello does not rejoin. Normal single-lobby leave does not erase a different joined lobby. |
| BASE-API-013 | Retain Medium | Listener activation can encounter a polling backlog with no SDK drain-before-register prerequisite. Announces the appended packet, Peeks/pops the front. Prohibited consuming calls in callbacks remain excluded. |
| BASE-API-014 | Retain Low | Both send variants enter the same queue drained by an independent background tick, contrary to documented ordinary ProcessData batching. Reliability mapping is not the defect and no latency measurement is claimed. |
| BASE-API-015 | Retain High; state version gate | 1.138.1+ operation-specific WS pointers bypass cancellation-aware request state. Completed Unregister before later callback creation is a legal trigger. Deferred strings are owned, so no duplicated string-lifetime claim. |
| BASE-API-016 | Retain Medium; add exceptional variant | Worker starts before publication; cleanup can erase a channel before queued data delivery. Allocation failure after worker start but before insertion leaves already queued notifications for an unpublished ID. Same lifecycle root; ordinary stop/join is counterevidence to a raw-this-only UAF accusation. |
| BASE-API-017 | Retain Medium; refine dependency claim | Transport internal state mutex does not synchronize the app's close-listener pointer. Worker/API interleaving remains real; some send-error close callbacks can also execute on the sending thread. No unsupported concurrent-Shutdown trigger needed. |
| BASE-API-018 | Keep Informational, unconfirmed reachability | Borrowed chat batch is not restored on nested dispatch, but nested ProcessData compatibility remains unestablished. Ordinary live/history callback reads retain the response. Calling after callback return is explicitly outside the contract and is not promoted. |

## Fresh source-first inspection notes and end-to-end traces

### Chat: correlation, invalidation and message-size semantics

The Server owns the room and replaces client-generated message identity/time on accepted send, acknowledges the sender, then broadcasts the resulting message. The sender ack inserts once; subsequent receipt/history compares message IDs before adding. Room creation completes both members before publishing the snapshot. These are real counterexamples to naive duplicate-count or half-initialized-room findings.

The correlation defect is more general than the original history example: a recipient gets another process's room-request token. A fix must distinguish unsolicited room/cache availability from requested completion as well as live from history messages. Merely keying by listener type does not prevent collisions within that type; merely requiring a non-null listener breaks global-listener callers.

The callback's response owns `messages`; the getter's index must be within that batch. Shared history's exclusive reference/limited suffix is correct for the inspected implementation. SDK history-success documentation itself instructs reading indexed messages despite a narrower remark in the getter documentation. Normal buffer copying reserves a terminator and returns the full content length. The current tests use `length+1`/oversized buffers; an exact-length-buffer native check is a gap, not sufficient evidence to assert a new off-by-one defect.

### Friends: snapshots, identity and mutation boundaries

`GetGalaxyUserData` returns a shared user object, not a null miss: self selectors resolve to local storage, others create placeholders. Owning that object protects neither an erased presence-map node nor a replaced nickname allocation. This distinction separates ADD-API-001's same-thread erasure from BASE-API-002's concurrent copying.

Server hello fills complete User snapshots, but its default message type routes to User rather than Friends; a populated nickname does not imply `friend_information_retrieved`. RequestFriendList succeeds from a live set without asking the Server or waiting for an initial enumeration marker. The acceptance message precedes existing-peer messages, so initial success can be early; incorporate readiness into BASE-API-005 validation. After a subsequent nickname change, Friends only sends NAME on the first retrieval; updating the string and publication need a common policy. An immutable friend enumeration snapshot during unrelated concurrent calls is not established by these SDK headers.

Default presence ID resolution is specifically supported by defaulted SDK declarations (also checked in 1.74.0). It is not a license to pass zero to every user-oriented method. The new finding concerns publishing the invalid selector as a concrete callback identity. Borrowed invitation/FindUser string arguments are extended into owned delayed values by the registrar, so temporary input strings are not an asynchronous UAF.

### Matchmaking: multiple lobbies, filters, ordered events and refresh

Both API and Server maintain maps of joined lobbies; Server explicitly permits multiple (`ServerHandlers.cxx:550`). Create/join publishes cache state before its synchronous completion; join refinds its iterator after a possible insertion. Existing-node `insert_or_assign` is not a rehash, and another map's insertion cannot invalidate this iterator. Leave erases only the supplied ID. List response replaces the all-known snapshot, but the actual Server response contains every extant lobby and Shared serialization includes message history. Divergent shared pointers alone do not prove that an active joined lobby or its messages vanished.

Filters are copied per request, cleared once, applied cumulatively, and the cap counts accepted entries. Joinability and explicit full-lobby rules are checked before result insertion. A discovery-only type fix must not accidentally restrict the all-known cache used for operations in other/private joined lobbies. Near-value behavior is absent; unknown numeric parse/priority policies are recorded as gaps rather than claimed SDK defects. The count-filter SDK requires a nonzero limit.

Membership/owner change notifications uniquely defer delivery even though their cache changes happen immediately. Later received events invoke callbacks now; only after the whole receive queue is drained does DelayRunner execute earlier transition callbacks. The Server's relevant sends default to reliable, and Enet++ actually sends them on transport channel 0 (`Source/Vendor/Enet++/src/enetpp.cxx:63-78`); the client inversion is not justified by cross-channel ordering. Correct either the notification timing or the entire state-application/delivery sequence, not only argument lifetime.

Structural refresh/rollback remain BASE-API-009/010. Shared/Server traces prevent overgeneralizing: ordinary property rejections supply current data, and owner getters on nonmembers have an explicit validity caveat. Disconnect/reconnect remains a different session-invalidation root, BASE-API-012.

### P2P: callback mode, polling, legacy receiving interfaces

User-directed packets pass the Server's shared-active-lobby membership checks; lobby-directed packets take the lobby-owner wrapper path. Client unwraps to the old server queue when that ABI exists. This proves ADD-API-004 independently of dedicated-server initialization and without forcing an illegal Read/Pop during a listener callback. Old ServerNetworking belongs to a regular peer; it is not synonymous with the separate GameServer API (`1.124.0/galaxy/GalaxyApi.h:165-181`).

Packet bytes are owned after API send and after queue pop; null output-size support in IsAvailable is not promised; channel 255 is allocated. Listener auto-pop is intentional. A backlog after legal listener activation remains BASE-API-013; wrong-interface dispatch is a distinct first-packet failure. One API instance can legitimately listen to ordinary networking while polling its separate legacy server interface.

The Server's server-originated send-to-user branch loops all owned lobbies containing that target (`ServerHandlers.cxx:339-365`), potentially emitting once per shared owned lobby. The SDK supplies no source-lobby selector for that call in the inspected surface. This is a Server-side multi-lobby policy/verification question for reconciliation, not an invented new API routing ID. General GameServer initialization-role handling is likewise CORE context, not additional owned coverage.

### WebSocket publication, cleanup, destruction and exceptions

WS uses its own IX worker, not the LAN transport. Callback values are delayed into the SDK pump. Open publication and terminal cleanup do not track that queue's lifetime; an atomic cleanup flag cannot make a handle readable when its registry entry is absent. Closed channels can instead retain buffers/resources until a later open. These remain BASE-API-016, including post-start allocation failure before insertion.

`Channel::~Channel` stops/joins before member destruction, and ordinary explicit reset destroys CustomNetworking before registrar/runner. WS callbacks enqueue; they do not invoke user code while holding the registry lock. Thus ordinary registry erasure does not demonstrate self-join/registry-lock deadlock. IX ignores a second close of an already CLOSED/CLOSING connection. Implicit InterfaceInstances member destruction has different ordering, but compliant explicit Shutdown/reset is the relevant supported path; partial-init/factory reconciliation belongs to CORE.

The callback has no exception boundary around buffer growth/notification construction, and IX has no catch around its worker entry. Fault-injection coverage is warranted, but no malformed supported input producing a non-resource exception was established. Thread-start failure, OOM and caller-thrown callbacks are not converted into new serious IDs. Reported cancellation still uses documented Unregister, and the close-pointer race still exists without exotic teardown. Byte-stream concatenation and bounded reads are consistent with ICustomNetworking rather than a frame-preserving API.

## Contract and dependency coverage actually obtained

These are contextual reads, not additions to the 10-file ownership count.

**Full file reads in this pass:**

- Repository documentation: `README.MD:1-314`, including deployment/version preconditions and compatibility table; this is documentation context, not an extra assigned source file.
- Client: `Client.cxx`, `ClientNetworkHandlers.cxx`, `UniverseLAN.{cxx,hxx}`, `UniverseGameServer.cxx`, `Impl/ListenerRegistrar.{cxx,hxx}`; Client_NoVer `Impl/DelayRunner.cxx`, `Impl/NotificationParamScopeExtender.hxx`.
- Shared: `ChatRoom.{cxx,hxx}`, `ChatRoomManager.cxx`, `ChatMessage.hxx`, `Lobby.{cxx,hxx}`, `LobbyManager.{cxx,hxx}`, `GalaxyUserData.{cxx,hxx}`, `GalaxyID.hxx`, `Networking/Networking.{cxx,hxx}`; message headers `RequestChatRoomWithUserMessage.hxx`, `RequestChatRoomMessagesMessage.hxx`, `RequestSpecificUserDataMessage.hxx`, `RichPresenceChangeMessage.hxx`, `P2PNetworkPacketMessage.hxx`.
- Shared_NoVer: `SafeStringCopy.hxx`, `AchievementsAndStatsContainer.{cxx,hxx}`, `Networking/MessageUniqueID.cxx`.
- Server: `ServerHandlers.cxx:1-1054`; feature map `Source/galaxy_sdk_features.cmake:1-306`.
- SDK 1.152.11: `IChat.h`, `IMatchmaking.h`, `INetworking.h`, `ICustomNetworking.h`, `GalaxyID.h`; IXWebSocket 12.0.1 `ixwebsocket/IXWebSocket.cpp:1-640`.
- SystemTests context: `Host/Chat.cxx:1-327`, `Host/Friends.cxx:1-202`, `Host/Lobby.cxx:1-509`, `Host/P2P.cxx:1-202`, `Host/CustomNetworking.cxx:1-128`.

**Selected ranges / symbol checks:**

- `Client/Impl/User.cxx:288-673`, user lookup/snapshot/publication/connection state; `Client/GalaxyDLL.cxx:150-189`, API pump order.
- `Shared/IniData.cxx:770-807,908-953` and accessor symbol searches; configuration implementation only, no config/secret files.
- SDK 1.152.11 `IFriends.h:20-314,365-525,570-1089`, `GalaxyApi.h:295-479`, `IListenerRegistrar.h:130-242`.
- SDK 1.57.0 `IMatchmaking.h:254-443` and `INetworking.h` server-listener symbol/contracts; 1.74.0 `IFriends.h:245-472`; 1.124.0 `INetworking.h:1-130`, `GalaxyApi.h:115-224`; 1.134.10 server-listener symbols. No claim that all SDK versions were read or binary-compared.
- IXWebSocket `IXWebSocketTransport.cpp:200-259,1160-1309` plus lifecycle searches; Enet++ `src/enetpp.cxx:40-119` and Send symbol search. Vendor code is used to establish integration preconditions, not certified as reviewed implementation.

Important gates: IChat 1.104.3+, history 1.109.0+, per-room operation listeners 1.134.10 and 1.136.0+; rich-presence queries 1.74.0+, Friends operation listeners 1.126.0+, key-pointer indexing 1.148.2+; allow-full 1.82.0+, lobby operation listeners/void adapter 1.125.0+, result count 1.131.0+, leave reasons 1.133.0+; legacy ServerNetworking through 1.134.10, immediate P2P sends 1.78.0+; custom networking 1.99.0+, its operation listeners 1.138.1+. Near enum is deliberately disabled at 9.999.0. Feature reading is not a feature-matrix build.

## Test gaps and proposed focused Windows verification

1. **Argument lifetime:** same-thread indexed-key deletion with ASan, borrowed aliases vs owned keys, null-as-delete propagation; concurrent Copy/availability mutation for retained BASE-API-002. No illegal retained pointer after an unrelated mutation.
2. **Identity and friend readiness:** default versus explicit-self presence callback IDs; friend-list requested inside auth success while initial peer messages are delayed; automatic existing-member/persona availability; changed and unchanged subsequent nickname snapshots.
3. **Chat correlation:** competing room-creation requests and history/live batches with equal process-local IDs, unsolicited global completions, different rooms/peers. Ordinary pagination tests already use a gated live-then-history sequence, not these collisions.
4. **Lobby event order:** queue entry/data/message/exit or migration/data before one pump, assert order and callback-visible state. Current SystemTests gate later actions on earlier member observations, preventing this backlog case. Repeat with two simultaneous joined lobbies and leave only one.
5. **Discovery/refresh:** all supported lobby types, legacy full-lobby exclusion and modern override, combined predicates/count limits, near policy against a native reference, partial cached structural refresh, valid ownership-lost-in-flight rejection. Do not rely on nonmember owner validity or out-of-callback GetLobbyByIndex.
6. **P2P:** old client/server listener classes, separate-interface listener/polling combinations, same channel/different receive roles, backlog activation and channels 0/255; pause sender ProcessData for ordinary/immediate scheduling. Inspected P2P tests use ordinary-interface polling and do not exercise these callback routes.
7. **WS:** delayed open/data/close dispatch across another open, Unregister before and after queueing, local/remote close arbitration, allocator ID reuse, cleanup without another open, post-start insertion failure, worker notification allocation failure. Current echo/close tests retain listeners and pump promptly; they establish no cancellation/fault-path result here.
8. **Session loss:** disconnect with two joined lobbies and pending requests, verify one loss per lobby and no silent rejoin; compare stale Friends/P2P state with session-generation policy. No tests were run.

Build/CI and exhaustive SDK ABI checks remain other owners' scope; no successful build/test status from prior reports is reused as validation of these paths. No security exploit or performance speedup is asserted. Windows fault-path/contract tests are the next evidence needed, not a reason to rerun unrelated successful suites.

## Positive findings and completion record

Useful existing foundations are request-specific filter snapshots, cache publication before create/join callbacks, owned packet buffers, complete channel bounds, history deduplication, binary lobby copying, copied delayed constant-string arguments, and explicit WS worker join before Channel member teardown. The added findings identify where those local protections do not span the full operation.

Executed terminal operations were read-only Git HEAD/status/diff comparisons and report diff/accounting checks. Source and report contents were read with dedicated Read/Glob/Grep tools. Original baseline sections were preserved and all proposed reproductions are clearly labelled unexecuted. The final report checks verify append-only sidecar changes, four ADD headings and whitespace; none is a build or runtime test. Final accounting is 4 new IDs, 18 explicit BASE dispositions, 10/10 assigned files complete.
