# Fresh review — Messages.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read all 79 lines.

## Inspection notes
- Reconciled every included message with the dispatch macro and both handler-declaration expansions. Chat's three messages share the ICHAT feature gate; connect/disconnect are local events, not wire switch cases.
- The same macro accepts request and response classes on both endpoints. Server-only/client-only handling and authentication occur after decoding, which is why direction/state filtering must move ahead of payload parsing for BASE-NET-001.
- Class IDs are compile-time class-name hashes, not schema fingerprints. The list is not evidence of version compatibility; BASE-NET-005 belongs to transport/schema negotiation.

## Result
No missing registered message or independent macro-list defect established. All included schemas were read individually; this umbrella file was not used as a substitute for their coverage.
