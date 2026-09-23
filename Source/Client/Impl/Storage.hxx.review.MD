# Fresh baseline review: Storage.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Entire file read, lines 1–274. Windows static inspection; no build or runtime tests.

## File-specific inspection

- Reviewed the worker record, container/mutex ownership, all public synchronous and asynchronous declarations, conditional listener arguments, filename/index methods, shared owner/size/read/close contracts, and response-handler signatures.
- `Worker` combines a joining thread with a shared atomic completion flag. The lambda retains its own completion-flag ownership, so member destruction order alone does not establish a dangling completion flag. The implementation's worker list is private and updated under its mutex.
- The worker design does not describe a cancellable operation record; BASE-STORAGE-013 explains the actual asynchronous registration race. The resolution belongs in admission/dispatch control flow, not in a superficial raw-pointer-to-smart-pointer substitution for caller-owned listeners.
- `InterfaceInstances`, registrar, and Shared file utilities are non-owning dependencies. Explicit reset order was inspected; implicit global member-destruction order requires the CORE teardown assessment.
- Filename preconditions require portable UTF-8 relative paths and forward slashes. Shared path sanitization/encoding must maintain this external contract; Windows case folding, code-page conversion, long paths, and file-clock conversion are dependency validation topics rather than independently tested guarantees.
- `GetSharedFileOwner` promises file ownership, not current-user identity (BASE-STORAGE-014). No nonempty restriction appears on file write or download (BASE-STORAGE-015). The asynchronous share completion contract applies to read/worker failure too (BASE-STORAGE-016).
- Offset defaults, output buffer lengths, zero-based enumeration bounds, and the close/re-download requirement were compared with the SDK and implementation. No header-level argument order mismatch was identified in the inspected branches.

## Findings disposition

No extra declaration-only defect counted. Full file-specific failure sections are BASE-STORAGE-013 through BASE-STORAGE-016 in `Storage.cxx.review.MD`. This does not certify implementation correctness or ABI compatibility across all version targets. Recommended validation includes deterministic worker cancellation, two-user ownership, empty files, Windows denied-sharing I/O, and normal plus automatic teardown paths.
