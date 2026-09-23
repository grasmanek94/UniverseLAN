# Fresh review — SetLobbyDataMessage.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read all 59 lines and both version branches.

## Inspection notes
- Request/lobby IDs, success, conditional reason and key/value have defaults. Server verifies owner and replaces success/value on failure; empty values also carry SDK clear semantics.
- Variable key/value allocations happen before owner/authentication checks; transport budgeting must precede this serializer.

### [BASE-NET-005] Conditional failure enum shifts key/value bytes under an unchanged message ID
- **Severity:** Medium
- **Confidence:** High
- **Category:** API/ABI
- **Location:** `Source/Shared/Networking/Messages/SetLobbyDataMessage.hxx:18-34`.
- **Affected scope:** Differing Windows SDK endpoints across 1.124.0/1.125.2.

**Evidence / failure mechanism:** Builds above 11240 serialize a failure enum after success; older ones serialize key length immediately. The class ID hashes only the name, and challenge/acceptance carries no schema version. A newer decoder consumes the first old key-length bytes as the enum and reads the following bytes as a displaced size tag.

**Reproduction conditions / impact:** Use a matching key with these differing SDK builds and set a nonempty lobby property. Requests may allocate from a misread length or be discarded, leaving callbacks unresolved. Matching schemas are unaffected; this is missing rejection of incompatible endpoints, not a cross-version support mandate.

**Alternatives / recommended resolution:** Negotiate/reject a schema fingerprint before application traffic, or define a stable protocol failure field and translate to each SDK.

**Verification:** Paired fixtures in both directions, same-version controls and bounded-allocation assertions. Count this transport/schema root cause once in NET.MD. Tests not run.
