# Fresh review — ChatMessage.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read all 71 lines.

## Inspection notes
- Default deserialization state initializes every enabled scalar and string. Copy construction preserves identity; normal construction allocates a new GlobalUniqueID.
- Message-type constructor/copy/getter branches agree with the header's feature guard. Contents are copied from caller storage, avoiding a retained caller-buffer lifetime dependency.
- `GetContents` returns a reference valid with the message's lifetime; network and room containers hold shared ownership while consuming it.

## Result
No additional implementation-local defect established. The feature-dependent wire layout is fully reported in the header (BASE-NET-005). Static Windows review; no builds or execution.
