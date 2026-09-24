# Fresh baseline review — Impl/InitOptionsModern.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–188. Static Windows review; shallow serious-defect scope.

## Checked
- Read constructors, all null-aware setters/getters and the SDK-option reconstruction path. Optional strings own copied input, and returned c_str pointers refer to retained InitOptionsModern storage during initialization.
- Checked feature-gated allocator/thread factory, storage, peer-path, host and port fields; fields start initialized even when unavailable.
- Legacy SDK InitOptions includes throwExceptions, but this conversion only copies it when HAS_INITOPTIONS is false; gameServicePlatform is explicitly omitted. These are compatibility limitations, not demonstrated serious memory faults.

## Result
No independent serious C++ lifetime defect confirmed here. The legacy factory initialization path also bypasses full option reconstruction; its behavioral fidelity needs separate validation. No allocator or initialization test was executed.

## Follow-up review addendum — 2026-09-24

Reread all 188 lines. The earlier no-lifetime-defect observation stands; the supported legacy option contract now establishes a material forwarding defect.

### ADD-INTERCEPT-002 — Legacy option conversion discards the caller's exception policy

- **Severity:** Medium
- **Confidence:** High
- **Category:** API/ABI
- **Location:** `Source/InterceptionLogger/Impl/InitOptionsModern.cxx:10–33,148–176`; downstream `UniverseLANInterceptor.cxx:145–166`.
- **Affected scope:** Factory SDKs with InitOptions (feature intersection 1.82.0–1.114.9), including 1.87.0 and 1.114.9.

**Evidence:** Both cited SDKs declare a caller-selected `const bool throwExceptions` in InitOptions (`1.87.0/galaxy/IGalaxy.h:35–60`; `1.114.9/galaxy/IGalaxy.h:38–63`). This constructor starts it as false and copies it only when `HAS_INITOPTIONS` is false. Reconstruction uses the SDK's default constructor argument instead. The downstream factory path forwards the resulting false policy using a string overload that also omits supported path settings. Full call-chain evidence is in `UniverseLANInterceptor.cxx.review.MD`, ADD-INTERCEPT-002.

**Failure mechanism:** A true legacy exception-policy argument becomes false during options conversion; the reverse adapter also cannot round-trip both policies. The always-false modern-options/factory feature intersection prevents use of the actual native options overload. Owned string storage is not the defect.

**Impact:** Legacy initialization changes error-delivery policy and can lose required SDK configuration/peer selection. No crash or vendor initialization was executed.

**Possible solutions:** A separate faithful legacy adapter, or exact feature-gated construction of each SDK options type.

**Recommended resolution:** Copy the policy when the supported SDK type actually has that member and pass it into the legacy SDK constructor, where the member is const. Coordinate with the native-overload correction; either change by itself leaves part of the same defect.

**Verification:** Proposed only: round-trip both policy values and distinct synthetic paths through supported 1.87.0/1.114.9 option adapters and inspect the overload/values received by a recording native factory. No execution. Same ADD-INTERCEPT-002 as the owner-side report, counted once.
