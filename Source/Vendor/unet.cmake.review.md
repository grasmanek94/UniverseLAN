# Review: `Source/Vendor/unet.cmake`

## Finding — directory paths are passed as library sources

- **Severity:** High when tests are enabled
- **Evidence:** `add_library(unet-lib-${GALAXY_VERSION} ...)` passes
  `src/Results`, `src/Services`, and `src/System` alongside source files,
  then separately adds selected files from those directories.
- **Impact:** Enabling `BUILD_TEST_CASES` can make CMake treat directories as
  source files and fail configuration or produce generator-dependent target
  inputs. The test build is therefore not reliable across generators.
- **Suggested fix:** Remove the directory entries and list the intended
  `.cpp` files explicitly (including the platform-specific file selected
  below).
