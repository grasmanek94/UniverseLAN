# Fresh baseline review — GalaxyDLL.cxx

- Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`.
- Coverage: entire file, lines 1–190; static review, including Windows startup, failure, and shutdown paths.

## Specific checked notes

- Traced console capture/release, initialization exception handling, tracing configuration, interface publication, and worker start. Module filename handling uses a bounded, initialized `MAX_PATH` buffer; long-path completeness is a diagnostic limitation, not a confirmed memory overrun here.
- Checked all feature-gated getters against graph members and SDK accessors. Their raw pointers borrow runtime-owned objects.
- `ProcessData` processes network events before delayed notifications. Null checks help outside initialization, but do not pin graph objects during callback execution (`BASE-CORE-003`).
- `ShutdownEx` currently shares normal reset and ignores the option; detailed SDK-internal static-preservation compatibility remains unverified.
- Inspected authentication-related diagnostic code without reading runtime configuration or credentials. Intentional LAN trust/authentication design is not treated as an exploit finding.

## Confirmed findings

### BASE-CORE-005 — Initialization failures bypass the SDK error-return contract

- **Severity:** Medium
- **Confidence:** High
- **Category:** API/ABI
- **Location:** `Source/Client/GalaxyDLL.cxx:35–47,183–185`; related `GalaxyApiFactory.cxx:40–65,154–156`, `Impl/InitOptionsModern.cxx:10–45`, `UniverseGameServer.cxx:26–37`.
- **Affected scope:** Modern client/game-server Init; legacy Init/InitLocal with exceptions disabled.

**Evidence**

The init catch displays an error then unconditionally rethrows. `GetError()` unconditionally returns null. The factory error manager does the same, and legacy `throwExceptions` arguments are not honored. SDK 1.152.11 `Errors.h:94–99` defines per-thread last-error retrieval; `GalaxyApi.h:77–85` defines `GetError` as the normal error channel and the optional `ThrowIfGalaxyError` translation. Legacy 1.114.9 `IGalaxy.h:46–58,89–91` explicitly supplies an exception policy. `InitOptionsModern` initializes its policy to false without copying the legacy field, and no consumer enforces it.

**Failure mechanism**

An unresolvable configured host makes `enetpp::NetworkClient::Connect` return null (`Vendor/Enet++/src/enetpp.cxx:166–170`). `Client.cxx:27–33` throws `std::runtime_error`, which escapes exported Init instead of becoming an SDK `IError`. A legacy caller that explicitly requested `throwExceptions=false` follows the same path. If the application catches it and consults `GetError`, the API still reports no error.

**Impact**

Recoverable network/configuration failures can become unhandled exceptions in games expecting the SDK's nonthrowing interface, and standard SDK error/exception helpers cannot diagnose them. This is an error-model incompatibility, not a proven binary-layout mismatch. Severity is Medium because the demonstrated trigger is an initialization failure, not every successful launch.

**Possible solutions**

1. Translate failures at API boundaries into thread-local SDK-compatible error objects, honoring legacy exception settings.
2. Centralize error entry/exit handling across interfaces so last-error reset and lifetime rules are consistently enforced.

**Recommendation**

Implement a per-thread last-error store and a single boundary policy. Modern APIs should report SDK errors without leaking implementation exceptions; old overloads should preserve their configured throwing behavior. Reset errors at the documented API boundaries and retain error data long enough for `GetError`/`ThrowIfGalaxyError`. Do not solve this by silently swallowing exceptions or reporting successful initialization.

**Verification**

Force DNS/ENet initialization failure with synthetic configuration. Check modern Init, game-server Init, legacy Init(false), InitLocal(false), and legacy InitOptions(false). Require the appropriate runtime error on the originating thread, independence on another thread, and reset on the next API call. Check legacy enabled-exception behavior separately. No fault injection or executable test was run.

### BASE-CORE-006 — Failed initialization leaves process-wide stdout captured

- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Client/GalaxyDLL.cxx:24,35–47,60`.
- **Affected scope:** Client initialization that throws after console capture and before release.

**Evidence**

`Redirector::get()->capture()` replaces `std::cout`'s stream buffer before initialization. The only balancing `release()` is on the success path. `Shared_NoVer/ConsoleCoutRedirector.cxx:25–46` shows the process-wide buffer replacement/restoration; its singleton is heap-allocated and never normally destroyed (`53–55`). Neither this catch nor `Shutdown` releases it.

**Failure mechanism**

Use the same ENet/DNS failure path as `BASE-CORE-005`. A host application catches the init exception and continues in offline mode. All subsequent output to the shared `std::cout` is appended to the redirector's string buffer instead of the original sink, because no success-path release occurred. Shutdown does not repair it.

**Impact**

Recovery diagnostics and later console output disappear and retained output can grow in memory for the rest of the process. This applies where the game and DLL share the affected C++ standard-stream instance; at minimum it captures subsequent output through the DLL's stream instance.

**Possible solutions**

1. Use a scope guard to release capture on every exit, including exceptions.
2. Make capture an RAII session that restores the previous buffer and exposes explicit successful replay.

**Recommendation**

Use RAII ownership for capture immediately after it starts, preserving the current success-path console/replay behavior while restoring the original stream on failure. This remains necessary after repairing the SDK error boundary.

**Verification**

Record the original `std::cout.rdbuf()`, force init failure, handle it, then verify buffer identity and visible output after recovery and shutdown. Repeat failed/successful initialization to detect nested capture errors. Proposed only; no execution occurred.
