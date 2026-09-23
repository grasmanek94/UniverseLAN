# Fresh baseline review — Impl/Listeners/ProxifySingleShotListener.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–68. Static Windows review; shallow serious-defect scope.

## Checked
- Checked null-preserving encapsulation, allocation/publication, target initialization, final-instruction callback macro and virtual deletion through SDK IGalaxyListener.
- Global tracing observers have null targets and survive callbacks; non-null targets are used for specific operations. Same-thread self-unregister is protected during the target call.
- Callback exceptions can bypass manual cleanup; nested dispatch of the same proxy is not reference-counted. Those are validation limits, not additional confirmed findings without a demonstrated SDK path.

## BASE-INTERCEPT-002 — Callback completion unconditionally deletes a proxy that cancellation may still own

- **Severity:** High
- **Confidence:** High
- **Category:** Concurrency
- **Location:** `Source/InterceptionLogger/Impl/Listeners/ProxifySingleShotListener.hxx:56–64`.
- **Affected scope:** All encapsulated specific-listener families during concurrent cancellation.

**Evidence and failure mechanism:** The macro clears protection, pops a mapping, ignores whether it found one and executes `delete this`. A second thread may already have popped that mapping into Unregister's local vector. If it pauses before real Unregister, the callback epilogue deletes the proxy first; cancellation later calls the SDK with the stale address and deletes it again via `delete_if_not_protected`. Separate container mutexes provide no ownership pin. General thread safety and asynchronous cancellation are documented in SDK `1.152.11/galaxy/GalaxyApi.h:99–106,310–314`.

**Impact:** Deterministic double-delete/use-after-free for the described interleaving. Correct single-thread self-unregister does not prevent it.

**Possible fixes:** Unified synchronized retirement state plus dispatch/cancellation references, or shared control-block ownership.

**Recommended resolution:** Replace unconditional self-delete with a unique retirement decision after all lifetime pins have been released. Use scope-bound dispatch cleanup, retaining reentrant SDK/game calls outside registry locks.

**Verification:** Barrier-controlled callback/cancel overlap with cancellation paused after pop; Windows ASan and destruction counters must prove one final destruction. Test callback self-unregister and several proxies for one target as regressions. Proposed only.

## BASE-INTERCEPT-003 — Proxy records cannot identify their owning client/server registrar

- **Severity:** High
- **Confidence:** High
- **Category:** Memory Safety
- **Location:** `Source/InterceptionLogger/Impl/Listeners/ProxifySingleShotListener.hxx:16–20,30–32,43–50`.
- **Affected scope:** Same specific listener instance used by client and game-server sessions.

**Evidence and failure mechanism:** Encapsulation publishes only proxy and target; the global map has no registrar/session/type field. Therefore cancellation cannot distinguish two proxies for the same target in different sessions. The registrar implementation extracts both, unregisters both on only its own real registrar, and deletes the other session's still-registered proxy. A client/server pair of CreateLobby operations with one ILobbyCreatedListener suffices. SDK 1.152.11 game-server overview and distinct registrar declarations establish these ownership domains.

**Impact:** Use-after-free when the other session delivers its callback, even with serialized calls and a live target.

**Possible fixes:** Owner-scoped registries or owner-aware records/encapsulation APIs.

**Recommended resolution:** Include immutable owner identity and listener type in the proxy control record and filter cancellation by owner. Session teardown must only retire its own records.

**Verification:** Two independently recording fake registrars and one target; cancel one domain and complete the other, checking allocation lifetime and callback delivery. Proposed only; counted once with the implementation/registrar reports.
