# Fresh baseline review: cereal.cmake

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. All eight lines reviewed.

## Inspection notes
Pinned vendored cereal-1.3.2 header tree is exposed by a dummy-C static target; recursive CONFIGURE_DEPENDS adds IDE inputs and PUBLIC includes reach consumers. No native Galaxy import library is introduced. Compiler successfully used this integration in all selected builds.

## Findings
No direct build defect. Archive allocation limits are an application boundary obligation: see BASE-NET-001 in Shared/Networking/Networking.hxx.review.MD. Do not interpret successful header integration as safe untrusted deserialization.
