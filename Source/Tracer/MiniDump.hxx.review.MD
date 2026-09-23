# Fresh review — MiniDump.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–5. Static review.

## Inspection notes
- The only exposed operation takes filename and verbosity and returns void. There is no argument for the original fault's exception pointers/thread ID and no success result.
- The active caller is Stacker's crash callback. This signature cannot preserve original exception context without an API extension: **BASE-SERVER-009** in `Stacker.cxx.review.MD`.
- Keeping an explicit snapshot overload for non-crash callers is compatible with adding a Windows crash-context overload.

## Result
No separately counted header finding; the cross-file context-loss defect is indexed once.
