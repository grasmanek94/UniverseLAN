# Independent addendum reconciliation

**2026-09-24 — production baseline `b30e83872c0006e8240c8b4f565da5351bf10080`.** Independently audited all 29 initial ADD findings in CORE/API/STORAGE/NET/UTIL/SERVER/INTERCEPT/BUILD against the baseline reconciliation and source contracts. A subsequent coordinator/ABI check adds the thirtieth record, ADD-ABI-001, with actual local callback-dispatch reproduction. This is findings reconciliation, not another full coverage review.

Observed HEAD: `48cea8c6c48fa41fddd348a0119129cc5643fc8b`. Read-only `git --no-optional-locks diff --exit-code --name-only b30e83872c0006e8240c8b4f565da5351bf10080 -- Source ':(exclude)**/*.review.MD' README.MD` returned no differences. No builds, tests, probes, Git writes, or secret inspection occurred. Only this reconciliation was authored.

## Accounting and confidence

| Disposition | ADD IDs | New counted groups |
|---|---:|---:|
| Retained from initial owner findings | 22 | 22 |
| Subsequent ABI handoff, locally reproduced | 1 | 1 |
| Aliases of baseline findings | 3 | 0 |
| Conditional: supported-input/SDK semantics unresolved | 3 | 0 |
| Informational: demonstrated helper defect, dormant route | 1 | 0 |
| Disproved whole findings / false positives | 0 | 0 |
| **Total** | **30** | **23** |

**Final new counted severity: 3 High, 19 Medium, 1 Low; zero Critical. Baseline 103 groups + 23 = 126 counted groups (24 High, 89 Medium, 13 Low).** The three conditional candidates comprise one potential High and two potential Medium findings. Together with the newly latent helper and two baseline investigations, six informational records remain outside confirmed totals.

The coordinator's local ASan-enabled probes additionally reproduced the quota pair and metadata namespace failures, and the borrowed-key memory-lifetime mechanism. That last mechanism does not settle SDK aliasing permission; ADD-API-001 remains conditional. Actual results are in [VERIFICATION.MD](VERIFICATION.MD). New counter-file and snapshot observations are carried as Correctness/state-ownership findings; no adversarial network validation was performed.

Conditional does not mean illegal caller behavior or a disproved mechanism. Their source mechanics have High confidence; compatibility conclusions have Medium confidence. Established version, configuration, and scheduling preconditions alone do not make a finding uncertain. The 103 baseline groups and their prior partial-alias rules are carried forward without reopening their dispositions.

## Exact alias map

| ADD alias | Existing canonical group | Independently verified scope |
|---|---|---|
| **ADD-NET-001** | **BASE-SERVER-019** | Same application broadcasts and transport-only recipient selection: `Server/ServerHandlers.cxx:199–210`, `Shared/Networking/Networking.hxx:193–231`, `Vendor/Enet-IPv6/src/host.c:306–321`, `Vendor/Enet++/src/enetpp_helpers.cxx:8–28`. Pending-challenge recipients were already counted. |
| **ADD-NET-004** | **BASE-SERVER-008** | Same sender-local chat IDs, room fan-out, and wrong interlocutor: `Server/ServerHandlers.cxx:222–242,284–293`; `Client/Impl/Chat.cxx:47–79,108–148`. Preserve BASE-API-001's previously separate unsolicited global history-success obligation. |
| **ADD-UTIL-002** | **BASE-SERVER-007**, name/ID-collision portion | The original SERVER-007 section already documents repeated-name/new-ID rejection, Debug assertion, two-uploader collisions, and ID-keyed remediation. `filesystem_container.cxx:174–182` is the identical shared helper. Its client-cache manifestation expands repair coverage, not the root count. Preserve SERVER-007's broader false-acknowledgment obligation. |

**Partial overlap:** ADD-NET-003's file-transfer send-loss/completion examples overlap BASE-STORAGE-016; retain ADD-NET-003 once for general session retirement and independently stranded lobby filters/requests. No additional file-transfer group is created. All other retained ADD IDs remain self-canonical. Related transaction/cancellation fixes are not, by themselves, evidence of duplication.

Paths below omit `Source/`. **F/** means `Shared_NoVer/filesystem_container/`; **SDK/** means `DLLs/1.152.11/galaxy/`, unless another version is specified. Ratings are **severity / confidence**.

## Complete disposition ledger

### CORE and API — 7/7

| ID | Disposition / rating | Evidence and correction |
|---|---|---|
| ADD-CORE-001 | Retain — Medium / High | `Client/UniverseLAN.cxx:49,64–65` constructs transport before Apps; `Client/Client.cxx:12–33` can throw; `Client/GalaxyDLL.cxx:130–133` then returns null. SDK/IApps.h:63–65 expressly preserves offline functionality after Init error. Catching errors under BASE-CORE-005 alone cannot create Apps. |
| ADD-CORE-002 | Retain, narrow compatibility scope — Medium / High | Normalizer copies controls; `Client/Client.cxx:27,66` bypasses them, and ENet++ `enetpp.cxx:179–185` binds with null address. SDK/InitOptions.h:39–41 specifies **local** host/port and custom internal-thread creation. The INI remote relay is a legitimate replacement choice; it does not implement these local controls. No allocator corruption or required proprietary-service behavior is established. |
| ADD-CORE-003 | Retain — Medium / High | Both graphs construct parameterless ClientIniData (`Client/UniverseLAN.cxx:18–25`); both submit `GetApiGalaxyID()` (`Client/ClientNetworkHandlers.cxx:60–71`). Fixed custom identity/zero offset yields duplicate rejection at `Server/ServerHandlers.cxx:84–129`. SDK/InitOptions.h:37 explicitly mentions both Peer and Game Server; GalaxyGameServerApi.h:43–56 supplies separate anonymous-server control. Simultaneous runtimes are a credible supported scenario. BASE-CORE-004's packet-role fix does not select another identity. |
| ADD-API-001 | **Conditional — potential High / Medium** | `Client/Impl/Friends.cxx:372,380,558–570` erases the borrowed key's node before copying that pointer into the request (indexed-pointer route: 1.148.2+). SDK/IFriends.h:1005–1016 documents a non-thread-safe getter but does not explicitly settle its lifetime/alias use across a mutating API call. Keep the UAF mechanism; withdraw the unconditional claim of proved SDK-compliant aliasing. An owned-key control does not have this mechanism. |
| ADD-API-002 | **Conditional — potential Medium / Medium** | `Friends.cxx:451–457` emits the supplied zero selector. SDK/IFriends.h:956 permits that default; callback comments at 440/460 say “ID of the user” without specifying normalization. GalaxyID invalidity alone does not disprove a zero-means-self callback convention. Native/version-specific convention or stronger documentation is needed; neither confirmed defect nor established false positive. |
| ADD-API-003 | Retain — Medium / High | `Client/Impl/Matchmaking.cxx:1141,1157` defers transitions while line 1096 reports later messages immediately; `Client/GalaxyDLL.cxx:166–173` drains network events first. Server sends entry before later member traffic. A single queued receive batch suffices; no recursive pump is required. Scope is this same ordered event stream. |
| ADD-API-004 | Retain — Medium / High | `Client/Impl/Networking.cxx:153–168` always notifies NETWORKING and auto-pops. `ClientNetworkHandlers.cxx:146–157` selects the legacy server queue; SDK 1.124.0 INetworking.h:43–68 requires SERVER_NETWORKING. Applies through 1.134.10; first-packet failure is independent of BASE-API-013's backlog issue. |

### STORAGE and NET — 9/9

| ID | Disposition / rating | Evidence and correction |
|---|---|---|
| ADD-STORAGE-001 | **Conditional — potential Medium / Medium** | `Client/Impl/CloudStorage.cxx:395–407` shares one TLS chunk across nested puts. Filling A, uploading B inside A's read callback, then returning A's count yields B bytes in A. SDK/ICloudStorage.h:324–386 neither prohibits nor expressly guarantees initiating another upload there. General thread-safety does not establish reentrancy. Retain the mechanism and require callback-contract clarification; do not call the sequence illegal. |
| ADD-STORAGE-002 | Retain — Medium / High | `CloudStorage.cxx:162–188,244–255,499–540` samples bytes and metadata separately. Even without nested callbacks, a successful concurrent buffered replacement between those reads produces mixed generations. SDK/ICloudStorage.h:88–90 associates completion metadata with downloaded data. Different from BASE-STORAGE-007's pending-result cache overwrite. |
| ADD-STORAGE-003 | Retain — Medium / High | `CloudStorage.cxx:55–60`, `Shared/SharedFileUtils.cxx:350–375`, F/filesystem_container.cxx:365–381 independently clamp capacity and whole-volume use. Each clamp is numerically safe; their quota relationship is not preserved. A 100-GiB capacity/20-GiB used fixture returns `(UINT32_MAX, UINT32_MAX)` despite 80 GiB available. This successful-query issue is distinct from BASE-UTIL-016. |
| ADD-STORAGE-004 | Retain — Medium / High | `Client/Impl/Stats.cxx:428–449` equates user-map presence with playtime availability. `User.cxx:560–565,578–607` creates an unhydrated online placeholder; server online notification precedes Hello. Success before hydration remains wrong after fixing baseline playtime serialization/clock issues. |
| ADD-STORAGE-005 | Retain — Medium / High | `Client/Impl/User.cxx:313–315` guards the entire remote completion with per-call-listener availability. SDK 1.125.2 IUser.h:161–184,380–387 already promises the global listener. Preserve the exact feature intersection, including later isolated/reintroduced per-call intervals. |
| ADD-NET-001 | Baseline alias — Medium / High | Maps completely to BASE-SERVER-019 above; **zero new groups**. |
| ADD-NET-002 | Retain — Medium / High | `Shared/IniData.cxx:692–709,898–912` persists unencoded strings. SimpleIni.h:470–474,1729–1755,2722–2740 establishes default single-line output and whitespace trimming. SDK/IUser.h:624–625 allows small newline/edge-space values. Successful I/O still changes bytes/keys; separate from failed persistence. |
| ADD-NET-003 | Retain, partial overlap — Medium / High | `Shared/Networking/Networking.cxx:247–262` discards packets; disconnect handlers do not retire operation state. `Client/Impl/Matchmaking.cxx:95–117,210–215` retains filters until a response that may never arrive. Old map retention is established independently of any promise to replay lost requests or support infinite network delivery. |
| ADD-NET-004 | Baseline alias — Medium / High | Maps completely to BASE-SERVER-008 above; **zero new groups**. Equal IDs must collide within the same listener type. |

### UTIL — 6/6

| ID | Disposition / rating | Evidence and correction |
|---|---|---|
| ADD-UTIL-001 | Retain — High / High | F/filesystem_container.cxx:84–100 samples absence before lookup: concurrent creation can make FileExists unlink the new file. Lines 293–351 also erase maps by key but search the vector by old pointer. F/filesystem_container_entry.cxx:91–110 deletes by pathname. Successful operations suffice; distinct from failed-delete BASE-UTIL-006. |
| ADD-UTIL-002 | Baseline alias — Medium / High | Existing BASE-SERVER-007 collision mechanism; **zero new groups**, including the shared-helper client consequence. |
| ADD-UTIL-003 | Retain, precise schedule — Medium / High | F/filesystem_container_metadata.hxx:27–32 locks each map during serialization; lines 65–72 provide no whole-record lock. F/filesystem_container_entry.cxx:351–371 independently opens/truncates the final archive. Large differing records can interleave after the first user-map traversal unlocks. See the supported metadata route below. |
| ADD-UTIL-004 | **Reclassify Low/current to Informational/latent; High mechanism confidence** | F/filesystem_container_entry.cxx:135–176 skips persistence when destination metadata becomes empty, retaining obsolete disk attributes/ID. `Shared/SharedFileUtils.cxx:331–347` exposes the affected reverse copy, but the production call search finds only active local-to-shared copying, whose destination ID prevents emptiness. Keep regression coverage; exclude current defect totals. |
| ADD-UTIL-005 | Retain, x86/oversize scope — Medium / High | F/filesystem_container_entry.cxx:223–226,248–263 narrows wide sizes to size_t before checking. On x86, 4 GiB + 8 becomes eight bytes. Callback upload accepts bounded chunks without a total-length guard. Remedy may reject oversized files; the finding does not require promising greater-than-32-bit SDK size results. |
| ADD-UTIL-006 | Retain — Medium / High | F/filesystem_container.cxx:247–255 maps `save` and `save.metadata/part` onto metadata paths requiring the same component to be both file and directory. Both data names satisfy portable relative-path rules. Error checking alone cannot repair this namespace representation. |

### SERVER, INTERCEPT and BUILD — 7/7

| ID | Disposition / rating | Evidence and correction |
|---|---|---|
| ADD-SERVER-001 | Retain with exact preconditions — High / High | `shared-id.counter` is an ordinary allowed filename under SDK/IStorage.h:116–120. `Client/Impl/Storage.cxx:158–182` forwards it unchanged; `Server/ServerHandlers.cxx:455–476` creates uploads in the counter's shared container. With counter absent, the preceding lookup-only Open cannot overwrite the first malicious upload. Nonnumeric content reaches uncaught stoul on restart (`Server.cxx:96–101`, Main.cxx:33). Requires authentication, uploads enabled, and restart before another counter-writing upload. |
| ADD-SERVER-002 | Retain, member-payload scope — Medium / High | `Server/ServerHandlers.cxx:171–173,532–540,613–630` sends whole lobbies to admitted outsiders; `Shared/Lobby.hxx:55–59` includes messages/member keys. SDK/IMatchmaking.h:581,620,673–684 distinguishes member data from permitted nonmember metadata refresh. Member-history disclosure survives admitted-recipient filtering; separate from baseline broadcast admission and history-size findings. |
| ADD-SERVER-003 | Retain — Low / High | `Tracer/Stacker.hxx:13` has capacity 260; Stacker.cxx:85 converts an unbounded source string before reporting/dumping. StackWalker.h:138,152 permits 1024 bytes; Boost static_string.hpp:6694–6700 throws on overflow. Optional diagnostics with long symbol paths are the exposure, not the original crash. |
| ADD-INTERCEPT-001 | Retain — Medium / High | `InterceptionLogger/GalaxyApiFactory.cxx:166–167` always returns null. SDK 1.114.9 GalaxyApi.h:538–540 routes public GetError through that manager. Ordinary post-init error loss remains independent of BASE-INTERCEPT-008's initialization handling. |
| ADD-INTERCEPT-002 | Retain — Medium / High | `InterceptionLogger/UniverseLANInterceptor.cxx:145–166` selects string Init; factory/modern-options feature intervals never intersect. `Impl/InitOptionsModern.cxx:15,31–33,148–176` also loses exception policy. SDK 1.114.9 IGalaxy.h:38–63,106 supplies all options. Unlike the replacement backend, this path forwards to the real SDK and must preserve supported configuration/peer selection. |
| ADD-INTERCEPT-003 | Retain — Medium / High | `InterceptionLogger/Impl/Apps.cxx:131–132` invokes a valid listener inline under the force-DLC option. SDK/IApps.h:90 and GalaxyApi.h:105–106 require asynchronous pump delivery. Keep scheduling/state-machine impact; no nullable-listener or unspecified game-UAF claim. |
| ADD-BUILD-001 | Retain, optional-target scope — Medium / High | DLL staging belongs to production POST_BUILD commands (`DLLs/CMakeLists.txt:168–182`). `TestCases/CMakeLists.txt:69–75,100–127` neither depends on those producers nor stages the imported Galaxy DLL name in interceptor mode. A clean individual-target build can lack runtime artifacts; prior full builds can mask this. |

## Independent verification suggestions — all unexecuted

- **CORE 001–003:** inject constructor DNS/host failure after configuration; check offline Apps and cleanup. Inspect requested local endpoint and spy-factory lifecycle without assuming native thread counts. Initialize client/server in both orders with one fixed fixture identity, require distinct accepted sessions and independent shutdown.
- **API 001–002 / STORAGE 001:** first establish borrowed-pointer lifetime, zero-selector callback convention, and producer-callback reentrancy from versioned documentation/native reference. Then compare borrowed versus owned keys under ASan, default versus explicit-self callback IDs, and nested A/B uploads with separate files/cursors and full valid counts. A synthetic harness proves mechanisms, not undocumented SDK permission.
- **API 003–004 / STORAGE 004–005 / NET 003:** queue entry/message/leave before one pump; separate legacy client/server listeners with empty queues; delay Hello after online presence; require the older global-only user-data callback; disconnect around request/reply admission and inspect filter/request retirement.
- **STORAGE 002–003 / UTIL 001,003,005,006:** barrier-controlled successful replacements and stale lookups; deterministic quota snapshots; x86 sparse-file boundaries; prefix-conflicting metadata names in both orders. For UTIL-003, use SDK **1.148.11**, a small persistent data buffer, and equally sized NULL-terminated metadata arrays with large differing string values (ICloudStorage.h:409–430 specifies no aggregate tag-byte cap; CloudStorage.cxx:507–514 copies them). Pause after user-map serialization, commit the second archive, then resume the first tail. This respects map locks and avoids invalid oversized hash arguments. Verify complete reloadable records, not merely successful closes.
- **NET 002:** round-trip API-owned user data through a fresh configuration instance using LF/CRLF, edge whitespace, equals signs, and section-like text; compare exact bytes, keys, and counts with successful-I/O controls.
- **Aliases / SERVER:** aligned same-type chat requests, challenge-pending recipients, and repeated same-name IDs validate existing groups. Isolate counter-name upload/restart ordering and upload-disabled controls. Decode outsider/member lobby responses; test 260/261-character diagnostic conversion boundaries.
- **INTERCEPT / BUILD / latent UTIL-004:** recording SDK factory for both exception policies, paths, and public error route; forced-DLC callback timing/cancellation; inspect single-target staging closure with prerequisites supplied independently. Exercise empty-metadata reverse-copy/reload directly while retaining its dormant classification.

Prioritize the three counted High additions, then operation/generation integrity and callback/version fidelity. The three conditional candidates merit contract resolution rather than automatic inclusion in confirmed totals. ADD-ABI-001 accounts once for BUILD's listener-tag handoff. The undefined persona-reader macro is recorded as a clarification, not an additional callback-contract defect. The initial audit's unexecuted verification suggestions remain proposals except for the explicitly recorded coordinator probes.
