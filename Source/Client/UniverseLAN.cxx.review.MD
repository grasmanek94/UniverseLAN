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

## Full-reread addendum — 2026-09-24

Production baseline remains `b30e83872c0006e8240c8b4f565da5351bf10080`; review HEAD is `48cea8c6c48fa41fddd348a0119129cc5643fc8b`. The original review above is preserved. This section records a newly established, separately actionable partial-initialization defect.

### [ADD-CORE-001] Transport construction failure prevents the documented offline Apps interface from existing

- **Severity:** Medium
- **Confidence:** High
- **Category:** API/ABI / initialization correctness
- **Exact location:** `Source/Client/UniverseLAN.cxx:38–50,64–66`, `InterfaceInstances::init`; accessor `Source/Client/GalaxyDLL.cxx:130–133`.
- **Affected scope:** Client builds with `HAS_IAPPS` (feature threshold 1.73.0), after configuration loads successfully but transport construction fails. Language methods additionally require their respective feature gates. This is not a claim about a missing game-server Apps export.

**Evidence**

`internal_reset()` establishes `config` before interface construction. `client = std::make_unique<Client>(this)` runs at line 49; Apps is only allocated at line 65. `Client.cxx:12–33` throws on ENet initialization or a null connection result. The actual connect implementation returns null for a hostname-resolution failure or host allocation failure (`Source/Vendor/Enet++/src/enetpp.cxx:166–190`). Consequently Apps remains null on a first failed initialization, and the public accessor returns that null pointer.

SDK 1.152.11 `GalaxyApi.h:293–308` explicitly says DLC discovery and game-language retrieval do not require the API to be fully initialized, although Init must have been called. Its lines 335–338 describe partial initialization and subsequent Shutdown. These are stronger, feature-specific guarantees than a generic assumption that every accessor must work before Init. The actual offline methods need only configuration: `Impl/Apps.cxx:20–33,37–66`.

**Failure mechanism / real trigger**

Start a fresh client with valid, readable local DLC/language configuration and a syntactically supplied server hostname that cannot resolve. Call Init using valid nonempty dummy SDK identifiers; catch the implementation exception currently described by BASE-CORE-005. A game continuing offline then obtains `Apps()` for DLC/language discovery. It receives null because construction stopped before the Apps allocation, despite the configuration required by those operations already being available. Simply translating the exception into GetError leaves exactly the same unavailable interface.

**Impact**

A recoverable LAN setup failure unnecessarily disables local DLC/language discovery; SDK-compliant offline fallback can dereference null or abandon startup. Medium reflects a failure-path compatibility defect, not an unconditional launch crash. An unreachable but resolvable relay generally does **not** trigger this constructor failure: ENet connection establishment is asynchronous.

**Possible solutions**

1. Establish a stable offline-capable interface tier before constructing optional transport, and track partial runtime state explicitly.
2. Catch transport failure within graph construction, retain valid offline services, and publish the failure through the SDK error channel.
3. Use a persistent Apps facade backed by valid configuration and explicit availability checks for its online-only operations.

**Recommended resolution**

Separate offline interface availability from network initialization, coordinated with BASE-CORE-005 but not reduced to an exception-boundary fix. Do not merely move the entire Apps allocation earlier and assume every Apps method is then safe: `IsDlcOwned` at `Apps.cxx:119–123` dereferences `user` and `notification`. Preserve offline methods while giving unavailable authentication-dependent methods a defined failure. Partial Shutdown must remain safe and a later clean initialization must work.

**Verification — proposed, not executed**

Inject DNS failure and ENet host-creation failure **after** configuration succeeds. Assert SDK error reporting, nonnull Apps, exact configured `IsDlcInstalled` and language/Copy results, and safe failure for authentication-dependent ownership checks. Then Shutdown and successfully reinitialize. Include a resolvable-but-offline relay control, which should not be mistaken for synchronous DNS failure. Use representative 1.114.9 and 1.152.11 Windows hosts; no external account credentials are needed.

**Baseline comparison**

The baseline described incremental publication and left partial initialization open; STORAGE's notebook also requested CORE investigation of Apps availability. No existing CORE ID covers this availability mechanism. BASE-CORE-005 covers error delivery, BASE-CORE-006 covers stdout restoration, and BASE-CORE-003 covers active-pump destruction; repairing any of those alone does not construct the missing offline interface.
