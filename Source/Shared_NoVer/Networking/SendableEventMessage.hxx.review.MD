# Fresh baseline review: Networking/SendableEventMessage.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Entire file read independently (32 lines). Static review only.

## Checked
- Archive/type-support includes and macro expansion produce a constexpr per-class identifier; class names are stringized and their length is used as the FNV initial seed.
- The 32-bit hash result is intentionally widened to uint64_t. Both sender and receiver use the same value, and receiver switch cases would diagnose duplicate IDs among registered message types at compile time.
- Traced UserHelloData/RequestSpecificUserData archive flow and Networking's class-ID prefix; there is no ownership or handle resource in this header.

## Result and limits
No confirmed current wire-ID defect. IDs are not cryptographic and changing hash/seed/type names would change protocol compatibility. The broad Cereal include surface is compile-time coupling, not measured performance evidence.
