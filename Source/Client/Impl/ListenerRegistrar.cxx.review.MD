# Fresh baseline review — ListenerRegistrar.cxx

- Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`.
- Coverage: entire file, lines 1–239.
- Method: static inspection; traced SDK unregistration and all four dispatch overloads.

## Specific checked notes

- `Register` and `Unregister` reject null pointers and listener types outside the SDK range before indexing.
- Global registration is idempotent through `std::set`; the extra-listener overload deduplicates a listener that is also globally registered.
- Each global set and request helper is locked for mutation. Dispatch deliberately releases the set lock before calling application code, avoiding a lock held across arbitrary callbacks but leaving raw snapshot lifetimes unprotected.
- Destructor diagnostics enumerate outstanding global listeners; explicit SDK shutdown requires callers to unregister first.
- Queue cancellation is separately documented as `BASE-CORE-001` in the header sidecar.

## Confirmed finding

### BASE-CORE-002 — A dispatch snapshot invokes listeners removed by an earlier callback

- **Severity:** High
- **Confidence:** High
- **Category:** Memory Safety
- **Location:** `Source/Client/Impl/ListenerRegistrar.cxx:88–117,137–147,169–207,227–237`.
- **Affected scope:** Global and mixed global/specific notifications; single-thread reentrancy and concurrent unregister.

**Evidence**

Both `ExecuteForListenerType` implementations copy the registered `IGalaxyListener*` set, unlock, and pass the snapshot to a loop that calls every pointer. `Unregister:62–67` only modifies the original set/helper. SDK 1.152.11 `IListenerRegistrar.h:156–165,231–235` defines cancellation and automatic unregistration on destruction.

**Failure mechanism**

Register A and B for one notification, arranging A before B in the set's pointer order. During A's callback, unregister and destroy B. Returning to the dispatch loop invokes B from the stale snapshot. Alternatively, after the snapshot is copied, another thread can unregister/destroy B before dispatch reaches it. The set mutex prevents container races but establishes no ownership or invocation barrier for the copied objects.

**Impact**

Listener-driven UI/session cleanup can cause a virtual call through freed storage despite proper `Unregister` use. The same-thread case makes this more than a speculative parallel-API hazard.

**Possible solutions**

1. Snapshot stable registration records with cancellation/generation state and acquire an invocation guard before each call.
2. Serialize dispatch/unregistration on a designated pump thread, with explicit deferral of destruction and support for removing a later listener during callbacks.

**Recommendation**

Share the cancellable-registration mechanism recommended in `BASE-CORE-001`. Skip records cancelled since snapshot creation; coordinate in-flight calls when unregistering from another thread. Merely locking while copying or checking membership and then unlocking still leaves a destruction race.

**Verification**

Use two listeners where the first unregisters/deletes the second. Assert that the second is not invoked. Add a deterministic barrier between snapshot and invocation for a second-thread unregister test, plus self-unregistration and re-registration/address-reuse cases. Run Windows ASan/page heap when permitted. No such execution occurred in this review.
