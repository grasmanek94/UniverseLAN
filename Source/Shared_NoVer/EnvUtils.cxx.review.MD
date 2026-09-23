# Fresh baseline review: EnvUtils.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Entire file read independently (66 lines). Static Windows review only.

## Checked
- Narrow/wide getenv_s size probes, allocation ownership, second-call status, zero/missing values, and exclusion of the trailing terminator from returned strings.
- If the environment changes between probe and copy, a failed second call returns empty instead of indexing an invalid length. No retry/stable-snapshot promise is made.
- Traced gamedata prefix use in IniData and real-DLL prefix use in SharedLibUtils. Environment-provided paths are user configuration, not a validated containment boundary.
- Wide overload and Windows CRT calls are guarded; non-Windows getter was read for guard consistency only.

## Result and limits
No confirmed defect for traced nonempty environment-variable names. Invalid variable-name/CRT invalid-parameter-handler behavior and concurrent environment mutation were not exercised.
