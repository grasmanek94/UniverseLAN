# Fresh baseline review — Impl/Utils.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–179. Static Windows review; shallow serious-defect scope.

## Checked
- Read image dimensions/RGBA, notification registration/retrieval, overlay methods and service-connection state forwarding.
- RGBA output is logged only as address/capacity. Notification type/content tracing uses the bounded helper, so the declared capacity bounds its scan.
- GetNotification inspects full content capacity rather than the returned written length and logs consumable without an error check; unwritten-tail/failed-output logging remains a validation concern. No out-of-allocation read was demonstrated here.
- Observer registration/destruction uses the shared container and therefore the shared shutdown-order finding.

## Result
No additional independent serious local defect confirmed. Game-server Utils availability is covered at the resolver (BASE-INTERCEPT-007). No overlay or notification operation was executed.

## Follow-up review addendum — 2026-09-24

Reread all 179 lines. The output-buffer contract strengthens the prior unwritten-tail observation as an additional instance of the existing trace-extent finding.

### BASE-INTERCEPT-005 — Addendum: notification tracing includes bytes the SDK did not write

- **Severity:** Medium for this bounded-disclosure instance; existing packet/details finding remains High
- **Confidence:** High for the extent mismatch; no native trace was executed
- **Category:** Memory Safety
- **Location:** `Source/InterceptionLogger/Impl/Utils.cxx:95–107`; `Source/Shared_NoVer/SafeStringCopy.hxx:94–114`.
- **Affected scope:** Notification content tracing with RETURN_VALUES enabled, for a successful binary notification shorter than the caller's content capacity.

**Evidence**

SDK `Source/DLLs/1.152.11/galaxy/IUtils.h:175–189` defines GetNotification's return as the number of bytes written to the content buffer. The wrapper stores that result but traces `safe_fix_null_char_ptr_annotate((const char*)content, contentSize)`. The helper scans for NUL up to the full supplied capacity and constructs a string through that extent; notification content is a void/binary buffer, not a promised NUL-terminated string.

**Failure mechanism**

A valid 64-byte reusable destination contains old data. A successful SDK call writes four nonzero content bytes and returns 4. If the next old bytes are nonzero, the trace continues past byte 4 into the old tail, up to its first NUL or byte 64. No malformed input, failed output or undersized allocation is needed. This is the same missing-valid-readable-extent class as BASE-INTERCEPT-005, with capacity used beyond the produced extent rather than a reported object size used beyond capacity.

**Impact**

Trace artifacts can contain stale caller-buffer contents unrelated to the notification. This particular path is capacity-bounded: an out-of-allocation read/crash is not established and is not inherited from the High packet/details examples. Separate scalar logging after failed calls remains a contract/failure-path validation question.

**Possible solutions**

Trace a checked binary span bounded by both the successful written length and capacity, or omit content while retaining address/length diagnostics.

**Recommended resolution**

Apply BASE-INTERCEPT-005's valid-extent rule consistently: limit content inspection to at most `min(result, contentSize)` after establishing usable output and nullability. Preserve the result returned to the caller and do not consume/overwrite the caller-visible SDK error while checking it.

**Verification**

Proposed only: prefill a 64-byte output with a synthetic tail marker, return a four-byte non-NUL binary notification, and require that neither the marker nor any tail byte appears in tracing. Cover exact-fit, embedded NUL, zero-written, null/zero-capacity where supported and failure cases. No secret data, native DLL load or test execution is needed for the proposed fake. Existing BASE ID; no new count.
