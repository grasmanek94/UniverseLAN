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
these are absent. The direct-chat scenario
requires approved official profiles to be friends with direct-message privacy
permitting friends. `IFriends` peer-information retrieval has no friendship or
direct-message privacy precondition. These are external test-environment
preconditions only; they are not UniverseLAN root-cause conclusions.

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
cmake -D BEHAVIOUR_TEST_BUILD_DIR="cmake-behaviour-15211-x64" -D BEHAVIOUR_TEST_CONFIGURATION="Debug" -D BEHAVIOUR_TEST_LABEL="^public-lobby-owner-close-lifecycle$" -P Source/BehaviourTests/RunBehaviorCTest.cmake
cmake -D BEHAVIOUR_TEST_BUILD_DIR="cmake-behaviour-15211-x64" -D BEHAVIOUR_TEST_CONFIGURATION="Debug" -D BEHAVIOUR_TEST_LABEL="^public-lobby-owner-ownership-transition$" -P Source/BehaviourTests/RunBehaviorCTest.cmake
cmake -D BEHAVIOUR_TEST_BUILD_DIR="cmake-behaviour-15211-x64" -D BEHAVIOUR_TEST_CONFIGURATION="Debug" -D BEHAVIOUR_TEST_LABEL="^public-lobby-data-propagation$" -P Source/BehaviourTests/RunBehaviorCTest.cmake
cmake -D BEHAVIOUR_TEST_BUILD_DIR="cmake-behaviour-15211-x64" -D BEHAVIOUR_TEST_CONFIGURATION="Debug" -D BEHAVIOUR_TEST_LABEL="^chat-room-message-delivery$" -P Source/BehaviourTests/RunBehaviorCTest.cmake
cmake -D BEHAVIOUR_TEST_BUILD_DIR="cmake-behaviour-15211-x64" -D BEHAVIOUR_TEST_CONFIGURATION="Debug" -D BEHAVIOUR_TEST_LABEL="^friends-peer-information-retrieval$" -P Source/BehaviourTests/RunBehaviorCTest.cmake
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

Characterize the non-mutating friends peer-information contract twice against
official GOG before changing strict facts:

```powershell
& "bin/Debug/universelan-behaviour-runner-x64-1.152.11.exe" --characterize-official-gog-friends-peer-information-retrieval --gog-host "bin/Debug/universelan-behaviour-host-gog-x64-1.152.11.exe" --gog-runtime-dir "Source/DLLs/1.152.11/gog"
```

The command needs approved signed-in profiles only. It does not create
friendships or mutate social data. It prints only symbolic
terminal/state/persona-change facts and removes the successful private root.

Characterize reliable listener-mode P2P before changing its strict facts:

```powershell
& "bin/Debug/universelan-behaviour-runner-x64-1.152.11.exe" --characterize-official-gog-reliable-p2p-listener-peek --gog-host "bin/Debug/universelan-behaviour-host-gog-x64-1.152.11.exe" --gog-runtime-dir "Source/DLLs/1.152.11/gog"
```

The authorized temporary-lobby probe creates a public, initially nonjoinable,
capacity-two FCM lobby, sets its collision marker, then explicitly sets and
observes joinable before discovery. The marker is not confidential because
public lobby data can be listed and read; it is never printed. The creator finds
the peer only from public lobby membership and schedules one reliable bounded
opaque payload on its fixed channel after a bounded post-arm `ProcessData`
settling window. For each expected-channel callback, the joiner performs two
non-consuming `PeekP2PPacket` calls only in that callback, with callback-sized
private buffers, and destroys the listener before shutdown.
Do not add `IsP2PPacketAvailable`, `ReadP2PPacket`, `PopP2PPacket`, or a
post-callback removal assertion. The header describes scheduled send and
non-consuming peek semantics, not a delivery guarantee. Three clean official
trials on 2026-09-14 produced the exact scheduled-no-delivery observation: one
non-target callback, no expected-channel callback, and no peeks, with both
terminal leaves acknowledged. The passing focused comparison accepts only that
exact GOG relation versus the observed exact UniverseLAN expected-channel,
two-peek relation. Every setup, send, cleanup, and other callback field remains
strict.

The similarly non-CTest lobby-data characterization mode is:

```powershell
& "bin/Debug/universelan-behaviour-runner-x64-1.152.11.exe" --characterize-public-lobby-data-propagation --universelan-host "bin/Debug/universelan-behaviour-host-universelan-x64-1.152.11.exe" --gog-host "bin/Debug/universelan-behaviour-host-gog-x64-1.152.11.exe" --client-dll "bin/1.152.11/Debug/Galaxy64.dll" --server "bin/1.152.11/Debug/UniverseLANServer64.exe" --gog-runtime-dir "Source/DLLs/1.152.11/gog"
```

Characterize the owner-close lifecycle against official GOG twice before
changing its strict facts:

```powershell
& "bin/Debug/universelan-behaviour-runner-x64-1.152.11.exe" --characterize-official-gog-public-lobby-owner-close-lifecycle --gog-host "bin/Debug/universelan-behaviour-host-gog-x64-1.152.11.exe" --gog-runtime-dir "Source/DLLs/1.152.11/gog"
```

This official-only command uses two hosts and the authorized temporary tagged
public FCM lobby. After the joiner joins, it registers public global
member-state and lobby-left listeners, then the creator calls `LeaveLobby`.
The header documents a local `user-left` callback and describes FCM owner
*disconnection* as closing the lobby; `LeaveLobby` generically documents
other-member notifications but does not guarantee the narrow normal-FCM-close
callback absence. The diagnostic retains that empirical distinction,
per-target-lobby listener sequence, and observed post-close list result without
imposing listener order or multiplicity. Controls, token-bearing configuration,
runtime output, and relays are removed from retained roots; only symbolic
traces/reports and staged binaries remain.

Characterize ownership transition twice against official GOG before changing
its strict facts:

```powershell
& "bin/Debug/universelan-behaviour-runner-x64-1.152.11.exe" --characterize-official-gog-public-lobby-owner-ownership-transition --gog-host "bin/Debug/universelan-behaviour-host-gog-x64-1.152.11.exe" --gog-runtime-dir "Source/DLLs/1.152.11/gog"
```

It creates a tagged public, explicitly joinable, capacity-two
`LOBBY_TOPOLOGY_TYPE_FCM_OWNERSHIP_TRANSITION` lobby. The joiner filters and
joins, then arms public global member-state and owner-change listeners before
the creator's normal leave. Promote only facts stable across repeated official
runs: creator local `user-left`; prior-owner `left`; owner-change-to-self;
owner-only cache; token-derived promoted-owner `SetLobbyData` success and copied
visibility; joiner local `user-left`; and a post-empty token-filtered list.
The former owner remains alive until that final probe. Listener-class ordering,
callback multiplicity, and bounded list attempt count are diagnostics, never
strict cross-host rules. Successful characterization artifacts are sanitized.

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
creates a collision-resistant marker only in those files, relays symbolic
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
`public-lobby-create-list-join-leave`, `public-lobby-owner-close-lifecycle`, `public-lobby-owner-ownership-transition`, `public-lobby-data-propagation`, and
`chat-room-message-delivery`, `reliable-p2p-listener-peek`, and
`multiple-lobby-membership-and-message-isolation`; the additional runner-selected diagnostics are
`gog-services-state-characterization`,
`public-lobby-owner-close-lifecycle-characterization`, `public-lobby-owner-ownership-transition-characterization`, `public-lobby-data-propagation-characterization`, and
`chat-room-message-delivery-characterization`, `reliable-p2p-listener-peek-characterization`, and
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
a public, nonjoinable, two-member FCM lobby, sets the collision marker under the
fixed metadata key, then explicitly makes it joinable and observes that state
before using an equality filter and at most six list attempts with a
250 ms backoff. The trace records the bounded retry fact, never the marker value. Both
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
and a nonempty collision-marker-derived value. The joiner uses only public
`GetLobbyDataCopy` to validate it. Its control protocol carries symbolic
observer-armed, update-complete, data-observed, leave, abort, and cleanup gates.
It never records the token, key, value, raw IDs, personas, credentials, or
timestamps. The strict comparison preserves per-host `IMatchmaking` record order
and has no creator/joiner callback-order assertion; callback count, duplicates,
and runner callback-gate discovery order are characterization diagnostics only.

`Simple/public-lobby-owner-close-lifecycle` uses the same public setup with a
distinct collision marker in each lane. The runner releases the creator only after
the joiner has armed `GlobalLobbyMemberStateListener` and
`GlobalLobbyLeftListener`. Its only cross-host constraints are listener arming
before creator leave and cleanup acknowledgements. The host completes post-close
listing, then performs a bounded final settle before recording target-lobby
callback presence or absence. Target-lobby sequence and cross-listener ordering
are diagnostic, but a target global leave reason other than `lobby-closed` is a
failure. Two official characterizations empirically observed local creator
`user-left`, joiner global `lobby-closed`, tagged-list absence, and no targeted
prior-owner member-state callback. `LeaveLobby` generically documents member
notifications, so that absence is not a header guarantee. UniverseLAN matches
the characterized narrow close behavior. A creator emits cleanup acknowledgement
only after its matching terminal leave callback; after failure or timeout it may
retry only while public owner/member state proves safety, and acknowledges only
if that retry's terminal callback confirms cleanup. Otherwise the runner reports
unacknowledged cleanup and fails diagnostics.

`Simple/public-lobby-owner-ownership-transition` is distinct from normal FCM
close. It uses only public `IMatchmaking` APIs with
`LOBBY_TOPOLOGY_TYPE_FCM_OWNERSHIP_TRANSITION`. The strict joiner record requires
the initial two-member non-self owner relation, listener registration before the
creator release, prior-owner `LEFT`, owner-change-to-self, public owner/cache
promotion, and successful token-derived `SetLobbyData` plus copied visibility.
After its matching `user-left` terminal callback, the joiner performs a bounded
token-filtered empty-list probe. The creator does not acknowledge completion
until that probe signals absence. Callback sequences across global listener
classes and list retry counts are retained as diagnostic context only; each
required relationship remains strict.

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

`Simple/friends-peer-information-retrieval` is non-mutating and uses only
`IFriends::RequestUserInformation(peer, AVATAR_TYPE_NONE, listener)`,
`IsUserInformationAvailable`, `GetFriendPersonaNameCopy`, and
`GetFriendPersonaState`, after both hosts install
`GlobalPersonaDataChangedListener`. Each host relays its self ID once through a
private file only after listener registration; the runner consumes/deletes it,
then supplies one peer relay that the receiving host deletes. The terminal
record contains only success/failure, callback peer=requested-peer and valid
non-self relations, post-terminal availability, copied-name nonemptiness, and
symbolic persona state. Ordered persona-change events contain only symbolic
relation/change pairs. No raw ID, name, avatar data, count, status text,
  timestamp, credential, runtime output, control, or relay is retained.
  `AVATAR_TYPE_NONE` does not assert absent avatar-related callbacks because
   default avatar criteria can apply. A later official `none`-only variation
   leaves requested-peer-only listener events as retained diagnostic context,
   never sorted or merged, and no cross-host total order is asserted. The
   manifest accepts only the observed same-profile persona-state pair `GOG
   offline` and `UniverseLAN online`, consistent with the documented
   service-state environment where official GOG has no GOG Galaxy service while
   UniverseLAN provides its LAN service. This accepted beneficial environmental
   difference is not an SDK guarantee; terminal, availability, copied-name,
   callback-peer, and all other required facts remain strict.

`Advanced/multiple-lobby-membership-and-message-isolation` uses the same two
profiles in one lane. Creator `CreateLobby` calls for symbolic `L0` and `L1`
are adjacent before `ProcessData`, with separate create/enter listeners. After
each successful automatic enter it explicitly sets public/capacity, writes its
public collision marker, then calls `SetLobbyJoinable(true)` and observes all
three public queries before discovery. The joiner independently discovers both
markers, then issues both
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
