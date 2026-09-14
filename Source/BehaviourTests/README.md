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
