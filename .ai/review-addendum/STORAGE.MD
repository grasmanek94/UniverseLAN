# STORAGE — full source-first re-review addendum

## 1. Executive summary

**Completed: 14/14 assigned files, 5,203 source/header lines, including every feature-guarded branch.** Production baseline is `b30e83872c0006e8240c8b4f565da5351bf10080`; observed HEAD is `48cea8c6c48fa41fddd348a0119129cc5643fc8b`. The scoped source comparison and the broader non-review `Source` comparison against that baseline were empty. Windows is the assessment focus. This is static review, not a runtime reproduction or release certification.

**Five genuinely additional findings, all Medium severity / High confidence**, were appended to owned implementation sidecars:

1. Reentrant callback uploads overwrite another invocation's TLS scratch bytes.
2. Downloaded bytes and returned save metadata can belong to different successful generations.
3. Independent 32-bit quota clamps report zero headroom on healthy large volumes.
4. Presence-only remote-user placeholders satisfy playtime retrieval as if hydrated.
5. Older SDK remote user-data completion is compiled out by the wrong listener gate.

**All 23 prior STORAGE IDs remain supported. Six have clearly marked BASE-ID addendum corrections/expansions; zero are withdrawn and no severity is changed.** Local accounting is therefore **28 IDs: 8 High, 20 Medium**. New primary categories are four Correctness and one API/ABI; the sidecars also identify concurrency/reentrancy aspects. These are owner-local counts, not a replacement for coordinator cross-owner deduplication. Existing findings are preserved verbatim above the appended material.

The strongest existing risks remain failed-save destruction, false persistence/deletion success, ignored conditional-delete guards, and cancellation/borrowed-state lifetime failures. New findings show that even successful operations need per-invocation buffers, coherent data/metadata generations, and domain-specific cache availability. The implementation has useful bounded copies, checked indexes, shared filesystem ownership, explicit worker joining and binary happy-path SystemTests; those do not establish operation-level consistency.

Recommended next step: repair the shared operation/commit model, then extend focused Windows verification to nested callbacks, successful concurrent replacements, quota headroom, legacy completion gates and unhydrated remote caches. Unsupported leaderboards/images/overlay, simulated tokens and invalid caller inputs were not counted as confirmed new defects.

## 2. Scope, method, environment and limits

- Instructions followed: `.ai/SKILLS/CppReviewer.md` and `.ai/review-addendum/PLAN.MD`.
- All 14 assigned implementations/declarations were read fully **before** reading `.ai/review-baseline/STORAGE.MD` or their 14 existing sidecars. SDK contracts, filesystem helpers, server handlers, messages, registrar, queue and explicit lifecycle were traced before baseline reconciliation. The retained notes below record independent conclusions and counterevidence, not just prior-ID validation.
- Read-only Git identity/status/diff operations and dedicated Read/Glob/Grep supplied evidence. No build, test, sanitizer, executable probe, source edit, Git write, branch change, credential-file access or real-service request was performed. All report edits used `apply_patch`.
- The initial status showed the existing untracked addendum directory. Other owners' report modifications appeared during work; only these 14 owned sidecars and this new report were edited by this review.
- SDK/vendor files are contract/dependency context only. SystemTests were inspected as verification evidence, not edited or run. Other owners retain first-party dependency findings. No Linux runtime conclusions are made.
- Source mechanics are high-confidence under the stated sequences; shipped-game frequency, native Galaxy hash vectors, every SDK ABI, Windows CRT failure diagnostics, and timing/durability behavior remain unmeasured.

## 3. Exact coverage and fresh independent notes

Every row is a complete first-line-through-EOF reread, not sampled or inferred from a prior report. Every corresponding `<path>.review.MD` received an explicit re-review addendum. No assigned file is unfinished.

| Assigned path | Lines | Fresh inspection / disposition |
|---|---:|---|
| `Source/Client/Impl/Apps.cxx` | 1-133 | DLC installed/owned, both language pointer/copy pairs and all gates. IniData returns stable member references, not temporary strings. Ownership forwards the listener on both paths. Configured entitlement and product-language policy are compatibility limits; NET owns mutating unknown-DLC lookup and CORE owns partial-Init access. No new local ID. |
| `Source/Client/Impl/Apps.hxx` | 1-94 | All defaults, product widths, virtual signatures and initialization remark. Latest SDK excepts ownership from post-Init-error availability; the copied broader remark does not prove a crash. Gates checked at 1.88.0/1.151.0/1.152.2. No new declaration defect. |
| `Source/Client/Impl/CloudStorage.cxx` | 1-649 | Both Get/Put/hash overloads, metadata-only Get, list/index getters, deletion and savegroup lifecycle. Added 001-003. Expanded BASE-002/003/006. Verified error callbacks versus actual bytes, callback/stream extent, TLS reentrancy, generation timing, implicit/explicit hash storage and held parent ownership. |
| `Source/Client/Impl/CloudStorage.hxx` | 1-366 | Complete conditional API surface, optional hash/timestamp/save type, callback-only state, plain mode flag/atomic counter, non-owning dependencies. Caller buffer lifetime through completion is required; signed callback chunk extent is a separate implementation responsibility. Implementation sidecar is canonical for additions. |
| `Source/Client/Impl/Stats.cxx` | 1-504 | Local and remote requests, numeric/average-rate operations, all achievements and enumeration, all leaderboard variants, playtime fast path. Added 004. Missing achievements are created by the helper; no null dereference/uninitialized getter output follows merely from a missing name. Positive finite deltas alone establish BASE-010. |
| `Source/Client/Impl/Stats.hxx` | 1-640 | All retrieval/mutation/store/reset preconditions, pointer versus Copy contracts, leaderboard range/order/details/force-update signatures and listener version gates. No successful leaderboard result exists to satisfy success-only getter preconditions. Playtime success must establish availability rather than mere identity presence. |
| `Source/Client/Impl/Storage.cxx` | 1-340 | Every local/shared wrapper, ID/name overload through Shared, offsets/counts/close, worker admission/compaction/teardown, upload and download replies. BASE-016 expanded through 32-MiB send rejection. Upload convenience-cache mismatch alone is narrowed by the SDK's download-first shared-read precondition. |
| `Source/Client/Impl/Storage.hxx` | 1-274 | Joining worker and shared completion-flag ownership, declaration defaults, portable UTF-8 relative-name preconditions, asynchronous listeners and download-first metadata/data access. Moved-from jthread slots and the lambda's flag ownership refute a superficial compaction/destruction-order UAF. No new header ID. |
| `Source/Client/Impl/Telemetry.cxx` | 1-211 | Constructor/disabled sink, all primitive/object/array/clear/sampling writes, send/anonymous send, visit pointer/copy/reset and flush. Valid null array names retained as 021; failed-insertion/pre-lock state race made concrete under 023. No remote sampling/transport requirement invented for the local trace. |
| `Source/Client/Impl/Telemetry.hxx` | 1-232 | Six nullable name contracts, recursive mutex, atomic IDs, sink-state absence, visit methods and version gates. Counter atomicity does not protect stream flags or multi-call event state. No new declaration-only mechanism. |
| `Source/Client/Impl/User.cxx` | 1-673 | Every auth variant and gate, sign-out/runtime queries, user-data retrieval/copy/index/set/empty-delete, ticket/token/session simulation, network updates, lazy user cache and waiting-auth drain. Added 005 for historical global completion; BASE-019 admission/acceptance gap expanded. |
| `Source/Client/Impl/User.hxx` | 1-814 | All old/new overloads and macro renames, defaults, external-service optional parameters, listeners, type aliases, output/buffer and state contracts. Global specific-user listener availability is distinct from the later per-operation argument. Pending-auth mutex protects its set, not the atomicity of state inspection/admission. |
| `Source/Client/Impl/Utils.cxx` | 1-97 | Both image calls, notification variants, overlay actions/state, service state/callback mapping. No image write/size arithmetic; avatar producer returns unavailable/0. URL is printed, not executed. Pre-login service state is explicitly undefined. No new confirmed local ID. |
| `Source/Client/Impl/Utils.hxx` | 1-176 | Legacy RGBA/notification types, consumable gate, image/overlay preconditions and non-owning members. Arbitrary IDs do not create valid-resource guarantees. Value-only global service notifications avoid a per-call capture at this site. No new declaration defect. |

## 4. End-to-end flow and operation boundaries

### Local and cloud filesystem

`InterfaceInstances::internal_reset` creates SharedFileUtils at the configured game-data path (`UniverseLAN.cxx:18-25`). SharedFileUtils constructs Local/Shared/Cloud/Avatars roots (`SharedFileUtils.cxx:25-30`); cloud calls acquire named or nameless owned subcontainers (`filesystem_container.cxx:434-461`). Entries have separately encoded data and metadata paths; container maps/indexes own entries while entries retain a raw parent back-pointer. Streaming Get captures the subcontainer shared_ptr, so its parent does remain alive during ordinary queued execution.

Local FileWrite creates/gets and writes; FileRead returns actual `gcount`; FileDelete calls unlink. Name/ID lookup and index bounds were followed through Shared, not inferred from facade pointer parameters. Creation can publish ghost entries, unlink can remove indexes despite failed deletion, and writes can return before implicit close error is checked; these lower-layer mechanisms already belong to UTIL.

Both cloud puts do data I/O synchronously and queue only completion. Callback put opens/truncates before rewind/read, loops on signed callback counts using one TLS array, then writes timestamp/type/ID/hash metadata and queues success before stream destruction. Buffered put checks the data helper's boolean but ignores metadata persistence. Callback Get queues the actual read and sink call, then samples metadata; buffered Get reads immediately after size validation and queues completion. Metadata-only Get queues zero downloaded bytes **as required** by SDK `ICloudStorage.h:88`; zero there is not a bug. List and legacy metadata state are shared members populated before result dispatch (BASE-007).

These are distinct state boundaries: file membership, physical bytes, metadata, a retrieved callback snapshot, and a completed operation. Shared pointers preserve object lifetime, not equality among those states. ADD-002 demonstrates successful-operation generation mixing; ADD-003 demonstrates quota fields losing their relationship even when filesystem queries succeed.

### Server-mediated file sharing

`FileShare` checks policy/existence, launches a jthread, and only inside it registers a request and reads/serializes the entire file (`Storage.cxx:137-196`). `SendAsync` serializes immediately and returns queue admission. Tick dispatch can later drop that packet on native Send failure (`Networking.cxx:123-131`). The 32-MiB native maximum applies to the serialized packet, not only its payload; normal fragmentation does not override it.

Authenticated server upload allocates/persists an ID attempt, creates the shared entry and writes data, then returns the ID even on failure (`ServerHandlers.cxx:455-477`). Request/download reads by ID/name and returns filename/data without a found/error or owner field (`479-511`, `FileRequestMessage.hxx:14-32`). Client download tests nonempty payload, creates/writes its cache and dispatches a result; upload response tests nonzero ID and populates a convenience cache from the current local file. Empty-file/error ambiguity, false server acknowledgement, global filename collisions and restart counter failures require protocol/server coordination, not a client-only `empty()` workaround.

The successful Download precondition limits claims about direct reading of upload convenience-cache contents. A later successful download normally overwrites that cache from the server, so no new finding is assigned merely because the local original changes during the upload round trip.

### Stats, user cache, and authentication

Self aliases resolve to the configuration-owned user. Remote lookup creates shared placeholder objects; map presence is not evidence of retrieved domains. Server Hello broadcasts full snapshots, specific requests return full stats/user/nickname data, and SetUserData stamps the authenticated sender. Therefore assigning a whole `asuc` on a user-data response is not a proven field-loss defect merely because the method name says UserData: this protocol actually carries the whole object. ADD-004 is instead the concrete missing-hydration check; ADD-005 is missing callback dispatch in a supported older branch.

Stats Store/Reset and User Set/Delete call INI persistence, then queue network updates/results. INI save results and dirty acknowledgements are already BASE-011 / BASE-NET-008. Complete scalar reads/mutations and Copy operations escape their container locks (012/022); pointer-return exceptions do not excuse those thread-safe APIs. Float persistence intentionally transports/stores union bits: there is no evidence here of a numeric float-to-int truncation on Windows. Union/archive/clock semantics remain UTIL-owned.

All ordinary auth wrappers converge on configuration policy plus runtime `logged_on`; sign-out does not perform a state transition. Pending listeners live in a separate raw-pointer set. Unregistration, acceptance, admission, sign-out and deadlines are not one operation lifecycle. The 019 addendum adds the lost-admission interleaving even with a healthy server; ignored explicit timeout is independently confirmed only where the argument exists (from 1.152.8).

### Callback lifetime, failure and reentrancy

`ProcessData` processes network events before draining DelayRunner (`GalaxyDLL.cxx:166-173`). Tick queues events; it does not directly execute User/Stats listeners. The registrar copies `const char*` arguments through NotificationParamScopeExtender, so queued container/name/save-ID/event-type strings are not dangling temporary-string findings. Supplied listeners remain raw pointers; cancellation must reach ordinary queued completions, the direct cloud lambda, late worker admission and private auth waiting state. BASE-009/013/017 and CORE's registrar findings remain distinct integration points.

Callback Get has an owning data vector; callback Put instead shares TLS scratch across nested invocations (ADD-001). Result caches need reentrant restoration (BASE-007), and content/metadata need a snapshot taken before invoking a sink (ADD-002). A callback throwing a C++ exception can unwind DelayRunner/network dispatch; the SDK does not establish throw-across-callback as supported, so this is not added as a confirmed invalid-caller crash. Documented negative read/write and nonzero rewind results **are** supported failure signals.

Explicit reset stops the transport and joins storage workers while their dependencies survive. The worker does not reacquire its container mutex, and compaction joins removed threads outside the mutex. Concurrent operation versus arbitrary interface destruction and callback-time Shutdown require CORE dispatch/teardown rules; this report does not equate a raw pointer with a demonstrated native UAF. Implicit member destruction still merits coordinator work because registrar/queue precede Storage.

## 5. Numeric, overload and state-boundary audit

| Boundary | Evidence-based conclusion |
|---|---|
| `ReadFunc` negative, zero, positive | Negative reports failure but the previous save is already truncated (001); zero is EOF; positive is clamped to 2048. A callback claiming more bytes than its provided extent is invalid input, not a confirmed compliant-call overread. Both upload and hash loops were inspected. |
| `WriteFunc` count and extent | Short nonnegative results are ignored (003). Whole-file `uint32_t` extent narrows to signed int at Cloud line 163; INT_MAX+1 is negative on target. The expanded 003 uses a file within UINT32_MAX and sufficient x64 memory, not a hypothetical x86 oversized allocation. |
| Rewind failure | Both Put and CalculateHash ignore nonzero return (003). Put calls both phases consecutively; no checksum-read phase occurs. Missing internal hash calculation stays 004 rather than a new phase-count ID. |
| Buffered cloud reads | `get_size() > bufferLength` rejects known oversized data; the helper never writes beyond requested length. It can return zero/short count on I/O error and still receive success (002). Zero metadata-only byte count is correct. |
| Metadata conversion | On Windows `long` is 32-bit. Missing/empty/nonnumeric or excessively large `SavegameType` can throw in buffered/metadata-only Get, while callback Get defaults/catches (008). Negative/trailing-junk/out-of-enum metadata needs checked decoding; passing an arbitrary invalid app enum is not an independent confirmed defect. |
| Size/count/quota conversion | Cloud file size casts directly to uint32_t; Shared size/count/space helpers saturate. UINT32_MAX+1 files exceed representable public size and are not needed for the signed callback finding. Successful-query correlated quota saturation is independently demonstrated by ADD-003. |
| Hash calculation and persistence | Both FNV-64 overloads include binary NULs and carry state across chunks; callback scratch is invocation-local. Decimal `to_string` output differs from the getter's stated hexadecimal representation, but inspected SDK text does not specify MD5 or supply vectors. No invented algorithm-compatibility defect is counted. NULL/empty default hashes and stale replacement hashes remain 004; ignored expectedHash remains 005. |
| Savegroups | Mode false returns the same counter without advancing; Close only toggles the bool. Same-group equality works but consecutive group/first post-close inequality fails (006). Whole-second seeds can reuse prior IDs across instances; plain bool plus atomic counter lacks compound synchronization. uint64_t exhaustion is not a credible exposure. |
| Stat values / average rate | Negative int32_t values are accepted without arithmetic. Average update uses floating division/addition, so positive finite deltas already prove the wrong aggregate (010). Zero/negative duration, NaN/infinity and extreme floating inputs require a specified policy; they are not used to inflate counts. |
| Indexes / shared offsets | Cloud vector and Shared container/index helpers compare against size before indexing. User/achievement enumeration checks end. Shared read seeks then reads and returns gcount, without `offset + length` overflow arithmetic. A negative application value converted to uint32_t is not an independent library defect. |
| Time / event identifiers | Explicit cloud uint32_t timestamps round-trip through metadata; default cloud timestamps use system epoch seconds. Local Storage and the earliest Cloud branch inherit raw file-clock epoch conversion (BASE-UTIL-007). Telemetry uint32_t wrap is defined; SDK does not establish a permanent nonzero/global-unique ID guarantee. |

### Feature boundaries actually checked

Cloud starts at 1.148.6; metadata index API is gated through 1.148.12; timestamp starts 1.148.7; hash getter 1.148.11; savegame 1.148.14; hashing 1.148.15. Early placeholder hashes before calculation APIs exist are not treated as the same default-hash contract introduced later. Callback typedef constness was read from actual 1.148.6 and 1.152.11 SDK headers; implementations inherit those typedefs.

IStorage starts 1.88.0; experimental Synchronize ends 1.99.0; per-call sharing listeners exist at 1.134.10 and from 1.138.1. Stats per-call listeners start 1.125.0; older globals are still meaningful. User's specific-user global listener starts 1.73.0, much earlier than its request argument (ADD-005). All auth renames and platform-specific overload bodies were read; console execution was not attempted. Telemetry starts 1.134.0, anonymous send 1.139.6, visit methods 1.139.7 and sampling 1.141.0. Textual gate checks do not claim vtable/export/stack compatibility for every build.

## 6. Status of all 23 prior IDs

R = retained with fresh evidence; E = retained with a full marked addendum correction/expansion. There are **17 R + 6 E**, not 29 prior findings. Each BASE section remains preserved in its original sidecar. No prior finding had sufficient contrary evidence for withdrawal or severity reduction.

| Prior ID | Status / severity | Fresh conclusion and scope |
|---|---|---|
| BASE-STORAGE-001 | R / High | Cloud `374-417,488-505`: live truncation precedes callback/destination success; valid negative source error can lose A. Transaction needed, not just failure notification. |
| BASE-STORAGE-002 | E / High | Cloud `162-267,404-456,539-580`: ignored I/O/metadata/unlink results retained; addendum covers success before streaming close and differentiates gcount-preserving buffer reads from padded vector EOF reads. |
| BASE-STORAGE-003 | E / Medium | Cloud `163,399-402,613-615`: partial sink/rewind signals retained; signed-int download extent is now explicit. Invalid over-reporting producers are excluded. |
| BASE-STORAGE-004 | R / Medium | Cloud `445-449,533-537`: NULL preserves old HASH/default placeholder; empty stores empty. Latest SDK expressly requires calculation. Exact native algorithm still unproven. |
| BASE-STORAGE-005 | R / High | Cloud `549-580`: expectedHash is unused; normal stale guarded delete removes the replacement. No multi-client remote service is required. |
| BASE-STORAGE-006 | E / Medium | Cloud `24-38,583-597`: consecutive group/post-close collision retained; restart seed reuse and compound-state synchronization added under this ID. |
| BASE-STORAGE-007 | R / Medium | Cloud `47-125,244-340`: two pending requests overwrite callback-only cache; reentrant restoration/value snapshots remain needed. ADD-002 is different: bytes versus metadata within one operation. |
| BASE-STORAGE-008 | R / Medium | Cloud `254,302`: absent fields are possible after old-version writes or failed separate metadata persistence; `stol` escapes. Callback overload already defaults/catches. |
| BASE-STORAGE-009 | R / High | Cloud `152-202`: direct lambda retains listener despite Unregister; ordinary queued completions additionally overlap CORE-001. Owned strings/subcontainer do not own listener lifetime. |
| BASE-STORAGE-010 | R / Medium | Stats `87-91`: two `(10,2)` updates produce 10 instead of combined rate 5. No undefined negative/zero-duration behavior is needed. |
| BASE-STORAGE-011 | R / Medium | Stats `127-161`, IniData `835-913`: enabled persistence can fail after dirty reset while store success is queued. Intentionally disabled saving is a separate policy, not the failure example. |
| BASE-STORAGE-012 | R / High | Stats `63-124,177-224`: scalar/Copy operations use mutable borrowed state outside locks. Concurrency is supported; plain pointer getters are not the premise. UTIL-002 overlaps at the root. |
| BASE-STORAGE-013 | R / High | Storage `171-196`: worker can register the listener after caller cancellation/destruction. Explicit reset/worker joining does not close that admission window. |
| BASE-STORAGE-014 | R / Medium | Storage `245-249`: after B successfully downloads A's file, owner is reported as B. Wire/persistence lacks uploader metadata; no privilege-escalation claim is inferred. |
| BASE-STORAGE-015 | R / Medium | Storage `287-304`: existing zero-byte shared entry is rejected; protocol has no independent status. Accepting all empty vectors would incorrectly accept not-found/denial. |
| BASE-STORAGE-016 | E / Medium | Storage `160-193,215-221`: read errors/exceptions retained; queue-admission false/native packet rejection also orphan completion. 33-MiB valid source is a non-OOM example. |
| BASE-STORAGE-017 | R / High | User `74-77,610-651`: private waiting set survives registrar cancellation. Same-thread unregister/destroy before pumping suffices; no unproven native listener lifetime assumption. |
| BASE-STORAGE-018 | R / Medium | User `253-259,440-445`: sign-out reports loss without changing logged_on/configured SignedIn or cancelling work. Kept as local lifecycle defect, not third-party account compromise. |
| BASE-STORAGE-019 | E / Medium | User `55-85,107-121,610-671`: explicit deadline ignored where present; check/enqueue can miss acceptance under supported concurrency even with a healthy server. |
| BASE-STORAGE-020 | R / Medium | User `520-557`: default NULL auth listener suppresses request and PlayFab ignores supplied failure listener. Unsupported service capability does not excuse missing supported failure delivery. |
| BASE-STORAGE-021 | R / Medium | Telemetry `58-122`: SDK permits NULL array names. Direct C-string insertion is invalid; exact checked/release CRT outcome is not claimed universally identical. |
| BASE-STORAGE-022 | R / High | User `348-358`: Copy binds unlocked string reference then copies, while updates/replacement can mutate it. Enumeration at `413-423` already copies under lock and is not an equivalent defect. |
| BASE-STORAGE-023 | E / Medium | Telemetry `16-24,159-175`: default unopened stream can pass truthiness and first failed write is acknowledged; addendum covers failed-insertion/pre-lock state interleaving. Disabled-success policy itself could be valid if explicit and consistent. |

### Corrections and narrowed interpretations

The six full correction sections are attached to **002, 003, 006, 016, 019, 023**, with unchanged IDs/severity, evidence, impact, options, recommendation and proposed verification. They extend or refine the claim; they do not silently replace baseline text. Additional counterevidence recorded in the coverage/flow notes prevents overreading earlier concerns:

- Buffered read bounds and actual gcount refute an automatic buffer-overflow claim; whole-file success/error handling is the issue.
- Full source snapshot fields refute an assumed UserData-response field-loss bug based only on the API name.
- SDK download-first preconditions narrow upload convenience-cache mismatch; it is not independently counted as a supported shared-file read failure.
- Worker flag ownership, moved-from slots, and explicit reset order refute a generic compaction UAF or worker-mutex deadlock claim.
- No dangling language pointer, queued temporary callback string, missing-user null pointer, valid leaderboard success output, or pre-login Utils state guarantee was established.

These are rejected candidate interpretations, **not invented refutations of baseline findings that already included the relevant caveats**.

## 7. New finding index and canonical full details

All five sections contain exact source ranges, severity/confidence/category/scope, SDK/dependency evidence, a concrete failure sequence, impact, solution options, recommended resolution and proposed verification. No verification section describes a test as executed.

| New ID | Severity / confidence | Mechanism | Canonical detail |
|---|---|---|---|
| ADD-STORAGE-001 | Medium / High | Same-thread nested callback puts reuse one TLS array; complete valid callback returns can still upload the wrong bytes. | [CloudStorage.cxx.review.MD](../../Source/Client/Impl/CloudStorage.cxx.review.MD), source `395-409` |
| ADD-STORAGE-002 | Medium / High | Successful replacement between data read and metadata sampling produces A bytes with B savegroup/type; concurrent puts also lack generation publication. | [CloudStorage.cxx.review.MD](../../Source/Client/Impl/CloudStorage.cxx.review.MD), source `152-200,244-255,499-540` |
| ADD-STORAGE-003 | Medium / High | `min(capacity,U32_MAX)` and `min(used,U32_MAX)` both saturate, destroying positive free headroom. | [CloudStorage.cxx.review.MD](../../Source/Client/Impl/CloudStorage.cxx.review.MD), source `55-60` and Shared adapter `350-375` |
| ADD-STORAGE-004 | Medium / High | Online-status-created identity record bypasses actual remote playtime retrieval. | [Stats.cxx.review.MD](../../Source/Client/Impl/Stats.cxx.review.MD), source `419-449` |
| ADD-STORAGE-005 | Medium / High | Per-call-listener feature guard incorrectly removes older global remote UserData completion. | [User.cxx.review.MD](../../Source/Client/Impl/User.cxx.review.MD), source `297-318` |

Distinctness check: 001 is not short/failed callback handling; 002 is not the pending list/tag result-cache overwrite; 003 requires successful space queries, unlike UTIL-016; 004 is missing domain hydration, unlike playtime clock/archive arithmetic; 005 is a historical compile-time notification gate, unlike BASE-020's latest optional-listener argument routing.

## 8. Cross-owner dependencies and reconciliation

| Owner | Required coordination / existing root IDs |
|---|---|
| CORE | BASE-CORE-001/002 cancellation and in-flight global snapshots affect many facades; preserve the direct cloud lambda (009), late FileShare admission (013), private auth waiters (017). BASE-CORE-003 covers callback-time teardown/pump destruction. Explicit reset is not the same as implicit member destruction; investigate the latter without calling normal joins unsafe. Error-state/partial-Init paths are CORE-005 context. Logger's CORE-010 state-check pattern parallels, but is a different object from, telemetry 023. |
| UTIL | Data/metadata commit and read snapshot primitives support ADD-002 plus 001/002/008. BASE-UTIL-005/006/008/009/010 already own ghost creation, failed-delete cache removal, unchecked close, destructive copy rollback and padded short reads; do not recount them here. BASE-UTIL-002 supports 012/022; 001/003 playtime archive/clock fixes remain separate from ADD-004. Timestamp epoch is UTIL-007, Windows case identity UTIL-004, dot namespaces UTIL-011 and link enumeration UTIL-012. |
| NET | ADD-003 needs a checked, jointly narrowed quota pair through SharedFileUtils; UTIL-016's failed-space-query status must also propagate. BASE-NET-008 owns INI dirty/save-result loss underlying 011 and User writes. UTF-8/native-path conversion remains NET-009. BASE-016 requires operation-aware queue/send failure handling; NET-006 packet-size and NET-007 queue-budget concerns must inform bounded transfer, not silently discard it. |
| SERVER | BASE-SERVER-006/007 counter and false share acknowledgements are independently preserved; global filename collisions are included in 007. Owner/status fields for 014/015 and proper completion for 016 require compatible protocol/persistence changes. Presence-before-Hello is valid input ordering; ADD-004 is a client availability bug, not a demand that the server delay all presence. |
| API | Friends turns an online announcement into a callback at `Friends.cxx:665-675`, making ADD-004 directly reachable from a normal presence callback. Coordinate one per-user domain-availability model. No edits or new findings were made in API-owned source/sidecars. |
| BUILD / coordinator | Verify legacy/global-only SDK branches for ADD-005 and callback typedef/gate boundaries when execution is permitted. Preserve exports/vtables. Reconcile owner-local 28-ID accounting with shared-root baseline IDs and other addenda; this report does not replace repository-wide totals. |

## 9. Verification, build/CI, security, performance and portability assessment

**Existing verification source inspected:** complete `Source/SystemTests/Host/{Apps,CloudStorage,Stats,Storage,Telemetry,UserData,Utils}.cxx`. These support normal copies/binary data, explicit cloud timestamp/hash, enabled profile restart persistence, live propagation and policy denial. They do not prove any run in this pass.

Concrete gaps exposed by fresh inspection:

- Cloud test uses only buffered Get/Put, one file/request, explicit hash/timestamp, no delete/group/hash calculation; it ignores quota values (`CloudStorage.cxx:43,99-124`). It cannot expose new callback or headroom cases.
- Older UserData request completion is bounded by a later Stats response instead of its own global listener (`Host/Stats.cxx:185-203`). This specifically masks ADD-005. Live SetUserData tests exercise a different correctly gated handler.
- File-share tests use a 13-byte same-user payload, close the upload cache before downloading, and cover server denial. They do not establish remote owner, empty-file, repeated-name/restart ID, cancellation, 32-MiB or fault-injection correctness.
- Telemetry test validates one success callback's type/index, not stored bytes or arrays/second-disabled-event/failing stream. It can pass the false-success path.
- Restart stats tests compare float bits and values, so it would be wrong to call the existing coverage merely numeric integer tests. Average-rate weighting, concurrent lookup/use and persistence retry still need focused verification.

**Build/CI:** Feature map and SDK dependency manifest were read as context; root build/CI ownership was not reopened and no compiler/linker/ABI result is asserted. This review added neither production tests nor test configuration. Proposed version checks are 1.125.2 global-only UserData, cloud 1.148.6 legacy metadata, 1.148.14 savegame and latest hashing/listeners, plus Windows x64 signed callback extents and ordinary x86-width inspection.

**Security/trust:** Game callbacks and app arguments are in-process SDK inputs; server file responses cross the LAN message boundary; filesystem bytes/metadata can fail independently. Canonical containment already rejects ordinary traversal; invalid portable-path/device-name arguments are not used as compliant-call vulnerabilities. Local reparse TOCTOU, encoding, remote deserialization and server authorization remain corresponding owners' findings. No secret content or real identity tokens were needed or used.

**Performance:** Whole-file vector read, message copies, serialization and one jthread per share imply memory/latency costs; no benchmark is claimed. Streaming callbacks actually receive whole-file downloads in one call, which is a concrete signed-width issue, not merely a performance hypothesis. Growing input above native packet limit has a confirmed lost-completion path (016), so fixing it needs a bounded transfer policy rather than just more buffering.

**Windows portability:** Names are converted through `std::filesystem::path`/`.string`, Windows case/encoding/reparse policies matter, and raw `file_clock` seconds are not Unix seconds. These are traced cross-owner roots, not new facade duplicates. `DeleteFile` macro push/undef/pop remains correct. Windows 32-bit `long` matters to `stol`; int remains 32-bit on x64 and determines callback extent. Negative/overflow conclusions above use those actual types.

## 10. Positive practices and remediation order

Positive evidence: bounded destination copying handles null/zero capacity; indexes check before access; callback strings are owned; self-ID aliases share an owned local object; streamed Get retains its filesystem parent; metadata map operations lock; completed worker joins occur outside the worker-list mutex; explicit reset preserves dependencies. SDK failure callbacks exist for unsupported leaderboards/PlayFab and should remain usable. Existing isolated binary/restart SystemTests are a useful foundation.

1. **Save integrity first:** retain previous committed generations on failure (001/002/008), isolate scratch (ADD-001), and publish/read coherent data plus metadata (ADD-002). Only then trust calculated hashes/guarded deletes (004/005) and savegroup identity (006).
2. **Operation lifecycle:** synchronous cancellable admission and exactly-once results across queue/send/auth/teardown (009/013/016/017/018/019 plus CORE). Close before publishing success; do not hold transaction locks while invoking game code.
3. **Usable state:** callback-scoped snapshot restoration (007), quota consistency (ADD-003), hydrated playtime (ADD-004), legacy callback gate (ADD-005), and lock-scoped numeric/user Copy access (012/022).
4. **Persistence/protocol correctness:** aggregate save status/dirty retries (011), weighted average records (010), uploader identity and empty/status separation (014/015 with NET/SERVER).
5. **Local telemetry:** valid anonymous element names, explicit sink policy, synchronized pre/post checks (021/023). Validate small deterministic failure cases before broadening the test matrix.

## 11. Context inventory and actual checks

Full dependency reads: SharedFileUtils `.cxx/.hxx`; filesystem container, entry, metadata `.cxx/.hxx` and utils `.cxx`; AchievementsAndStatsContainer `.cxx/.hxx`, AchievementData `.cxx`, ConstHash, SafeStringCopy, ContainerGetByIndex; GalaxyUserData `.cxx`; file-share/request/response and RequestSpecificUserData schemas; ListenerRegistrar `.cxx/.hxx`; DelayRunner `.cxx`; NotificationParamScopeExtender `.cxx/.hxx`; UniverseLAN `.cxx/.hxx`; Client `.cxx`; Networking `.cxx`; vendor Galaxy CMake manifest. `Source/galaxy_sdk_features.cmake:1-260` was read through relevant definitions, not claimed through its helper-function EOF.

Targeted flow context: `IniData.cxx:690-954`; `ServerHandlers.cxx:30-239,430-524`; `ClientNetworkHandlers.cxx:1-190`; `GalaxyDLL.cxx:140-190`; `Friends.cxx:167-231,650-699`; `Networking.hxx:1-179`; actual ENet packet-limit declarations and peer-send rejection plus Enet++ send forwarding. SDK context: latest IApps/ICloudStorage/IStorage/ITelemetry/IUtils in full; IStats `377-897`, IUser `415-469,515-644` plus contract searches, IListenerRegistrar `134-241`, GalaxyApi `275-389`; legacy 1.148.6 ICloudStorage `190-414` and 1.125.2 IUser `1-200,376-406` plus signature searches. SDKs/vendors were not implementation review targets.

Baseline comparison: STORAGE report and all 14 corresponding sidecars read fully; CORE/NET/UTIL/SERVER indexes and relevant SharedFileUtils/filesystem/server sidecars consulted afterward for deduplication. Cross-owner summaries are context, not claims of rereviewing those full assignments.

Actually executed read-only Git checks:

- `git rev-parse HEAD` returned the HEAD above; initial `git status --short` showed `?? .ai/review-addendum/`.
- `git diff b30e83872c0006e8240c8b4f565da5351bf10080 --` followed by the 14 explicit assigned source/header paths returned no differences.
- `git diff --exit-code b30e83872c0006e8240c8b4f565da5351bf10080 -- Source ':(exclude)**/*.review.MD'` returned no differences, including dependency source read here.
- Later `git --no-optional-locks status --short` showed the 14 report edits plus concurrent other-owner report work. Only owned report edits belong to this review.

### Final artifact validation (executed)

- `rg --no-ignore --count-matches` restricted to the 14 owned sidecars found exactly **one re-review addendum marker per file**.
- Heading enumeration found **ADD-STORAGE-001 through 005 once each**: CloudStorage 3, Stats 1, User 1. Separate correction-heading count found **six**: CloudStorage 3, Storage 1, Telemetry 1, User 1.
- The required finding structure (heading, five metadata fields and six detail labels) totals **408 elements = 34 full sections**: CloudStorage 180, Stats 48, Storage 60, Telemetry 36, User 84. These are 23 preserved BASE sections, 5 new sections and 6 same-ID corrections, not 34 unique findings.
- Report-row checks found exactly **14 coverage rows, 23 BASE-ID status rows, and 5 new-index rows**. This report was read back fully before final validation was appended.
- `git diff --numstat --` the 14 explicit owned sidecar paths showed additions only and **zero deleted lines in every file**. `git diff --check --` those same paths completed with no whitespace errors. The untracked new report was checked through the dedicated reader and row/ID checks, not represented as included in Git's tracked-file whitespace check.
- The final `git diff --exit-code b30e83872c0006e8240c8b4f565da5351bf10080 -- Source ':(exclude)**/*.review.MD'` was empty/successful. No production change was introduced.

Coverage and artifact accounting are complete for this STORAGE assignment. Proposed runtime verification remains future work; repository-wide reconciliation and cross-owner accounting remain coordinator work.
