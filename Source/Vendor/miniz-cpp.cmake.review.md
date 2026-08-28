# Review: `Source/Vendor/miniz-cpp.cmake`

## Finding — include path is applied to the wrong target

- **Severity:** Medium
- **Evidence:** The file creates `universelan-miniz-cpp` but calls
  `target_include_directories(universelan-simpleini ...)`.
- **Impact:** Consumers of the miniz target do not receive its include path,
  while an unrelated target is modified. The miniz wrapper is also not linked
  by any current project target, so this integration can silently remain
  unused until a consumer is added.
- **Suggested fix:** Attach the include directory to
  `universelan-miniz-cpp`, link that target from the component that uses miniz,
  and add a configure/build check for the public header.
