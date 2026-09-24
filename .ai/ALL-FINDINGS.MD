# UniverseLAN - complete detailed findings ledger

This is the self-contained consolidated review ledger for production baseline `b30e83872c0006e8240c8b4f565da5351bf10080` and the follow-up published in `556efc639e0c4e748bb718a487b33ad60d0616bc`.

It records **126 actionable canonical groups** (24 High, 89 Medium, 13 Low) plus **six informational or conditional investigations**. Each record below identifies its primary source location and function, fault mechanism, proposed correction, and original detailed review item. The final section records eight aliases, so all **140 finding/investigation IDs** are traceable without double-counting overlapping root causes.

This is a C++ correctness, memory/resource lifetime, API compatibility, persistence, build, and regression-coverage review. It is not a cybersecurity risk assessment.

## Baseline canonical findings

### CORE

### `BASE-CORE-001` - High
- **Location/function:** `Source/Client/Impl/ListenerRegistrar.hxx:231-269,309-331`, `NotifyAll` and `NotifyAllSpecificOnly`; pop-to-invocation gap at `:91-110,232-251,356-368`.
- **Issue:** Queued or already-popped raw specific listeners survive `Unregister`; an earlier callback can delete a later listener that is still invoked.
- **Proposed solution:** Store generation-bearing registration records, cancel before dispatch, and acquire an in-flight invocation guard before calling each target.
- **Original review:** [ListenerRegistrar.hxx.review.MD](../Source/Client/Impl/ListenerRegistrar.hxx.review.MD).

### `BASE-CORE-002` - High
- **Location/function:** `Source/Client/Impl/ListenerRegistrar.cxx:88-117,137-147,169-207,227-237`, `ExecuteForListenerType`.
- **Issue:** Global dispatch snapshots raw listener pointers; callback A can unregister and delete callback B while B remains in the snapshot.
- **Proposed solution:** Snapshot cancellable registration records, pin each target for invocation, and skip records cancelled after snapshot creation.
- **Original review:** [ListenerRegistrar.cxx.review.MD](../Source/Client/Impl/ListenerRegistrar.cxx.review.MD).

### `BASE-CORE-003` - High
- **Location/function:** `Source/Client/UniverseLAN.cxx:91-134`, `InterfaceInstances::reset`; active pump at `Source/Client_NoVer/Impl/DelayRunner.cxx:7-11`, `DelayRunner::Run`.
- **Issue:** Shutdown from a callback destroys the active runner/client and the pump resumes into destroyed member state.
- **Proposed solution:** Mark shutdown pending, stop further dispatch, and defer ordered graph destruction until the outermost pump frame exits.
- **Original review:** [UniverseLAN.cxx.review.MD](../Source/Client/UniverseLAN.cxx.review.MD).

### `BASE-CORE-004` - Medium
- **Location/function:** `Source/Client/UniverseGameServer.cxx:25-28,74-80`, game-server initialization and networking getter.
- **Issue:** Modern game-server initialization defaults to the client networking role, so direct member sends carry user identity instead of lobby/server identity.
- **Proposed solution:** Pass the game-server role explicitly, preferably through a required role enum rather than a defaulted boolean.
- **Original review:** [UniverseGameServer.cxx.review.MD](../Source/Client/UniverseGameServer.cxx.review.MD).

### `BASE-CORE-005` - Medium
- **Location/function:** `Source/Client/GalaxyDLL.cxx:24,35-47,49-69,72-75,183-185`, `Init` and `GetError`; legacy adapters at `Source/Client/GalaxyApiFactory.cxx:40-65,154-156`.
- **Issue:** Initialization exceptions escape instead of following SDK error policy; legacy exception settings and last-error retrieval are ignored.
- **Proposed solution:** Establish one exception/error boundary before normalization and through worker creation, preserving legacy throw policy and modern thread-local errors.
- **Original review:** [GalaxyDLL.cxx.review.MD](../Source/Client/GalaxyDLL.cxx.review.MD).

### `BASE-CORE-006` - Medium
- **Location/function:** `Source/Client/GalaxyDLL.cxx:24,35-47,60`, initialization console capture/release.
- **Issue:** Failed initialization leaves `std::cout` redirected to the capture buffer.
- **Proposed solution:** Make console capture RAII or scope-guarded so every failure path restores the previous stream buffer.
- **Original review:** [GalaxyDLL.cxx.review.MD](../Source/Client/GalaxyDLL.cxx.review.MD).

### `BASE-CORE-007` - Low
- **Location/function:** `Source/Client/GalaxyApiFactory.cxx:166-174`, `GalaxyFactory::GetInstance`.
- **Issue:** Later SDK `GetInstance` calls allocate a facade instead of returning null; only SDK 1.57.0 permits creation on query.
- **Proposed solution:** Version-gate creating query behavior and keep allocation in `CreateInstance` for later SDKs.
- **Original review:** [GalaxyApiFactory.cxx.review.MD](../Source/Client/GalaxyApiFactory.cxx.review.MD).

### `BASE-CORE-008` - Medium
- **Location/function:** `Source/Client/Impl/GalaxyThread.cxx:25-26,44-45,49-58`, `Join`, `Detach`, and destructor.
- **Issue:** The dormant wrapper destructor detaches an already non-joinable thread after `Join` or `Detach`, throwing through a nonthrowing destructor.
- **Proposed solution:** Check `joinable()` and define explicit join/detach behavior; destruction of an already completed wrapper must be a no-op.
- **Original review:** [GalaxyThread.cxx.review.MD](../Source/Client/Impl/GalaxyThread.cxx.review.MD).

### `BASE-CORE-009` - Low
- **Location/function:** `Source/Client/Impl/Logger.cxx:69-79`, formatted logging path.
- **Issue:** The logger writes `iLen + 1` bytes and includes the string terminator in every record.
- **Proposed solution:** Validate formatter success and construct/write exactly `iLen` bytes.
- **Original review:** [Logger.cxx.review.MD](../Source/Client/Impl/Logger.cxx.review.MD).

### `BASE-CORE-010` - Medium
- **Location/function:** `Source/Client/Impl/Logger.cxx:62-79`, logging methods.
- **Issue:** An unlocked stream-state read can race a locked failed insertion that changes the stream state.
- **Proposed solution:** Perform state check, write, flush, and failure handling under the same mutex.
- **Original review:** [Logger.cxx.review.MD](../Source/Client/Impl/Logger.cxx.review.MD).

### API

### `BASE-API-001` - Medium
- **Location/function:** `Source/Client/Impl/Chat.cxx:47-69`, room-response processing; `:108-148`, `RequestChatRoomMessagesProcessed`.
- **Issue:** Sender-local IDs in chat fan-out can consume an unrelated local history request; unsolicited events also emit request-success callbacks.
- **Proposed solution:** Separate replies from unsolicited events, send requester tokens only to requesters, and correlate replies with recipient-local operation state.
- **Original review:** [Chat.cxx.review.MD](../Source/Client/Impl/Chat.cxx.review.MD).

### `BASE-API-002` - High
- **Location/function:** `Source/Client/Impl/Friends.cxx:147-154,477-485`, persona and presence Copy getters.
- **Issue:** Copy APIs read mutable nickname/presence strings after the protecting locks are released.
- **Proposed solution:** Copy under per-user/container locks or return owning snapshots, with all nickname, availability, and writer paths synchronized together.
- **Original review:** [Friends.cxx.review.MD](../Source/Client/Impl/Friends.cxx.review.MD).

### `BASE-API-003` - Medium
- **Location/function:** `Source/Client/Impl/Friends.cxx:209-246,665-685`, `RequestFriendList`, `IsFriend`, and `ChangeOnlineStatus`.
- **Issue:** Friend-list enumeration exposes reachable peers, but `IsFriend` always reports false.
- **Proposed solution:** Implement `IsFriend` from the same locked reachable-peer relation used by enumeration.
- **Original review:** [Friends.cxx.review.MD](../Source/Client/Impl/Friends.cxx.review.MD).

### `BASE-API-004` - Medium
- **Location/function:** `Source/Client/Impl/Friends.cxx:342-360`, `SetRichPresence`.
- **Issue:** SDK-valid null rich-presence values are normalized to empty strings and sent as sets rather than deletions.
- **Proposed solution:** Detect null before normalization and route it through an explicit delete action.
- **Original review:** [Friends.cxx.review.MD](../Source/Client/Impl/Friends.cxx.review.MD).

### `BASE-API-005` - Medium
- **Location/function:** `Source/Client/Impl/Friends.cxx:209-222,665-685`, friend-list/presence handling; related `Source/Client/Impl/Matchmaking.cxx:343-374`.
- **Issue:** Listed friends and existing lobby members do not automatically gain persona availability or persona-change notification.
- **Proposed solution:** Request or publish persona snapshots for initial friends/members through one shared availability and notification path.
- **Original review:** [Friends.cxx.review.MD](../Source/Client/Impl/Friends.cxx.review.MD).

### `BASE-API-006` - Medium
- **Location/function:** `Source/Client/Impl/Matchmaking.cxx:198-201,231-259,303-307`, near-filter recording, filtering, and list processing.
- **Issue:** Near-value filtering is compiled out in supported versions, and the enabled code has no proximity behavior.
- **Proposed solution:** Represent near criteria independently, rank/filter candidates by documented proximity, then apply result limits.
- **Original review:** [Matchmaking.cxx.review.MD](../Source/Client/Impl/Matchmaking.cxx.review.MD).

### `BASE-API-007` - Medium
- **Location/function:** `Source/Client/Impl/Matchmaking.cxx:97-110,244-250`, `RequestLobbyList` and result filtering.
- **Issue:** Legacy no-argument list requests set `allow_full=true`, exposing full lobbies contrary to that ABI contract.
- **Proposed solution:** Use `allow_full=false` in pre-1.82 branches and retain the newer explicit override only where available.
- **Original review:** [Matchmaking.cxx.review.MD](../Source/Client/Impl/Matchmaking.cxx.review.MD).

### `BASE-API-008` - Medium
- **Location/function:** `Source/Client/Impl/Matchmaking.cxx:231-254`, `RequestLobbyListProcessed`.
- **Issue:** Discovery has no lobby-type predicate, exposing friends-only and legacy private lobbies.
- **Proposed solution:** Apply SDK-versioned searchable-type filtering before count limiting while retaining non-discovery cache behavior.
- **Original review:** [Matchmaking.cxx.review.MD](../Source/Client/Impl/Matchmaking.cxx.review.MD).

### `BASE-API-009` - Medium
- **Location/function:** `Source/Client/Impl/Matchmaking.cxx:735-759`, `RequestLobbyDataProcessed`.
- **Issue:** Refreshing an existing lobby copies properties/members but omits owner, capacity, type, and joinability.
- **Proposed solution:** Apply a complete authoritative structural snapshot under the matchmaking lock and test owner only in valid member contexts.
- **Original review:** [Matchmaking.cxx.review.MD](../Source/Client/Impl/Matchmaking.cxx.review.MD).

### `BASE-API-011` - Medium
- **Location/function:** `Source/Client/Impl/Matchmaking.cxx:782-793,927-938`, `GetLobbyDataCopy` and `GetLobbyMemberDataCopy`.
- **Issue:** Invalid or missing lobby branches leave caller output unchanged instead of returning an empty string.
- **Proposed solution:** Clear valid output buffers or call the shared safe-copy helper with an empty string on missing-lobby paths.
- **Original review:** [Matchmaking.cxx.review.MD](../Source/Client/Impl/Matchmaking.cxx.review.MD).

### `BASE-API-012` - Medium
- **Location/function:** `Source/Client/Impl/Matchmaking.cxx:394-421,1065-1076`, joined-lobby state and loss handling.
- **Issue:** Disconnect removes server membership but leaves local joined-lobby state alive across reconnect.
- **Proposed solution:** Add atomic session-loss invalidation for joined caches/pending work and reject late prior-session replies.
- **Original review:** [Matchmaking.cxx.review.MD](../Source/Client/Impl/Matchmaking.cxx.review.MD).

### `BASE-API-013` - Medium
- **Location/function:** `Source/Client/Impl/Networking.cxx:66-93,153-168`, `AddPacket`.
- **Issue:** With polling backlog, the callback announces appended packet P2 while `Peek` returns older front packet P1 and pop removes P1.
- **Proposed solution:** Deliver FIFO packet identities consistently, or drain/adapt backlog when listener mode starts.
- **Original review:** [Networking.cxx.review.MD](../Source/Client/Impl/Networking.cxx.review.MD).

### `BASE-API-014` - Low
- **Location/function:** `Source/Client/Impl/Networking.cxx:37-63`, `SendP2PPacket`.
- **Issue:** Ordinary and immediate P2P sends enter the same background queue, losing the documented ProcessData scheduling distinction.
- **Proposed solution:** Hold ordinary sends until API-pump release and keep immediate transport scheduling and reliability mapping separate.
- **Original review:** [Networking.cxx.review.MD](../Source/Client/Impl/Networking.cxx.review.MD).

### `BASE-API-015` - High
- **Location/function:** `Source/Client/Impl/CustomNetworking.cxx:57-73,95-110,219-232`, Channel open/close listener handling.
- **Issue:** Channel retains raw operation listeners outside registrar state, so `Unregister` or destruction does not prevent later WebSocket callbacks.
- **Proposed solution:** Store cancellable operation tokens and resolve listeners on API dispatch, retiring each token after terminal delivery.
- **Original review:** [CustomNetworking.cxx.review.MD](../Source/Client/Impl/CustomNetworking.cxx.review.MD).

### `BASE-API-016` - Medium
- **Location/function:** `Source/Client/Impl/CustomNetworking.cxx:62-64,69-112,149-163,198-216`, channel startup, publication, and cleanup.
- **Issue:** Worker callbacks can precede registry publication, and cleanup can erase a channel before queued data/close notifications run.
- **Proposed solution:** Publish a stable channel identity before worker start and retire channels only after ordered API-thread completion delivery.
- **Original review:** [CustomNetworking.cxx.review.MD](../Source/Client/Impl/CustomNetworking.cxx.review.MD).

### `BASE-API-017` - Medium
- **Location/function:** `Source/Client/Impl/CustomNetworking.cxx:91-97,226-232`, `CloseConnection` and `WebSocketOnClose`.
- **Issue:** API and transport callback paths read/write `listener_close` without common synchronization.
- **Proposed solution:** Use one synchronized channel lifecycle state machine with deterministic close-listener consumption.
- **Original review:** [CustomNetworking.cxx.review.MD](../Source/Client/Impl/CustomNetworking.cxx.review.MD).

### `BASE-API-018` - Informational
- **Location/function:** `Source/Client/Impl/Chat.hxx:37-47`, `incomming_messages_buffer`; `Source/Client/Impl/Chat.cxx:116-153,259-264`.
- **Issue:** Nested chat dispatch can replace the borrowed message view and fail to restore the outer view; support for nested `ProcessData` is unresolved.
- **Proposed solution:** If nested pumping is supported, use RAII-owned callback context that restores prior state; otherwise enforce non-reentrant dispatch.
- **Original review:** [Chat.hxx.review.MD](../Source/Client/Impl/Chat.hxx.review.MD).

### STORAGE

### `BASE-STORAGE-001` - High
- **Location/function:** `Source/Client/Impl/CloudStorage.cxx:374-417,488-505`, `PutFile` overloads.
- **Issue:** Replacement truncates the live save before source/destination success, losing the last committed version on failure.
- **Proposed solution:** Stage bytes and metadata, verify write/flush/close, then atomically commit while retaining the old generation for rollback.
- **Original review:** [CloudStorage.cxx.review.MD](../Source/Client/Impl/CloudStorage.cxx.review.MD).

### `BASE-STORAGE-002` - High
- **Location/function:** `Source/Client/Impl/CloudStorage.cxx:162-200,244-267,404-456,539-544,575-580`, `GetFile`, `PutFile`, and `DeleteFile`.
- **Issue:** Read/write/metadata/unlink/close failures become success results, and incomplete reads can appear valid.
- **Proposed solution:** Propagate typed I/O status and actual byte counts; close/flush and commit metadata before success; preserve cache state on failed delete.
- **Original review:** [CloudStorage.cxx.review.MD](../Source/Client/Impl/CloudStorage.cxx.review.MD).

### `BASE-STORAGE-003` - Medium
- **Location/function:** `Source/Client/Impl/CloudStorage.cxx:162-169,399-402,613-615`, callback `GetFile`, `PutFile`, and `CalculateHash`.
- **Issue:** Short sink writes and failed rewinds are ignored, and whole-file callback download can narrow a valid size into negative `int`.
- **Proposed solution:** Check rewind, require bounded positive chunks and full sink progress, retry/fail short writes, and report terminal failure.
- **Original review:** [CloudStorage.cxx.review.MD](../Source/Client/Impl/CloudStorage.cxx.review.MD).

### `BASE-STORAGE-004` - Medium
- **Location/function:** `Source/Client/Impl/CloudStorage.cxx:108-125,445-449,533-537,602-645`, hash getters, `PutFile`, and `CalculateHash`.
- **Issue:** Null/empty default upload hashes are not calculated, and null overwrite can retain stale metadata hash.
- **Proposed solution:** Calculate and persist one validated content hash for null or empty input, replacing stale metadata in both upload paths.
- **Original review:** [CloudStorage.cxx.review.MD](../Source/Client/Impl/CloudStorage.cxx.review.MD).

### `BASE-STORAGE-005` - High
- **Location/function:** `Source/Client/Impl/CloudStorage.cxx:549-580`, `DeleteFile`.
- **Issue:** `expectedHash` is unused, so a stale guarded delete can remove newer content.
- **Proposed solution:** Compare-and-delete atomically against committed hash/generation and return conflict without changing bytes, metadata, or indexes on mismatch.
- **Original review:** [CloudStorage.cxx.review.MD](../Source/Client/Impl/CloudStorage.cxx.review.MD).

### `BASE-STORAGE-006` - Medium
- **Location/function:** `Source/Client/Impl/CloudStorage.cxx:24-38,583-597`, savegroup ID generation, `OpenSavegame`, and `CloseSavegame`.
- **Issue:** Consecutive groups and the first post-close save reuse IDs; a second-based seed can also collide across reinitialization.
- **Proposed solution:** Allocate a fresh persisted/opaque ID per group and ungrouped write, synchronizing group mode and ID as one state.
- **Original review:** [CloudStorage.cxx.review.MD](../Source/Client/Impl/CloudStorage.cxx.review.MD).

### `BASE-STORAGE-007` - Medium
- **Location/function:** `Source/Client/Impl/CloudStorage.cxx:47-60,63-125,244-267,293-340`, list/metadata request completion state.
- **Issue:** Later requests overwrite shared callback-only list/metadata members before earlier callbacks run.
- **Proposed solution:** Capture immutable per-request result snapshots, scoped/restored for reentrant callbacks.
- **Original review:** [CloudStorage.cxx.review.MD](../Source/Client/Impl/CloudStorage.cxx.review.MD).

### `BASE-STORAGE-008` - Medium
- **Location/function:** `Source/Client/Impl/CloudStorage.cxx:253-255,301-303`, buffered `GetFile` and `GetFileMetadata`.
- **Issue:** Missing or malformed savegame type metadata reaches uncaught `stol`.
- **Proposed solution:** Centralize checked nonthrowing metadata decoding, default compatible absence, validate ranges, and issue one failure/result callback.
- **Original review:** [CloudStorage.cxx.review.MD](../Source/Client/Impl/CloudStorage.cxx.review.MD).

### `BASE-STORAGE-009` - High
- **Location/function:** `Source/Client/Impl/CloudStorage.cxx:152-202`, deferred callback `GetFile`.
- **Issue:** A direct cloud lambda retains a raw listener after unregister/destruction; ordinary queued completions overlap CORE-001.
- **Proposed solution:** Admit cancellable cloud operation records synchronously and resolve listener tokens only at dispatch.
- **Original review:** [CloudStorage.cxx.review.MD](../Source/Client/Impl/CloudStorage.cxx.review.MD).

### `BASE-STORAGE-010` - Medium
- **Location/function:** `Source/Client/Impl/Stats.cxx:87-91`, `UpdateAvgRateStat`.
- **Issue:** It sums interval rates, so equivalent split intervals produce a different average.
- **Proposed solution:** Persist cumulative numerator and duration under one lock and expose their weighted ratio.
- **Original review:** [Stats.cxx.review.MD](../Source/Client/Impl/Stats.cxx.review.MD).

### `BASE-STORAGE-011` - Medium
- **Location/function:** `Source/Client/Impl/Stats.cxx:127-161`, store/reset; dependency `Source/Shared/IniData.cxx:835-913`.
- **Issue:** Failed INI persistence clears dirty state yet queues success, preventing reliable retry.
- **Proposed solution:** Return aggregate persistence status, clear dirty data only after durable commit, and report failure/retry correctly.
- **Original review:** [Stats.cxx.review.MD](../Source/Client/Impl/Stats.cxx.review.MD).

### `BASE-STORAGE-013` - High
- **Location/function:** `Source/Client/Impl/Storage.cxx:171-196`, `FileShare` worker.
- **Issue:** Worker registers a raw specific listener only after returning, allowing cancellation/destruction before registration.
- **Proposed solution:** Create a cancellable request token synchronously before launching the worker; the worker retains the token/ID, not a listener pointer.
- **Original review:** [Storage.cxx.review.MD](../Source/Client/Impl/Storage.cxx.review.MD).

### `BASE-STORAGE-014` - Medium
- **Location/function:** `Source/Client/Impl/Storage.cxx:245-249`, `GetSharedFileOwner`.
- **Issue:** Downloaded file owner is always reported as downloader rather than uploader.
- **Proposed solution:** Persist authenticated uploader ID server-side, include it in file response/metadata, and cache it by share ID.
- **Original review:** [Storage.cxx.review.MD](../Source/Client/Impl/Storage.cxx.review.MD).

### `BASE-STORAGE-015` - Medium
- **Location/function:** `Source/Client/Impl/Storage.cxx:275-305`, `FileDownloaded`.
- **Issue:** Existing zero-byte shared files are rejected because empty payload also represents error.
- **Proposed solution:** Add explicit protocol success/status independent of payload length and accept empty files only with positive status.
- **Original review:** [Storage.cxx.review.MD](../Source/Client/Impl/Storage.cxx.review.MD).

### `BASE-STORAGE-016` - Medium
- **Location/function:** `Source/Client/Impl/Storage.cxx:160-193,215-221`, `FileShare` worker and submission.
- **Issue:** Source-read, worker, admission, native-send, and oversized-packet failures can become empty success or strand request completion.
- **Proposed solution:** Preserve read status, propagate failures through one operation token, retire requests exactly once, and preflight/chunk oversized transfers.
- **Original review:** [Storage.cxx.review.MD](../Source/Client/Impl/Storage.cxx.review.MD).

### `BASE-STORAGE-017` - High
- **Location/function:** `Source/Client/Impl/User.cxx:74-77,610-621,630-651`, sign-in waiter set and `RunForAllWaitingAuthListeners`.
- **Issue:** Private pending-auth raw listener set is not connected to registrar `Unregister`.
- **Proposed solution:** Use synchronously admitted registrar-owned tokens and resolve still-live waiters at auth completion.
- **Original review:** [User.cxx.review.MD](../Source/Client/Impl/User.cxx.review.MD).

### `BASE-STORAGE-018` - Medium
- **Location/function:** `Source/Client/Impl/User.cxx:43-47,253-259,440-445,624-671`, `SignOut` and auth-state transitions.
- **Issue:** Sign-out emits auth loss but leaves signed-in/logged-on state and pending work live.
- **Proposed solution:** Perform a real runtime sign-out transition, cancel/finish pending operations, and reject late prior-session replies.
- **Original review:** [User.cxx.review.MD](../Source/Client/Impl/User.cxx.review.MD).

### `BASE-STORAGE-019` - Medium
- **Location/function:** `Source/Client/Impl/User.cxx:55-85,107-121,610-671`, `SignInGalaxy` and sign-in waiter handling.
- **Issue:** Explicit timeout is ignored; check-then-enqueue can also miss an already processed successful acceptance.
- **Proposed solution:** Use synchronized auth-operation state with atomic immediate-or-pending admission, deadlines, cancellation, and late-reply suppression.
- **Original review:** [User.cxx.review.MD](../Source/Client/Impl/User.cxx.review.MD).

### `BASE-STORAGE-020` - Medium
- **Location/function:** `Source/Client/Impl/User.cxx:520-527,542-557`, authorization-code and PlayFab methods.
- **Issue:** A null default authorization listener suppresses a valid request, and supplied PlayFab failure listener is not routed.
- **Proposed solution:** Execute valid requests regardless of optional listener and forward nullable/specific listeners through common cancellation-safe completion routing.
- **Original review:** [User.cxx.review.MD](../Source/Client/Impl/User.cxx.review.MD).

### `BASE-STORAGE-021` - Medium
- **Location/function:** `Source/Client/Impl/Telemetry.cxx:58-122`, `Add*Param` methods.
- **Issue:** SDK-valid null array element names are streamed as null C strings.
- **Proposed solution:** Explicitly represent anonymous names/elements with a consistent marker or structured trace representation.
- **Original review:** [Telemetry.cxx.review.MD](../Source/Client/Impl/Telemetry.cxx.review.MD).

### `BASE-STORAGE-023` - Medium
- **Location/function:** `Source/Client/Impl/Telemetry.cxx:16-24,159-175`, constructor and `SendTelemetryEvent`.
- **Issue:** A disabled unopened stream can report its first write as success, and pre-lock state checks race failed writes.
- **Proposed solution:** Define explicit disabled-sink policy and protect enabled/open/error checks, write, flush, and result under one sink lock.
- **Original review:** [Telemetry.cxx.review.MD](../Source/Client/Impl/Telemetry.cxx.review.MD).

### NET

### `BASE-NET-001` - High
- **Location/function:** `Source/Shared/Networking/Networking.hxx:25-63`, `MessageReceiver::ProcessEventFor<T>`.
- **Issue:** Cereal allocates strings, vectors, and pointer graphs from received lengths before direction/authentication or aggregate-budget checks.
- **Proposed solution:** Pre-gate message direction/state and decode bounded value DTOs with checked field/aggregate limits and acyclic ownership rules.
- **Original review:** [Networking.hxx.review.MD](../Source/Shared/Networking/Networking.hxx.review.MD).

### `BASE-NET-002` - High
- **Location/function:** `Source/Shared/Networking/Networking.hxx:58-63`, `MessageReceiver::ProcessEventFor<T>`.
- **Issue:** `Handle()` is outside the decode catch; a sandbox-rejected upload path throws through server dispatch.
- **Proposed solution:** Translate expected path/input failures to operation failure and add a per-event exception boundary that safely rejects the event.
- **Original review:** [Networking.hxx.review.MD](../Source/Shared/Networking/Networking.hxx.review.MD).

### `BASE-NET-003` - High
- **Location/function:** `Source/Shared/Networking/Networking.cxx:20-104,146-214`, `MessageReceiver::ProcessEvent` and `GalaxyNetworkClient::RunNetworking`.
- **Issue:** `ENET_EVENT_TYPE_DISCONNECT_TIMEOUT` is ignored, leaving initial retries unarmed and server/application state stale through ENet slot reuse.
- **Proposed solution:** Normalize both disconnect event types through one retirement path, arm failed-connect retries, and generation-tag cross-thread events.
- **Original review:** [Networking.cxx.review.MD](../Source/Shared/Networking/Networking.cxx.review.MD).

### `BASE-NET-004` - Medium
- **Location/function:** `Source/Shared/Networking/Networking.hxx:173-185`, `GalaxyNetworkServer::Send<T>`.
- **Issue:** An ENet-rejected send leaves the packet caller-owned, but the wrapper neither destroys nor returns it.
- **Proposed solution:** Hold new packets in RAII ownership and release only after successful enqueue; otherwise destroy and report send failure.
- **Original review:** [Networking.hxx.review.MD](../Source/Shared/Networking/Networking.hxx.review.MD).

### `BASE-NET-005` - Medium
- **Location/function:** `Source/Shared/Networking/Networking.hxx:46-56,79-82`, `MessageReceiver::ProcessEventFor<T>` and `ConvertToENetPacket<T>`.
- **Issue:** Class-name IDs have no schema version, while SDK feature gates alter message layouts for peers that can still authenticate.
- **Proposed solution:** Exchange and enforce a protocol/schema fingerprint during handshake, or use version-independent wire DTOs/enums.
- **Original review:** [Networking.hxx.review.MD](../Source/Shared/Networking/Networking.hxx.review.MD).

### `BASE-NET-006` - Medium
- **Location/function:** `Source/Shared/Lobby.hxx:48-59`, `Lobby::serialize`.
- **Issue:** Routine lobby/chat snapshots serialize unbounded retained message history and can exceed transport limits.
- **Proposed solution:** Separate current-state/discovery DTOs from history, page history with byte/count budgets, and handle response-send failure.
- **Original review:** [Lobby.hxx.review.MD](../Source/Shared/Lobby.hxx.review.MD).

### `BASE-NET-007` - Medium
- **Location/function:** `Source/Shared/Networking/Networking.hxx:124-125,142-153`, queue members and `GalaxyNetworkClient::SendAsync`; `Networking.cxx:123-132,146-167,219-226`.
- **Issue:** Shared unbounded inbound/outbound queues retain packets after ENet removes them from waiting-data accounting.
- **Proposed solution:** Enforce configurable queued-byte/event high-water marks, including outbound admission, with explicit disconnect/drop/coalescing behavior.
- **Original review:** [Networking.hxx.review.MD](../Source/Shared/Networking/Networking.hxx.review.MD).

### `BASE-NET-009` - Medium
- **Location/function:** `Source/Shared/IniData.cxx:283-301,350-357`, `IniData::IniData`, `GetGameDataPath`, and `GetServerDataPath`.
- **Issue:** UTF-8 SimpleIni path values are implicitly interpreted using the Windows ANSI code page.
- **Proposed solution:** Explicitly convert UTF-8 to UTF-16/native filesystem paths and define environment-prefix encoding.
- **Original review:** [IniData.cxx.review.MD](../Source/Shared/IniData.cxx.review.MD).

### `BASE-NET-010` - Low
- **Location/function:** `Source/Shared/IniData.cxx:193-237,296-298,435-436`, default-config checks and client initialization.
- **Issue:** First-run boot/client configuration creation excludes the selected plain-AppData fallback.
- **Proposed solution:** Treat both game-specific and plain-AppData managed locations as provisionable while preserving search precedence and reporting failures.
- **Original review:** [IniData.cxx.review.MD](../Source/Shared/IniData.cxx.review.MD).

### `BASE-NET-011` - Low
- **Location/function:** `Source/Shared/IniData.cxx:492-505,565-586`, `ClientIniData::ClientIniData`.
- **Issue:** Account-name and installation-ID branches validate machine-name availability instead of the identity value they will use.
- **Proposed solution:** Retrieve and validate the selected identity itself, then reject missing values or use a documented fallback.
- **Original review:** [IniData.cxx.review.MD](../Source/Shared/IniData.cxx.review.MD).

### `BASE-NET-012` - Low
- **Location/function:** `Source/Shared/IniData.cxx:649-663`, DLC-loading loop in `ClientIniData::ClientIniData`.
- **Issue:** `from_chars` checks only `ec`, accepting numeric prefixes such as `123junk`.
- **Proposed solution:** Require both `ec == std::errc{}` and `result.ptr == input.end()` after deliberate normalization.
- **Original review:** [IniData.cxx.review.MD](../Source/Shared/IniData.cxx.review.MD).

### `BASE-NET-013` - Low
- **Location/function:** `Source/Shared/Networking/Networking.cxx:158-165,186-191,219-226,247-255`, `RunNetworking`, `ProcessEvents`, and `Cleanup`.
- **Issue:** The application can pop an original disconnect before cleanup publishes a synthetic one, producing duplicate logical notifications.
- **Proposed solution:** Publish retirement once from a single state machine, or generation-tag and deduplicate disconnect delivery.
- **Original review:** [Networking.cxx.review.MD](../Source/Shared/Networking/Networking.cxx.review.MD).

### UTIL

### `BASE-UTIL-001` - Medium
- **Location/function:** `Source/Shared_NoVer/AchievementsAndStatsContainer.hxx:51-55`, `AchievementsAndStatsContainer::serialize`.
- **Issue:** Input archives write `PlayTime.load()`'s temporary and never update the atomic counter.
- **Proposed solution:** Split save/load or load through a local `uint32_t` and call `PlayTime.store()` after successful input.
- **Original review:** [AchievementsAndStatsContainer.hxx.review.MD](../Source/Shared_NoVer/AchievementsAndStatsContainer.hxx.review.MD).

### `BASE-UTIL-002` - High
- **Location/function:** `Source/Shared_NoVer/AchievementsAndStatsContainer.cxx:14-19,57-83,109-117,138-146`, copy constructor, `GetStat`, `GetUserData`, and `GetRichPresence`.
- **Issue:** Source maps are copied without locks and getters expose references/pointers after unlocking, racing supported scalar, Copy, mutation, and snapshot operations.
- **Proposed solution:** Return owned values copied while locked and provide locked mutations/coherent multi-map immutable snapshots, including `BootTime`.
- **Original review:** [AchievementsAndStatsContainer.cxx.review.MD](../Source/Shared_NoVer/AchievementsAndStatsContainer.cxx.review.MD).

### `BASE-UTIL-003` - Medium
- **Location/function:** `Source/Shared_NoVer/AchievementsAndStatsContainer.cxx:25-30`, `AchievementsAndStatsContainer::GetPlayTime`.
- **Issue:** Elapsed play time uses local wall clock minus a potentially remote wall-clock anchor, then converts negative durations to unsigned values.
- **Proposed solution:** Persist/transmit accumulated duration and retain only a local steady-clock anchor; version the wire representation if needed.
- **Original review:** [AchievementsAndStatsContainer.cxx.review.MD](../Source/Shared_NoVer/AchievementsAndStatsContainer.cxx.review.MD).

### `BASE-UTIL-004` - Medium
- **Location/function:** `Source/Shared_NoVer/filesystem_container/filesystem_container.cxx:78-104,113-135,144-200`, `get`, `get_or_create`, and `create_shared`.
- **Issue:** Case-sensitive map keys represent one case-insensitive Windows file as separate logical entries.
- **Proposed solution:** Define one Windows-equivalent logical/physical key policy, reject ambiguous aliases, and migrate/reconcile existing aliases.
- **Original review:** [filesystem_container.cxx.review.MD](../Source/Shared_NoVer/filesystem_container/filesystem_container.cxx.review.MD).

### `BASE-UTIL-005` - Medium
- **Location/function:** `Source/Shared_NoVer/filesystem_container/filesystem_container.cxx:123-135,174-204`, `get_or_create` and `create_shared`.
- **Issue:** Creation and metadata-save failures are ignored while entries and shared IDs are published into indexes.
- **Proposed solution:** Make file/metadata creation return status; stage and commit index publication only after completed persistence, preserving prior state on failure.
- **Original review:** [filesystem_container.cxx.review.MD](../Source/Shared_NoVer/filesystem_container/filesystem_container.cxx.review.MD).

### `BASE-UTIL-006` - Medium
- **Location/function:** `Source/Shared_NoVer/filesystem_container/filesystem_container_entry.cxx:91-112`, `filesystem_entry::unlink`.
- **Issue:** Failed data deletion still removes metadata, unregisters the entry, and resets in-memory state.
- **Proposed solution:** Confirm data deletion first; retain registration/metadata on failure and use explicit recovery for partial cleanup.
- **Original review:** [filesystem_container_entry.cxx.review.MD](../Source/Shared_NoVer/filesystem_container/filesystem_container_entry.cxx.review.MD).

### `BASE-UTIL-007` - Medium
- **Location/function:** `Source/Shared_NoVer/filesystem_container/filesystem_container_entry.cxx:188-195`, `filesystem_entry::get_timestamp`.
- **Issue:** MSVC `file_clock` seconds are exposed as Unix seconds without epoch conversion.
- **Proposed solution:** Convert `file_clock` to `system_clock` before seconds/range conversion.
- **Original review:** [filesystem_container_entry.cxx.review.MD](../Source/Shared_NoVer/filesystem_container/filesystem_container_entry.cxx.review.MD).

### `BASE-UTIL-008` - Medium
- **Location/function:** `Source/Shared_NoVer/filesystem_container/filesystem_container_entry.cxx:291-308,351-371`, `filesystem_entry::write` and `save_metadata`.
- **Issue:** `good()` is tested before buffered writes flush/close, and live metadata is truncated before a successful replacement exists.
- **Proposed solution:** Check write/flush/close explicitly and persist through a completed temporary followed by checked replacement.
- **Original review:** [filesystem_container_entry.cxx.review.MD](../Source/Shared_NoVer/filesystem_container/filesystem_container_entry.cxx.review.MD).

### `BASE-UTIL-009` - Medium
- **Location/function:** `Source/Shared_NoVer/filesystem_container/filesystem_container_entry.cxx:150-176`, `filesystem_entry::copy_to(filesystem_entry&)`.
- **Issue:** Failure rollback deletes pre-existing destination data/metadata; final metadata-save failure can leave mixed new state.
- **Proposed solution:** Use staged data/metadata with backups and a two-artifact commit; roll back only artifacts created by this operation.
- **Original review:** [filesystem_container_entry.cxx.review.MD](../Source/Shared_NoVer/filesystem_container/filesystem_container_entry.cxx.review.MD).

### `BASE-UTIL-010` - Medium
- **Location/function:** `Source/Shared_NoVer/filesystem_container/filesystem_container_entry.cxx:238-269`, vector-returning `filesystem_entry::read`.
- **Issue:** A file truncated after sizing can return the original vector length with zero-filled tail bytes as valid data.
- **Proposed solution:** Require an exact read or return explicit partial/error status, and synchronize whole-file sharing reads with writes.
- **Original review:** [filesystem_container_entry.cxx.review.MD](../Source/Shared_NoVer/filesystem_container/filesystem_container_entry.cxx.review.MD).

### `BASE-UTIL-011` - Medium
- **Location/function:** `Source/Shared_NoVer/filesystem_container/filesystem_container.cxx:434-459`, `filesystem_container::get_subcontainer`.
- **Issue:** Unescaped `.` and `..` names normalize to named-container or parent roots, creating independent caches for the same storage.
- **Proposed solution:** Encode every accepted name as a non-special opaque component and enforce containment beneath `named_containers`.
- **Original review:** [filesystem_container.cxx.review.MD](../Source/Shared_NoVer/filesystem_container/filesystem_container.cxx.review.MD).

### `BASE-UTIL-012` - Medium
- **Location/function:** `Source/Shared_NoVer/filesystem_container/filesystem_container.cxx:29-42`, constructor; `filesystem_container_utils.cxx:56-64`, `generic_list_files<T>`.
- **Issue:** Canonicalizing relative listing paths collapses an in-root link and target; failed map insertion is ignored while both entries enter indexes.
- **Proposed solution:** Define/enforce a link policy, preserve the chosen identity, and append indexes only after successful canonical-key insertion.
- **Original review:** [filesystem_container.cxx.review.MD](../Source/Shared_NoVer/filesystem_container/filesystem_container.cxx.review.MD).

### `BASE-UTIL-013` - Medium
- **Location/function:** `Source/Shared_NoVer/MachineInfo.cxx:511-523`, `MachineInfo::MachineInfo`.
- **Issue:** `GetComputerName` already excludes NUL from its returned count, but code subtracts one and drops the final character before hashing.
- **Proposed solution:** Use the complete API-reported count and adopt an explicit A/W encoding policy; plan migration for changed derived identities.
- **Original review:** [MachineInfo.cxx.review.MD](../Source/Shared_NoVer/MachineInfo.cxx.review.MD).

### `BASE-UTIL-014` - Low
- **Location/function:** `Source/Shared_NoVer/MachineInfo.cxx:97-105`, `RetriveLocalMacAddress`.
- **Issue:** The output `HeapAlloc` is dereferenced without a null check after adapter enumeration succeeds.
- **Proposed solution:** Check allocation, free the adapter buffer on failure, and return explicit unavailable-MAC status with RAII storage.
- **Original review:** [MachineInfo.cxx.review.MD](../Source/Shared_NoVer/MachineInfo.cxx.review.MD).

### `BASE-UTIL-015` - Informational
- **Location/function:** `Source/Shared_NoVer/SharedLibUtils.cxx:99-118`, `SharedLibUtils::SharedLibUtils`; `Source/Shared_NoVer/CMakeLists.txt:3-13`.
- **Issue:** A once-compiled common loader cannot receive the RED-prefix feature used by future versioned interceptor variants; no current SDK activates that branch.
- **Proposed solution:** Have version-aware code supply the complete DLL filename to the generic loader, or compile the loader per version.
- **Original review:** [SharedLibUtils.cxx.review.MD](../Source/Shared_NoVer/SharedLibUtils.cxx.review.MD).

### `BASE-UTIL-016` - Low
- **Location/function:** `Source/Shared_NoVer/filesystem_container/filesystem_container.cxx:365-381`, disk-space getters.
- **Issue:** Failed `std::filesystem::space` calls return sentinels reported as huge valid capacity and potentially zero use.
- **Proposed solution:** Take one checked `space_info` snapshot and propagate failure or a documented unknown/conservative result.
- **Original review:** [filesystem_container.cxx.review.MD](../Source/Shared_NoVer/filesystem_container/filesystem_container.cxx.review.MD).

### SERVER

### `BASE-SERVER-001` - Medium
- **Location/function:** `Source/Server/ServerHandlers.cxx:77-130`, `Server::Handle(KeyChallengeMessage)`.
- **Issue:** Rejected authentication resets ENet without application cleanup; slot reuse loses `Data` and leaks it.
- **Proposed solution:** Perform one idempotent application cleanup of memberships, maps, and `Data` before every forced transport reset.
- **Original review:** [ServerHandlers.cxx.review.MD](../Source/Server/ServerHandlers.cxx.review.MD).

### `BASE-SERVER-003` - Medium
- **Location/function:** `Source/Server/ServerHandlers.cxx:543-578`, `Server::Handle(JoinLobbyMessage)`.
- **Issue:** Cached-ID joins check capacity but not non-joinable and applicable private/invite admission rules.
- **Proposed solution:** Enforce joinability and explicit supported type/invite policy immediately before adding membership.
- **Original review:** [ServerHandlers.cxx.review.MD](../Source/Server/ServerHandlers.cxx.review.MD).

### `BASE-SERVER-004` - Medium
- **Location/function:** `Source/Server/ServerHandlers.cxx:397-427`, `Server::Handle(P2PNetworkPacketMessage)`.
- **Issue:** Lobby-ID P2P forwarding checks lobby existence/owner but not that sender is an active lobby member.
- **Proposed solution:** Require active-lobby membership before lobby-addressed forwarding and define any pre-join route separately.
- **Original review:** [ServerHandlers.cxx.review.MD](../Source/Server/ServerHandlers.cxx.review.MD).

### `BASE-SERVER-005` - Medium
- **Location/function:** `Source/Server/ServerHandlers.cxx:703-729,748-797`, `BoilerplateHandleLobbyDataUpdate` and structural lobby handlers.
- **Issue:** Failed owner checks return the request's optimistic value because rollback callback is unused; clients cache it before checking failure.
- **Proposed solution:** Return authoritative rollback values for existing lobbies, define safe nonexistent-lobby failures, and defer client mutation or refresh on failure.
- **Original review:** [ServerHandlers.cxx.review.MD](../Source/Server/ServerHandlers.cxx.review.MD).

### `BASE-SERVER-006` - Medium
- **Location/function:** `Source/Server/ServerHandlers.cxx:464-466`, `Server::Handle(FileShareMessage)`.
- **Issue:** Fresh shared-ID counter is opened through a non-creating path, so counter writes fail and IDs repeat after restart.
- **Proposed solution:** Explicitly create and durably update control state, validate/recover it from committed metadata, and use a checked high-water counter.
- **Original review:** [ServerHandlers.cxx.review.MD](../Source/Server/ServerHandlers.cxx.review.MD).

### `BASE-SERVER-007` - Medium
- **Location/function:** `Source/Server/ServerHandlers.cxx:464-476`, `Server::Handle(FileShareMessage)`.
- **Issue:** Failed creation/write or repeated filename still receives a new nonzero shared-file ID although no usable object was committed.
- **Proposed solution:** Commit data/metadata before success, return zero-ID failure and roll back partial entries, and define repeated-name update/immutability semantics.
- **Original review:** [ServerHandlers.cxx.review.MD](../Source/Server/ServerHandlers.cxx.review.MD).

### `BASE-SERVER-008` - Medium
- **Location/function:** `Source/Server/ServerHandlers.cxx:214-243,263-294`, `Handle(RequestChatRoomWithUserMessage)` and `Handle(SendToChatRoomMessage)`.
- **Issue:** Fan-out reuses the sender's request ID; matching recipient listener IDs can be consumed and recipient gets wrong interlocutor ID.
- **Proposed solution:** Send correlated replies only to requester, send recipient notifications with zero/distinct IDs, and send correct peer identity.
- **Original review:** [ServerHandlers.cxx.review.MD](../Source/Server/ServerHandlers.cxx.review.MD).

### `BASE-SERVER-009` - Medium
- **Location/function:** `Source/Tracer/Stacker.cxx:102-117,161-175,207-214`, `StackerUnhandledExceptionCallback` and `OurCrashHandler`.
- **Issue:** Original `EXCEPTION_POINTERS` are dropped, so stack walking/minidumps use handler/current context and synthetic exception code.
- **Proposed solution:** Preserve/copy original exception record/context, walk it, and pass it with original fault thread to minidump generation.
- **Original review:** [Stacker.cxx.review.MD](../Source/Tracer/Stacker.cxx.review.MD).

### `BASE-SERVER-010` - Medium
- **Location/function:** `Source/Tracer/Tracer.cxx:98,389-415`, `LogUnhandledExceptionOccurred` and `Tracer::Exit`.
- **Issue:** Direct `ofstream::flush()` accesses the shared wrapped file outside `osyncstream` synchronization.
- **Proposed solution:** Put every global-file emit/flush behind one synchronization discipline: synchronized emit-and-flush or one shared mutex.
- **Original review:** [Tracer.cxx.review.MD](../Source/Tracer/Tracer.cxx.review.MD).

### `BASE-SERVER-011` - Low
- **Location/function:** `Source/Tracer/Tracer.cxx:191-207`, `Trace::InitTracing`.
- **Issue:** An already-existing same-second trace directory makes `create_directories` return false and disables tracing.
- **Proposed solution:** Generate unique session directories with PID/high-resolution timestamp/suffix retry and distinguish exists from filesystem errors.
- **Original review:** [Tracer.cxx.review.MD](../Source/Tracer/Tracer.cxx.review.MD).

### `BASE-SERVER-012` - Medium
- **Location/function:** `Source/SystemTests/Runner/Main.cxx:136-138`, `runner::run`.
- **Issue:** Runner snapshots logs before observing child exit and can reject a flushed terminal PASS it has not drained.
- **Proposed solution:** On exit transition, drain remaining complete records before applying PASS/event/exit predicates.
- **Original review:** [Main.cxx.review.MD](../Source/SystemTests/Runner/Main.cxx.review.MD).

### `BASE-SERVER-013` - Medium
- **Location/function:** `Source/SystemTests/Runner/Model.cxx:127-154`, `runner::parseScenario`.
- **Issue:** Role and persistence-group tokens permit dot/internal/case-equivalent Windows path aliases, breaking staging/scheduling isolation.
- **Proposed solution:** Map logical roles/groups to generated staging paths and reject Windows-equivalent aliases, reserved/internal names, and dot segments.
- **Original review:** [Model.cxx.review.MD](../Source/SystemTests/Runner/Model.cxx.review.MD).

### `BASE-SERVER-014` - Medium
- **Location/function:** `Source/SystemTests/Host/Chat.cxx:8-30`, `ChatRoomMessagesListener::OnChatRoomMessagesReceived`.
- **Issue:** Typed-ID chat SDKs before `ChatMessageType` compile unguarded newer declarations and retrieval signature.
- **Proposed solution:** Gate body/listener by `HAS_ICHAT_MESSAGETYPE` or provide exact legacy-signature branches.
- **Original review:** [Chat.cxx.review.MD](../Source/SystemTests/Host/Chat.cxx.review.MD).

### `BASE-SERVER-015` - Low
- **Location/function:** `Source/SystemTests/Runner/Process.cxx:39-41`, `runner::startChild`.
- **Issue:** Native narrow Windows paths are assembled then interpreted as UTF-8, corrupting or rejecting non-UTF-8 executable/control paths.
- **Proposed solution:** Build and quote command line in UTF-16 from native paths, explicitly convert textual arguments, and align child decoding.
- **Original review:** [Process.cxx.review.MD](../Source/SystemTests/Runner/Process.cxx.review.MD).

### `BASE-SERVER-016` - Medium
- **Location/function:** `Source/Server/Server.cxx:90-103`, `Server::Server`.
- **Issue:** Startup logs effective challenge-key material that directly enables future challenge responses.
- **Proposed solution:** Do not log protocol key; log only configuration state or separately derived non-reusable diagnostic fingerprint.
- **Original review:** [Server.cxx.review.MD](../Source/Server/Server.cxx.review.MD).

### `BASE-SERVER-017` - Low
- **Location/function:** `Source/Tracer/Stacker.cxx:165-175,207-214`, `StackerUnhandledExceptionCallback` and `OurCrashHandler`.
- **Issue:** Minidump creation is reachable only through non-null text logging callback, so dump-only configuration creates no dump.
- **Proposed solution:** Run crash processing when either logging or dumps is enabled and permit null text callbacks.
- **Original review:** [Stacker.cxx.review.MD](../Source/Tracer/Stacker.cxx.review.MD).

### `BASE-SERVER-018` - Medium
- **Location/function:** `Source/Server/Server.cxx:172-177`, `Server::Tick`.
- **Issue:** `while (connection.Pull())` treats negative service failures as events, causing persistent spin and skipping sweeps/sleep.
- **Proposed solution:** Process only positive pulls, distinguish zero from failure, and use logged restart/backoff/bounded retry on errors.
- **Original review:** [Server.cxx.review.MD](../Source/Server/Server.cxx.review.MD).

### `BASE-SERVER-019` - Medium
- **Location/function:** `Source/Server/ServerHandlers.cxx:199-210,703-735,923-957`, broadcast paths.
- **Issue:** Transport broadcasts target all ENet-connected peers, including peers awaiting challenge completion.
- **Proposed solution:** Centralize broadcasts over authenticated identity-linked recipients and reserve pre-auth delivery for handshake/ping only.
- **Original review:** [ServerHandlers.cxx.review.MD](../Source/Server/ServerHandlers.cxx.review.MD).

### INTERCEPT

### `BASE-INTERCEPT-001` - Medium
- **Location/function:** `Source/InterceptionLogger/GalaxyDLL.cxx:72-86`, `Shutdown`/`ShutdownEx`; `UniverseGameServer.cxx:39-54`, game-server shutdown.
- **Issue:** Real SDK shutdown precedes destruction/unregistration of interceptor-owned listeners using the borrowed registrar. Native registrar destruction/UAF impact remains conditional.
- **Proposed solution:** Quiesce callbacks and detach owned listeners/proxies while registrar is live, then invoke real shutdown and clear wrappers.
- **Original review:** [GalaxyDLL.cxx.review.MD](../Source/InterceptionLogger/GalaxyDLL.cxx.review.MD).

### `BASE-INTERCEPT-002` - High
- **Location/function:** `Source/InterceptionLogger/Impl/Listeners/ProxifySingleShotListener.hxx:56-64`, proxy callback macro; `ListenerRegistrar.cxx:43-48`, `Unregister`.
- **Issue:** Callback completion and concurrent cancellation each claim raw ownership and can delete the same proxy.
- **Proposed solution:** Use a single retirement state machine with callback/cancellation lifetime pins and exactly one final deletion decision.
- **Original review:** [ProxifySingleShotListener.hxx.review.MD](../Source/InterceptionLogger/Impl/Listeners/ProxifySingleShotListener.hxx.review.MD).

### `BASE-INTERCEPT-003` - High
- **Location/function:** `Source/InterceptionLogger/Impl/ListenerRegistrar.cxx:43-48`, `Unregister`; `Listeners/ProxifySingleShotListener.hxx:16-20,43-50`.
- **Issue:** Target-only proxy lookup lets one client/server session unregister and delete another session's still-registered proxy.
- **Proposed solution:** Store immutable registrar/session and listener-type identity in each proxy record; cancel/retire only owning session records.
- **Original review:** [ListenerRegistrar.cxx.review.MD](../Source/InterceptionLogger/Impl/ListenerRegistrar.cxx.review.MD).

### `BASE-INTERCEPT-004` - High
- **Location/function:** `Source/InterceptionLogger/Impl/Listeners/UserListener.cxx:27-30`, `AuthListener::OnAuthSuccess`.
- **Issue:** Successful authentication only traces; it neither forwards to supplied specific listener nor retires its proxy.
- **Proposed solution:** Forward `OnAuthSuccess` to non-null targets and retire through corrected proxy-lifetime protocol.
- **Original review:** [UserListener.cxx.review.MD](../Source/InterceptionLogger/Impl/Listeners/UserListener.cxx.review.MD).

### `BASE-INTERCEPT-005` - High
- **Location/function:** `Source/InterceptionLogger/Impl/Networking.cxx:83-89,115-121`, `PeekP2PPacket`/`ReadP2PPacket`; `Impl/Stats.cxx:525-550`, leaderboard details.
- **Issue:** Trace code treats returned object size as readable buffer length despite documented truncation and can read beyond caller destination.
- **Proposed solution:** Inspect only non-null successful spans bounded by `min(capacity, valid-written-length)` and preserve caller-visible result/error semantics.
- **Original review:** [Networking.cxx.review.MD](../Source/InterceptionLogger/Impl/Networking.cxx.review.MD).

### `BASE-INTERCEPT-006` - High
- **Location/function:** `Source/InterceptionLogger/Impl/Listeners/MatchmakingListener.cxx:25-47,74-97`, `LobbyListListener::OnLobbyList` and `LobbyLeftListener::OnLobbyLeft`.
- **Issue:** Forwarding uses operation-listener availability instead of list-result/leave-reason type transition gates, suppressing valid legacy callbacks.
- **Proposed solution:** Gate each active override with exact result/leave feature macros while retaining `override`.
- **Original review:** [MatchmakingListener.cxx.review.MD](../Source/InterceptionLogger/Impl/Listeners/MatchmakingListener.cxx.review.MD).

### `BASE-INTERCEPT-007` - High
- **Location/function:** `Source/InterceptionLogger/UniverseLANInterceptor.cxx:133-140,263-264,283-284`, `InterfaceInstances::init`.
- **Issue:** Mandatory resolver requests factory and game-server exports absent from supported SDK ranges.
- **Proposed solution:** Use exact version/export descriptors: early factory `GetInstance`/`Reset`, and exact game-server Utils/Telemetry feature gates.
- **Original review:** [UniverseLANInterceptor.cxx.review.MD](../Source/InterceptionLogger/UniverseLANInterceptor.cxx.review.MD).

### `BASE-INTERCEPT-008` - Medium
- **Location/function:** `Source/InterceptionLogger/GalaxyDLL.cxx:37-59,72-77,164-180`, client `Init`, `Shutdown`, `ProcessData`, and `GetError`.
- **Issue:** Init swallows exceptions and leaves absent error state/empty cleanup callables; later wrapper setup can overwrite initial failure.
- **Proposed solution:** Make initialization transactional with explicit partial-failure state, preserve initial error before setup calls, and make cleanup safe at every stage.
- **Original review:** [GalaxyDLL.cxx.review.MD](../Source/InterceptionLogger/GalaxyDLL.cxx.review.MD).

### `BASE-INTERCEPT-009` - Medium
- **Location/function:** `Source/InterceptionLogger/GalaxyApiFactory.cxx:178-185`, `GalaxyFactory::GetInstance`.
- **Issue:** Newer factory `GetInstance` creates interceptor instance, defeating null-query guards for pre-init/repeated shutdown and `ProcessData`.
- **Proposed solution:** Preserve create-on-query only for old SDKs; newer `GetInstance` returns existing/null and `CreateInstance` owns creation.
- **Original review:** [GalaxyApiFactory.cxx.review.MD](../Source/InterceptionLogger/GalaxyApiFactory.cxx.review.MD).

### `BASE-INTERCEPT-010` - Medium
- **Location/function:** `Source/InterceptionLogger/GalaxyGameServerApi.cxx:24-28`, exported `ShutdownGameServerEx`.
- **Issue:** The options overload calls ordinary shutdown and drops `preserveStaticObjects`.
- **Proposed solution:** Forward to `gameserver.ShutdownGameServerEx(shutdownOptions)` after separate pre-shutdown listener detachment.
- **Original review:** [GalaxyGameServerApi.cxx.review.MD](../Source/InterceptionLogger/GalaxyGameServerApi.cxx.review.MD).

### `BASE-INTERCEPT-011` - Medium
- **Location/function:** `Source/InterceptionLogger/Impl/User.cxx:205-206,244-245,703-727,760-782,793-795,835-856`, token/key/code methods.
- **Issue:** Enabled tracing persists reusable refresh/access/ID tokens, authorization codes, server keys, and PlayFab secrets.
- **Proposed solution:** Use typed sensitive-value redaction for inputs/results and log only presence, type, and safe metadata.
- **Original review:** [User.cxx.review.MD](../Source/InterceptionLogger/Impl/User.cxx.review.MD).

## Follow-up canonical findings

### `ADD-CORE-001` - Medium
- **Location/function:** `Source/Client/UniverseLAN.cxx:38-50,64-66`, `InterfaceInstances::init`.
- **Issue:** Transport construction can throw before `AppsImpl` exists, leaving documented offline DLC/language APIs unavailable.
- **Proposed solution:** Construct/preserve offline-capable Apps independently of transport failure and define safe online-dependent failures.
- **Original review:** [UniverseLAN.cxx.review.MD](../Source/Client/UniverseLAN.cxx.review.MD).

### `ADD-CORE-002` - Medium
- **Location/function:** `Source/Client/Client.cxx:23-33,61-67`, `Client::Client` and `Client::Start`.
- **Issue:** Normalized local bind host/port and custom thread factory are accepted but ignored in favor of relay settings, null bind, and `std::thread`.
- **Proposed solution:** Apply local endpoint/factory at connection/worker creation or reject unsupported non-default options explicitly.
- **Original review:** [Client.cxx.review.MD](../Source/Client/Client.cxx.review.MD).

### `ADD-CORE-003` - Medium
- **Location/function:** `Source/Client/UniverseGameServer.cxx:25-28,53`, `UniverseGameServer::InitGameServer`.
- **Issue:** Client and game-server graphs use the same configured Galaxy identity, so relay duplicate-ID admission rejects the second session.
- **Proposed solution:** Make runtime role select independently allocated/persisted game-server identity while retaining relay uniqueness checks.
- **Original review:** [UniverseGameServer.cxx.review.MD](../Source/Client/UniverseGameServer.cxx.review.MD).

### `ADD-API-001` - Informational
- **Location/function:** `Source/Client/Impl/Friends.cxx:363-380,558-570`, `FriendsImpl::DeleteRichPresence` and `GetRichPresenceKeyByIndex`.
- **Issue:** Deleting a borrowed indexed key erases its owning map node, then serializes through freed `char*`; SDK permission to pass that borrowed pointer into the mutating call is unresolved.
- **Proposed solution:** Copy/snapshot key before erase and use owned value for both erase and outgoing message; promote only after SDK contract resolution.
- **Original review:** [Friends.cxx.review.MD](../Source/Client/Impl/Friends.cxx.review.MD).

### `ADD-API-002` - Informational
- **Location/function:** `Source/Client/Impl/Friends.cxx:444-457`, `FriendsImpl::RequestRichPresence`.
- **Issue:** Default zero/self selector resolves locally for storage but is emitted unchanged as invalid callback identity; native zero-means-self convention is unresolved.
- **Proposed solution:** Publish resolved configured local ID for self branch while retaining concrete remote IDs, after confirming versioned contract.
- **Original review:** [Friends.cxx.review.MD](../Source/Client/Impl/Friends.cxx.review.MD).

### `ADD-API-003` - Medium
- **Location/function:** `Source/Client/Impl/Matchmaking.cxx:1112-1157`, `LobbyMemberStateChange` and `LobbyOwnerChange`.
- **Issue:** Membership/owner callbacks are deferred while later lobby events are synchronous, allowing later traffic/cache state to overtake transition.
- **Proposed solution:** Preserve receive order for state application and notifications, notifying outside lock synchronously where supported.
- **Original review:** [Matchmaking.cxx.review.MD](../Source/Client/Impl/Matchmaking.cxx.review.MD).

### `ADD-API-004` - Medium
- **Location/function:** `Source/Client/Impl/Networking.cxx:153-168`, `NetworkingImpl::AddPacket`.
- **Issue:** Legacy server-queue packets notify `INetworkingListener` instead of `IServerNetworkingListener`; wrong-listener success can auto-pop unseen packet.
- **Proposed solution:** Dispatch and auto-pop according to receiving queue/interface, using server networking for legacy server queue.
- **Original review:** [Networking.cxx.review.MD](../Source/Client/Impl/Networking.cxx.review.MD).

### `ADD-STORAGE-001` - Informational
- **Location/function:** `Source/Client/Impl/CloudStorage.cxx:395-409`, callback `CloudStorageImpl::PutFile`.
- **Issue:** Nested same-thread producer callbacks share TLS scratch buffer, allowing upload B to overwrite upload A's chunk; callback reentrancy permission is unresolved.
- **Proposed solution:** Use per-invocation/per-operation scratch storage through callback-result consumption; promote only after contract resolution.
- **Original review:** [CloudStorage.cxx.review.MD](../Source/Client/Impl/CloudStorage.cxx.review.MD).

### `ADD-STORAGE-002` - Medium
- **Location/function:** `Source/Client/Impl/CloudStorage.cxx:152-200,244-255,499-540`, `GetFile` overloads and buffered `PutFile`.
- **Issue:** Bytes can come from generation A while metadata/type/save ID is sampled from successful replacement B.
- **Proposed solution:** Publish data and metadata as one committed generation and snapshot both before invoking callbacks.
- **Original review:** [CloudStorage.cxx.review.MD](../Source/Client/Impl/CloudStorage.cxx.review.MD).

### `ADD-STORAGE-003` - Medium
- **Location/function:** `Source/Client/Impl/CloudStorage.cxx:55-60`, `CloudStorageImpl::GetFileList`.
- **Issue:** Independently saturating total and used volume to `UINT32_MAX` reports zero headroom on healthy large volumes.
- **Proposed solution:** Calculate coherent quota/used pair jointly in wide type with explicit local quota semantics.
- **Original review:** [CloudStorage.cxx.review.MD](../Source/Client/Impl/CloudStorage.cxx.review.MD).

### `ADD-STORAGE-004` - Medium
- **Location/function:** `Source/Client/Impl/Stats.cxx:419-449`, `StatsImpl::RequestUserTimePlayed`.
- **Issue:** Presence-map membership is treated as hydrated remote playtime, so online placeholder yields fabricated success.
- **Proposed solution:** Track per-domain hydration/pending state; only complete local-cache stats may satisfy fast path.
- **Original review:** [Stats.cxx.review.MD](../Source/Client/Impl/Stats.cxx.review.MD).

### `ADD-STORAGE-005` - Medium
- **Location/function:** `Source/Client/Impl/User.cxx:297-318`, `UserImpl::SpecificUserDataRequestProcessed`.
- **Issue:** Newer per-call listener feature gate suppresses required older global remote-user-data completion.
- **Proposed solution:** Always notify supported global listener and add per-operation dispatch only where that API exists.
- **Original review:** [User.cxx.review.MD](../Source/Client/Impl/User.cxx.review.MD).

### `ADD-NET-002` - Medium
- **Location/function:** `Source/Shared/IniData.cxx:692-709,898-912`, client initialization and `SaveStatsAndAchievements`.
- **Issue:** Default SimpleIni persistence truncates multiline values and trims significant whitespace, corrupting valid user-data on reload.
- **Proposed solution:** Use versioned reversible encoding or byte-safe data format with legacy migration.
- **Original review:** [IniData.cxx.review.MD](../Source/Shared/IniData.cxx.review.MD).

### `ADD-NET-003` - Medium
- **Location/function:** `Source/Shared/Networking/Networking.cxx:123-132,186-214,247-262`, `DispatchQueuedPackets`, `RunNetworking`, and `Cleanup`.
- **Issue:** Disconnect destroys raw packets/replies but does not retire Client operation listeners or lobby filters.
- **Proposed solution:** Add session-generation retirement that issues exactly-once failure/cancellation and clears auxiliary request state.
- **Original review:** [Networking.cxx.review.MD](../Source/Shared/Networking/Networking.cxx.review.MD).

### `ADD-UTIL-001` - High
- **Location/function:** `Source/Shared_NoVer/filesystem_container/filesystem_container.cxx:78-104,113-136,287-351`, `get`, `get_or_create`, and `remove`.
- **Issue:** Stale existence/removal can unlink replacement file and erase map registration while leaving vector/index state inconsistent.
- **Proposed solution:** Use generation-aware entry transactions spanning existence, deletion, share ID, and membership maps; erase only if maps still reference entry.
- **Original review:** [filesystem_container.cxx.review.MD](../Source/Shared_NoVer/filesystem_container/filesystem_container.cxx.review.MD).

### `ADD-UTIL-003` - Medium
- **Location/function:** `Source/Shared_NoVer/filesystem_container/filesystem_container_entry.cxx:351-371`, `filesystem_entry::save_metadata`.
- **Issue:** Separate truncating streams can interleave two successful metadata archives; per-map locks do not protect full record/file commit.
- **Proposed solution:** Create one owned metadata snapshot, serialize to unique temporary, then make versioned/atomic commit under entry transaction.
- **Original review:** [filesystem_container_entry.cxx.review.MD](../Source/Shared_NoVer/filesystem_container/filesystem_container_entry.cxx.review.MD).

### `ADD-UTIL-004` - Informational
- **Location/function:** `Source/Shared_NoVer/filesystem_container/filesystem_container_entry.cxx:135-147,150-176`, `notify_copy_done` and `copy_to`.
- **Issue:** Successful copy with final empty metadata skips persistence/deletion, allowing obsolete attributes or source share ID to reappear after reload; route is dormant.
- **Proposed solution:** Persist exact final record, including empty/deleted state, inside copy transaction before enabling affected route.
- **Original review:** [filesystem_container_entry.cxx.review.MD](../Source/Shared_NoVer/filesystem_container/filesystem_container_entry.cxx.review.MD).

### `ADD-UTIL-005` - Medium
- **Location/function:** `Source/Shared_NoVer/filesystem_container/filesystem_container_entry.cxx:223-230,248-269`, `get_size` and whole-file `read`.
- **Issue:** x86 narrows 64-bit file size before validation, making 4 GiB+ files appear as small successful prefix read.
- **Proposed solution:** Retain wide sizes through checks and reject/stream oversize data before narrowing.
- **Original review:** [filesystem_container_entry.cxx.review.MD](../Source/Shared_NoVer/filesystem_container/filesystem_container_entry.cxx.review.MD).

### `ADD-UTIL-006` - Medium
- **Location/function:** `Source/Shared_NoVer/filesystem_container/filesystem_container.cxx:247-255`, `get_path_metadata` overloads.
- **Issue:** Valid names such as `save` and `save.metadata/part` require one metadata path component to be both file and directory.
- **Proposed solution:** Use prefix-conflict-free encoded/hash metadata layout and migrate stored records.
- **Original review:** [filesystem_container.cxx.review.MD](../Source/Shared_NoVer/filesystem_container/filesystem_container.cxx.review.MD).

### `ADD-SERVER-001` - High
- **Location/function:** `Source/Server/ServerHandlers.cxx:455-476`, `Server::Handle(FileShareMessage)`.
- **Issue:** User-controlled `shared-id.counter` can occupy internal counter namespace and next startup parses nonnumeric user content.
- **Proposed solution:** Separate control state from upload namespace, validate complete numeric counters, and recover from committed IDs.
- **Original review:** [ServerHandlers.cxx.review.MD](../Source/Server/ServerHandlers.cxx.review.MD).

### `ADD-SERVER-002` - Medium
- **Location/function:** `Source/Server/ServerHandlers.cxx:171-173,532-540,613-630`, `Handle(UserHelloDataMessage)`, `Handle(RequestLobbyListMessage)`, and `Handle(RequestLobbyDataMessage)`.
- **Issue:** Full lobby snapshots disclose member roster/data and message history to authenticated nonmembers.
- **Proposed solution:** Send recipient-specific public summaries to nonmembers and member/history DTOs only to authorized members.
- **Original review:** [ServerHandlers.cxx.review.MD](../Source/Server/ServerHandlers.cxx.review.MD).

### `ADD-SERVER-003` - Low
- **Location/function:** `Source/Tracer/Stacker.cxx:64-85,161-175,207-220`, `MyStackWalker::OnCallstackEntry` and crash-report continuation.
- **Issue:** Source-symbol path over 260 characters throws during bounded conversion, bypassing normal log/dump handling.
- **Proposed solution:** Use explicit nonthrowing bounded conversion with truncation indication and keep dump production independent from stack text.
- **Original review:** [Stacker.cxx.review.MD](../Source/Tracer/Stacker.cxx.review.MD).

### `ADD-INTERCEPT-001` - Medium
- **Location/function:** `Source/InterceptionLogger/GalaxyApiFactory.cxx:155-169,188-197`, `ErrorManager::GetLastError` and `GalaxyFactory::GetErrorManager`.
- **Issue:** Factory public error-manager always returns null, hiding ordinary post-init SDK errors.
- **Proposed solution:** Forward real factory error manager or compatible facade and keep factory/direct error routes consistent.
- **Original review:** [GalaxyApiFactory.cxx.review.MD](../Source/InterceptionLogger/GalaxyApiFactory.cxx.review.MD).

### `ADD-INTERCEPT-002` - Medium
- **Location/function:** `Source/InterceptionLogger/UniverseLANInterceptor.cxx:145-166`, `InterfaceInstances::init`; `Impl/InitOptionsModern.cxx:10-33,148-176`, options conversion.
- **Issue:** Legacy options Init is reduced to string Init/InitLocal, losing config path, often peer path, and requested exception policy.
- **Proposed solution:** Reconstruct/call exact legacy `InitOptions` overload, preserving every supported field and const exception-policy value.
- **Original review:** [UniverseLANInterceptor.cxx.review.MD](../Source/InterceptionLogger/UniverseLANInterceptor.cxx.review.MD).

### `ADD-INTERCEPT-003` - Medium
- **Location/function:** `Source/InterceptionLogger/Impl/Apps.cxx:121-136`, `AppsImpl::IsDlcOwned`.
- **Issue:** Forced-DLC mode invokes listener inline instead of during `ProcessData`, causing unexpected reentrancy and lost completion state.
- **Proposed solution:** Queue cancellable synthetic completion through normal pump/proxy lifecycle.
- **Original review:** [Apps.cxx.review.MD](../Source/InterceptionLogger/Impl/Apps.cxx.review.MD).

### `ADD-BUILD-001` - Medium
- **Location/function:** `Source/DLLs/CMakeLists.txt:153-183`, interceptor target and producer-only `POST_BUILD` staging commands.
- **Issue:** Individually built interceptor-mode testcase has no dependency on client/interceptor/server staging producers, so required runtime DLLs may be absent.
- **Proposed solution:** Make each testcase depend on version/config runtime-staging target that owns all required copies.
- **Original review:** [CMakeLists.txt.review.MD](../Source/DLLs/CMakeLists.txt.review.MD).

### `ADD-ABI-001` - High
- **Location/function:** `Source/Client/Impl/ListenerRegistrar.hxx:213-250`, `ListenerRegistrarImpl::NotifyAllNow` template overloads.
- **Issue:** SDK 1.73.0-1.75.0 leaderboard and time-played listeners share tag 26; registrar C-casts bucket entries to unrelated callback interface and invokes wrong vtable slot.
- **Proposed solution:** Implement ABI-preserving collision-aware typed receiver records/discrimination, with defined fallback where compatible RTTI is unavailable.
- **Original review:** [ListenerRegistrar.hxx.review.MD](../Source/Client/Impl/ListenerRegistrar.hxx.review.MD).

## Alias findings, not additional groups

### `BASE-SERVER-002` - Alias of `BASE-NET-003`
- **Location/function:** `Source/Server/Server.cxx:172-188`, `Server::Tick`.
- **Issue:** Ignored ENet timeout event allows old-ID lookup through reused slot, stale memberships, and a possible null-user dereference.
- **Proposed solution:** Dispatch both disconnect events, clean application state before reattachment, and validate connection generation/ownership on ID lookup.
- **Original review:** [Server.cxx.review.MD](../Source/Server/Server.cxx.review.MD); canonical [Networking.cxx.review.MD](../Source/Shared/Networking/Networking.cxx.review.MD).

### `BASE-API-010` - Alias of `BASE-SERVER-005`
- **Location/function:** `Source/Client/Impl/Matchmaking.cxx:436-503,552-618,635-699`, structural setters and response handlers.
- **Issue:** Rejected structural updates retain optimistic cache values; server rollback callback is unused.
- **Proposed solution:** Apply only acknowledged updates or retain versioned acknowledged state and authoritative rollback/invalidation for failure.
- **Original review:** [Matchmaking.cxx.review.MD](../Source/Client/Impl/Matchmaking.cxx.review.MD); canonical [ServerHandlers.cxx.review.MD](../Source/Server/ServerHandlers.cxx.review.MD).

### `BASE-NET-008` - Alias of `BASE-STORAGE-011`
- **Location/function:** `Source/Shared/IniData.cxx:835-861,885-912`, `ClientIniData::SaveStatsAndAchievements`.
- **Issue:** Dirty achievements are acknowledged before persistence; caller can report success despite write/flush/close failure or stale save.
- **Proposed solution:** Commit checked versioned snapshots through temporary-file replacement, clear only committed revisions, and propagate failure to caller.
- **Original review:** [IniData.cxx.review.MD](../Source/Shared/IniData.cxx.review.MD); canonical [Stats.cxx.review.MD](../Source/Client/Impl/Stats.cxx.review.MD).

### `BASE-STORAGE-012` - Alias of `BASE-UTIL-002`
- **Location/function:** `Source/Client/Impl/Stats.cxx:63-124,177-197,201-224`, stat/achievement accessors; canonical container at `Shared_NoVer/AchievementsAndStatsContainer.cxx:57-83,109-117,138-146`.
- **Issue:** Facade uses references/pointers after container locks release; remote replacement can invalidate them.
- **Proposed solution:** Read/mutate under container locks or return owning value snapshots; do not invoke game callbacks while locked.
- **Original review:** [Stats.cxx.review.MD](../Source/Client/Impl/Stats.cxx.review.MD); canonical [AchievementsAndStatsContainer.cxx.review.MD](../Source/Shared_NoVer/AchievementsAndStatsContainer.cxx.review.MD).

### `BASE-STORAGE-022` - Alias of `BASE-UTIL-002`
- **Location/function:** `Source/Client/Impl/User.cxx:348-358`, `GetUserDataCopy`; canonical container at `Shared_NoVer/AchievementsAndStatsContainer.cxx:109-117`.
- **Issue:** Copy binds unlocked mutable string reference; update or map replacement can invalidate it during copy.
- **Proposed solution:** Copy under user-data lock or return owning snapshot from shared container.
- **Original review:** [User.cxx.review.MD](../Source/Client/Impl/User.cxx.review.MD); canonical [AchievementsAndStatsContainer.cxx.review.MD](../Source/Shared_NoVer/AchievementsAndStatsContainer.cxx.review.MD).

### `ADD-NET-001` - Alias of `BASE-SERVER-019`
- **Location/function:** `Source/Shared/Networking/Networking.hxx:193-231`, `GalaxyNetworkServer::Broadcast` templates.
- **Issue:** Application fan-out selects transport-connected peers, including challenge-pending peers.
- **Proposed solution:** Route application broadcasts only to admitted, hello-complete sessions and keep handshake traffic separate.
- **Original review:** [Networking.hxx.review.MD](../Source/Shared/Networking/Networking.hxx.review.MD); canonical [ServerHandlers.cxx.review.MD](../Source/Server/ServerHandlers.cxx.review.MD).

### `ADD-NET-004` - Alias of `BASE-SERVER-008`
- **Location/function:** `Source/Shared/Networking/Messages/RequestChatRoomMessagesMessage.hxx:16-25,30-33`, constructors and `serialize`.
- **Issue:** Request-result and live-push DTOs reuse sender-local request IDs, allowing another client's push to consume pending local listener.
- **Proposed solution:** Use distinct notification/result semantics and recipient-correct IDs; validate context before popping pending requests.
- **Original review:** [RequestChatRoomMessagesMessage.hxx.review.MD](../Source/Shared/Networking/Messages/RequestChatRoomMessagesMessage.hxx.review.MD); canonical [ServerHandlers.cxx.review.MD](../Source/Server/ServerHandlers.cxx.review.MD).

### `ADD-UTIL-002` - Alias of `BASE-SERVER-007`
- **Location/function:** `Source/Shared_NoVer/filesystem_container/filesystem_container.cxx:144-204`, `create_shared`; canonical server handler at `ServerHandlers.cxx:464-476`.
- **Issue:** One filename maps to one shared object, rejecting valid distinct shared IDs for repeat uploads/downloads and producing false acknowledgments.
- **Proposed solution:** Store shared objects by opaque ID, retain filename as non-unique metadata/index, and commit before reporting success.
- **Original review:** [filesystem_container.cxx.review.MD](../Source/Shared_NoVer/filesystem_container/filesystem_container.cxx.review.MD); canonical [ServerHandlers.cxx.review.MD](../Source/Server/ServerHandlers.cxx.review.MD).

Partial overlaps remain separate canonical records when their remaining mechanism requires separate remediation, including `BASE-API-001`, `BASE-API-002`, `BASE-CORE-001`, `BASE-STORAGE-009`, and `BASE-API-015`. Exact overlap scope is documented in [baseline reconciliation](review-baseline/RECONCILIATION.MD) and [follow-up reconciliation](review-addendum/RECONCILIATION.MD).
