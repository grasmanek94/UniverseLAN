# Fresh baseline — execution and verification

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080` (`feature/fix-issues`). All in-scope tracked production inputs remained byte-identical to this commit. These are coordinator execution results; subsystem notebooks accurately describe the earlier static-only work performed by their respective reviewers.

## Environment

- Windows 10 host (build 19045), Windows SDK 10.0.26100.0.
- CMake 4.2.1, Visual Studio 18 2026 Professional, MSVC 19.51.36252.0 (toolset directory 14.51.36231).
- Build configuration executed: x64 Debug. No Linux build, x86 build, Release build, sanitizer run, vendor-native DLL runtime test or game compatibility run.
- Tests from the excluded old test trees were not reused or run. No credential files were opened or needed.

## Source and Git checks

`git fetch origin`, checkout/fast-forward pull of `feature/fix-issues`, and merge into `feature/ai-review` established baseline `b30e8387` in merge `40265aed`. Existing remote review history was retained so publishing uses a normal fast-forward push; old review content was removed/replaced, not carried into this assessment.

The following comparison returned no paths before and after builds/probes:

```powershell
git diff --name-only b30e83872c0006e8240c8b4f565da5351bf10080 -- Source CMakeLists.txt ':!*.review.MD'
```

The branch also inherits preexisting history outside this review scope. In particular its source baseline is established by the exact comparison above, not by pretending all repository history is identical to the source branch.

## Windows configure/build

Workdir: `C:\Development\AI\UL`. Build parent existence was checked first. This follows the repository's documented `cmake -A x64 -B ... -D LIMIT_VERSIONS=...` workflow with an isolated writable build tree and explicit generator/options.

```powershell
cmake -S . -B 'C:\Users\Rafal\AppData\Local\Temp\opencode\ul-baseline-b30e8387-x64' -G 'Visual Studio 18 2026' -A x64 '-DLIMIT_VERSIONS=1.139.2' -DBUILD_INTERCEPTOR=ON -DBUILD_ALL_TESTS=OFF -DBUILD_UNIVERSELAN_TEST_CASES=OFF -DBUILD_UNIVERSELAN_UNIT_TESTS=OFF -DBUILD_UNIVERSELAN_SYSTEM_TESTS=OFF -DBUILD_UNIVERSELAN_BEHAVIOUR_TESTS=OFF
cmake --build 'C:\Users\Rafal\AppData\Local\Temp\opencode\ul-baseline-b30e8387-x64' --config Debug --target universelan-client-x64-1.139.2 universelan-server-x64-1.139.2 universelan-interceptor-x64-1.139.2 --parallel 4
```

**Result: configure and all three builds succeeded.** Broader feature-gate concerns warranted the user-recommended representative matrix, covering code omitted by 1.139.2 (factory-era interfaces and modern cloud/thread/shutdown paths):

```powershell
cmake -S . -B 'C:\Users\Rafal\AppData\Local\Temp\opencode\ul-baseline-b30e8387-x64' -G 'Visual Studio 18 2026' -A x64 '-DLIMIT_VERSIONS=1.57.0,1.124.0,1.148.3,1.139.2,1.152.11' -DBUILD_INTERCEPTOR=ON -DBUILD_ALL_TESTS=OFF -DBUILD_UNIVERSELAN_TEST_CASES=OFF -DBUILD_UNIVERSELAN_UNIT_TESTS=OFF -DBUILD_UNIVERSELAN_SYSTEM_TESTS=OFF -DBUILD_UNIVERSELAN_BEHAVIOUR_TESTS=OFF
$targets = @()
foreach ($v in @('1.57.0','1.124.0','1.148.3','1.152.11')) {
    foreach ($component in @('client','server','interceptor')) {
        $targets += "universelan-$component-x64-$v"
    }
}
cmake --build 'C:\Users\Rafal\AppData\Local\Temp\opencode\ul-baseline-b30e8387-x64' --config Debug --target $targets --parallel 4 -- /verbosity:quiet /nologo
```

**Result: configure and the remaining 12 builds succeeded.** Existence checks confirmed Galaxy64.dll, UniverseLANServer64.exe and GalaxyInterceptor64.dll in `bin/<version>/Debug/` for every listed version (15 outputs). This is compilation/linkage evidence, not behavioral validation or proof of proprietary export availability.

Observed warnings: CMake dependency-policy deprecations and MSB8029 because this review deliberately used a temporary build directory. The first build generated the ignored version header and caused an expected CONFIGURE_DEPENDS rescan. Generated `.rc`, version header, build projects and bin outputs are not review-commit contents.

## Three focused runtime reproductions

A fresh, review-only probe was compiled outside the repository and linked to the just-built **actual** `universelan-common-shared-no-ver.lib`, using bundled cereal headers. This did not replace production methods with mirrored test implementations.

Source location during execution: `%LOCALAPPDATA%\Temp\opencode\ul-review-probes\shared-probes.cxx`. Compiler command after `vcvars64.bat`:

```text
cl /nologo /std:c++20 /EHsc /MDd /Zi /I"C:\Development\AI\UL\Source\Shared_NoVer" /I"C:\Development\AI\UL\Source\Vendor\cereal-1.3.2\include" shared-probes.cxx "C:\Users\Rafal\AppData\Local\Temp\opencode\ul-baseline-b30e8387-x64\Source\Shared_NoVer\Debug\universelan-common-shared-no-ver.lib" /Fe:shared-probes.exe /link /DEBUG
```

An initial inline `cmd /c` attempt had a shell quoting error before compilation. A small `build.cmd` containing `call vcvars64.bat` and the command above corrected that harness issue; compilation and execution then succeeded. No production change was needed.

### BASE-UTIL-001 — play-time serialization

Construct `AchievementsAndStatsContainer before`, call `SetPlayTime(123456)`, serialize through `cereal::PortableBinaryOutputArchive`, then deserialize the bytes through `PortableBinaryInputArchive` into a freshly constructed `after`. Include cereal chrono/string/unordered_map adapters and query both containers immediately.

### BASE-UTIL-007 — timestamp epoch

Create a fresh filesystem container and write `probe.bin` using its real `filesystem_entry::write`. Set its physical last-write time to `clock_cast<file_clock>(sys_seconds{seconds{1700000000}})`. Call the real `filesystem_entry::get_timestamp()` and compare with 1700000000.

### BASE-UTIL-006 — failed deletion/index divergence

Open that file with Windows `CreateFileW`, `GENERIC_READ`, sharing `FILE_SHARE_READ | FILE_SHARE_WRITE` but **not** FILE_SHARE_DELETE. Invoke the real `entry->unlink()`, test physical existence and call `store.get_file_count()`. Close the handle. The scratch directory was newly created under the approved temporary probe directory, not a user's storage directory.

Executed output:

```text
BASE-UTIL-001 before=123456 after=0
BASE-UTIL-007 expected=1700000000 actual=13344473600
BASE-UTIL-006 deleted=0 disk_exists=1 indexed_count=0
Three baseline defects reproduced; exit 0 means reproduction succeeded.
```

The probe exits nonzero on setup/compilation errors or if the observed baseline failure is not reproduced. **Its successful exit confirms the bugs; it is not a passing fixed-behavior regression test.** Counter loss, wrong epoch and index divergence are runtime-established. End-to-end game behavior and other findings remain static conclusions.

## Coverage and document verification

Run `python .ai/review-baseline/verify_review.py` from the root. The read-only checker derives the scope from the baseline Git tree, matches every input to one report, checks baseline markers, finding IDs/severity consistency, relative report links, whitespace and production-source integrity, then applies the exact alias map in RECONCILIATION.MD.

Expected final inventory: **529 source/build inputs, 529 sidecars**, no out-of-scope sidecars; 110 distinct IDs comprising 108 confirmed finding records and two informational investigations. Five exact aliases yield **103 actionable groups (21 High, 70 Medium, 12 Low), plus two informational groups**. Partial overlaps keep their independent mechanisms and are explained in RECONCILIATION.MD rather than silently discarded. The check verifies report accounting, not the completeness of semantic defect detection.

One ignored nested-vendor sidecar left by a superseded report-generation pass was discovered by whole-tree coverage checking and removed. Initial missing VERIFICATION.MD was resolved by this file. Final checker and Git whitespace results are recorded in the consolidated README.
