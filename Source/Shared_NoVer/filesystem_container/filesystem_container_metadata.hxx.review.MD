# Fresh baseline review: filesystem_container_metadata.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Entire file read independently (86 lines). Static review only.

## Checked
- Cereal field ordering (`share_id`, user, system), map/string archive dependencies, mutex-protected map serialization, mutable/const callback types, assignment and snapshot declarations.
- Mutexes prohibit implicit copying; explicit assignment is implemented with two-object locking. Returned get_all/get_vector containers are owning values.
- Callback templates can technically return references that escape locks, but traced metadata consumers use value APIs; no unsupported caller lifetime is promoted into a defect.
- Outer share_id and user/system maps are not a single locked snapshot. Individual serialization locks protect map structure, not atomic file-plus-metadata commits or share-ID registration.

## Result and limits
No additional confirmed finding in this header. The portable archive has no explicit format version/checksum or size policy here; corrupt/untrusted metadata recovery is an entry/parser-boundary limitation rather than proof of a new exploit.
