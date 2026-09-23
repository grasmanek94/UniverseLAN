# Fresh review — SystemTests/CMakeLists.txt

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–666. Static build-input review; no CMake execution.

## Inspection notes
- Inspected all target definitions and test registrations, matching client/server target dependencies, SDK include path/version definitions, provider path arguments, feature gates, CTest timeouts, serial/resource-lock settings and skip regexes.
- Host and runner are instantiated through the selected version list, not hardcoded SDK variants. Telemetry is conditionally compiled; other host source files are included for every selected version and must self-guard.
- That distinction exposes **BASE-SERVER-014** in `Host/Chat.cxx.review.MD`: excluding a scenario at add_test does not stop an unsupported ChatMessageType reference from being compiled in the host target.
- Custom-networking-close registration is x64-only; x86 coverage must not be inferred from the shared implementation. Most optional features are registered only where SDK interfaces exist.
- Inspected credential wiring as code only: optional profile values become host compile definitions when available. No credential file was opened, included or executed. This means building credential-enabled hosts requires separate artifact-handling care, but no credential disclosure was observed here.
- Root CMake makes SystemTests opt-in unless BUILD_ALL_TESTS is selected. No claim of full all-version compilation or passing tests is made.

## Result
One related build defect, **BASE-SERVER-014**, indexed at its source; no additional independent manifest finding.
