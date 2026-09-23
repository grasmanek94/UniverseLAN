# Fresh baseline review: EnvUtils.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Entire file read independently (13 lines). Static review only.

## Checked
- Windows-only wide declaration matches its guarded definition; both overloads return owning strings.
- get_gamedata_path_prefix has no borrowed-environment lifetime; consumers receive a value and form their own paths.
- Empty/missing/error results share the empty-string convention, consistent with prefix concatenation callers.

## Result and limits
No confirmed header defect. This API does not distinguish unset variables from failures or claim thread-stable environment snapshots.
