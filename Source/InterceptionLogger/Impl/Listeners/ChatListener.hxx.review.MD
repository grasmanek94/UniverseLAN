# Fresh baseline review — Impl/Listeners/ChatListener.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–51. Static Windows review; shallow serious-defect scope.

## Checked
- Read the four listener classes, SDK inheritance and encapsulation target types.
- Matched send callback message index/ID/time and receive/history count/longest-length signatures to implementation, including the history-listener feature gate.
- No callback payload pointers are retained by these declarations; only the borrowed game listener target is stored by the shared macro.

## Result
No independent serious header defect confirmed. Borrowed-target/proxy lifetime is limited by the shared implementation reports and not proven safe by these declarations.
