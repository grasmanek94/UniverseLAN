# Review: `Source/InterceptionLogger`

## Design summary

InterceptionLogger is a Galaxy ABI-compatible forwarding layer. It resolves
the real Galaxy exports, creates wrapper implementations and listener proxies,
and forwards calls while recording them through `Tracer`. It is a distinct
implementation from `Source/Client/Impl`, not a duplicate of that component.
The 75 in-scope files were reviewed by the lifecycle, factory, listener, proxy,
and representative wrapper paths; the generated Galaxy SDK headers remain
versioned inputs rather than edited source.

## Verified findings

### Critical — lifecycle teardown is not synchronized with exported calls

`InterfaceInstances universe_client_api` is shared by `Init`, `Shutdown`,
`ProcessData`, `load`, and all interface getters without a lifecycle lock.
`reset()` clears wrapper objects and function objects while callers can still
read or invoke them. The same issue exists for the static game-server wrapper.
An API call racing shutdown can call through a destroyed object or an empty
`std::function`.

**Suggested fix:** define a single lifecycle state machine, serialize init,
process, getters, and shutdown (or return stable handles protected by shared
ownership), stop/drain callbacks before clearing wrappers, and make calls before
successful init return a documented error.

### High — reset does not shut down or reset the real Galaxy instance

`InterfaceInstances::reset()` clears `real_shutdown` and wrapper pointers but
does not invoke the underlying Galaxy shutdown/factory reset first. This leaves
the real SDK instance initialized and can leak the factory-owned object across
reinitialization.

**Suggested fix:** quiesce wrapper calls, invoke the real shutdown and factory
reset exactly once, then clear function pointers and wrapper ownership.

### High — factory and error-manager ownership are unsafe

`GalaxyFactory::GetInstance()`, `CreateInstance()`, `Reset*()`, and
`GetErrorManager()` access raw static pointers without synchronization.
Concurrent creation/reset can race, and `errorManager` is allocated but not
released by reset. The interceptor's `ErrorManager::GetLastError()` also
always returns `nullptr`, discarding errors.

**Suggested fix:** use one mutex/`call_once` lifecycle policy, make reset
quiescent, own factory objects with an explicit destruction path, and delegate
error-manager queries to the real implementation.

### High — operation-specific listener proxies have incomplete ownership

`ProxifySyncHandler` maps one real listener to one proxy, so a second active
operation for the same target is silently not tracked. Proxy macros store raw
targets, delete proxies after a callback, and do not unregister on all paths.
An exception, nested callback, or asynchronous callback after target teardown
can leak, double-delete, or dereference freed storage.

**Suggested fix:** track registrations by operation/proxy, use explicit target
ownership or cancellation, remove the map entry before invoking user code,
defer destruction until callbacks drain, and contain exceptions at the ABI
boundary.

### High — persistent listener ownership leaks

`ListenersContainer::AddListener()` allocates listeners with `new`. Failed
registration leaks the allocation, and `UnregisterAllListeners()` erases map
entries without deleting successfully unregistered listeners.

**Suggested fix:** store listeners in RAII ownership, roll back on registration
failure, unregister while ownership remains valid, then destroy them.

### Medium — several ABI arguments and feature guards are ignored

`GalaxyImpl::InitLocal()` ignores `galaxyPeerPath` and `throwExceptions`;
`GalaxyImpl::Init()` ignores `throwExceptions`; and `ShutdownEx` ignores its
options. `GameServerUtils()` is exported without the same `HAS_IUTILS` guard as
the member it calls. `StorageListener.hxx` declares listener functionality
without matching feature gating even though the implementation is omitted in
feature-off builds.

**Suggested fix:** preserve every supported SDK argument, map unsupported
options explicitly, and keep declaration/definition/export guards identical
for each Galaxy feature family.

### Medium — callback forwarding is incomplete

The operation-specific `AuthListener` paths trace `OnAuthSuccess` and
`OnAuthLost` but do not forward those callbacks to their non-null target.
Callers waiting for authentication completion can therefore never observe the
result.

**Suggested fix:** distinguish persistent trace-only listeners from
operation-specific proxies and forward every callback required by the Galaxy
contract exactly once.

### Medium — lazy real-function resolution is racy and lifecycle-sensitive

`load()` lazily assigns a shared `std::function` without synchronization and
can be called before initialization or after reset. Concurrent assignment or
invocation can race, and an empty `real_process_data` throws through the
exported ABI.

**Suggested fix:** resolve function pointers once under the lifecycle lock,
validate the resolved symbol, and return a documented failure before init or
after teardown.

## Positive patterns

The wrappers consistently use feature guards around most version-dependent
interfaces, `std::unique_ptr` for the main wrapper set, and a centralized
listener registrar. These are useful foundations once lifecycle and callback
ownership are made explicit.

## Remediation order

1. Make init/process/getter/shutdown quiescent and shut down the real SDK.
2. Replace raw factory/listener ownership with synchronized RAII.
3. Correct proxy registration and callback forwarding.
4. Preserve ABI arguments and align all feature guards.
