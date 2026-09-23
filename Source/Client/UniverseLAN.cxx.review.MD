# Fresh baseline review — UniverseLAN.cxx

- Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`.
- Coverage: entire file, lines 1–135.
- Method: static lifecycle tracing through client/game-server entry points, network pumping, delayed callbacks, and WebSocket cleanup.

## Specific checked notes

- Initialization creates configuration/file utilities, the callback queue and registrar, then interfaces; `Client` connects in its constructor but its network worker is started only after interface construction by the entry-point layer.
- Normal explicit reset stops/joins the ENet worker before destroying interfaces. It destroys `CustomNetworkingImpl` (whose channels stop WebSocket workers) before the registrar and callback queue: this is a useful dependency ordering for ordinary non-reentrant shutdown.
- `config` and `sfu` are deliberately retained across reset. `internal_reset` can allocate/load configuration even when reset is called before initialization.
- Initialization publishes members incrementally. Reinitialization without shutdown, simultaneous init/shutdown, partial initialization, and DLL static-destruction order have no explicit state machine. These broader lifecycle assumptions remain validation items; they are not additional confirmed IDs here.
- Game-server role selection is correctly parameterized at lines 56–58, but its caller omits the argument (`BASE-CORE-004`).

## Confirmed finding

### BASE-CORE-003 — Shutdown from a callback destroys the currently executing event pump

- **Severity:** High
- **Confidence:** High
- **Category:** Memory Safety
- **Location:** `Source/Client/UniverseLAN.cxx:91–134`, especially 130–133; `Source/Client_NoVer/Impl/DelayRunner.cxx:7–11`.
- **Affected scope:** Client and game-server callbacks that call their corresponding shutdown API.

**Evidence**

`GalaxyDLL.cxx:166–173` and `UniverseGameServer.cxx:111–120` directly call the owned `Client::ProcessEvents` and `DelayRunner::Run`. A callback executes synchronously inside these methods. `reset` immediately destroys both objects and all interfaces. `DelayRunner::Run` resumes with `queue.try_pop` after each callback. The network pump likewise resumes its member-queue loop (`Shared/Networking/Networking.cxx:219–226`). SDK 1.152.11 documents unregistering/deleting self-registering listeners before shutdown, but the inspected declarations provide no callback-time shutdown exclusion.

**Failure mechanism**

A specific DLC-completion listener, with no self-registering listeners left, unregisters itself and calls `Shutdown()` during `ProcessData()`. Reset joins the separate worker, destroys the registrar and `delay_runner`, then returns. The callback returns to the still-active `DelayRunner::Run`, which accesses its destroyed queue on the next loop condition. Keeping the listener itself alive does not prevent this. A network callback can similarly destroy the active client/connection and resume into freed state.

**Impact**

Callback-driven shutdown, such as returning to a menu or handling an authentication/session failure, can crash or corrupt memory. The defect does not require overlapping threads or failure to unregister listeners.

**Possible solutions**

1. Defer graph destruction until all active dispatch frames exit; let shutdown mark a stop request and prevent further callbacks.
2. Pin the complete runtime graph for each pump and make teardown wait/defer appropriately, including the same-thread reentrant case.

**Recommendation**

Introduce an explicit runtime lifecycle/dispatch guard shared by both APIs. Make callback-time shutdown request termination, stop further queue draining, and perform ordered cleanup at the outermost safe pump boundary. Pinning only the queue leaves interface and registrar lifetimes unsafe; waiting synchronously for the current callback would deadlock.

**Verification**

Exercise a manually registered/specific listener that unregisters and shuts down from a delayed completion, then repeat from a network notification and the game-server pump. Verify clean return, no callbacks after shutdown, null accessors, and successful subsequent init, under Windows ASan/page heap. Tests were not executed.
