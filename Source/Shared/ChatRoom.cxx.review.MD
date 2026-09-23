# Fresh review — ChatRoom.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read all 138 lines.

## Inspection notes
- History slicing uses an exclusive reference, returns empty for unknown reference, and caps subtraction via `min`; empty history and limit zero do not underflow.
- Message creation assigns room ID and wall-clock seconds; server substitutes the authenticated sender before this call. The overload copying a received ChatMessage preserves ID/time; duplicate filtering occurs in one Client callback rather than in the model.
- Checked membership set operations, checked `at` indexing, monotonic longest-message cache and saturating unread subtraction. `AddMessage` itself is not an authorization gate; server verifies membership and non-null input.

### [BASE-NET-006] Append-only chat storage exceeds the full-snapshot transport ceiling
- **Severity:** Medium
- **Confidence:** High
- **Category:** Performance
- **Location:** `Source/Shared/ChatRoom.cxx:72-104`; `ChatRoom.hxx:57-60`.
- **Affected scope:** Long-lived Windows chat sessions and cached room snapshots.

**Evidence / failure mechanism:** Both AddMessage overloads append and never evict/page storage. Every room snapshot serializes all messages, and server existing-room requests send that snapshot. Accumulated payload above 32 MiB cannot pass the actual ENet packet cap even though individual messages fit.

**Reproduction conditions / impact:** Continue a two-member room past that byte total and request the room again: growing memory/copy cost, failed response, and potentially the separate server-send leak. Ordinary short chat remains functional.

**Alternatives / recommended resolution:** Split room metadata from history, byte-bound history pages, and choose documented retention or persistence. Simply limiting the retrieval slice does not fix the whole-room serializer.

**Verification:** Long chat, repeated room retrieval, limited history retrieval and reference-ID boundaries. Verify bounded reply sizes and preserved unread/ordering behavior on Windows. Not run.
