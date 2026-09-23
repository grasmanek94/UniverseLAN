# Fresh baseline review — Impl/Apps.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–103. Static Windows review; shallow serious-defect scope.

## Checked
- Matched IApps inheritance, getter function type, force-DLC flag and owned observer container with the implementation.
- Read all language/code/copy declarations and the mandatory IsDlcOwned listener parameter; compared the modern SDK declaration rather than assuming all listener arguments are optional.
- Feature guards separate language names, language codes and async ownership checks; declarations retain SDK argument order and output capacities.

## Result
No independent serious header defect confirmed. Forced callback scheduling/null handling is an implementation validation item documented in Apps.cxx.review.MD, not proof of an allowed-null crash.
