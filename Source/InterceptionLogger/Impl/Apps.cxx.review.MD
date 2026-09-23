# Fresh baseline review — Impl/Apps.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–141. Static Windows review; shallow serious-defect scope.

## Checked
- Read DLC installation/ownership override paths, language/code getters and copy-buffer tracing; checked ownership-listener construction and feature guards.
- Compared IsDlcOwned with SDK 1.152.11 IApps: it requires an explicitly supplied listener and documents an asynchronous response. The forced-DLC path calls it synchronously and dereferences it directly; a permitted null-listener contract or concrete unsafe game reentrancy was not established, so neither was promoted to a confirmed crash finding.
- Language copy traces use the capacity-bounded helper. Direct language pointers are formatted without null annotation; SDK null-return behavior remains unverified.

## Result
No independent serious defect confirmed at this depth. Shared listener shutdown/proxy lifetime findings apply through the common infrastructure. Validate forced-DLC callback scheduling and null/error returns before asserting full transparency.
