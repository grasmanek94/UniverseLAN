# Fresh baseline review: User.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Entire file read, lines 1–673; matches baseline. Static Windows review; no production edits, builds, credential access, or runtime reproduction.

## File-specific inspection

- Read every authentication entry point and feature branch, sign-out, state query, user-data request/mutation/enumeration, token/ticket/session facade, online-state update, lazy user lookup, pending authentication listener operation, and connection transition.
- Traced SDK `IUser.h` authentication, optional listener, sign-out, and copy contracts; registrar cancellation; current `ProcessData` ordering; client transport/auth events; server user-data response and authenticated sender rewriting; Shared user-data storage and persistence.
- Authentication is intentionally configuration/LAN-based: credentials/tickets are not validated against third-party services and token getters return a fixed emulation value. No real-service authentication bypass or credential vulnerability is claimed on that basis. Console-platform overloads were inspected textually, not executed on Windows.
- `GetGalaxyUserData` returns owned shared objects, recognizes all three self-ID forms, and constructs placeholders for unknown peers under a map mutex. A missing peer is not a demonstrated null pointer. The configured local object is established before User construction in the inspected normal initialization path.
- `GetUserData` returns a reference-backed pointer, not a temporary string pointer; its SDK explicitly excludes general thread safety. The `Copy` variant has a separate confirmed problem below. Enumeration performs the copy while holding the user-data lock and checks the end iterator.
- Null optional listeners are valid and ordinary `NotifyAll` handles them by notifying globals. Required strings are not assumed nullable without a contract. The authorization-code exception is a valid default-argument path, detailed below.
- `DeleteUserData` deliberately uses an empty value, matching the SDK's specified equivalence to `SetUserData(key, "")`; retaining an empty map entry is not independently reported as a delete defect.
- Success notifications for local writes inherit Shared persistence limitations (BASE-STORAGE-011). Ordinary deferred specific listeners also inherit CORE's generic cancellation gap; the private auth waiting set below needs its own integration even if the registrar queue is fixed.

## Findings

### [BASE-STORAGE-017] Waiting authentication listeners are not removed by Unregister

- **Severity:** High
- **Confidence:** High
- **Category:** Memory Safety / asynchronous lifetime
- **Location:** `Source/Client/Impl/User.cxx:74–77,610–621,630–651`.
- **Affected scope:** Sign-in pending a server authentication response; per-call listeners cancelled before completion.

**Evidence:** `SignIn` inserts the raw listener into `waiting_auth_listeners`. `RunForAllWaitingAuthListeners` copies/drains that private set and invokes callbacks through `NotifyAllNowSpecificOnly`. Registrar `Unregister` removes only its global set and request-helper maps (`ListenerRegistrar.cxx:50–68`), with no connection to this set. SDK `IListenerRegistrar.h:156–165` explicitly covers pending asynchronous calls.

**Failure mechanism:** Before server acceptance, call a sign-in method with listener L. Cancel by unregistering L and destroying it. A subsequent accepted connection drains the waiting set and calls L's stale virtual method. The game can perform cancellation and destruction on the same thread before pumping, so the fault does not depend on a concurrent destructor race. A listener passed both globally and specifically can also be notified twice by the separate dispatch paths; deduplication should be addressed by the same lifecycle design.

**Impact:** Use-after-free when a login screen is closed or replaced while connecting. A common UI lifecycle follows precisely this pattern.

**Possible solutions:** Store registrar-owned request tokens instead of raw pointers; connect unregistration to the waiting set with safe synchronization; or centralize authentication operation ownership/cancellation.

**Recommended resolution:** Admit authentication requests through the registrar synchronously, and resolve a still-live registration at dispatch. Preserve global notifications without double-calling the same listener. A generic delayed-notification fix alone does not remove this private-set retention.

**Verification:** Hold server acceptance, issue sign-in, unregister/destroy L, then release acceptance and pump with Windows ASan. Expect no call to L and a valid completion for a retained control listener. Test a globally registered listener also passed as the specific listener, requiring only the intended notification count.

### [BASE-STORAGE-022] GetUserDataCopy copies an unlocked mutable string

- **Severity:** High
- **Confidence:** High
- **Category:** Concurrency / Memory Safety
- **Location:** `Source/Client/Impl/User.cxx:348–358`; concurrent writers at `305–310,361–381,568–574`.
- **Affected scope:** Games using the documented thread-safe copy API while user data changes.

**Evidence:** The method binds `const std::string& str` from `stats.GetUserData(key)` and only then copies it. `AchievementsAndStatsContainer.cxx:109–117` releases `mtx_userdata` before returning that reference. `SetUserData` assigns the same string under that lock; response handling can replace the entire stats/user-data map. SDK `IUser.h:592–615` specifically contrasts the unsafe pointer getter with the copy method.

**Failure mechanism:** Thread A obtains the reference and pauses. Thread B processes a live user-data update with a longer value, reallocating the string, or applies a response replacing its map. A's subsequent `safe_copy_str_n` reads size/data while the object changes or after its entry is destroyed. A background game/UI thread copying cached user data while the main thread pumps network events is a realistic supported usage.

**Impact:** Data race, torn values, or use-after-free despite choosing the copy API for safety. Passing a valid writable destination does not prevent the source lifetime failure.

**Possible solutions:** Return a string value snapshot from the Shared getter; perform lookup and copy inside `run_locked_userdata`; or publish immutable snapshots.

**Recommended resolution:** Keep the lock for the full lookup/read/copy or produce an owning snapshot under it. Preserve appropriate missing-key semantics and avoid invoking callbacks while locked. Coordinate with UTIL's borrowed-reference APIs and BASE-STORAGE-012.

**Verification:** Synchronize two threads to interleave lookup with long-string replacement and map replacement, then repeatedly copy with realistic buffer lengths under Windows ASan. Check exact complete values and lock coverage; sanitizer silence alone is not evidence of race freedom.

### [BASE-STORAGE-018] SignOut emits notifications without changing authentication state

- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness / state machine
- **Location:** `Source/Client/Impl/User.cxx:43–47,253–259,440–445,624–671`.
- **Affected scope:** Versions exposing sign-out, after an accepted LAN connection.

**Evidence:** `SignOut` only queues `OnAuthLost` and an operational state still containing `SIGNED_IN`. It does not change configuration, `logged_on`, `connected`, pending sign-ins, or request state. `SignedIn` reads the configuration boolean and `IsLoggedOn` remains `logged_on && SignedIn()`. SDK `IUser.h:562–570` requires signing out and finishing pending asynchronous operations.

**Failure mechanism:** Establish a signed-in/logged-on session, call `SignOut`, then pump. The auth-lost callback arrives, but both queries remain true. Outstanding sign-in operations are not retired and a later connection event can dispatch success through the old waiting set. Sign-out therefore creates contradictory observable states rather than an actual transition.

**Impact:** Games cannot reliably return to a logged-out state, cancel authentication-dependent work, or sequence reauthentication. This is a local compatibility/lifecycle defect; no third-party security compromise is asserted.

**Possible solutions:** Separate configuration's permitted simulated identity from runtime auth state; centralize sign-in/sign-out transitions; or explicitly model signed-in/offline/online/logged-out states and operation cancellation.

**Recommended resolution:** Implement a real sign-out transition before dispatching completion, clear runtime login state, finish/cancel pending operations as specified, and prevent late replies from reviving the prior session. Keep configuration policy immutable rather than using it as the runtime state variable.

**Verification:** Sign in, begin a pending request, sign out, and pump. Assert coherent queries and operational bits, one appropriate terminal result for pending work, and rejection of a late prior-session success. Then sign in again and verify normal operation.

### [BASE-STORAGE-019] SignInGalaxy ignores timeout and can remain pending indefinitely

- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness / asynchronous completion
- **Location:** `Source/Client/Impl/User.cxx:55–85,107–121,624–671`.
- **Affected scope:** Unavailable/nonaccepting LAN server; especially versions exposing explicit timeout (feature introduced at 1.152.8).

**Evidence:** `requireOnline` and `timeout` are discarded when the wrapper calls `SignIn(listener)`. With configured sign-in true and `logged_on` false, the listener is merely stored. A disconnected transition emits operational state but does not fail or complete waiting sign-ins. SDK `IUser.h:439–443` defines timeout in seconds for the auth listener.

**Failure mechanism:** Connection initiation succeeds but no server acceptance arrives, such as an unreachable address or rejected authentication/repeated reconnect. Call `SignInGalaxy(true, 1, L)` and keep pumping. No timer or deadline exists to complete L at the requested timeout. With `requireOnline=false`, offline behavior is likewise not distinguished; the explicit ignored deadline alone establishes the finding.

**Impact:** Login/progress screens can wait forever rather than taking their timeout/fallback path; retained listeners also enlarge the exposure of BASE-STORAGE-017.

**Possible solutions:** Track an operation deadline and complete on expiry; use the networking timeout as an explicit mapped failure if compatible; or complete locally when online access is not required and the simulated identity is available.

**Recommended resolution:** Preserve `requireOnline` and per-call timeout in an auth operation state machine. Deliver exactly one success/failure, cancel its timer when resolved, and ignore late replies for expired operations. Use an available SDK failure reason appropriate to the selected version.

**Verification:** With an unreachable server and valid local initialization, request a short explicit timeout and pump beyond it. Require one failure within a defined tolerance and no later duplicate success. Test online-required versus offline-allowed modes and reconnect after timeout.

### [BASE-STORAGE-020] Optional listener routing suppresses authentication and OpenID completions

- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness / API contract
- **Location:** `Source/Client/Impl/User.cxx:520–527,542–557`.
- **Affected scope:** Authorization-code sign-in using a global listener; unsupported PlayFab calls using a specific listener.

**Evidence:** `SignInAuthorizationCode` requires `listener != nullptr` before doing anything, although the SDK supplies `NULL` as the default and documents global listeners (`IUser.h:547–560`). Both PlayFab wrappers accept a specific listener but call the `NotifyAll` overload without it. Other authentication wrappers correctly forward nullable listeners.

**Failure mechanism:** After settling initial connection events, register a global auth listener and call authorization-code sign-in with nonnull code/URI and omitted listener: the method is a no-op, so no result is queued. Conversely, call either PlayFab operation with a specific nonglobal listener: even the intentional unsupported-operation failure never reaches that listener.

**Impact:** Callers wait for completions that cannot arrive or miss their supported failure/fallback path. This finding does not demand implementation of PlayFab or real OpenID services.

**Possible solutions:** Forward the nullable auth listener to the common path and pass specific PlayFab listeners to the existing notification helper; centralize listener-aware unsupported-operation completion.

**Recommended resolution:** Treat the listener solely as a delivery target, not a condition for executing an otherwise valid request. Preserve global delivery and add the supplied specific listener for failures. Use the cancellation-safe registrar mechanism rather than introducing new raw deferred captures.

**Verification:** Exercise null/global-only, specific-only, and the same object globally registered plus specifically passed. Require the correct success/failure route and count for each affected API, with unrelated connection notifications drained first. Dummy argument strings suffice; no external credentials or services are needed.

## Source-first re-review addendum — 2026-09-24

Read all `User.cxx:1-673` and `User.hxx:1-814` before baseline comparison, including every historical auth overload. BASE-STORAGE-017/018/020/022 remain supported; 019 is expanded below. Required credential/string inputs were not treated as legally nullable. The default null authorization-code listener is legally optional, so 020 remains a real routing defect. No credential files or real credentials were accessed. Fixed token/ticket emulation is not characterized as real-service authentication.

### [ADD-STORAGE-005] Older SDK remote user-data requests never notify their global completion listener

- **Severity:** Medium
- **Confidence:** High
- **Category:** API/ABI / asynchronous correctness
- **Location:** `Source/Client/Impl/User.cxx:297-318`, especially the preprocessor guard at 313; declarations `User.hxx:449-456`.
- **Affected scope:** Versions where `HAS_SPECIFICUSERDATALISTENER` is true but `HAS_REQUESTUSERDATA_ISPECIFICLISTENER` is false; concrete shipped SDK example 1.125.2. The per-call-listener gate is true only for 1.134.10 and from 1.138.1 onward (`Source/galaxy_sdk_features.cmake:50,177,189`).

**Evidence:** Remote requests are sent at 287-293 and responses update the cache at 305-310. The *entire* `OnSpecificUserDataUpdated` notification is guarded by availability of the newer per-operation argument, rather than availability of the global listener type. The fallback `IUserDataListener` is only called for self IDs. SDK `Source/DLLs/1.125.2/galaxy/IUser.h:161-184,380-387` defines `GlobalSpecificUserDataListener` and promises it for `RequestUserData(GalaxyID)`, despite that version lacking a listener parameter. `ServerHandlers.cxx:176-195` returns the requested remote ID and full data; `ClientNetworkHandlers.cxx:98-101` reaches this handler.

**Failure mechanism:** In 1.125.2, register a global specific-user-data listener, drain unrelated events, and request a connected remote user's data. A valid server response updates the requested cache. The required notification is compiled out, and the self-only notification is skipped. The game waits indefinitely for completion even though retrieval succeeded. Live `SetUserDataMessageReceived` notifications at 568-574 use the older type gate correctly, so an unrelated later live update can misleadingly appear to complete the request.

**Impact:** Supported older games cannot reliably sequence remote data retrieval. Latest-version tests and tests of live updates do not establish correctness of this version branch. This is different from BASE-STORAGE-020's latest authorization-code/PlayFab argument routing.

**Possible solutions:** Guard the global notification by listener-type availability and conditionally insert only the extra listener argument; or centralize a version-independent completion helper that accepts an optional listener internally.

**Recommended resolution:** Always emit the supported remote global update notification, retaining per-operation dispatch on SDKs that expose it. Preserve self-specific/current-user notifications and cancellation semantics. No protocol change or implementation of unsupported services is needed.

**Verification:** Proposed 1.125.2 global-only remote request must complete without any subsequent SetUserData or stats request; compare with latest specific-only/global-only cases. `Source/SystemTests/Host/Stats.cxx:185-203` currently waits on the later stats response to bound the legacy data request and never checks this global callback, so that test masks the defect. `Host/UserData.cxx:64-79` tests the separate live-update path. Static gate evaluation only; no version build/test was run.

### BASE-STORAGE-019 — ADDENDUM CORRECTION: auth admission can miss an already-delivered acceptance

- **Disposition:** Retained and expanded under the existing pending-auth completion ID; no duplicate ID for the header's previously noted check-then-enqueue gap.
- **Severity:** Medium (unchanged)
- **Confidence:** High
- **Category:** Concurrency / asynchronous correctness
- **Location:** `Source/Client/Impl/User.cxx:55-77,610-628,642-651`; `User.hxx:80-88`.
- **Affected scope:** Concurrent sign-in API calls and `ProcessData`; specific auth listeners. The ignored explicit timeout remains version-gated from 1.152.8.

**Evidence:** `SignIn` checks the plain `logged_on` bool outside `mtx_waiting_auth_listeners`, then inserts under that mutex. Acceptance sets `logged_on` and separately drains the waiting set. There is no state recheck while admitting the waiter. Transport Tick only queues events: `Client.cxx:37-43,79-82`, `Source/Shared/Networking/Networking.cxx:146-165,219-226`, and `GalaxyDLL.cxx:166-173` place the state handler on the application's pump thread.

**Failure mechanism:** Thread A observes not logged on and pauses before insertion. Thread B pumps acceptance, sets logged_on, drains the empty set, and delivers globals. A then inserts its specific listener after that drain; a healthy accepted connection has no reason to send another acceptance. The listener remains pending despite success already occurring. Concurrent access to the plain bool also lacks synchronization; simply making it atomic would still leave the logical lost-wakeup sequence. This does not require a second concurrent pump or a native transport callback into User.

**Impact:** A specific login UI can wait indefinitely even with a working server, in addition to the existing no-timeout failure on unavailable servers. Retained raw listeners still interact with BASE-STORAGE-017.

**Possible solutions:** One lock covering state inspection/admission/acceptance drain; an operation state machine with synchronized generations; or serialized auth commands plus cancellable waiter tokens.

**Recommended resolution:** Atomically decide between immediate completion and pending admission with respect to every auth transition, release state locks before invoking listeners, and implement per-operation deadlines/cancellation. Narrow the original timeout observation to the SDK versions actually exposing that argument; do not infer a configured networking reconnect timeout is the same contract.

**Verification:** Proposed barriers pause sign-in between its state check and insertion while another thread processes acceptance, then resume. Require exactly one specific result without another reconnect. Repeat unavailable-server explicit timeout separately. Windows ASan alone cannot prove bool race freedom; inspect complete synchronization. No concurrency experiment was run.

## Targeted ABI handoff — persona gate / BASE-API-005 clarification, 2026-09-24

**Disposition: confirmed undefined consumer macro; no distinct confirmed sign-in notification contract defect and no ADD-ABI-002.** BASE-API-005 remains the existing Medium / High-confidence automatic-persona-retrieval/publication finding, primary in [Friends.cxx.review.MD](Friends.cxx.review.MD). This clarification adds no finding count or severity change.

**Exact evidence**

- `User.cxx:67,655` tests `GALAXY_BUILD_FEATURE_HAS_IFRIENDS_ONPERSONADATACHANGED`. `Source/galaxy_sdk_features.cmake:16` defines the feature name **`IFRIENDS_ONPERSONADATACHANGED`**, and `290-305` emits `GALAXY_BUILD_FEATURE_IFRIENDS_ONPERSONADATACHANGED=0/1`. Source/build-definition searches found no definition or alias for the additional-`HAS_` spelling. Under the repository's normal definitions, both undefined `#if` expressions evaluate to zero; neither notification at `68,656` is compiled in. This is a consumer spelling mismatch, not an incorrect SDK version interval.
- The first suppressed body follows an already-logged-on sign-in success (`55-73`); the second follows accepted connection/auth notification (`642-660`). Both would notify the **local** user with **`PERSONA_CHANGE_NONE`**. Neither path updates persona name/avatar or performs `RequestUserInformation` for remote friends/lobby members. The configured self cache already exists (`24-35`); `Friends.cxx:103-107` treats self information as available.
- Examined SDK contracts: 1.61.0 `IFriends.h:34-63,131-138` defines change notifications and explicit-request responses; 1.73.0 `IFriends.h:32-61,207-215` does the same. 1.73.0 `IUser.h:225-263` promises sign-in responses to **IAuthListener** and operational-state notifications. 1.152.11 `IUser.h:414-443` makes the same distinction; `IFriends.h:58` explicitly defines NONE as “No information has changed.” These declarations do **not establish an unconditional self-persona notification for every successful sign-in**. The absence of a matching promise is a limit on this finding, not proof that native Galaxy never emits such an event.
- A genuine positive contract exists in 1.152.11 `IFriends.h:645-667`: explicit user-information responses go to persona/information listeners, and requests are automatic for friends and fellow lobby members. The explicit self path uses the **correct** gate and queues its persona notification (`Friends.cxx:38-54`); the remote response path also uses the correct gate (`87-99`). Those calls are not suppressed by the User typo.

**BASE-API-005 relationship / impact limit**

`User.cxx:297-319` can update a remote nickname without publishing Friends availability/persona state. The existing BASE-API-005 already covers hello/user-data routing, omitted automatic friend/member retrieval, and later actual-name-change publication (see its preserved Friends addenda). Changing `User.cxx:67,655` only restores two intended **self/NONE** notifications; it does not repair that remote path. Conversely, sign-in alone with no identified persona change is not enough to prove a game is owed this extra callback, so no new behavioral-ID claim is justified by the undefined macro alone.

**Resolution / proposed verification**

Align the consumer feature spelling in a future implementation change and check intended self-notification semantics against a matching native SDK trace or an explicit product compatibility policy. Add a feature-reader/definition consistency check and verify the disabled boundary before 1.61.0. Keep BASE-API-005's automatic friend/member retrieval and genuine persona-change regressions under its existing ID. For the sign-in question, distinguish (a) unchanged self sign-in, (b) explicit `RequestUserInformation(self)`, and (c) a real name/avatar change; record callback order, IDs and flags instead of assuming auth implies a persona change. No builds, tests, native calls or credential reads were performed here.
