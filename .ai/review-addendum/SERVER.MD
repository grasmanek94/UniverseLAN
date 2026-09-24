# SERVER — source-first follow-up addendum

## Executive summary

**43/43 owned inputs re-read completely; zero unfinished inputs.** Review date: 2026-09-24. Actual checkout: `C:\Development\AI\UL`, HEAD `48cea8c6`. The supplied `b30e8387` identifies the production baseline, not a directory suffix: `C:\Development\AI\UL b30e8387` does not exist. The owned source/build inputs match `b30e83872c0006e8240c8b4f565da5351bf10080`.

**Three new confirmed static findings:** one High, one Medium, one Low, all High confidence in their stated conditions. **All 19 BASE-SERVER IDs remain supported; none withdrawn or severity-reclassified.** Three receive substantive scope refinements under their existing IDs (003, 008, 013). Preserved baseline total 19 plus three additions gives **22 SERVER-owner IDs: 2 High, 16 Medium, 4 Low; zero Critical**. These are owner-local counts before cross-owner deduplication, not 22 independent repository-wide defects.

The new principal risk is a legal uploaded filename entering the server's administrative counter namespace and preventing its next startup. Whole-model lobby exports additionally disclose member communication to authenticated nonmembers. Crash reporting has a concrete oversize-source-path exception before log/dump creation. The highest retained integrated risk remains timeout retirement and old-ID resolution through a reused ENet slot.

Recommendations: repair lifecycle retirement/generation checks and separate control state from uploads first; then apply recipient-specific lobby publication, consistent admission and correlation/error semantics. Preserve the working ordinary owner-migration and sender-substitution behavior. This static pass establishes coverage and source mechanisms, not release readiness or runtime validation.

## Scope, method and artifacts

Followed `.ai/SKILLS/CppReviewer.md` and `.ai/review-addendum/PLAN.MD`. Read all owned source first, then supporting implementations/SDK/vendor contracts, then compared existing findings. Existing reports remain intact; additions and corrections are appended only to SERVER-owned sidecars. No other owner's report was edited.

Owned inventory: **Server 10; SystemTests 22; Tracer 8; Version 3 = 43**. Extensions: **28 `.cxx`, 11 `.hxx`, 4 `.txt`, 0 `.cmake`**. Generated Version `.h` files, scenario JSON, root/shared build files, SDKs, vendor code and updater scripts are context rather than extra owned coverage. No content-identity shortcut or sampling was used for the 43 inputs.

New detailed records are locally complete: severity, confidence, category, locations, scope, evidence, mechanism, impact, solution options, recommendation and proposed verification. BASE IDs keep their original detailed records plus clearly headed addenda. Verification throughout means future work unless explicitly listed under actual operations below.

## Exact 43-path coverage and fresh inspection notes

Every range is **1 through EOF, fully read this pass**, including disabled branches and all function/test bodies. Finding suffixes below use BASE-SERVER- unless prefixed ADD.

| Owned path | Full read | Fresh inspection / disposition |
|---|---:|---|
| `Source/Server/CMakeLists.txt` | 1–31 | Versioned executable/definitions, shared dependency, output and debugger paths; no new local finding. |
| `Source/Server/Challenge.cxx` | 1–22 | Temporary response copies occur within their full expressions; early completed flag alone does not bypass immediate rejection reset. |
| `Source/Server/Challenge.hxx` | 1–21 | Challenge state/returned-reference ownership traced through synchronous send. |
| `Source/Server/GalaxyApiFactory.cxx` | 1–50 | Legacy feature/calling-convention gates and server-side null factory stubs; no invoked invalid factory path established. |
| `Source/Server/Main.cxx` | 1–42 | Global unique server, uncaught construction, infinite tick/sleep; startup sink for ADD-SERVER-001, not a normal teardown loop. |
| `Source/Server/Peer.cxx` | 1–136 | Allocation, publication, ID map, disconnect/delete, lobby links; generation hazard 002 and rejection leak 001 retained. |
| `Source/Server/Peer.hxx` | 1–82 | Raw attachment owned through explicit disconnect, no Mapper destructor/generation field; ordinary process exit limits shutdown observation. |
| `Source/Server/Server.cxx` | 1–200 | Construction/config/counter, authentication/activity sweeps, service return handling; 002/016/018 retained; ADD-SERVER-001 startup consumer. |
| `Source/Server/Server.hxx` | 1–75 | Member order, timeout state, manager/peer graphs and reserved counter name; no independent 32-bit-exhaustion count. |
| `Source/Server/ServerHandlers.cxx` | 1–1054 | Every handler/helper checked for admission, recipient authorization, input replacement, graph mutation, error and cleanup; ADD-SERVER-001/002. |
| `Source/SystemTests/CMakeLists.txt` | 1–666 | Every target/scenario registration, feature gate, timeout/serialization/skip property; host compilation is distinct from test registration (014). |
| `Source/SystemTests/Common/Protocol.cxx` | 1–36 | Unsigned-char classification, duplicate token rejection and 56-bit IDs; token validity is not Windows path identity (013). |
| `Source/SystemTests/Common/Protocol.hxx` | 1–18 | Protocol prefixes/declarations; final-output race belongs to runner 012. |
| `Source/SystemTests/Host/Apps.cxx` | 1–77 | Installed/disabled/absent DLC, exact/truncated language copies, specific/global owned callbacks and unregister. |
| `Source/SystemTests/Host/Chat.cxx` | 1–327 | Live, reuse, unknown-send and history/cursor bodies; callback-access contract checked, 014 retained and 008 coverage gap precise. |
| `Source/SystemTests/Host/CloudStorage.cxx` | 1–127 | Put/list/metadata/get callbacks, hash/time/type/ID and binary bytes; single container/happy-path limits. |
| `Source/SystemTests/Host/CustomNetworking.cxx` | 1–128 | Open/echo/close listeners, binary NUL payload, close duplicate window and network setup cleanup; echo is not teardown coverage. |
| `Source/SystemTests/Host/Friends.cxx` | 1–202 | Online/persona/invitation/join and rich-presence bodies, exact sender/value checks and coordination gates. |
| `Source/SystemTests/Host/Host.hxx` | 1–238 | Versioned interface facade, pump final iteration, deadline and feature declarations; no new header finding. |
| `Source/SystemTests/Host/Lobby.cxx` | 1–509 | All create/list/tag/join/data/leave/owner-transfer/close bodies, listener counts/IDs/cache assertions; two-member orderly scenarios. |
| `Source/SystemTests/Host/Main.cxx` | 1–575 | Argument/profile-token validation, version dispatch, init/sign-in pump and flushed PASS plus `_Exit`; no credential data accessed. |
| `Source/SystemTests/Host/P2P.cxx` | 1–202 | Bidirectional, directed three-peer, channel 255/1200 bytes, leave/quiet, offline-query bodies; finite quiet windows and unchecked leave-send control noted. |
| `Source/SystemTests/Host/Stats.cxx` | 1–216 | Remote stats/achievement/user-data barrier plus process-separated int/float/achievement persistence, exact float bits. |
| `Source/SystemTests/Host/Storage.cxx` | 1–198 | Share/read/offset/cache-close/invalid-ID and upload/download-policy-denied bodies; one server lifetime does not cover 006 or ADD-SERVER-001. |
| `Source/SystemTests/Host/Telemetry.cxx` | 1–47 | Exact event/index and single success/failure; local store setting, no transport-delivery claim. |
| `Source/SystemTests/Host/UserData.cxx` | 1–82 | Writer result and receiver registration/cache checks, unregister on early/normal exits; one live update. |
| `Source/SystemTests/Host/Utils.cxx` | 1–46 | Disabled-overlay state plus bounded no-callback observation; no overlay implementation claim. |
| `Source/SystemTests/Runner/Configuration.cxx` | 1–169 | Root/host/server INIs, shared persistence paths, fixed public test key, port probes, staging/runtime checks; 013/015 consumers. |
| `Source/SystemTests/Runner/Main.cxx` | 1–200 | Setup, all scheduling loops, event/action/finish gates, persistence serialization, exit/PASS accounting and cleanup; 012 retained. |
| `Source/SystemTests/Runner/Model.cxx` | 1–252 | Full schema/identity/group/event/dependency/peer parsing and CLI; 013 extended to persistence-group case aliases. |
| `Source/SystemTests/Runner/Process.cxx` | 1–176 | Native child/log/thread/process handles, argument conversion, exit/kill/wait, incremental log protocol; 015 retained. |
| `Source/SystemTests/Runner/Runner.hxx` | 1–113 | Initialized process/model state, ownership of child records and declarations; no active Child copy found. |
| `Source/Tracer/CMakeLists.txt` | 1–17 | Static tracer, Windows-only StackWalker/Detours/imagehlp dependencies; no build run. |
| `Source/Tracer/MiniDump.cxx` | 1–161 | Every allocation/load/open/export/write/cleanup branch and exception-context synthesis; 009 retained, bounded resource observations. |
| `Source/Tracer/MiniDump.hxx` | 1–5 | Void/path-only interface cannot carry original fault context or signal write failure. |
| `Source/Tracer/ReturnAddress.hxx` | 1–18 | MSVC intrinsic/GNU fallback/unknown compiler branches; return address is not original exception context. |
| `Source/Tracer/Stacker.cxx` | 1–264 | Active UEF graph, nesting guard/counter, stack walk, dump and previous filter; ADD-SERVER-003; 009/017 retained. |
| `Source/Tracer/Stacker.hxx` | 1–45 | Fixed capacities, vector/callback lifetime, singleton; 260-character field versus actual 1024-byte producer traced. |
| `Source/Tracer/Tracer.cxx` | 1–419 | Init/TLS scope/stream/flag/exception paths; 010/011 retained; unproven general init races not promoted. |
| `Source/Tracer/Tracer.hxx` | 1–94 | Flags, scope noncopyability, formatting and stream access/destructor exception boundary. |
| `Source/Version/CMakeLists.txt` | 1–20 | Static target, updater choice and dependency; supported MSVC ordering valid, shared-source generation limits retained. |
| `Source/Version/Version.cxx` | 1–7 | BUILD_VERSION constant and extern-derived linkage; no runtime lifecycle issue. |
| `Source/Version/Version.hxx` | 1–7 | Self-contained declaration/type/namespace consistency; no wire/ABI promise inferred from size_t. |

## New finding index

| ID | Severity / confidence / category | Mechanism and primary complete sidecar |
|---|---|---|
| ADD-SERVER-001 | **High / High / Security** | Upload `shared-id.counter` into an absent counter entry; next startup parses attacker-controlled text and throws. [ServerHandlers.cxx.review.MD](../../Source/Server/ServerHandlers.cxx.review.MD), source 455–476 and Server.cxx 96–101. |
| ADD-SERVER-002 | **Medium / High / Security** | Hello/list/direct-data exports serialize historical lobby messages and member roster to authenticated nonmembers. [ServerHandlers.cxx.review.MD](../../Source/Server/ServerHandlers.cxx.review.MD), source 171–173, 532–540, 613–630. |
| ADD-SERVER-003 | **Low / High / Correctness** | An unfiltered source filename longer than 260 characters throws during frame conversion, skipping normal logging/dumping continuation. [Stacker.cxx.review.MD](../../Source/Tracer/Stacker.cxx.review.MD), source 64–85, 161–175. |

New category totals: Security 2, Correctness 1. Combined owner-local category totals: Correctness 11, Security 5, Testing 2, Memory Safety 1, Concurrency 1, Build 1, Portability 1. High confidence describes explicit static mechanisms; it is not a runtime-reproduction claim.

## Every baseline ID disposition

All rows retain **High confidence**. Exact mechanism, impact, options and original proposed verification remain in the named existing sidecar. S = `Source/Server`, T = `Source/Tracer`, ST = `Source/SystemTests` for the location column only.

| Existing ID | Disposition / severity / category | Fresh contract and reachability comparison; complete report location |
|---|---|---|
| BASE-SERVER-001 | Retain / Medium / Memory Safety | Immediate rejection reset generates no local disconnect; reconnect clears an unreleased allocation. Reset prevents treating the completed flag alone as auth bypass. S/ServerHandlers.cxx:77–130, sidecar. |
| BASE-SERVER-002 | Retain / High / Correctness | Actual ENet fork emits timeout type 4; Shared ignores it, slot reset retains data, subsequent connect loses old attachment and old-ID map resolves B. Pre-auth B has null user data. S/Server.cxx:172–188, sidecar; NET-003 overlap. |
| BASE-SERVER-003 | **Refine** / Medium / Correctness | Cached-ID join ignores nonjoinability; normal client list already filters that flag. Private/type admission is likewise unenforced (no invite graph); grouped under the same admission ID. S/ServerHandlers.cxx:543–578, BASE-ID addendum in sidecar. |
| BASE-SERVER-004 | Retain / Medium / Security | SDK same-lobby rule applies to lobby-ID routing; handler stamps real sender but does not check membership. Direct-user/owner routes do have authorization checks. S/ServerHandlers.cxx:397–452, sidecar. |
| BASE-SERVER-005 | Retain / Medium / Correctness | Server correctly denies non-owner property changes but never calls rollback; all three client consumers apply response values before checking success. S/ServerHandlers.cxx:703–797, sidecar; API-010 overlap. |
| BASE-SERVER-006 | Retain / Medium / Correctness | `Open` gets rather than creates the absent counter; persistent share IDs survive restart, high-water counter does not. S/ServerHandlers.cxx:464–466, sidecar. Distinct from ADD-SERVER-001's namespace violation. |
| BASE-SERVER-007 | Retain / Medium / Correctness | Container rejects already-shared name/new ID or writing fails; server still replies nonzero, client reports success. Debug assertion not generalized to Release. S/ServerHandlers.cxx:464–476, sidecar. |
| BASE-SERVER-008 | **Refine** / Medium / Correctness | Recipient-local request IDs collide only within the popped listener type; affected specific-listener feature gates stated. Wrong interlocutor remains. Rich presence and invitations have contrary handling. S/ServerHandlers.cxx:222–293, BASE-ID addendum in sidecar; API-001 overlap. |
| BASE-SERVER-009 | Retain / Medium / Correctness | Real ExceptionInfo is discarded, default walker captures handler context, dump constructs code zero. Native API contract corroborates; no UEF-recursion premise. T/Stacker.cxx:102–175,207–214, sidecar. |
| BASE-SERVER-010 | Retain / Medium / Concurrency | Direct wrapped-file flush can overlap another syncbuf emission; TLS/local scope accounting does not protect it. T/Tracer.cxx:98,389–415, sidecar. |
| BASE-SERVER-011 | Retain / Low / Correctness | Existing same-second directory returns false, interpreted as setup failure; accepting it unchanged would truncate shared output. T/Tracer.cxx:191–213, sidecar. |
| BASE-SERVER-012 | Retain / Medium / Testing | Log-size snapshot can precede flushed PASS while exit poll follows zero exit; runner fails without terminal drain. Existing hosts do flush. ST/Runner/Main.cxx:136–138, sidecar. |
| BASE-SERVER-013 | **Refine** / Medium / Testing | Unsafe role aliases retained; dot-free persistence groups also collide case-insensitively while scheduler/identity maps compare case-sensitively. ST/Runner/Model.cxx:127–154, BASE-ID addendum in sidecar. |
| BASE-SERVER-014 | Retain / Medium / Build | Chat + typed IDs precede ChatMessageType in 1.106/1.109; host source always compiled regardless of add_test guard. ST/Host/Chat.cxx:8–30, sidecar. |
| BASE-SERVER-015 | Retain / Low / Portability | Native narrow executable/control paths reparsed as UTF-8 fail on non-UTF-8 Windows code pages. Fixed generated argument shapes do not establish generic quoting exploit. ST/Runner/Process.cxx:39–41, sidecar. |
| BASE-SERVER-016 | Retain / Medium / Security | Printed hashed value itself answers challenge; no hash inversion or original secret needed. Conditional log-reader/network access. S/Server.cxx:90–103, sidecar. |
| BASE-SERVER-017 | Retain / Low / Correctness | Null textual callback suppresses the only helper checking dump flag. T/Stacker.cxx:165–175,207–214, sidecar. |
| BASE-SERVER-018 | Retain / Medium / Correctness | Pull passes through negative failure; truthy loop spins and skips sweeps/sleep. Vendor clears event, so no stale-packet double-free proved. S/Server.cxx:172–177, sidecar. |
| BASE-SERVER-019 | Retain / Medium / Security | Transport broadcast chooses connected slots, including challenge-pending ones. Sender gate is not recipient authorization. S/ServerHandlers.cxx:199–210,703–735,923–957, sidecar. |

**Accounting:** 16 retained without substantive scope change + 3 refined = 19 baseline IDs; 0 withdrawn; 0 newly promoted native-lifetime/UEF hypotheses. Reconfirmation addenda do not create new IDs.

## Fresh end-to-end boundary analysis

### Authorization, client fields and direct access

- **Handshake:** ENet connect is not application admission. Key equality sets `completed` before unique ID/user linkage, but rejected transports immediately reset and discard queued commands. No ordinary post-rejection bypass is established. `GalaxyID::IsValid` checks nonzero, not the USER type; a stricter typed identity invariant is desirable, but self-selected LAN identities are the existing design and no external GOG identity compromise is claimed.
- **Decode precedes handler auth:** Cereal can allocate/deserialize response-shaped graphs before the macro executes. BASE-NET-001/002 remain NET-owned input-boundary defects; authorization checks cannot retroactively bound decoding. EventConnect/EventDisconnect are not application wire dispatch cases in `Messages.hxx`.
- **Overwritten fields:** `SetUserData.id`, rich-presence `id`, invitation `user_id`, lobby-message `sender/message_id`, member-data `member_id`, and relayed user P2P identity are server-derived. Chat constructs a new message with real sender/server ID/time; forged message sender/time/room fields are not stored verbatim. Client-supplied room/lobby snapshots in requests are not adopted as server ownership graphs. Hello replaces only the admitted sender's stats and first nickname; shared response reuse serializes synchronously.
- **Chat:** Direct room creation is for requester plus online target; both memberships exist before publication. Reads/sends enforce membership; missing target returns null, unauthorized history returns empty and send returns forbidden. No friend-only chat rule was found in the inspected IChat contract. Self-chat/reconnect retention remains a product/coverage question. Correlation, not member authorization, is 008.
- **Social:** Specific-user requests return whole public LAN snapshots for a mapped target. There is no demonstrated friend/block privacy model to violate merely by direct lookup. Invitation strings are intended opaque data; the server overwrites sender and targets the requested online peer. Rich-presence self-ID gating prevents foreign request IDs consuming a local change listener. Unknown action + supplied success can cause a redundant own-user update notification, not a proved other-user mutation.
- **Files:** Upload/download policy checks exist. Successful download overwrites response bytes/name; denial/miss can echo supplied fields only to their sender, so that is not server-file disclosure by itself. Public SharedFileID download is not documented as owner-only. Container canonical containment blocks the traced escape, although its throwing rejection is NET-002. Global Windows name aliases are UTIL-004. The new reserved-counter attack stays entirely inside the allowed namespace and needs neither issue.
- **Lobbies:** Live messages/member edits require membership; owner data edits check owner, helper properties check both member and owner. Public nonmember metadata refresh is explicitly supported by SDK. Full history/roster export exceeds that purpose (ADD-SERVER-002); missing admission flags/type rules are 003; missing membership on lobby-directed P2P is 004. Retained response fields on error are not assumed to overwrite other users' state: actual consumers were followed.

### Pointer generations, allocation and shutdown

Normal `Connect -> new Data -> peer->data -> ID linkage -> graph membership` has one explicit `Disconnect -> delete Data` retirement. Destructor removes its mapped ID and clears attachment. `Get(id)` follows a reusable raw slot rather than an identity/generation-checked owner. Rejection without cleanup and ignored transport timeout are concrete exceptions (001/002). A smart pointer alone would not repair old-ID resolution or orphan membership.

Ordinary leave removes the peer's lobby link and member key before selecting a remaining owner. Zero members removes the manager entry; FCM/STAR owner leave removes remaining peer links and the manager entry. The live keys view is over lobby member data, which those peer-map removals do not mutate. Duplicate AddMember fails before the peer-link insertion; no normal two-stage-join partial-graph failure was established from an initially consistent graph. Allocation exceptions can interrupt multi-step mutations, but without containment they already escape the server; they are not invented as a continuing corrupt-session interleaving.

Chat disconnect copies the peer's room map, removes both directions and removes empty manager entries. Untimed-out ordinary graphs keep listed peers mapped; null dereferences after timeout/reuse derive from 002 rather than an independently assumed ordinary leave crash. Server destruction lacks an explicit peer sweep, but the shipped infinite-loop executable is not a repeated graceful-destruction caller. Receive-packet cleanup on exception and synchronous outgoing serialization were traced; failed typed Send ownership is NET-004.

### Tracer, exception and stack resources

The original fault record/context never reaches walking/dumping (009). Frame text can exceed its fixed output capacity (ADD-SERVER-003). MiniDump's three allocations survive even success; load/open/export/write failures additionally retain acquired module/file resources. The observed caller is crash reporting; repeated nonfatal snapshots were not established, so no additional high-severity leak is counted. Use stack/context ownership, RAII, error reporting and a best-effort dump path independent of text conversion.

Normal UEF entry destroys its local KeepCount before waiting. The disabled terminate hook is not executable evidence. Microsoft's fault-thread/previous-filter contract does not prove same-thread recursive UEF entry on handler exceptions. Concurrent DbgHelp use is outside the dependency/API contract, but actual simultaneous-fault effects, native filter reentry and DLL-unload continuation were not probed. No speculative deadlock/UAF is elevated. Trace destructor allocations and one-time non-atomic setup remain hardening/contract limits without a separate claimed production interleaving.

## SystemTests, build, performance and portability assessment

All test bodies were inspected, not inferred from scenario names. Strengths include binary NUL/high-byte payloads, sender/ID/value checks, channel 255, history cursors, owner authority after migration, close-cache invalidation, explicit denied file operations, specific/global listener checks and fresh-process exact-bit float persistence. Chat history callbacks are contract-supported: IChat's retrieval listener documentation explicitly authorizes the indexed getter despite the getter's abbreviated remark.

Coverage limits are concrete: two-member orderly lobby lifecycles do not establish three-way migration/timeout-slot reuse; direct-user P2P and offline metadata queries do not test outsider lobby-ID routing; 750 ms quiet windows are finite, and leave-send ignores its scheduling result. Share “persisted roundtrip” does not restart the server. Existing tests do not exercise the reserved filename, whole-lobby confidentiality, equal-type crossed chat request IDs, rejected property rollback or corrupt counters. These gaps are not extra defect IDs.

Protocol/model/process/config were all read: strict field/event checks are useful, but filesystem aliases (013), terminal log draining (012) and path encoding (015) undermine harness trust. Cycles time out rather than falsely pass; integer narrowing and probe-before-bind port selection are local robustness limits. CTest RUN_SERIAL/resource lock reduces inter-test port collisions, not interference from unrelated processes. Host PASS explicitly `_Exit`s; normal SDK shutdown/static teardown are outside its guarantee. The WebSocket echo body does not close its channel, while the separate close test is x64-gated. No native provider lifetime was inferred from these tests.

CMake's registered scenario matrix cannot protect an always-compiled unsupported type (014). Server/Tracer/Version target wiring was traced, including C++20, versioned Shared, Windows dependencies and updater-before-compilation. Version's source-tree header/temp generation is shared between build trees and changes only differing content on the MSVC script path. It is build metadata, not a unique protocol/build identity guarantee. Alternative Windows toolchains, concurrent build trees and read-only source trees remain BUILD validation work.

No latency/memory benchmark was run. Snapshot history growth and packet caps remain NET-006; the new confidentiality issue exists even with one short message. The server's unbounded positive-event drain is a fairness question separate from confirmed persistent-negative spin 018. Platform conclusions are Windows x86/x64 source/contract analysis; Linux branches were inspected only as text.

## Cross-owner handoffs and deduplication

| Owner | Evidence / requested reconciliation |
|---|---|
| NET | BASE-SERVER-002 integrates BASE-NET-003's missing timeout dispatch; one integrated lifecycle repair, not two independent global counts. Handle both disconnect event kinds and validate generations. Keep NET-001 pre-auth allocation, NET-002 handler/path exceptions, NET-004 rejected-send ownership and NET-006 history budgets with NET. ADD-SERVER-002 needs public/member DTO separation and schema compatibility; a recipient fix does not by itself bound history. |
| API / CORE | BASE-SERVER-008 overlaps BASE-API-001's chat correlation; same receiving listener type is required. BASE-SERVER-005 overlaps BASE-API-010 rollback/cache semantics. Agree on request versus unsolicited event shape and nonexistent-lobby handling. ADD-SERVER-002 must not be “fixed” by client-only filtering; client cache refresh behavior also needs reconciliation. No new count for already-owned borrowed-chat-view or callback lifetime concerns. |
| UTIL / STORAGE | ADD-SERVER-001 is server control/upload namespace policy; use normalized namespace separation and safe counter recovery. BASE-SERVER-006/007 need metadata/high-water/commit/error consistency. Windows file aliases remain BASE-UTIL-004, not another SERVER ID. Empty-file success/denial and local upload-copy error semantics remain STORAGE contract work. |
| BUILD | BASE-SERVER-014's early-chat host compilation requires feature-boundary verification. Version updater race/read-only-source/alternative-toolchain questions remain cross-tree build validation; no updater was run. Existing successful baseline builds are not repeated or represented as new checks. |
| Coordinator / CORE / INTERCEPT | Reconcile tracer one-time initialization/teardown ownership across linked DLLs before asserting native unload/filter lifetime faults. ADD-SERVER-003 proves text conversion interruption without that premise. DbgHelp serialization and original-context dump verification require isolated Windows probes. No cross-owner reports edited. |

## Actual operations, limits and proposed verification order

Actual non-mutating terminal operations before report writing: `git rev-parse --short=8 HEAD` returned `48cea8c6`; `git status --short` showed the pre-existing untracked `.ai/review-addendum/`; scoped `git diff b30e83872c0006e8240c8b4f565da5351bf10080 -- Source/Server Source/SystemTests Source/Tracer Source/Version ':(exclude)*.review.MD'` was empty. Extension-filtered `git ls-files` returned exactly the 43 ledger paths. Dedicated Read/Glob/Grep supplied source/context/report inspection; AGENTS.md search found none. All report edits used `apply_patch`.

Contract context actually inspected includes Shared Networking/dispatch/messages, Lobby/manager, ChatRoom/manager, SharedFileUtils and selected IniData; Shared_NoVer filesystem container/entry/path routines, message IDs and public default configuration; selected Client Chat/Friends/Matchmaking/Storage/registrar consumers; SDK 1.152.11 matchmaking/networking/chat/storage/ID contracts and 1.109.0 chat signature; feature definitions; actual vendored ENet wrapper/reset/timeout/service/broadcast and StackWalker/Boost fixed-string code. Scenario context: three-peer P2P, leave-revokes-routing and durable-stats JSON. Root/Source/Shared CMake and both Version updater scripts were read as context. Unread portions of context-only files are not additional coverage.

Read-only web contract checks: Microsoft [SetUnhandledExceptionFilter](https://learn.microsoft.com/en-us/windows/win32/api/errhandlingapi/nf-errhandlingapi-setunhandledexceptionfilter) and [MiniDumpWriteDump](https://learn.microsoft.com/en-us/windows/win32/api/minidumpapiset/nf-minidumpapiset-minidumpwritedump). The obsolete dbghelp-header MiniDumpWriteDump URL returned 404; the linked minidumpapiset page was fetched successfully. No remote server/SDK behavior was tested.

**Execution limits:** no configure/build/test, server/client/probe, sanitizer, fuzzer, analyzer, crash injection, Linux execution, updater, production/config edit, credential access or Git mutation. Existing reports and user work were preserved. Static complete reading is not a claim of exhaustive defect discovery, measured exploitability or native-runtime reproduction.

Proposed verification order:

1. Fresh/absent counter + reserved-name upload + restart; then corrupt counter recovery and ID preservation (ADD-SERVER-001, 006/007).
2. Timeout before application sweep + slot reuse + old-ID query before/after new admission; ordinary rejection/disconnect controls (001/002 with NET).
3. Decode hello/list/direct-data for member/outsider/former member; check no member history/roster leakage while public metadata remains supported (ADD-SERVER-002).
4. Cached-ID nonjoinable/private join, both P2P routing forms, rollback replies, equal-ID same-type chat callbacks and pending-handshake broadcast recipient tests (003–005,008,019).
5. Terminal-log scheduling probe, Windows role/group alias cases and non-ASCII argument round trips; compile only the justified SDK feature boundaries after remediation (012–015).
6. Bounded frame conversion at 259/260/261/1023 characters and an isolated original-context Windows dump; all dump/log flag combinations and synchronized trace flushes (ADD-SERVER-003,009–011,017).

No owned source file is unfinished. Open questions are product policy for explicit open-LAN/private-lobby compatibility, self-chat/reconnect retention, simultaneous crash handling and build-tree generation isolation; their uncertainty does not replace the concrete defects above.

### Final artifact checks

Read-only reconciliation of the ledger's exact paths against extension-filtered Git inventory returned **Owned=43, Covered=43, Differences=0**. Separate index counts returned **19 BASE rows and 3 ADD rows**; owned sidecars contain exactly three ADD finding headings (two ServerHandlers, one Stacker). Scoped `git diff --numstat` shows **11 existing SERVER-owned sidecars appended, zero removed lines**; this notebook is the one new SERVER artifact. `git diff --check` was clean, and the scoped baseline source comparison remained empty. Final status also showed concurrent changes in other owners' reports; those were left untouched. These are report/source-integrity checks, not product tests.
