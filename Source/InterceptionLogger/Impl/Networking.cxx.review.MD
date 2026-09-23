# Fresh baseline review — Impl/Networking.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–213. Static Windows review; shallow serious-defect scope.

## Checked
- Read packet send/peek/read/availability/pop, NAT and connection-type forwarding and all trace branches.
- Noted that the internal NetworkingListener registration is deliberately disabled; merely observing packets with that listener would change SDK queue consumption. NAT observer registration remains active.
- Compared capacity versus returned-size handling with SDK 1.152.11 INetworking and with the explicitly bounded lobby-message tracing implementation.

## BASE-INTERCEPT-005 — Returned object sizes are used as readable output-buffer extents

- **Severity:** High
- **Confidence:** High for the missing bound and documented truncation path; real DLL behavior was not executed.
- **Category:** Memory Safety
- **Location:** `Source/InterceptionLogger/Impl/Networking.cxx:83–89,115–121`, PeekP2PPacket/ReadP2PPacket.
- **Affected scope:** Packet return tracing across SDK versions; related leaderboard-details path in Stats.cxx.

**Evidence and failure mechanism:** Successful reads hash `*outMsgSize` bytes and optionally hex/string-encode that many bytes from `dest`, without bounding by `destSize`. SDK `1.152.11/galaxy/INetworking.h:160–177,211–221` allows a small destination, truncates data and describes outMsgSize as the message size, not the destination capacity. A larger packet can therefore report a length greater than the bytes available in `dest`. For a 1024-byte message read into a 16-byte destination, the tracing code is permitted by no contract to read 1024 bytes from that destination. The hash already reads the extent with RETURN_VALUES enabled; payload-content tracing is not needed for the invalid read.

**Impact:** Out-of-bounds reads/crashes; content tracing can persist adjacent process memory. This is a logger-introduced failure on a truncation case the API supports, not an accusation that callers supplied an undersized allocation for their declared capacity.

**Possible fixes:** Clamp all output inspection to the minimum of capacity and documented valid written length, or log only lengths/addresses where success/extent is uncertain.

**Recommended resolution:** Establish a checked readable span (`dest != nullptr`, successful call, length at most `destSize`) and use it consistently for hash, hex and encoded output. Preserve the SDK's returned size for callers. Also gate availability output-value inspection on a successful result.

**Verification:** A fake SDK returns success, writes only 16 bytes and reports a 1024-byte packet; put the destination at a guard-page boundary and enable each trace mask separately. Repeat exact-fit, zero capacity, failure and optional size pointer cases under Windows ASan. Confirm actual vendor out-size semantics on representative versions. Proposed only; unique ID shared with the Stats instance.
