# Source/DLLs/1.149.0/compat_list.txt

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`.

Inspection: compatibility notes individually read by coordinator and reporting pass. Git proof: baseline blob `0369a29978fd75637d69b7501a0a1cfa21e491e4` is unique among the 37 manifests.

Tokens (source order): `1.148.15`, `1.148.16`, `1.148.17`, `1.148.18`, `1.148.19`, `1.148.20`, `1.148.21`, `1.148.22`, `1.148.23`, `1.148.25`, `1.148.26`, `1.149.0`, `1.150.0?`.

Human compatibility hypotheses, not build inputs; in-tree CMake does not parse this list or the question mark in `1.150.0?`. That punctuation records uncertainty, not a CMake syntax defect. Compatibility binaries were not executed; binary compatibility is unverified.

No direct confirmed defect. Global generation issues: `Source/DLLs/CMakeLists.txt.review.MD`.
