# Fresh review — SetLobbyJoinableMessage.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read all 48 lines.

## Inspection notes
- joinable/success default true; request and failure constructors preserve supplied state. Server update records this flag, and client discovery filtering consults it.
- Server direct Join currently ignores it. The actual SDK explicitly forbids joining a nonjoinable lobby; NET.MD records that server-owned handoff without claiming the bool schema enforces admission.

### [BASE-NET-005] Joinability updates change schema without changing admission or message ID
- **Severity:** Medium
- **Confidence:** High
- **Category:** API/ABI
- **Location:** `Source/Shared/Networking/Messages/SetLobbyJoinableMessage.hxx:17-31`.
- **Affected scope:** Windows endpoints built on opposite sides of version 11240.

**Evidence / failure mechanism:** Conditional fail_reason adds enum bytes after two bools; older frames end earlier. The same message ID is accepted after a versionless key handshake, so new readers short-read old frames and old readers can ignore new trailing data.

**Reproduction conditions / impact:** Connect 1.124.0/1.125.2 peers with matching key and set joinable. The update/reply may be dropped instead of reporting incompatible wire versions.

**Alternatives / recommended resolution:** Schema fingerprint negotiation/rejection or invariant wire fields translated at the SDK boundary. Supporting arbitrary mixed SDKs is optional; deterministic rejection is sufficient.

**Verification:** Cross-version fixtures both ways and same-version controls; assert bounded parsing and explicit compatibility outcome. Same root ID counted once; no product execution.
