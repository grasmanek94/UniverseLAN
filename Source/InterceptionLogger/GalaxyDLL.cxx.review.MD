# Fresh baseline review — GalaxyDLL.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–190. Static Windows review; shallow serious-defect scope.

## Checked
- Traced the static `InterfaceInstances`, console capture, initialization catch, all interface getters, error query, data pump and lazy `load` resolution.
- Compared ordinary and extended shutdown with the listener-registration lifetime contract. `ShutdownEx` forwards its argument correctly in this client path.
- Investigated failure states rather than assuming real DLL resolution always succeeds.

## BASE-INTERCEPT-001 — Internal listeners are unregistered after real SDK shutdown

- **Severity:** Medium (High memory-safety impact is conditional on native registrar destruction)
- **Confidence:** High for the ordering/contract violation; exact vendor failure mode is runtime-dependent.
- **Category:** API/ABI
- **Location:** `Source/InterceptionLogger/GalaxyDLL.cxx:72–86`, `Shutdown` and `ShutdownEx`.
- **Affected scope:** Client shutdown across versions; same root cause in game-server shutdown.

**Evidence and failure mechanism:** Both functions invoke real shutdown first and only then `InterfaceInstances::reset`. Reset destroys wrappers whose destructors call `ListenersContainer::UnregisterAllListeners`; that container calls the cached real registrar at `ListenersContainer.cxx:25`. Wrappers register internal listeners during normal construction, so the application cannot remove these hidden registrations itself. SDK `1.152.11/galaxy/IListenerRegistrar.h:148–149` requires all registered listeners to be unregistered before Shutdown, and `GalaxyApi.h:350,360` imposes the equivalent lifetime precondition.

**Impact:** Every initialized session follows an invalid teardown order. A real SDK that releases its registrar during shutdown leaves a dangling virtual-call target, causing a shutdown crash/use-after-free; SDKs retaining a facade may instead reject the late unregister. No vendor crash was reproduced.

**Possible fixes:** Add an explicit pre-shutdown listener-detachment phase, or destroy listener-bearing wrappers while saving the real shutdown callable separately. A null check on the cached pointer cannot establish object lifetime.

**Recommended resolution:** Quiesce dispatch and detach all interceptor-owned registrations while the real registrar is alive, invoke real shutdown, then clear forwarding objects. Integrate pending-proxy cleanup with that lifecycle.

**Verification:** Use a fake real SDK whose shutdown destroys/poisons its registrar and asserts zero registrations. Exercise ordinary/extended client and game-server shutdown, partial initialization and repeat initialization under Windows ASan. Proposed only.

## BASE-INTERCEPT-008 — Swallowed initialization exceptions leave a success-looking, unsafe API state

- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/InterceptionLogger/GalaxyDLL.cxx:37–59,72–77,164–180`.
- **Affected scope:** Real DLL missing, export resolution failure, or another initialization exception.

**Evidence and failure mechanism:** `Init` catches `std::exception`, displays a message and continues normally without recording an interceptor error or rolling back. If real DLL loading fails before callable/interface assignment, `GetError` returns null because `error` is absent, getters return null, and Shutdown/ProcessData invoke empty `std::function` objects. The SDK explicitly instructs callers to invoke Shutdown even after partial Init failure (`1.152.11/galaxy/GalaxyApi.h:335–338`). If config construction itself throws, the subsequent unconditional `config` dereference is also unsafe.

**Impact:** A recoverable deployment/init failure is reported as apparent success through the API; ordinary cleanup then throws `std::bad_function_call`, or callers dereference null interfaces. The modal diagnostic does not repair the API state.

**Possible fixes:** Propagate exceptions where the SDK contract permits them, or persist a compatible initialization error and explicit lifecycle state. Guard cleanup according to how far initialization progressed.

**Recommended resolution:** Make initialization transactional with documented partial-success states, retain the failure for `GetError`, and make required cleanup safe after every failed stage. Use RAII for console capture so error exits restore it.

**Verification:** Substitute missing DLL, missing export and failing-config cases; assert that callers observe failure and can follow SDK-mandated cleanup without a second exception or null dereference. No fault injection was run.

## Follow-up review addendum — 2026-09-24

Reread all 190 lines, all InterfaceInstances construction/reset code and both game-server shutdown routes.

### BASE-INTERCEPT-001 — Addendum: retain the contract rating and track the actual Windows module owner

- **Severity:** Medium, retained; native lifetime-dependent High impact remains conditional
- **Confidence:** High for teardown ordering, unexecuted for native object destruction
- **Category:** API/ABI
- **Location:** `Source/InterceptionLogger/GalaxyDLL.cxx:72–86`; `UniverseGameServer.cxx:39–54`; loader context `Source/Shared_NoVer/SharedLibUtils.cxx:84–86,90–139`.
- **Affected scope:** Explicit client/server shutdown and the additional, unverified process/module-teardown path.

**Evidence / failure mechanism**

Real shutdown still precedes observer Unregister calls through the cached registrar. The SDK's documented unregister-before-shutdown rule is unchanged. The actual Windows loader constructs a name from the optional prefix plus `RealGalaxy[64].dll`, inventories that image, calls LoadLibraryA once for its lazy singleton, and releases that HMODULE only in SharedLibUtils's destructor. Neither ordinary nor extended SDK Shutdown in this owner directly calls FreeLibrary.

`Shared_NoVer` is statically linked through common-shared into each interceptor DLL (`Source/Shared_NoVer/CMakeLists.txt:5`; `Source/Shared/CMakeLists.txt:19–23`; `Source/DLLs/CMakeLists.txt:153–163`). Thus a "shared" library target name is not proof of a separate shared helper DLL or a process-wide loader singleton. Client and server within one interceptor do use the same native load. Separate copies can still load the same Windows native module, depending on paths/module resolution; their state maps are not thereby shared.

**Impact**

The explicit lifecycle contract violation is confirmed at Medium. Retaining an HMODULE does not establish that native Shutdown preserves registrar objects, and releasing the load handle does not by itself prove where an SDK facade's vtable lives. The native implementation, remaining Windows module references, and any vendor-internal peer module are not known from these sources. Static destruction ordering warrants validation but supplies no additional confirmed unloaded-DLL crash here.

**Possible solutions / recommended resolution**

Detach owned observers/proxies while their documented SDK owner is active, then invoke native shutdown and clear forwarding objects. Tie the real module reference to the complete lifetime of calls that can enter it. Diagnose the actual module containing the registrar/vtable before attributing a native crash to FreeLibrary.

**Verification**

Proposed only: recording native registrar asserts no calls after shutdown and zero owned registrations at shutdown entry. On an authorized native Windows lifecycle probe, identify the module containing the registrar's virtual targets and record SDK object teardown, LoadLibrary/FreeLibrary references and interceptor unload order. Test client/server shutdown independently and in both orders. No DLL was loaded, unloaded or inspected as a running process. This retains the already reconciled Medium rating and adds no finding.

### BASE-INTERCEPT-008 — Addendum cross-reference

The full non-throwing partial-init/error-clobber extension is appended under this same BASE ID in `UniverseLANInterceptor.cxx.review.MD`. It follows real Init through subsequent observer registrations, which reset the native error before public GetError. The existing swallowed-exception/empty-std::function mechanism remains confirmed and Medium. Missing exports throw from SharedLibUtils rather than returning null function pointers; calling an empty stored std::function is `std::bad_function_call`, not a demonstrated jump through a null native address.
