# Fresh baseline review — Impl/Logger.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–122. Static Windows review; shallow serious-defect scope.

## Checked
- Read log-path construction, directory/open failure paths, destructor flush and all six variadic severity methods.
- The two-pass vsnprintf uses va_copy and va_end correctly for normal formatting. Output writes are serialized under the recursive mutex.
- Checked edge cases: a negative formatting length is unchecked, the pre-lock `if (logfile)` reads stream state outside the writer lock, and the string includes the terminating NUL. Error/concurrent-I/O behavior needs targeted validation; no severe concrete runtime failure was reproduced or established from valid ordinary formatting alone.

## Result
No independent serious finding assigned in this shallow pass. Logger robustness is not certified, and this file is separate from token disclosure in User.cxx's call traces.
