# Fresh baseline review — Impl/Listeners/UtilsListener.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–74. Static Windows review; shallow serious-defect scope.

## Checked
- Read overlay visibility/state, notification ID/length and service-connection callbacks under all feature gates.
- Checked bool/enum/size arguments and final-position proxy forwarding, with no payload access based on notification sizes.
- Traced construction in UtilsImpl: these are normally null-target global tracing observers, while game-registered listeners are passed directly to the SDK registrar.

## Result
No independent serious callback defect confirmed. Observer shutdown ordering remains BASE-INTERCEPT-001; no overlay or service callback was executed.
