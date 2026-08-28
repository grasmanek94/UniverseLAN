# Review: `Source/galaxy_sdk_features.cmake`

## Finding — repeated range declarations duplicate disabled definitions

- **Severity:** Low
- **Evidence:** `HAS_GAMESERVERTELEMETRY`, `HAS_ICHAT_ROOMLISTENERS`,
  `HAS_ISTORAGE_FILESHARELISTENERS`, and
  `HAS_REQUESTUSERDATA_ISPECIFICLISTENER` are declared twice. When a version is
  in the gap between ranges, `afvd()` appends the same name to
  `BUILD_FEATURES_LIST_DISABLED` more than once because it only checks the
  enabled list.
- **Impact:** `afvd_finalize()` emits duplicate `target_compile_definitions`
  entries. The value is currently the same, so this is primarily build
  noisiness and a maintenance hazard, not the previously claimed incorrect
  enabled feature.
- **Suggested fix:** Deduplicate the disabled list before appending (or model
  ranges as a single table and evaluate them once), then add a configure-time
  check for expected feature values at range boundaries.
