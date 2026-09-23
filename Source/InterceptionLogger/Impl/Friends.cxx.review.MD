# Fresh baseline review — Impl/Friends.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–833. Static Windows review; shallow serious-defect scope.

## Checked
- Read persona/avatar operations, user-info and friend/invitation requests, rich-presence mutations/enumeration, invitation UI and FindUser across feature guards.
- Nullable rich-presence values are trace-annotated without changing the original pointer sent to the SDK; avatar binary buffers are not dumped.
- Checked the bool/void GetRichPresenceByIndex transition, returned-string annotation and capacity-bounded Copy tracing. Scalar sendTime output on an SDK error remains a validation item, not a claimed reproduced defect.
- Followed specific listener wrapping and global observer setup through the common lifecycle; directly registered game listeners bypass the observer proxies.

## Result
No additional independent serious defect confirmed. Common teardown/proxy findings 001–003 apply; no social/backend behavior was tested.
