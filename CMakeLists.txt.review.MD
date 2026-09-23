# Fresh baseline review: CMakeLists.txt

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. All 103 lines reviewed.

## Inspection notes
- Traced C++20 requirements, MSVC x86/x64 selection, default-disabled test options, BUILD_ALL_TESTS cache forcing and enable_testing conditions.
- Checked comma-separated LIMIT_VERSIONS conversion and downstream selection. Empty input deliberately selects all supported directories; unknown requested versions produce no matching targets rather than a fatal diagnostic. Stricter input validation is an improvement, not a demonstrated production defect in valid invocations.
- Experimental unity mode is opt-in and documented as requiring adjustment; the interceptor handles exclusions downstream. No claim that experimental unity is validated.
- ROOT/bin output is the user's explicitly intended deployment convention. It is not reported as an accidental defect. Separate build directories share that output location: do not concurrently build the same architecture/version/configuration into it.
- Inspected non-MSVC branches statically; no Linux build. MinGW is explicitly unsupported downstream. x86 and Release were not executed in this review.

## Findings and validation
No independent confirmed defect assigned. Windows MSVC x64 Debug configure and client/server/interceptor builds succeeded for 1.57.0, 1.124.0, 1.139.2, 1.148.3 and 1.152.11. Exact commands and limits are in `.ai/review-baseline/VERIFICATION.MD`. This does not establish behavior or all-version ABI compatibility.
