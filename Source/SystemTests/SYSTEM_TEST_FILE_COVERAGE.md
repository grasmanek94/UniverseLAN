# System Test File Coverage

This register maps SystemTest scenarios to production files whose observable
behavior they assert. It is intentionally not a line-coverage report: startup,
transport, and listener infrastructure used by every scenario are listed as
shared dependencies rather than claimed as independently tested behavior.

See [`DEVELOPER_GUIDE.md`](DEVELOPER_GUIDE.md) for SystemTest build, execution,
authoring, and maintenance instructions.

Update this file whenever a SystemTest is added, removed, or materially changes
which production behavior it verifies. `SYSTEM_TEST_COVERAGE.md` remains the
scenario/API overview.

## Direct Coverage

| Scenario | Production files and asserted behavior |
| --- | --- |
| `initialize-and-sign-in` | `Client/Impl/User.cxx`: local sign-in/authenticated state. `Server/Challenge.cxx`, `Server/ServerHandlers.cxx`: challenge/response acceptance and connection acceptance. |
| `lobby-create-list-join` | `Client/Impl/Matchmaking.cxx`: create/list/join callbacks and cache. `Server/ServerHandlers.cxx`: create/list/join handlers. `Shared/Lobby.cxx`, `Shared/LobbyManager.cxx`: lobby creation, membership, and listing. |
| `lobby-data-member-propagation` | `Client/Impl/Matchmaking.cxx`: lobby/member-data writes, callbacks, caches, and member state. `Server/ServerHandlers.cxx`: data authorization/propagation. `Shared/Lobby.cxx`: lobby and member data storage. |
| `lobby-member-leave-lifecycle` | `Client/Impl/Matchmaking.cxx`: leave callbacks, local cache removal, remote member-state cache. `Server/ServerHandlers.cxx`: leave handling and `LEFT` notification. `Server/Peer.cxx`, `Shared/Lobby.cxx`: peer/lobby association and member removal. |
| `lobby-owner-ownership-transfer` | `Client/Impl/Matchmaking.cxx`: owner-change and member-state callbacks, owner/member caches, and promoted-owner data-write callback. `Server/ServerHandlers.cxx`: ownership-transition leave handling, owner-change notification, and owner-only data authorization. `Shared/Lobby.cxx`: successor selection, owner state, and membership removal. |
| `lobby-owner-close-lifecycle` | `Client/Impl/Matchmaking.cxx`: `LOBBY_CLOSED` callback and removal of closed lobby data, list, joined, member, and owner caches. `Server/ServerHandlers.cxx`: FCM/STAR owner close, remote `LEFT`, and synthetic close notification. `Server/Peer.cxx`, `Shared/Lobby.cxx`, `Shared/LobbyManager.cxx`: remaining-peer removal and lobby destruction. |
| `raw-p2p-bidirectional` | `Client/Impl/Networking.cxx`: reliable send, per-channel receive queues, and sender attribution. `Client/Impl/Matchmaking.cxx`, `Server/ServerHandlers.cxx`, `Shared/Lobby.cxx`, `Shared/LobbyManager.cxx`: lobby-backed peer routing eligibility. |
| `raw-p2p-three-peer-routing` | Same files as bidirectional P2P, including server direct-recipient routing and observer nonreceipt. |
| `raw-p2p-offline-recipient` | `Client/Impl/Networking.cxx`: an undeployed typed user reports no direct P2P connection and unavailable ping after local sign-in. |
| `raw-p2p-channel-boundary-routing` | `Client/Impl/Networking.cxx`: all 256 `uint8_t` receive channels, including channel 255, retain routed packets. `Server/ServerHandlers.cxx`, `Client/Impl/Matchmaking.cxx`, `Shared/Lobby.cxx`, and `Shared/LobbyManager.cxx`: tagged-lobby sender-to-recipient routing. |
| `raw-p2p-leave-revokes-routing` | `Client/Impl/Matchmaking.cxx`: version-correct leave callback and local departed-lobby cache removal. `Client/Impl/Networking.cxx`: scheduled direct send and bounded channel drain. `Server/ServerHandlers.cxx`, `Server/Peer.cxx`, `Shared/Lobby.cxx`, and `Shared/LobbyManager.cxx`: active shared-lobby authorization revokes direct-recipient routing after `LEFT`. |
| `chat-room-message-delivery` | `Client/Impl/Chat.cxx`: room retrieval, send success, inbound notification, indexed read. `Server/ServerHandlers.cxx`: room creation/member delivery. `Shared/ChatRoom.cxx`, `Shared/ChatRoomManager.cxx`, `Shared/ChatMessage.cxx`: room/member/message state. |
| `chat-room-history-retrieval` | Same chat files as delivery. `Shared/ChatRoom.cxx`: newest-first pagination and reference handling. `Client/Impl/Chat.cxx`: retrieved-message cache deduplication and unread count. |
| `chat-room-reuse` | `Server/ServerHandlers.cxx`: one-to-one room retrieval before creation. `Shared/ChatRoomManager.cxx`: exact two-member lookup that excludes group rooms. `Client/Impl/Chat.cxx`: repeated room responses succeed without replacing cached state. |
| `chat-room-unknown-send-failure` | `Server/ServerHandlers.cxx`: unknown/nonmember sends return forbidden. `Shared/Networking/Messages/SendToChatRoomMessage.hxx`: send failure reason transport. `Client/Impl/Chat.cxx`: wire failure reason reaches the send listener. |
| `online-persona-game-invitation` | `Client/Impl/User.cxx`: online state propagation. `Client/Impl/Friends.cxx`: persona retrieval, peer callbacks, game invitation and auto-join. `Server/ServerHandlers.cxx`: user-data lookup/invitation routing. `Shared/GalaxyUserData.cxx`: identity/persona state. |
| `rich-presence-live-propagation` | `Client/Impl/Friends.cxx`: remote rich-presence cache update and `IRichPresenceListener` delivery. `Server/ServerHandlers.cxx`: rich-presence mutation routing to connected peers. `Shared/GalaxyUserData.cxx`: rich-presence storage. |
| `stats-achievement-user-data-propagation` | `Client/Impl/Stats.cxx`: local mutation/store callbacks and remote stats/achievement retrieval. `Client/Impl/User.cxx`: arbitrary user-data write and remote retrieval cache. `Server/ServerHandlers.cxx`: ordered stats, user-data, and rich-presence routing. `Shared/AchievementsAndStatsContainer.cxx`: stat, achievement, and user-data storage. |
| `stats-achievement-durable-persistence` | `Client/Impl/Stats.cxx`: self retrieve, integer/float mutation, achievement unlock, and store callback. `Shared/IniData.cxx`: enabled local stats and achievement serialization/reload. `Shared_NoVer/AchievementsAndStatsContainer.cxx`: integer/float union storage. This does not assert server persistence. |
| `user-data-live-propagation` | `Client/Impl/User.cxx`: remote arbitrary user-data cache mutation and `ISpecificUserDataListener` notification after that mutation. `Server/ServerHandlers.cxx`: remote update routing excludes the writer. `Shared/AchievementsAndStatsContainer.cxx`: arbitrary user-data storage. |
| `custom-networking-echo` | `Client/Impl/CustomNetworking.cxx`: WebSocket open, binary write, receive buffer, and read. The runner-owned echo service is the asserted remote endpoint. |
| `custom-networking-close` | `Client/Impl/CustomNetworking.cxx`: WebSocket open success and explicit close callbacks are delivered exactly once through `ListenerRegistrar`. The runner-owned echo service is the asserted endpoint. |
| `file-share-server-persisted-roundtrip` | `Client/Impl/Storage.cxx`: local IStorage write/read, file-share and download callbacks, shared-file cache close, metadata, indexed lookup, and ranged reads. `Server/ServerHandlers.cxx`: shared-file persistence and returned content. `Shared/SharedFileUtils.cxx`: isolated local/shared storage manipulation. |
| `file-share-server-policy-denied` | `Server/ServerHandlers.cxx`: server upload policy returns a zero shared-file ID before counter or shared-storage mutation. `Client/Impl/Storage.cxx`: zero ID reaches the version-correct file-share failure callback without a shared-file cache entry. `Shared/IniData.cxx`: server upload/download policy configuration. |
| `file-share-server-download-policy-denied` | `Server/ServerHandlers.cxx`: server download policy returns an empty shared-file response without reading storage. `Client/Impl/Storage.cxx`: that response reaches one version-correct download failure callback with its requested ID and no shared-file cache entry. `Shared/IniData.cxx`: server upload/download policy configuration. |
| `cloud-storage-local-roundtrip` | `Client/Impl/CloudStorage.cxx`: client-local cloud-container buffered put/list/metadata/get callbacks, including metadata-only zero file size, explicit timestamp/hash metadata, manual save type, generated savegame ID, and exact binary bytes from the full get. This does not exercise server-synchronized cloud storage. |
| `apps-config-and-dlc-ownership` | `Client/Impl/Apps.cxx`: configured DLC installation, language and language-code direct/copy APIs, and `IsDlcOwned` delivery to both supplied and global listeners. `Shared/IniData.cxx`: isolated language and DLC configuration loading, including disabled unknown-DLC persistence. `Client/Impl/ListenerRegistrar.cxx`: union of supplied and global ownership listeners. |
| `telemetry-local-event-result` | `Client/Impl/Telemetry.cxx`: Store-enabled client-local sink initialization, directory creation, event result index, and supplied listener success. `Shared/IniData.cxx`: isolated `[Telemetry] Store=1` configuration loading. No server telemetry behavior is exercised. |
| `utils-overlay-disabled-invariant` | `Client/Impl/Utils.cxx`: unsupported overlay remains `OVERLAY_STATE_DISABLED` and not visible while valid web-page and documented popup-group requests are inert. `Client/Impl/ListenerRegistrar.cxx`: registered global overlay initialization-state and visibility listeners receive no callback. |

## Shared Dependencies

- `Server/Server.cxx`, `Server/Peer.cxx`, `Shared/Networking/Networking.cxx`,
  and `Shared/IniData.cxx` support the server-backed scenarios but do not yet
  have isolated SystemTest contracts.
- `Client/Impl/ListenerRegistrar.cxx` delivers callbacks asserted by several
  scenarios. Its supplied/global listener union is directly asserted for
  `IApps::IsDlcOwned`; registration/unregistration lifecycle is not isolated.
- `Client/Impl/User.cxx` initializes every host. Sign-in, online-peer state,
  and live arbitrary user-data updates have direct assertions.

## Not Directly Covered

| Area | Key production files | Next system-level contracts |
| --- | --- | --- |
| Lobby lifecycle/control | `Client/Impl/Matchmaking.cxx`, `Server/ServerHandlers.cxx`, `Shared/Lobby.cxx` | Joinability, capacity, filters, messages, and failure callbacks. |
| P2P failures | `Client/Impl/Networking.cxx`, `Server/ServerHandlers.cxx` | Disconnect, unreliable send, and server-host paths. |
| Chat failures/lifecycle | `Client/Impl/Chat.cxx`, `Server/ServerHandlers.cxx`, `Shared/ChatRoom*.cxx` | Disconnect cleanup, ordering, read marking, member enumeration, and history failure semantics. |
| Storage/file sharing | `Client/Impl/Storage.cxx`, `Server/ServerHandlers.cxx`, `Shared/SharedFileUtils.cxx`, `Client/Impl/CloudStorage.cxx` | Cloud synchronization, timestamps, invalid-ID behavior, and failure semantics beyond the covered server upload/download policy paths. |
| Stats/presence | `Client/Impl/Stats.cxx`, `Client/Impl/User.cxx`, `Client/Impl/Friends.cxx`, `Shared/GalaxyUserData.cxx` | Stats/achievement reset, failure paths, and arbitrary user-data deletion. |
| Other Galaxy interfaces | `Errors.cxx`, `GalaxyThread.cxx`, `Logger.cxx` | API-specific observable contracts after their multi-process or persisted behavior is mapped. |

## Known Semantic Limitation

`Client/Impl/Friends.cxx` is covered for the existing online-peer/persona and
game-invitation model only. Real friendship state, invitation acceptance,
persistence, and truthful `IsFriend` behavior remain unsupported; see
`FOUND_DEFECTS.md`.
