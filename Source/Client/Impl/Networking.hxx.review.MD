# Networking.hxx — fresh baseline review

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. All 245 lines read; Windows-focused static review.

## File-specific inspection

- Inspected the client/server/game-server kind, packet ownership (`shared_ptr<const P2PNetworkPacketMessage>`), queue wrapper, lock aliases and all networking overrides.
- The channel-array bound is explicitly `max(uint8_t) + 1`, correctly covering every public `uint8_t` channel. No channel-255 off-by-one finding is present.
- Per-channel recursive mutexes protect queue mutation. A popped packet remains owned while its bytes are copied; no iterator/reference into the queue escapes the critical section. That does not by itself couple callbacks to the correct packet, as BASE-API-013 demonstrates in `Networking.cxx.review.MD`.
- Compared the full modern `INetworking.h`, including recommended packet size (not a mandatory hard limit), truncation, peek versus consuming reads, and listener auto-removal rules. Auto-pop is intentional SDK behavior. The output-size parameter has no documented null allowance in the inspected contract.
- Traced both P2P wire wrappers and Server user/lobby routing. Different interface queues are maintained; legacy ServerNetworking and newer GameServer listener registrars require separate integration validation rather than inferring semantics from interface names.
- The SDK scheduling distinction for ordinary/immediate sends is BASE-API-014 beside the implementation. Stub ping/NAT/connection information was identified but no unsupported-service exploit or arbitrary performance claim was inferred.

No independent declaration defect was confirmed. The SystemTests P2P source search identifies polling cases and channel-255 coverage, but that search is not a full test-file review or a passing test result. All version-conditional declarations were read; exhaustive SDK ABI comparison/build validation is incomplete. No builds/tests executed.
