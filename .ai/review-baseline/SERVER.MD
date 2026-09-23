# SERVER — fresh baseline review

## Executive summary

Baseline: **`b30e83872c0006e8240c8b4f565da5351bf10080`**. Inspected checkout HEAD: `40265aed370464569e873692ef5d53fbdb12679b`. Review date: 2026-09-23. The owned implementation/build inputs have no working-tree difference from the baseline. This is a fresh inspection; no superseded review, FOUND_DEFECTS report or previous coverage report was consulted.

**Coverage: 43/43 tracked owned inputs read completely, 43 new sibling `.review.MD` reports, zero missing owned files.** Breakdown: Server 10, SystemTests 22, Tracer 8, Version 3; 28 `.cxx`, 11 `.hxx`, 4 `.txt`, zero `.cmake` files in this assignment. This notebook is the 44th report artifact.

**19 unique confirmed static findings: 1 High, 15 Medium, 3 Low; no Critical.** All have High confidence in the stated conditional mechanism, not runtime reproduction. Categories: Correctness 10, Security 3, Testing 2, Memory Safety 1, Concurrency 1, Build 1, Portability 1. Cross-references in companion sidecars are not additional findings.

The principal risk is incomplete peer cleanup across transport generations: an ignored ENet timeout can let an old GalaxyID resolve a newly attached peer, including a null user snapshot. Other material issues affect enforced lobby admission, request correlation, file-share persistence and trustworthy test outcomes. Normal user snapshot serialization and owner migration were traced and do not justify the commonly assumed alias/election defects. Windows crash reporting definitively loses the original exception context; recursive UEF entry was **not confirmed** and is not reported as a deadlock.

For LAN use, stabilize peer lifecycle first, then lobby/correlation semantics and file persistence. These results do not certify a release: no build, test or crash injection was authorized/executed. Optional diagnostic/storage limitations are rated proportionally.

## Exact coverage ledger

Every row is fully read, with the shown source line range, and has a new report at **the listed path plus `.review.MD`**. IDs in this ledger identify the primary detailed finding locations; companion reports also contain relevant cross-references. “—” means no independent confirmed finding, not proof of correctness.

| Owned path | Complete read | Primary finding IDs (BASE-SERVER-) |
|---|---:|---|
| `Source/Server/CMakeLists.txt` | 1–31 | — |
| `Source/Server/Challenge.cxx` | 1–22 | — |
| `Source/Server/Challenge.hxx` | 1–21 | — |
| `Source/Server/GalaxyApiFactory.cxx` | 1–50 | — |
| `Source/Server/Main.cxx` | 1–42 | — |
| `Source/Server/Peer.cxx` | 1–136 | — |
| `Source/Server/Peer.hxx` | 1–82 | — |
| `Source/Server/Server.cxx` | 1–200 | 002, 016, 018 |
| `Source/Server/Server.hxx` | 1–75 | — |
| `Source/Server/ServerHandlers.cxx` | 1–1054 | 001, 003–008, 019 |
| `Source/SystemTests/CMakeLists.txt` | 1–666 | — |
| `Source/SystemTests/Common/Protocol.cxx` | 1–36 | — |
| `Source/SystemTests/Common/Protocol.hxx` | 1–18 | — |
| `Source/SystemTests/Host/Apps.cxx` | 1–77 | — |
| `Source/SystemTests/Host/Chat.cxx` | 1–327 | 014 |
| `Source/SystemTests/Host/CloudStorage.cxx` | 1–127 | — |
| `Source/SystemTests/Host/CustomNetworking.cxx` | 1–128 | — |
| `Source/SystemTests/Host/Friends.cxx` | 1–202 | — |
| `Source/SystemTests/Host/Host.hxx` | 1–238 | — |
| `Source/SystemTests/Host/Lobby.cxx` | 1–509 | — |
| `Source/SystemTests/Host/Main.cxx` | 1–575 | — |
| `Source/SystemTests/Host/P2P.cxx` | 1–202 | — |
| `Source/SystemTests/Host/Stats.cxx` | 1–216 | — |
| `Source/SystemTests/Host/Storage.cxx` | 1–198 | — |
| `Source/SystemTests/Host/Telemetry.cxx` | 1–47 | — |
| `Source/SystemTests/Host/UserData.cxx` | 1–82 | — |
| `Source/SystemTests/Host/Utils.cxx` | 1–46 | — |
| `Source/SystemTests/Runner/Configuration.cxx` | 1–169 | — |
| `Source/SystemTests/Runner/Main.cxx` | 1–200 | 012 |
| `Source/SystemTests/Runner/Model.cxx` | 1–252 | 013 |
| `Source/SystemTests/Runner/Process.cxx` | 1–176 | 015 |
| `Source/SystemTests/Runner/Runner.hxx` | 1–113 | — |
| `Source/Tracer/CMakeLists.txt` | 1–17 | — |
| `Source/Tracer/MiniDump.cxx` | 1–161 | — (009 shared) |
| `Source/Tracer/MiniDump.hxx` | 1–5 | — |
| `Source/Tracer/ReturnAddress.hxx` | 1–18 | — |
| `Source/Tracer/Stacker.cxx` | 1–264 | 009, 017 |
| `Source/Tracer/Stacker.hxx` | 1–45 | — |
| `Source/Tracer/Tracer.cxx` | 1–419 | 010, 011 |
| `Source/Tracer/Tracer.hxx` | 1–94 | — |
| `Source/Version/CMakeLists.txt` | 1–20 | — |
| `Source/Version/Version.cxx` | 1–7 | — |
| `Source/Version/Version.hxx` | 1–7 | — |

## Findings index

Detailed sections live in the primary sidecars above. Each includes severity, confidence, category, exact source locations, evidence, mechanism, affected scope/impact, alternatives/recommendation and focused verification.

| ID | Severity | Finding |
|---|---|---|
| BASE-SERVER-001 | Medium | Authentication rejection immediately resets transport without application cleanup; rapid slot reuse leaks Data. |
| BASE-SERVER-002 | **High** | Ignored transport-timeout event permits old-ID lookup through a reused ENet slot, stale memberships and null-user dereference. |
| BASE-SERVER-003 | Medium | JoinLobby ignores acknowledged non-joinable state. |
| BASE-SERVER-004 | Medium | Lobby-ID P2P route omits sender membership authorization. |
| BASE-SERVER-005 | Medium | Failed lobby property changes omit rollback and preserve rejected values in client caches. |
| BASE-SERVER-006 | Medium | Fresh shared-file counter is opened but never created; IDs repeat after restart. |
| BASE-SERVER-007 | Medium | Failed/repeated-name uploads return a nonzero success ID despite missing persisted data. |
| BASE-SERVER-008 | Medium | Chat notifications reuse sender-local request IDs and can consume another peer's pending callback. |
| BASE-SERVER-009 | Medium | Windows crash path discards original EXCEPTION_POINTERS; stack/dump capture describes the handler instead. |
| BASE-SERVER-010 | Medium | Direct shared-ofstream flush bypasses osyncstream synchronization. |
| BASE-SERVER-011 | Low | Same-second trace directory collision prevents initialization. |
| BASE-SERVER-012 | Medium | Child exit can precede final log consumption, falsely failing a valid test. |
| BASE-SERVER-013 | Medium | Role tokens permit dot/internal/case-equivalent filesystem aliases on Windows. |
| BASE-SERVER-014 | Medium | Early typed-ID chat SDK hosts compile unavailable ChatMessageType API. |
| BASE-SERVER-015 | Low | Native narrow Windows paths are reinterpreted as UTF-8 in child command construction. |
| BASE-SERVER-016 | Medium | Startup prints protocol-equivalent reusable LAN authentication key material. |
| BASE-SERVER-017 | Low | Dump-only configuration never invokes dump creation. |
| BASE-SERVER-018 | Medium | Tick treats negative Pull failure as a delivered event and can spin on persistent errors. |
| BASE-SERVER-019 | Medium | Broadcast recipients include challenge-pending, unauthenticated transport peers. |

## Architecture and traced contracts

### Server state and networking

`Main → Server::Tick → GalaxyNetworkServer/ENet → MessageReceiver → Handle` is single-threaded. The transport slot's Data points back to its Mapper; a separate GalaxyID map points to the transport slot. This ownership model makes cleanup-before-reuse essential. Ordinary disconnects and application sweeps call lobby/chat/user cleanup then delete Data. Immediate auth rejection omits it; ENet's distinct timeout event is ignored upstream. The timeout event's `data` is zero, and ENet clears `connectID` during reset: neither is a preserved application generation ID.

The handshake verifies a shared configured LAN key, not external GOG identity. Protected mutation handlers do return before work on authentication failure. Correct challenge arithmetic followed by duplicate-ID rejection resets the transport immediately, so a premature `completed` flag alone does not prove post-rejection authorization. Outbound broadcasts need their own authenticated-recipient selection.

Hello messages replace a user's stats container and supply the initial nickname; specific requests reply with complete snapshots and request type. Serialization happens within Send, so reusing a response pointer in a loop does not defer all payloads to the final value.

Lobbies have manager, peer-membership and shared-object representations. Owner data edits and member data/message writes enforce their expected roles; joinability and lobby-directed P2P are gaps. Owner departure removes the old member before choosing an existing successor, or closes FCM/STAR and removes peer references. No normal owner-election defect was confirmed.

Chat builds both memberships before publication and checks membership for history/send. Correlation IDs remain connection-local and cannot be copied into another participant's response. Files use persistent metadata and a global filename/ID index; upload/download policy checks exist, but persistence acknowledgments/counter creation are defective. Missing offline durable chat or external account service features are not presented as security exploits.

### Tracing and exception handling

Trace scopes write thread-local logs and synchronized global records; raw global flushes violate that synchronization discipline. Stacker registers one active UEF per linked instance; terminate detouring is inactive. The saved filter is chained after callback work and KeepCount destruction. Original Windows exception pointers reach OurCrashHandler but are dropped before walking/dumping.

Recursive UEF reachability was investigated through the actual registration/callback call graph, StackWalker context behavior and the Microsoft API contract. There is no explicit self-call/repeated Init path. A hypothetical nested handler could self-wait, but an exception inside UEF does not establish that Windows will call it recursively. **No recursive-UEF deadlock is confirmed.** This needs an isolated OS-specific reproduction before escalation.

### SystemTests and Version

The model validates schema/identities/events, Configuration stages isolated SDK-linked hosts and INIs, and Runner schedules them using control files and line-based stdout. A PASS must combine successful process exit and all declared events; final-read ordering undermines that intent. Shared persistence groups serialize host lifetimes. Hosts pump SDK callbacks and use `_Exit`, intentionally excluding graceful DLL shutdown from coverage. Feature guards span SDK versions, but Chat has an early-version compile gap.

Version is a static library initialized from generated BUILD_VERSION. Its custom dependency runs the compiler-selected updater before compilation. Windows generation counts commits, falls back to an environment value/zero and updates only changed content. Source-tree output is shared across build trees; concurrent generation/read-only-source behavior was not executed or certified.

## Dependency/context inventory and ownership boundaries

Context was read only to trace contracts; it is **not additional reviewed-file coverage**, and excluded trees received no independent findings:

- `Source/Shared/Networking/Networking.{cxx,hxx}`, `Messages.hxx`, and message headers for KeyChallenge, RequestSpecificUserData, FileRequest and FileShareResponse: dispatch, serialization, correlation and response semantics.
- `Source/Shared/Lobby.{cxx,hxx}`, `LobbyManager.cxx`, `ChatRoom.cxx`, `ChatRoomManager.cxx`, `SharedFileUtils.cxx`, `IniData.cxx:268–352`: ownership/membership, histories, file lookup and option/time constraints.
- `Source/Shared_NoVer/Networking/MessageUniqueID.cxx`, selected `filesystem_container.cxx:1–208` and `filesystem_container_entry.cxx:1–180`: ID origin, persistent indexes and file creation/metadata semantics.
- `Source/Client/Client.cxx`, selected `ClientNetworkHandlers.cxx`, `UniverseLAN.cxx`, Impl User/Storage/Matchmaking/Chat/Networking/ListenerRegistrar/GalaxyThread sections and caller searches: actual sends, response handling, cache updates and lifetime. These are other reviewers' ownership.
- `Source/galaxy_sdk_features.cmake` feature searches; root `CMakeLists.txt`; SDK `1.152.11` networking/matchmaking and early `1.104.3`/`1.109.0` chat declarations: build/contract context. SDKs are not first-party targets.
- Vendored `Enet++` wrapper/header/helper and selected `Enet-IPv6` peer/protocol/host/header sections: immediate-disconnect, timeout/reset and broadcast guarantees. Selected StackWalker header/implementation: default NonExcept constructor and missing-context capture. These are excluded implementation dependencies, not reviewed targets.
- `Util/UpdateVersion.bat` and `.sh`: generation context only. No script was executed. `Source/Version/stringize.h` is outside the requested extensions and not claimed reviewed.
- Scenario JSON context: `raw-p2p-three-peer-routing.json`, `raw-p2p-leave-revokes-routing.json`, `stats-achievement-durable-persistence.json`. No credential example/file or old defect report was opened.
- Microsoft Learn [SetUnhandledExceptionFilter](https://learn.microsoft.com/en-us/windows/win32/api/errhandlingapi/nf-errhandlingapi-setunhandledexceptionfilter): documented registration, fault-thread context and chaining; not evidence of recursive dispatch.

BASE-SERVER-002 needs coordinated NET dispatcher remediation. BASE-SERVER-005/008 involve existing client response contracts; storage metadata behavior informs 006/007. The coordinator should deduplicate any overlapping NET/API/STORAGE findings by root cause, preserving this server-side reachability evidence.

## Actual execution and limits

Read `.ai/review-baseline/PLAN.MD`, `.ai/SKILLS/CppReviewer.md` and `.ai/ai-instructions-review.txt`. No AGENTS.md was found by repository glob. Dedicated read/glob/grep tools supplied all code/context reads; edits used **apply_patch only**.

Read-only terminal operations actually run:

1. `git status --short`, `git rev-parse HEAD`, and `git ls-files` for the four ownership roots (initial status included pre-existing staged deletion of superseded sidecars).
2. `git diff b30e83872c0006e8240c8b4f565da5351bf10080 -- Source/Server Source/SystemTests Source/Tracer Source/Version ':(exclude)*.review.MD'`: empty implementation/build-input diff.
3. Extension-filtered Git inventory and Test-Path existence reconciliation: **Owned=43, SidecarsPresent=43, Missing=0**. Repeated baseline name-only comparison remained empty.
4. Report heading/severity/coverage searches and readback of fresh artifacts for consistency; no old report contents were used.

Web searches and the Microsoft Learn fetch were read-only research. No configure/build, executable/test/sanitizer/analyzer run, fault injection, updater, credential access or Git mutation was performed. No source change was made. Linux code was inspected only for static guards. Findings' verification steps are proposed future work, not claimed results.

## Assessment and remediation order

- **First:** close all lifecycle paths and prove generation-safe lookup (002,001), then enforce joinability/lobby routing and authenticated broadcast recipients (003,004,019). Preserve existing ordinary owner migration.
- **Next:** fix authoritative rollback and recipient-local chat correlation (005,008), persistent counter and truthful storage responses (006,007), and network error handling (018). Suppress usable key output (016).
- **Diagnostics:** preserve original exception context (009), unify stream synchronization (010), then unique sessions/dump-only behavior (011,017). Avoid escalating unconfirmed UEF recursion into a release blocker.
- **Verification infrastructure:** terminal log drain, Windows-safe staging, SDK boundary guards and path encoding (012–015). Extend existing meaningful binary/callback/owner-migration tests with timeout-reuse, restart persistence and rejected-operation scenarios.

Positive practices include server-stamped sender identity, existing ownership/membership checks, immediate snapshot serialization, post-removal owner selection, policy-denial callbacks, strict protocol records, isolated positive test payloads and feature-driven target generation. Performance/resource bounds, simultaneous crash behavior, real SDK matrix compilation and graceful teardown remain unmeasured. Full owned-file reading is complete; runtime validation is explicitly outstanding.
