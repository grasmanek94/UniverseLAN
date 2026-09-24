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

## Thorough re-review addendum — BASE-UTIL-015 retained outside defect counts (2026-09-24)

The entire 30-line manifest was reread before findings. **BASE-UTIL-015 remains Informational / High confidence / Build**, shared with `SharedLibUtils.cxx.review.MD`; the current directory matrix still contains no RED-feature SDK. The root supplies C++20 and explicit MSVC x86/x64 selection (`CMakeLists.txt:7-9,46-51`), which is relevant to ADD-UTIL-005's x86 size narrowing. PRIVATE Win7 declarations in this target and the MSVC/PPL queue branch were checked; no Linux runtime assessment was performed.

Testing correction/context: `Source/UnitTests/CMakeLists.txt:5-38` lists the 21 Shared_NoVer test sources; versioned message tests are globbed and registered in `Source/UnitTests/Versioned.cmake:6-22`. Root test options default OFF (`CMakeLists.txt:14-29`). Thus test source/discovery exists, but this static review cannot claim those tests were executed or enforced in a particular build. The nonzero play-time serialization assertions are specifically documented under BASE-UTIL-001. No manifest changes, configure, build or test were performed. Full-filename injection and a future mixed RED/non-RED validation remain the original options/recommendation/verification for 015.
