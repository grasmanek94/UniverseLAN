# Fresh review — ConnectionAcceptedMessage.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read all 15 lines.

## Inspection notes
- Empty payload is intentional; class ID is the signal. Server sends it after challenge validation and identity mapping; client sends hello and marks authenticated on receipt.
- No protocol version, server proof or negotiated capabilities are carried. Trusted configured-server/LAN assumptions must be explicit; the public default key alone is not a vulnerability finding.
- Empty-class elision in cereal is compatible with this payload; transport still contains endian marker and class ID.

## Result
No independent schema-local defect. Missing compatibility negotiation is fully defined at the transport boundary as BASE-NET-005.
