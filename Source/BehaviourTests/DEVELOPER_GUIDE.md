# BehaviourTests Developer Guide

BehaviourTests compare public Galaxy SDK observations from the matching official
GOG runtime with UniverseLAN. Start at [README.md](README.md), then read the
[`BEHAVIOUR_TEST_PLAN.md`](BEHAVIOUR_TEST_PLAN.md),
[`COVERAGE.md`](COVERAGE.md), and
[`BEHAVIOUR_DIFFERENCES.md`](BEHAVIOUR_DIFFERENCES.md) before adding a probe.
Use [`TODO_PROGRESS.md`](TODO_PROGRESS.md) to distinguish completed work from
future work and required validation.

## Build And Opt In

The framework is x64 SDK `1.152.11` only. It builds two different hosts from
the same public-SDK source: one links to the UniverseLAN import target and one
links to `gog/Galaxy64.lib`. `BUILD_ALL_TESTS=ON` builds the framework but does
not opt into official scenarios.

```powershell
cmake -S . -B cmake-behaviour-15211-x64 -G "Visual Studio 18 2026" -A x64 -D BUILD_UNIVERSELAN_BEHAVIOUR_TESTS=ON -D LIMIT_VERSIONS="1.152.11"
cmake --build cmake-behaviour-15211-x64 --config Debug
ctest --test-dir cmake-behaviour-15211-x64 -C Debug -N -L "behavior|gog"
```

The last command lists no tests unless all prerequisites exist and
`ENABLE_UNIVERSELAN_GOG_BEHAVIOUR_TESTS=ON` was set at configure time. The
opt-in requires ignored `Source/TestCommon/credentials.cmake`, matching
`Galaxy64.lib`, `Galaxy64.dll`, and `GalaxyPeer64.dll` under
`Source/DLLs/1.152.11/gog/`, an authenticated official environment, and
network access. CMake emits an unavailable diagnostic instead of failing when
these are absent. The direct `IChat` scenario also requires the approved
official profiles to be friends and their messaging privacy to permit friends.
That setting is an external test-environment precondition only; it is not a
UniverseLAN root-cause conclusion.

After verifying those prerequisites, configure a separate opt-in build (or
reconfigure the framework build) explicitly:

```powershell
cmake -S . -B cmake-behaviour-15211-x64 -G "Visual Studio 18 2026" -A x64 -D BUILD_UNIVERSELAN_BEHAVIOUR_TESTS=ON -D ENABLE_UNIVERSELAN_GOG_BEHAVIOUR_TESTS=ON -D LIMIT_VERSIONS="1.152.11"
cmake --build cmake-behaviour-15211-x64 --config Debug
```

Run explicitly registered behavior tests only with the portable script:

```powershell
cmake -D BEHAVIOUR_TEST_BUILD_DIR="cmake-behaviour-15211-x64" -D BEHAVIOUR_TEST_CONFIGURATION="Debug" -P Source/BehaviourTests/RunBehaviorCTest.cmake
cmake -D BEHAVIOUR_TEST_BUILD_DIR="cmake-behaviour-15211-x64" -D BEHAVIOUR_TEST_CONFIGURATION="Debug" -D BEHAVIOUR_TEST_LABEL="^gog-services-state$" -P Source/BehaviourTests/RunBehaviorCTest.cmake
cmake -D BEHAVIOUR_TEST_BUILD_DIR="cmake-behaviour-15211-x64" -D BEHAVIOUR_TEST_CONFIGURATION="Debug" -D BEHAVIOUR_TEST_LABEL="^session-id-repeatability$" -P Source/BehaviourTests/RunBehaviorCTest.cmake
cmake -D BEHAVIOUR_TEST_BUILD_DIR="cmake-behaviour-15211-x64" -D BEHAVIOUR_TEST_CONFIGURATION="Debug" -D BEHAVIOUR_TEST_LABEL="^public-lobby-create-list-join-leave$" -P Source/BehaviourTests/RunBehaviorCTest.cmake
cmake -D BEHAVIOUR_TEST_BUILD_DIR="cmake-behaviour-15211-x64" -D BEHAVIOUR_TEST_CONFIGURATION="Debug" -D BEHAVIOUR_TEST_LABEL="^public-lobby-data-propagation$" -P Source/BehaviourTests/RunBehaviorCTest.cmake
cmake -D BEHAVIOUR_TEST_BUILD_DIR="cmake-behaviour-15211-x64" -D BEHAVIOUR_TEST_CONFIGURATION="Debug" -D BEHAVIOUR_TEST_LABEL="^chat-room-message-delivery$" -P Source/BehaviourTests/RunBehaviorCTest.cmake
cmake -D BEHAVIOUR_TEST_BUILD_DIR="cmake-behaviour-15211-x64" -D BEHAVIOUR_TEST_CONFIGURATION="Debug" -D BEHAVIOUR_TEST_LABEL="^multiple-lobby-membership-and-message-isolation$" -P Source/BehaviourTests/RunBehaviorCTest.cmake
```

The strict service-state contract is CTest-registered; its characterization
diagnostic is deliberately not. Invoke the diagnostic runner flag explicitly
after building the framework:

```powershell
& "bin/Debug/universelan-behaviour-runner-x64-1.152.11.exe" --characterize-gog-services-state --universelan-host "bin/Debug/universelan-behaviour-host-universelan-x64-1.152.11.exe" --gog-host "bin/Debug/universelan-behaviour-host-gog-x64-1.152.11.exe" --client-dll "bin/1.152.11/Debug/Galaxy64.dll" --server "bin/1.152.11/Debug/UniverseLANServer64.exe" --gog-runtime-dir "Source/DLLs/1.152.11/gog"
```

It launches the same four hosts and uses the same private credential profiles
as the contract test. Its successful root is retained and printed as
`runDirectory=...`; it contains raw and normalized lane reports. The mode is
characterization data only: it records immediate, one-`ProcessData`, and
ten-pump settled service-state queries and symbolic globally registered
listener events, but does not compare lanes or assert a total event order.

Characterize the official direct-chat behavior before changing its strict
public facts:

```powershell
& "bin/Debug/universelan-behaviour-runner-x64-1.152.11.exe" --characterize-official-gog-chat-room-message-delivery --gog-host "bin/Debug/universelan-behaviour-host-gog-x64-1.152.11.exe" --gog-runtime-dir "Source/DLLs/1.152.11/gog"
```

Then collect the dual-lane diagnostic when needed:

```powershell
& "bin/Debug/universelan-behaviour-runner-x64-1.152.11.exe" --characterize-chat-room-message-delivery --universelan-host "bin/Debug/universelan-behaviour-host-universelan-x64-1.152.11.exe" --gog-host "bin/Debug/universelan-behaviour-host-gog-x64-1.152.11.exe" --client-dll "bin/1.152.11/Debug/Galaxy64.dll" --server "bin/1.152.11/Debug/UniverseLANServer64.exe" --gog-runtime-dir "Source/DLLs/1.152.11/gog"
```

The similarly non-CTest lobby-data characterization mode is:

```powershell
& "bin/Debug/universelan-behaviour-runner-x64-1.152.11.exe" --characterize-public-lobby-data-propagation --universelan-host "bin/Debug/universelan-behaviour-host-universelan-x64-1.152.11.exe" --gog-host "bin/Debug/universelan-behaviour-host-gog-x64-1.152.11.exe" --client-dll "bin/1.152.11/Debug/Galaxy64.dll" --server "bin/1.152.11/Debug/UniverseLANServer64.exe" --gog-runtime-dir "Source/DLLs/1.152.11/gog"
```

Characterize the Advanced multiple-lobby contract against official GOG first:

```powershell
& "bin/Debug/universelan-behaviour-runner-x64-1.152.11.exe" --characterize-multiple-lobby-membership-and-message-isolation --universelan-host "bin/Debug/universelan-behaviour-host-universelan-x64-1.152.11.exe" --gog-host "bin/Debug/universelan-behaviour-host-gog-x64-1.152.11.exe" --client-dll "bin/1.152.11/Debug/Galaxy64.dll" --server "bin/1.152.11/Debug/UniverseLANServer64.exe" --gog-runtime-dir "Source/DLLs/1.152.11/gog"
```

All characterization modes report `comparison=none`; they retain sanitized
raw/normalized traces for local inspection and never make a contract pass.

## Security And Runtime Isolation

Credentials are compiled from a private generated header based on the ignored
local file and chosen only through the `user1` and `user2` profile tokens.
Never place credential values in arguments, manifests, traces, documentation,
diagnostics, or commits.
Each run has a private temporary root. The runner stages the UniverseLAN DLL
next to UniverseLAN hosts and every matching official `*.dll` beside official
hosts. Successful comparison roots are removed. Characterization roots and
failed or mismatched comparison roots are retained and reported as
`runDirectory=...`; they contain raw lane traces and the normalized comparison
report and must be treated as sensitive local artifacts.
Do not attach, commit, paste, or quote a retained root. Reports are interpreted
from symbolic records and classifications only: `exact-equality` is a match,
`accepted-difference` is a documented narrow passing exception, and `mismatch`
or a candidate difference is a failure. Diagnostic-only fields, including
elapsed timing, retry counts, callback multiplicity, and cross-host gate
discovery order, are context unless the scenario contract explicitly says
otherwise.

`laneMode` defaults to `concurrent`: the UniverseLAN server, two UniverseLAN
hosts, and two official hosts are launched together. The manifest can select
`sequential` when local account or runtime contention requires it.

`Simple/public-lobby-create-list-join-leave` is concurrent only in practice: it
starts the UniverseLAN server, both UniverseLAN hosts, and both official hosts.
Its private run root contains a distinct control file for each host. The runner
creates a collision-resistant token only in those files, relays symbolic
creator-ready/joiner-joined/two-member/joiner-left gates through them, and uses
separate event files for acknowledgements. Do not inspect or copy those files.
They are orchestration data, never test evidence. On any host failure or timeout
the runner requests abort through every control file, waits up to five seconds
for every `cleanup-ack`, then terminates any remaining host. Failed roots remain
for local cleanup diagnosis; successful roots are removed only after both leaves
and all acknowledgements complete.

The portable script runs the `behavior` label in `Debug` by default. Set
`BEHAVIOUR_TEST_CONFIGURATION` for another multi-config build configuration and
`BEHAVIOUR_TEST_LABEL` to an anchored registered scenario label for a focused
run. A passing `Simple/gog-services-state` run prints the matched/mismatched
comparison result, each lane's normalized symbolic state, and its
same-profile `exact-equality` or `accepted-difference` classification; no account
IDs, credentials, or persona text are printed. Its manifest accepts only `GOG
undefined` with `UniverseLAN connected`; every other state and record remains
strict. The lobby report retains bounded retry diagnostics and identifies the
observed faster UniverseLAN convergence as an accepted difference without making
attempt count or retry timing a lane-equivalence requirement.

## Scenario Rules

Host assertions must use only the selected version's public `galaxy/` headers.
Do not include UniverseLAN implementation headers, call product APIs, inspect
configuration/state/protocol files, or compare raw opaque IDs across lanes.
Every scenario declares its own expected, permitted, and failing record rules;
there is no global callback allowance. Do not compare elapsed timing except for
bounded liveness. Simple scenarios preserve callback/event order within the
logical SDK interface under test; use only causal constraints across independent
interfaces or hosts. Update the coverage register and the difference log when
adding or characterizing a scenario.

The approved comparator host contracts are `initialize-and-sign-in`,
`session-id-repeatability`, `gog-services-state`,
`public-lobby-create-list-join-leave`, `public-lobby-data-propagation`, and
`chat-room-message-delivery`, and
`multiple-lobby-membership-and-message-isolation`; the additional runner-selected diagnostics are
`gog-services-state-characterization`,
`public-lobby-data-propagation-characterization`, and
`chat-room-message-delivery-characterization`, and
`multiple-lobby-membership-and-message-isolation-characterization`. Manifests and host
arguments outside that fixed registry are rejected. The strict `gog-services-state`
contract uses no service-state listener and makes its single public
`IUtils::GetGogServicesConnectionState()` query after auth success and before
another `ProcessData` call.

The strict `session-id-repeatability` contract uses the same concurrent four-host
credential sign-in path. After `OnAuthSuccess`, before another `ProcessData`, it
calls only `IUser::GetSessionID()` twice back-to-back and emits only their boolean
equality relation. Its focused run prints the matched/mismatched comparison and
official normalized equality for `user1` and `user2`. A mismatch retains the raw
traces and normalized report under its printed `runDirectory`; add a candidate to
`BEHAVIOUR_DIFFERENCES.md` using only those boolean observations.

The lobby contract uses only public `IMatchmaking` calls and listeners. It creates
a public, joinable, two-member FCM lobby, sets the private token under the fixed
metadata key, then uses an equality filter and at most six list attempts with a
250 ms backoff. The trace records the bounded retry fact, never the token. Both
lanes must converge successfully within that bound; their successful attempt
counts are retained for diagnosis but are not cross-lane equality because public
listing is eventually consistent. It
requires one selected candidate inside the list callback, performs the join, and
compares only normalized public relations. Do not add a global member-callback
ordering assertion. If the official comparison mismatches, retain its root and
add a candidate entry using only normalized symbolic facts and cleanup status.

`Simple/public-lobby-data-propagation` reuses the temporary lobby setup but arms
the joiner's public `GlobalLobbyDataListener` only after join completion. The
runner then releases the creator to call `SetLobbyData` with a separate fixed key
and a nonempty private token-derived value. The joiner uses only public
`GetLobbyDataCopy` to validate it. Its control protocol carries symbolic
observer-armed, update-complete, data-observed, leave, abort, and cleanup gates.
It never records the token, key, value, raw IDs, personas, credentials, or
timestamps. The strict comparison preserves per-host `IMatchmaking` record order
and has no creator/joiner callback-order assertion; callback count, duplicates,
and runner callback-gate discovery order are characterization diagnostics only.

`Simple/chat-room-message-delivery` is authorized only for temporary rooms and
one opaque runner-generated message per lane. Its official lane requires the
approved profiles to be friends with messaging privacy permitting friends; this
is an external test-environment precondition, not a product root-cause claim.
Each receiver registers a public
`GlobalChatRoomMessagesListener` before announcing readiness. Each host sends
its self ID only through a one-time private relay; the runner consumes it and
relays only the other participant ID through a second one-time private relay.
The host removes received relays immediately, and the runner removes every
relay, generated config, control, and runtime output from retained chat failure
artifacts. The token is supplied and consumed the same way. No raw ID, room ID,
message ID, token, or runtime stdout/stderr is retained or printed.

The sender uses only public `IChat::RequestChatRoomWithUser` and
`SendChatRoomMessage` operation listeners. The receiver reads index zero only
inside its public message callback and records symbolic sender, type, and token
relations. Ordered records are compared inside each host's `IChat` stream; the
only cross-host gate is receiver arming before sender release. Sender terminal
and receiver delivery callbacks have no cross-host order requirement. Both
hosts exit by their bounded deadline after their public callback contracts.
That exit is the agreed cleanup mechanism for temporary rooms/messages; the
public SDK exposes no delete-room API, so this test does not claim one exists.
The 2026-09-14 official-only characterization and strict four-host comparison
matched the stable symbolic request, send, and receive facts. Keep every one of
those facts strict; the external messaging permission is not encoded as a
product behavior or accepted-difference rule.

`Advanced/multiple-lobby-membership-and-message-isolation` uses the same two
profiles in one lane. Creator `CreateLobby` calls for symbolic `L0` and `L1`
are adjacent before `ProcessData`, with separate create/enter listeners. After
each successful automatic enter it explicitly calls `SetLobbyType(public)`,
`SetLobbyJoinable(true)`, and `SetMaxNumLobbyMembers(2)`, waits for their public
operation callbacks, and checks the three public queries before tagging either
lobby. The joiner independently discovers both tags, then issues both
`JoinLobby` calls adjacent before `ProcessData` with separate listeners. Both
hosts arm public lobby-message listeners before the creator sends adjacent,
opaque token-derived messages. Callback-local reads validate only symbolic
`L0`/`L1`, owner/sender, and payload relations. `ILobbyMessageListener` and
`GetLobbyMessage` expose no public message-type field in this SDK header, so
the trace explicitly reports that unavailable field rather than fabricating a
message type. Role-local callback record order is retained and strict for stable
operation sequences; the joiner cross-lobby message sequence is retained but not
equality-required because official characterization observed both `L0`, `L1`
and `L1`, `L0`. Cross-host order is not asserted. Cleanup leaves joiner `L1`
then `L0`, followed by creator `L1` then `L0`, all within the bounded deadline.
There is no claimed lobby delete API.

## Scenario Authoring And Required Validation

Keep a scenario narrow. First add a manifest with version, architecture, lane
mode, bounded timeout, roles, required public records, terminal outcome, and
opaque-value policy. Characterize it against official GOG before choosing strict
facts. Define required, permitted, ignored, and failing callbacks per scenario;
never add a suite-wide callback allowance. Normalize only opaque generated
values while retaining validity, type, equality, and cross-callback relations.

The manifest registry is intentionally fixed. To add a scenario, add its
public-SDK host behavior, matching runner contract/validation/normalization,
manifest, and opt-in CTest registration together; unknown manifest names and
host arguments are rejected. Then update the coverage, difference, and progress
registers with the actual official characterization and comparison result.

Before calling a scenario complete, perform the six checks in
[`TODO_PROGRESS.md`](TODO_PROGRESS.md#required-validation): public-SDK-only
audit, framework configure/build, diagnostic characterization, opt-in focused
CTest, cleanup verification, and synchronized register updates plus
`git diff --check`.
