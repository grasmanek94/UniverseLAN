# `virtual bool PeekP2PPacket(void* dest, uint32_t destSize, uint32_t* outMsgSize, GalaxyID& outGalaxyID, uint8_t channel = 0) = 0;`

## Declaration and applicability

- Header: `INetworking.h`
- Exact declaration/signature:
```cpp
virtual bool PeekP2PPacket(void* dest, uint32_t destSize, uint32_t* outMsgSize, GalaxyID& outGalaxyID, uint8_t channel = 0) = 0;
```
- Observed snapshot availability: 1.57.0, 1.60.0, 1.61.0, 1.64.0, 1.66.0, 1.67.0, 1.68.0, 1.69.0, 1.70.0, 1.72.0, 1.73.0, 1.74.0, 1.75.0, 1.76.0, 1.77.0, 1.80.0, 1.87.0, 1.92.0, 1.95.0, 1.99.0, 1.100.2, 1.104.2, 1.104.3, 1.104.4, 1.106.0, 1.109.0, 1.112.2, 1.113.1, 1.113.3, 1.114.9, 1.121.2, 1.124.0, 1.125.2, 1.126.1, 1.127.0, 1.128.3, 1.130.0, 1.131.3, 1.132.1, 1.133.0, 1.133.6, 1.134.8, 1.134.9, 1.134.10, 1.135.0, 1.138.0, 1.139.2, 1.139.5, 1.139.6, 1.139.9, 1.140.0, 1.142.0, 1.144.1, 1.148.1, 1.148.2, 1.148.3, 1.148.5, 1.148.6, 1.148.7, 1.148.11, 1.148.14, 1.149.0, 1.150.0, 1.151.0, 1.152.1, 1.152.2, 1.152.6, 1.152.9, 1.152.11.
- Relevant build matrix gate: No dedicated feature gate; compile only where this exact declaration is present.
- Existing coverage: Grounded existing coverage: `Source/BehaviourTests/COVERAGE.md` describes scenarios using public `INetworking::PeekP2PPacket`.

## Fact boundary

- Documented fact: the selected public header declares the signature above. Any adjacent header precondition, return description, or callback statement may be asserted verbatim.
- Characterization required: result values, error category, callback delivery/count/order/thread, timing, cross-client visibility, pointer lifetime, and behavior for inputs not explicitly documented. Do not promote these observations to SDK guarantees.

## Expected observations

- Availability, callback-local peek/read, buffer boundary, sender/channel/index relation, and consumption after read/pop are distinct observations when this signature supports them.
- A peek is not treated as consuming, and delivery is never inferred from scheduling alone.

## Public-SDK-only plan

1. Arm the documented listener before sending one bounded opaque public payload, or use the documented polling path without a listener; synchronize sender/receiver with a causal gate.
2. At availability/callback, perform only the read/peek/pop form declared by `PeekP2PPacket`, using documented exact/undersized boundaries. Record success, symbolic sender/channel/message relation, and whether a subsequent availability query changes.
3. Do not mix listener-mode and polling-mode semantics. Destroy listeners, leave/close temporary public state, and shut down within bounded cleanup.

## Result placeholders

- UniverseLAN server + 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized message-read result: `<documented facts and characterization observations>`.
- Official GOG 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized message-read result: `<documented facts and characterization observations>`.
## Verdict and next step

- `[ ] Pass` `[ ] Fail` `[x] Not-run`
- Least-feasible next step: run the smallest valid `PeekP2PPacket` probe in both lanes, then add only the documented boundary or lifecycle observation needed to explain a difference.
