# Review: `Source/DLLs`

## Scope and method

The repository contains 1,783 tracked SDK-tree files: 71 files under the
explicitly excluded `Source/DLLs/*/gog/**` paths and 1,712 non-GOG files. The
non-GOG set contains 1,381 generated C/C++ headers and implementations, 139
CMake manifests (the common manifest plus one `x86` and one `x64` manifest for
each of 69 version families), module definition files, and version-specific
factory/entrypoint sources.

The generated families were reviewed by representative and transition samples,
rather than by adding comments to every generated header:

- earliest family: `1.57.0`
- factory-to-DLL transition: `1.99.0` -> `1.121.2`
- service additions: `1.104.2` -> `1.104.3`, `1.121.2`, `1.134.8`
- latest family: `1.152.11`
- both `x86` and `x64` CMake/module-definition paths

The 69 families present are:

```text
1.57.0, 1.60.0, 1.61.0, 1.64.0, 1.66.0, 1.67.0, 1.68.0,
1.69.0, 1.70.0, 1.72.0, 1.73.0, 1.74.0, 1.75.0, 1.76.0,
1.77.0, 1.80.0, 1.87.0, 1.92.0, 1.95.0, 1.99.0, 1.100.2,
1.104.2, 1.104.3, 1.104.4, 1.106.0, 1.109.0, 1.112.2,
1.113.1, 1.113.3, 1.114.9, 1.121.2, 1.124.0, 1.125.2,
1.126.1, 1.127.0, 1.128.3, 1.130.0, 1.131.3, 1.132.1,
1.133.0, 1.133.6, 1.134.8, 1.134.9, 1.134.10, 1.135.0,
1.138.0, 1.139.2, 1.139.5, 1.139.6, 1.139.9, 1.140.0,
1.142.0, 1.144.1, 1.148.1, 1.148.2, 1.148.3, 1.148.5,
1.148.6, 1.148.7, 1.148.11, 1.148.14, 1.149.0, 1.150.0,
1.151.0, 1.152.1, 1.152.2, 1.152.6, 1.152.9, 1.152.11
```

## Findings

### Medium — generated resources are written into the source tree

The common `Source/DLLs/CMakeLists.txt` uses `configure_file()` to write
version resources below `Source/DLLs/<version>/<arch>`. This makes configuration
depend on checkout writability and leaves generated artifacts in the source
tree. The detailed finding and suggested build-tree fix are in
`Source/DLLs/CMakeLists.txt.review.md`.

### Low — SDK feature declarations can duplicate disabled definitions

The repeated feature ranges in `Source/galaxy_sdk_features.cmake` can append the
same disabled definition more than once in version gaps. The enabled feature
value was not found to be incorrectly overwritten; see that sidecar for the
bounded finding.

## Assessment

No additional high-confidence ABI or source defect was found in the
representative generated families. The visible export-set changes track SDK
surface growth across versions, so each version-specific module definition must
continue to be built with its matching headers and factory/entrypoint source.
Future SDK updates should rerun the transition comparison and verify both
architectures.

## Manifest count clarification

There are 138 version/architecture `CMakeLists.txt` files under
`Source/DLLs/<version>/<arch>/`, plus the common `Source/DLLs/CMakeLists.txt`
manifest: 139 CMake files in that tree. `Source/Vendor/galaxy.cmake` is a
separate SDK integration manifest, so the repository contains 140
SDK-related manifest files when that file is included. The 138 module
definition files are not CMake manifests.
