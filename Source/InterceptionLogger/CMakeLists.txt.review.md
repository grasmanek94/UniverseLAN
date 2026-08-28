# Review: `Source/InterceptionLogger/CMakeLists.txt`

## Finding — recursive glob includes the component's review sidecar

- **Severity:** Low
- **Evidence:** `GLOB_RECURSE` covers `Source/InterceptionLogger/*.*`, which
  includes `InterceptionLogger.review.md` and this sidecar.
- **Impact:** Non-code review documents are added to each generated static
  target's source list and can clutter IDE projects or interact poorly with
  generators that classify unknown extensions.
- **Suggested fix:** Use explicit C/C++ source lists or filter the glob by
  extension.
