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
