# Galaxy SDK Interface Coverage

This register records which Galaxy SDK interfaces have a direct UniverseLAN
SystemTest contract. It is not a full API conformance matrix: each row names
the behavior asserted against version-specific Galaxy headers and client
libraries. Update it with every SystemTest that adds or removes interface
coverage.

See [`DEVELOPER_GUIDE.md`](DEVELOPER_GUIDE.md) for SystemTest build, execution,
authoring, and maintenance instructions.

## Directly Covered

| Interface | SystemTest contracts |
| --- | --- |
| Galaxy initialization / `IUser` | Initialization, local sign-in, authenticated state, online-peer state, arbitrary user-data retrieval, and remote user-data change callbacks. |
| `IMatchmaking` | Public lobby create/list/join, lobby/member data, explicit leave, owner transfer, owner-close, cache invalidation, owner authorization, and member/owner callbacks. |
| `INetworking` | Reliable direct P2P send/read, sender attribution, three-peer routing, offline connection/ping state, channel `255`, a 1200-byte binary payload, and routing revocation after leave. |
| `IChat` | One-to-one room retrieval/reuse, message send/delivery, forbidden denied send, history limit/reference pagination, and message-cache deduplication. |
| `IFriends` | Online-peer persona retrieval, game invitation receive/auto-join, rich-presence mutation and remote update callbacks. |
| `IStats` | Stat and achievement mutation/store plus remote retrieval, using rich presence as a server-ordering barrier; and fresh-process local-profile reload of integer, finite float bit representation, and achievement state/time. The latter is not server durability. |
| `IStorage` | Local file read/write, server-persisted shared-file upload/download, binary/ranged reads, cache close, and server upload/download-policy failures. The download-denial contract requires one matching-ID undefined-reason failure, no success, no cache repopulation, and no late terminal callback. |
| `ICloudStorage` | Client-local cloud-container buffered put/list/metadata/get with fixed binary data, metadata-only zero size, explicit timestamp/hash, manual save type, and savegame ID. This is not server-synchronized cloud storage. |
| `ICustomNetworking` | Loopback WebSocket open, binary send, receive, read, and explicit close lifecycle with one undefined-reason close callback. |
| `IApps` | Configured installed/disabled/absent DLC checks; direct and exact/truncated null-terminated language copies; language-code APIs when offered; and 1.152.11 `IsDlcOwned` success delivery to both supplied and global listeners. |
| `ITelemetry` | Local telemetry-sink event submission with a supplied operation listener, exact event type, nonzero matching event index, and one success/no failure. This is not server telemetry. |
| `IUtils` | Unsupported-overlay invariant: after local sign-in, `IUtils` is nonnull, reports `OVERLAY_STATE_DISABLED` and not-visible before and after a valid web-page request and all documented popup-group disable requests, and emits no global initialization-state or visibility callbacks. |

## Not Directly Covered

| Interface / area | Missing contracts |
| --- | --- |
| `IUser` | User-data deletion, local/remote failure paths, and restart-persistence behavior. |
| `IMatchmaking` | Joinability/capacity controls, advanced filters, lobby messages, and broader operation failures. |
| `INetworking` | Unreliable sends, disconnect/NAT behavior, and server-host networking paths. |
| `IChat` | History-denial result semantics, room member enumeration, read marking, member-disconnect cleanup, and longer ordering sequences. |
| `IFriends` | Real friendship relationships, find/add/delete/accept workflows, friendship persistence, and truthful `IsFriend`. |
| `IStats` | Reset/deletion/failure paths and server durability. Local durable restart persistence is covered for integer/finite-float stats and achievement state. |
| `IStorage` | Timestamps, invalid-ID behavior, and broader failure semantics. |
| `ICloudStorage` | Server synchronization, conflict handling, notifications, quota, oversized-buffer behavior, and omitted-hash behavior. |
| `ITelemetry` | Failure semantics, parameter serialization, sampling, visit ID, and server telemetry. |
| `ILogger`, error/thread APIs | No isolated observable SystemTest contracts. |
| `ICustomNetworking` | Connection failure and concurrent connections. |
| `IListenerRegistrar` | Callback outcomes are exercised, but registration/unregistration itself is not isolated. |

## Runtime Scope

The complete registered UniverseLAN suite is validated on `1.125.2`, `1.139.2`,
and `1.152.11` x64. Older `1.114.9` coverage is initialization/sign-in only.
Official GOG runtime validation remains an opt-in credentialed scenario, not an
automated CTest contract.
