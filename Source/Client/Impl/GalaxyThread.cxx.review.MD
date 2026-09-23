# Fresh baseline review — GalaxyThread.cxx

- Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`.
- Coverage: entire file, lines 1–89; static Windows C++ lifetime review.

## Specific checked notes

- Checked the thread move into the wrapper, forwarding entry point/parameter, join/detach/Joinable feature gates, and destructor behavior against SDK `GalaxyThread.h`.
- Source call tracing found `GalaxyThreadFactory::SpawnThread` only in its implementation/declaration, not wired into `Client::Start`. The runtime creates a `std::thread` directly; supplied SDK factory pointers are copied into InitOptions but not consumed by this path.
- `SpawnThread` uses ordinary `new` despite the SDK allocator note. Because no production consumer of this wrapper was found, allocator integration is recorded as an unverified integration gap rather than a demonstrated cross-allocator free.

## Confirmed finding

### BASE-CORE-008 — Destroying a joined or explicitly detached thread wrapper terminates

- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Client/Impl/GalaxyThread.cxx:25–26,44–45,49–58`.
- **Affected scope:** Direct use of `GalaxyThreadImpl`/`GalaxyThreadFactory` when the feature is enabled (1.140.0 onward); no current production caller found.

**Evidence**

`Join()` calls `_thread.join()`, and newer versions expose `Detach()` calling `_thread.detach()`. Both leave the thread non-joinable. The destructor unconditionally calls `_thread.detach()` again. Detaching a non-joinable `std::thread` throws `std::system_error`; this destructor is implicitly nonthrowing.

**Failure mechanism**

Spawn a thread, join it normally, then delete its `IGalaxyThread` wrapper. The destructor tries to detach the now non-joinable thread and invokes `std::terminate` when the exception escapes. Explicit detach followed by deletion has the same result. A default/non-joinable thread moved into the public constructor also triggers it.

**Impact**

Normal wrapper cleanup is fatal if this class is used. Severity is reduced to Medium because the reviewed client startup bypasses this otherwise confirmed defective implementation; this is not a claim that normal production shutdown currently reaches it.

**Possible solutions**

1. Guard any destructor thread operation with `joinable()` and select a documented join/detach policy.
2. Require explicit lifecycle completion and enforce it through a nonthrowing destructor policy, with diagnostics for a still-running thread.

**Recommendation**

Make destruction after Join or Detach a no-op for the native thread. Decide explicitly whether destruction of a still-running wrapper joins or detaches, considering parameter/DLL lifetime; do not blindly detach an SDK worker that may outlive its data. Integrate allocator/factory support only with matching ownership semantics.

**Verification**

When execution is allowed, cover spawn/join/delete, spawn/detach/delete (newer SDKs), completed-but-unjoined destruction, and a moved non-joinable thread. No termination should occur on valid completed lifecycles. No executable test was run here.
