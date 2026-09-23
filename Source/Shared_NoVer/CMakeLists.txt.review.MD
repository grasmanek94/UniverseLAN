# Fresh baseline review: CMakeLists.txt

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Entire manifest read independently (30 lines). Root/Source, versioned Shared, interceptor, DLL feature wiring and Tracer manifests inspected as context. No configure/build.

## Checked
- Static target, public include root, C++20 inherited from root, Win7 PRIVATE platform definitions, public dependency propagation and Windows-only system libraries.
- `GLOB_RECURSE CONFIGURE_DEPENDS *.*` includes report Markdown as source-list items; it is broad but does not compile Markdown as C++. No build was run to assert generator behavior.
- TBB is restricted to Linux; non-Windows code guards were inspected incidentally. Imagehlp comes through the tracer dependency. No unsupported-MinGW/Linux runtime claim.

## Finding

### BASE-UTIL-015 — Version-sensitive loader source is compiled in the no-version target
- **Severity:** Informational
- **Confidence:** High
- **Category:** Build
- **Location:** `Source/Shared_NoVer/CMakeLists.txt:3-13`; `SharedLibUtils.cxx:99-118`
- **Affected scope:** Future REDGalaxy interceptor variants; no current generated SDK version enables RED. Same observation as SharedLibUtils.cxx, counted once outside confirmed-defect totals.

**Evidence / mechanism:** The glob includes SharedLibUtils.cxx in one common target, but its conditional RED basename needs a per-version feature. This target never receives `add_version_definitions_to`; definitions applied to consuming versioned targets cannot affect this object's preprocessing. Feature range evidence is `Source/galaxy_sdk_features.cmake:234`, with per-version definitions in `Source/DLLs/CMakeLists.txt:10-40`.

**Impact:** A future affected interceptor would look for the ordinary RealGalaxy DLL rather than RealREDGalaxy. All 69 current version directories fall outside the enabled interval 1.149.12–1.149.16; this is latent architectural debt, not a current-build failure.

**Possible fixes:** Compile version-dependent loader code per version, or inject the filename from a versioned caller. A global RED define cannot satisfy mixed-version builds.

**Recommended fix:** Keep platform loading generic and move basename selection across the versioned boundary as an explicit parameter.

**Verification:** In a future mixed RED/non-RED build, inspect compile commands and resolve each expected DLL name without renaming either real DLL. Not executed.
