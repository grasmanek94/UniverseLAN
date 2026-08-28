# Review: `Source/Shared_NoVer/CMakeLists.txt`

## Finding — recursive glob has an unrestricted extension set

- **Severity:** Low
- **Evidence:** The target collects `Source/Shared_NoVer/*.*` recursively.
- **Impact:** Non-source artifacts become part of the target's source metadata
  and new files can change the build without an intentional target edit.
- **Suggested fix:** Use an explicit source list or a CMake glob filtered to
  C/C++ extensions.
