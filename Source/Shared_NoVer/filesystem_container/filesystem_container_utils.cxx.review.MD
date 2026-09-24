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

## Thorough re-review addendum — BASE-UTIL-012 retained and path-policy qualifications (2026-09-24)

- **BASE-UTIL-012 disposition:** Retained, Medium / High confidence / Correctness, at `filesystem_container_utils.cxx:56-64,209-215` and constructor `filesystem_container.cxx:29-42`. `std::filesystem::relative` resolves existing components; the consumer still ignores failed insertion and appends a second index object. One finding across both sidecars, not two.
- **Canonicalization detail:** `inside_basepath:77-117` compares full canonical path components with both iterator ends, blocking ordinary `../outside` and sibling-string-prefix tricks. `sanitize_path:142-149` only performs lexical normalization and absolutization, despite the weak-canonical wording in the header. The checked canonical path is discarded; subsequent I/O uses a cached lexical absolute path. Thus this check is not a persistent file-identity/handle guarantee. Case-sensitive `path` comparison is also not Windows identity folding (BASE-UTIL-004).
- **Trust boundary / reparse counterevidence:** Existing outward links are ordinarily rejected by the containment check. Replacing an ancestor with a junction after validation can redirect a later open because no handle pins the tree; that requires local ability to change the storage tree. No remotely created symlink/junction path was established from accepted upload data. Keep this as an explicit deployment/TOCTOU limit, not a newly counted remote exploit. A future confinement fix should use one defined reparse policy and validated handle-relative operations, not assume the helper's name proves confinement.
- **Naming:** Ordinary encoder-generated uppercase escapes roundtrip, including percent itself. Invalid/truncated/lowercase hand-authored escapes lack validation. Device/trailing-dot/space experiments do not establish compliant IStorage defects given `IStorage.h:116-120`. ADD-UTIL-006 instead uses two completely portable names to expose metadata namespace prefix conflicts; no malformed escape is needed.
- **Options / recommendation / verification:** Retain the explicit link-policy plus insertion-result fix. Proposed Windows checks should distinguish ordinary lexical containment, in-root/outward links, locally replaced ancestors, case-sensitive-directory mode, and post-restart index uniqueness. The actual utils tests cover encoding and ordinary traversal/normalization (`UnitTests/Shared_NoVer/filesystem_container/filesystem_container_utilsTests.cxx:11-39`); none were run here.
