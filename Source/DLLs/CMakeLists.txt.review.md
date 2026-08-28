# Review: `Source/DLLs/CMakeLists.txt`

## Finding — configure regenerates version resources inside the source tree

- **Severity:** Medium
- **Evidence:** `prep_version_rc()` writes each configured
  `*_versioninfo.rc` below `Source/DLLs/<version>/<arch>` with
  `configure_file()`.
- **Impact:** Configuration mutates source-controlled/generated inputs, makes
  parallel or repeated configurations depend on checkout writability, and can
  leave changed files that interfere with packaging's clean-tree check.
- **Suggested fix:** Generate resources in the build tree, declare them as
  target outputs, and use the build-tree path in `target_sources()`.

## Finding — version discovery is implicit and not semantically ordered

- **Severity:** Low
- **Evidence:** `SUBDIRLIST()` uses a filesystem glob and passes every
  directory containing an architecture `CMakeLists.txt` to `add_subdirectory`.
- **Impact:** A stray directory can create an unexpected SDK target, while
  lexical filesystem order is not Galaxy semantic version order. The generated
  family set is difficult to audit from the configure input.
- **Suggested fix:** Keep an explicit version manifest (or sort/validate the
  discovered names as semantic versions) and fail on malformed entries.
