# Fresh baseline review — Impl/Friends.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–619. Static Windows review; shallow serious-defect scope.

## Checked
- Read every declaration and alias: AvatarCriteria, RGBA buffer pointer transition, dynamic bool/void rich-presence return and feature-conditioned listener arguments.
- Checked nullable SetRichPresence values, callback-scoped invitation enumeration, borrowed strings and Copy capacities against the implementation.
- Getter, registrar and observer members provide forwarding/observation, not ownership of SDK-returned data.

## Result
No independent serious declaration defect confirmed. This static signature comparison does not certify all SDK vtables or runtime thread safety; common lifetime issues are documented in their implementation reports.
