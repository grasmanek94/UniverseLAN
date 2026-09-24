# CustomNetworking.cxx — fresh baseline review

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. All 295 lines read. Windows-focused static review; no socket test/build executed.

## File-specific inspection

Reviewed Channel construction, connect validation, IXWebSocket worker callbacks, open/data/close/error notification flow, registry publication and cleanup, destructor stop/join, send and incoming byte-stream peek/read/pop. Traced IXWebSocket 12.0.1 `start/stop/connect/run/close`, `ListenerRegistrar`, `NotificationParamScopeExtender`, `DelayRunner`, interface reset ordering and SDK `1.152.11/galaxy/ICustomNetworking.h` in full.

The API's incoming buffer is documented as a byte stream, so concatenating WebSocket messages is not itself a framing defect. Buffer operations are mutex-protected and use bounded copy/erase sizes. GetChannel returns shared ownership while operations use the channel. The Channel destructor stops/joins the worker before its data members are destroyed; normal `InterfaceInstances::reset` destroys CustomNetworking before the registrar/runner. Deferred `connection_string.c_str()` is copied by the notification parameter extender, so deleting a Channel is not by itself a dangling string callback. Exceptions, extreme multi-gigabyte buffers and shutdown from inside callbacks were not dynamically assessed.

## Findings

### [BASE-API-015] WebSocket operation listeners survive SDK Unregister and can be called after destruction

- **Severity:** High
- **Confidence:** High
- **Category:** Memory Safety
- **Location:** `Source/Client/Impl/CustomNetworking.cxx:57-73,95-110,219-232`; declarations `CustomNetworking.hxx:52-54`.
- **Affected scope:** Open/close operation-specific listeners in SDK versions with `HAS_ICONNECTIONLISTENERS`.

**Evidence.** The channel stores borrowed listener pointers directly and later passes them as the extra listener to `NotifyAll`. It never calls `AddRequestListener`. SDK `Source/DLLs/1.152.11/galaxy/IListenerRegistrar.h:156-165` promises Unregister removes the listener from all pending asynchronous calls. Actual `ListenerRegistrarImpl::Unregister` removes global registrations and request-helper entries only (`ListenerRegistrar.cxx:50-67`); it cannot reach these Channel members. The extra-listener execution path adds the supplied pointer unconditionally (`150-207`), and delayed notification capture does not own or validate listener objects (`ListenerRegistrar.hxx:309-321`).

**Failure mechanism.** Open a slow connection with operation listener L, unregister L while the handshake is pending, and destroy L. When the handshake succeeds/fails, the worker still captures the stale pointer in a delayed notification. The next ProcessData invokes a virtual function through freed storage even though the caller used the documented cancellation operation. Close listeners have the same retention path. This failure does not require racing destruction with an already executing callback: cancellation can finish well before the network event exists.

**Impact.** Use-after-free/crash during normal operation cancellation or owner/UI teardown. Global unregistration does not help when the same object was explicitly passed as an operation listener.

**Alternatives / recommended resolution.** Register operation listener identities in cancellation-aware request state. Queue an event/request token, then resolve/pop the still-registered listener on the API dispatch thread, rather than queueing its raw pointer from the WebSocket worker. Alternatively use a shared cancellation control block consulted immediately before dispatch. Merely registering and then popping on the worker still leaves a cancellation gap before deferred delivery. Retire operation listeners after their single terminal result.

**Verification.** Delay both a successful and failing handshake, call Unregister and destroy the open listener before allowing completion, then pump callbacks and verify no invocation. Repeat for a delayed close and for cancellation after a worker event was queued but before ProcessData. Use Windows ASan to expose stale virtual dispatch. Not executed.

### [BASE-API-016] Channel registry lifetime is not synchronized with queued notification lifetime

- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Client/Impl/CustomNetworking.cxx:62-64,69-112,149-163,198-216`.
- **Affected scope:** Fast remote open/data/close, multiple opens between API pumps, and concurrent OpenConnection/ProcessData.

**Evidence.** `connect` starts the worker before OpenConnection inserts the channel into `channels`. Worker callbacks queue notifications containing only a numeric pointer-derived ConnectionID. On close/error, `cleanup=true` is set immediately after queueing the terminal event. The next OpenConnection runs `PerformCleanup` and erases marked channels, irrespective of pending notifications. `NotifyAll` retains arguments, not Channel ownership (`ListenerRegistrar.hxx:309-321`); DelayRunner executes them only when pumped (`Client_NoVer/Impl/DelayRunner.cxx:7-15`; `GalaxyDLL.cxx:166-173`). IXWebSocket `start` creates a thread and `connect` invokes Open on that thread (`IXWebSocket.cpp:180-184,239-245,373-449`). SDK `ICustomNetworking.h:33-39,102-108,158-184` ties successful connection/data notifications to handles and readable incoming bytes.

**Failure mechanism.** A valid connection A opens, receives bytes and closes while the application is between pumps. Success/data/close callbacks wait in DelayRunner. The application opens B, whose cleanup pass erases A. Later A's data callback announces bytes but `GetChannel(A)` fails, so reads silently return nothing and buffered data is gone. A concurrent API pump can also deliver OpenSuccess before initial insertion, making the just-announced handle unavailable. Pointer-derived IDs permit a later allocation to reuse an erased ID while old notifications still reference it.

**Impact.** Successful callbacks can expose unusable handles, data notifications can lose their payload, and stale events can address a reused channel. Conversely, if no subsequent OpenConnection occurs, finished channels retain incoming buffers and joinable worker resources until interface destruction. Both outcomes stem from cleanup being tied to an unrelated future open rather than event delivery.

**Alternatives / recommended resolution.** Publish a stable channel identity before starting asynchronous work; roll it back on startup failure. Tie cleanup to an ordered completion on the API/event thread, retaining channels while their earlier notifications/data are observable. Prefer monotonic/generation-tagged ConnectionIDs over addresses to prevent reuse ambiguity. A queued shared owner helps lifetime but is insufficient unless registry visibility is retained for public reads until the appropriate delivery boundary. Release completed resources through the normal pump independently of new opens.

**Verification.** Let A send a final payload and close before the first pump; open B, then deliver A's callbacks and verify ordered, readable data. Force a worker Open callback before OpenConnection returns while another thread pumps. Cycle many channels with allocator reuse and delayed callbacks; verify old IDs cannot target a replacement. Check cleanup also occurs without another open. Not executed.

### [BASE-API-017] Close-listener access races with the WebSocket close callback

- **Severity:** Medium
- **Confidence:** High
- **Category:** Concurrency
- **Location:** `Source/Client/Impl/CustomNetworking.cxx:91-97,226-232`; `CustomNetworking.hxx:54`.
- **Affected scope:** Local CloseConnection concurrent with remote/transport closure, including a single application API thread plus the library's worker.

**Evidence.** `CloseConnection` assigns the plain `listener_close` pointer after GetChannel has released the registry mutex. `WebSocketOnClose` reads the pointer from IXWebSocket's asynchronous callback with no common lock or atomic access. The only per-channel mutex is used for the byte buffer, not this listener. IXWebSocket `start/run` establishes a separate thread (`IXWebSocket.cpp:180-184,373-449`); the SDK documents asynchronous close completion (`ICustomNetworking.h:139-147`) and general API thread safety (`GalaxyApi.h:310-314`).

**Failure mechanism.** The application stores listener L at the same time that the worker processes a peer-initiated close and reads `listener_close`. Neither operation establishes happens-before. The worker can capture the old null/listener value, queue the terminal event, and mark cleanup, leaving the new close request without its listener completion. Concurrent repeated close calls can also overwrite the pending listener.

**Impact.** A C++ data race and nondeterministic close completion. Medium severity reflects the concrete bounded lost/wrong-listener effect rather than assuming that every aligned pointer race crashes on Windows.

**Alternatives / recommended resolution.** Protect close state and pending listener registration with one channel lifecycle synchronization policy; transition open/closing/closed once, and consume callbacks deterministically. An atomic pointer removes the narrow data race but does not define whether a newly registered close operation has missed the terminal event. Prefer integrating close-state arbitration with BASE-API-015's cancellation-aware request tokens and BASE-API-016's event-thread cleanup.

**Verification.** Use barriers to race remote close with local CloseConnection, including two local calls and cancellation. Verify the defined number of completions, correct listener routing, and race-free access. No reliance on probabilistic crash reproduction is necessary. Not executed.

## Thorough follow-up addendum — 2026-09-24

All 295 implementation lines and 166 header lines reread at unchanged production baseline `b30e8387`. Reread IXWebSocket 12.0.1 `IXWebSocket.cpp` in full and selected transport close/state sections as dependency context. The three existing findings remain the appropriate root-cause accounting; no new WS ID is added.

### BASE-API-015 — retained (High / High confidence / Memory Safety)

The supported trigger remains completed SDK Unregister before network completion, followed by listener destruction; it is not premature destruction of an actively called listener. Global `const char*` notification arguments are copied by `NotificationParamScopeExtender`, but one-time listener pointers are neither owned nor cancellation-validated. Operation-specific custom-networking listeners only exist with `HAS_ICONNECTIONLISTENERS` (1.138.1 onward); do not imply the direct Channel-member retention path exists in the earlier global-only ABI. Resolving the request token at dispatch rather than on the WS worker is still needed to cover cancellation after enqueue.

### BASE-API-016 — expanded exception/cleanup evidence (Medium / High confidence / Correctness)

**Startup and publication.** `client.start()` at line 64 can run callbacks before the registry insertion. After start, `PerformCleanup` allocates a vector and `channels.emplace` allocates a node (`149-163,205-215`). If either throws, the local shared owner unwinds and stops the worker, but previously queued success/data notifications still contain the unpublished numeric ID. This is an exceptional variant of the already counted publication-versus-event-lifetime defect, not an independent finding. Publication must be transactional: establish registry visibility before the worker starts, and cancel/retire queued events on a failed start/commit.

**Cleanup/destruction counterevidence.** Erasing a channel stops/joins its worker in the Channel destructor while `connection_string`, buffer and mutex still exist (`166-171`; IX `187-200`). The callback merely enqueues application work; it does not directly invoke the application's OpenConnection/CloseConnection or acquire the channel-registry mutex. Consequently, an ordinary cleanup erase under that registry mutex is not demonstrated to deadlock or self-join. IX's second `stop()` from its own destructor is not evidence of a second close callback: the transport close path returns for CLOSED/CLOSING (`IXWebSocketTransport.cpp:1194-1215`) and unchanged state does not call close again (`209-237`). Explicit `InterfaceInstances::reset` destroys CustomNetworking before registrar/queue (`UniverseLAN.cxx:91-133`). Its implicit C++ member-destruction order is different (`UniverseLAN.hxx:50-96`); SDK-compliant Shutdown/reset makes those pointers null, so no new defect is asserted solely for skipping required lifecycle handling. CORE owns partial-init/factory lifetime reconciliation.

**Remaining exception boundary.** Allocation during WS buffer growth or `NotifyAll` capture can escape `WebSocketCallback`, and IX's thread entry has no catch (`IXWebSocket.cpp:373-454`). Thread creation can also throw before any asynchronous failure callback. These are concrete fault-injection gaps, but no ordinary malformed-input exception or promised recoverable-OOM contract was demonstrated. Do not turn generic resource exhaustion or a caller-thrown SDK callback into another confirmed serious ID. A future lifecycle fix should set terminal state even if event construction fails and define worker exception containment.

**Additional verification.** Inject failure after worker start but before registry insertion; separately inject terminal-notification allocation failure. Check that no callback advertises an unusable ID, cleanup can progress without a future open, and normal stop/join does not duplicate close notifications. These complement the existing delayed-final-data and allocator-ID-reuse tests. Not executed.

### BASE-API-017 — retained with dependency precision (Medium / High confidence / Concurrency)

`listener_close` still has no common synchronization between the API writer and async close reader. IX transport serializes its internal ready-state transition, not this application-owned pointer (`IXWebSocketTransport.cpp:209-237`). Some IX send-error paths can also switch to CLOSED on the sending thread (`flushSendBuffer:1265-1295`), so describe callbacks as transport-originated rather than guaranteed to come only from the dedicated worker. The single-API-thread versus worker interleaving already proves the finding; speculative concurrent shutdown is unnecessary. Repeated local close after a completed terminal event needs an explicit policy, not an assumed SDK guarantee of unlimited completions.
