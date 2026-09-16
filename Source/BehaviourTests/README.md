# BehaviourTests

BehaviourTests compare what an SDK client can observe from UniverseLAN with the
matching official GOG Galaxy runtime. They are compatibility contracts, not
UniverseLAN implementation tests. The authoritative lane is official GOG.

Start with [DEVELOPER_GUIDE.md](DEVELOPER_GUIDE.md) for the runnable tutorial,
then use these living registers:

| Document | Use it for |
| --- | --- |
| [BEHAVIOUR_TEST_PLAN.md](BEHAVIOUR_TEST_PLAN.md) | Architecture, comparison policy, and implemented scope. |
| [COVERAGE.md](COVERAGE.md) | Per-scenario status, observations, and comparison rules. |
| [BEHAVIOUR_DIFFERENCES.md](BEHAVIOUR_DIFFERENCES.md) | Live accepted differences, candidate mismatches, and matched baselines. |
| [TODO_PROGRESS.md](TODO_PROGRESS.md) | Completed milestones, remaining work, and required validation. |

## Non-Negotiable Rule

Host assertions may use only the selected SDK version's public `galaxy/`
headers and public calls, callbacks, and state queries. Do not include or
inspect UniverseLAN implementation headers, server state, protocol/configuration
files, generated files, or raw runtime output. Runner control files coordinate
processes only; they are never behavior evidence.

## Quick Start

The current framework supports x64 SDK `1.152.11` only. Build the framework
without registering live official-GOG tests:

```powershell
cmake -S . -B cmake-behaviour-15211-x64 -G "Visual Studio 18 2026" -A x64 -D BUILD_UNIVERSELAN_BEHAVIOUR_TESTS=ON -D LIMIT_VERSIONS="1.152.11"
cmake --build cmake-behaviour-15211-x64 --config Debug
```

Live comparisons are deliberately opt-in. After the local preflight described
in the guide succeeds, add
`-D ENABLE_UNIVERSELAN_GOG_BEHAVIOUR_TESTS=ON` to the configure command and
run the registered `behavior` label through `RunBehaviorCTest.cmake`.

Never commit or print credentials. The ignored
`Source/TestCommon/credentials.cmake` supplies two approved accounts plus the
client credentials. Matching official `Galaxy64.lib`, `Galaxy64.dll`, and the
default `GalaxyPeer64.dll` under `Source/DLLs/1.152.11/gog`, an authenticated
official environment, and network access are also required. The base
`Galaxy64.dll` remains in that directory; the channel-8 peer is a local-only
staging overlay. Missing prerequisites leave live tests unregistered rather
than making normal builds fail. Direct `IChat` additionally needs approved
official profiles to be friends with direct-message privacy permitting friends.
`IFriends` peer-information retrieval has no friendship or direct-message
privacy precondition. These are external test-environment preconditions, not
product root-cause claims.

## Local Channel-8 Peer Overlay

The runner can stage a verified channel-8 `msvc-18` `GalaxyPeer64.dll` over its
side-by-side copy. Do not replace or commit the official `Galaxy64.dll` or any
downloaded binary. Download and verify the peer in a temporary directory, using
GOG's channel-8 manifest as the authority:

```powershell
$root = Join-Path $env:TEMP "universelan-gog-peer-8"
New-Item -ItemType Directory -Force -Path $root | Out-Null
$manifestUri = "https://cfg.gog.com/desktop-galaxy-peer/8/master/files-windows.json"
$manifestPath = Join-Path $root "files-windows.json"
curl.exe --fail --silent --show-error --location $manifestUri --output $manifestPath
$manifest = Get-Content -Raw -LiteralPath $manifestPath | ConvertFrom-Json
$entry = @($manifest.files | Where-Object { $_.path -eq "peer/msvc-18/GalaxyPeer64.dll" })
if ($entry.Count -ne 1) { throw "Channel-8 msvc-18 peer entry was not unique" }
$archivePath = Join-Path $root "GalaxyPeer64.dll.zip"
curl.exe --fail --silent --show-error --location "$($manifest.baseURI)/$($entry[0].resource)" --output $archivePath
if ((Get-Item -LiteralPath $archivePath).Length -ne [Int64]$entry[0].size) { throw "Peer archive size mismatch" }
Expand-Archive -LiteralPath $archivePath -DestinationPath (Join-Path $root "expanded") -Force
$peerPath = Join-Path $root "expanded\GalaxyPeer64.dll"
if ((Get-FileHash -LiteralPath $peerPath -Algorithm MD5).Hash.ToLowerInvariant() -ne $entry[0].hash) { throw "Peer MD5 mismatch" }
if ((Get-FileHash -LiteralPath $peerPath -Algorithm SHA256).Hash.ToLowerInvariant() -ne $entry[0].sha256) { throw "Peer SHA256 mismatch" }
```

The verified manifest selects resource
`GalaxyPeer/145625863/windows/peer/msvc-18/GalaxyPeer64.dll.zip`, archive size
`4046641`, extracted MD5 `42003330fb3100d7597544b465211e9f`, and extracted
SHA-256 `e3526b29caad722468081a9c2d04f918db046b155a17baf797d562b950ee3713`.
The manifest hashes the extracted DLL, not the ZIP. Configure the local-only
overlay directory (or pass its DLL directly with `--gog-peer-overlay`):

```powershell
cmake -S . -B cmake-behaviour-15211-x64 -G "Visual Studio 18 2026" -A x64 -D BUILD_UNIVERSELAN_BEHAVIOUR_TESTS=ON -D ENABLE_UNIVERSELAN_GOG_BEHAVIOUR_TESTS=ON -D LIMIT_VERSIONS="1.152.11" -D UNIVERSELAN_BEHAVIOUR_TEST_GOG_PEER_OVERLAY="$root\expanded"
```

The runner copies all default official DLLs, then overwrites only staged
`GalaxyPeer64.dll`. CMake passes the option to every registered official
scenario; with no cache entry or `--gog-peer-overlay` argument, staging is
unchanged. Treat the temporary directory as local tooling: never attach, print,
or commit its binaries.

The verified 2026-09-14 full-suite run staged the expected peer hash in both
official hosts, but finished 18/21: all three listener P2P contracts retained
the historical non-target callback. GOG documents that modern SDKs load this
component from installed GOG Galaxy client redistributables, so side-by-side
staging alone is not evidence that the runtime selected the overlay. The strict
listener contracts remain unresolved and are not passing UniverseLAN differences.

`Simple/reliable-p2p-listener-peek` uses an authorized tagged temporary public
FCM lobby. The public tag is a collision marker, not confidential data. The
creator creates it nonjoinable, tags/configures it, then explicitly observes
`SetLobbyJoinable(true)` before discovery. The joiner constructs
`GlobalNetworkingListener` before the runner releases the creator. For each
expected-channel `OnP2PPacketAvailable` callback, it performs two
`PeekP2PPacket` calls, then destroys the listener before `Shutdown`. It never
uses polling, read, or pop APIs in listener mode. The strict contract requires
exactly one expected-channel callback and two equivalent callback-local peeks in
both lanes. The verified local overlay did not establish that result in the
current environment, so this test remains failing rather than accepting no
delivery; setup, scheduling, cleanup, and all callback relations remain strict.

`Simple/bidirectional-reliable-p2p-listener-peek` uses the same safe public,
capacity-two FCM lobby setup. Both members obtain the other peer only from the
joined lobby's public member queries, construct `GlobalNetworkingListener`, and
complete the bounded post-arm settling window before the runner releases their
synchronized exchange. Each sends one distinct opaque token-derived payload with
`P2P_SEND_RELIABLE`: channel 73 from `user1` to `user2`, and channel 74 in the
reverse direction. Every expected-channel callback makes exactly two
callback-local `PeekP2PPacket` calls; listener mode never polls, reads, or pops.
Each direction strictly requires one expected-channel callback and exactly two
equivalent callback-local peeks in both lanes. The verified local overlay did
not establish those facts in the current environment. Listener destruction,
peer/lobby/channel/payload relations, scheduling, and fresh-deadline cleanup
remain strict; no raw IDs, bytes, lengths, token, or marker are retained.

`Simple/bidirectional-unreliable-p2p-listener-peek` reuses that public,
initially nonjoinable, capacity-two FCM-lobby and fresh-deadline cleanup path.
Both members derive their peer only from current public lobby membership, arm and
settle `GlobalNetworkingListener`, then send one distinct opaque payload with
`P2P_SEND_UNRELIABLE` on separate non-default channels after the synchronized
release. Each expected-channel callback makes exactly two callback-local,
non-consuming `PeekP2PPacket` calls; listener mode never polls, reads, or pops.
Both directions strictly require one expected-channel callback and two
equivalent callback-local peeks in both lanes. The verified local overlay did
not establish those facts in the current environment. `SendP2PPacket` returning
true still means only that its UDP-like packet was scheduled. Peer/lobby/channel/
payload, delivery, scheduling, listener destruction, and cleanup remain strict;
no raw IDs, bytes, lengths, token, or marker are retained.

`Simple/bidirectional-reliable-p2p-poll-read` is a separate listener-free
contract. Both members use the same safe public capacity-two FCM lobby, obtain
the other peer only from joined-lobby membership, and send one distinct reliable
opaque payload on separate channels after the synchronized polling gate. No
`GlobalNetworkingListener` is constructed. In each polling loop, `ProcessData`
precedes `IsP2PPacketAvailable`; only availability permits one exact-size
`ReadP2PPacket`. The immediately following availability check confirms that the
read consumed the expected-channel queue entry. Three clean official-only trials
and the focused four-host comparison on 2026-09-14 matched every symbolic
peer/channel/payload, read, consumption, and cleanup relation. This polling-mode
delivery result is separate from the unresolved listener-mode exact-delivery
contracts. The header still directs listener users to callback-local
non-consuming peeks rather than polling or reading.

`Simple/reliable-p2p-after-lobby-leave` is a separate post-leave contract. It
creates the same authorized nonjoinable-to-joinable tagged public capacity-two
FCM lobby. User2 arms `GlobalNetworkingListener`, confirms `LeaveLobby`, and
remains alive. User1 arms `GlobalLobbyMemberStateListener`, observes the former
member `left`, settles public one-member/self-owner state, then calls one
reliable `SendP2PPacket` to the saved former valid user ID. Two official
`1.152.11/x64` trials and the focused four-host comparison observed scheduling
but no former-member networking callback or peek. This matched baseline claims
no LAN benefit and does not generalize scheduling into delivery. Listener mode
uses only callback-local non-consuming peeks and never polls, reads, or pops.

`Simple/bidirectional-lobby-message-delivery` uses one tagged temporary public,
capacity-two FCM lobby per lane. The creator creates it nonjoinable, writes the
public collision marker and capacity, then explicitly completes and observes
`SetLobbyJoinable(true)` before discovery. Both members arm
`GlobalLobbyMessageListener` before the shared exchange release and each
schedules exactly one distinct opaque binary payload. Each callback reads only
with callback-local `GetLobbyMessage`, retaining symbolic shared-lobby,
self/other-sender, payload, and size relations. Two official-only trials
observed two callbacks in local `self, other` order for both hosts. The focused
 comparison matched every strict relation; the UniverseLAN joiner reported
`other, self`, which remains an explicit independent-sender order diagnostic,
not a cross-host or global-order contract. All cleanup acknowledgements passed.

`Simple/bidirectional-lobby-member-data-propagation` uses the same initially
nonjoinable, tagged public capacity-two FCM lobby setup. Both hosts establish
public two-member state and arm `GlobalLobbyDataListener` before the shared
release. Each sets one distinct opaque token-derived member-data value under its
own fixed public key with `SetLobbyMemberData`. In this selected header the call
is void, so the operation listener supplies its terminal public result. Each
callback makes only its matching callback-local `GetLobbyMemberDataCopy` read,
then both self and other copies are read after bounded pumping. Two official
trials observed successful terminals, symbolic self/other callback targets,
visible/equal private copies, and eventual self/other copies. Callback order and
count remain host-local diagnostics because both updates begin after the shared
gate; the focused strict comparison matched all required facts and cleanup.

`Simple/bidirectional-chat-room-message-delivery` uses public `IChat` only and
is separate from lobby behavior. Both official profiles must be friends with
messages privacy permitting friends. Both public chat listeners register before
readiness; user1 initiates and user2 resolves the shared one-to-one room before
the runner permits one opaque token-derived send in each direction. Callback
reads are callback-local and retain only symbolic room, sender, type, payload,
and size relations. Two clean official trials on 2026-09-14 observed self echoes
but variable callback batching/cardinality and self/other order, so those are
diagnostic rather than strict or cross-host rules. The focused four-host strict
comparison and full behavior suite passed. Token-mismatched prior-room messages
are callback-local diagnostics only and never satisfy a fresh directional
relation. Participant exit is agreed cleanup because public `IChat`
has no room-delete API; all relays and sensitive artifacts are removed.

`Simple/public-lobby-not-joinable-behavior` uses an authorized tagged public,
capacity-two FCM lobby. The creator explicitly completes and verifies
`SetLobbyJoinable(false)` before the joiner makes one marker-filtered ordinary
list request. Two official-only `1.152.11/x64` trials returned a successful empty
list, so the strict contract records no selected candidate and issues no join or
direct-ID fallback. It also requires no member/member-data/send access, creator
sole ownership, terminal cleanup, and post-delete absence. It does not claim an
unobserved join error reason, callback order, or list-exposed branch.

`Simple/public-lobby-string-filtering` creates two temporary public capacity-two
FCM lobbies sequentially. Each begins nonjoinable; user1 configures its public
collision marker under one fixed filter key, verifies its distinct opaque
marker-derived value locally, then explicitly completes `SetLobbyJoinable(true)`.
User2 makes only the target equality-filtered `RequestLobbyList` request and
uses `GetLobbyByIndex` only from its list callback. It privately classifies each
listed candidate before selecting only one matching the equality predicate. The
trace retains no values, IDs, indexes, or candidate counts, only symbolic target
appearance, predicate match, unmatched-candidate presence/exclusion, selected
join, two-member/non-self-owner, and cleanup relations. Eventual list retries
remain diagnostics. Both lanes strictly require target appearance/match,
correct selected join, membership, and cleanup. Stable official GOG additionally
requires unmatched exclusion; UniverseLAN intentionally permits an unmatched
candidate in the public result as diagnostic context only. This is not permission
for malformed filters or wrong-target selection/join.

`Simple/public-lobby-numerical-filtering` passed its first x64 `1.152.11`
two-lane comparison on 2026-09-16 in 9.76 seconds. It uses the same safe sequential
nonjoinable-to-joinable public FCM lifecycle, with fixed distinct numeric lobby
properties and one shared token-derived run marker. User2 combines
`AddRequestLobbyListNumericalFilter(..., LOBBY_COMPARISON_TYPE_EQUAL)` with the
run-marker filter, classifies only callback-local candidates, and requires the
run-owned numerical nonmatch to be absent before target-only selection/join plus
public two-member/non-self-owner and cleanup relations. Retry and the retained
unmatched boolean are excluded from cross-lane equality, but each lane must prove
the absence relation. Numeric values, markers, IDs, counts, indexes, timestamps,
and runtime data are never retained.

`Simple/custom-networking-loopback-roundtrip-close` is currently an official-only
characterization probe, not a registered strict comparison. It uses public
`ICustomNetworking` against a runner-owned ephemeral loopback WebSocket endpoint
that echoes opaque binary frames only. Two official `1.152.11/x64` trials signed
in both profiles but each `OpenConnection` terminal failed. A later symbolic
URL-form diagnostic observed both valid WebSocket forms fail asynchronously with
`connection-failure` and no synchronous API error; the omitted-scheme diagnostic
reported synchronous `invalid-argument` without a bounded terminal callback. No
send, callback-local peek/read, or close fact was established. The endpoint
URL/port, connection IDs, payload bytes/lengths, credentials, timestamps,
controls, and runtime output are not retained. Do not add a strict UniverseLAN
comparison until successful official open/roundtrip/close observations repeat.

## How To Read A Result

Each scenario runs two synchronized lanes: UniverseLAN server plus two
UniverseLAN hosts, and two official-GOG hosts using the same profiles. Reports
compare normalized public traces. Opaque IDs, public collision-marker values,
timestamps, and other server-assigned values are converted to local symbolic
relationships.

`exact-equality` means the required normalized facts matched. An
`accepted-difference` is an intentionally narrow, documented exception that
still passes. A `candidate difference` remains a strict mismatch; it is not
accepted merely because it has been characterized. Current records include the
accepted GOG-service-state pair, accepted `IFriends` peer persona-state pair,
accepted faster UniverseLAN lobby convergence, and matched direct-chat and
Advanced multiple-lobby baselines.

Per-interface callback order is meaningful where a scenario says it is. Across
hosts or independent interfaces, only documented causal gates are compared;
elapsed timing and eventual-list retry counts are bounded diagnostics, not a
comparison rule.

`Simple/friends-peer-information-retrieval` uses only public `IFriends` calls.
Both hosts install `GlobalPersonaDataChangedListener` before one-time private
peer-ID relays and call `RequestUserInformation(peer, AVATAR_TYPE_NONE,
listener)`. `AVATAR_TYPE_NONE` does not assert absent avatar-related callbacks
because default avatar criteria can still apply. It retains no raw ID, persona
text, avatar data, count, status text, timestamp, credential, runtime output,
or relay artifact. Successful paths remove their private run root; failures
retain only sanitized symbolic traces and reports.
Its sole accepted difference is the observed same-profile persona-state pair
`GOG offline` versus `UniverseLAN online`, consistent with the documented
service-state environment. This is an accepted beneficial environmental
difference, not an SDK guarantee; terminal, availability, name, callback-peer,
and all other required facts remain strict. Requested-peer listener variation
remains diagnostic only.

## Authoring And Validation

Author one focused Simple scenario at a time, characterize the official lane,
declare required/permitted/failing records and normalization rules in its
manifest and coverage entry, then add a strict contract only for stable public
facts. Advanced scenarios require characterized Simple prerequisites.

Temporary lobby and chat scenarios have special cleanup assumptions. Public
lobbies use a runner-generated collision marker, which is not confidential
because public lobby data can be listed and read. They are created nonjoinable,
tagged/configured, then explicitly made joinable and observed before discovery;
all hosts must prove cleanup acknowledgements.
`Simple/public-lobby-owner-close-lifecycle` additionally isolates the token per
lane, waits for the joiner's public global listeners before the creator's normal
leave, and redacts controls, configuration, and runtime output from retained
artifacts. `LeaveLobby` generically documents member notifications, while the
topology documentation discusses owner disconnection; neither header guarantees
the observed narrow normal-FCM-close callback absence. Two official
characterizations observed joiner `lobby-closed` and subsequent tagged-list
absence, with no targeted prior-owner member-state callback. UniverseLAN matches
those empirical facts. The probe settles after all close/list pumps before
finalizing callback presence or absence; sequence order remains diagnostic, but
an additional non-close target leave reason fails. Creator cleanup is acknowledged
only after a matching terminal callback or a safe bounded retry confirms it.
`Simple/public-lobby-owner-ownership-transition` uses the ownership-transition
topology rather than FCM-close. After a filtered join, the joiner arms public
member-state and owner-change listeners, verifies the two-member prior-owner
snapshot, and waits for the creator's local `user-left` callback. Stable
official observations require the prior owner left, ownership changed to the
joiner, an owner-only cache, and successful token-derived owner-data update.
The joiner then confirms its own terminal leave and a token-filtered empty list;
the former owner remains alive until that probe completes. Cross-listener
callback order and list retry count are retained only as diagnostics. Both
cleanup acknowledgements require confirmed terminal leaves.
The public SDK has no chat-room delete API: chat participants exit after their
bounded callback contracts, and that bounded host exit is the agreed cleanup.
`Simple/public-lobby-full-join-failure` uses an authorized temporary public FCM
lobby with an explicit single-member limit. The creator makes it joinable only
after writing its public collision marker and observing the explicit public
state. The joiner performs one filtered full-lobby list request and exactly one
`JoinLobby` call. Two official-only trials observed terminal `full` with no
entry. Its joiner uses only list, lobby-data retrieval, and public state calls;
it never sends a lobby message or uses member/member-data APIs. Creator cleanup
requires a terminal local leave; the nonmember joiner finishes after a stable
post-empty tagged-list absence probe.

Details, diagnostics, artifact handling, and the required validation checklist
are in [DEVELOPER_GUIDE.md](DEVELOPER_GUIDE.md) and
[TODO_PROGRESS.md](TODO_PROGRESS.md).
