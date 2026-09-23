# Fresh baseline review — UniverseGameServer.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–109. Static Windows review; shallow serious-defect scope.

## Checked
- Traced initialization with `gameserver=true`, owned interface getters, data pumping and telemetry feature guard.
- The class's extended shutdown correctly calls the real extended function; its exported caller bypasses it (BASE-INTERCEPT-010).

## BASE-INTERCEPT-001 — Game-server observers are detached after their SDK owner shuts down

- **Severity:** Medium (High memory-safety impact is conditional on native registrar destruction)
- **Confidence:** High for the contract violation; vendor-specific crash behavior unexecuted.
- **Category:** API/ABI
- **Location:** `Source/InterceptionLogger/UniverseGameServer.cxx:39–54`.
- **Affected scope:** Both game-server shutdown variants.

**Evidence and failure mechanism:** `real_shutdown`/`real_shutdown_ex` runs before `gameserver_intf_inst.reset`. Reset destroys listener-bearing wrappers; their containers call `Unregister` through the cached real game-server registrar. SDK `1.152.11/galaxy/IListenerRegistrar.h:148–149` requires unregister before shutdown, and `GalaxyGameServerApi.h:93,103` explicitly requires listener cleanup before both shutdown forms. Internal observers are registered automatically, so even a game that correctly removes its own listeners reaches this sequence.

**Impact:** If the vendor shutdown destroys the registrar, cleanup makes virtual calls through a dangling pointer. Other SDK implementations can reject late cleanup; the wrapper relies on lifetime outside the documented contract.

**Possible fixes:** Explicitly detach observers while the SDK is active, or preserve the shutdown callable and destroy dependent wrappers first.

**Recommended resolution:** Establish one teardown sequence: quiesce callbacks, detach owned listeners/proxies against the live registrar, invoke real shutdown, clear wrappers. Keep the client and server sessions separate.

**Verification:** Stub registrar rejects all use after SDK shutdown and asserts zero live registrations at shutdown entry; run both game-server variants and client variants with normal/partial init and reinit. Proposed only. Same unique finding as the client-side report, not another count.
