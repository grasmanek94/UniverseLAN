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
| `IMatchmaking` | Create/list/join public lobby, operation result, owner/member relationships, basic lobby data. | Multiple concurrent memberships and lobby-message isolation are implemented; leave/owner migration/closure, filters, and other failure paths remain. |
| `INetworking` | Reliable P2P packet scheduling, receive callback/poll state, payload/content, sender relationship. | Three-peer routing, channel behavior, unreliable packets, disconnect/NAT/server-host behavior. |
| `IChat` | One-to-one room request, room identity reuse, message send terminal result, remote message content/sender relationship. | History/pagination, membership lifecycle, read state, denial/failure behavior. |
| `IFriends` | Persona information retrieval, persona state, rich-presence set/get callback behavior, game invitations where official accounts permit it. | Friend relationships, invitation/acceptance flows, persistence, richer presence state. |
| `IStats` | Retrieve/store operation outcomes, a dedicated test stat/achievement value, post-store public read. | Cross-process durability, reset/failure handling, ordering with presence/user data. |
| `IStorage` | Local write/read, share/download operation result, metadata/content relationships. | Policy/failure paths, timestamps, invalid IDs, multi-account sharing. |
| `ICloudStorage` | Put/list/get/metadata callback behavior where the official SDK supports it. | Conflict, quota, synchronization, notification, deletion behavior. |
| `ICustomNetworking` | Open, send/receive, close, terminal callback/result behavior against a runner-owned endpoint. | Connection failure, concurrency, close/error races. |
| `IApps` | DLC installed/owned result and language API behavior for the configured application. | DLC state changes and failure paths. |
| `ITelemetry` | Public send result/callback behavior only if the official environment accepts deterministic telemetry testing. | Parameter, sampling, visit ID, failure behavior. |
| `IUtils` | Overlay and post-auth service connection state observable behavior. | Notifications, images/avatars, auth-loss/reconnect behavior. |

The initial implementation targets `1.152.11`: initialization/sign-in, self
identity and state, then a two-host simple matchmaking/P2P contract. No
mutating GOG social, cloud, achievement, or public-lobby scenario will be
enabled before account and application isolation rules are agreed.

Every behavior lobby that a peer must join explicitly configures and observes a
joinable public state and its intended maximum-member capacity before the join
phase. These are public `IMatchmaking` setup conditions, not inferred defaults.

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
  lobby only. The runner generates its token inside the private run root and puts
  it only in one control file per host. The token is never in a manifest, host
  argument, trace, log, normalized report, console output, or documentation.
  The creator writes its metadata before signalling ready. The runner relays only
  symbolic event-file gates to the joiner and requires cleanup acknowledgement
  before forcibly stopping a failed host.

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

- `Simple/public-lobby-data-propagation` uses the same temporary lobby harness.
  After the joiner joins and its public `GlobalLobbyDataListener` is armed, the
  owner sets a separate fixed key to a nonempty runner-private token-derived
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
