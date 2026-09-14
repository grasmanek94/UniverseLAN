# UniverseLAN System Test Plan

Current verified and planned API coverage is tracked in
[`SYSTEM_TEST_COVERAGE.md`](SYSTEM_TEST_COVERAGE.md). For build, execution,
scenario-authoring, and diagnostic instructions, see
[`DEVELOPER_GUIDE.md`](DEVELOPER_GUIDE.md).

## Scope

System tests validate externally visible UniverseLAN Galaxy API behavior through
real UniverseLAN client DLLs and, when declared by a scenario, real
UniverseLAN server executables. The default runtime provider is `universelan`.
A scenario can explicitly select the `gog` provider for future behavior
comparison work, but current SystemTests use `universelan` only.

Each scenario is automatic: it has bounded deadlines, machine-readable
protocol output, and a single CTest PASS or FAIL result.

## Topology

CTest launches one version-specific orchestrator. The orchestrator reads a
scenario manifest and launches the declared processes:

```text
ctest
  -> universelan-system-test-runner-<version>
       -> UniverseLANServer<arch>              optional, one per scenario
       -> universelan-system-test-host-<version> creator
       -> universelan-system-test-host-<version> joiner
       -> universelan-system-test-host-<version> peer-c
```

A scenario can declare zero or one UDP server, zero or one runner-managed
loopback WebSocket server, and any number of DLL hosts. This
supports isolated API checks, two-client lobby/message exchange, and
three-or-more-client multiplayer packet scenarios without creating a bespoke
executable for each topology.

## Scenario Manifest

Scenarios use JSON because process roles, dependencies, expected events, and
per-process configuration are explicit and readable. The runner owns the
schema and rejects unknown required fields, malformed dependencies, duplicate
roles, and unsafe paths before starting any child process.

Example: `Scenarios/lobby-create-list-join.json`:

```json
{
  "name": "lobby-create-list-join",
  "runtimeProvider": "universelan",
  "timeoutSeconds": 30,
  "server": {
    "enabled": true,
    "readyEvent": "server-ready",
    "configuration": {
      "maxConnections": 8
    }
  },
  "hosts": [
    {
      "role": "creator",
      "scenario": "create-lobby",
      "identity": {
        "userId": 1001,
        "personaName": "SystemCreator"
      },
      "waitFor": ["server-ready"],
      "signals": ["lobby-ready"],
      "finishAfter": ["lobby-joined"],
      "timeoutSeconds": 10
    },
    {
      "role": "joiner",
      "scenario": "list-and-join-lobby",
      "identity": {
        "userId": 1002,
        "personaName": "SystemJoiner"
      },
      "waitFor": ["server-ready", "lobby-ready"],
      "signals": ["lobby-joined"],
      "timeoutSeconds": 10
    }
  ]
}
```

The manifest describes process orchestration only. `actionAfter` is an optional
mid-scenario gate: the runner writes the host action file only after every
named event is observed. `peerUserIds`, when present, is a validated list of
other manifest identities passed as typed Galaxy user IDs. A `websocket` block
declares a runner-owned loopback WebSocket service and its ready event. Worker
scenario names map
to compiled, version-aware Galaxy API behaviors; manifests never embed C++ or
untrusted commands.

Each `identity` accepts a required `userId`, an optional `personaName`, and an
optional `credentialProfile`. A credential profile is the token `user1` or
`user2`; manifests never contain login or password fields. The non-registered
`Scenarios/gog-credential-sign-in.example.json` shows the required shape for a
future official GOG run and deliberately has no server declaration or secrets.

A host can declare an `apps` block for the constrained `IApps` test settings:
language, language code, the two DLC policy booleans, and a nonempty map of
numeric DLC product IDs to booleans. The runner validates every field and
renders only those values into that isolated host's `Config.ini` and `DLC.ini`;
manifests cannot inject arbitrary INI sections or keys.

A host can declare a `telemetry` block containing only the `store` boolean. The
runner validates it and renders the value only as `[Telemetry] Store=<0|1>` in
that host's isolated `Config.ini`; it does not create a telemetry directory or
expose arbitrary INI configuration.

A host can declare `persistenceGroup` with the matching explicit
`saveAchievementsAndStats: true` setting. The group is an alphanumeric,
hyphen, or underscore token, never a path.
The runner creates its profile below the temporary run root, enables only
`SaveAchievementsAndStats=1`, and shares only that `GameDataPath` among group
members. Group members use one identity and start in manifest order; each later
member waits for every earlier member to PASS and exit with code zero. All other
host roots, working directories, and GameData paths remain private with
`SaveAchievementsAndStats=0`.

## Process Protocol

The orchestrator captures server and host stdout. Server output is retained as
native diagnostics and the `Listening...` line supplies its ready event. Host
lines prefixed with `SYSTEM_TEST ` use this line-delimited protocol:

```text
SYSTEM_TEST EVENT name=server-ready
SYSTEM_TEST EVENT name=lobby-ready lobby=1234
SYSTEM_TEST PASS role=joiner
SYSTEM_TEST FAIL role=creator reason=CreateLobbyTimeout
```

The runner forwards declared events to dependent hosts through a per-run
control directory. A host receives a release only after all of its `waitFor`
events have been observed. A host declaring `finishAfter` receives its
completion gate only after those declared events have been observed, and waits
for it with its bounded host timeout. Untagged native stdout is retained as diagnostics;
a malformed tagged protocol line, unexpected exit, duplicate PASS, FAIL line,
or deadline expiry fails the scenario and records the child output in the run
directory.

For each scenario run, the runner generates a safe unique lobby token. Raw P2P
hosts create a public lobby, persist the token in a lobby data field, then
discover it with an exact string filter and verify the returned data before
joining. They never select an arbitrary lobby-list entry.

## Isolation And UniverseLAN Selection

For every run, the orchestrator creates a unique temporary root with separate
working directories for the server and every host. It writes deterministic
UniverseLAN configuration into each directory:

- Loopback-only networking with a runner-selected UDP port and a fixed test key.
- A separately selected TCP port for a declared runner-owned `ws://127.0.0.1`
  echo server. The runner calls `ix::initNetSystem()`, binds and listens before
  publishing readiness, starts the service, then stops it and calls
  `ix::uninitNetSystem()` on both success and failure paths.
- Unique fixed client identities per role, except sequential members of one
  validated persistence group; no PID, MAC, debug-ID, or user-data derived
  identities.
- Tracing, console interaction, and real-service behavior disabled.
- Server and client data directories below the temporary root only.

For `universelan` scenarios, the runner receives the selected version's built
`UniverseLANServer`, native Galaxy host, and client DLL target paths from
CMake. It copies the host executable and selected runtime DLL into each host
directory, so Windows native import resolution chooses UniverseLAN or the
requested GOG provider without changing the host command line.

## Runtime Providers

`runtimeProvider` determines which Galaxy runtime the orchestrator places next
to a version-specific DLL host:

- `universelan` is the default. The host uses the selected build's
  `universelan-client-<version>` target and, when required, the matching built
  `universelan-server-<version>` target. A declared server is launched only for
  this provider.
- `gog` is opt-in. Before launching any process, the orchestrator verifies that
  `Source/DLLs/<version>/gog/` contains the official architecture-specific
  Galaxy runtime and import library: `Galaxy<arch>.dll` and `Galaxy<arch>.lib`
  on Windows, or the corresponding `libGalaxy<arch>.so` on Linux. Some SDKs
  use the `REDGalaxy` prefix, so the resolver follows the version feature flag
  used by the build. `gog` scenarios cannot declare a UniverseLAN server;
  connectivity is provided by the real GOG environment when the scenario
  requires it.

If a `gog` scenario lacks any required artifact, it is reported as skipped with
an explicit diagnostic, never as a UniverseLAN failure. A GOG provider scenario
also declares that network access and an installed, authenticated GOG Galaxy
environment are prerequisites; the runner does not attempt to create or fake
that environment.

GOG hosts use their selected credential profile with the SDK's
version-compatible credentials sign-in API. If a GOG host does not select a
profile, it reports `CredentialProfileRequired`. If the local credentials file
or selected profile is unavailable, it reports `CredentialProfileUnavailable`.
Neither protocol reason includes credential values.

The provider resolver, manifest schema, process protocol, and isolation code
are intentionally reusable by future `BehaviourTests`. Behaviour tests can run
the same scenario once with `universelan` and once with `gog`, compare their
machine-readable outcome/event traces, and keep provider-specific prerequisites
outside the core SystemTests suite.

## Configuration And Identity Management

The orchestrator builds each process configuration from a scenario-wide
deterministic baseline, then applies validated server or role-specific
overrides. Scenarios do not copy repository configuration directories or edit
INI files themselves.

- The baseline supplies the selected loopback port, authentication key, disabled
  tracing, and all data paths below the run root.
- `server.configuration` may override supported server settings such as maximum
  connections, tick rate, and the server-only `allowFileSharingUpload` and
  `allowFileSharingDownload` booleans. Client storage policy remains enabled
  unless a future host override explicitly changes it.
- Each host has a required unique `identity.userId` and optional stable persona
  name. A duplicate ID is valid only for sequential members of one shared
  `persistenceGroup`; that group must contain no other identity.
- `identity.credentialProfile` is optionally `user1` or `user2`; it selects a
  local build-time profile and cannot carry raw credentials. The local
  UniverseLAN sign-in path ignores it, uses `SignInGalaxy`, and needs no real
  credentials.
- `Source/TestCommon/credentials.cmake` is optional for SystemTests. When it
  provides both named profiles and the Galaxy application ID and secret, CMake
  passes opaque host-only definitions; when unavailable, normal UniverseLAN
  builds still configure and GOG hosts report `CredentialProfileUnavailable`
  without logging credential values.
- `Source/TestCommon/credentials.cmake.example` is the checked-in template for
  the ignored local credentials file.
- Secrets are never written to protocol events, CTest command lines, generated
  test configuration, or retained logs.
- Worker command lines receive only role, scenario, control directory, timeout,
  version, architecture, runtime provider, and the optional profile token. They
  read generated configuration from their private working directory, preventing
  cross-host configuration leakage.

This supports a server plus any number of hosts with distinct identities and,
when needed, distinct credentials, without introducing hand-maintained
configuration files per test.

## CMake Contract

- `BUILD_UNIVERSELAN_SYSTEM_TESTS=1` adds `Source/SystemTests` and enables CTest.
- `BUILD_ALL_TESTS=1` also enables system tests.
- Unit tests and GoogleTest remain independent of system tests.
- For each selected SDK version, CMake creates a version-specific native Galaxy
  host linked to `universelan-client-...` and a runner, passing the selected
  server, host, and client DLL target paths to `add_test`.
- SystemTests conditionally include the ignored credentials file only when it
  exists. No official GOG scenario is registered as a CTest because it requires
  local credentials, official SDK artifacts, network access, and GOG runtime
  prerequisites.
- Each system test has `TIMEOUT`, `RUN_SERIAL`, and a shared network
  `RESOURCE_LOCK` to prevent port and output collisions.
- Cross-platform CMake/CTest runs the native orchestrator. No batch or shell
  script is required for test execution; optional scripts only configure common
  unit, system, or all-test build modes.

## Implemented Scenarios

`initialize-and-sign-in` is registered as a CTest for each selected SDK
version. It starts the real UniverseLAN server, waits until its stdout reports
`Listening...`, then releases an isolated native Galaxy host. The host imports
the selected UniverseLAN client DLL directly, initializes the version-specific
Galaxy API, calls the local Galaxy-compatible sign-in API, pumps `ProcessData`
to a bounded deadline, and requires `User()->SignedIn()` before it emits PASS.

Every run receives a separate root `UniverseLAN.ini` with repository-standard
storage paths, a fixed non-secret authentication key, disabled tracing, and a
network timeout. Client and server `Config.ini` files use their respective
`UniverseLANData` and `UniverseLANServerData` conventions. The runner probes
candidate loopback UDP ports before selecting one, stages a host executable and
the selected runtime DLL together in each host directory, and preserves failed
run directories for diagnostics while removing successful runs.

`lobby-create-list-join` is registered only for SDK versions with the
`LOBBY_LISTENERS` feature definition. The creator uses the operation-specific
create listener to confirm a public, joinable lobby before emitting
`lobby-ready`, then keeps pumping data until the `lobby-joined` completion
gate. The joiner uses operation-specific list and join listeners to require a
non-empty successful list and successful join before emitting `lobby-joined`
and passing. Hosts return `UnsupportedScenario` when a lobby listener API is
not compiled into their SDK target.

`lobby-data-member-propagation` has the same `LOBBY_LISTENERS` requirement.
The owner creates a uniquely tagged lobby with an operation-specific data
update listener. Its global member-state listener confirms the joiner entered
and that the two-member list contains both declared users before releasing the
joiner action gate. The joiner writes member data with an operation-specific
member-data update listener. The owner requires the remote global lobby-data
callback for that member and the exact member-data value before writing lobby
data with an operation-specific listener. The joiner then requires the remote
global lobby-data callback and exact owner value. Callback filtering ignores
the setup tag and any other data updates, and runner events provide every
cross-host ordering edge.

`lobby-member-leave-lifecycle` has the same `LOBBY_LISTENERS` requirement and
therefore runs from 1.125.2 onward. The owner creates a tagged public lobby and
keeps a global member-state listener alive while it verifies the joiner's
entered notification and the exact two-member cache. The runner then releases
the joiner to leave with an operation-specific listener. The joiner requires
the version-correct successful leave callback and verifies its tagged lobby data
is no longer exposed locally; the owner requires the remote `LEFT` callback and
an owner-only member cache. SDKs before 1.133.0 use the legacy `ioFailure`
leave callback, while later SDKs require `LOBBY_LEAVE_REASON_USER_LEFT`.

`lobby-owner-ownership-transfer` is registered from 1.125.2 for SDK versions
with `LOBBY_LISTENERS` and `HAS_LOBBYTOPOLOGYTYPE_ENUM`. The owner creates a
public uniquely tagged `LOBBY_TOPOLOGY_TYPE_FCM_OWNERSHIP_TRANSITION` lobby,
never the closing FCM topology. After list/join, the joiner installs global
owner-change and member-state listeners, verifies the initial owner and exact
two-member cache, and emits its readiness event. Only then does the runner
release the owner's explicit leave. The owner requires the version-correct
operation callback: legacy SDKs require `ioFailure == false`; SDKs from 1.133.0
require `LOBBY_LEAVE_REASON_USER_LEFT`. The joiner requires the departed-owner
`LEFT` callback, an owner-change callback naming itself, and a final cache with
itself as the only member and owner. It then writes a new lobby value with an
operation-specific success callback, proving that promotion authorized owner
operations. Runner action and completion gates, plus bounded host pumps,
enforce every cross-host ordering edge.

`lobby-owner-close-lifecycle` is registered under the same lobby and topology
feature gates, but remains distinct from ownership transfer. The owner creates
a uniquely tagged closing `LOBBY_TOPOLOGY_TYPE_FCM` lobby. Once the joiner has
joined, it installs a global leave listener, verifies the initial state, and
releases the owner. The owner uses the version-correct successful operation
callback to leave. The joiner requires the global close notification; SDKs from 1.133.0 require
`LOBBY_LEAVE_REASON_LOBBY_CLOSED`, while earlier SDKs expose only the legacy
successful `ioFailure == false` callback. After notification delivery it
requires the tagged data and list entry to be gone, `SendLobbyMessage` to reject
the former joined lobby, no lobby members, an invalid member index, and an
invalid owner.

`raw-p2p-bidirectional` is registered only with `LOBBY_LISTENERS` and
`GALAXYID_HAS_IDTYPE`. Two hosts create and discover the uniquely tagged public
lobby, wait at a runner action gate until both have joined, then exchange
reliable raw `INetworking` packets on fixed nonzero channel 37. Each receive
path pumps `ProcessData`, polls, uses `ReadP2PPacket` sender attribution, and
validates a canonical binary payload.

`raw-p2p-three-peer-routing` has the same feature requirements. Sender, target,
and observer join the same tagged lobby and wait until all three joins complete.
The sender directs one reliable raw P2P packet only to the target, then emits
`sender-sent`. The target and observer start their checks only after that event.
The target validates the payload and sends a canonical ACK. The observer drains
channel 37 and verifies nonreceipt during a bounded, explicit 750 ms quiet
interval. The sender does not pass until both the target ACK event and observer
quiet event have completed.

`raw-p2p-offline-recipient` is registered only for 1.125.2, 1.139.2, and
1.152.11 where typed IDs and `GetConnectionType` are available. One signed-in
host and a real loopback server construct an undeployed typed user ID and require
`CONNECTION_TYPE_NONE` plus `GetPingWith(...) == -1`. It intentionally does not
assert the return from `SendP2PPacket`, whose contract is only scheduling.

`raw-p2p-channel-boundary-routing` is registered for the same three SDKs. Two
hosts create and discover a uniquely tagged lobby, then the creator schedules a
reliable exact 1200-byte binary packet, including zero bytes, to the joiner on
channel 255. The joiner requires positive availability on that channel and
validates the exact typed sender and payload before it signals receipt. Runner
action and completion gates keep the send and receive ordering deterministic.

`raw-p2p-leave-revokes-routing` is registered for 1.125.2, 1.139.2, and
1.152.11. Two signed-in hosts create and join a tagged public lobby. The receiver
uses the version-correct successful leave callback and requires the tagged lobby
data cache to be gone. The sender requires the remote `LEFT` callback and its
owner-only member cache before the runner releases its send action. It schedules
a reliable direct packet on otherwise unused channel 38 without asserting the
`SendP2PPacket` scheduling result. The receiver begins a bounded 750 ms channel
drain only after the runner observes that scheduling event, and requires no
payload while both hosts remain signed in. This asserts that an active shared
lobby authorizes direct raw P2P routing and that leaving revokes it.

`chat-room-message-delivery` is registered only with `HAS_ICHAT`, operation-
specific `HAS_ICHAT_ROOMLISTENERS`, and `GALAXYID_HAS_IDTYPE` (including
1.139.2 and 1.152.11). The receiver creates the persistent global chat-message
listener before it emits ready. The sender is released by that runner gate,
requests a one-to-one room with the receiver using an operation listener, and
requires its callback's typed peer ID and nonzero room ID before sending the
fixed test message with a send operation listener. The sender requires the
send-success callback, not its failure callback, then remains alive until the
receiver emits `receiver-received`. The receiver reads index zero exclusively
inside its message callback and validates the exact byte length and contents,
the message type, nonzero message ID, and typed sender ID. Every host and
scenario deadline is bounded.

`chat-room-history-retrieval` is registered only with `HAS_ICHAT`,
`HAS_ICHAT_ROOMLISTENERS`, `HAS_ICHATROOMMESSAGERETRIEVELISTENER`,
`HAS_ICHAT_MESSAGETYPE`, and `GALAXYID_HAS_IDTYPE`. The sender creates the
one-to-one room and persists distinct older and newer messages, requiring a
send-success callback for each before publishing its event. The receiver first
uses live message notifications to establish the room and both message IDs,
then waits for the runner action gate. It separately requires successful
operation-specific history callbacks for `limit=1, reference=0` (the newest
message) and `limit=1, reference=<newest ID>` (the immediately older message).
Each callback validates the exact ID, payload, sender, type, and length; the
receiver also requires its unread room cache count to remain two, proving the
retrieved IDs were not duplicated after their live delivery.

`chat-room-reuse` is registered for 1.125.2, 1.139.2, and 1.152.11. Two
signed-in hosts and a real loopback server establish an online peer, then the
requester makes two sequential `RequestChatRoomWithUser` calls for that same
peer. It requires two successful nonzero callbacks with one identical room ID.
The 1.125.2 host uses the global listener API; 1.139.2 and 1.152.11 use the
operation listener API. The server lookup accepts only rooms with exactly those
two members, so group rooms cannot satisfy this one-to-one request.

`chat-room-unknown-send-failure` is registered for the same SDK versions. One
signed-in host and a real loopback server send a fixed message to room ID zero.
It requires exactly one terminal send failure with the same room and returned
message index and `FAILURE_REASON_FORBIDDEN`, then pumps through a bounded quiet
period to require no send-success callback or message delivery. The 1.125.2
host uses the global listener API; later SDKs use the operation listener API.
This send-result contract does not reinterpret empty authorized history results
as forbidden history access.

`online-persona-game-invitation` is registered only with typed Galaxy IDs,
persona and user-information retrieval, friend-add, invitation send/receive,
and game-join listener features. The receiver starts first with runner-written
`AutoAcceptGameInvitations=1`, installs online-peer and invitation listeners,
and signals readiness. The sender then requests the connected receiver's user
information with an operation listener, requires the matching persona callback,
and validates the exact receiver persona and online state before sending a
fixed connection string with an operation-specific send-success listener. The
receiver waits on the runner action gate after it observes the sender's online
peer callback, then requires the sender ID and exact string in both invitation
and auto-accepted game-join callbacks. The sender remains alive through a
runner completion gate until both receiver callbacks are observed. This covers
the existing online-peer model only; it does not call `IsFriend` or use
friend-invitation APIs.

`rich-presence-live-propagation` is registered only with
`IFRIENDS_SET_DEL_CLR_RICHPRESENCE` and `ADDED_RICH_PRESENCE_LISTENERS`, which
includes 1.125.2, 1.139.2, and 1.152.11. The receiver installs its global rich
presence listener before it signals readiness. The writer starts only after
that runner gate, sets a fixed unique key/value, and requires the SDK-correct
success callback: the legacy global change listener in 1.125.2, or the
per-operation change listener from 1.126.0 onward. The receiver accepts one
remote callback only for the declared writer, then validates the cached key,
value, and nonzero presence count. The writer remains alive through the
receiver validation gate.

The scenario uses a real loopback UniverseLAN server, distinct fixed host
identities, and no external credentials.

`stats-achievement-user-data-propagation` is registered with the same rich-
presence feature gates plus `ISTATS_UPDATE_1_125`, covering 1.125.2, 1.139.2,
and 1.152.11. The writer first retrieves its own stats with an operation
listener, writes a scenario-specific integer stat, configured achievement, and
arbitrary user-data value, and requires the version-compatible store-success
listener. Store success is only local acknowledgement, so it then sends rich
presence. The reader installs its global rich-presence listener before releasing
the writer and starts remote reads only after the exact writer barrier update.
It requests user data first and stats second. In SDKs with a per-operation user-
data listener it retains both retrieval listeners; in 1.125.2 the ordered stats
response bounds the prior listenerless user-data response. The reader requires
the exact stat and user-data values plus an unlocked achievement with a nonzero
unlock time, while the writer remains alive through the reader validation gate.

`stats-achievement-durable-persistence` is registered from 1.125.2 through
the compatible `ISTATS_UPDATE_1_125` listener APIs on 1.125.2, 1.139.2, and
1.152.11. It uses a real loopback server but validates only UniverseLAN's local
profile persistence and reload, not server durability. The runner creates one
fresh profile for a fixed identity and explicitly enables
`SaveAchievementsAndStats=1`. The writer retrieves its own isolated baseline,
requires zero integer and float stats plus a locked fixture-defined achievement,
writes fixed integer and finite float stats, unlocks the fixture achievement,
requires store success, then exits. Only after that successful exit does the
runner start a new reader process against the same profile. The reader retrieves
its own stats and requires the exact integer, an unlocked achievement with a
nonzero time, and the finite float's numeric and `uint32_t` bit values.

`user-data-live-propagation` is registered for 1.125.2, 1.139.2, and 1.152.11
with `HAS_SPECIFICUSERDATALISTENER` and typed Galaxy IDs. The receiver creates
and registers its specific-user-data listener before emitting its ready event. The
writer is released only by that event, writes a fixed unique key/value, and
requires the SDK-correct local callback: the global listener in 1.125.2 or the
per-operation listener in 1.139.2 and 1.152.11. The receiver accepts exactly
one callback for the declared writer, then validates the fixed key through the
remote `GetUserData(writer, key)` cache and rejects unrelated updates. The
writer remains alive through the receiver
validation gate; the runner release event bounds listener installation before
the mutation without an arbitrary propagation sleep.

`custom-networking-echo` is registered only with `HAS_ICUSTOMNETWORKING` and
`HAS_ICONNECTIONLISTENERS`.
The runner binds a binary-preserving ixwebsocket echo service to loopback on a
separate TCP port and publishes the WebSocket ready event only after `listen()`
and `start()`. The host initializes UniverseLAN locally, opens the supplied
plain `ws://127.0.0.1:<port>/echo` URL asynchronously, requires a nonzero open
connection ID, sends a payload containing a zero byte, pumps `ProcessData`,
and uses the connection read buffer to require an exact echo from that same
 connection. The host initializes and uninitializes its ixwebsocket network
 system around this operation. No SystemTest uses an external network.

`custom-networking-close` is registered for 1.125.2, 1.139.2, and 1.152.11
x64 with `HAS_ICUSTOMNETWORKING`. It uses the same real loopback UniverseLAN
server, sign-in, and runner-owned WebSocket echo service as the echo scenario.
The host opens the supplied URL, requires one successful nonzero connection ID
with no terminal failure, then closes that exact ID and requires one close
callback with `CLOSE_REASON_UNDEFINED`. A bounded pump rejects duplicate or
late terminal callbacks. SDK 1.125.2 uses the header's global open and close
listeners; 1.139.2 and 1.152.11 use only their operation-specific open and
close listeners, proving both callback paths remain version-correct.

`file-share-server-persisted-roundtrip` is registered only with `HAS_ISTORAGE`
and uses one host plus a real loopback UniverseLAN server. Runner-generated
client and server configuration explicitly enable shared-file upload and
download while retaining the normal isolated storage roots. The host writes a
scenario-unique nonempty binary payload containing a zero byte with `IStorage`,
then requires local existence, size, and exact bytes before sharing it. SDK
1.125.2 uses global file-share/download listeners; SDKs with
`HAS_ISTORAGE_FILESHARELISTENERS` use per-operation listeners. After a
successful nonzero shared ID, the host closes its local shared cache entry and
requires an empty cache before downloading that returned ID. It then validates
the successful download, sole indexed entry, name and copied name, size, full
payload, and an offset read before closing it. Finally, it requests the invalid
maximum ID, requires the failure callback, and confirms that no shared-file
cache entry was created. This cache eviction before download makes the byte
assertions a server-persistence contract rather than a read of the upload cache.

`file-share-server-policy-denied` is registered for 1.125.2, 1.139.2, and
1.152.11 with `HAS_ISTORAGE`. Its generated client configuration retains both
file-sharing permissions while the real server receives
`AllowFileSharingUpload=0`. The host writes and exactly rereads a valid nonempty
binary local file, then requires one terminal file-share failure with
`FAILURE_REASON_UNDEFINED`, no success callback or remote shared-file ID, and an
empty shared-file cache. SDK 1.125.2 exercises the global listener; 1.139.2 and
1.152.11 exercise per-operation listeners. This makes denial a server-policy
contract, rather than the existing client-side policy failure path.

`file-share-server-download-policy-denied` is registered through the same
storage-policy version list. It uses one host and a real loopback server with
upload enabled and download disabled, while the generated client configuration
retains both permissions. The host writes and exactly rereads a nonempty binary
file, shares it successfully with a nonzero ID, closes the upload-side shared
cache entry, and requires that cache to be empty before requesting that ID.
The request must produce exactly one download failure with the requested ID and
`FAILURE_REASON_UNDEFINED`, zero successes, and no cache repopulation. A
bounded post-failure pump rejects duplicate terminal callbacks. SDK 1.125.2
uses the global file-share/download listeners; 1.139.2 and 1.152.11 use only
their operation-specific listeners.

`cloud-storage-local-roundtrip` is registered only with `HAS_ICLOUDSTORAGE`,
which currently selects 1.152.11 x64 in the SystemTest matrix. It uses one
signed-in host and a real loopback UniverseLAN server. The host retains each
per-operation listener and the put/get buffers while pumping `ProcessData`.
It puts a fixed container/name and nonempty binary payload containing a zero
byte with `SAVEGAME_TYPE_MANUAL`, a fixed timestamp, and an explicit 32-character
hash. It requires exactly one put success and no terminal failure callback,
then lists the container and, inside the list callback, requires the sole entry
name, size, timestamp, and hash without asserting quota. It then calls
`GetFileMetadata` with a retained listener and requires one success, no failure,
matching container/name, a metadata-only size of zero, manual save type, and a
nonempty savegame ID. Finally, it gets the file with an exact payload-size buffer
and requires one success, no terminal failure callback, matching container/name/
manual save type/nonempty savegame ID/actual payload size, and exact bytes.
This exercises UniverseLAN's client-local cloud container only; it does not
exercise server-synchronized cloud storage. Quota, oversized buffers, and
omitted hashes are deliberately not asserted because they are not deterministic
or currently compatible baseline contracts.

`apps-config-and-dlc-ownership` is registered for the `HAS_IAPPS` and
`HAS_GETCURRENTGAMELANGUAGE` contracts on 1.125.2, 1.139.2, and 1.152.11. It
uses one signed-in host and a real loopback UniverseLAN server. Its validated
host-only `apps` configuration sets `Language=polish`, `LanguageCode=pl-PL`,
`EnableAllDLC=0`, `SaveUnknownDLCIDs=0`, and `DLC.ini` values `210001=1` and
`210002=0`. The host requires the installed/disabled/absent DLC results and
the direct, exact-copy, and null-terminated truncated language results. SDKs
with `HAS_IAPPS_LANGUAGECODE` assert the corresponding `pl-PL` APIs. SDK
1.152.11 additionally retains a supplied `IIsDlcOwnedListener`, registers a
separate global listener, and requires one successful `(210001, true)` callback
with no failures for each, proving supplied and global delivery coexist.

`telemetry-local-event-result` is registered only with `HAS_ITELEMETRY` for
1.139.2 and 1.152.11 x64, never 1.125.2. It uses one signed-in host and a real
loopback UniverseLAN server, while explicitly exercising only the client-local
telemetry sink, not server telemetry. Its sole validated `telemetry` override
renders `[Telemetry] Store=1`; the runner deliberately does not precreate the
sink directory. The host requires nonnull `ITelemetry`, retains a supplied
`ITelemetryEventSendListener`, sends one fixed event type, pumps `ProcessData`,
and requires exactly one success, no failure, the exact event type, and a
nonzero callback index equal to `SendTelemetryEvent`'s return value.

`utils-overlay-disabled-invariant` is registered for 1.125.2, 1.139.2, and
1.152.11 only when `HAS_IUTILS`, `HAS_IUTILS_SHOWOVERLAYWITHWEBPAGE`,
`OVERLAYSTATE_ENUM`, and `HAS_DISABLEOVERLAYPOPUPS` are available. One
signed-in host runs against a real loopback UniverseLAN server, requires a
nonnull `IUtils`, and requires `OVERLAY_STATE_DISABLED` plus a false visibility
getter before the exercise. It installs global overlay initialization-state and
visibility listeners before calling `ShowOverlayWithWebPage` with a fixed valid
URL and `DisableOverlayPopups` for every documented group: `chat_message`,
`friend_invitation`, and `game_invitation`. A bounded `ProcessData` pump then
requires unchanged disabled/not-visible getters and zero callbacks. This is an
unsupported-overlay behavior contract; it does not assert artificial success
from either void request API.

## Implementation Maintenance

The native implementations are split into target-private `SystemTests/Host`
and `SystemTests/Runner` source/header units by responsibility. The narrow
`SystemTests/Common` layer contains only shared standard-library protocol and
validation utilities; Galaxy dependencies remain host-private. The refactor
preserves CTest names, manifests, provider behavior, and version-feature guards.
