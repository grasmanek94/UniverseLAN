# Fresh review — Stacker.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–45. Static review.

## Inspection notes
- Reviewed fixed-capacity module/function/path fields, vector ownership, virtual callback lifetime and singleton API.
- The callback carries formatted exception strings and frames rather than a Windows exception record/context. This contributes to **BASE-SERVER-009**; adding raw fault code/address and preserving CONTEXT would distinguish SEH faults from C++ exceptions.
- Callback publication is atomic in the implementation, but ownership remains caller-managed. The actual Trace callback is static-lifetime; no short-lived registered callback use was established.
- Fixed strings can throw on oversized input, but throwing inside the callback does not by itself establish recursive UEF entry or the hypothesized self-wait. See the explicit reachability assessment in `Stacker.cxx.review.MD`.

## Result
No independently counted declaration defect. Global dump settings are initialized during tracing setup; unsupported concurrent reconfiguration was not presumed.
