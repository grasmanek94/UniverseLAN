# Fresh review — Common/Protocol.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–36. Static review.

## Inspection notes
- Checked token character classification, duplicate rejection and numeric Galaxy real-ID parsing, including empty/non-digit/overflow/zero/out-of-range values.
- Character predicates receive unsigned char, avoiding signed-char cctype undefined behavior. stoull exceptions are converted to failure; real IDs are limited to the 56-bit payload.
- Generic protocol tokens intentionally permit dots. They are not safe filesystem components: the model uses role tokens as directory names, producing **BASE-SERVER-013** in `Runner/Model.cxx.review.MD`.

## Result
No independent protocol-helper defect. Filesystem constraints should be enforced at path-bearing model fields, not by silently narrowing every event token.
