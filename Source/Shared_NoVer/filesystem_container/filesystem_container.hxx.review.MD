# Fresh baseline review: filesystem_container.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Entire file read independently (90 lines). Static review only.

## Checked
- Mapped all three entry registries, their recursive mutexes, subcontainer ownership, friend callbacks, private path helpers and public name/ID/index APIs to implementation.
- Entry and subcontainer handles are shared_ptrs; the raw reverse parent pointer is in the entry class. A copied file-list vector owns entries but not their parent; traced SharedFileUtils/CloudStorage ownership retains parents during permitted use.
- The virtual destructor supports extension; mutex members naturally prevent accidental container copies. Counts and index reads are individually locked, not an atomic multi-call snapshot.
- Path identity, publication/error handling, subcontainer aliasing, duplicate startup entries, and space-error reports are detailed in implementation findings BASE-UTIL-004/005/011/012/016. No additional declaration-only defect is asserted.

## Result and limits
No additional independent finding. Public return types do not express creation/space-query errors or a stable content/stat snapshot; recommendations are attached to the concrete implementation failures. No post-parent-lifetime operation is treated as a proven reachable use-after-free.
