# Fresh baseline review — DelayRunner.cxx

- Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`.
- Coverage: entire file, lines 1–17; static review only.

## Specific checked notes

- `Add` copies the callable into the concurrent queue; `Run` pops into a local `std::function` before invocation, so execution does not retain a reference to a queue element.
- Traced both callers: client `ProcessData` and game-server `ProcessGameServerData`. On Windows/MSVC, `ConcurrentQueue.hxx` selects PPL's concurrent queue.
- Producer/consumer queue safety does not serialize multiple `Run` callers or protect the enclosing runner's lifetime. Shutdown destroys the runner while a callback may still be executing.
- Drain-until-empty permits callbacks/producers to extend a pump indefinitely; callback exceptions also propagate out of `Run`. These are unbounded-work/exception-policy observations, without a separate demonstrated starvation or exception contract violation here.

## Confirmed cross-file defect

### BASE-CORE-003 — Run resumes on a destroyed queue after callback-time shutdown

- **Severity:** High
- **Confidence:** High
- **Category:** Memory Safety
- **Location:** `Source/Client_NoVer/Impl/DelayRunner.cxx:7–11`; destruction at `Source/Client/UniverseLAN.cxx:130–133`.
- **Affected scope:** Both SDK pumps and any callback that requests their shutdown. Canonical graph-level report: `Source/Client/UniverseLAN.cxx.review.MD`; counted once in `CORE.MD`.

**Evidence**

`Run` invokes application code at line 10 and then unconditionally accesses the member queue again at line 9. The SDK entry-point pumps call this through a `unique_ptr`. Their shutdown methods immediately reset the same owner. SDK shutdown's documented listener-unregistration precondition can be satisfied while a manually managed specific callback is still executing.

**Failure mechanism**

A specific DLC listener unregisters itself, calls `Shutdown`, and returns. Reset deletes this runner. The locally popped callable survives until it returns, but the enclosing queue does not; the next loop condition dereferences freed storage. No concurrent producer or double-free of the listener is needed.

**Impact**

Callback-driven session cleanup can cause use-after-free and a process crash.

**Possible solutions**

Defer destruction until dispatch exits, or pin a runtime state object through every active pump and implement a stop request. A queue-only lifetime extension cannot protect the registrar/interfaces used by other callbacks.

**Recommendation**

Coordinate this loop with the graph-level lifecycle guard: stop dispatch on a shutdown request and perform ordered teardown at a safe outer boundary.

**Verification**

Queue a specific completion that unregisters then shuts down; require the pump to return cleanly with no later callbacks, then reinitialize. Repeat for the game-server pump under Windows ASan/page heap. Proposed only, not executed.
