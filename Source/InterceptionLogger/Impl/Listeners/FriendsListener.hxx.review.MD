# Fresh baseline review — Impl/Listeners/FriendsListener.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–183. Static Windows review; shallow serious-defect scope.

## Checked
- Read every SDK-derived class and feature gate, including sent/received invitations, later user-info/rich-presence retrieval and FindUser.
- Matched macro class/target types and method signatures with implementation; checked bool acceptance, timestamps, IDs and borrowed strings.
- The header adds no owned callback payload storage and uses separate listener subobjects per SDK interface.

## Result
No independent serious declaration defect confirmed. Common proxy ownership is documented separately; absence of a local mismatch is not an ABI certification.
