# Review: `z-compile+release-gh.bat`

## Finding — configure/build errors are ignored

- **Severity:** High
- **Evidence:** Lines 23–27 run two configure and two build commands without checking `ERRORLEVEL`; packaging is invoked unconditionally at line 29.
- **Impact:** A failed architecture build can be silently replaced by a partial one-architecture archive, and the workflow may succeed despite failed compilation.
- **Suggested fix:** Check `if errorlevel 1 exit /b 1` after every configure/build step and propagate the packaging script's exit code.
