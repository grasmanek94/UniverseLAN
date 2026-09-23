# Fresh baseline review — Factory.cxx

- Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`.
- Coverage: entire file, lines 1–259; static review only.

## Specific checked notes

- Read every wrapper and feature gate; traced instance creation, interface queries, processing, shutdown/reset, and the error-manager path into `GalaxyApiFactory.cxx`.
- `Shutdown` calls the facade's shutdown before deleting it, which correctly handles the fact that `GalaxyImpl`'s destructor itself does not own the global runtime.
- Compared historical `GalaxyFactory` query/create contracts. The null guards here depend on the creating/non-creating behavior and are ineffective in later builds because of `BASE-CORE-007`.
- `Init` and `InitLocal` do forward their boolean argument from this layer; it is lost in the facade implementation (`BASE-CORE-005`).
- SDK 1.114.9 `GalaxyApi.h` contains header-local static forwarding functions, including Chat. Absence of a Chat wrapper in this file alone was therefore not treated as a missing required DLL export.
- The CMake unity exclusion for this translation unit keeps its public-wrapper definitions from sharing a unity translation unit with SDK header-local wrapper definitions.

## Findings and limits

No independent wrapper defect confirmed. Full cross-file findings are `BASE-CORE-005` and `BASE-CORE-007`. Source declarations/calling conventions were checked; binary export coverage and concurrent singleton use were not executed or certified.
