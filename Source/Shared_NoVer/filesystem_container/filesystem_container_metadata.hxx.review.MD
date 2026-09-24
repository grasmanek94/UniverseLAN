# Fresh baseline review: filesystem_container_metadata.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Entire file read independently (86 lines). Static review only.

## Checked
- Cereal field ordering (`share_id`, user, system), map/string archive dependencies, mutex-protected map serialization, mutable/const callback types, assignment and snapshot declarations.
- Mutexes prohibit implicit copying; explicit assignment is implemented with two-object locking. Returned get_all/get_vector containers are owning values.
- Callback templates can technically return references that escape locks, but traced metadata consumers use value APIs; no unsupported caller lifetime is promoted into a defect.
- Outer share_id and user/system maps are not a single locked snapshot. Individual serialization locks protect map structure, not atomic file-plus-metadata commits or share-ID registration.

## Result and limits
No additional confirmed finding in this header. The portable archive has no explicit format version/checksum or size policy here; corrupt/untrusted metadata recovery is an entry/parser-boundary limitation rather than proof of a new exploit.

## Thorough re-review addendum — serializer lock boundary (2026-09-24)

Reread all 86 lines. `serialize:27-32` takes one container's recursive mutex while traversing its map. Outer `file_entry_metadata::serialize:68-72` has no corresponding whole-record lock and archives the plain `share_id` before two independent map locks. This is supporting evidence for **ADD-UTIL-001** (membership/share-ID state, container implementation sidecar) and **ADD-UTIL-003** (same-file archive interleavings, entry implementation sidecar), not an additional count. Locking only the map wrapper cannot stop two fstreams from truncating/writing the same archive. Metadata map assignment's two-object `std::lock` is correct within its narrower scope. A remediation should define an owned full-record snapshot, synchronized ID lifecycle, and ordered persistence commit. Proposed verification belongs to the two full finding sections; no compile/test was run.
