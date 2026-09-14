# Galaxy BehaviourTests Plan

## Purpose

BehaviourTests are the third test suite, alongside UnitTests and SystemTests.
They compare **observable Galaxy SDK behavior** from the public headers under
`Source/DLLs/<version>/galaxy/` between the authoritative official GOG Galaxy
runtime and UniverseLAN.

The suite must not inspect UniverseLAN internals, server state, generated data
files, or implementation-only protocol details as assertions. A test may only
observe SDK calls, return values, callback payloads, state queries, and
callback/event timing relationships available to a client using the SDK.

## Required Topology

Each behavior scenario has two synchronized lanes:

| Lane | Processes |
| --- | --- |
| UniverseLAN | Selected UniverseLAN server, two UniverseLAN DLL hosts, and two configured credential profiles. |
| Official GOG | Two hosts linked to and run with the matching official Galaxy SDK runtime, using the same two credential profiles. |

The two lanes execute the same scenario contract. The orchestrator captures
their observable traces, normalizes server-assigned values, then compares the
UniverseLAN trace to the official-GOG trace. Official GOG behavior is the
authority; a mismatch is a BehaviourTest failure unless a scenario explicitly
defines an SDK-version-supported equivalence rule. A separately invoked
characterization diagnostic may collect additional public observations before a
contract is defined; it is not a CTest comparison and never decides lane
equality.

## Layout

Planned source layout:

```text
Source/BehaviourTests/
  CMakeLists.txt
  Common/                 # Public-observation records, normalization, comparison
  Runner/                 # Dual-lane process/config/runtime orchestration
  Host/                   # Header-only SDK behavior probes, no product internals
  Scenarios/
    Simple/               # One focused behavior contract per scenario
    Advanced/             # Combined/multi-interface contracts
  README.md                # Entry point and quick-start
  BEHAVIOUR_TEST_PLAN.md
  DEVELOPER_GUIDE.md
  COVERAGE.md
  TODO_PROGRESS.md         # Completed work and remaining validation
```

The implementation may reuse proven SystemTests concepts such as isolated run
roots, bounded child lifetimes, CTest resource locks, manifest validation, and
the event-file protocol. It must not couple a behavior assertion to
   `SystemTests` host code or UniverseLAN implementation headers. Private runner
   control/event files are orchestration only, not a product observation source.

## Trace And Comparison Model

Hosts emit structured, machine-readable observation records. Each record has a
scenario role, operation name, phase, observable result, and public callback or
state payload. The comparator receives one trace per lane.

Comparison rules:

- Compare SDK-visible result enums, booleans, strings, byte lengths/content,
  member counts, callback categories, and state transitions exactly unless a
  scenario declares a narrow equivalence rule.
- Normalize opaque Galaxy IDs, lobby IDs, room IDs, message IDs, and generated
  timestamps to role/operation-local symbols. Preserve validity, ID type,
  equality/inequality, and cross-callback identity relationships.
- Compare unordered collections as normalized sets when the SDK does not
  guarantee enumeration order.
- Do not compare elapsed timing except for bounded liveness/retry limits. For a
  Simple scenario, preserve and compare callback/event order within the one
  logical SDK interface being tested. Across independent interfaces or hosts,
  compare only scenario-defined causal constraints rather than imposing a
  global total order. Each scenario documents which callbacks are required,
  permitted, ignored, or failures and why.
- Never discard an unexpected callback solely to make traces match. Record it
  and fail unless it is explicitly classified as permitted background behavior.
- Retain raw lane traces and the normalized comparison report on every failure.
- Characterization diagnostics retain raw and normalized lane reports on a
  successful collection too. They record observations without asserting a
  total callback order or cross-lane equality; promote only stable, documented
  observations to a contract test.

## Runtime And Credential Boundaries

- UniverseLAN hosts use the same credential profile tokens and SDK call paths
  as the official-GOG hosts. UniverseLAN may accept those credentials locally;
  credentials are never emitted in traces, command lines, manifests, or logs.
- Official-GOG hosts require the matching official import library/runtime,
  authenticated GOG environment, network access, and the two ignored local
  credential profiles. Direct one-to-one chat additionally requires the
  approved profiles to be friends with direct-message privacy permitting
  friends. Peer-information retrieval has no friendship or direct-message
  privacy precondition; these are external test-environment preconditions, not
  product root-cause claims.
- Every lane gets private working/configuration directories. The official lane
  must also isolate mutable SDK data as far as official-runtime requirements
  permit.
- Scenarios that mutate persistent official account, social, cloud, or public
  lobby state require a cleanup contract and must be opt-in until confirmed safe
  for the supplied accounts/application.

## Behavior Index

Simple scenarios test one narrow public contract at a time. Advanced scenarios
combine already-characterized Simple contracts.

| Interface | Simple behavior index | Advanced follow-up |
| --- | --- | --- |
| Initialization / `IUser` | Init outcome, sign-in terminal behavior, `SignedIn`, `IsLoggedOn`, self ID validity/type, persona availability, and consecutive `GetSessionID()` equality. | Reinitialization, sign-out, connection loss/recovery. |
| `IMatchmaking` | Create/list/join public lobby, nonjoinable public-list behavior, full-lobby join failure, operation result, owner/member relationships, basic lobby data, owner-close lifecycle, ownership-transition characterization, and bidirectional lobby-message delivery. | Multiple concurrent memberships, lobby-message isolation, owner-close comparison, and ownership-transition comparison are implemented; other filters and failure paths remain. |
| `INetworking` | Reliable P2P listener-mode scheduling and callback-local non-consuming peek relations. Three clean official 2026-09-14 trials established the exact accepted environmental pair for current members: scheduled send with a non-target callback and no expected-channel delivery/peek versus UniverseLAN expected-channel delivery and two peeks. A separate two-trial post-leave probe observed scheduled sends but zero callbacks/peeks for the alive former member in both official and UniverseLAN lanes. | Three-peer routing, channel behavior, unreliable packets, disconnect/NAT/server-host behavior. |
| `IChat` | One-to-one room request, room identity reuse, message send terminal result, remote message content/sender relationship. | History/pagination, membership lifecycle, read state, denial/failure behavior. |
| `IFriends` | Persona information retrieval, persona state, rich-presence set/get callback behavior, game invitations where official accounts permit it. | Friend relationships, invitation/acceptance flows, persistence, richer presence state. |
| `IStats` | Retrieve/store operation outcomes, a dedicated test stat/achievement value, post-store public read. | Cross-process durability, reset/failure handling, ordering with presence/user data. |
| `IStorage` | Local write/read, share/download operation result, metadata/content relationships. | Policy/failure paths, timestamps, invalid IDs, multi-account sharing. |
| `ICloudStorage` | Put/list/get/metadata callback behavior where the official SDK supports it. | Conflict, quota, synchronization, notification, deletion behavior. |
| `ICustomNetworking` | Official-only loopback open/roundtrip/close characterization is implemented. Two 2026-09-14 official trials signed in but observed open failure for both profiles, so no send/receive/close contract is enabled. | Successful endpoint characterization, connection failure, concurrency, close/error races. |
| `IApps` | DLC installed/owned result and language API behavior for the configured application. | DLC state changes and failure paths. |
| `ITelemetry` | Public send result/callback behavior only if the official environment accepts deterministic telemetry testing. | Parameter, sampling, visit ID, failure behavior. |
| `IUtils` | Overlay and post-auth service connection state observable behavior. | Notifications, images/avatars, auth-loss/reconnect behavior. |

The initial implementation targets `1.152.11`: initialization/sign-in, self
identity and state, then a two-host simple matchmaking/P2P contract. No
mutating GOG social, cloud, achievement, or public-lobby scenario will be
enabled before account and application isolation rules are agreed.

Every behavior lobby that a peer must join is created nonjoinable, configured
and tagged with a collision marker, then explicitly made joinable and observed
before discovery. Public lobby markers are not confidential because public lobby
data can be listed and read; they are never printed. These are public
`IMatchmaking` setup conditions, not inferred defaults.

## Development Phases

1. Confirm the environment, account, application, network, cleanup, and
   comparison-policy decisions listed below.
2. Add `BUILD_UNIVERSELAN_BEHAVIOUR_TESTS`, credentials/runtime preflight, and
   separate version/architecture-specific UniverseLAN and official-GOG host
   targets.
3. Build the runner, structured public-observation protocol, normalized ID
   binder, trace artifact retention, and CTest registration. Start opt-in until
   a real official-GOG smoke run succeeds reliably.
4. Implement `Simple/initialize-and-sign-in`, first as trace capture, then as
   a comparator-backed behavior test for a selected supported SDK version.
5. Add self-state and two-host simple scenarios one at a time, extending the
   normalizer only for observed opaque values and documented ordering variance.
6. Add Advanced scenarios only after their underlying Simple contracts are
   characterized and stable.
7. Maintain `COVERAGE.md`, `TODO_PROGRESS.md`, the developer guide, and a
   behavior-difference log that distinguishes accepted differences, candidates,
   confirmed incompatibilities, and uncontrolled official-environment variation.

## Confirmed Decisions

- The first implementation targets SDK `1.152.11`; expand the version matrix
  only after the first official comparison is stable.
- Existing ignored local configuration supplies the approved GOG application and
  two credential profiles.
- UniverseLAN and official-GOG lanes run concurrently by default. A sequential
  lane option remains available for account/runtime contention.
- Official-GOG BehaviourTests are opt-in CTest tests under a distinct label and
  preflight their credentials and matching runtime artifacts.
- Before each scenario, characterize the authoritative official callback trace.
  Each scenario documents its required, permitted, ignored, and failing callback
  categories; there is no suite-wide callback allowlist.
- Initial scenarios are non-mutating: initialization, sign-in, and public state
  observation only. Later mutable scenarios must create a known test state and
  reset or delete it before and after each lane. Achievements and stats use an
  explicit reset/setup contract before their comparison scenarios are enabled.
- Tagged temporary public lobbies and temporary chat rooms/messages are now
  authorized. Each scenario must use a runner-generated collision-resistant
  token, prove its own cleanup, and avoid achievements, stats, files, cloud,
  telemetry, and friendship mutation.
- For the authorized chat scenarios, both participating hosts exit after their
  bounded public callback contract. Host exit is the agreed cleanup mechanism
  for the temporary chat room/message lifecycle; tests still never copy message
  content or peer IDs into traces, reports, arguments, or logs.
- Direct one-to-one official chat is run only when the approved profiles are
  friends and messaging privacy permits friends. This qualifies the external
  official test environment and does not classify the setting as a UniverseLAN
  defect cause or a behavior-comparison exception.
- `Simple/chat-room-message-delivery` uses four concurrent hosts: one sender and
  one receiver in each lane. A receiver installs its global public listener
  before readiness. Each host relays its self ID once to the runner; the runner
  consumes and deletes it, then writes each peer ID once for the other host.
  Sender and receiver consume and delete their peer/token relays. Retained chat
  failures keep only symbolic traces and reports, never runtime output, config,
   controls, IDs, room/message IDs, or token contents.
- `Simple/friends-peer-information-retrieval` uses two concurrent hosts per
  lane. After sign-in, each installs public `GlobalPersonaDataChangedListener`
  before writing its self ID to a one-time private relay. Only after both
  listener-registration gates arrive does the runner consume/delete the self
  relays and write/delete one peer relay for each host. Each host calls only
  `IFriends::RequestUserInformation(peer, AVATAR_TYPE_NONE, listener)` and the
  specified public availability/name-copy/persona-state queries. Its listener
  records only the requested peer. `AVATAR_TYPE_NONE` does not assert absent
  avatar activity because default avatar criteria can apply. It never creates
  friendships or mutates social data. Successful private roots are removed;
  retained failures redact relays, controls, configuration, and runtime output.
- `Simple/public-lobby-create-list-join-leave` uses the approved tagged temporary
  lobby only. The runner generates its collision marker inside the private run
  root and puts it only in one control file per host. The marker is never in a
  manifest, host argument, trace, log, normalized report, console output, or
  documentation. Public lobby data can expose it, so it is a collision marker,
  not confidential data. The creator writes metadata and observes explicit
  joinability before signalling ready. The runner relays only
   symbolic event-file gates to the joiner and requires cleanup acknowledgement
    before forcibly stopping a failed host.
- `Simple/public-lobby-full-join-failure` uses the same authorized temporary
  public FCM setup with an explicit single-member limit and no inferred defaults.
  The joiner requests full lobbies through a marker filter, retrieves only public
  lobby data/state, and makes exactly one asynchronous join attempt. Official
  characterization must establish its terminal enum before the strict contract.
  The rejected joiner never calls member-data, member-enumeration, or lobby-message
   APIs. The creator verifies sole ownership/membership after the terminal failure,
   leaves with a fresh cleanup deadline, and acknowledges only its terminal local
   leave; the joiner completes after the post-empty filtered-list absence probe.
- `Simple/public-lobby-not-joinable-behavior` uses a distinct authorized temporary
  public capacity-two FCM lobby. The creator sets its marker and explicitly calls
  `SetLobbyJoinable(false)`, then verifies public type, capacity, joinability, and
  marker visibility before releasing the joiner. Two official-only trials observed
  a successful filtered list with no candidate, so the strict contract issues no
  join and makes no direct-ID fallback. It requires no member/member-data/send
  access, sole creator ownership, terminal creator leave under a fresh deadline,
  and successful tagged-list absence after deletion. It does not infer behavior
  for a list-exposed nonjoinable lobby, direct join, callback order, or an error
  reason that official GOG did not expose.
- `Simple/public-lobby-owner-ownership-transition` uses a distinct tagged public
  `LOBBY_TOPOLOGY_TYPE_FCM_OWNERSHIP_TRANSITION` lobby in each lane. It explicitly
  sets and observes joinable true and capacity two before the filtered joiner is
  released. The joiner validates the two-member non-self-owner snapshot, arms
  public global member-state and owner-change listeners, and only then releases
  the creator's normal leave. The former owner remains alive until the joiner's
  matching terminal leave and token-filtered post-empty absence probe. Tokens,
  token-derived data, raw IDs, controls, relays, and runtime output are not
   retained. Global listener-class ordering and list retries are diagnostics only.

- `Simple/reliable-p2p-listener-peek` creates the authorized public FCM lobby
  nonjoinable, configures capacity and its public collision marker, then calls
  and observes `SetLobbyJoinable(true)` before discovery. After the joiner arms
  `GlobalNetworkingListener`, the creator performs ten bounded `ProcessData`
  settling pumps before scheduling the reliable send. For each expected-channel
  callback, the joiner makes exactly two non-consuming `PeekP2PPacket` calls;
  listener-mode code never polls, reads, or pops packets. Three clean official
  trials observed exactly one non-target callback and no expected-channel peek;
  the focused comparison observed UniverseLAN expected-channel delivery and two
  equivalent peeks. The manifest accepts only that exact pair. Both leaves use a
  fresh bounded deadline and continue `ProcessData` pumping after the observation
  window; a host clears joined state or acknowledges cleanup only after its own
    matching terminal leave callback.
- `Simple/reliable-p2p-after-lobby-leave` uses the same safe FCM setup but
  changes only the recipient relation. User2 arms `GlobalNetworkingListener`,
  confirms local `LeaveLobby`, and remains alive. User1 arms
  `GlobalLobbyMemberStateListener`, records the former member's `left`, settles
  public sole-owner membership, then schedules one reliable payload to the saved
  former valid ID. Two official characterizations and the focused comparison
  observed scheduling with no callback or peek at the former member. This is an
  exact matched baseline, not a delivery guarantee or an accepted LAN benefit.
- `Simple/bidirectional-reliable-p2p-listener-peek` uses the same safe temporary
  public FCM lobby sequence with two accounts per lane. Both hosts construct
  `GlobalNetworkingListener`, query the other current member only through public
  lobby membership, and complete ten bounded settling pumps before the runner
  releases one synchronized exchange. `user1` sends exactly one distinct opaque
  token-derived reliable payload on channel 73 and `user2` does the same on channel
  74. Each expected-channel callback makes exactly two callback-local peeks; no
  listener-mode polling, reading, or popping is permitted. Three official trials
  scheduled both sends but observed one non-target callback, no expected-channel
  callback, and no peeks in both directions. The manifest accepts only each exact
  direction's official no-delivery versus UniverseLAN delivery/two-peek pair. All
   other peer/lobby/channel/payload, scheduling, destruction, and fresh-deadline
   cleanup relations remain strict without assuming symmetry.
- `Simple/bidirectional-unreliable-p2p-listener-peek` reuses the same safe
  temporary public FCM lobby sequence with two accounts per lane. Both hosts
  construct `GlobalNetworkingListener`, query the other current member only
  through public lobby membership, and complete ten bounded settling pumps before
  the runner releases one synchronized exchange. `user1` sends exactly one
  distinct opaque token-derived `P2P_SEND_UNRELIABLE` payload on channel 73 and
  `user2` does the same on channel 74. Each expected-channel callback makes
  exactly two callback-local peeks; no listener-mode polling, reading, or
  popping is permitted. Three official trials scheduled both sends but observed
  one non-target callback, no expected-channel callback, and no peeks in both
  directions. The manifest accepts only each exact direction's official
  no-delivery versus UniverseLAN delivery/two-peek pair. `P2P_SEND_UNRELIABLE`
  is UDP-like, and scheduled does not mean delivered; all other peer/lobby,
  channel/payload, scheduling, destruction, and fresh-deadline cleanup relations
  remain strict without assuming reliable/unreliable equivalence or symmetry.
- `Simple/bidirectional-lobby-message-delivery` creates one authorized public
  FCM lobby initially nonjoinable, writes its public collision marker and
  capacity-two setting, then explicitly completes and observes
  `SetLobbyJoinable(true)` before discovery. Both members arm public global
  lobby-message listeners before a shared exchange gate. Each schedules exactly
  one distinct opaque token-derived binary payload and calls `GetLobbyMessage`
  only from that callback. Two official `1.152.11/x64` trials observed exactly
  two callback-local messages per host, one self and one other, with valid
  shared-lobby/sender/payload/size relations and `self, other` local order. The
   strict comparison requires all cardinality and directional relationships but
   retains independent-sender callback order diagnostically: the focused
   UniverseLAN joiner observed `other, self` while matching every strict fact.
- `Simple/bidirectional-lobby-member-data-propagation` uses the same safe public
  FCM setup and public collision marker, with explicit observed joinability
  before discovery. After both joined-lobby two-member states are established,
  both hosts arm `GlobalLobbyDataListener` before the runner releases the
  exchange. Each member makes one `SetLobbyMemberData` call on its own fixed
  public key with a distinct opaque token-derived value. The selected header
  makes this setter void, so `ILobbyMemberDataUpdateListener` is the public
  terminal result. Listener callbacks make only matching callback-local
  `GetLobbyMemberDataCopy` reads; each host then performs bounded settled self
  and other copies. Two official trials established successful terminals,
  symbolic self/other callback targets, changed-data visibility/private equality,
  and settled copies. Callback count and local target order remain diagnostics,
  not cross-host or sender-order rules.

## Acceptance Criteria

- A BehaviorTest compiles against the selected Galaxy header and uses no
  UniverseLAN implementation API in its host assertions.
- It launches both two-host lanes with bounded lifetimes and retains complete
  raw/normalized traces on mismatch.
- It compares public behavior without raw equality requirements for
  server-assigned opaque identifiers.
- It never records credentials or secrets.
- It is repeatable within the agreed official-GOG environment and its cleanup
  obligations are fulfilled.
- A new behavior scenario updates the behavior coverage register and documents
  its normalization/ordering rules.

## Implementation Status

- Phase 1 decisions are confirmed above for the x64 `1.152.11` initial probe.
- Phases 2 and 3 are implemented for the framework: separate official and
  UniverseLAN hosts, isolated runner roots, trace comparison, artifact staging,
  preflight, and opt-in CTest registration.
- Phase 4 implements the non-mutating `Simple/initialize-and-sign-in`,
  `Simple/session-id-repeatability`, and `Simple/gog-services-state` contracts.
  Session repeatability uses the same four-host concurrent topology and credential
  sign-in path. After successful `IAuthListener::OnAuthSuccess` and before another
  `ProcessData` call, each host calls only `IUser::GetSessionID()` twice back-to-back
  and records only their boolean equality relation. It does not record a raw session
  ID, zero/nonzero classification, user ID, persona, timestamp, or internals; the
  comparator requires successful sign-in and exact same-profile lane equality without
  assuming either boolean value. The service-state contract uses the same four-host
  concurrent topology and credential sign-in path, then queries only public
  `IUtils::GetGogServicesConnectionState()` immediately after `OnAuthSuccess`
   and before another `ProcessData` call. Its fifth record requires exact
   same-profile symbolic-state equality except for the manifest-declared accepted
   pair `GOG undefined` and `UniverseLAN connected`, observed because the official
   lane runs without the GOG Galaxy service while UniverseLAN supplies its LAN
   service. The report marks that pair `accepted-difference` rather than
   `exact-equality`; every other state or record mismatch fails. No service-state
   listener or ordering rule is registered. Their exact record and opaque-ID rules
   are in [`COVERAGE.md`](COVERAGE.md).
- An explicit `--characterize-gog-services-state` runner mode extends the
  latter investigation without changing its contract. It uses the same
  concurrent four-host/two-profile topology and credential sign-in path, then
  captures immediate, one-`ProcessData`, and ten-pump settled public state
  queries plus phased global service-state-listener events. It retains the
  successful run root and reports no match/fail comparison.
- Later phases remain unimplemented. In particular no social, stats, storage,
  cloud, telemetry, or other unapproved mutating official-GOG scenario is
  enabled. The authorized temporary lobby and chat scenarios below are the only
  current exceptions.
- `Simple/public-lobby-create-list-join-leave` is implemented under the existing
  opt-in GOG label. It is the exception for the approved temporary lobby: its
  normal path leaves joiner then creator, and its failure path uses private
  abort-control and cleanup-ack event files with bounded waiting before process
   termination. It does not assert member callback order. The 2026-09-13 live
  official four-host run matched its normalized public facts and acknowledged
   cleanup in every host. The observed official two-attempt versus UniverseLAN
   one-attempt list convergence is an accepted beneficial variation; each lane
   remains required to converge within the documented bound, without equating
    eventual-consistency timing across lanes.

- `Simple/public-lobby-owner-close-lifecycle` first ran twice as an
  official-GOG-only diagnostic, then as a strict four-host comparison. The
  `LeaveLobby` header generically documents notifications to other members; its
  FCM topology description concerns owner *disconnection*, so the observed lack
  of a targeted prior-owner notification in this normal-close path is empirical,
  not a header guarantee. The joiner arms global public member-state and
  lobby-left listeners before a causal release of the creator. Both official
  runs observed `lobby-closed`, tagged-list absence, and no targeted prior-owner
  member-state callback. The probe finalizes that absence only after post-close
  listing and a bounded final settling window. Target-lobby sequence and
  cross-listener ordering remain diagnostic, while any target global leave
  reason other than `lobby-closed` fails. UniverseLAN now matches the empirical
  absence by sending surviving close members only the synthetic close
  notification. Creator cleanup acknowledgement requires a matching terminal
  callback, or a safe bounded retry confirmed by its terminal callback. Every
   host acknowledged cleanup; retained artifacts remove controls, configuration,
   relays, and runtime output.

- `Simple/public-lobby-owner-ownership-transition` ran twice as an official-GOG-
  only diagnostic before its strict four-host baseline on 2026-09-14. Both
  official trials observed the creator local `user-left`, joiner prior-owner
  `LEFT`, owner-change-to-self, owner-only member and owner cache, successful
  token-derived promoted-owner data update/copy, joiner local `user-left`, and
  post-empty tagged-list absence. The two global-listener classes delivered the
  same local sequence in those trials, but this is not a public ordering promise
  and remains retained diagnostic context. The initial official list took one and
  two attempts respectively, so retry count is likewise bounded diagnostic data.
  The focused strict comparison matched every stable relation in UniverseLAN and
  acknowledged cleanup for all four hosts.

- `Simple/public-lobby-data-propagation` uses the same temporary lobby harness.
  After the joiner joins and its public `GlobalLobbyDataListener` is armed, the
  owner sets a separate fixed key to a nonempty runner collision-marker-derived
  value. The joiner validates only through public `GetLobbyDataCopy`. Official
  `1.152.11/x64` characterization confirmed owner update success, joined-lobby
  notification availability, invalid symbolic `memberID` for lobby-level data,
  same-callback and eventual copy visibility, and no duplicate notification in
  that run. Duplicate count and callback-gate discovery order are diagnostic
   only. The comparator preserves per-host `IMatchmaking` order and compares only
   observer-before-update and joiner-before-cleanup causal gates across hosts.
   The coverage and difference registers record a matched live baseline; its
    retained register did not capture a run date. Callback multiplicity and
     callback-gate discovery order remain diagnostic rather than equality facts.

- `Simple/public-lobby-string-filtering` creates two distinct temporary public
  capacity-two FCM lobbies sequentially. Each stays nonjoinable while the creator
  sets a value derived from the private runner marker under one fixed public key,
  verifies the local copy, and only then completes and observes joinability. The
  two values are distinct but are never retained. User2 applies one public string
  equality filter for the target value on each bounded diagnostic request and
  calls `GetLobbyByIndex` only in `ILobbyListListener::OnLobbyList`. It requests
   public data for each callback-local candidate, retains symbolic target
   appearance, predicate-match, and unmatched-candidate presence/exclusion facts
   without a value, ID, index, or candidate count, then selects and joins only a
   matching target and verifies public two-member/non-self-owner state. Official
   characterization established stable target-only equality-filter evidence on
   2026-09-14. Retry is diagnostic; both lanes strictly require target appearance,
   predicate match, correct selected join, and lifecycle cleanup after stability.
   Official GOG's unmatched exclusion remains strict. UniverseLAN intentionally
   permits an unmatched public candidate as a diagnostic relaxed-filter superset;
   that narrow policy never permits a malformed filter or an unmatched selection
    or join.

- `Simple/custom-networking-loopback-roundtrip-close` uses public
  `ICustomNetworking` only. The runner owns an ephemeral loopback WebSocket
  endpoint that returns opaque binary frames unchanged; it is transport setup,
  never behavior evidence. A successful host path would open one connection,
  send one private NUL-containing payload, validate callback-local availability,
  two non-consuming peeks and one read, then close. Two official-only
  `1.152.11/x64` trials on 2026-09-14 signed both profiles in but observed open
  failure for both profiles, leaving send/data/close uncharacterized. No strict
  UniverseLAN CTest is registered and no product cause or comparison rule is
  inferred until successful official observations are stable. Connection IDs,
  endpoint URL/port, bytes/lengths, credentials, timestamps, controls, and
  runtime output are not retained.

- `Simple/public-lobby-not-joinable-behavior` ran twice as an official-GOG-only
  characterization before its strict four-host baseline on 2026-09-14. Both
  official trials observed the same public branch: `SetLobbyJoinable(false)`
  completed and was publicly visible with the public/capacity-two/tag setup; one
  marker-filtered ordinary list returned success with no selected candidate; no
  join operation was issued; the creator remained sole owner/member; and its
  terminal leave preceded a successful post-delete absence probe. UniverseLAN
  initially exposed the lobby, so normal client list filtering now excludes
  nonjoinable lobbies. The strict contract promotes no broader behavior: no
   direct-ID join, error reason, callback order, or list-exposed branch is assumed.

- `Simple/bidirectional-lobby-message-delivery` ran twice as an official-GOG-only
  diagnostic and then as a focused strict four-host comparison on 2026-09-14.
  Official GOG scheduled one send per host and delivered one callback-local
  symbolic self message and one other message to each host, with all shared-lobby,
  sender, payload, size, and cleanup relations valid. Both official trials had
  local `self, other` callback order. UniverseLAN matched all strict facts; its
  joiner retained `other, self`. That order is visible diagnostic context, not a
  mismatch, because the independent sends have no cross-host or sender-global
   ordering guarantee.

- `Simple/bidirectional-reliable-p2p-listener-peek` ran three times as an
  official-GOG-only diagnostic before its focused strict four-host comparison on
  2026-09-14. Every direction in every official trial scheduled once after both
  listener instances settled, then received one symbolic non-target callback and
  no expected-channel callback or callback-local peeks. The strict comparator has
  a separate narrow accepted no-delivery versus delivery/two-peek pair for each
  direction. It preserves all other setup, current-public-peer, channel/payload,
   listener-destruction, and terminal-cleanup checks, and does not infer directional
   symmetry from the shared exchange.

- `Simple/bidirectional-unreliable-p2p-listener-peek` ran three times as an
  official-GOG-only diagnostic before its focused strict four-host comparison on
  2026-09-14. Every direction in every official trial scheduled once after both
  listener instances settled, then received one symbolic non-target callback and
  no expected-channel callback or callback-local peeks. The strict comparator has
  a separate narrow accepted no-delivery versus delivery/two-peek pair for each
  direction. It preserves all other setup, current-public-peer, channel/payload,
  listener-destruction, and terminal-cleanup checks, and does not infer reliable
  equivalence or directional symmetry from the shared exchange.

- `Advanced/multiple-lobby-membership-and-message-isolation` is the first
  Advanced contract. Its official-GOG-only 2026-09-14 characterization observed
  support for adjacent `CreateLobby` and adjacent `JoinLobby` requests before
  `ProcessData`, two simultaneous memberships, explicit public/joinable/capacity
  setup, and independent `L0`/`L1` message delivery. The strict four-host run
  matched UniverseLAN after a first focused strict mismatch exposed that the
  official joiner callback sequence can be either `L0`, `L1` or `L1`, `L0`.
  The test retains that order but does not compare the unstable independent-
  lobby sequence; stable role-local `IMatchmaking` operation order is strict and
  no cross-host order is imposed. Header contract and empirical
  result are distinct: `ILobbyMessageListener`/`GetLobbyMessage` provide no
  public message-type field, while public callback, sender, byte payload, and
   lobby relations were empirically observed. It never claims a delete-lobby API;
   both roles leave `L1` then `L0` within the bounded cleanup contract.

- `Simple/chat-room-message-delivery` is implemented as an opt-in x64
  `1.152.11` contract with an explicit characterization mode. It uses only
  public `IChat` interfaces: room-request and send operation listeners plus a
  receiver `GlobalChatRoomMessagesListener` that reads only inside the callback.
  Per-host `IChat` record order is strict; receiver arming is the sole
  cross-host causal gate and sender-terminal/receiver-message callback order is
  deliberately not asserted. The 2026-09-14 official-only characterization
  followed by the strict four-host comparison matched one successful symbolic
  room request, send, and callback-local receive path in each lane. The
   friendship/messaging-privacy setting is an external official-environment
   precondition, not an accepted difference or root-cause claim.

- `Simple/bidirectional-chat-room-message-delivery` is implemented as an opt-in
  x64 `1.152.11` public `IChat` contract, independent of all lobby interfaces.
  Both hosts construct `GlobalChatRoomMessagesListener` before readiness and
  exchange only private one-time self-ID peer relays. User1 requests the
  one-to-one room; only after that symbolic room/peer relation succeeds does
  user2 resolve and validate the same public two-member relation. The runner
  then releases exactly one distinct token-derived chat payload per direction.
  Reads occur only inside matching callbacks and retain symbolic shared-room,
  self/other sender, chat-type, token equality, and size-equality relations.
  Two clean official-only trials on 2026-09-14 found self echoes, but callback
  batching/cardinality and self/other local order varied. Token-mismatched
  messages from an already existing one-to-one room are callback-local prior
  message diagnostics and never satisfy the fresh directional relation. Those
  facts remain same-host diagnostics and no cross-host/global order is imposed.
  The focused strict comparison and full portable suite passed after UniverseLAN
  began publishing a new room only after both members were added. Host exit is the agreed cleanup;
  the public SDK has no delete-room API and no deletion claim is made.

- `Simple/friends-peer-information-retrieval` is implemented as an opt-in x64
  `1.152.11` contract. Three clean official-only runs on 2026-09-14 established
  terminal success, requested-peer valid non-self callback identity, available
  information, nonempty copied persona name, symbolic `offline` peer state, and
  ordered requested-peer persona changes `name-avatar`, then `none`, for both
  profiles. A later full run observed terminal `none` without `name-avatar` in
  one official lane, so filtered requested-peer listener events are retained as
  diagnostic context rather than equality-required. No cross-host total order is
  asserted. Retrieval has no friendship or direct-message privacy precondition.
  The focused 2026-09-14 two-lane CTest accepts only the manifest-declared
  observed persona-state pair `GOG offline` and `UniverseLAN online`, consistent
  with the service-state environment where official GOG has no GOG Galaxy service
  while UniverseLAN provides its LAN service. This accepted beneficial
  environmental difference is not an SDK guarantee; terminal success, callback
  identity, availability, copied-name, and every other record remain strict.

See [`DEVELOPER_GUIDE.md`](DEVELOPER_GUIDE.md) for opt-in prerequisites,
security boundaries, lane operation, artifact diagnostics, and the
public-SDK-only host rule. Record characterized differences using
[`BEHAVIOUR_DIFFERENCES.md`](BEHAVIOUR_DIFFERENCES.md), and maintain completed
work and future work in [`TODO_PROGRESS.md`](TODO_PROGRESS.md).
