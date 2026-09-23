# Fresh baseline review: filesystem_container_utils.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Entire file read independently (216 lines). Static review only.

## Checked
- Read both encoders, unchecked percent decoder, all path-normalization/concatenation overloads, both directory-listing instantiations, and Unix-second helper.
- `std::mismatch` uses both end iterators and compares components, avoiding a string-prefix `container`/`container2` error. Existing symlinks are resolved for the containment check; errors fail closed.
- Normalization does not itself promise a relative path in the C++ sense, and sanitize_path does not weakly canonicalize despite the header comment. Main entry operations perform a separate containment check.
- A cached path is not a Windows handle-bound sandbox; reparse changes after validation remain a local-filesystem trust limitation. No credible remotely-created symlink path was found in traced upload callers.
- Case and opaque dot-container handling are BASE-UTIL-004/011. Windows device names, trailing-dot/space names, and malformed on-disk percent sequences are not made fully portable by this encoder. IStorage explicitly requires portable names (`IStorage.h:116-120`), so prohibited-name calls are not counted as a separate reachable SDK defect.
- Valid encoder output round-trips hex escapes; untrusted hand-edited escapes have no validation/version marker. Listing uses throwing iterators; filesystem errors can abort initialization rather than return a partial inventory.

## Finding

### BASE-UTIL-012 — Canonical relative listing loses link entry identity
- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Shared_NoVer/filesystem_container/filesystem_container_utils.cxx:56-64,209-215`
- **Affected scope:** Filesystem-container startup scan; same finding as the container implementation sidecar, counted once.

**Evidence / mechanism:** `relative(entry, search_root_path)` weakly canonicalizes the entry. A real file and an in-root file symlink to it can therefore produce the same relative path. The consumer at `filesystem_container.cxx:29-42` ignores duplicate map insertion and appends both to its vector index.

**Impact:** Duplicate list entries and count/index divergence after enumeration/removal. This requires locally present aliases; it is not an allegation of a remote link-creation vulnerability.

**Possible fixes:** Return lexical relative directory-entry names with an explicit link policy, skip unsupported links, or deduplicate canonical identities in the consumer.

**Recommended fix:** Establish the link policy before listing, preserve the chosen identity consistently, and append to the index only when map insertion succeeds.

**Verification:** On Windows, enumerate a regular file and an in-root file symlink, reconstruct the container and remove the indexed file; validate unique entries and consistent counts throughout. Not run.
