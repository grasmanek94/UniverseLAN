# Review: `Source/Client/CMakeLists.txt`

## Finding — recursive glob includes non-source review artifacts

- **Severity:** Low
- **Evidence:** `file(GLOB_RECURSE ... "Source/Client/*.*")` collects every
  extension below the directory. This review now places Markdown sidecars under
  the same tree.
- **Impact:** Review documents and future unrelated files become target source
  entries. Most generators merely display them, but source classification and
  IDE projects become less predictable.
- **Suggested fix:** List implementation/header files explicitly or filter the
  glob to supported source extensions.
