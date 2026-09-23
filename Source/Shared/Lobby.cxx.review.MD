# Fresh review — Lobby.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read all 300 lines; static Windows review.

## Inspection notes
- Constructors initialize all fields, register the owner as a member, and preserve IDs/message state when copying. `ChooseNewOwner` selects but does not assign; the server explicitly follows it with `SetOwner`.
- Checked empty/boundary member indexing through ContainerGetByIndex, null-key/value behavior, borrowed C strings and binary message copy. Missing members return neutral results; mutation is caller-synchronized.
- `AddMember` does not enforce capacity or joinability. Server Join checks fullness but comments out joinability; that server-owned contract defect is documented in NET.MD for handoff, rather than falsely attributing access control to a client snapshot model.
- Delete methods set an empty string. The SDK explicitly equates deletion with setting empty; no erased-key/count guarantee was established, so no deletion finding is asserted.
- Message IDs start at one; wrap/collision is a long-duration boundary to validate, not a separately inflated finding.

### [BASE-NET-006] Retained messages eventually make lobby snapshots unsendable
- **Severity:** Medium
- **Confidence:** High
- **Category:** Performance
- **Location:** `Source/Shared/Lobby.cxx:232-250`, `SendMsg`/`AddMsg`; `Lobby.hxx:54-60`.
- **Affected scope:** Long-lived Windows lobbies, join/data/list replies and client caches.

**Evidence / failure mechanism:** Both insertion paths retain messages indefinitely. The model's serializer includes all messages, and server list/join/data handlers send that model directly. With 1,024 messages of 32,768 bytes, payload alone reaches ENet's 32 MiB limit; per-message/container framing pushes replies over it although each submitted message fits.

**Impact / reproduction conditions:** An active lobby with enough accumulated traffic becomes unlistable/unjoinable through successful responses; memory and copying grow until the lobby is removed. A failed oversized Send also leaks via BASE-NET-004. This is accumulated valid traffic, not malformed-frame allocation.

**Alternatives / recommended resolution:** Keep history out of routine snapshots; provide bounded pages and an explicit retention policy or persistent history preserving SDK retrieval promises. A packet-size precheck alone prevents a leak but cannot restore discoverability.

**Verification:** Accumulate above/below the 32 MiB threshold, then list, join, fetch data and retrieve old message IDs. Verify bounded snapshots and defined history retrieval. No runtime reproduction performed.
