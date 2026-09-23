# Fresh baseline review — Impl/Utils.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–175. Static Windows review; shallow serious-defect scope.

## Checked
- Read RGBA pointer-type and NotificationID compatibility aliases, dimension references and notification output-capacity contracts.
- Matched consumable-output, notification, overlay and connection-state feature guards to Utils.cxx.
- Checked caller-owned buffer roles and the documented byte-count return for notification content, which should guide output tracing rather than capacity alone.

## Result
No independent serious declaration defect confirmed. Partial-output logging and common observer ownership remain implementation-level validation items/findings; no ABI build matrix was run.
