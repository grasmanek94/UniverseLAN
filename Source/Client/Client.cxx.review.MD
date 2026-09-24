# Fresh baseline review — Client.cxx

- Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`.
- Coverage: entire file, lines 1–83; static Windows lifecycle/network review.

## Specific checked notes

- Traced constructor setup into `enetpp::NetworkClient::Connect`: ENet initialization, host lookup, socket/host creation, and initial peer allocation. A non-null connect result starts an asynchronous connection; it is not treated as authentication success.
- Configuration timeout is installed before the worker starts. `running` is atomic; ordinary Stop clears it and joins a joinable worker before member destruction.
- `Tick` performs only networking/queue work; application message handlers run when `ProcessEvents` is called by the SDK pump. This distinction was used when assessing teardown and callback races.
- `Start` is not idempotent: assigning to an already joinable thread would terminate. Actual production callers start once after constructing a fresh Client; no supported double-Start path was found, so no standalone finding is claimed.
- Traced the worker's final `Disconnect` and the connection's queue cleanup/destructors. Normal explicit shutdown joins before destroying the connection.
- Connection construction throws `std::runtime_error`; SDK translation is absent at the public boundary (`BASE-CORE-005`). Pump destruction during callbacks is `BASE-CORE-003`.

## Findings and limits

No independent Client-local defect was confirmed beyond those canonical cross-file findings. Concurrent Start/Stop, thread-creation failure, ENet timeout/reconnect behavior, and Windows DLL-unload/loader-lock execution were not tested. Source inspection of atomic termination and join ordering does not prove the whole runtime thread-safe.

## Full-reread addendum — 2026-09-24

The original conclusion above is preserved. Fresh contract-to-callee tracing promotes the previously open stored-options observation to a concrete API behavior finding; it does not allege a binary-layout or cross-allocator corruption defect.

### [ADD-CORE-002] Accepted initialization controls are stored but never applied to transport or worker creation

- **Severity:** Medium
- **Confidence:** High
- **Category:** API/ABI / configuration semantics
- **Exact location:** `Source/Client/Client.cxx:23–33,61–67`; `Source/Client/UniverseLAN.cxx:47–49`; `Source/Client/Impl/InitOptionsModern.cxx:31–43`.
- **Affected scope:** Client and game-server graphs using nondefault local bind options (`HAS_INITOPTIONS_HOST_PORT`, threshold 1.132.0) or a nonnull custom thread factory (`HAS_IGALAXYTHREADFACTORY`, threshold 1.140.0). These are two manifestations of the same inert normalized runtime-options object, counted once.

**Evidence**

SDK 1.132.1 `InitOptions.h:38–39,64–65` and 1.152.11 `InitOptions.h:39–41,68–70` identify host/port as the **local** bind address/port and the thread factory as the hook used to spawn internal threads. The normalizer copies these values, and `InterfaceInstances::init` stores them before creating Client. A source search of Client implementations finds only creation/reset of `init_options`, with no runtime consumer.

Client connects using `config->GetServerAddress()/GetPort()` and starts its worker with a direct `std::thread`. The ENet++ callee resolves that configured **remote** relay address, then calls `enet_host_create(address.type, nullptr, ...)` (`Source/Vendor/Enet++/src/enetpp.cxx:166–185`): no requested local endpoint reaches host creation. Neither Client nor its startup caller invokes the supplied factory. The existing `GalaxyThreadFactory::SpawnThread` implementation is also not wired into this path. SDK `GalaxyThread.h:62–73` defines the custom spawn operation.

**Failure mechanism / real triggers**

1. A host passes a valid local interface address and a selected nonzero UDP port in InitOptions, for example to match a local firewall rule or an established port reservation policy. Initialization silently creates the ordinary automatically assigned client endpoint instead. Changing the INI relay port changes the destination, not this ignored local endpoint.
2. A game supplies an IGalaxyThreadFactory that establishes worker affinity, naming, accounting, or required per-thread setup before invoking the supplied entry point. Initialization succeeds and the network worker runs, but the hook is never called, so that setup is absent.

Both triggers use supported, nondefault SDK arguments. No particular game's dependence on either option, percentage of failures, or credential/service interaction is asserted.

**Impact**

The ABI accepts controls that do not control runtime behavior. Configured endpoint expectations and custom-worker integration silently fail, complicating networking and host integration. This is a bounded compatibility defect, not evidence that ignored allocator hooks cause a mismatched free: current ordinary allocations are not shown being returned through an application allocator.

**Possible solutions**

1. Apply a normalized runtime policy at connection/worker creation: separate local bind from the remote relay and use the supplied thread factory when present.
2. If a control cannot be supported by this backend, explicitly reject that nondefault setting through the SDK error channel and document the supported subset rather than silently accepting it.

**Recommended resolution**

Wire local endpoint and thread-factory policy into the owning Client lifecycle, with the current behavior as the null/zero default. A factory-created IGalaxyThread needs the SDK-compatible join/destruction/allocator ownership protocol; fix the dormant BASE-CORE-008 wrapper before considering it a safe default adapter. Include custom-networking workers in the eventual hook policy. Do not reinterpret SDK `host` as the relay host. The allocator/config-directory/static-preservation questions need their own explicitly defined support policy; this finding does not infer arbitrary meanings for them.

**Verification — proposed, not executed**

On Windows, pass a known available local address/port and inspect the created UDP endpoint (`getsockname` via an instrumented transport or OS endpoint inspection). Assert the requested endpoint, with null/zero controls and an unavailable-port case. Pass a spy thread factory that runs the entry point on a real joined worker and records creation/setup/join/destruction; require the network worker to pass through it and verify clean shutdown. Repeat through InitGameServer. No builds, sockets, hooks, or executable probes were run in this review.

**Baseline comparison**

Baseline CORE recorded copied-but-unused hooks/bind values as an integration question, without an ID. The decisive extra evidence here is the SDK's local-endpoint contract plus the actual null ENet bind argument and unconditional native worker creation. This is distinct from BASE-CORE-005's lost exception policy and BASE-CORE-008's defective but dormant wrapper destructor. All manifestations above share one new ID to avoid inflating the count for each unused field.
