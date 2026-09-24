# Fresh review — Server.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–200. Windows-focused static review; no server execution.

## Inspection notes
- Traced constructor configuration, host creation, LAN-key challenge seed, share-counter load, authentication/activity sweeps and Tick.
- `KickUnauthenticated` returns false and the calling macro returns from protected handlers; commented-out immediate kicking does not disable the authorization gate.
- Timeout sweeps explicitly call application disconnect cleanup before immediate transport reset. Authentication rejection does not: **BASE-SERVER-001**.
- Snapshot sends serialize synchronously; mutable outgoing shared-message reuse does not itself alias later packets.

### [BASE-SERVER-002] Transport timeout can leave an old identity attached to a reused peer slot

- **Severity:** High
- **Confidence:** High (static control/data-flow evidence; not reproduced)
- **Category:** Correctness
- **Location:** `Source/Server/Server.cxx:172–188`, `Server::Tick`; `Source/Server/ServerHandlers.cxx:36–45`; `Source/Server/Peer.cxx:22–28,31–39`.
- **Affected scope:** Server identity, lobby/chat membership and user lookups after ENet timeout and slot reuse.

**Evidence.** Tick forwards events to `MessageReceiver::ProcessEvent`. Its switch at `Source/Shared/Networking/Networking.cxx:85–104` handles ordinary disconnect only. Vendored ENet defines `ENET_EVENT_TYPE_DISCONNECT_TIMEOUT = 4` (`include/enet6/enet.h:462`) and emits it while resetting the slot (`src/protocol.c:163–183`). Reset retains `peer->data` but clears transport `connectID` (`src/peer.c:389–443`). The next server connect unconditionally writes `peer->data = nullptr`. `Mapper::Get(oldID)` follows the old map entry to whatever Data is now on that same slot.

**Failure mechanism.** A transport timeout occurs before the application sweep (for example with a longer configured application timeout, or loss of reliable acknowledgments while inbound activity keeps that timer alive). The timeout event is ignored. A new connection reuses the slot before cleanup; its connect handler loses the old Data and its memberships, but the old GalaxyID map and user record remain. A request for the old ID now resolves the new Data. Before that newcomer authenticates, `RequestSpecificUserDataMessage` at `ServerHandlers.cxx:186–189` dereferences its null `user_data`; afterward old-ID traffic can resolve to the new identity. Reconnecting with the old ID can also remain rejected because the original registration survives.

**Impact.** Reachable server crash or incorrect identity routing and stale membership. The default application timeout often wins, reducing likelihood, but does not establish a lifecycle invariant. This is not an assertion that every ordinary disconnect is broken.

**Alternatives / recommendation.** Handle both transport disconnect event kinds in the shared dispatcher and perform server cleanup before any replacement attachment. Add an explicit connection generation/ownership check to ID lookups; do not infer a generation from disconnect event data (the timeout path sets it to zero and resets `connectID`). A defensive cleanup-on-connect is useful but should not replace handling the timeout event. Coordinate the shared-dispatch fix with NET ownership.

**Verification.** On Windows, set application timeout above ENet timeout, authenticate A with lobby/chat state, induce transport timeout, then connect B into that slot before the sweep. Query A before and after B authenticates; verify no crash, no A-to-B routing, old membership cleanup and successful later A reconnect. Repeat with the normal disconnect path. Not executed here.

### [BASE-SERVER-016] Startup prints the reusable authentication key material

- **Severity:** Medium
- **Confidence:** High
- **Category:** Security
- **Location:** `Source/Server/Server.cxx:90–103`, constructor key hashing and console output.
- **Affected scope:** Deployments using a non-default LAN key whose console output is exposed to log readers/support bundles.

**Evidence.** The printed `authentication_key` is exactly the 64-bit value supplied to `Challenge::Prepare`. `KeyChallengeMessage.hxx:67–75` computes the valid response by XORing that value with the received challenge and hashing the resulting bytes.

**Failure mechanism.** Knowledge of the printed number suffices to answer future challenges. Recovering the configured text or inverting its FNV hash is unnecessary.

**Impact.** Someone with output/log access and server network reachability can join the protected LAN service. This is conditional log disclosure, not an assertion that the public default key establishes a strong security perimeter.

**Alternatives / recommendation.** Omit the value entirely; log only that authentication configuration loaded. If operators need key matching, use a separately derived, non-reusable diagnostic fingerprint, not the actual protocol key.

**Verification.** Capture startup output using a synthetic non-secret test key and confirm no usable protocol-key value appears. An isolated protocol test should show that output alone cannot supply challenge-response material.

### [BASE-SERVER-018] Negative network-service results are treated as events

- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Server/Server.cxx:172–177`, `Server::Tick`.
- **Affected scope:** Server event loop under a persistent socket/service error.

**Evidence.** `while (connection.Pull())` accepts `-1`. The wrapper returns `enet_host_service` verbatim (`Enet++/src/enetpp.cxx:54–60`); that function documents negative failure and returns -1 on outgoing/incoming network errors (`Enet-IPv6/src/protocol.c:1913–1915,1956–1982`). It resets event type to NONE before servicing.

**Failure mechanism.** A persistent error repeatedly enters the body with no useful event; the outer sleep and the sweeps after the drain never run. A transient error is silently consumed.

**Impact.** CPU spin and unavailable service on an already-failing socket. No stale-packet double-free is alleged because this ENet implementation clears the event.

**Alternatives / recommendation.** Drain only positive results, distinguish zero from negative, and use an explicit logged restart/exit policy or bounded retry/backoff for errors. Avoid an unbounded immediate retry.

**Verification.** Inject a Pull sequence of positive, zero, and persistent negative results; verify each valid event is processed once and failure exits/backoffs without spinning or starving cleanup.

## Follow-up addendum — 2026-09-24

Full lines 1–200 re-read before baseline comparison; all three findings retain their original severity/category and High confidence.

### [BASE-SERVER-002] Addendum — generation, timeout and ownership revalidation

The vendor's timeout event is explicitly different from ordinary disconnect (`Enet-IPv6/src/protocol.c:80–90,163–184`), and the shared receiver still omits it (`Shared/Networking/Networking.cxx:85–104`). Reset does not clear/free application `data`; replacement connect does. The baseline failure sequence therefore remains reachable without asynchronous server-side event processing: the server processes one timeout event, then a later connect on the same slot before its application cleanup. `Mapper::Get(oldID)` does not validate the new attachment's `id`. Before B authenticates, A's old map resolves B's null `user_data`; after B authenticates, old-ID lookup resolves B's state. The application timeout is clamped to at least 100 ms (`Shared/IniData.cxx:312–315`), but there is no upper bound that makes it always precede ENet's timeout. Neither the reset `connectID` nor event data zero is an application generation token. Keep the High integrated priority and NET handoff; original focused validation remains proposed.

### [BASE-SERVER-016] Addendum — protocol-equivalent disclosure retained

The number printed at 103 is the exact effective key used by `Challenge::Prepare`; XOR plus the public response hash accepts that number without knowing the original text. This is a log-reader-with-network-access condition, not passive-network cryptanalysis or an external account impersonation claim. No runtime INI, private key or credential was opened during this review.

### [BASE-SERVER-018] Addendum — error return contract retained

Re-read `enet_host_service`'s >0/0/<0 contract and error exits (`Enet-IPv6/src/protocol.c:1906–1982`). It clears type/peer/packet at 1924–1928 before servicing, so the confirmed persistent-negative spin still does not establish a stale-packet double-free. A bounded event-drain budget would additionally help fairness under sustained positive traffic, but no separate measured starvation finding is counted.

### Startup/shutdown notes

The counter consumer at 96–101 is also the sink for **ADD-SERVER-001**, fully documented in `ServerHandlers.cxx.review.MD`; no duplicate ID is assigned here. `Server::~Server` performs no peer sweep, and `Mapper` has no owning destructor. That is a cleanup limitation, but the actual executable's endless main loop and process termination do not establish repeated normal server-object teardown leaks. Server operation is single-threaded; no concurrent-map race is inferred from raw pointers alone. Network/config/source files were not modified or executed.
