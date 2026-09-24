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

## Follow-up review addendum — 2026-09-24

Reread the complete 68-line header and 92-line implementation.

### BASE-INTERCEPT-002 — Addendum: distinguish proven cancellation overlap from hypothetical nested dispatch

- **Severity:** High, retained for the recorded concurrent cancellation sequence
- **Confidence:** High for that sequence; SDK behavior after escaping callbacks is unverified
- **Category:** Concurrency
- **Location:** `Source/InterceptionLogger/Impl/Listeners/ProxifySingleShotListener.hxx:56–64`; `.cxx:18–37,55–91`; `Impl/ListenerRegistrar.cxx:43–48`.
- **Affected scope:** Non-null operation-specific proxies, with the original target kept alive.

**Evidence / failure mechanism**

The original cancellation interleaving remains valid: cancellation can extract the raw proxy before making any native call, while a currently executing target returns and its epilogue deletes that proxy. Later cancellation deletes it again. This needs no unsupported reentrant ProcessData, target destruction, or concurrent invocation of the same native callback. The protection set does cover an ordinary same-thread self-unregister that returns normally.

The set is not a nesting count, and a throw from `target->func` bypasses protection-disable, map-pop and deletion. A self-unregister followed by such a throw can leave a protected allocation with its mapping already removed. However, the inspected SDK contract (`1.152.11/galaxy/GalaxyApi.h:99–106`) makes specific registrations one-event registrations; it does not establish legal nested delivery of the *same proxy* or recovery semantics for an exception escaping a callback. Reusing the original target for a new request creates a different proxy and is not proof of same-proxy recursion.

**Impact**

The confirmed race remains a double-delete/use-after-free. Escaping-throw cleanup leaks and recursive same-proxy deletion are recorded as conditional validation concerns, not new confirmed crashes or extra IDs.

**Possible solutions / recommended resolution**

Use one retirement protocol with callback/cancellation pins and scope-bound cleanup. Record cancellation and dispatch depth as state rather than treating membership in an independently locked set as ownership. Establish the SDK's exception policy before deciding whether to propagate or contain application exceptions.

**Verification**

Proposed only: retain the barrier-controlled race test; add normal self-unregister, a second request using the same target, SDK-approved nested pumping, and throwing-target cases with and without self-unregister. Check map entries, protection entries and exact destruction counts, and distinguish native exception containment from a fake dispatcher's chosen behavior. No build, test, sanitizer or callback execution ran. BASE-INTERCEPT-003's module/address clarification is in the registrar sidecar.
