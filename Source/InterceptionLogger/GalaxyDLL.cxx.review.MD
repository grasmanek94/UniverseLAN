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
