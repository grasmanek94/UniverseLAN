# Fresh baseline review — Impl/Listeners/FriendsListener.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–362. Static Windows review; shallow serious-defect scope.

## Checked
- Read every persona, user-info, friend-list, invitation, rich-presence, game-join and user-find callback across feature guards.
- Checked enum/flag formatting, null-annotated connection/specifier strings and argument ordering for success/failure pairs.
- Every actual target-forwarding macro is last. Distinguished unsolicited global-only observers from request-specific proxy use in FriendsImpl.

## Result
No independent serious callback defect confirmed. The shared macro's concurrency and owner-scoping issues are BASE-INTERCEPT-002/003. No game callback or social API was executed.
