# `INetworking.h` Header Coverage

## Selected SDK

This matrix covers `Source/DLLs/1.152.11/galaxy/INetworking.h`.

| Declaration group | Practical coverage | Boundary |
| --- | --- | --- |
| Send, availability, peek, read, packet callback/listener | Existing controlled P2P coverage | Current public-lobby peer, bounded opaque payload, fixed non-default channel only. Listener delivery has an unresolved official runtime prerequisite. |
| Reliable/unreliable non-immediate send and self direct connection type | Existing coverage | Do not infer immediate-send, peer proxy/none, or arbitrary channel behavior. |
| `PopP2PPacket` | Pending controlled extension | Extend listener-free known-peer/channel topology only. |
| Ping and arbitrary peer/channel/payload forms | Fixture-blocked | Never manufacture peer IDs, payloads, or topology. |
| NAT query/detection/listeners | NAT-fixture-blocked | No deterministic public NAT fixture exists. |
| Game-server networking/listener aliases | Header-gated characterization | Existing sender-identity scenario requires selected `InitLocal`/server-networking headers and artifacts; it does not establish listener or NAT behavior. |
| Destructor | Lifecycle-only | Accessor-owned; direct destruction is invalid. |

## Safety Rules

- Never retain peer IDs, payloads, channel values, pings, NAT values, credentials, timestamps, or runtime artifacts.
- Use only scenario-owned lobby peers and bounded opaque payloads for P2P operations.
- Historical server-listener plans absent from the selected header are excluded.
