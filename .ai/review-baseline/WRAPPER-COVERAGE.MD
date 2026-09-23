# Per-version DLL wrapper coverage

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`.

Mechanical reporting of the coordinator's fresh inspection of all 244 inputs. Each input below has a newly authored adjacent sidecar at `<input>.review.MD`, with its exact input path, full baseline SHA, role, evidence, and result. No old reports were used.

## Counts and methods

| Input class | Paths | Distinct blobs | Reporting evidence |
| --- | ---: | ---: | --- |
| Empty markers: 30 Factory.cxx + 39 Dll.cxx | 69 | 1 | Baseline tree membership; zero-byte blob confirmed with git cat-file |
| Architecture dispatchers: 69 x86 + 69 x64 | 138 | 1 | Baseline tree membership; shared blob content confirmed; representative file read |
| Compatibility manifests | 37 | 36 | Every small file read individually; exact tokens and source order rendered |
| Total | 244 | 38 | 207 paths covered by two proven byte-equivalence classes; 37 individual manifest reads |

- Empty-marker blob: `e69de29bb2d1d6434b8b29ae775ad8c2e48c5391` (0 bytes). Filename/context distinguishes factory-era markers through `1.114.9` from direct-DLL markers starting at `1.121.2`; byte equality does not erase that role distinction.
- Dispatcher blob: `2ea4783757bd44da55a293d7c6404e10ec8d0894`. Its two commands are `cmake_minimum_required(VERSION 3.12)` and `add_universelan_executables(${GALAXY_VERSION_NUMBER})`, separated by a blank line. Each invokes the shared generator with the inherited version in the selected x86/x64 architecture context.
- Manifest blobs: 35 singleton classes and one two-path class. The `1.139.2` and `1.139.5` manifests share `576e2b84b7955b91bf86d1159071dee71ea5ee65`; both were still read individually. Each sidecar records its manifest's full blob ID.
- The coordinator individually inspected all manifests using grep/read. This reporting pass read all 37 again for accurate token rendering. They express human compatibility hypotheses, not build inputs. In-tree CMake does not parse the `1.149.0` list or its literal `1.150.0?` entry.
- All 244 working-tree inputs were checked with read-only `git hash-object` against the baseline tree: 0 blob mismatches.
- Coordinator result: no direct confirmed defects in these 244 inputs. Global generation issues are located in `Source/DLLs/CMakeLists.txt.review.MD`.
- Compatibility binaries were not executed; binary compatibility is unverified. No builds or Git writes were performed.

## Coverage differences

| Comparison | Missing | Extra |
| --- | ---: | ---: |
| Baseline scope versus exact input list below | 0 | 0 |
| Expected adjacent sidecars versus newly created per-version sidecars | 0 | 0 |

244 unique inputs, 244 new sidecars, and this one coverage ledger (245 new reporting files). The path list is restricted to per-version markers, x86/x64 dispatchers, and compatibility manifests.

## Exact input paths: 69 empty markers

```text
Source/DLLs/1.57.0/Factory.cxx
Source/DLLs/1.60.0/Factory.cxx
Source/DLLs/1.61.0/Factory.cxx
Source/DLLs/1.64.0/Factory.cxx
Source/DLLs/1.66.0/Factory.cxx
Source/DLLs/1.67.0/Factory.cxx
Source/DLLs/1.68.0/Factory.cxx
Source/DLLs/1.69.0/Factory.cxx
Source/DLLs/1.70.0/Factory.cxx
Source/DLLs/1.72.0/Factory.cxx
Source/DLLs/1.73.0/Factory.cxx
Source/DLLs/1.74.0/Factory.cxx
Source/DLLs/1.75.0/Factory.cxx
Source/DLLs/1.76.0/Factory.cxx
Source/DLLs/1.77.0/Factory.cxx
Source/DLLs/1.80.0/Factory.cxx
Source/DLLs/1.87.0/Factory.cxx
Source/DLLs/1.92.0/Factory.cxx
Source/DLLs/1.95.0/Factory.cxx
Source/DLLs/1.99.0/Factory.cxx
Source/DLLs/1.100.2/Factory.cxx
Source/DLLs/1.104.2/Factory.cxx
Source/DLLs/1.104.3/Factory.cxx
Source/DLLs/1.104.4/Factory.cxx
Source/DLLs/1.106.0/Factory.cxx
Source/DLLs/1.109.0/Factory.cxx
Source/DLLs/1.112.2/Factory.cxx
Source/DLLs/1.113.1/Factory.cxx
Source/DLLs/1.113.3/Factory.cxx
Source/DLLs/1.114.9/Factory.cxx
Source/DLLs/1.121.2/Dll.cxx
Source/DLLs/1.124.0/Dll.cxx
Source/DLLs/1.125.2/Dll.cxx
Source/DLLs/1.126.1/Dll.cxx
Source/DLLs/1.127.0/Dll.cxx
Source/DLLs/1.128.3/Dll.cxx
Source/DLLs/1.130.0/Dll.cxx
Source/DLLs/1.131.3/Dll.cxx
Source/DLLs/1.132.1/Dll.cxx
Source/DLLs/1.133.0/Dll.cxx
Source/DLLs/1.133.6/Dll.cxx
Source/DLLs/1.134.8/Dll.cxx
Source/DLLs/1.134.9/Dll.cxx
Source/DLLs/1.134.10/Dll.cxx
Source/DLLs/1.135.0/Dll.cxx
Source/DLLs/1.138.0/Dll.cxx
Source/DLLs/1.139.2/Dll.cxx
Source/DLLs/1.139.5/Dll.cxx
Source/DLLs/1.139.6/Dll.cxx
Source/DLLs/1.139.9/Dll.cxx
Source/DLLs/1.140.0/Dll.cxx
Source/DLLs/1.142.0/Dll.cxx
Source/DLLs/1.144.1/Dll.cxx
Source/DLLs/1.148.1/Dll.cxx
Source/DLLs/1.148.2/Dll.cxx
Source/DLLs/1.148.3/Dll.cxx
Source/DLLs/1.148.5/Dll.cxx
Source/DLLs/1.148.6/Dll.cxx
Source/DLLs/1.148.7/Dll.cxx
Source/DLLs/1.148.11/Dll.cxx
Source/DLLs/1.148.14/Dll.cxx
Source/DLLs/1.149.0/Dll.cxx
Source/DLLs/1.150.0/Dll.cxx
Source/DLLs/1.151.0/Dll.cxx
Source/DLLs/1.152.1/Dll.cxx
Source/DLLs/1.152.2/Dll.cxx
Source/DLLs/1.152.6/Dll.cxx
Source/DLLs/1.152.9/Dll.cxx
Source/DLLs/1.152.11/Dll.cxx
```

## Exact input paths: 138 architecture dispatchers

```text
Source/DLLs/1.57.0/x86/CMakeLists.txt
Source/DLLs/1.57.0/x64/CMakeLists.txt
Source/DLLs/1.60.0/x86/CMakeLists.txt
Source/DLLs/1.60.0/x64/CMakeLists.txt
Source/DLLs/1.61.0/x86/CMakeLists.txt
Source/DLLs/1.61.0/x64/CMakeLists.txt
Source/DLLs/1.64.0/x86/CMakeLists.txt
Source/DLLs/1.64.0/x64/CMakeLists.txt
Source/DLLs/1.66.0/x86/CMakeLists.txt
Source/DLLs/1.66.0/x64/CMakeLists.txt
Source/DLLs/1.67.0/x86/CMakeLists.txt
Source/DLLs/1.67.0/x64/CMakeLists.txt
Source/DLLs/1.68.0/x86/CMakeLists.txt
Source/DLLs/1.68.0/x64/CMakeLists.txt
Source/DLLs/1.69.0/x86/CMakeLists.txt
Source/DLLs/1.69.0/x64/CMakeLists.txt
Source/DLLs/1.70.0/x86/CMakeLists.txt
Source/DLLs/1.70.0/x64/CMakeLists.txt
Source/DLLs/1.72.0/x86/CMakeLists.txt
Source/DLLs/1.72.0/x64/CMakeLists.txt
Source/DLLs/1.73.0/x86/CMakeLists.txt
Source/DLLs/1.73.0/x64/CMakeLists.txt
Source/DLLs/1.74.0/x86/CMakeLists.txt
Source/DLLs/1.74.0/x64/CMakeLists.txt
Source/DLLs/1.75.0/x86/CMakeLists.txt
Source/DLLs/1.75.0/x64/CMakeLists.txt
Source/DLLs/1.76.0/x86/CMakeLists.txt
Source/DLLs/1.76.0/x64/CMakeLists.txt
Source/DLLs/1.77.0/x86/CMakeLists.txt
Source/DLLs/1.77.0/x64/CMakeLists.txt
Source/DLLs/1.80.0/x86/CMakeLists.txt
Source/DLLs/1.80.0/x64/CMakeLists.txt
Source/DLLs/1.87.0/x86/CMakeLists.txt
Source/DLLs/1.87.0/x64/CMakeLists.txt
Source/DLLs/1.92.0/x86/CMakeLists.txt
Source/DLLs/1.92.0/x64/CMakeLists.txt
Source/DLLs/1.95.0/x86/CMakeLists.txt
Source/DLLs/1.95.0/x64/CMakeLists.txt
Source/DLLs/1.99.0/x86/CMakeLists.txt
Source/DLLs/1.99.0/x64/CMakeLists.txt
Source/DLLs/1.100.2/x86/CMakeLists.txt
Source/DLLs/1.100.2/x64/CMakeLists.txt
Source/DLLs/1.104.2/x86/CMakeLists.txt
Source/DLLs/1.104.2/x64/CMakeLists.txt
Source/DLLs/1.104.3/x86/CMakeLists.txt
Source/DLLs/1.104.3/x64/CMakeLists.txt
Source/DLLs/1.104.4/x86/CMakeLists.txt
Source/DLLs/1.104.4/x64/CMakeLists.txt
Source/DLLs/1.106.0/x86/CMakeLists.txt
Source/DLLs/1.106.0/x64/CMakeLists.txt
Source/DLLs/1.109.0/x86/CMakeLists.txt
Source/DLLs/1.109.0/x64/CMakeLists.txt
Source/DLLs/1.112.2/x86/CMakeLists.txt
Source/DLLs/1.112.2/x64/CMakeLists.txt
Source/DLLs/1.113.1/x86/CMakeLists.txt
Source/DLLs/1.113.1/x64/CMakeLists.txt
Source/DLLs/1.113.3/x86/CMakeLists.txt
Source/DLLs/1.113.3/x64/CMakeLists.txt
Source/DLLs/1.114.9/x86/CMakeLists.txt
Source/DLLs/1.114.9/x64/CMakeLists.txt
Source/DLLs/1.121.2/x86/CMakeLists.txt
Source/DLLs/1.121.2/x64/CMakeLists.txt
Source/DLLs/1.124.0/x86/CMakeLists.txt
Source/DLLs/1.124.0/x64/CMakeLists.txt
Source/DLLs/1.125.2/x86/CMakeLists.txt
Source/DLLs/1.125.2/x64/CMakeLists.txt
Source/DLLs/1.126.1/x86/CMakeLists.txt
Source/DLLs/1.126.1/x64/CMakeLists.txt
Source/DLLs/1.127.0/x86/CMakeLists.txt
Source/DLLs/1.127.0/x64/CMakeLists.txt
Source/DLLs/1.128.3/x86/CMakeLists.txt
Source/DLLs/1.128.3/x64/CMakeLists.txt
Source/DLLs/1.130.0/x86/CMakeLists.txt
Source/DLLs/1.130.0/x64/CMakeLists.txt
Source/DLLs/1.131.3/x86/CMakeLists.txt
Source/DLLs/1.131.3/x64/CMakeLists.txt
Source/DLLs/1.132.1/x86/CMakeLists.txt
Source/DLLs/1.132.1/x64/CMakeLists.txt
Source/DLLs/1.133.0/x86/CMakeLists.txt
Source/DLLs/1.133.0/x64/CMakeLists.txt
Source/DLLs/1.133.6/x86/CMakeLists.txt
Source/DLLs/1.133.6/x64/CMakeLists.txt
Source/DLLs/1.134.8/x86/CMakeLists.txt
Source/DLLs/1.134.8/x64/CMakeLists.txt
Source/DLLs/1.134.9/x86/CMakeLists.txt
Source/DLLs/1.134.9/x64/CMakeLists.txt
Source/DLLs/1.134.10/x86/CMakeLists.txt
Source/DLLs/1.134.10/x64/CMakeLists.txt
Source/DLLs/1.135.0/x86/CMakeLists.txt
Source/DLLs/1.135.0/x64/CMakeLists.txt
Source/DLLs/1.138.0/x86/CMakeLists.txt
Source/DLLs/1.138.0/x64/CMakeLists.txt
Source/DLLs/1.139.2/x86/CMakeLists.txt
Source/DLLs/1.139.2/x64/CMakeLists.txt
Source/DLLs/1.139.5/x86/CMakeLists.txt
Source/DLLs/1.139.5/x64/CMakeLists.txt
Source/DLLs/1.139.6/x86/CMakeLists.txt
Source/DLLs/1.139.6/x64/CMakeLists.txt
Source/DLLs/1.139.9/x86/CMakeLists.txt
Source/DLLs/1.139.9/x64/CMakeLists.txt
Source/DLLs/1.140.0/x86/CMakeLists.txt
Source/DLLs/1.140.0/x64/CMakeLists.txt
Source/DLLs/1.142.0/x86/CMakeLists.txt
Source/DLLs/1.142.0/x64/CMakeLists.txt
Source/DLLs/1.144.1/x86/CMakeLists.txt
Source/DLLs/1.144.1/x64/CMakeLists.txt
Source/DLLs/1.148.1/x86/CMakeLists.txt
Source/DLLs/1.148.1/x64/CMakeLists.txt
Source/DLLs/1.148.2/x86/CMakeLists.txt
Source/DLLs/1.148.2/x64/CMakeLists.txt
Source/DLLs/1.148.3/x86/CMakeLists.txt
Source/DLLs/1.148.3/x64/CMakeLists.txt
Source/DLLs/1.148.5/x86/CMakeLists.txt
Source/DLLs/1.148.5/x64/CMakeLists.txt
Source/DLLs/1.148.6/x86/CMakeLists.txt
Source/DLLs/1.148.6/x64/CMakeLists.txt
Source/DLLs/1.148.7/x86/CMakeLists.txt
Source/DLLs/1.148.7/x64/CMakeLists.txt
Source/DLLs/1.148.11/x86/CMakeLists.txt
Source/DLLs/1.148.11/x64/CMakeLists.txt
Source/DLLs/1.148.14/x86/CMakeLists.txt
Source/DLLs/1.148.14/x64/CMakeLists.txt
Source/DLLs/1.149.0/x86/CMakeLists.txt
Source/DLLs/1.149.0/x64/CMakeLists.txt
Source/DLLs/1.150.0/x86/CMakeLists.txt
Source/DLLs/1.150.0/x64/CMakeLists.txt
Source/DLLs/1.151.0/x86/CMakeLists.txt
Source/DLLs/1.151.0/x64/CMakeLists.txt
Source/DLLs/1.152.1/x86/CMakeLists.txt
Source/DLLs/1.152.1/x64/CMakeLists.txt
Source/DLLs/1.152.2/x86/CMakeLists.txt
Source/DLLs/1.152.2/x64/CMakeLists.txt
Source/DLLs/1.152.6/x86/CMakeLists.txt
Source/DLLs/1.152.6/x64/CMakeLists.txt
Source/DLLs/1.152.9/x86/CMakeLists.txt
Source/DLLs/1.152.9/x64/CMakeLists.txt
Source/DLLs/1.152.11/x86/CMakeLists.txt
Source/DLLs/1.152.11/x64/CMakeLists.txt
```

## Exact input paths: 37 compatibility manifests

```text
Source/DLLs/1.60.0/compat_list.txt
Source/DLLs/1.64.0/compat_list.txt
Source/DLLs/1.66.0/compat_list.txt
Source/DLLs/1.72.0/compat_list.txt
Source/DLLs/1.80.0/compat_list.txt
Source/DLLs/1.87.0/compat_list.txt
Source/DLLs/1.92.0/compat_list.txt
Source/DLLs/1.95.0/compat_list.txt
Source/DLLs/1.100.2/compat_list.txt
Source/DLLs/1.104.2/compat_list.txt
Source/DLLs/1.104.4/compat_list.txt
Source/DLLs/1.106.0/compat_list.txt
Source/DLLs/1.112.2/compat_list.txt
Source/DLLs/1.113.1/compat_list.txt
Source/DLLs/1.113.3/compat_list.txt
Source/DLLs/1.114.9/compat_list.txt
Source/DLLs/1.121.2/compat_list.txt
Source/DLLs/1.124.0/compat_list.txt
Source/DLLs/1.125.2/compat_list.txt
Source/DLLs/1.126.1/compat_list.txt
Source/DLLs/1.128.3/compat_list.txt
Source/DLLs/1.130.0/compat_list.txt
Source/DLLs/1.131.3/compat_list.txt
Source/DLLs/1.132.1/compat_list.txt
Source/DLLs/1.133.6/compat_list.txt
Source/DLLs/1.134.8/compat_list.txt
Source/DLLs/1.138.0/compat_list.txt
Source/DLLs/1.139.2/compat_list.txt
Source/DLLs/1.139.5/compat_list.txt
Source/DLLs/1.139.9/compat_list.txt
Source/DLLs/1.142.0/compat_list.txt
Source/DLLs/1.144.1/compat_list.txt
Source/DLLs/1.148.1/compat_list.txt
Source/DLLs/1.148.3/compat_list.txt
Source/DLLs/1.148.7/compat_list.txt
Source/DLLs/1.148.11/compat_list.txt
Source/DLLs/1.149.0/compat_list.txt
```
