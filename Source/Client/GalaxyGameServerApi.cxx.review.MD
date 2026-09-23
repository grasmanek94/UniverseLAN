# Fresh baseline review — GalaxyGameServerApi.cxx

- Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`.
- Coverage: entire file, lines 1–65; static Windows SDK contract review.

## Specific checked notes

- Traced every export to the single translation-unit `UniverseGameServer`, including init/shutdown, all getters, listener registrar, and event pumping.
- Exported functions retain the SDK `GALAXY_DLL_EXPORT`/`GALAXY_CALLTYPE` annotations. The SDK's Windows call type is `__cdecl`; no independent source-level calling-convention mismatch was found.
- `GAME_SERVER_API` starts later than `HAS_IUTILS` in the inspected feature matrix, so the unguarded `GameServerUtils` body inside that outer guard has an implementation available.
- Telemetry and extended shutdown match their feature gates. `ShutdownGameServerEx` ignores `preserveStaticObjects`; the graph already retains some state, and SDK-internal static-object semantics were not established sufficiently to assert another concrete defect.
- The process-static server delegates lifetime and dispatch handling to reviewed owners. Role selection (`BASE-CORE-004`), error propagation (`BASE-CORE-005`), and callback shutdown (`BASE-CORE-003`) are canonical cross-file findings, not new forwarding defects.

## Findings and limits

No independent forwarding defect confirmed. DLL export tables, ordinal completeness, loader-lock teardown, and live SDK interoperability were not tested.
