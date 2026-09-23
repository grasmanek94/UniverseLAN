# Fresh baseline review: Apps.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Entire file read, lines 1–94. Static Windows review; no compile/run evidence.

## File-specific inspection

- Inspected class ownership, virtual destructor/overrides, product-ID defaults, language and language-code copy signatures, ownership-listener declaration, and all feature guards.
- The sole member is a non-owning `InterfaceInstances*`, consistent with the implementation facade and normal initialization/reset ownership. Language pointer lifetime is backed by stable configuration member references, verified in the implementation dependency.
- Copy methods preserve explicit destination lengths. The code-level helper's null/zero-length behavior was read, not inferred from its name.
- The broad header remark that Apps works after an Init error is older than the latest SDK exception for `IsDlcOwned`; actual post-failure availability depends on CORE construction/accessors. No standalone crash is claimed merely from the stale remark.
- Latest SDK distinguishes installed DLC from ownership and documents login requirements. The implementation deliberately maps both to configuration; this is a compatibility limitation recorded in `Apps.cxx.review.MD`, not a vulnerability finding.
- Optional/global listener dispatch and cancellation require registrar integration; the declaration itself does not supply lifetime ownership.

## Findings disposition

No additional declaration-only defect counted. This scoped observation does not certify all SDK ABI variants or initialization-failure behavior. Verification priorities are copy-buffer boundaries, configuration lifetime, feature-matrix signatures, and a coherent auth/ownership-query lifecycle. Existing SystemTests cover the healthy configuration/copy path only.
