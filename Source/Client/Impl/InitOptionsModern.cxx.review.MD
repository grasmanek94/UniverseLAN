# Fresh baseline review — InitOptionsModern.cxx

- Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`.
- Coverage: entire file, lines 1–65; static inspection only.

## Specific checked notes

- Checked every constructor member against the header's feature guards. Both constructors initialize all enabled fields; default objects contain empty strings, zero port, false exception policy, and null hooks.
- Optional config/storage/host strings explicitly tolerate null before string assignment; required client ID/secret are assigned without null checks. The inspected SDK documents them as supplied credentials, not optional values, so a valid-null contract was not invented for a separate finding.
- Input strings are copied before caller-owned buffers can expire; custom allocator/factory objects themselves remain borrowed.
- SDK 1.114.9 `InitOptions` has `throwExceptions`, but the conversion always leaves the normalized field false. Legacy string overloads also lose the supplied flag and runtime ignores it. This participates in the demonstrated public error-policy failure `BASE-CORE-005`.
- Copied host/port and custom hooks are not consumed by the inspected client startup; preserving values does not establish feature implementation.

## Confirmed cross-file defect

### BASE-CORE-005 — Legacy exception policy is discarded during normalization

- **Severity:** Medium
- **Confidence:** High
- **Category:** API/ABI
- **Location:** `Source/Client/Impl/InitOptionsModern.cxx:10–45`, especially line 15.
- **Affected scope:** Legacy SDKs with an InitOptions exception flag; part of the single error-channel finding canonically reported in `../GalaxyDLL.cxx.review.MD`.

**Evidence**

SDK 1.114.9 `IGalaxy.h:49–58` initializes and stores `InitOptions::throwExceptions`. This conversion initializes its corresponding field to false and never copies that input field. The facade's string overloads also discard their flag, and the public runtime catch unconditionally rethrows while GetError returns null.

**Failure mechanism**

An application selects exception behavior with legacy InitOptions, but normalization loses that value. A configured DNS/ENet failure ultimately escapes as `std::runtime_error` regardless of the requested policy. Simply preserving the field will not fix the separately missing boundary enforcement.

**Impact**

Games relying on the legacy nonthrowing contract can receive unhandled exceptions, while callers using SDK error retrieval receive no useful error.

**Possible solutions**

Copy the field only for SDK inputs that actually declare it, and supply explicit defaults/policy from legacy string overloads; alternatively normalize policy through separate named constructors for the old and modern contracts.

**Recommendation**

Preserve legacy policy during normalization and implement the shared SDK error boundary described in `BASE-CORE-005`. Do not access a nonexistent modern SDK field or treat modern default policy as permission to throw.

**Verification**

Check normalized values for both legacy booleans, then force init failure through both legacy overload forms and the modern API. Require the appropriate exception/error behavior on each path. No malformed-init, hook, allocation-failure, or complete version-matrix execution ran.
