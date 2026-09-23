# Fresh baseline review — ListenerRegistrar.hxx

- Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`.
- Coverage: entire file, lines 1–418; Windows SDK versions selected by the feature matrix.
- Method: static inspection and caller/SDK tracing; no build or runtime execution.

## Specific checked notes

- Checked the version-dependent `Register`/`Unregister` argument type against SDK `IListenerRegistrar.h`, the listener-type arrays, and the callback member-function extraction/downcasts. Correct registration types remain a caller precondition.
- Traced request insertion, both pop overloads, reverse-index removal, and `std::any` payload ownership. The per-helper mutex protects the two maps together; removing an entry before handing out its raw pointer does not protect the subsequent callback lifetime.
- Traced `NotifyAll` through `std::bind_front`, `DelayRunner`, and `NotificationParamScopeExtender`: `const char*` payloads become owned strings, but listener pointers remain borrowed pointers.
- Concrete callers inspected: `FriendsImpl::RequestUserInformation` (self-user fast path), `AppsImpl::IsDlcOwned`, `UserImpl::SignIn`, and WebSocket notifications in `CustomNetworkingImpl`.
- Related defects owned by other sidecars: global dispatch snapshots (`BASE-CORE-002`, `ListenerRegistrar.cxx.review.MD`) and pump teardown (`BASE-CORE-003`, `../UniverseLAN.cxx.review.MD`).

## Confirmed finding

### BASE-CORE-001 — Unregister cannot cancel queued specific-listener callbacks

- **Severity:** High
- **Confidence:** High
- **Category:** Memory Safety
- **Location:** `Source/Client/Impl/ListenerRegistrar.hxx:231–269,309–331`; `ListenerRegistrar.cxx:50–68`.
- **Affected scope:** All versions/callers that enqueue a non-null specific listener; ordinary single-threaded use is sufficient.

**Evidence**

`NotifyAll` and `NotifyAllSpecificOnly` bind their arguments into a delayed callable. The specific listener is a raw pointer, so the lifetime extender forwards it unchanged. `Unregister` removes only global-set entries and request-helper entries. Neither those operations nor `NotifyAllNow` check/cancel the already bound listener. SDK 1.152.11 `IListenerRegistrar.h:156–165` promises unregistration from all pending asynchronous calls, and `GalaxyApi.h:99–103` says specific listeners may be unregistered at any time.

**Failure mechanism**

Call `Friends()->RequestUserInformation` for the local user with a heap-allocated `IUserInformationRetrieveListener`; `Friends.cxx:50–54` enqueues the pointer without entering `request_helpers`. Call `Unregister`, delete the listener, then call `ProcessData`. The queued callable still supplies the old pointer as `extra`; dispatch inserts it into the invocation set and invokes a virtual method on freed storage. `Apps.cxx:119–123` provides another direct caller. This does not require network timing or concurrent destruction.

**Impact**

Normal cancellation of a screen/request can produce a use-after-free, crash, or unintended callback into a replacement allocation.

**Possible solutions**

1. Track every specific-listener delivery using cancellable registration records shared by the queue and registrar.
2. Queue request/registration IDs rather than pointers and resolve them at dispatch, preserving global-listener delivery even if the specific listener was cancelled.

**Recommendation**

Use generation-bearing registration tokens and an invocation-lifetime protocol. `Unregister` must invalidate queued deliveries and coordinate already-started invocations; a pointer-only membership test would mishandle pointer reuse. Apply the same mechanism to immediate local completions and subsystem-owned pending listeners, not only network request maps.

**Verification**

Add a regression that queues the local-user information callback, unregisters and destroys the specific listener before the next pump, then pumps with a surviving global listener. Require zero specific callbacks, correct global delivery, and no Windows ASan/page-heap failure. Repeat for DLC completion and address reuse. These checks are proposed, not executed.
