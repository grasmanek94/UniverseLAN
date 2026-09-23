# Fresh baseline review — Impl/Stats.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–748. Static Windows review; shallow serious-defect scope.

## Checked
- Read stats/achievement getters and setters, all leaderboard request/score paths, specific-listener wrapping, time-played APIs and latest achievement-name/count additions.
- Checked enum-by-value/reference feature branches and bounded string-copy tracing. User arrays are traversed only after null/positive-count checks.
- Plain scalar out-values are logged without consulting SDK error state; failure-path output initialization requires validation. The concrete extent defect below is independently supported by the truncation contract.

## BASE-INTERCEPT-005 — Leaderboard detail tracing ignores the caller's buffer capacity

- **Severity:** High
- **Confidence:** High for the missing bound and SDK truncation contract; not dynamically reproduced.
- **Category:** Memory Safety
- **Location:** `Source/InterceptionLogger/Impl/Stats.cxx:525–550`, especially line 548.
- **Affected scope:** `HAS_LEADERBOARD_WITH_DETAILS` (1.69.0 onward), RETURN_VALUES tracing. Same unique root cause as packet tracing in Networking.cxx.

**Evidence and failure mechanism:** After forwarding `GetRequestedLeaderboardEntryWithDetails`, the logger calls `bytes_to_hex(details, outDetailsSize)` without considering `detailsSize`. SDK `1.152.11/galaxy/IStats.h:745–775` expressly allows truncation to the passed buffer size, while outDetailsSize is the size of the extra information. `Shared_NoVer/SafeStringCopy.hxx:117–127` reads exactly the requested byte count; it does not know the destination capacity. Thus an entry with 1024 detail bytes and a valid 16-byte destination can cause tracing beyond the destination. The void API also leaves the wrapper without a checked success predicate before reading outDetailsSize on failure.

**Impact:** Out-of-bounds reads, a crash or adjacent-memory disclosure into trace files. Users need not provide malformed input: a documented truncated read is sufficient under the stated size contract.

**Possible fixes:** Bound the trace length by the caller's capacity and verified valid extent, or omit detail bytes if the call failed/extent is unknown.

**Recommended resolution:** Inspect details only after success is established without corrupting caller-visible error state, and use at most `min(detailsSize, outDetailsSize)` readable bytes with a null check. Preserve all original output values/API semantics.

**Verification:** During a legal leaderboard-result callback, return larger detail size than destination capacity from a fake SDK and use a guard-page destination. Exercise RETURN_VALUES on/off, zero capacity and SDK-error paths under Windows ASan. Compare vendor size behavior at early/modern feature boundaries. Proposed only; counted once with the Networking instance.
