# Review: `Source/Client_NoVer/CMakeLists.txt`

## Finding — recursive glob has an unrestricted extension set

- **Severity:** Low
- **Evidence:** The target uses `GLOB_RECURSE "*.*"` for all files under
  `Source/Client_NoVer`.
- **Impact:** Documentation, generated artifacts, or review sidecars can be
  added to the compilation unit list and behavior changes when unrelated files
  are created.
- **Suggested fix:** Maintain an explicit source list or restrict the glob to
  C/C++ source and header extensions.
