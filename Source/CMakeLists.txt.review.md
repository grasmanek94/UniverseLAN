# Review: `Source/CMakeLists.txt`

## Finding — excluded EnetTest code is still wired into the test build

- **Severity:** Low
- **Evidence:** `add_subdirectory(EnetTest)` is enabled whenever
  `BUILD_TEST_CASES` is set, although `.github/copilot-instructions.md`
  explicitly excludes `Source/EnetTest/**` from the baseline review.
- **Impact:** A normal test build pulls an excluded, separately maintained
  project into the build and can fail for reasons outside the reviewed scope.
- **Suggested fix:** Make EnetTest an explicit, separately documented option
  or keep it outside the default `BUILD_TEST_CASES` path.

The remaining subdirectories are thin target-registration layers; their
component-specific source-glob and target-policy notes are recorded in their
adjacent `CMakeLists.txt.review.md` files.
