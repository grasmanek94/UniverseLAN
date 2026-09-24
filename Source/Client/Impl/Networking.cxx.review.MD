# Networking.cxx — fresh baseline review

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. All 170 lines read; Windows-focused static review.

## File-specific inspection

Reviewed reliability selection, client/server wrapper choice, per-channel queues, peek/read/pop/truncation/output behavior, listener dispatch/removal, NAT and connection-type stubs. Traced `ClientNetworkHandlers.cxx:141-158`, `ServerHandlers.cxx:302-453`, `Shared/Networking/Networking.{cxx,hxx}`, P2P message serialization, listener return semantics and SDK `1.152.11/galaxy/INetworking.h` in full. Also inspected legacy ServerNetworking routing documentation (`1.124.0/galaxy/GalaxyApi.h:157-181`).

The header allocates 256 channels, so channel 255 is in bounds. Packet ownership is retained by a shared pointer after releasing the queue lock. Reads truncate by the destination capacity and report full message size, matching the SDK. Auto-pop after all listener notifications is explicitly required by `INetworking.h:206-231`; consuming a packet with Read/Pop from those callbacks is expressly forbidden and is not used as a defect trigger. `IsP2PPacketAvailable` assumes a valid size output pointer; inspected SDK documentation does not promise null support, so the null dereference was not labeled a supported-input defect. NAT/ping/service approximations are recorded as compatibility limitations without an inferred networking exploit.

## Findings

### [BASE-API-013] Listener activation with queued packets mismatches notification and payload

- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Client/Impl/Networking.cxx:66-93,153-168`.
- **Affected scope:** Switching a P2P channel from queued polling to registered-listener delivery while unread packets remain.

**Evidence.** `AddPacket` appends the new packet, notifies with that new packet's size/channel, then pops the queue front if any listeners were invoked. `GetP2PPacket` always returns the front. `ListenerRegistrar.cxx:88-119,137-147` returns false when no listeners exist, so earlier packets remain queued. SDK `INetworking.h:29-35,155-179,206-209` associates callback size, callback-time Peek, and automatic removal with the packet being announced. SDK registration (`IListenerRegistrar.h:144-165`) has no prerequisite to empty P2P queues before registration.

**Failure mechanism.** Receive P1 on channel C with no listener, leaving it queued. Register a listener, then receive differently sized P2 on C. The queue becomes `[P1,P2]`; the callback announces P2's length, but its documented `PeekP2PPacket` call reads P1. After notification P1 is removed and P2 is left without its own correct notification. Later packets keep the stream one packet behind; the final packet can remain undelivered indefinitely. This sequence never calls forbidden Read/Pop/IsAvailable APIs from the listener.

**Impact.** Incorrect payload-size association, truncation based on the wrong announced length, and stranded packets. The same “append, notify outside queue coordination, pop front” design also needs care if event pumps run concurrently, but the finding does not depend on that extra assumption.

**Alternatives / recommended resolution.** Dispatch queued packets in FIFO order with size, Peek context and removal all referring to the same packet identity. Alternatively maintain an explicit callback-local packet view separate from polling backlog, with a defined transition policy. Prefer a per-channel delivery mechanism that drains pending packets after listener activation and serializes delivery for that channel; do not discard the backlog silently.

**Verification.** Queue P1 without listeners, register two listeners that only Peek, then deliver P2 on the same channel. Both listeners must see matching size/sender/payload for each packet exactly once. Repeat on channels 0 and 255 and verify the other channel is independent. Not executed.

### [BASE-API-014] Ordinary and immediate send types share the same background scheduling

- **Severity:** Low
- **Confidence:** High
- **Category:** API/ABI
- **Location:** `Source/Client/Impl/Networking.cxx:37-63`.
- **Affected scope:** Versions exposing `P2P_SEND_*_IMMEDIATE` and callers relying on ProcessData batching.

**Evidence.** Reliable and reliable-immediate map to the same flag; unreliable and unreliable-immediate likewise share a path. All call `GalaxyNetworkClient::SendAsync`, which queues a serialized packet (`Shared/Networking/Networking.hxx:142-153`). The independently running `Client::Tick` calls `RunNetworking` continuously (`Client.cxx:37-41`), which drains that queue before polling (`Networking.cxx:123-140`). SDK `INetworking.h:96-102` says ordinary types send during the next ProcessData call, whereas immediate types send instantly.

**Failure mechanism.** Call an ordinary send, then continue application work without ProcessData. The network thread can transmit it before the documented batching boundary. Immediate mode selects no distinct dispatch/flush behavior. Keeping `send_type` in the wire packet does not restore the client-side scheduling boundary.

**Impact.** Observable SDK scheduling/ordering incompatibility for games using ProcessData as a frame/batch boundary. No measured throughput or latency degradation is asserted, hence Low severity.

**Alternatives / recommended resolution.** Separate ordinary sends awaiting the next API pump from immediate transport scheduling, preserving thread-safe enqueueing and reliability flags. If transport-thread delivery is retained, an explicit release-to-transport step from ProcessData can provide the ordinary-send boundary without calling ENet from arbitrary application threads.

**Verification.** Schedule an ordinary packet while the sender's background transport runs but its API pump is paused; the receiver should not observe it until the next sender ProcessData. Contrast immediate mode and both reliability levels. Not executed.

## Thorough follow-up addendum — 2026-09-24

All 170 implementation lines and 245 header lines reread at unchanged production baseline `b30e8387`, followed by actual Client/Server routing and versioned SDK checks. Original findings remain preserved; no execution performed.

### [ADD-API-004] NEW — Legacy server packets notify the client listener class and can be discarded unseen

- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Client/Impl/Networking.cxx:153-168`, `AddPacket`; initialization at `UniverseLAN.cxx:56-59`; dispatch at `ClientNetworkHandlers.cxx:141-157`.
- **Affected scope:** SDK 1.57.0 through 1.134.10 inclusive (`HAS_ISERVERNETWORKING`), ordinary peer lobby-owner `ServerNetworking()` reception; also the corresponding old GameServer server-networking listener path. This finding does not depend on dedicated-server initialization working.

**Evidence.** SDK `1.124.0/galaxy/INetworking.h:43-68` defines a distinct `IServerNetworkingListener`, listener type `SERVER_NETWORKING`, and method `OnServerP2PPacketAvailable`; the 1.57.0 header also supplies that interface. The regular peer has separate client and server `NetworkingImpl` objects sharing its registrar. Server routing wraps lobby-addressed input in `P2PServerNetworkPacketMessage` (`ServerHandlers.cxx:397-423`); Client puts it into `server_networking` for those versions. Regardless of which queue owns the packet, `AddPacket` calls only `INetworkingListener::OnP2PPacketAvailable`, whose registrar type is `NETWORKING`, and uses that call's boolean result to decide auto-pop. The transport/registrar contains no compensating translation.

**Failure mechanism.** With empty queues, a member sends to its lobby ID. The owner registers the documented server listener: its queue receives the packet but its listener is never invoked. If the owner also has a normal client listener, that unrelated listener is invoked instead. Its legitimate `Networking()->PeekP2PPacket` cannot see the packet in `ServerNetworking`; nevertheless, notification returns true and the server packet is popped. No polling/listener overlap on the same interface and no forbidden Read/Pop inside a callback are needed. A normal client listener can even cause loss from a separately polled server queue.

**Impact.** Callback-driven legacy hosting fails outright; dual-interface consumers can silently lose lobby-directed packets. Polling-only coverage can pass, masking the listener-class error. This is independent of BASE-API-013's backlog packet-identity defect and occurs with the very first packet.

**Alternatives.** Choose the proper notification interface from the receive-queue role and SDK gate, or give the two queue implementations distinct dispatch policies. Merely consulting whether any listener is registered still makes auto-pop depend on the wrong interface.

**Recommended fix.** Preserve legacy `SERVER_NETWORKING` dispatch for the legacy server queue; use `NETWORKING` for ordinary client reception and the unified newer networking surface. Base automatic removal solely on delivery to listeners of that receiving interface. Do not change modern GameServer registrar selection to the peer registrar. Queue role must remain unambiguous when both objects exist.

**Verification.** On an SDK such as 1.124.0, create/join a valid lobby, register both listener types, and deliver distinct payloads to the owner's user ID and lobby ID on the same channel. Each callback must Peek its own interface with matching size/sender/payload and only its own packet must auto-pop. Repeat with only server listeners, client-listener plus server-polling mode, channels 0/255, and a post-1.134.10 unified-interface control. Not executed.

### Existing BASE findings and exception-path qualification

- **BASE-API-013 retained (Medium):** activating a listener with pending polling data is not forbidden by the inspected registrar contract. Read/Pop/IsAvailable while employing that same listener is forbidden and remains excluded as a trigger. A callback exception skips `PopP2PPacket`, leaving another possible backlog; exception-safe callback cleanup should be specified with the same queue-identity fix, not counted as a new defect without a supported throwing-listener contract.
- **BASE-API-014 retained (Low):** serialization/queueing preserves reliability but the independent Client tick releases both ordinary/immediate sends. No latency claim or requirement to call ENet from arbitrary API threads is inferred.
- `IsP2PPacketAvailable(nullptr)` still has no SDK-supported null-output contract. Packet data is copied into the wire object before send returns, and `GetP2PPacket` retains a shared owner after pop; neither path requires caller storage to survive asynchronously. 1,200 bytes is a recommendation, not a hard limit. No new size/null or channel-255 finding.
