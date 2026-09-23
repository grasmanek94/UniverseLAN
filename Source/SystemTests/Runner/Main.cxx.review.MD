# Fresh review — Runner/Main.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–200. Static Windows review.

## Inspection notes
- Followed provider/version checks, unique run root, server and loopback WebSocket startup, host staging, wait/action/finish gates, persistence-group serialization, signal completeness, failure cleanup and final directory removal.
- A persistence successor requires its previous same-group host to have PASS, exit and code zero. Host `_Exit` intentionally bypasses DLL teardown; server-observed disconnect is asynchronous, so this is not equivalent to waiting for backend identity removal.
- The pass predicate requires all started hosts, their PASS and successful exit, and every declared signal. WebSocket and children are stopped on std::exception failure paths.
- CTest timeout includes setup/cleanup while the runner's scenario deadline begins after setup; failure-time cleanup may consume additional time. No execution-duration claim is made.

### [BASE-SERVER-012] Child can exit successfully between log snapshot and exit check, causing a false failure

- **Severity:** Medium
- **Confidence:** High
- **Category:** Testing
- **Location:** `Source/SystemTests/Runner/Main.cxx:136–138`; `Runner/Process.cxx:138–160`; host terminal output `Host/Main.cxx:572–574`.
- **Affected scope:** Every polled SystemTests host on Windows (also structurally applicable to the other process branch).

**Evidence.** The runner reads currently visible log bytes, then calls updateChild, then immediately rejects an exited child if sawPass is false. readLines first snapshots file size; it does not wait for process exit or terminal output. Hosts flush PASS via endl immediately before `_Exit(0)`.

**Failure mechanism.** Runner snapshots the log before PASS exists. Child writes/flushed PASS and exits before GetExitCodeProcess. Runner observes exit code zero but has not consumed the newly appended PASS, and throws without a final drain. The same ordering can miss final event records even if PASS was already observed.

**Impact.** Scheduling-dependent false negatives in otherwise correct tests, especially short hosts. Child-side flushing does not close the race because the reader's snapshot occurred earlier.

**Alternatives / recommendation.** Once exit is observed, drain all remaining complete log records and then validate terminal state. Alternatively poll exit before reading, while still doing a final drain on transition. Preserve duplicate/invalid-protocol rejection and define handling of a non-newline tail.

**Verification.** Use a tiny controlled child that flushes final EVENT/PASS and exits between the runner's file-size snapshot and exit poll. Repeat with no PASS, nonzero exit, malformed final record and duplicate PASS: valid output must succeed while invalid terminal states remain failures. No child was launched in this review.
