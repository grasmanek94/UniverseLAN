# Fresh review — IniData.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read all 206 lines; static Windows inspection.

## Inspection notes
- Audited base/derived storage paths, authentication/timeouts, tracing settings, user-ID choices, DLC map and local stats ownership against every constructor/getter in IniData.cxx.
- Base members are initialized before MachineInformation-dependent loading; derived primitive fields are assigned on normal constructor completion. Throwing construction does not expose an initialized instance with those fields unset.
- The immutable MachineInfo snapshot supplies path selection; getters recompute the environment-dependent game path. `local_user_data` is shared with Client models rather than an independently synchronized configuration snapshot.
- `SaveStatsAndAchievements` returns void and has no file-wide synchronization contract. Its concrete lost-retry defect is assigned to the implementation report (BASE-NET-008); path conversion/provisioning and parser defects are likewise reported at their executing code.
- Credential-option declarations were inspected as source only; no external configured values were accessed.

## Result
No additional declaration-local defect established. The API should gain an explicit persistence result when BASE-NET-008 is resolved. This is a scoped observation, not proof of concurrency or initialization correctness.
