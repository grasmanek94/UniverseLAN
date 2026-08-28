# Review: `z-compile+release.bat`

## Finding — interactive pause masks failures in automation

- **Severity:** Medium
- **Evidence:** The wrapper unconditionally executes `pause` after `call z-compile+release-gh.bat` (lines 4–6).
- **Impact:** Non-interactive CI hangs waiting for input, and the final `pause` can replace the called script's failure status with success.
- **Suggested fix:** Remove the unconditional pause, or make it opt-in and preserve the called command's `%ERRORLEVEL%` with `exit /b`.
