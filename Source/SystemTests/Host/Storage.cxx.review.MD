# Fresh review — Host/Storage.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–198. Static review.

## Inspection notes
- Traced local write/read validation, server share, local shared-cache removal, server download, ID/name/count/size checks, binary/full/offset reads, invalid-ID failure and upload/download policy denial.
- SharedFileClose clears the local shared entry before downloading, so the tested download is not merely reading the upload's local cache.
- Download denial checks exactly one matching failure after an additional pump and no cached result. Zero-length legitimate files are not exercised by the nonempty payload.
- The persisted roundtrip uses one server lifetime and one filename. It does not establish restart-stable IDs (**BASE-SERVER-006**) or truthful failure/repeated-name behavior (**BASE-SERVER-007**).
- Legacy/global versus explicit listener signatures are guarded. No server filesystem was modified during this review.

## Result
No independent confirmed test defect. Add fresh-store restart and repeated-name/error-injection cases when implementing the server fixes.
