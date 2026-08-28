# Review: `Source/Version/CMakeLists.txt`

## Finding — version generation makes builds depend on a writable Git checkout

- **Severity:** Medium
- **Evidence:** The `custom_version_updater` target always runs `Util/UpdateVersion.*` before building the version library (lines 15–20); those scripts call `git rev-list HEAD --count` and write/delete `Source/Version/auto_version.h`.
- **Impact:** Source archives, read-only checkouts, and builds without Git metadata cannot reliably configure/build. The build also mutates a tracked source file's timestamp and derives the ABI-visible build number from repository history.
- **Suggested fix:** Generate the header in the build tree with a declared output, pass an explicit version/commit value from CI, and fail clearly when it is unavailable instead of mutating the source tree.
