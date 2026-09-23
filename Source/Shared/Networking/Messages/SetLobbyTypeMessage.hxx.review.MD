# Fresh review — SetLobbyTypeMessage.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read all 48 lines.

## Inspection notes
- Default lobby type is public, success true; request/error constructors initialize enabled fields. Server requires owner/member through its update helper.
- Invalid type enum and rollback behavior are handler policy; the passive DTO does not establish authorization.

### [BASE-NET-005] Optional trailing failure reason is not schema-negotiated
- **Severity:** Medium
- **Confidence:** High
- **Category:** API/ABI
- **Location:** `Source/Shared/Networking/Messages/SetLobbyTypeMessage.hxx:17-31`.
- **Affected scope:** Windows SDK pairs spanning GALAXY_VERSION 11240.

**Evidence / failure mechanism:** Newer serializers append fail_reason; older serializers omit it. Same class-name hash and versionless acceptance admit either. New readers short-read an older frame, while older readers do not reject a newer frame's extra bytes.

**Reproduction conditions / impact:** Connect 1.124.0 with 1.125.2 and set lobby type. A request/reply may disappear after successful admission instead of delivering an explicit incompatible-version result.

**Alternatives / recommended resolution:** Negotiate a schema fingerprint and reject mismatches; alternatively keep a stable fixed-width reason field across SDK adapters.

**Verification:** Both serializer directions and matched controls; assert early rejection or supported translation. This is the same BASE-NET-005 root cause, not an extra finding count. No tests run.
