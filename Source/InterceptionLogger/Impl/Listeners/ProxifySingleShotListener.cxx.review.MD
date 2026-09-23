# Fresh baseline review — Impl/Listeners/ProxifySingleShotListener.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–92. Static Windows review; shallow serious-defect scope.

## Checked
- Read insertion, both removal directions, all protection-set operations and mutex boundaries.
- The erase-while-iterating loop is well-formed. Returned vectors contain raw pointers with no retained ownership, and the separate protection set is a boolean membership set rather than a lifetime reference count.
- Traced callback entry/exit and self-unregister without relying on prior reviews. Exception exits from game callbacks and nested dispatch of the same proxy remain additional validation limits; the findings below need neither.

## BASE-INTERCEPT-002 — Map removal does not pin proxies against callback deletion

- **Severity:** High
- **Confidence:** High
- **Category:** Concurrency
- **Location:** `Source/InterceptionLogger/Impl/Listeners/ProxifySingleShotListener.cxx:18–37,74–91`.
- **Affected scope:** Concurrent Unregister and specific-listener completion.

**Evidence and failure mechanism:** `pop_proxies_from_real` erases a proxy from the map, then returns its raw address. `delete_if_not_protected` tests a separately synchronized set and directly deletes. A cancellation thread can pop and pause; the callback thread can subsequently clear protection, fail to find its already-popped entry, and self-delete in the header macro. Cancellation then sees no protection and double-deletes the stale address. SDK 1.152.11 `GalaxyApi.h:99–106,310–314` documents cancellation and general thread safety.

**Impact:** Heap corruption/use-after-free. Mutexes make map/set operations individually safe but do not transfer ownership between them.

**Possible fixes:** A stable shared control block or a unified refcount/state machine for dispatch, cancellation and retirement.

**Recommended resolution:** Return pinned records, not unowned pointers, and permit one final deleter only after both dispatch and cancellation references are released. Avoid holding registry locks during arbitrary SDK/game calls.

**Verification:** Pause after map removal, complete callback self-retirement, then resume cancellation under Windows ASan; require one deletion and no stale SDK call. Include same-thread self-unregister to preserve currently working reentrancy. Proposed only; duplicate location of the same unique finding.

## BASE-INTERCEPT-003 — Global target-only lookup crosses registrar ownership boundaries

- **Severity:** High
- **Confidence:** High
- **Category:** Memory Safety
- **Location:** `Source/InterceptionLogger/Impl/Listeners/ProxifySingleShotListener.cxx:11–15,18–29`.
- **Affected scope:** Shared listener targets used for separate client and game-server operations.

**Evidence and failure mechanism:** `add` stores only proxy-to-real pointers; `pop_proxies_from_real` removes every matching target without owner identity. When the same ILobbyCreatedListener is passed to client and server CreateLobby, client cancellation extracts both. `ListenerRegistrarImpl::Unregister` sends both to the client registrar and deletes both, leaving the server's pending proxy dangling. SDK game-server documentation explicitly defines an independently controlled session and registrar (`1.152.11/galaxy/GalaxyGameServerApi.h:43–51`, `IListenerRegistrar.h:174–192`).

**Impact:** Later dispatch by the unaffected SDK session uses a freed callback object; no concurrent interleaving is required.

**Possible fixes:** Separate registries per owning session, or store owner/type/target in each record and filter cancellation accordingly.

**Recommended resolution:** Carry owner identity through encapsulation and make pop/select operations registrar-scoped. Combine with lifetime pins from BASE-INTERCEPT-002.

**Verification:** Two fake registrars, same target, two pending proxies; client cancellation must leave the server registration and allocation intact through server completion. Repeat after restarting one session. Proposed, not executed.
