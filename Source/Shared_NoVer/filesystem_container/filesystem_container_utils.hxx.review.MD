# Fresh baseline review: filesystem_container_utils.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Entire file read independently (30 lines). Static review only.

## Checked
- Matched all path, encode/decode, listing and timestamp declarations to definitions and parent/entry callers.
- The sanitize_path comment promises weak canonicalization, but the implementation performs lexical normalization plus absolute conversion. The actual security check separately weakly canonicalizes; this comment mismatch alone is not reported as a bypass.
- `sanitize_relative_path` does not reject rooted inputs; containment helpers are the enforcement boundary. Encoders are byte/string interfaces and do not establish a comprehensive Windows filename or UTF-8 conversion policy.
- Listing returns path values; BASE-UTIL-012 covers canonical identity loss in the implementation. Whole-file and subcontainer identity findings are in the container sidecar.

## Result and limits
No additional independent declaration defect. Windows reparse-point races, case-sensitive directories, malformed escapes, and narrow/wide encoding need explicit supported-input policies. The review did not execute filesystem probes.
