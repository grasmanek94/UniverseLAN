# Fresh review — Host/CustomNetworking.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–128. Static review.

## Inspection notes
- Reviewed ix network initialization balance, feature-specific explicit/global listeners, open callback validation, binary echo and close callback counting.
- Echo checks available length and exact NUL-containing byte payload. Close checks one open, no open failure, same connection ID/string, one close and the expected local close reason; an extra one-second pump observes immediate duplicates.
- Echo does not explicitly close its channel; the host's established `_Exit` lifecycle and runner process cleanup bound it. Therefore this scenario does not validate successful connection-resource teardown.
- CMake registers close only for x64. Global-listener compatibility branches and POSIX portability are not runtime-certified by this review.

## Result
No independent confirmed finding. Optional connection service limitations are not treated as core server failures.
