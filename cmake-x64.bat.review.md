# Review: `cmake-x64.bat`

## Findings

- **Medium — cleanup/configuration failures are ignored.** `rd`, `mkdir`, and
  `cmake` are run without `if errorlevel` checks, so a failed configure can
  look successful to the caller.
- **Medium — the script is interactive by default.** `pause` blocks CI and
  automation after configuration.

## Suggested fix

Check and propagate each command's exit status, use an explicit source/build
directory, and make the pause opt-in.
