# Fresh review — SetLobbyMaxMembersMessage.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read all 46 lines.

## Inspection notes
- Capacity uses uint32; success defaults true and error constructor sets false. Server authorizes owner but does not validate capacity range or restore the authoritative field on rejected updates.
- Those admission/rollback issues live in the handler/model callers, not integer serialization itself.

### [BASE-NET-005] Capacity updates have incompatible optional trailing reason bytes
- **Severity:** Medium
- **Confidence:** High
- **Category:** API/ABI
- **Location:** `Source/Shared/Networking/Messages/SetLobbyMaxMembersMessage.hxx:17-31`.
- **Affected scope:** Mixed Windows SDK endpoints across 1.124.0/1.125.2.

**Evidence / failure mechanism:** `fail_reason` is emitted only above version 11240. Class-name ID and handshake do not encode that distinction; newer readers require bytes older writers never send, and older readers accept trailing bytes without a compatibility decision.

**Reproduction conditions / impact:** Authenticate differing schema builds and update maximum members. Decode rejection can silently lose the operation or callback although both peers were accepted.

**Alternatives / recommended resolution:** Reject incompatible schema groups during handshake, or use invariant wire reason fields with version-specific SDK translation.

**Verification:** Both directions across the boundary, matching builds, and explicit error reporting before the update reaches state. Counted under the single BASE-NET-005 index entry; not executed.
