# Fresh baseline review: SharedLibUtils.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Entire file read independently (186 lines). Static Windows review; no DLL loading or builds.

## Checked
- Read PE export enumeration, MapAndLoad/UnMapAndLoad exception cleanup, singleton construction, environment prefix/name composition, LoadLibrary/FreeLibrary, null checks, exact symbol lookup, and ambiguous/missing substring handling.
- Function-local singleton initialization serializes construction. Loaded image mappings are unmapped before a caught C++ exception is rethrown. Returned name pointers refer to a vector populated once; no later normal mutation was found.
- Traced interceptor function-pointer construction and per-version CMake definitions. Imagehlp linking is supplied transitively through the static tracer target; absence from this target's direct list alone is not a demonstrated unresolved-symbol defect.
- PE sizes/RVAs/string termination are not independently bounded, and Win32 SEH access violations are not made safe by catch-all under ordinary /EHsc. DLLs here are trusted executable inputs; no remotely supplied PE path or security exploit is claimed.
- Relative DLL searching/environment prefixes and process-global loader lifetime are deployment assumptions. No normal caller deletes the singleton or deliberately uses pointers after module teardown.

## Finding

### BASE-UTIL-015 — Version-independent loader cannot receive the RED-prefix feature
- **Severity:** Informational
- **Confidence:** High
- **Category:** Build
- **Location:** `Source/Shared_NoVer/SharedLibUtils.cxx:99-118`; `Source/Shared_NoVer/CMakeLists.txt:3-13`
- **Affected scope:** Future Windows interceptor variants requiring `RealREDGalaxy[64].dll`; none of the current 69 version directories enables this feature.

**Evidence / mechanism:** The filename contains RED only under `GALAXY_BUILD_FEATURE_HAS_RED_PREFIX`, but this source is compiled once into `universelan-common-shared-no-ver`. That target receives only OS/version-minimum definitions. `add_version_definitions_to` applies features to versioned Shared/interceptor targets; consumers' definitions do not propagate backwards into an already compiled dependency. `galaxy_sdk_features.cmake:234` enables the RED feature for 1.149.12–1.149.16, and DLL manifests use the same feature for REDGalaxy output naming. The helper therefore compiles the no-RED branch for all variants in the normal graph.

**Impact:** If a RED-gated SDK is added, its interceptor will search for the wrong real DLL and can fail initialization or load an unintended ordinary DLL. The current directory matrix has no version in 1.149.12–1.149.16, so no current target demonstrates this failure. The environment prefix cannot insert RED into the fixed basename. Count this as latent integration debt, not a present production defect.

**Possible fixes:** Move version-sensitive name construction into a versioned translation unit and pass the resolved name to a generic loader; alternatively compile a loader object per version.

**Recommended fix:** Keep generic handle/lookup ownership shared, but supply the complete expected filename from the version-aware interceptor. Do not put a single global version define on the common library, which would break simultaneous variant builds.

**Verification:** Inspect compile definitions and resolve filenames for one RED and one ordinary variant in the same configuration; initialize each against only its correctly named real DLL. No build/load test was run.

## Thorough re-review addendum — BASE-UTIL-015 remains informational (2026-09-24)

- **Disposition / severity / confidence / category:** Retained as Informational / High / Build, not reinstated as a confirmed current-target defect. Source locations remain `SharedLibUtils.cxx:99-118` and `Shared_NoVer/CMakeLists.txt:3-13`.
- **Fresh evidence:** The feature interval is still 1.149.12–1.149.16 (`Source/galaxy_sdk_features.cmake:234`); the actual `Source/DLLs` directory list has 1.149.0 and then 1.150.0, with no directory inside that interval. `Source/DLLs/CMakeLists.txt:10-40` applies definitions to versioned targets, not retroactively to the common object. Passing a complete version-aware filename remains the recommended option if an affected SDK is added.
- **Loader counterevidence:** Function-local static initialization serializes this singleton's export-vector population. Normal subsequent lookups do not mutate the vector; returned matching-name pointers are not demonstrated dangling. `ListDLLFunctions` unmaps after ordinary C++ exceptions, exact lookup checks missing symbols, and substring lookup rejects ambiguity. `Source/Tracer/CMakeLists.txt:9-16` supplies imagehlp through the static dependency graph. No new linker-failure claim is made merely because the library is absent from Shared_NoVer's direct list.
- **Boundary / verification:** Relative search, environment-selected executable inputs, PE-RVA validation and cross-module ImageHlp concurrency remain assumptions to validate for a specific deployment. They do not establish a remote input exploit in the inspected callers. Current `SharedLibUtilsTests.cxx:9-14` only checks null/empty rejection before loading. Mixed-name loader validation is proposed for the future feature; no DLL load/build/test was executed here.
