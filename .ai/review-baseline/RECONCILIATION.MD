# Cross-subsystem reconciliation

Baseline: **`b30e83872c0006e8240c8b4f565da5351bf10080`**. Inputs: the seven **new** CORE/API/STORAGE/NET/UTIL/SERVER/INTERCEPT notebooks and their fresh detailed sidecars, with targeted production, SDK and vendored-library tracing. Superseded reports were not used. This is reconciliation, not another full review.

**Conclusions:** remove BASE-UTIL-015 from current-version defect counts; narrow BASE-INTERCEPT-001's proven outcome; retain callback-time shutdown, pending WebSocket cleanup and savegroup-ID findings. Combine the omitted-timeout findings at **High** integrated priority. Several umbrella findings overlap only partially and must not disappear wholesale.

Paths below are relative to **`Source/`**. `SDK/` means **`Source/DLLs/1.152.11/galaxy/`**, except where another version is specified. “Confirmed” denotes static evidence, not runtime reproduction.

## 1. Exact duplication map

An alias removes duplicate accounting only for the stated mechanism. A **partial alias** preserves the remaining independent defect under its original ID.

| Canonical ID | Aliases / scope | Evidence and reconciliation |
|---|---|---|
| **BASE-NET-003** | **BASE-SERVER-002** | Same omitted `ENET_EVENT_TYPE_DISCONNECT_TIMEOUT`: `Shared/Networking/Networking.cxx:85–104,146–167`. SERVER supplies the consequential old-ID/new-peer failure; NET additionally supplies stalled initial reconnect. One root, both client/server branches, **High** integrated priority rather than two findings. |
| **BASE-SERVER-005** | **BASE-API-010** | Same rejected structural-update transaction: unused rollback callback at `Server/ServerHandlers.cxx:703–729,748–797`; optimistic mutation and unconditional response application at `Client/Impl/Matchmaking.cxx:436–503,552–618,635–699`. Preserve both ends in one remediation. Moving only the response assignment behind `success` leaves the earlier optimistic value. |
| **BASE-STORAGE-011** | **BASE-NET-008** (contained achievement-save/retry failure) | `Shared/IniData.cxx:835–860` clears dirty state before an unchecked save; `Client/Impl/Stats.cxx:127–161` unconditionally reports success. STORAGE also covers stat/reset error propagation. Count the achievement-loss sequence once; fix persistence acknowledgment and caller results together. |
| **BASE-UTIL-002** | **BASE-STORAGE-012**, **BASE-STORAGE-022**; **BASE-API-002, presence portion only** | Same container lock-escape defect: `Shared_NoVer/AchievementsAndStatsContainer.cxx:57–83,109–117,138–146`; consumers at `Client/Impl/Stats.cxx:63–124`, `User.cxx:348–357`, `Friends.cxx:477–484`. UTIL also owns unlocked snapshot construction at lines 14–19. **Retain API-002's nickname race separately**: `Friends.cxx:148–154` versus writes at 76–83 and `User.cxx:305–310`; nickname is outside this container. |
| **BASE-SERVER-008** | **BASE-API-001, live-message request-ID collision only** | Sender-local IDs are broadcast at `Server/ServerHandlers.cxx:284–293` and consumed at `Client/Impl/Chat.cxx:111–143`. SERVER additionally covers room lookup fan-out/wrong interlocutor at 222–242. **API-001's unsolicited global history-success remains an additional obligation**: assigning notification ID zero prevents collisions but `NotifyAllNow` still emits retrieval success without a request. Separate event/reply semantics and recipient-local correlation are both required. |
| **BASE-CORE-001** | **BASE-STORAGE-009, ordinary queued notifications only**; **BASE-API-015, already-queued phase only** | `Client/Impl/ListenerRegistrar.hxx:309–331` captures raw specific listeners; `ListenerRegistrar.cxx:50–67` cannot cancel those captures. Do **not** retire either whole alias: cloud directly captures listeners in `CloudStorage.cxx:152–202`; WebSocket Channels retain them before event creation at `CustomNetworking.cxx:57–73,95–110,231`. Those producers need cancellation-aware admission as well. |

**Mirrored contract defect, separate implementations:** BASE-CORE-007 and BASE-INTERCEPT-009 both create on `GetInstance` (`Client/GalaxyApiFactory.cxx:166–174`; `InterceptionLogger/GalaxyApiFactory.cxx:178–186`). They can share a compatibility work item, but neither source fix repairs the other. SDK 1.64.0 `GalaxyFactory.h:31–64` separates null-query from creation; 1.57.0:30–38 explicitly creates on query. Preserve that version distinction and the interceptor's additional empty-callable consequence.

## 2. Definite corrections and challenged findings

### BASE-UTIL-015 — dormant, not a current build failure

**Reclassify Medium/confirmed Build to Informational/latent feature-integration defect.** `galaxy_sdk_features.cmake:234,255–267` enables RED only for inclusive **1.149.12–1.149.16**. Baseline directory inventory contains **69 SDK versions, zero in that interval**; the current directory inventory likewise jumps from 1.149.0 to 1.150.0. `DLLs/CMakeLists.txt:198–226` generates versions from those directories.

The architectural error is real: `Shared_NoVer/SharedLibUtils.cxx:99–118` selects a version-dependent basename inside a once-compiled target whose definitions lack that feature (`Shared_NoVer/CMakeLists.txt:3–13`). However, no current generated variant requests RED. Retract “current RED variants fail loading,” not the latent code defect. This is **not** an alias of BASE-INTERCEPT-007's independently reachable export-version gates.

### BASE-CORE-003 — retain High, with the exact callback contract

`SDK/GalaxyApi.h:458–470` puts notifications inside `ProcessData`; lines 344–364 require deleting self-registering listeners before shutdown. `SDK/IListenerRegistrar.h:148–160` additionally requires unregistering registrations. These conditions do **not** prohibit calling Shutdown from a callback.

A manually managed specific DLC listener can unregister itself, keep its object alive, and call Shutdown with no global/self-registering listeners remaining. `Client/Impl/Apps.cxx:108–123` queues that callback; `Client/GalaxyDLL.cxx:166–173` drains it. `Client/UniverseLAN.cxx:130–133` destroys the active runner, then `Client_NoVer/Impl/DelayRunner.cxx:9` accesses its dead queue on return. The network pump has the analogous member-queue continuation at `Shared/Networking/Networking.cxx:219–226`.

This needs neither nested `ProcessData` nor concurrent API calls nor a listener-precondition violation. Retain the concrete memory-safety finding; do not claim native-SDK behavior was established. BASE-API-018 remains informational because its distinct reproduction requires nested pumping and callback-view restoration.

### BASE-INTERCEPT-001 — proven teardown violation; native UAF conditional

**Reclassify the confirmed claim as Medium API/lifecycle, retaining High conditional memory-safety risk.** Client shutdown calls native shutdown before reset (`InterceptionLogger/GalaxyDLL.cxx:72–86`); game-server shutdown does likewise (`UniverseGameServer.cxx:39–54`). Reset destroys listener-bearing wrappers (`UniverseLANInterceptor.cxx:316–348`), whose `ListenersContainer.cxx:16–26` calls the cached registrar. These are genuine hidden registrations (`ListenersContainer.hxx:25–29`), so application cleanup cannot satisfy the native precondition for them.

`SDK/IListenerRegistrar.h:148–149` proves wrong ordering. It does **not** prove the native registrar is freed by every Shutdown: `SDK/GalaxyApi.h:344–364` specifies deactivation/pre-init state, not allocation lifetime. `SDK/ShutdownOptions.h:26–33` also exposes static preservation without identifying registrar ownership. The original sidecar already qualifies vendor behavior; carry that qualification into severity/category accounting instead of counting a proven native UAF. Preserve late-unregistration as definite. Detach while native interfaces remain valid, then invoke shutdown. This is independent of CORE-003's locally proven active-pump destruction.

### BASE-API-016 — retain Medium; pending events really outlive registry visibility

`Client/Impl/CustomNetworking.cxx:73,88,95–112` queues open/data/terminal events, then marks cleanup. Another successful open erases marked Channels at 149–163,213 before `DelayRunner` necessarily delivers their notifications. Thus A can receive final bytes and close between pumps; opening B destroys A's buffer, yet A's pending data callback subsequently runs with no readable channel. `SDK/ICustomNetworking.h:102–108,158–184` connects data notifications to that incoming buffer.

The publication race is also real: worker start at line 64 precedes insertion at 215; IXWebSocket's `start` creates a thread and `connect` invokes Open (`Vendor/IXWebSocket-12.0.1/ixwebsocket/IXWebSocket.cpp:180–184,239–245`). A concurrent pump can therefore expose the handle before insertion.

**Narrow the consequence:** pointer-derived ConnectionID is a lookup key, not a queued dereference of Channel. Destruction joins the worker; notification strings are copied. This is lost data/invalid or reused handles, not automatically Channel UAF. Also B is allocated **before** cleanup at line 205, so address reuse requires a later allocation, not B itself. Retain separately from listener cancellation (015) and the close-listener race (017).

### BASE-STORAGE-006 — retain Medium; sequential identity reuse is explicit

`Client/Impl/CloudStorage.cxx:24–31` returns counter **N** without increment while grouped; `OpenSavegame/CloseSavegame:583–597` only toggle a boolean. Uploads store that generated ID at 440–442/528–530. Therefore:

- `Open; Put A; Close; Open; Put B` assigns **N to both groups**.
- `Open; Put A; Close; Put B` assigns **N to A and the first ungrouped B**, then advances.

`SDK/ICloudStorage.h:484–496` promises a new savegame and different IDs after close; SDK 1.148.14:423–434 says the same. Neither timestamp coincidence nor cross-session uniqueness assumptions are needed. Allocate group identity at a boundary and synchronize the compound state. BASE-SERVER-006 is unrelated: its shared-file counter is never created/persisted, causing restart reuse of another ID namespace.

### Timeout evidence — retain the server consequence

The actual fork emits event **4** and resets the peer before returning it (`Vendor/Enet-IPv6/src/protocol.c:80–90,163–183`). `peer.c:389–443` clears `connectID` but leaves application `data`; timeout event data is zero. Neither supplies a preserved session generation.

Ignored timeout followed by slot reuse reaches `Server/ServerHandlers.cxx:40–45`, overwriting old data, while `Server/Peer.cxx:22–28` still resolves the old ID through that slot. `ServerHandlers.cxx:186–189` then dereferences the newcomer's potentially null `user_data`. Application sweeps may mask this, but a longer application timeout or activity without reliable acknowledgments permits it. Preserve the conditional High consequence; do not dismiss it because default timing often differs.

## 3. Related failures that must remain separate

- **Cancellation:** CORE-002's global invocation snapshot; STORAGE-013's registration after worker launch; STORAGE-017's private auth set; INTERCEPT-002's competing proxy deleters; INTERCEPT-003's missing registrar identity each require their own fix. Generic queued-notification cancellation alone closes none of these paths.
- **Connection state:** SERVER-001 uses immediate disconnect, which generates no local event (`Vendor/Enet-IPv6/src/peer.c:506–536`); NET-013 publishes duplicate ordinary disconnects; API-012 omits lobby-session invalidation even when disconnect arrives. STORAGE-019 ignores an authentication deadline. None is an alias of the omitted timeout event.
- **Persistence:** STORAGE-001 destructive replacement, UTIL-009 destructive copy rollback, UTIL-005 failed publication, UTIL-006 failed-unlink index removal, UTIL-008 unchecked close, UTIL-010 short-read padding, STORAGE-002 ignored statuses, STORAGE-016 source-read/worker completion and SERVER-007 false upload acknowledgment are distinct failure points. A shared transaction/result design must fix all implicated layers. STORAGE-004 missing hashes and STORAGE-005 ignored guarded deletion also remain distinct.
- **Initialization/security:** CORE-005 escaping initialization errors and INTERCEPT-008 swallowed initialization errors are different implementations. NET-001 pre-auth allocation, NET-002 escaping handler exceptions, SERVER-019 unauthenticated broadcasts and SERVER-016/INTERCEPT-011 secret-bearing logs are different mechanisms, despite a common hardening roadmap.

## 4. Priority cross-component roadmap

1. **P0 — prevent corruption, crashes and save loss:** CORE/API/STORAGE establish synchronous cancellable operation admission, pinned dispatch and deferred teardown; INTERCEPT adds owner-scoped proxy retirement, pre-shutdown detachment and bounded output tracing. UTIL/API/STORAGE introduce locked value/snapshot operations, including separate nickname synchronization. UTIL/STORAGE implement checked staged replacement and guarded deletion. NET/SERVER bound decoding before allocation, contain expected handler failures and retire timed-out peers before slot reuse.
2. **P1 — coherent sessions and protocol:** NET/SERVER unify retirement with explicit generations and exactly-once disconnect; API/STORAGE invalidate memberships and retire expired/sign-out work. Repair rollback, event/reply correlation, authoritative joinability/P2P admission and authenticated broadcast recipients. Coordinate file-share status, uploader identity, empty-file support and restart-safe IDs. API binds WebSocket registry cleanup to event delivery; STORAGE isolates callback snapshots and savegroup identity.
3. **P2 — compatibility and diagnostics:** fix reachable interceptor export/callback guards, factory semantics, option forwarding and error state. Address Windows timestamps/path identities, remaining API contracts and tracing defects. Keep RED integration dormant until a qualifying SDK is introduced. Hand focused cancellation, timeout-slot-reuse, failed-save/retry and callback-order scenarios to the existing BUILD/execution coordinator.

Validation in this pass: read-only baseline Source comparison excluding sidecars returned **no differences**; read-only Git directory counting returned **69 / 0 RED-range**. No builds or runtime tests ran. The sole authored artifact is this file. Findings without an explicit correction or overlap above retain their notebook disposition; partial aliases do not justify subtracting whole IDs from aggregate totals.
