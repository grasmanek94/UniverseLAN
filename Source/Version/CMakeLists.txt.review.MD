# Fresh review — Version/CMakeLists.txt

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–20. Static Windows-focused review.

## Inspection notes
- Traced the static version library, public include path, compiler-selected updater suffix and explicit dependency ordering before compilation.
- Read `Util/UpdateVersion.bat` and `.sh` only as generation context (excluded from first-party finding ownership). The Windows script obtains git commit count, falls back to an environment override or zero, compares a temporary header, and updates auto_version.h/touches Version.cxx only when content differs.
- Generated-header creation therefore precedes compiling Version.cxx on the normal MSVC build path. The custom target intentionally runs each build but need not rewrite unchanged content.
- Generation writes into the source tree, and independent build trees share header/temp filenames. Parallel cross-tree generation and read-only-source builds remain documented architecture limits, not reproduced races in this review.
- Compiler-based `.bat` versus `.sh` selection assumes the documented MSVC Windows path; alternative Windows toolchains were not executed.

## Result
No confirmed independent defect in the owned manifest. No updater/build was run, so neither generated files nor source timestamps were changed by review execution.

## Follow-up addendum — 2026-09-24

All three owned Version inputs re-read completely. Root CMake selects C++20; `Source/CMakeLists.txt:8` creates this static target before Shared, and `Source/Shared/CMakeLists.txt:19–29` carries its dependency to the versioned server. `custom_version_updater` orders generation before compilation on the documented MSVC path. `Version.hxx` supplies external linkage for the namespace-scope const definition; no runtime initialization/lifetime issue was found.

Both updater scripts were read only as context. The Windows script compares before replacing/touching and has a git-count/environment/zero fallback. Concurrent independent build trees still share source-tree output/temp names; no concurrent build or unsupported compiler path was executed. These remain BUILD handoff limits, not a new SERVER finding. The generated `.h` files lie outside the exact `.cxx/.hxx/.cmake/.txt` assignment and were not needed to verify the target wiring. No updater, build or Git write was performed.
