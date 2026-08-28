# Review: `cmake-linux-x86.sh`

## Findings

- **Medium — execution depends on the caller's working directory.** The script
  never changes to its own directory before removing `cmake-linux-x86/` and
  configuring `..`; invoking it elsewhere can affect the wrong directory.
- **Medium — command failures are not propagated.** `rm`, `mkdir`, and `cmake`
  are not checked, so an unsuccessful configuration can be mistaken for a
  completed setup.

## Suggested fix

Resolve the script directory, `cd` there before relative operations, use
strict shell error handling, and pass an explicit build directory/source path.
