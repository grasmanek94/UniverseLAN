# UniverseLAN System Test Plan

## Scope

System tests validate externally visible UniverseLAN Galaxy API behavior through
real UniverseLAN client DLLs and, when declared by a scenario, real
UniverseLAN server executables. They do not load or contact real GOG Galaxy
libraries or services.

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

A scenario can declare zero or one server and any number of DLL hosts. This
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
  "timeoutSeconds": 30,
  "server": {
    "enabled": true,
    "readyEvent": "server-ready"
  },
  "hosts": [
    {
      "role": "creator",
      "scenario": "create-lobby",
      "waitFor": ["server-ready"],
      "signals": ["lobby-ready"],
      "timeoutSeconds": 10
    },
    {
      "role": "joiner",
      "scenario": "list-and-join-lobby",
      "waitFor": ["server-ready", "lobby-ready"],
      "timeoutSeconds": 10
    }
  ]
}
```

The manifest describes process orchestration only. Worker scenario names map
to compiled, version-aware Galaxy API behaviors; manifests never embed C++ or
untrusted commands.

## Process Protocol

The orchestrator captures each child stdout and accepts one line-delimited
protocol:

```text
SYSTEM_TEST EVENT name=server-ready
SYSTEM_TEST EVENT name=lobby-ready lobby=1234
SYSTEM_TEST PASS role=joiner
SYSTEM_TEST FAIL role=creator reason=CreateLobbyTimeout
```

The runner forwards declared events to dependent hosts through a per-run
control directory. A host receives a release only after all of its `waitFor`
events have been observed. Any malformed protocol line, unexpected exit,
duplicate PASS, FAIL line, or deadline expiry fails the scenario and records
the child output in the run directory.

## Isolation And UniverseLAN Selection

For every run, the orchestrator creates a unique temporary root with separate
working directories for the server and every host. It writes deterministic
UniverseLAN configuration into each directory:

- Loopback-only networking with a runner-selected UDP port and a fixed test key.
- Unique fixed client identities per role; no PID, MAC, debug-ID, or user-data
  derived identities.
- Tracing, console interaction, and real-service behavior disabled.
- Server and client data directories below the temporary root only.

The runner receives the selected version's built `UniverseLANServer` target
path and version-specific DLL host target path from CMake. It therefore always
launches UniverseLAN artifacts, never a real GOG Galaxy executable or runtime.

## CMake Contract

- `BUILD_UNIVERSELAN_SYSTEM_TESTS=1` adds `Source/SystemTests` and enables CTest.
- `BUILD_ALL_TESTS=1` also enables system tests.
- Unit tests and GoogleTest remain independent of system tests.
- For each selected SDK version, CMake creates a version-specific DLL host and
  orchestrator, passing `$<TARGET_FILE:universelan-server-...>` and the host
  path to `add_test`.
- Each system test has `TIMEOUT`, `RUN_SERIAL`, and a shared network
  `RESOURCE_LOCK` to prevent port and output collisions.
- Cross-platform CMake/CTest runs the native orchestrator. No batch or shell
  script is required for test execution; optional scripts only configure common
  unit, system, or all-test build modes.

## Initial Scenarios

1. `lobby-create-list-join`: server plus creator and joiner hosts. Verifies
   initialize, local sign-in, asynchronous callback pumping, lobby creation,
   lobby list visibility, and join success.
2. `p2p-message-exchange`: server plus two hosts. Verifies a visible custom
   networking send/receive callback path.
3. `p2p-three-peer-routing`: server plus three hosts. Verifies recipient
   routing and that a non-recipient does not receive the packet.

Only the first scenario will be implemented initially. Later scenarios reuse
the same manifest, host protocol, process runner, and isolation behavior.
