# Fresh review — Server.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–75. Static review.

## Inspection notes
- Checked member construction order: configuration precedes connection-dependent setup and SharedFileUtils, and managers precede use by event handlers.
- Traced authentication set, ID map, user snapshots, lobby/chat state, persisted share counter and activity timeout into implementations.
- The counter is 32-bit although shared-file IDs on the wire are wider. Exhaustion is a bounded long-run limitation; the reachable fresh-store/restart defect is **BASE-SERVER-006** in `ServerHandlers.cxx.review.MD`.
- The declared authentication timeout is 60 seconds; cleanup is tick-count-driven. Network timeout configuration is clamped to at least 100 ms by IniData, so a zero-valued uninitialized timeout is not the established runtime path.

## Result
No independent header finding. The implementation sidecars document state-machine, authorization and persistence failures.
