# Review: `Source/Vendor/Enet++/CMakeLists.txt`

## Findings

- **Medium — the target silently relies on root-level C++ settings.** This
  target includes `<format>` and therefore requires C++20, but this
  `CMakeLists.txt` does not set or validate a C++ standard. If the wrapper is
  configured as a standalone subdirectory or the parent changes its global
  standard, configuration can succeed and compilation can fail. Prefer a
  target-scoped `CXX_STANDARD`/`CXX_STANDARD_REQUIRED` requirement.
- **Low — recursive source globbing hides the build input.** `file(GLOB_RECURSE
  ENET_SRC CONFIGURE_DEPENDS "src/*.*")` will include any future file placed
  under `src`, including files that are not compilable sources, and makes code
  review/build intent less explicit. List the wrapper sources explicitly or
  filter by the intended extensions.
- **Low — no target-level warning or portability policy is defined.** The
  target only suppresses Windows deprecation warnings and inherits most
  compiler/linker behavior from its parent. If this wrapper remains a supported
  library boundary, set its required language features and relevant warning/
  visibility properties on the target rather than relying on global settings.

The underlying `Source/Vendor/Enet-IPv6/` implementation is excluded by
`.github/copilot-instructions.md`; this review covers only the custom Enet++
wrapper and its helper bridge.
