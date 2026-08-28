# Review: `Source/Shared/CMakeLists.txt`

## Finding — recursive glob includes every file below the component

- **Severity:** Low
- **Evidence:** `GLOB_RECURSE` uses `Source/Shared/*.*` without an extension
  filter.
- **Impact:** Markdown review sidecars and future non-C++ files are registered
  as target sources, making IDE/build inputs implicit and generator-dependent.
- **Suggested fix:** List the shared implementation files explicitly or filter
  the glob to the supported C/C++ extensions.
