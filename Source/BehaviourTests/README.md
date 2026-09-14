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
client credentials. Matching official `Galaxy64.lib`, `Galaxy64.dll`, and
`GalaxyPeer64.dll`, an authenticated official environment, and network access
are also required. Missing prerequisites leave live tests unregistered rather
than making normal builds fail. Direct `IChat` additionally needs approved
official profiles to be friends with direct-message privacy permitting friends.
`IFriends` peer-information retrieval has no friendship or direct-message
privacy precondition. These are external test-environment preconditions, not
product root-cause claims.

`Simple/reliable-p2p-listener-peek` uses an authorized tagged temporary public
FCM lobby. The public tag is a collision marker, not confidential data. The
creator creates it nonjoinable, tags/configures it, then explicitly observes
`SetLobbyJoinable(true)` before discovery. The joiner constructs
`GlobalNetworkingListener` before the runner releases the creator. For each
expected-channel `OnP2PPacketAvailable` callback, it performs two
`PeekP2PPacket` calls, then destroys the listener before `Shutdown`. It never
uses polling, read, or pop APIs in listener mode. Three clean official-only
trials on 2026-09-14 scheduled the post-arm-settled reliable send but observed
one non-target callback and no expected-channel callback or peeks. The focused
four-host comparison observed the exact UniverseLAN delivery/two-peek relation.
The manifest accepts only that `GOG no delivery` versus `UniverseLAN delivery`
pair as a beneficial environmental difference; setup, scheduling, cleanup, and
all other callback relations remain strict.

`Simple/bidirectional-reliable-p2p-listener-peek` uses the same safe public,
capacity-two FCM lobby setup. Both members obtain the other peer only from the
joined lobby's public member queries, construct `GlobalNetworkingListener`, and
complete the bounded post-arm settling window before the runner releases their
synchronized exchange. Each sends one distinct opaque token-derived payload with
`P2P_SEND_RELIABLE`: channel 73 from `user1` to `user2`, and channel 74 in the
reverse direction. Every expected-channel callback makes exactly two
callback-local `PeekP2PPacket` calls; listener mode never polls, reads, or pops.
Three official-only trials on 2026-09-14 scheduled both directions but observed
one non-target callback, no expected-channel callback, and no peeks per host.
The strict contract accepts only that exact per-direction no-delivery relation
against UniverseLAN's matching delivery/two-peek relation. Listener destruction,
peer/lobby/channel/payload relations, scheduling, and fresh-deadline cleanup
remain strict; no raw IDs, bytes, lengths, token, or marker are retained.

`Simple/bidirectional-unreliable-p2p-listener-peek` reuses that public,
initially nonjoinable, capacity-two FCM-lobby and fresh-deadline cleanup path.
Both members derive their peer only from current public lobby membership, arm and
settle `GlobalNetworkingListener`, then send one distinct opaque payload with
`P2P_SEND_UNRELIABLE` on separate non-default channels after the synchronized
release. Each expected-channel callback makes exactly two callback-local,
non-consuming `PeekP2PPacket` calls; listener mode never polls, reads, or pops.
Three clean official-only runs on 2026-09-14 scheduled both directions but each
host observed one non-target callback, no expected-channel callback, and no
peek. The focused four-host comparison observed the exact UniverseLAN
delivery/two-peek relation in both directions. `SendP2PPacket` returning true
means only that its UDP-like packet was scheduled; neither this send type nor
the observed environmental pair guarantees delivery. The manifest accepts only
those independently exact directional pairs. Peer/lobby/channel/payload,
scheduling, listener destruction, and cleanup remain strict; no raw IDs, bytes,
lengths, token, or marker are retained.

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
Advanced multiple-lobby baselines. See the

Per-interface callback order is meaningful where a scenario says it is. Across
hosts or independent interfaces, only documented causal gates are compared;
elapsed timing and eventual-list retry counts are bounded diagnostics, not a

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
