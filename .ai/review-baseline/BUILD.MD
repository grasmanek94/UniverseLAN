# BUILD — fresh baseline review

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. 260/260 assigned input files reviewed. No independent confirmed build-manifest defect was established in the current valid Windows configurations. This is not a guarantee of all-version or all-toolchain compatibility.

## Exact coverage

These 16 control inputs were fully read:

- `CMakeLists.txt`
- `Source/CMakeLists.txt`
- `Source/galaxy_sdk_features.cmake`
- `Source/DLLs/CMakeLists.txt`
- `Source/DLLs/determine_galaxy_version_feature_definitions.cmake`
- `Source/Vendor/CMakeLists.txt`
- `Source/Vendor/cereal.cmake`
- `Source/Vendor/galaxy.cmake`
- `Source/Vendor/ixwebsocket.cmake`
- `Source/Vendor/ixwebsocket-mbedtls.cmake`
- `Source/Vendor/ixwebsocket-zlib.cmake`
- `Source/Vendor/json.cmake`
- `Source/Vendor/magic_enum.cmake`
- `Source/Vendor/miniz-cpp.cmake`
- `Source/Vendor/simpleini.cmake`
- `Source/Vendor/unet.cmake`

The other **244 individually listed inputs** are in [WRAPPER-COVERAGE.MD](WRAPPER-COVERAGE.MD): 69 empty factory/direct markers, 138 identical x86/x64 dispatchers and 37 compatibility lists. Git blob identity proves the wrapper/dispatcher equivalence classes; all distinct content and all manifest entries were inspected. Their 244 individual sidecars identify the source path, baseline, role, method and limits. Thus repetitive files are covered by verified identity, not unverified sampling.

## Architecture and findings disposition

The root establishes C++20, host architecture and selected-version policy. Source first registers common/vendor targets and per-version definition functions; DLL discovery instantiates them through identical architecture dispatchers. Per-version SDK include paths/definitions propagate PUBLIC into the correct implementation. No production CMake change or hardcoded target was introduced.

The in-tree dependency bridge avoids runtime download/version drift and compiled successfully with the installed Windows toolchain. Runtime and interface feature errors may still exist despite successful compilation (notably BASE-INTERCEPT-006/007). The versioned/no-version split must not hide features in a once-compiled object; the current RED-branch example is dormant because no present SDK directory enables it.

Source-tree generated resources/header files and ROOT/bin deployment are intentional conventions. They limit read-only/concurrent build use, but the requested writable checkout and documented output paths work. Human compatibility lists are not parsed by the build; no failure is invented for uncertainty annotations. Optional old test configurations and experimental unity remain unexecuted.

## Actual verification

Windows 10 host, CMake 4.2.1, Visual Studio 18 2026, MSVC 19.51.36252.0, Windows SDK 10.0.26100.0. Initial 1.139.2 x64 Debug client/server/interceptor build succeeded. Then the recommended five-version matrix was configured; the remaining four versions' three production targets also compiled and linked successfully. This exercises factory, early game-server, mature networking and newest cloud/thread/shutdown branches; it does not prove dynamically loaded proprietary exports or game behavior.

No Linux build. x86, Release, all 69 SDK variants, old tests, sanitizers, CI workflows and excluded tooling were not executed/reviewed beyond stated context. MSB8029 warnings came from the chosen temporary build directory; CMake dependency-policy notices were warnings. See [VERIFICATION.MD](VERIFICATION.MD) for exact commands and results.
