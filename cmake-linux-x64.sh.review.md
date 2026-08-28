# Review: `cmake-linux-x64.sh`

## Findings

- **Medium — execution depends on the caller's working directory.** The script
  never changes to its own directory before removing `cmake-linux-x64/` and
  configuring `..`; invoking it elsewhere can delete/create a same-named
  directory outside the checkout and configure the wrong parent.
- **Medium — command failures are not propagated.** `rm`, `mkdir`, and `cmake`
  are not checked, so a failed cleanup or configuration can still look
  successful to a caller.

## Suggested fix

Resolve the script directory, `cd` there before relative operations, use
strict shell error handling, and pass an explicit build directory/source path.
