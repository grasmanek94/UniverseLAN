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

## Full-reread addendum — BASE-CORE-001 scope correction, 2026-09-24

**Disposition: retain High severity / High confidence / Memory Safety; broaden the existing ID's cancellation-lifetime coverage. No new ID and no extra finding count.** The original queued-callback proof remains valid, but a queue-only repair would leave an independently traced admission-to-invocation gap in network completions.

- **Exact additional location:** `ListenerRegistrar.hxx:91–110,232–251,356–368`; caller `Source/Client/Impl/Matchmaking.cxx:55–74`; cancellation `ListenerRegistrar.cxx:50–68`.
- **Affected scope:** Specific lobby-created/lobby-entered listeners in `LOBBY_LISTENERS` builds (threshold 1.125.0), and other callers retaining popped raw listeners across application callbacks.

**Additional evidence and real trigger**

`CreateLobbyProcessed` pops **both** specific listeners at lines 61–62. Each pop removes the request and reverse registration record. It then invokes the created callback at line 73, followed by the entered callback at line 74. Supply distinct manually managed listeners A (created) and B (entered), neither globally registered. In A's callback unregister B with its proper listener type and destroy B. At that moment B's request has already been erased, so Unregister cannot invalidate the local B pointer. The following `NotifyAllNow(B, OnLobbyEntered, ...)` inserts and invokes the dangling extra listener.

This is single-threaded cancellation of a still-pending entered callback, allowed by SDK 1.152.11 `IListenerRegistrar.h:156–165` and `GalaxyApi.h:99–103`. B need not be in A's snapshot or any DelayRunner callable. Thus fixing only BASE-CORE-002's per-notification snapshot loop or only delayed captures does not close this interval. The same pointer-handoff issue exists between pop and invocation if cancellation occurs on another thread.

**Impact / resolution options**

The impact remains a use-after-free after documented cancellation. Keep request registration tokens alive through invocation admission; mark results ready rather than handing out an untracked raw pointer. Alternatively serialize cancellation and invocation through a guarded dispatcher, still supporting same-thread removal of a later callback. Defer operation-record retirement until each notification has either acquired an invocation guard or been cancelled. Avoid holding an ordinary nonrecursive mutex across application code or making self-unregistration wait on itself.

**Recommended resolution and verification**

Expand the BASE-CORE-001 token/invocation design to **all** asynchronous specific-listener paths, including completed network requests and multi-callback responses. Add a successful CreateLobby case where A unregisters/deletes B before OnLobbyEntered; require A once, B never, valid surviving global delivery, and no Windows ASan/page-heap error. Repeat cancellation after pop using a deterministic second-thread barrier and address reuse. Proposed only; no executable validation occurred. Coordinate private auth/WebSocket/cloud listener stores with their owners rather than assuming this helper controls them.

## Targeted ABI handoff verification — 2026-09-24

### [ADD-ABI-001] Colliding legacy SDK listener tags dispatch callbacks through an unrelated interface

- **Severity:** High
- **Confidence:** High; wrong callback delivery was reproduced by the coordinator on MSVC x64 using the actual SDK 1.73.0 and production registrar. Detailed x86 calling-convention consequences remain static deductions.
- **Category:** API/ABI / Memory Safety
- **Location:** `Source/Client/Impl/ListenerRegistrar.hxx:213-250`, especially tag selection and casts at `222-227,245-250`; storage/iteration in `ListenerRegistrar.cxx:34-47,88-117,137-145,169-207,227-235`.
- **Production callers:** `Source/Client/Impl/Stats.cxx:380-415,419-443,453-469`; cached-self predicate `User.cxx:594-599`.
- **Affected scope:** Windows x86/x64 clients built against the bundled **1.73.0, 1.74.0 and 1.75.0** SDK interfaces. Both listener objects and requests can be correctly typed and remain alive throughout dispatch. SDK 1.76.0 is the adjacent negative control.
- **Ownership/accounting:** Primary finding here; Stats carries a cross-reference. This dispositions the unnumbered BUILD handoff, not a second BUILD or INTERCEPT finding. Distinct from BASE-CORE-001/002 cancellation/lifetime defects and ADD-STORAGE-004's unhydrated remote cache.

**Evidence**

1. In **each** `Source/DLLs/{1.73.0,1.74.0,1.75.0}/galaxy/IStats.h:276,313`, both `ILeaderboardRetrieveListener` and `IUserTimePlayedRetrieveListener` inherit `GalaxyTypeAwareListener<LEADERBOARD_RETRIEVE>`. Their success methods at `291,324` take `const char*` and **by-value `GalaxyID`**, respectively; their failure methods at `307,340` add their respective `FailureReason` enum. The names and parameter types do not describe interchangeable interfaces.
2. These SDKs' `IListenerRegistrar.h` defines `LEADERBOARD_RETRIEVE` as enum value **26**, with no `USER_TIME_PLAYED_RETRIEVE` enumerator. `GetListenerType()` is a **static** template accessor returning that tag, not a virtual dynamic-type query (1.73.0: `79-92`). `Register(uint32_t, IGalaxyListener*)` is the supported public API (`107-125`); the SDK's `GlobalLeaderboardRetrieveListener` uses the same tag automatically (`IStats.h:346`, `IListenerRegistrar.h:151-167`). No incorrectly supplied registration type is needed.
3. `galaxy_sdk_features.cmake:37,52,66,135,137` enables both listener interfaces and time-played dispatch on all three versions; the time-played **UPDATE** flag and per-operation Stats listener arguments are false. 1.76.0 fixes the time-played base to `GalaxyTypeAwareListener<USER_TIME_PLAYED_RETRIEVE>` and adds its global typedef (`IStats.h:318-351`; enum value 33 at `IListenerRegistrar.h:64`). The feature table's UPDATE boundary is consistent with the headers.
4. `Register` stores the correctly supplied leaderboard object as an `IGalaxyListener*` in bucket 26. `NotifyAllNow` extracts the requested interface from the callback member-pointer type, chooses `T::GetListenerType()`, and C-casts **every** entry in that bucket to `T*`. The commented-out `dynamic_cast` does not run. A non-null-pointer assertion cannot establish dynamic type. Calling a time-played member on a leaderboard-only object is undefined behavior before any callback body dereferences its arguments.

**Exact supported client sequence / failure mechanism**

Use one matching legacy SDK and initialized UniverseLAN client, with successful sign-in already observed through the SDK's normal auth listener and `ProcessData` loop:

1. Keep a concrete `L : ILeaderboardRetrieveListener` alive. Implement both leaderboard callbacks and globally register it with `ListenerRegistrar()->Register(L::GetListenerType(), &L)`. Equivalently, construct a `GlobalLeaderboardRetrieveListener` subclass after initialization. Registration is valid even when no leaderboard request is pending.
2. Obtain `self = User()->GetGalaxyID()` and call **`Stats()->RequestUserTimePlayed(self)`**. That is the complete legacy signature: there is **no per-call listener parameter**. `IStats.h:770-787` in 1.73.0, and `773-790` in 1.74.0/1.75.0, document the request and its time-played response interface. A time-played listener need not be registered to make the request; registering an additional correctly typed one does not protect L.
3. The legacy factory facade resolves `GetStats()` to the real `StatsImpl` (`GalaxyApiFactory.cxx:92-94`, `GalaxyDLL.cxx:120-122`). `Stats.cxx:428` calls `UserImpl::IsGalaxyUserDataPresent(self)`, which immediately returns true for the configured local ID (`User.cxx:597-599`; `Shared/IniData.cxx:921-926`). This avoids remote placeholder state and any network response requirement.
4. `Stats.cxx:429-433` queues `&IUserTimePlayedRetrieveListener::OnUserTimePlayedRetrieveSuccess` with a copied `GalaxyID`. `ListenerRegistrar.hxx:309-321` binds it into the real `DelayRunner`. The argument extender forwards this value; it does not convert it to a leaderboard name.
5. Call **`ProcessData()`**. The old SDK wrapper calls `IGalaxy::ProcessData`; UniverseLAN's `GalaxyImpl` forwards it to `universelan::client::ProcessData` (`GalaxyApiFactory.cxx:134-136`). After processing network events, this runs the delayed queue (`GalaxyDLL.cxx:166-173`; `Client_NoVer/Impl/DelayRunner.cxx:7-10`). The callback-member type selects bucket 26, includes L, casts it to `IUserTimePlayedRetrieveListener*`, and invokes its success slot. L's **`OnLeaderboardRetrieveSuccess(const char*)`** is the slot occupant, although no successful leaderboard retrieval occurred.

**Interleaving:** Register L -> request cached-self playtime -> pump -> unregister L. One thread suffices; there is no cancellation, destruction, pointer reuse, reentrancy or racing request in this proof. L merely needs to remain registered when the queued notification runs. The same error occurs on remote playtime success/failure: `ClientNetworkHandlers.cxx:107-109` reaches `Stats.cxx:453-469`, whose null extra listener falls back to global dispatch in `ListenerRegistrar.hxx:235-236`.

The reverse path is also reachable: manually register a concrete `IUserTimePlayedRetrieveListener` using its inherited tag, then call `Stats()->FindLeaderboard("board")` or the correctly typed `FindOrCreateLeaderboard`. `Stats.cxx:388-415` queues a leaderboard **failure**, and the shared bucket invokes the time-played **failure** slot. The legacy SDK lacks a `GlobalUserTimePlayedRetrieveListener` typedef, but explicit public registration remains available. The primary proof does not depend on that legacy time-listener registration ambiguity.

**Signature slots and Windows ABI consequence**

For these simple single-inheritance listener interfaces under the Microsoft C++ ABI, zero-based vftable function slots are:

| Slot | Leaderboard interface | Time-played interface |
| --- | --- | --- |
| 0 | inherited virtual deleting destructor | inherited virtual deleting destructor |
| 1 | `void OnLeaderboardRetrieveSuccess(const char*)` | `void OnUserTimePlayedRetrieveSuccess(GalaxyID)` |
| 2 | `void OnLeaderboardRetrieveFailure(const char*, ILeaderboardRetrieveListener::FailureReason)` | `void OnUserTimePlayedRetrieveFailure(GalaxyID, IUserTimePlayedRetrieveListener::FailureReason)` |

`GalaxyTypeAwareListener` adds no virtual slot. A virtual member pointer selects the slot, not a matching function name or signature; `std::invoke` does not dynamically validate the receiver. Slot byte offsets are 0/4/8 on x86 and 0/8/16 on x64, relative to the vftable function-entry address. RTTI metadata is not an additional function slot.

In all three versions, `GalaxyID.h:22,43-77,151-156` specifies a packed, eight-byte object containing one `uint64_t`, with a **user-provided copy constructor**, no virtuals and a trivial destructor. Treating it as a trivially copyable integer on every ABI would give the wrong analysis:

- **MSVC x64:** the nontrivial by-value class argument is passed indirectly. `RCX` holds `this`; `RDX` holds a pointer to the caller-constructed `GalaxyID` parameter object. For failure, `R8D` holds the enum. The leaderboard callback instead treats `RDX` as `const char*`. It receives **the address of an ID temporary, not the numeric ID reinterpreted as an address**. Reading it as a name yields binary ID bytes, possibly an unterminated read beyond eight bytes; retaining it as a name retains a temporary-object address. The reverse failure path treats the leaderboard string address as a `GalaxyID*`, reading unrelated bytes as an ID, potentially beyond a short string. Both failure enums occupy the same `R8D` position, but that does not make the callbacks type-compatible. No x64 stack-cleanup mismatch is asserted.
- **MSVC x86 default `__thiscall`:** `ECX` holds `this`; the non-overaligned `GalaxyID` parameter is constructed directly in the eight-byte stack argument area. At callee entry, success has ID low/high words at `[ESP+4]`/`[ESP+8]`, whereas the leaderboard callback expects one four-byte pointer at `[ESP+4]`. It sees the low ID word as the pointer and has a four-byte rather than eight-byte callee-pop obligation. Failure supplies ID low/high words and reason at `[ESP+4]`/`[ESP+8]`/`[ESP+12]`; the leaderboard failure callback reads the high ID word as its reason and pops eight rather than twelve argument bytes. Reverse failure consumes the name-pointer/enum words as the ID, reads a reason beyond the supplied arguments, and over-pops four bytes. Frame restoration/optimization can change the visible symptom; a crash on every invocation is not claimed.

These are default Microsoft-ABI deductions, corroborated by Microsoft calling-convention documentation and LLVM's Microsoft ABI `getRecordArgABI` implementation; links and a proposed actual-header/registrar probe are in [ABI.MD](../../../.ai/review-addendum/ABI.MD). No compiler layout dump, disassembly or execution was performed.

**Impact**

Ordinary games can receive a spurious leaderboard success or time-played failure, consume nonsensical IDs/names, read out of bounds, or corrupt the x86 call frame. A callback that only increments a counter still demonstrates wrong routing. This is a first-party compatibility-dispatch defect exposed by bundled SDK metadata, not proof of how the proprietary Galaxy DLL dispatches. Its severity reflects reachable memory/ABI corruption; exposure is limited to the three historical versions. Making listener lifetimes perfect or hydrating every cache entry would not repair it.

**Possible solutions**

1. Add collision-aware checked interface selection at dispatch, or use proven typed registration records/internal distinct buckets while retaining the original SDK-facing tags and layouts. A `dynamic_cast` plus a null check can discriminate these interfaces **only where compatible client RTTI is actually available**. An assertion on a failed cast is not a delivery policy.
2. Introduce a documented compatibility adapter supplying trustworthy type information for the affected registration path. `Register(uint32_t, IGalaxyListener*)` plus the shared integer alone cannot identify which unrelated interface an arbitrary prebuilt object implements.
3. Where client type information cannot be established, explicitly restrict the affected legacy capability and suppress unsafe ambiguous dispatch. An unsupported-operation failure sent through the same shared tag is still unsafe; silently dropping valid callbacks is not full compatibility.

**Recommended resolution**

Implement and validate an ABI-preserving, collision-aware receiver policy for both directions and both result slots. Check the supported games' RTTI assumptions before choosing a checked cast as the compatibility solution, and define the fallback for objects without usable RTTI. Preserve ordinary leaderboard notifications and valid time-played delivery wherever discrimination is supported. Do not retag excluded SDK headers, synthesize a nonexistent enum, or merely enable the UPDATE flag: already compiled clients register the old numeric tag, and Stats currently uses the older availability gate anyway. Dispatch-lifetime work for BASE-CORE-001/002 remains separately necessary.

**Verification**

Proposed only: run the small standalone Windows x64 probe in `ABI.MD`, using the **actual selected SDK headers and production registrar/DelayRunner**, with only a correctly registered leaderboard listener. Queue a time-played success and require **zero** leaderboard calls; the uncorrected slot dispatch is expected to increment the leaderboard success counter. Add a retained time-played receiver and verify one correctly typed result, then separately exercise both failure directions. Repeat 1.73.0, 1.74.0, 1.75.0 and the 1.76.0 control. A full-client follow-up must use the exact cached-self `RequestUserTimePlayed(self)` / `ProcessData` sequence above and real `FindLeaderboard` failure, not fabricated registration or replacement listener interfaces. Inspect the x86 argument area and callee cleanup in a debugger before relying on process exit; use memory instrumentation for application string reads. Also verify the selected fix against actual RTTI-enabled/disabled client support requirements. No builds or tests were run for this addendum.

**Coordinator execution update:** An isolated x64 Debug probe linked the actual instrumented `universelan-lib-x64-1.73.0` target. It registered a live `ILeaderboardRetrieveListener` with its correct tag and called production `NotifyAllNow` for a time-played success. Output: `leaderboard_tag=26 playtime_tag=26 incompatible_matches=1`, then `wrong_leaderboard_success_calls=1`. The spy did not dereference the wrongly typed argument. This confirms incorrect actual dispatch, not just enum equality. The full public Stats flow, other legacy versions and x86 were traced statically but not executed. See `.ai/review-addendum/VERIFICATION.MD`; the earlier owner-local no-execution statement is superseded only for this coordinator probe.
