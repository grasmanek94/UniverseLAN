# Fresh baseline review — Client/CMakeLists.txt

- Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`.
- Coverage: entire file, lines 1–25; static build-graph review only.

## Specific checked notes

- Traced `define_client` from the DLL version-project factory. Each requested version receives a distinct static implementation target and feature definitions through `add_version_definitions_to`.
- Checked public include paths, the `CLIENT` definition, and transitive SDK/ENet/tracer dependencies through `universelan-common-shared-${GALAXY_VERSION}`. The generic delay/parameter helpers come from `universelan-lib-no-ver`.
- Root CMake sets C++20, matching concepts, `bind_front`, and formatting use in the inspected implementation. This manifest alone is not a standalone build entry point.
- `Factory.cxx` is excluded from unity inclusion when experimental unity mode is enabled; this is appropriate given its public wrappers and the historical SDK's header-local static wrapper definitions.
- Recursive `*.*` globs also collect documentation sidecars as project inputs; no unsupported-extension compilation failure is established from that alone. Source inventory is broad and configure-dependent.

## Findings and limits

No confirmed defect in this manifest. No CMake configure, build, link, unity build, x86/x64 export inspection, or dependency acquisition was executed. Root/version/SDK manifests were read as dependency context, not counted as owned coverage.
