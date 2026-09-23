# Fresh baseline review: filesystem_container_entry.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Entire file read independently (89 lines). Static review only.

## Checked
- Followed enable_shared_from_this ownership, raw parent association, immutable path accessors, mutable metadata/share ID/cache index, returned owning fstreams, both read/write forms and deprecated raw-path copy forms.
- All production constructions found go through make_shared in the parent. Public stack construction followed by unlink would violate shared_from_this ownership, but no such production caller was found.
- SharedFileUtils retains root containers; parents retain cloud subcontainers; CloudStorage's deferred GetFile captures a shared subcontainer; InterfaceInstances reset retains sfu and destroys cloud/storage users. These callers do not establish a reachable dangling-parent defect.
- Cache-index mutation is performed under parent index locking in production; tests manually setting an index do not demonstrate a production race. Entry I/O and share_id as a whole are not independently synchronized.
- Implemented failure/clock/read findings BASE-UTIL-006–010 and publication finding BASE-UTIL-005 apply to these interfaces; see their complete sections in implementation sidecars.

## Result and limits
No additional independent header finding. Entry lifetime, parent lifetime and file-content stability are distinct contracts; shared_ptr alone only addresses the first. Valid public raw-path copy operations remain deprecated and unconstrained by a sandbox by design.
