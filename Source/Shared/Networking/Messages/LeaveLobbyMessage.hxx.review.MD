# Fresh review — LeaveLobbyMessage.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read all 59 lines and both reason branches.

## Inspection notes
- Request/lobby IDs have in-class defaults; overloads set either an SDK leave reason or legacy ioFailure bool. Server overwrites request reason before replying.
- Client maps reason to cache removal and listener behavior; no missing field initialization found.

### [BASE-NET-005] Leave-reason width changes behind the same wire ID
- **Severity:** Medium
- **Confidence:** High
- **Category:** API/ABI
- **Location:** `Source/Shared/Networking/Messages/LeaveLobbyMessage.hxx:16-28`.
- **Affected scope:** Mixed Windows SDK endpoints across the 1.133.0 leave-reason feature boundary.

**Evidence / failure mechanism:** `reason` is a bool in older builds and an SDK enum in newer ones. Both serialize under the same class-name hash; handshake does not negotiate the schema and dispatch does not require complete input consumption. A legacy one-byte reason cannot satisfy the newer enum read; a new reason's extra bytes may be ignored by an older decoder.

**Reproduction conditions / impact:** Authenticate differing-version peers and leave a lobby. Requests/responses can be discarded or misinterpreted after authentication instead of cleanly rejecting incompatible endpoints. Same-schema builds are unaffected.

**Alternatives / recommended resolution:** Reject incompatible schema fingerprints during handshake, or use a fixed-width protocol leave reason with SDK-specific translation. Do not require arbitrary SDK interoperation if it is unsupported.

**Verification:** Serialize both reason formats and test both directions plus same-version controls; expect supported translation or early compatibility failure. Unique root finding counted once; no test executed.
