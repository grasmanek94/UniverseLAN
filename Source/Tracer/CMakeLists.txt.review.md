# Review: `Source/Tracer/CMakeLists.txt`

## Finding — unrestricted glob obscures the tracer target inputs

- **Severity:** Low
- **Evidence:** `GLOB_RECURSE "*.*"` is used for the whole tracer directory.
- **Impact:** Any documentation, sidecar, or generated file can appear in the
  target source set, and adding files does not communicate a deliberate build
  change.
- **Suggested fix:** List tracer sources explicitly or restrict the glob to
  known C/C++ extensions.
