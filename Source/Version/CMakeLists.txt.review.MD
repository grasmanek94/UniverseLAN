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
