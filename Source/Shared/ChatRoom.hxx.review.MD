# Fresh review — ChatRoom.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read all 64 lines, including ICHAT and message-type feature branches.

## Inspection notes
- Audited set membership, shared message vector, unread counters, borrowed references and complete serialization order. The class has no internal synchronization; client ChatImpl locks, server uses its event loop.
- Wire graphs can contain null shared messages and arbitrary counters; cereal parsing is not semantic validation. Server-generated normal room snapshots contain non-null messages. Client null-element validation needs API-owner handling.

### [BASE-NET-006] Full chat history is serialized into routine room retrieval
- **Severity:** Medium
- **Confidence:** High
- **Category:** Performance
- **Location:** `Source/Shared/ChatRoom.hxx:23,40-49,57-60`; `ChatRoom.cxx:72-104`.
- **Affected scope:** Windows chat-enabled client/server builds.

**Evidence / failure mechanism:** Message insertion is append-only; room serialization includes the entire vector. `ServerHandlers.cxx:230-233` returns the complete existing room in `RequestChatRoomWithUserMessage`, despite a separate paged-history message. A response whose accumulated history exceeds ENet's 32 MiB packet ceiling is rejected after serialization.

**Reproduction conditions / impact:** Keep a two-person chat alive, accumulate more than 32 MiB through individually size-compliant messages, then request the same room. History retention consumes growing memory and the ordinary room response is not delivered; repeated failure can also trigger BASE-NET-004. This is the same full-snapshot/history root cause as Lobby, counted once.

**Alternatives / recommended resolution:** Return bounded room identity/membership metadata, retrieve history in byte-bounded pages and define a compatible retention/persistence policy. Raising the ENet cap postpones the failure and increases peak allocations.

**Verification:** Windows long-lived chat with bounded messages above/below the aggregate threshold; room retrieval must remain bounded and history pages preserve order, IDs and unread semantics. Proposed tests only.
