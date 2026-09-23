# NET — fresh Shared baseline review

## Executive summary

**Complete: 59/59 assigned implementation/build inputs read in full; 59 new per-file sidecars written. Incomplete assigned files: none.** Baseline `b30e83872c0006e8240c8b4f565da5351bf10080`; working HEAD `40265aed370464569e873692ef5d53fbdb12679b`. The Shared inputs match the baseline. This is an independent static review; superseded review contents were never consulted.

**13 unique findings: 2 High, 7 Medium, 4 Low; all High confidence from source evidence, none runtime-reproduced.** Locally complete finding sections live in the relevant sidecars; repeated schema/history sections intentionally reuse the same root-cause ID. No Critical finding. No private configuration/credential access, production source changes, builds, Git writes or network experiments.

Principal strengths are explicit wire field initialization, value/shared ownership of decoded data, portable numeric archives, receive-packet cleanup on unwind, correct client rejected-send cleanup, sender substitution in normal relays, and checked history slicing. Principal risks are resource allocation before authentication, uncontained handler exceptions, a vendor timeout event omitted from lifecycle handling, and packet/history/queue limits that do not compose into a bounded service.

**Readiness:** Matching-version trusted-LAN happy paths have coherent layering, but the two High input-boundary defects should be resolved before treating reachable peers as robustly contained. Next priorities are timeout retirement, failed-send ownership and bounded/versioned wire traffic. This is not a claim of Internet-grade identity or transport confidentiality, nor an argument that a public default LAN key is itself an authentication vulnerability.

## Unique finding index

| ID | Severity | Category | Finding | Primary complete section |
|---|---|---|---|---|
| BASE-NET-001 | High | Security | Wire lengths allocate before authentication/payload validation | `Source/Shared/Networking/Networking.hxx.review.MD` |
| BASE-NET-002 | High | Correctness | Rejected file path throws through dispatch and terminates server | `Source/Shared/Networking/Networking.hxx.review.MD` |
| BASE-NET-003 | Medium | Correctness | Vendor timeout-disconnect event is omitted | `Source/Shared/Networking/Networking.cxx.review.MD` |
| BASE-NET-004 | Medium | Memory Safety | Failed single-peer server Send leaks packet ownership | `Source/Shared/Networking/Networking.hxx.review.MD` |
| BASE-NET-005 | Medium | API/ABI | Incompatible SDK schemas share IDs without negotiation | `Source/Shared/Networking/Networking.hxx.review.MD` |
| BASE-NET-006 | Medium | Performance | Unbounded history makes routine snapshots exceed transport cap | `Source/Shared/Lobby.hxx.review.MD` |
| BASE-NET-007 | Medium | Performance | Application packet queues bypass ENet waiting-data budget | `Source/Shared/Networking/Networking.hxx.review.MD` |
| BASE-NET-008 | Medium | Correctness | Failed achievement save clears retry markers | `Source/Shared/IniData.cxx.review.MD` |
| BASE-NET-009 | Medium | Portability | UTF-8 path values use Windows ANSI conversion | `Source/Shared/IniData.cxx.review.MD` |
| BASE-NET-010 | Low | Correctness | Plain-AppData first-run boot/config provisioning is skipped | `Source/Shared/IniData.cxx.review.MD` |
| BASE-NET-011 | Low | Correctness | Identity branches validate the wrong MachineInfo property | `Source/Shared/IniData.cxx.review.MD` |
| BASE-NET-012 | Low | Correctness | DLC parser accepts trailing junk after numeric ID | `Source/Shared/IniData.cxx.review.MD` |
| BASE-NET-013 | Low | Concurrency | Cleanup/pop interleaving delivers disconnect twice | `Source/Shared/Networking/Networking.cxx.review.MD` |

Category totals: Security 1; Correctness 6; Memory Safety 1; API/ABI 1; Performance 2; Portability 1; Concurrency 1. Confidence is not execution: reproduction conditions and verification procedures in sidecars are proposed, not results.

## Exact assigned coverage

Inventory: **9 `.cxx`, 49 `.hxx`, 1 `.txt`, 0 `.cmake` = 59**. Every row is full-read coverage including comments, constructors, serializers and conditional branches; line count is the baseline EOF observed with the reader. Each has a new adjacent `<filename>.review.MD`. A dash denotes no separately assigned local finding, not proof of correctness or immunity from cross-cutting transport findings.

| # | Exact path | Lines | Local finding section(s) |
|---|---|---:|---|
| 1 | `Source/Shared/CMakeLists.txt` | 37 | — |
| 2 | `Source/Shared/ChatMessage.cxx` | 71 | — |
| 3 | `Source/Shared/ChatMessage.hxx` | 51 | 005 |
| 4 | `Source/Shared/ChatRoom.cxx` | 138 | 006 |
| 5 | `Source/Shared/ChatRoom.hxx` | 64 | 006 |
| 6 | `Source/Shared/ChatRoomManager.cxx` | 53 | — |
| 7 | `Source/Shared/ChatRoomManager.hxx` | 34 | — |
| 8 | `Source/Shared/DynamicReturn.hxx` | 33 | — |
| 9 | `Source/Shared/GalaxyID.hxx` | 68 | — |
| 10 | `Source/Shared/GalaxyIDSerialization.hxx` | 24 | — |
| 11 | `Source/Shared/GalaxyUserData.cxx` | 7 | — |
| 12 | `Source/Shared/GalaxyUserData.hxx` | 27 | — |
| 13 | `Source/Shared/GalaxyVersionedTypes.hxx` | 54 | — |
| 14 | `Source/Shared/IniData.cxx` | 980 | 008, 009, 010, 011, 012 |
| 15 | `Source/Shared/IniData.hxx` | 206 | — |
| 16 | `Source/Shared/Lobby.cxx` | 300 | 006 |
| 17 | `Source/Shared/Lobby.hxx` | 125 | 006 |
| 18 | `Source/Shared/LobbyManager.cxx` | 35 | — |
| 19 | `Source/Shared/LobbyManager.hxx` | 31 | — |
| 20 | `Source/Shared/Networking/MessageHandlersDeclareOverride.hxx` | 6 | — |
| 21 | `Source/Shared/Networking/MessageHandlersDeclarePureVirtual.hxx` | 6 | — |
| 22 | `Source/Shared/Networking/Messages.hxx` | 79 | — |
| 23 | `Source/Shared/Networking/Messages/ConnectionAcceptedMessage.hxx` | 15 | — |
| 24 | `Source/Shared/Networking/Messages/CreateLobbyMessage.hxx` | 33 | — |
| 25 | `Source/Shared/Networking/Messages/CreateLobbyResponseMessage.hxx` | 30 | — |
| 26 | `Source/Shared/Networking/Messages/EventConnect.hxx` | 12 | — |
| 27 | `Source/Shared/Networking/Messages/EventDisconnect.hxx` | 12 | — |
| 28 | `Source/Shared/Networking/Messages/FileRequestMessage.hxx` | 34 | — |
| 29 | `Source/Shared/Networking/Messages/FileShareMessage.hxx` | 26 | — |
| 30 | `Source/Shared/Networking/Messages/FileShareResponseMessage.hxx` | 31 | — |
| 31 | `Source/Shared/Networking/Messages/InvitationMessage.hxx` | 36 | — |
| 32 | `Source/Shared/Networking/Messages/JoinLobbyMessage.hxx` | 36 | — |
| 33 | `Source/Shared/Networking/Messages/KeyChallengeMessage.hxx` | 78 | — |
| 34 | `Source/Shared/Networking/Messages/LeaveLobbyMessage.hxx` | 59 | 005 |
| 35 | `Source/Shared/Networking/Messages/LobbyMemberStateChangeMessage.hxx` | 30 | — |
| 36 | `Source/Shared/Networking/Messages/LobbyOwnerChangeMessage.hxx` | 29 | — |
| 37 | `Source/Shared/Networking/Messages/OnlineStatusChangeMessage.hxx` | 25 | — |
| 38 | `Source/Shared/Networking/Messages/P2PNetworkPacketMessage.hxx` | 36 | — |
| 39 | `Source/Shared/Networking/Messages/P2PServerNetworkPacketMessage.hxx` | 33 | — |
| 40 | `Source/Shared/Networking/Messages/PingMessage.hxx` | 26 | — |
| 41 | `Source/Shared/Networking/Messages/RequestChatRoomMessagesMessage.hxx` | 36 | — |
| 42 | `Source/Shared/Networking/Messages/RequestChatRoomWithUserMessage.hxx` | 31 | — |
| 43 | `Source/Shared/Networking/Messages/RequestLobbyDataMessage.hxx` | 37 | — |
| 44 | `Source/Shared/Networking/Messages/RequestLobbyListMessage.hxx` | 28 | — |
| 45 | `Source/Shared/Networking/Messages/RequestSpecificUserDataMessage.hxx` | 47 | — |
| 46 | `Source/Shared/Networking/Messages/RichPresenceChangeMessage.hxx` | 44 | — |
| 47 | `Source/Shared/Networking/Messages/SendToChatRoomMessage.hxx` | 33 | — |
| 48 | `Source/Shared/Networking/Messages/SendToLobbyMessage.hxx` | 31 | — |
| 49 | `Source/Shared/Networking/Messages/SetLobbyDataMessage.hxx` | 59 | 005 |
| 50 | `Source/Shared/Networking/Messages/SetLobbyJoinableMessage.hxx` | 48 | 005 |
| 51 | `Source/Shared/Networking/Messages/SetLobbyMaxMembersMessage.hxx` | 46 | 005 |
| 52 | `Source/Shared/Networking/Messages/SetLobbyMemberDataMessage.hxx` | 52 | 005 |
| 53 | `Source/Shared/Networking/Messages/SetLobbyTypeMessage.hxx` | 48 | 005 |
| 54 | `Source/Shared/Networking/Messages/SetUserDataMessage.hxx` | 30 | — |
| 55 | `Source/Shared/Networking/Messages/UserHelloDataMessage.hxx` | 30 | — |
| 56 | `Source/Shared/Networking/Networking.cxx` | 270 | 003, 013 |
| 57 | `Source/Shared/Networking/Networking.hxx` | 236 | 001, 002, 004, 005, 007 |
| 58 | `Source/Shared/SharedFileUtils.cxx` | 385 | — |
| 59 | `Source/Shared/SharedFileUtils.hxx` | 66 | — |

## Architecture and end-to-end analysis

### Components and dependency direction

Versioned Shared combines domain models, SDK compatibility types, configuration/persistence and transport DTOs. Both Client and Server depend on it; it depends on Shared_NoVer utilities, the chosen Galaxy SDK, cereal, ENet/Enet++, SimpleIni and tracing. The per-version CMake target applies common version definitions and exports dependencies. SDK compatibility leaks into wire representation: a compile-time feature decision can change the protocol without changing its message ID.

Most messages are initialized passive DTOs, but requests often carry complete response graphs (Lobby/ChatRoom/stats) that the server will discard/replace. This expands pre-auth parsing and makes direction/state validation occur too late. Separating bounded wire DTOs from cached model snapshots would address both attack surface and protocol evolution.

### Client and server lifecycle

Client constructs configuration/containers, connects transport, starts a worker, and pumps `RunNetworking(2)`. Application `ProcessData` separately drains received events and invokes API handlers. ENet connect reports transport availability; key response uses configured identity; ConnectionAccepted triggers hello and logged-on state. `Stop` joins the worker before connection destruction; normal reset calls Stop before tearing down interfaces. Shared destructor drains owned queued packets before base host destruction.

Server runs `Tick` serially: connect creates peer::Data and challenge; successful response maps a unique identity, sends acceptance/presence, and hello fills stats/nickname and publishes user/lobby snapshots. Request handlers guard application operations using challenge completion. Pings intentionally work before application acceptance. Ordinary disconnect removes user, lobby/chat membership and mapper state.

The actual ENet fork emits a distinct timeout event and resets its reusable peer slot before application dispatch. Shared omits that event (003). Explicit client disconnect is queued before cleanup, then synthesized again (013). Concurrent queues make individual pops safe but do not supply session generations. An already popped old-session challenge/callback can outlive Cleanup and enqueue work for the replacement connection; this generation hazard is documented for validation without asserting an unproven native-peer use-after-free. The host remains allocated through reconnect.

### Ownership, exceptions and decoding limits

Receive event ownership is transferred out of ENet, queued on client or dispatched immediately on server, then destroyed by the receive scope guard. Decode exceptions release decoded temporaries and receive packet. Handler exceptions also free the receive packet but escape into Server/Main or the SDK pump (002). Object allocation before the decoder try block and output serialization can throw as well; the report does not claim allocation failure was reproduced.

Send success transfers ownership to ENet. Client destroys rejected packets; server typed Send loses them (004). Both broadcast implementations destroy the packet if no peer accepted it, so they do not share that particular leak. Outgoing queue push still lacks an RAII handoff if allocation throws; its operational significance requires fault injection.

Actual vendor limits: **32 MiB maximum packet** on both sides; **512 MiB server / 32 MiB client maximum waiting data**. Fragment checks enforce received total length. Delivered receive packets cease counting against ENet waiting data even while Shared queues them (007). These limits neither constrain a declared cereal allocation (001) nor make append-only history snapshots deliverable (006).

Cereal's portable archive reads the endian marker and swaps arithmetic bytes. String/vector loaders resize from wire length before verifying remaining payload; map loaders iterate/insert with no aggregate budget. shared_ptr load accepts null and references to earlier archive objects. Structural success does not validate enum/bool ranges, room/member identity consistency, pointer-graph semantics or complete frame consumption. No buffer-overread is attributed to the short eight-byte frame precheck: the missing marker byte produces a caught short read.

### Authentication and Windows/endian/schema gates

The code implements shared-key LAN admission, self-selected GalaxyIDs and a configured-server trust assumption. FNV/XOR challenge response is not encrypted or authenticated transport; claims about private-key protection against active attackers require a stronger explicit product threat model. The review did not access private keys, capture traffic or claim a cryptographic break. The pre-auth allocation finding needs only ENet reachability and remains valid with a private key.

Windows x86/x64 agree on the fixed-width scalar fields and little-endian nonce-memory hash. Numeric portable archives do not stabilize SDK enum/member schemas. Gate changes include ChatMessage type at 1.110.0, lobby update fail_reason above 1.124.0 and leave reason at 1.133.0 (005). Cross-endian response hashing is a portability limitation outside the supported Windows focus, not a new release-blocking finding.

### Lobby/chat invariants

Lobby membership is the per-user data-map key set; shared pointers keep models alive across manager/peer/client caches. Server normally substitutes sender IDs, checks lobby-message membership and performs owner reassignment explicitly after departure. Chat publication waits until both members are added; retrieval checks membership, and exclusive-reference slicing bounds arithmetic correctly. Client callbacks hold their own model locks; the Shared model classes are not independently synchronized.

Policies remain scattered: AddMember does not enforce admission, direct Join ignores the model's joinable flag, and setters accept capacity/type without a central invariant check. Discovery filters are client-side, so they cannot provide server authorization. Full history in all snapshots couples state retrieval to session age (006). SDK deletion explicitly equals setting an empty value; absent an erased-key-count contract, this review does not label empty-valued entries a confirmed deletion defect.

### Windows configuration, paths and persistence

MachineInfo selects one boot INI, not layered configuration: working directory, library directory, executable directory, per-game AppData and temporary directory are checked for existing boot files. Fallback selects per-game storage with local/global boot INI, otherwise plain AppData. A higher-priority selected INI does not merge missing values from lower-priority files. These are observed precedence rules, not an assertion that working-directory precedence is unsafe.

INI files themselves use Windows wide-file paths. UTF-8 values subsequently converted from std::string into filesystem paths use the wrong native encoding on non-UTF-8 ACP processes (009). Absolute configured bases replace the left operand in filesystem joins; there is no established doubled-absolute-path defect. Environment game-data prefix is concatenated as a string and reread on each path call. Missing plain-AppData provisioning (010), wrong identity-source checks (011) and incomplete DLC numeric parsing (012) are independently reproducible local edge cases.

Persistence snapshots several logical stores into separate INIs. Achievement dirtiness is acknowledged before save success and results are discarded (008). File-level saves are not serialized across the entire load/modify/save transaction; concurrent callers also merit revision/transaction validation. Filesystem sandbox rejection is effective for the traced traversal, but its exception must be translated at the network boundary (002).

## Context-only dependencies and owner handoffs

These are source observations outside the 59-file assignment, not additional NET IDs or claims of exhaustive review of those directories. They must be reconciled by the respective owner before global counting:

- **SERVER:** `ServerHandlers.cxx:77-130` uses immediate Disconnect on challenge rejection without the normal application cleanup; vendor `enet_peer_disconnect_now` emits no local disconnect event. Old peer data/unauthenticated entries can persist until cleanup or slot reuse. This is distinct from the Shared omitted timeout event.
- **SERVER/API:** Direct Join at `ServerHandlers.cxx:559` comments out IsJoinable; SDK `IMatchmaking.h:648-654` explicitly forbids joining a nonjoinable lobby. Capacity updates/creation also lack the documented range enforcement. Update helper accepts a rollback callback but never invokes it, allowing rejected speculative client metadata to remain wrong.
- **SERVER:** Lobby-target P2P at `ServerHandlers.cxx:398-426` does not verify source membership as the direct-user branch does. File upload at 464-476 acknowledges a nonzero ID after create/write failure; its counter file is opened through a non-creating SharedFileUtils::Open. Unknown rich-presence action can preserve supplied success because the switch has no default reset.
- **UTIL:** `AchievementsAndStatsContainer.hxx:54` passes `PlayTime.load()` to a bidirectional archive: input writes the temporary, not the atomic. Shared hello/specific-user schemas inherit lost persisted play time. Copy/serialize do not automatically lock every source map.
- **UTIL/STORAGE:** `filesystem_container_entry.cxx:188-195` returns file-clock epoch seconds; MSVC file time uses the Windows epoch. Shared's uint32 saturation cannot convert it to Unix time, yielding incorrect SDK timestamps. A complete fix belongs below the wrapper with SDK verification.
- **API/CORE:** `Chat.cxx:120-127` dereferences nullable decoded message elements; `137-153` clears its borrowed incoming vector pointer only on exception, not normal return. The latter leaves a dangling pointer after the decoded DTO dies. Retained listener/callback ownership and shutdown reentrancy need owner review. No claim is made that an arbitrary unauthenticated client can directly send such a server response to another game.
- **STORAGE:** FileDownloaded treats empty data as failure, so zero-byte shared files cannot succeed through that path; the response needs an unambiguous success convention. FileUploaded reports success even when local CopyFromLocalToShared fails.
- **API:** RequestLobbyDataProcessed refreshes maps but not owner/capacity/joinability/type in an existing snapshot; chat request IDs/target fields are broadcast to both participants and require recipient-specific correlation review.

## Context actually inspected

Full files read for lifecycle: `Source/Client/Client.{cxx,hxx}`, `ClientNetworkHandlers.cxx`, `UniverseLAN.cxx`; `Source/Server/Server.{cxx,hxx}`, `ServerHandlers.cxx`, `Peer.{cxx,hxx}`, `Challenge.{cxx,hxx}`, `Main.cxx`; Client `Impl/Chat.cxx`.

Full utility context: Shared_NoVer `MachineInfo.{cxx,hxx}`, `EnvUtils.cxx`, `DefaultConfigFiles.cxx`, `AchievementsAndStatsContainer.{cxx,hxx}`, `AchievementData.cxx`, `GlobalUniqueID.{cxx,hxx}`, `ContainerGetByIndex.hxx`, `SafeStringCopy.hxx`, `ConcurrentQueue.hxx`, `MemoryInputStream.{cxx,hxx}`, `MemoryInputBuffer.{cxx,hxx}`, `Networking/SendableEventMessage.hxx`, `Networking/MessageUniqueID.hxx`, and filesystem_container's container, entry and utils `.cxx` implementations.

Vendor context: full Enet++ wrapper/header and broadcast-except implementation; full cereal portable archive, string/vector loaders and pair-associative loader; targeted shared_ptr loader; targeted ENet-IPv6 event dispatch, reset/disconnect, send/receive, service loop and broadcast code plus limit declarations; targeted SimpleIni UTF-8, conversion and Windows file-open contract plus its manifest. These are actual repository versions, not assumed upstream limits.

Targeted caller/SDK context: Client Matchmaking create/list/join/leave/data/member/message paths; Client Networking AddPacket, User/Utils connection notifications and User/Stats saves; Storage upload/download/copy paths; GalaxyDLL ProcessData; SDK 1.152.11 matchmaking property/joinability/capacity contracts; feature matrix chat/leave thresholds. Unread portions of these context-only files are not included in assigned coverage.

## Execution, validation and limitations

- Read `.ai/review-baseline/PLAN.MD`, `.ai/SKILLS/CppReviewer.md`, and exclusion instructions in `.ai/ai-instructions-review.txt`. No AGENTS.md was found by the repository glob. Current task's no-Git-writes/no-credentials/no-build rules governed execution.
- Windows PowerShell read-only Git: `git rev-parse HEAD`; `git status --short`; `git diff b30e83872c0006e8240c8b4f565da5351bf10080 -- Source/Shared '*.cxx' '*.hxx' '*.cmake' '*.txt'`; `git ls-files -- Source/Shared/*.cxx Source/Shared/*.hxx Source/Shared/*.cmake Source/Shared/*.txt`. Initial status showed coordinator-staged removals of old reports; no old report text was opened.
- Rechecked with `git diff --exit-code b30e83872c0006e8240c8b4f565da5351bf10080 -- 'Source/Shared/**/*.cxx' 'Source/Shared/**/*.hxx' 'Source/Shared/**/*.cmake' 'Source/Shared/**/*.txt' 'Source/Shared/*.cxx' 'Source/Shared/*.hxx' 'Source/Shared/*.cmake' 'Source/Shared/*.txt'`: no output, success, no input changes.
- Dedicated Read/Glob/Grep tools supplied source coverage; reports written only with `apply_patch`. No source/config mutation, Git index update, branch change, commit, credentials access, subagent or product/build/test invocation.
- PowerShell counted Git inventory and `rg --count '^# Fresh review' Source/Shared -g '*.review.MD'`: **59 inputs / 59 report headings**. Unique finding headings were enumerated with `rg --no-filename --only-matching '^### \[BASE-NET-[0-9]+\]' ... | Sort-Object -Unique`: **13 unique IDs, 001–013**.
- Final exact-path reconciliation compared `git ls-files` input paths with fresh-report paths returned by `rg --files-with-matches '^# Fresh review' Source/Shared -g '*.review.MD'`, normalizing separators and removing only the `.review.MD` suffix. PowerShell `Compare-Object` returned **0 differences**. Content-count checks on this notebook returned **59 coverage rows; 2 High, 7 Medium, 4 Low index entries**. All assigned files and report paths reconcile; no incomplete Shared file remains.
- **Limitations:** Static review only; Windows x86/x64 behavior inferred from source/vendor contracts. No build, ABI matrix, runtime reproducer, sanitizer, fuzzer, benchmark or SDK comparison was run. Linux guards were inspected only. Private threat model, intended mixed-SDK interoperability, self-chat semantics and precise long-term retention guarantees remain product questions. Complete reading is not proof of defect completeness.

## Verification and remediation roadmap

1. Bound/pre-gate decoding (001) and translate expected handler/input exceptions (002). Add Windows malformed-frame/allocation-budget cases and a correctly serialized rejected-path case; verify process survival and receive ownership.
2. Normalize ENet timeout retirement/retry (003), adopt RAII for rejected server sends (004) and publish one logical disconnect (013). Verify initial offline startup recovery, slot reuse and deterministic queue interleavings.
3. Establish schema admission (005), bounded metadata/history separation (006) and application queue byte budgets (007). Exercise representative SDK schema boundaries and >32 MiB aggregate history without increasing individual packets.
4. Make persistence commits observable/retriable (008), decode UTF-8 paths correctly (009), provision all selected default locations (010), validate chosen identity inputs (011) and require complete DLC ID parse (012).
5. Coordinate the context-only handoffs before integration counting. Existing test/build/CI coverage was not executed or certified by this assignment; proposed tests should exercise contracts and failure modes rather than mirror implementation.
