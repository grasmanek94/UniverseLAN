# Fresh review — Stacker.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–45. Static review.

## Inspection notes
- Reviewed fixed-capacity module/function/path fields, vector ownership, virtual callback lifetime and singleton API.
- The callback carries formatted exception strings and frames rather than a Windows exception record/context. This contributes to **BASE-SERVER-009**; adding raw fault code/address and preserving CONTEXT would distinguish SEH faults from C++ exceptions.
- Callback publication is atomic in the implementation, but ownership remains caller-managed. The actual Trace callback is static-lifetime; no short-lived registered callback use was established.
- Fixed strings can throw on oversized input, but throwing inside the callback does not by itself establish recursive UEF entry or the hypothesized self-wait. See the explicit reachability assessment in `Stacker.cxx.review.MD`.

## Result
No independently counted declaration defect. Global dump settings are initialized during tracing setup; unsupported concurrent reconfiguration was not presumed.

## Follow-up addendum — 2026-09-24

Re-read all 45 lines and traced the actual source-filename producer and Boost constructor. The previously noted fixed-string exception now has a complete producer-to-report-abort mechanism: **ADD-SERVER-003**, fully recorded in `Stacker.cxx.review.MD`. A dependency field can contain 1023 characters while `CallEntryFile.path` accepts 260; reporting/dumping follows the unguarded conversion. This adds no recursive-UEF or native callback-lifetime claim. One finding is counted at the implementation, not again here.
