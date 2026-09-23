# Fresh review — Networking.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read all 270 lines. Static Windows lifecycle and packet-ownership review; no execution of product code.

## Inspection notes
- Followed `ProcessEvent` to all Client/Server handlers and the actual cereal input archive. Its receive guard destroys packets on rejected class IDs, decode failures, normal returns and handler unwinding.
- `Cleanup` and `ProcessEvents` both consume the concurrent queue. A packet successfully popped by one cannot also be popped by the other; no generic double-free finding is justified. Their logical disconnect-delivery race is BASE-NET-013 below. Connection generations also deserve targeted validation.
- The worker flushes outbound packets before polling, timestamps every transport event, and reconnects immediately on its own inactivity timer or after five seconds for ordinary disconnects. Enet++ reuses a peer slot in the existing host; raw event peers are not independent session tokens. A callback already popped before cleanup can still enqueue stale work after cleanup.
- `Pull` returns an integer; negative errors are treated as truthy. The vendor normally resets the event to NONE first, so this is error swallowing, not established stale-packet dispatch. Server's `while(Pull())` on persistent errors needs separate owner review.
- BASE-NET-001/002/004/005/007 are fully defined in the header's report, where their decoder/send/queue contracts reside; this file was independently inspected, not inferred from that report.

### [BASE-NET-003] Vendor timeout-disconnect events are omitted from both lifecycle switches
- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Shared/Networking/Networking.cxx:20-104,146-167,171-214`.
- **Affected scope:** Windows client initial connection/retry and server peer retirement.

**Evidence / failure mechanism:** This vendored ENet-IPv6 has `ENET_EVENT_TYPE_DISCONNECT_TIMEOUT = 4` (`include/enet6/enet.h:462`). `protocol.c:163-183` and `60-90` emit it and reset the peer. Shared recognizes only `ENET_EVENT_TYPE_DISCONNECT` in both `MessageReceiver::ProcessEvent` and `GalaxyNetworkClient::RunNetworking`. A timeout event is queued and counts as activity but changes no lifecycle state and reaches no disconnect handler.

**Reproduction conditions:** Start a client against a silently unavailable endpoint and let ENet's initial CONNECT retransmission time out before any CONNECT event. `is_connected` stays false, `next_reconnect_time` is still empty, and the application inactivity check requires `is_connected`; bringing the server up afterward does not initiate another attempt. On the server, let ENet retire a peer before Shared's cleanup timer (notably a transport-connected unauthenticated peer, whose application timeout is 60 seconds), then reuse the ENet slot.

**Impact:** Initial connection can remain permanently stalled until client recreation. Server disconnect handling is skipped while its mapper/unauthenticated set still refers to a slot already reset by ENet; reconnect's `peer->data = nullptr` can lose the old allocation/state before the later cleanup. Ordinary application timeout often masks the connected-session symptom, which limits severity.

**Alternatives / recommended resolution:** Normalize both vendor disconnect events into one retirement path, preserving timeout reason for diagnostics. Ensure failed initial connection attempts arm retry independently of previous connected state. Use an explicit connection generation if events cross threads, and retire server application state before a peer slot is reused.

**Verification:** Windows tests should cover no-server startup followed by server startup, loss during connecting and after acceptance, explicit disconnect, and timed-out slot reuse. Verify retries, one logical disconnect, empty mapper/lobby memberships and no leaked peer data. No such tests were run here.

### [BASE-NET-013] Queue cleanup races with delivery and can emit two disconnect notifications
- **Severity:** Low
- **Confidence:** High
- **Category:** Concurrency
- **Location:** `Source/Shared/Networking/Networking.cxx:158-165,186-191,219-226,247-255`.
- **Affected scope:** Windows client's network worker and application-thread ProcessData.

**Evidence / failure mechanism:** An ordinary ENet disconnect is first pushed into `received_events_to_process`. The same worker then calls Cleanup and unconditionally pushes a synthetic disconnect. If ProcessEvents pops the first event before Cleanup, the cleanup cannot remove it and the synthetic event is delivered too. Client handlers call Utils/User state-change notifications without an equal-state suppression check (`ClientNetworkHandlers.cxx:47-58`, `Impl/Utils.cxx:85-92`, `Impl/User.cxx:624-670`). Queue thread safety preserves memory ownership but not exactly-once logical delivery.

**Reproduction conditions:** Two threads run normally; pause the worker immediately after line 165 on an explicit remote disconnect, let the application pump consume that event, then resume worker cleanup and pump again. Both notifications refer to one transport transition. No timeout or malicious frame is necessary.

**Impact:** Duplicate connection/operational-state callbacks and duplicate consumer side effects. No memory corruption is established; repeat state assignment is benign for the internal flags, hence Low severity.

**Alternatives / recommended resolution:** Retire/drain the connection before publishing one disconnect event, rather than publishing and trying to retract it. Alternatively attach connection generations and deduplicate transition delivery in one owning state machine. Merely using a concurrent queue cannot make this compound operation atomic.

**Verification:** Deterministically schedule the pop between enqueue and cleanup, then also test the opposite ordering and application inactivity timeouts. Assert exactly one disconnect notification per generation and exactly-once receive-packet destruction. Proposed test only.
