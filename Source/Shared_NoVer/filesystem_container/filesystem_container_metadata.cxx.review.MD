# Fresh baseline review: filesystem_container_metadata.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Entire file read independently (162 lines). Static review only.

## Checked
- Every data-map read/write/clear/size/snapshot operation acquires its recursive mutex; get_str returns an owned value and get_all/get_vector produce owned snapshots.
- Assignment checks self-assignment and acquires both mutexes via deferred std::lock. Timestamp helpers consistently use signed stored Unix seconds and defaults.
- get_ll catches conversion exceptions and returns the supplied fallback; std::stoll accepts numeric prefixes, which matters for manually edited metadata but no strict parser contract was found.
- get_keys and get_values are separate snapshots; get_vector is the paired snapshot used by CloudStorage. No caller was found relying on separately retrieved vectors remaining aligned during mutation.
- file_entry_metadata reset/empty access share_id without an object-wide lock; the individual maps' locks do not create atomic metadata transactions. Parent file/metadata persistence failures are reported in the entry sidecar, not duplicated here.

## Result and limits
No additional confirmed standalone defect. Composite metadata concurrency and exception recovery need a defined entry-level transaction policy; no runtime stress/fault tests were executed.

## Thorough re-review addendum — composite-state findings now traced (2026-09-24)

The earlier limitation now has concrete production schedules, recorded without duplicate IDs:

- **ADD-UTIL-001**, full section in `filesystem_container.cxx.review.MD`: `share_id` read/reset/promotion is outside a common membership/entry operation lock. `reset:144-149` is not made atomic by its two separately locked clears. Lookup/recreate/removal can leave maps and index describing different entry generations.
- **ADD-UTIL-003**, full section in `filesystem_container_entry.cxx.review.MD`: independent serializers of one on-disk archive can interleave despite correct map locks. `operator=:111-125` locks both involved maps and protects each assignment; it does not combine source/destination system+user maps or persist one whole entry transaction.
- **ADD-UTIL-004**, same entry sidecar: `empty:151-157` is a state predicate, not proof that the destination archive is absent. A successful copy with empty final metadata must still erase or replace a previously existing archive.

Positive counterevidence remains: getters return owned strings/containers; paired `get_vector` snapshots preserve key/value correspondence. Integer metadata parse exceptions return defaults. Normal SDK timestamps are nonnegative; arbitrary signed inputs and permissive numeric-prefix parsing remain contract limits, not separate production findings. Verification for the new schedules is proposed in the responsible sidecars; no tests were executed.
