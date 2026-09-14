# Found Defects

See [`DEVELOPER_GUIDE.md`](DEVELOPER_GUIDE.md) for when to update this defect
record with a SystemTest regression.

## Open

### IFriends does not model actual friendship relationships

Status: identified from the client and server friend paths; not yet covered by
a dedicated SystemTest.

The server tracks connected peers only. The client exposes those online peers
through friend-list APIs while `IsFriend` remains false, friend invitations are
not transported or persisted, and invitation responses always fail. See
[`Friends.cxx`](../Client/Impl/Friends.cxx) and
[`ServerHandlers.cxx`](../Server/ServerHandlers.cxx).

## Resolved

### ICloudStorage metadata requests reported the payload size

Status: fixed and validated by
`universelan-system-cloud-storage-local-roundtrip-x64-1.152.11`.

`CloudStorageImpl::GetFileMetadata` reported the stored file's 13-byte payload
size through `OnGetFileSuccess`, despite the ICloudStorage metadata-only
contract requiring zero. It now reports zero only for metadata requests; file
listing and full `GetFile` continue to report the actual payload size. The
1.152.11 regression retains a dedicated metadata listener after put/list and
before full get, requiring exactly one successful manual-save callback with a
matching container/name, zero size, and a nonempty savegame ID; the following
full get still requires the exact 13-byte binary payload.

### ICustomNetworking open omitted the supplied specific listener

Status: fixed and validated by
`universelan-system-custom-networking-close-x64-1.125.2`,
`universelan-system-custom-networking-close-x64-1.139.2`, and
`universelan-system-custom-networking-close-x64-1.152.11`.

`CustomNetworkingImpl::Channel::WebSocketOnOpen` notified only registered
global open listeners, ignoring the listener supplied to `OpenConnection` on
SDKs that expose operation-specific connection listeners. The callback now
uses the same registrar overload as failure and close, which unions the stored
specific listener with global listeners without duplicate delivery. The close
lifecycle regression uses the legacy global open/close listener API in 1.125.2
and only supplied open/close listeners in 1.139.2 and 1.152.11. It requires one
successful nonzero open ID, then one `CLOSE_REASON_UNDEFINED` callback for that
same ID with no terminal failure or duplicate callback.

### Store-enabled telemetry did not initialize its local sink directory

Status: fixed and validated by
`universelan-system-telemetry-local-event-result-x64-1.139.2` and
`universelan-system-telemetry-local-event-result-x64-1.152.11`.

With `[Telemetry] Store=1` and no precreated `UniverseLANData/Telemetry`
directory, `TelemetryImpl` attempted to open its output file first. The open
failed and `SendTelemetryEvent` reported its undefined failure callback. The
constructor now creates the local sink directory before opening the file. The
one-host regression uses a real loopback server only for the normal signed-in
host lifecycle; telemetry remains client-local and is not sent to that server.

### IApps IsDlcOwned omitted the supplied specific listener

Status: fixed and validated by
`universelan-system-apps-config-and-dlc-ownership-x64-1.125.2`,
`universelan-system-apps-config-and-dlc-ownership-x64-1.139.2`, and
`universelan-system-apps-config-and-dlc-ownership-x64-1.152.11`.

`AppsImpl::IsDlcOwned` delivered its terminal success or signed-out failure
only through the global listener path, ignoring the method's supplied specific
listener. The callback now uses the established registrar overload that unions
the supplied listener with registered global listeners. The 1.152.11 branch of
the one-host Apps SystemTest retains a supplied listener and registers a
separate global listener, requiring each to receive exactly one successful
`(210001, true)` callback and no failure. Its typed isolated configuration also
validates the associated DLC and language contracts; 1.125.2 and 1.139.2 cover
the base IApps contracts without APIs those SDKs do not offer.

### Remote arbitrary user-data updates did not notify specific listeners

Status: fixed and validated by
`universelan-system-user-data-live-propagation-x64-1.125.2`,
`universelan-system-user-data-live-propagation-x64-1.139.2`, and
`universelan-system-user-data-live-propagation-x64-1.152.11`.

`UserImpl::SetUserDataMessageReceived` updated the remote cache but never
notified `ISpecificUserDataListener`. A listenerless two-host probe first
confirmed that the receiver cache changed after the writer's local callback.
The receive path now emits the specific listener after the non-self cache
mutation, preserving local/self behavior and avoiding duplicate notifications.
The regression installs the receiver listener before the runner releases the
writer, filters the writer and fixed key/value, and requires both the remote
callback and exact remote cache value. SDK 1.125.2 uses the global local-write
listener; 1.139.2 and 1.152.11 use the per-operation listener.

### Server file-sharing policy was parsed but not enforced

Status: fixed and validated by
`universelan-system-file-share-server-policy-denied-x64-1.125.2`,
`universelan-system-file-share-server-policy-denied-x64-1.139.2`, and
`universelan-system-file-share-server-policy-denied-x64-1.152.11`.

`ServerIniData` loaded the server upload/download flags, but the shared-file
handlers always wrote or read shared storage. Upload denial now returns the
existing zero-ID file-share failure result before incrementing the shared ID or
persisting a file; download denial returns the existing empty file response
before reading storage. The single-host regression keeps client policy enabled,
writes a valid nonempty local file, and requires exactly the version-correct
file-share failure callback with no success ID or shared cache entry. It uses a
global listener in 1.125.2 and per-operation listeners in 1.139.2 and 1.152.11.

### RequestChatRoomWithUser created a new room for the same peer

Status: fixed and validated by
`universelan-system-chat-room-reuse-x64-1.125.2`,
`universelan-system-chat-room-reuse-x64-1.139.2`, and
`universelan-system-chat-room-reuse-x64-1.152.11`.

The server always created a new room for a valid online target. It now looks up
an existing room with exactly the requester and target as members before
creation. Repeated responses also leave an already cached client room intact
and still complete successfully. The two-host regression makes two sequential
requests and requires the same nonzero ID; it uses the legacy global listener
in 1.125.2 and operation listeners in later SDKs.

### Unknown chat-room send reported an undefined failure

Status: fixed and validated by
`universelan-system-chat-room-unknown-send-failure-x64-1.125.2`,
`universelan-system-chat-room-unknown-send-failure-x64-1.139.2`, and
`universelan-system-chat-room-unknown-send-failure-x64-1.152.11`.

The server represented an unknown or nonmember send with a null message only,
and the client consequently reported `FAILURE_REASON_UNDEFINED`. The send wire
message now carries a failure reason; denied sends carry `FORBIDDEN` and the
client forwards it to the listener. The one-host regression sends to room zero,
requires exactly one matching forbidden failure, and rejects success or delivery.
Authorized empty history responses remain separate from this send failure.

### Raw P2P routing remained authorized after a peer left its lobby

Status: fixed and validated by
`universelan-system-raw-p2p-leave-revokes-routing-x64-1.125.2`,
`universelan-system-raw-p2p-leave-revokes-routing-x64-1.139.2`, and
`universelan-system-raw-p2p-leave-revokes-routing-x64-1.152.11`.

The server previously forwarded a direct raw P2P packet to any online target.
It now requires the sender and direct target to share an active lobby before
delivery. Server-host and lobby-target broadcast routing are unchanged. The
two-host SystemTest uses a successful version-correct receiver leave, local
cache eviction, and the sender's remote `LEFT` notification to order a scheduled
post-leave packet, then requires an explicit bounded receiver channel drain to
remain empty while both hosts stay signed in.

### Raw P2P reported a direct connection for undeployed users

Status: fixed and validated by
`universelan-system-raw-p2p-offline-recipient-x64-1.125.2`,
`universelan-system-raw-p2p-offline-recipient-x64-1.139.2`, and
`universelan-system-raw-p2p-offline-recipient-x64-1.152.11`.

`NetworkingImpl::GetConnectionType` unconditionally returned
`CONNECTION_TYPE_DIRECT`, including for a valid typed user ID that has not been
deployed to the server. It now preserves the documented direct result for the
current user and returns `CONNECTION_TYPE_NONE` otherwise. The one-host SystemTest
uses a real server and also requires the existing unavailable-ping result of `-1`.
It deliberately does not treat `SendP2PPacket` scheduling as delivery failure.

### Raw P2P channel 255 indexed beyond the receive container

Status: fixed and validated by
`universelan-system-raw-p2p-channel-boundary-routing-x64-1.125.2`,
`universelan-system-raw-p2p-channel-boundary-routing-x64-1.139.2`, and
`universelan-system-raw-p2p-channel-boundary-routing-x64-1.152.11`.

The receive container was sized with `uint8_t`'s maximum value, yielding 255
entries for a valid 0 through 255 channel domain. Receive, availability, and pop
operations consequently indexed past the container for channel 255. It now has
256 entries. The two-host tagged-lobby SystemTest schedules and receives an exact
1200-byte binary payload, including zero bytes, on channel 255 with exact sender
attribution.

### Remote rich-presence updates did not notify global listeners

Status: fixed and validated by
`universelan-system-rich-presence-live-propagation-x64-1.125.2`,
`universelan-system-rich-presence-live-propagation-x64-1.139.2`, and
`universelan-system-rich-presence-live-propagation-x64-1.152.11`.

`FriendsImpl::RichPresenceChangeMessageProcessed` updated remote user caches
after successful rich-presence messages but did not emit
`IRichPresenceListener::OnRichPresenceUpdated`. The notification was instead
guarded by an unreachable non-self condition in the self acknowledgement path.
The listener is now emitted after the remote cache mutation. The two-host
SystemTest registers the receiver listener before releasing the writer, checks
the exact writer ID and fixed key/value, and validates the remote cache.

### FCM/STAR owner close retains stale lobby caches

Status: fixed and validated by
`universelan-system-lobby-owner-close-lifecycle-x64-1.125.2`,
`universelan-system-lobby-owner-close-lifecycle-x64-1.139.2`, and
`universelan-system-lobby-owner-close-lifecycle-x64-1.152.11`.

When an FCM or STAR owner leaves, the server sends remaining members a synthetic
`LOBBY_CLOSED` leave notification. The reason-aware client path cleaned caches
only for `USER_LEFT`, leaving closed lobbies, their data, membership, and owner
visible locally. `LeaveLobbyProcessed` now cleans caches for `LOBBY_CLOSED` as
well, while leaving unrelated failure reasons untouched. The two-host FCM
SystemTest requires the close notification, then verifies the tagged lobby is
absent from data, list, joined, member, and owner APIs. The BehaviorTest covers
the empirically absent redundant prior-owner member-state callback. Legacy
SDKs do not expose a close reason but exercise their compatible successful
callback path.

### Local lobby leave retains stale lobby-list data

Status: fixed and validated by
`universelan-system-lobby-member-leave-lifecycle-x64-1.125.2` and
`universelan-system-lobby-member-leave-lifecycle-x64-1.139.2`.

Successful local leave now removes only the departed lobby from both local
lobby-list caches and the joined set. The server also forwards the normal
remote `LEFT` member-state notification. The lifecycle SystemTest requires the
version-correct leave callback, verifies the departed lobby data is no longer
locally exposed, and confirms the owner receives `LEFT` with an owner-only
member cache.

### Chat history ignores default reference and requested limit

Status: fixed and validated by
`universelan-system-chat-room-history-retrieval-x64-1.139.2` and
`universelan-system-chat-room-history-retrieval-x64-1.152.11`.

The history request now serializes `limit`, and the server applies it while
selecting messages before a nonzero reference. A zero reference selects the
newest messages. The SystemTest persists two distinct messages through
send-success callbacks, uses live notifications only to establish their room
and IDs, then requires operation-specific retrieval success callbacks for the
newest message and its immediately older predecessor.

### Chat history can duplicate live messages in the local cache

Status: fixed and validated by
`universelan-system-chat-room-history-retrieval-x64-1.139.2` and
`universelan-system-chat-room-history-retrieval-x64-1.152.11`.

Retrieved messages are merged only when their message ID is absent from the
local room cache. The SystemTest retrieves both messages after observing their
live notifications and verifies the room's unread count remains two.

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
