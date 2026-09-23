# Fresh review — Common/Protocol.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–18. Static review.

## Inspection notes
- Verified EVENT/PASS/FAIL prefixes against host emit/fail/PASS output and runner handleLine parsing.
- string_view constants have static backing storage; declarations match implementation signatures and numeric overloads.
- The protocol is line-oriented and host output uses endl. The runner's exit/log ordering, rather than a missing newline in these constants, causes **BASE-SERVER-012**.

## Result
No confirmed declaration defect. No live IPC test was executed.
