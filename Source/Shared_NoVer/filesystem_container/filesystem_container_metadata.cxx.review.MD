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
