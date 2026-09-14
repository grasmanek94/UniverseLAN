# UniverseLAN System Test Coverage

[`SYSTEM_TEST_PLAN.md`](SYSTEM_TEST_PLAN.md) describes the framework and
[`DEVELOPER_GUIDE.md`](DEVELOPER_GUIDE.md) covers build, execution, and
scenario maintenance. This file tracks behavior that is currently exercised
and the next coverage targets. Direct production-file coverage is maintained separately in
[`SYSTEM_TEST_FILE_COVERAGE.md`](SYSTEM_TEST_FILE_COVERAGE.md). Galaxy SDK
interface coverage is maintained in
[`SYSTEM_TEST_GALAXY_API_COVERAGE.md`](SYSTEM_TEST_GALAXY_API_COVERAGE.md).

## Covered

| Behavior | Scenario | Requirements |
| --- | --- | --- |
| SDK initialization and local sign-in | `initialize-and-sign-in` | All supported SystemTest SDKs |
| Public lobby create, list, and join | `lobby-create-list-join` | `LOBBY_LISTENERS` |
| Lobby/member-data propagation | `lobby-data-member-propagation` | `LOBBY_LISTENERS` |
| Explicit lobby leave and remote member removal | `lobby-member-leave-lifecycle` | `LOBBY_LISTENERS` |
| Lobby owner transfer, owner-change callback, and promoted-owner authorization | `lobby-owner-ownership-transfer` | `LOBBY_LISTENERS`, `HAS_LOBBYTOPOLOGYTYPE_ENUM` |
| FCM/STAR owner-close notification and closed-lobby cache removal | `lobby-owner-close-lifecycle` | `LOBBY_LISTENERS`, `HAS_LOBBYTOPOLOGYTYPE_ENUM` |
| Reliable two-peer raw packet exchange | `raw-p2p-bidirectional` | `LOBBY_LISTENERS`, `GALAXYID_HAS_IDTYPE` |
| Targeted three-peer raw packet routing | `raw-p2p-three-peer-routing` | `LOBBY_LISTENERS`, `GALAXYID_HAS_IDTYPE` |
| Offline typed P2P recipient connection state and ping | `raw-p2p-offline-recipient` | `HAS_CONNECTION_TYPE`, `GALAXYID_HAS_IDTYPE`; 1.125.2, 1.139.2, 1.152.11 |
| P2P channel 255 routing of an exact 1200-byte binary payload | `raw-p2p-channel-boundary-routing` | `LOBBY_LISTENERS`, `GALAXYID_HAS_IDTYPE`; 1.125.2, 1.139.2, 1.152.11 |
| Raw P2P leave revokes direct-recipient routing | `raw-p2p-leave-revokes-routing` | `LOBBY_LISTENERS`, `GALAXYID_HAS_IDTYPE`; 1.125.2, 1.139.2, 1.152.11 |
| Chat-room send success and remote delivery | `chat-room-message-delivery` | `HAS_ICHAT`, `HAS_ICHAT_ROOMLISTENERS`, `GALAXYID_HAS_IDTYPE` |
| Chat history pagination, limits, and cache deduplication | `chat-room-history-retrieval` | `HAS_ICHAT`, retrieval and room listeners, `GALAXYID_HAS_IDTYPE` |
| One-to-one chat-room retrieval reuses its existing room | `chat-room-reuse` | `HAS_ICHAT`, `GALAXYID_HAS_IDTYPE`; 1.125.2, 1.139.2, 1.152.11 |
| Unknown chat-room send fails as forbidden without success or delivery | `chat-room-unknown-send-failure` | `HAS_ICHAT`, `GALAXYID_HAS_IDTYPE`; 1.125.2, 1.139.2, 1.152.11 |
| Online-peer persona retrieval and game-invitation delivery | `online-persona-game-invitation` | Friends information, friend-add, invitation send/receive, game-join, and typed-ID listeners |
| Live remote rich-presence propagation | `rich-presence-live-propagation` | `IFRIENDS_SET_DEL_CLR_RICHPRESENCE`, `ADDED_RICH_PRESENCE_LISTENERS` |
| Cross-host stats, achievement, and arbitrary user-data retrieval | `stats-achievement-user-data-propagation` | `IFRIENDS_SET_DEL_CLR_RICHPRESENCE`, `ADDED_RICH_PRESENCE_LISTENERS`, `ISTATS_UPDATE_1_125` |
| Fresh-process local stats, achievement, and float-bit persistence/reload | `stats-achievement-durable-persistence` | `ISTATS_UPDATE_1_125`; 1.125.2, 1.139.2, 1.152.11. This validates the runner-isolated UniverseLAN local profile, not server durability. |
| Live remote arbitrary user-data propagation and specific listener delivery | `user-data-live-propagation` | `HAS_SPECIFICUSERDATALISTENER`, `GALAXYID_HAS_IDTYPE`; 1.125.2, 1.139.2, 1.152.11 |
| Custom-networking binary WebSocket echo | `custom-networking-echo` | `HAS_ICUSTOMNETWORKING`, `HAS_ICONNECTIONLISTENERS` |
| Custom-networking WebSocket open/close lifecycle | `custom-networking-close` | `HAS_ICUSTOMNETWORKING`; 1.125.2, 1.139.2, 1.152.11 x64. Uses global listeners in 1.125.2 and operation-specific listeners in later SDKs. |
| Server-persisted shared-file upload/download roundtrip | `file-share-server-persisted-roundtrip` | `HAS_ISTORAGE` |
| Server-disabled shared-file upload fails without a remote ID or shared cache | `file-share-server-policy-denied` | `HAS_ISTORAGE`; 1.125.2, 1.139.2, 1.152.11 |
| Server-disabled shared-file download fails without repopulating its closed cache | `file-share-server-download-policy-denied` | `HAS_ISTORAGE`; 1.125.2, 1.139.2, 1.152.11. Uses global listeners in 1.125.2 and operation-specific listeners in later SDKs. |
| Client-local cloud-container put/list/metadata/get roundtrip | `cloud-storage-local-roundtrip` | `HAS_ICLOUDSTORAGE`; 1.152.11 x64 |
| Configured DLC installation, language copy semantics, and DLC ownership listeners | `apps-config-and-dlc-ownership` | `HAS_IAPPS`, `HAS_GETCURRENTGAMELANGUAGE`; 1.125.2, 1.139.2, 1.152.11 x64. Language-code and supplied ownership listener assertions use their respective SDK feature gates. |
| Local telemetry-sink event result | `telemetry-local-event-result` | `HAS_ITELEMETRY`; 1.139.2 and 1.152.11 x64. This does not assert server telemetry. |
| Unsupported overlay state and visibility remain inert | `utils-overlay-disabled-invariant` | `HAS_IUTILS`, `HAS_IUTILS_SHOWOVERLAYWITHWEBPAGE`, `OVERLAYSTATE_ENUM`, `HAS_DISABLEOVERLAYPOPUPS`; 1.125.2, 1.139.2, 1.152.11 x64. |

The runner also supports the unregistered `gog-credential-sign-in.example.json`
provider scenario. It requires matching official runtime artifacts and a real,
authenticated GOG environment.

## Verified Matrix

| SDK / Architecture | Result |
| --- | --- |
| `1.114.9` x64 | Initialization/sign-in passed |
| `1.125.2` x64 | Full registered SystemTests suite, including custom-networking close lifecycle, the unsupported-overlay invariant, configured `IApps` DLC/language contracts, chat-room reuse and unknown-send forbidden failure, raw P2P leave routing revocation, file-share roundtrip and upload/download policy denial, rich-presence propagation, stats/achievement/user-data propagation, fresh-process local stats/achievement persistence, and live user-data listener propagation, passed |
| `1.139.2` x64 | Full registered SystemTests suite, including custom-networking close lifecycle, the unsupported-overlay invariant, configured `IApps` DLC/language contracts, local telemetry-sink event results, chat-room reuse and unknown-send forbidden failure, raw P2P leave routing revocation, file-share roundtrip and upload/download policy denial, rich-presence propagation, stats/achievement/user-data propagation, fresh-process local stats/achievement persistence, and live user-data listener propagation, passed |
| `1.139.2` x86 | Full suite available at that point passed |
| `1.152.11` x64 | Full registered SystemTests suite, including custom-networking close lifecycle, the unsupported-overlay invariant, configured `IApps` DLC/language/language-code contracts and supplied ownership listener delivery, local telemetry-sink event results, chat-room reuse and unknown-send forbidden failure, raw P2P leave routing revocation, file-share roundtrip and upload/download policy denial, client-local cloud-container roundtrip, rich-presence propagation, stats/achievement/user-data propagation, fresh-process local stats/achievement persistence, and live user-data listener propagation, passed |

Run the selected-version suite with:

```powershell
ctest --test-dir <build-directory> -C Debug --output-on-failure -L system
```

## Next Coverage

- Chat-room historical retrieval error paths and multi-message ordering beyond
  the current two-message pagination contract.
- Raw P2P disconnect handling and unreliable-send behavior.
- Custom-networking connection failure and multiple concurrent connection paths.
- Cloud storage synchronization and notifications, after their visible
  cross-process contracts are mapped. The current cloud roundtrip covers only
  UniverseLAN's client-local cloud container, not server-synchronized storage.

## Implementation Maintenance

- The native host and runner implementations are split into `Host`, `Runner`,
  and narrow `Common` source/header units. The CTest and JSON-manifest contract
  remains unchanged.

## Not Yet Supported

- Real Galaxy friend relationships. The current server tracks online peers, not
  friendship state. Friend invitations, acceptance, persistence, and truthful
  `IsFriend` behavior need production support before they can be tested as
  Galaxy friend workflows.
- Automatic official-GOG CTest registration. These tests depend on local GOG
  runtime artifacts, credentials, authentication, and network availability, so
  they remain opt-in scenarios.
