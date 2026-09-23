# Fresh baseline review — Impl/Listeners/UtilsListener.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–55. Static Windows review; shallow serious-defect scope.

## Checked
- Read legacy NotificationID alias, overlay listener classes, notification and service-state declarations and their feature guards.
- Matched SDK-derived base/target types and callback signatures to UtilsListener.cxx.
- Notification lengths are metadata only in this class; no local content buffer or retained borrowed event payload is introduced.

## Result
No independent serious declaration defect confirmed. Shared proxy and observer ownership constraints are documented in their owning reports; no compiled ABI verification was run.
