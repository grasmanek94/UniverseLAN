# Review: `Source/TestCases/CMakeLists.txt`

## Finding — test credentials are embedded in build metadata and binaries

- **Severity:** High
- **Evidence:** Lines 27–35 turn usernames, passwords, client IDs, and client
  secrets from `credentials.cmake` into `PUBLIC` compile definitions for every
  test executable.
- **Impact:** Credentials are exposed in compiler command lines, generated
  build files, IDE metadata, and the resulting binaries. A copied test artifact
  can disclose credentials even when the source file is private.
- **Suggested fix:** Load test credentials at runtime from a protected
  environment/secret store and keep them out of target definitions and
  distributable binaries.

## Finding — newly added test cases are not part of the configure dependency

- **Severity:** Low
- **Evidence:** The two `file(GLOB ...)` calls that discover test sources omit
  `CONFIGURE_DEPENDS`, unlike the header glob above.
- **Impact:** Adding or removing a test source after configuration does not
  reliably regenerate the build graph, so a requested test can be silently
  absent until CMake is rerun manually.
- **Suggested fix:** Use explicit source lists or add `CONFIGURE_DEPENDS` and
  prefer target-scoped test registration.

## Finding — test targets copy external files without consistent validation

- **Severity:** Medium
- **Evidence:** The Linux path copies a Galaxy shared library without an
  `EXISTS` check, while the Windows path checks the DLL/peer files. The
  configure-time copy/rename operations are repeated for every generated SDK
  target.
- **Impact:** A missing SDK artifact can fail late during configuration, and
  repeated side effects make partial test trees difficult to diagnose.
- **Suggested fix:** Validate required artifacts before creating each target,
  report the exact missing version/architecture, and use build/install
  commands for per-target copying.
