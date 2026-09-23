# Fresh review — MiniDump.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–161. Static Windows-focused review.

## Inspection notes
- Followed synthesized EXCEPTION_RECORD/CONTEXT allocation, dbghelp dynamic load/export lookup, CreateFile, dump-verbosity flags, MiniDumpWriteDump and cleanup paths.
- At lines 19–40 and 48–50, the dump uses code zero, `_ReturnAddress()` and `RtlCaptureContext` inside the dumper rather than the UEF's original ExceptionInfo. The complete finding is **BASE-SERVER-009** in `Stacker.cxx.review.MD`; the misleading exception stream is confirmed even if useful process memory is still captured.
- Error branches after allocation/load/file-open do not consistently free allocations, DLL references or handles; even success leaves the three exception allocations. In the established fatal-process path, process exit reclaims them. Repeated nonfatal snapshots are not an established production caller, so this is a bounded cleanup observation rather than a separately elevated leak finding. Stack-owned context and RAII handles are appropriate in the context-preservation fix.
- `CreateMiniDump` does not report failure to its caller; the file may be absent or partial. Failure telemetry and wide-path Windows APIs would improve diagnostics. No dump was created or inspected in this review.

## Result
One shared finding, **BASE-SERVER-009**. No recursive exception-filter behavior is inferred from allocation failure in this function.
