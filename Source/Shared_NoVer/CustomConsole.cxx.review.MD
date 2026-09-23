# Fresh baseline review: CustomConsole.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Entire file read independently (73 lines). Static Windows review only.

## Checked
- AllocConsole/GetConsoleWindow/GetWindowLongPtrA, stdin/stderr/stdout reopening, C++ stream error-state clearing, once-enabled flag, and version title formatting.
- No subclass procedure is installed: the saved WNDPROC/HWND do not imply ownership or require restoration/CloseHandle. Standard FILE streams remain CRT-owned after freopen_s.
- AllocConsole/freopen_s failures are ignored and the flag is set before success; an existing console can still be rebound. The normal caller is startup configuration, so retry/concurrent enable semantics were not assumed to establish a current failure.
- Windows calls are guarded; no non-Windows runtime findings. Console ownership is process-wide with no FreeConsole shutdown policy.

## Result and limits
No confirmed independent defect with sufficient caller evidence. Console failures and concurrent host logging are untested operational limits; startup/teardown behavior should be specified before adding restoration logic.
