# Fresh review — SetLobbyMemberDataMessage.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read all 52 lines and conditional constructors.

## Inspection notes
- Serializes request, lobby, member, success, conditional failure reason, key/value. Server replaces member_id with authenticated peer ID, and Lobby::SetMemberData rejects nonmembers.
- Constructors initialize every enabled field; empty values are deliberate clear operations, not evidence of missing string initialization.

### [BASE-NET-005] SDK-dependent reason field changes member-data wire offsets
- **Severity:** Medium
- **Confidence:** High
- **Category:** API/ABI
- **Location:** `Source/Shared/Networking/Messages/SetLobbyMemberDataMessage.hxx:17-34`.
- **Affected scope:** Mixed Windows SDK schemas across GALAXY_VERSION 11240.

**Evidence / failure mechanism:** An enum is inserted before key/value only in newer builds, while the message ID and authentication handshake remain unchanged. Portable binary cannot infer the omitted field. Older/newer readers disagree on string size-tag offsets.

**Reproduction conditions / impact:** Authenticate 1.124.0 and 1.125.2 endpoints to each other and update member data; decode can fail or misread lengths instead of refusing the incompatible peer. Normal matching builds do not trigger this.

**Alternatives / recommended resolution:** Early schema-fingerprint rejection, or fixed wire fields with SDK adaptation. Do not rely on trailing-byte acceptance or exceptions for compatibility negotiation.

**Verification:** Bidirectional cross-boundary fixtures with nonempty key/value plus same-schema controls; reject before dynamic decoding when incompatible. Shared finding counted once; no execution.
