# Fresh baseline review — InitOptionsFactory.hxx

- Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`.
- Coverage: entire file, lines 1–49; static legacy-adapter review.

## Specific checked notes

- Checked constructor member initialization and optional path defaults. This is an internal compatibility carrier for SDK generations without their own InitOptions; it is not exported as the modern SDK struct.
- `InitOptionsModern.hxx` selects this type only when `GALAXY_BUILD_FEATURE_HAS_INITOPTIONS` is false. Legacy string overloads populate credentials and configuration path before normalization.
- The inner guard uses unprefixed `HAS_INITOPTIONS`, whereas the build feature mechanism defines prefixed macros. In the inspected include/build path it is undefined and evaluates to zero, so the adapter is present when needed. No failing repository configuration was established; using the same feature spelling would reduce ambiguity.
- Pointers are borrowed only until conversion into owning strings. Required credential pointers still need to be valid at that boundary; optional path pointers are normalized safely downstream.

## Findings and limits

No confirmed standalone defect. This carrier has no exception-policy field; legacy policy propagation is broken in its callers/normalizer as documented by `BASE-CORE-005`. No external-macro or complete SDK-version build matrix was executed.
