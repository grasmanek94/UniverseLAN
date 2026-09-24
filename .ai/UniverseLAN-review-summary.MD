# UniverseLAN — full baseline review and thorough follow-up

## 1. Executive summary

**Reviewed baseline:** `feature/fix-issues` at **`b30e83872c0006e8240c8b4f565da5351bf10080`**. Review destination: `feature/ai-review`. This assessment replaces the previous review; its findings were established afresh from the current implementation and SDK/dependency contracts.

**Latest follow-up:** [Thorough review addendum](review-addendum/SUMMARY.MD), starting from review commit `48cea8c6`, re-inspected the same 529 inputs and preserves the baseline evidence. It adds **23 distinct confirmed groups (3 High, 19 Medium, 1 Low)**, clarifies existing findings and records focused local Windows ASan-enabled checks. This is ordinary C++ correctness/API/persistence review, with isolated local validation.

**Single findings index:** [ALL-FINDINGS.MD](ALL-FINDINGS.MD) lists all 132 canonical groups (126 actionable and six informational/conditional investigations) and maps the eight duplicate IDs that are excluded from the group count.

**Coverage: 529/529 in-scope files, with 529 new per-file reports and an architecture assessment.** The inventory includes Client, Client_NoVer, Shared, Shared_NoVer, Server, SystemTests, Tracer, Version, root/Source CMake, all DLL version dispatchers/markers/manifests, and the eleven direct Vendor build manifests. InterceptionLogger received the requested shallow scan for serious defects. Every distinct implementation was read; repetitive empty wrappers and identical dispatchers were verified by Git blob identity with individual coverage records.

**Current result after reconciliation: 126 actionable finding groups — 24 High, 89 Medium, 13 Low — plus six informational/conditional investigations.** There are 134 confirmed finding records; eight whole-record aliases are counted once. The baseline contributed 103 groups and the follow-up adds 23. Partial overlaps retain separately actionable mechanisms. These totals are review findings, not a count of runtime reproductions or a claim that every possible defect has been found.

The principal risks are listener cancellation/teardown, unsafely shared cache values, loss or false acknowledgment of saved data, pre-authentication deserialization, and incomplete ENet peer retirement. The interceptor adds proxy ownership, callback-versioning and trace-buffer issues. These warrant targeted fixes before a reliability sign-off, particularly for irreplaceable saves or peers outside a trusted private LAN.

**Execution evidence:** all **15 Windows x64 Debug client/server/interceptor targets** built across SDK **1.57.0, 1.124.0, 1.139.2, 1.148.3 and 1.152.11**. Three independent runtime probes against the built code reproduced lost serialized play time, the Windows timestamp epoch error and failed-delete/index divergence. Other findings remain code/contract conclusions with proposed verification.

**Follow-up execution:** isolated ASan-enabled x64 probes reproduced the wrong legacy SDK 1.73.0 callback, inconsistent quota headroom and metadata-name conflict. ASan also detected the borrowed-key erase/copy use-after-free mechanism, which remains a conditional SDK-compatibility finding rather than a counted confirmed API defect. Full results and limits are in [addendum verification](review-addendum/VERIFICATION.MD).

## 2. Scope, environment and limitations

- Mandatory method: `.ai/SKILLS/CppReviewer.md`; exclusions and Windows focus from `.ai/ai-instructions-review.txt`, with the user's latest branch/replacement/publication instructions taking precedence.
- Pulled the source branch and incorporated it in merge `40265aed370464569e873692ef5d53fbdb12679b`. `git diff` verifies that every reviewed source/build input matches `b30e8387` exactly. No production implementation was changed for this review.
- Compiler environment: CMake 4.2.1, Visual Studio 18 2026, MSVC 19.51.36252.0, Windows SDK 10.0.26100.0. Exact commands/results: [VERIFICATION.MD](review-baseline/VERIFICATION.MD).
- Excluded implementation trees: EnetTest, BehaviourTests, TestCases, TestCommon, UnitTests, nested Vendor source and the named excluded root directories/tools. Selected SDK/vendor/test declarations were consulted only as contract/dependency context where necessary.
- Credential files were not accessed, copied or committed. Real proprietary GOG DLLs were not required for compilation and were not executed. No Linux, x86, Release, all-69-version, fuzzing or game-runtime test was performed. The initial review had no sanitizer execution; the follow-up adds the explicitly scoped local ASan probes described above.
- Existing CI workflows are explicitly out of scope. There is no CI certification. Local passing compilation does not resolve callback timing, proprietary allocation lifetime, output truncation behavior or dynamically resolved export names.
- Unsupported hosted-service features (for example successful leaderboard operations) and deliberate LAN configuration were not automatically classified as defects or vulnerabilities.

## 3. Codebase map and architecture assessment

### Build-time structure

The feature matrix selects declarations for each Galaxy SDK. Per-version Client/Shared/Server/Interception targets link version-independent utilities rather than duplicating them. DLL marker files and identical x86/x64 dispatchers instantiate that common graph. Dependency sources are vendored; the MbedTLS/TF-PSA-Crypto and zlib bridges resolve actual build targets. ROOT/bin deployment and generated resources in the source tree are intentional conventions, with limitations for read-only/concurrent builds.

### Runtime flows and current weaknesses

1. **Initialization and exported API:** SDK exports create facade interfaces around configuration, shared user data, local filesystem containers and a transport client. Error reporting and partial-initialization cleanup do not consistently follow the SDK contract. The game-server packet role also differs across API generations.
2. **Network processing:** ENet service and application dispatch are separate stages. Framed Cereal messages become typed handler calls; authentication is checked inside handlers, after collection decoding. The fork's timeout event is not handled as a retirement event. Peer-slot pointers need application generation/lifetime ownership, not just ENet address identity.
3. **Callbacks:** Requests use specific-listener maps, global listener snapshots, direct deferred lambdas, WebSocket-held pointers and private auth collections. There is no single cancellable operation lifetime across all those routes. Shutdown during a callback can destroy the active pump; a queue mutex alone cannot repair that ownership problem.
4. **State and cache coherence:** The server is authoritative for lobby/user state, while clients hold derived search/member/session caches. Rejection, refresh and disconnect must reconcile those caches. Server events and request replies also need recipient-local correlation instead of reusing another process's sequence number.
5. **Persistence:** File bytes, metadata and indexes are independent mutable artifacts. Status is lost at multiple layers; replace/delete/copy can partially commit. A reliable solution must combine staged replacement, checked close/save results and publication/rollback, then propagate outcomes to SDK callbacks.
6. **Interception:** A versioned facade dynamically resolves the native DLL and owns observers/proxies. Proxy bookkeeping is process-wide while native registrars are session-specific. Cancellation and completion need a single retirement owner; internal observers must detach before native shutdown. Trace lengths must use readable capacity, not the native API's reported total object size.

These are observable lifecycle, correctness and reliability problems, not style objections to facades, raw pointers, singleton configuration or static libraries.

## 4. Findings summary

### Prioritized High groups

The follow-up adds **ADD-ABI-001** (incompatible legacy listener dispatch), **ADD-UTIL-001** (stale file membership/removal can delete replacement data), and **ADD-SERVER-001** (user-file and internal-counter namespace overlap). See [the addendum](review-addendum/SUMMARY.MD) for full dispositions and proposed corrections. The table below retains the baseline High groups.

| IDs | Principal failure | Detailed evidence |
|---|---|---|
| BASE-CORE-001, 002, 003 | Queued/snapshotted callbacks survive cancellation; callback-time shutdown destroys an active dispatcher | [CORE](review-baseline/CORE.MD) |
| BASE-API-002; BASE-UTIL-002 | Supported Copy/scalar APIs and snapshots race mutable nickname/stat/user-data storage | [API](review-baseline/API.MD), [UTIL](review-baseline/UTIL.MD) |
| BASE-API-015; BASE-STORAGE-009, 013, 017 | WebSocket, direct cloud, late worker registration and private auth listeners remain callable after cancellation | [API](review-baseline/API.MD), [STORAGE](review-baseline/STORAGE.MD) |
| BASE-STORAGE-001, 002, 005 | Cloud saves can be destructively replaced, failed I/O acknowledged, and guarded deletion performed without checking the expected hash | [STORAGE](review-baseline/STORAGE.MD) |
| BASE-NET-001, 002, 003 | Untrusted archive lengths allocate before validation/auth; handler exceptions escape; omitted timeout retirement enables stale peer-ID resolution | [NET](review-baseline/NET.MD), [SERVER](review-baseline/SERVER.MD) |
| BASE-INTERCEPT-002, 003 | Proxy completion/cancellation competing ownership and cancellation through the wrong native session | [INTERCEPT](review-baseline/INTERCEPT.MD) |
| BASE-INTERCEPT-004, 005, 006, 007 | Lost auth/version-specific callbacks, trace-buffer overreads, and resolving exports absent from the selected SDK | [INTERCEPT](review-baseline/INTERCEPT.MD) |

### Medium and Low areas

The complete indexes in the notebooks cover lobby filters/refresh/rollback/joinability/P2P authorization; recipient-local chat correlation; file-share IDs/owner/empty-file semantics; cloud callback snapshots/savegroup IDs/hash production; stat averages/save retry; auth state/deadlines; filesystem case/link identity, timestamps and error paths; startup/diagnostics; and SystemTests process/path/version-boundary behavior. Each locally owned substantive finding has location, evidence, mechanism, impact, possible solutions, recommended resolution and verification in its adjacent source report.

Canonical primary-category counts (mixed labels normalized to their primary category):

| Category | Groups |
|---|---:|
| Correctness | 73 |
| API/ABI | 19 |
| Memory Safety | 11 |
| Concurrency | 10 |
| Security | 5 |
| Performance | 2 |
| Portability | 2 |
| Testing | 2 |
| Build | 2 |
| **Total** | **126** |

### Reconciliation rules

[RECONCILIATION.MD](review-baseline/RECONCILIATION.MD) contains code evidence for the following exact aliases:

- BASE-SERVER-002 → BASE-NET-003 (omitted timeout event; integrated severity High).
- BASE-API-010 → BASE-SERVER-005 (rejected lobby-setting rollback).
- BASE-NET-008 → BASE-STORAGE-011 (failed achievement persistence/retry).
- BASE-STORAGE-012 and BASE-STORAGE-022 → BASE-UTIL-002 (shared lock-escape root).

Other partial overlaps are explicitly preserved: nickname writes outside the stats container; unsolicited chat completions beyond ID collisions; direct cloud captures and pre-event WebSocket listener retention beyond the generic queue. Their fixes are coordinated without claiming one small change closes all paths.

The follow-up's [reconciliation ledger](review-addendum/RECONCILIATION.MD) adds aliases ADD-NET-001 → BASE-SERVER-019, ADD-NET-004 → BASE-SERVER-008, and ADD-UTIL-002 → BASE-SERVER-007. These expand evidence without inflating the new-group count.

**Two informational records are excluded from actionable totals:** BASE-API-018 depends on unestablished nested-pump guarantees; BASE-UTIL-015 is latent RED-prefix integration debt with no current SDK directory activating it. BASE-INTERCEPT-001 is Medium for a proven teardown-contract violation; native registrar destruction/use-after-free remains conditional, not a proven High crash.

**Four further follow-up records are excluded:** ADD-API-001 borrowed-key aliasing, ADD-API-002 zero-as-self callback convention, and ADD-STORAGE-001 producer-callback reentrancy need stronger contract evidence; ADD-UTIL-004 concerns a dormant helper route. The ASan mechanism result for ADD-API-001 does not establish the missing SDK permission.

## 5. Detailed reports and complete coverage

Each reviewed file has a new sibling `<filename>.review.MD`. The previous reports' assertions were not reused as findings. A file with no confirmed local defect has concrete inspection notes and relevant cross-component dependencies; it is not a certificate of correctness.

| Workstream | Inputs | Notebook |
|---|---:|---|
| Client facade/lifecycle and Client_NoVer | 30 | [CORE.MD](review-baseline/CORE.MD) |
| Multiplayer/client API | 10 | [API.MD](review-baseline/API.MD) |
| Storage/stats/user/other client API | 14 | [STORAGE.MD](review-baseline/STORAGE.MD) |
| Shared models/config/transport/messages | 59 | [NET.MD](review-baseline/NET.MD) |
| Shared_NoVer utilities/persistence | 40 | [UTIL.MD](review-baseline/UTIL.MD) |
| Server/SystemTests/Tracer/Version | 43 | [SERVER.MD](review-baseline/SERVER.MD) |
| InterceptionLogger, shallow serious-defect scan | 73 | [INTERCEPT.MD](review-baseline/INTERCEPT.MD) |
| Build controls and wrapper matrix | 260 | [BUILD.MD](review-baseline/BUILD.MD), [WRAPPER-COVERAGE.MD](review-baseline/WRAPPER-COVERAGE.MD) |
| **Total** | **529** | **No missing or extra baseline sidecars** |

Each owner also recorded fresh reread coverage and BASE-ID dispositions in [review-addendum](review-addendum/SUMMARY.MD). The coverage checker reconciles all eight owner sets, with verified identity for the repetitive wrapper/dispatcher files. The targeted ABI notebook is a cross-owner handoff, not an expansion of the 529-file inventory.

## 6. Testing, build, security, performance and portability

**Follow-up coverage assessment:** [TEST-COVERAGE-GAPS.MD](review-baseline/TEST-COVERAGE-GAPS.MD) maps all 27 fix-branch commits to existing tests and missing regressions. It also corrects an earlier coverage statement: two existing message-serialization tests already assert nonzero play-time preservation; running/enforcing those tests is the immediate gap.

- **Build:** The five-version x64 Debug matrix passed for all three production components; this provides evidence of current source compatibility, not binary or behavioral equivalence with GOG. No hardcoded version-specific CMake logic was added.
- **Tests:** Three review-only probes reproduced concrete baseline failures using real built code. They are bug reproductions, not passing fixed-behavior tests. Existing excluded test cases were not reused. Additional cancellation, peer reuse, denied/full-volume writes and multi-pending-callback regressions are proposed locally beside findings.
- **Follow-up local checks:** MSVC ASan-enabled helper programs exercised actual registrar and persistence code for the stated scenarios. No full sanitizer-suite pass is claimed. Instrumentation/setup failures were corrected in the external harness and documented separately from production findings.
- **Security:** Authentication checks occur after archive decoding; application exceptions need containment; broadcasts/logs must respect authentication and credential boundaries. No real credentials were read or emitted. Intentional shared-key LAN defaults were assessed in their context rather than treated alone as a universal compromise finding.
- **Performance:** ENet's packet/waiting-data ceilings do not bound later application queues, archive-declared allocations or accumulated state snapshots. No benchmark, percentage improvement or measured throughput claim is made.
- **Portability:** Windows path case, code pages, file-clock epoch and handle-sharing behavior matter directly. Non-Windows guards were inspected only; no Linux compilation or runtime assertion is offered.
- **CI:** Workflows are excluded. The review does not assert that repository CI covers this matrix, sanitizer scenarios or failure cases.

## 7. Positive engineering practices

- Centralized feature flags and reused version-independent libraries keep a broad SDK surface tractable; identical dispatcher verification and the successful representative builds support that structure.
- Packet guards, shared message ownership and bounded string-copy helpers eliminate several basic lifetime/buffer errors in ordinary paths.
- Several indexed accessors check bounds; file-share workers now have joining ownership and normal teardown preserves their dependencies.
- Portable and legacy metadata decoding, canonical path checks, error-code filesystem probes and clear per-operation messages provide useful foundations, though they need transaction and trust-boundary guarantees.
- The in-scope SystemTests model exercises observable callbacks/state, isolated processes and timeouts. Its own edge cases are reviewed rather than using test existence as proof of correctness.

## 8. Remediation roadmap

1. **Immediate:** unify cancellation-aware operation ownership, pin dispatch targets, defer destructive shutdown until pumps unwind; repair interceptor proxy/session retirement. Bound pre-auth decode, contain expected handler failures and handle ENet timeout retirement. Preserve old saves on every failed replacement and enforce conditional delete hashes.
2. **Near term:** return locked snapshots from mutable caches; centralize peer/session generation and exactly-once disconnect; reconcile lobby/cache rollback and request/event identities. Make filesystem bytes/metadata/index changes transactional and propagate actual results all the way to listeners.
3. **Compatibility/diagnostics:** correct interceptor callback/export gates, SDK error/lifecycle behavior and output trace extents; address Windows clocks/path identities and restore original exception context in diagnostics.
4. **Validation:** convert reproduced defects into regression cases, then add targeted adversarial/fault/concurrency tests from the sidecars. Expand to x86/Release and additional SDK boundaries where the changed implementation warrants it. Keep dormant RED behavior an integration requirement when a qualifying SDK is actually added.

## 9. Open questions and final checks

Native SDK allocation lifetime, nested ProcessData guarantees, exact cloud hash compatibility vectors, required mixed-SDK wire compatibility and all-version ABI/export behavior remain explicit validation questions. No unsupported answer was used to promote a speculative runtime crash to a reproduced defect.

`python .ai/review-baseline/verify_review.py` verifies the 529-file inventory, per-file baseline markers, ID/severity accounting, report links, whitespace and unchanged production inputs. Final validation reports **zero errors**. Git whitespace checks also pass. Commit/push identity is reported in the delivery response; generated binaries and temporary probes are excluded from the review commit.

For the latest addendum, the checker also validates the expanded finding ledger and all follow-up coverage paths. The existing published baseline commit is `48cea8c6`; new addendum publication status is reported separately in the delivery response.
