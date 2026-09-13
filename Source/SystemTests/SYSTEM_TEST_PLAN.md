# UniverseLAN System Test Plan

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
- Unique fixed client identities per role; no PID, MAC, debug-ID, or user-data
  derived identities.
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
  connections and tick rate.
- Each host has a required unique `identity.userId` and optional stable persona
  name. The runner rejects duplicate IDs before launching a process.
- `identity.credentialProfile` is optionally `user1` or `user2`; it selects a
  local build-time profile and cannot carry raw credentials. The local
  UniverseLAN sign-in path ignores it, uses `SignInGalaxy`, and needs no real
  credentials.
- `Source/TestCommon/credentials.cmake` is optional for SystemTests. When it
  provides both named profiles and the Galaxy application ID and secret, CMake
  passes opaque host-only definitions; when unavailable, normal UniverseLAN
  builds still configure and GOG hosts report `CredentialProfileUnavailable`
  without logging credential values.
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
