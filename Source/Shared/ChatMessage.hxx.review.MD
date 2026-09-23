# Fresh review — ChatMessage.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read all 51 lines and both feature branches.

## Inspection notes
- Wire sequence is ID, optional type, room, sender, timestamp, contents. Copy/getter ownership is value-based except a borrowed const contents reference.
- The server rebuilds submitted messages using its own sender/room/time rather than trusting these client fields. Timestamp is a fixed 32-bit seconds value, with the expected long-horizon range limitation.

### [BASE-NET-005] Chat message layout changes without a negotiated wire schema
- **Severity:** Medium
- **Confidence:** High
- **Category:** API/ABI
- **Location:** `Source/Shared/ChatMessage.hxx:40-48`.
- **Affected scope:** Differing Windows SDK builds across `HAS_ICHAT_MESSAGETYPE` (introduced at 1.110.0).

**Evidence / failure mechanism:** This feature inserts a ChatMessageType between message ID and room ID. Enclosing SendToChatRoom/RequestChatRoomMessages messages retain class-name-only IDs. Transport handshake has no schema fingerprint, and cereal does not translate changed field positions.

**Reproduction conditions / impact:** Connect compatible-key 1.109.0 and 1.112.2 endpoints and exchange chat payloads; subsequent room/sender/time/string bytes are parsed at the wrong offsets, resulting in rejection or misinterpretation. Matching versions are unaffected. Cross-SDK operation is not assumed to be promised; missing early rejection is the defect.

**Alternatives / recommended resolution:** Reject differing schema fingerprints during handshake, or define a stable wire message type independent of the SDK feature and adapt at API boundaries.

**Verification:** Cross-boundary and same-boundary serialized fixtures; prove either correct round trips or rejection before chat payload decoding. This shared finding is counted once in NET.MD. No test executed.
