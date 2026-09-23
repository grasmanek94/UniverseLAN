# Fresh baseline review — Impl/ListenerRegistrar.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–54. Static Windows review; shallow serious-defect scope.

## Checked
- Traced direct global registration and specific-proxy cancellation into both proxy maps and callback self-destruction.
- The erase loop in `pop_proxies_from_real` advances correctly; same-thread self-unregister from one callback leaves its protected proxy for the callback epilogue to delete. Neither observation establishes cross-thread lifetime safety.
- Checked SDK 1.152.11 `IListenerRegistrar.h:156–165` and `GalaxyApi.h:99–106,310–314`: pending calls may be unregistered, specific listeners are reusable and the API is generally thread-safe.

## BASE-INTERCEPT-002 — Unregister's raw proxy list races callback self-destruction

- **Severity:** High
- **Confidence:** High
- **Category:** Concurrency
- **Location:** `Source/InterceptionLogger/Impl/ListenerRegistrar.cxx:43–48`; proxy epilogue at `Impl/Listeners/ProxifySingleShotListener.hxx:60–64`.
- **Affected scope:** Specific-listener completion concurrent with Unregister on another thread.

**Evidence and failure mechanism:** Unregister removes map entries and receives unowned raw proxy pointers. The callback protects itself only while calling the game listener, then unprotects, pops its map entry and unconditionally deletes itself. Interleaving: (1) thread A is inside the game callback; (2) thread B pops the proxy into its local vector and pauses before real Unregister; (3) A returns, removes protection, finds no map entry and deletes the proxy; (4) B resumes, submits the stale pointer to real Unregister and calls `delete_if_not_protected`, which deletes it again. Any vendor synchronization inside Unregister occurs too late to preserve the wrapper's raw pointer.

**Impact:** Double deletion/use-after-free during supported concurrent cancellation, even while the real game listener itself remains alive. The map mutex and protection-set mutex protect containers, not ownership across these steps.

**Possible fixes:** Shared ownership of a stable proxy control block, or one synchronized state machine with callback and cancellation pins and a unique retirement decision.

**Recommended resolution:** Acquire a lifetime pin when taking a proxy for cancellation; make callback completion and cancellation participate in one retirement protocol. Release external SDK/game calls outside registry locks to preserve reentrancy.

**Verification:** Barrier-controlled fake SDK: pause Unregister immediately after pop, finish the game callback, then resume cancellation. Windows ASan and destruction counters must show exactly one destruction. Also test self-unregister and cancellation of several pending proxies. Proposed, not executed.

## BASE-INTERCEPT-003 — Cancellation deletes proxies belonging to the other SDK session

- **Severity:** High
- **Confidence:** High
- **Category:** Memory Safety
- **Location:** `Source/InterceptionLogger/Impl/ListenerRegistrar.cxx:43–48`; shared registry at `Impl/Listeners/ProxifySingleShotListener.hxx:16–20`.
- **Affected scope:** Concurrently initialized client and game-server SDK sessions, using the same specific listener object.

**Evidence and failure mechanism:** `pop_proxies_from_real(listener)` is process-wide and selects by target pointer alone. Each returned proxy is unregistered using this registrar's `intf()`, then deleted. Use one `ILobbyCreatedListener` instance for one client CreateLobby and one GameServer CreateLobby. Client Unregister extracts both proxies; unregistering the game-server proxy on the client registrar cannot cancel the game-server pending registration. The proxy is nevertheless deleted, leaving the real game-server dispatcher with a dangling callback pointer. SDK `1.152.11/galaxy/GalaxyGameServerApi.h:43–51` defines separate sessions/listeners; `IListenerRegistrar.h:178,192` exposes distinct registrars.

**Impact:** A later server callback dispatch can use freed memory. This requires no race and no invalid listener type or destroyed application object.

**Possible fixes:** Per-session proxy registries, or records keyed by registrar/session identity, listener type and target.

**Recommended resolution:** Attach immutable owner identity/type to every encapsulated proxy and cancel only records belonging to the requested registrar. Retire only after unregistering with the owning real SDK; combine with BASE-INTERCEPT-002 lifetime pins.

**Verification:** Register two pending CreateLobby proxies for one target against two fake registrars. Unregister only on the client; assert that the server proxy remains alive and receives its callback. Repeat with sessions reversed and with session shutdown. Proposed only.
