# Fresh review — Host/Apps.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–77. Static review.

## Inspection notes
- Checked installed/disabled/absent DLC queries and expected language values against runner-generated app configuration fields.
- Full and truncated language buffers explicitly verify content and terminating bytes, including the optional language-code API.
- Optional ownership checking registers a global listener, also passes a specific listener, pumps, unregisters, and checks both receive exactly one successful result for the requested ID.
- The pump stops at the first observed callback and expects both callbacks to be delivered within the same ProcessData batch. That matches the examined local callback style but is not a general alternate-provider timing proof.

## Result
No confirmed independent test defect. This tests configured local ownership behavior, not an external DLC entitlement service.
