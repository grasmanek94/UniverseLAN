# Follow-up review — local Windows verification

Production baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. These coordinator checks supplement the owners' earlier static-only notebooks. They exercise local C++ objects, callback dispatch, and temporary filesystem storage. No client/server session, adversarial traffic, external service, or credential was involved.

## What was executed

| Check | Observed result | Interpretation |
|---|---|---|
| Actual legacy SDK 1.73.0 plus production ListenerRegistrar | Both tags 26; one incompatible listener selected; one wrong leaderboard success delivered | ADD-ABI-001 wrong callback routing reproduced |
| Actual SharedFileUtils quota adapters with a deterministic space provider | Total and used both 4294967295; their difference 0; independent available result 4294967295 | ADD-STORAGE-003 arithmetic inconsistency reproduced |
| Actual filesystem container with two ordinary relative names | Second metadata save returned false | ADD-UTIL-006 namespace conflict reproduced |
| Actual presence container erasure followed by actual message string construction | MSVC ASan reported heap-use-after-free in strlen/string construction | ADD-API-001 mechanism reproduced; SDK-permitted borrowed-pointer alias use remains conditional |

The first three probes returned 0 **to indicate the expected baseline defect was observed**, not that corrected behavior passed. The ASan probe terminated with exit 1 and an error report, as expected. These are focused review reproductions, not an exhaustive sanitizer-clean test suite.

## Environment and instrumentation

- Windows x64 Debug; Visual Studio 18 2026/MSVC 19.51.36252.0, CMake 4.2.1, Windows SDK 10.0.26100.0.
- Probe sources and the CMake inclusion hook live outside the repository under `C:\Users\Rafal\AppData\Local\Temp\opencode\ul-addendum-probes`.
- Build tree: `C:\Users\Rafal\AppData\Local\Temp\opencode\ul-addendum-asan-x64`.
- The hook defines two review-only executables, links existing versioned production targets and inherits their real SDK include directories/feature flags. It adds no substitute registrar, SDK interfaces or filesystem implementation.
- C++ dependencies were consistently compiled with `/fsanitize=address`. Debug `/RTC1` was omitted, `/Zi` retained, and probe executables linked with `/INCREMENTAL:NO`. RTTI and standard exception unwinding were retained with `/GR /EHsc`.
- C vendor libraries were not globally ASan-instrumented; the probes do not exercise networking. No claim is made that every production binary or execution path was sanitizer-tested.
- The ASan runtime directory was added only to the executing tool process's PATH. No machine/global environment or Git configuration was changed.

## Build configuration

The effective successful configuration, combining the recorded command-line adjustments, was:

```powershell
cmake -S . -B 'C:\Users\Rafal\AppData\Local\Temp\opencode\ul-addendum-asan-x64' -G 'Visual Studio 18 2026' -A x64 '-DLIMIT_VERSIONS=1.73.0,1.152.11' -DBUILD_INTERCEPTOR=OFF -DBUILD_ALL_TESTS=OFF -DBUILD_UNIVERSELAN_TEST_CASES=OFF -DBUILD_UNIVERSELAN_UNIT_TESTS=OFF -DBUILD_UNIVERSELAN_SYSTEM_TESTS=OFF -DBUILD_UNIVERSELAN_BEHAVIOUR_TESTS=OFF '-DCMAKE_CXX_FLAGS_DEBUG=/Zi /Ob0 /Od' '-DCMAKE_C_FLAGS_DEBUG=/Zi /Ob0 /Od' '-DCMAKE_CXX_FLAGS=/DWIN32 /D_WINDOWS /W3 /GR /EHsc /fsanitize=address' '-DCMAKE_PROJECT_INCLUDE=C:/Users/Rafal/AppData/Local/Temp/opencode/ul-addendum-probes/inject.cmake' '-DREVIEW_OLD_SDK:STRING=1.73.0' '-DREVIEW_NEW_SDK:STRING=1.152.11'
cmake --build 'C:\Users\Rafal\AppData\Local\Temp\opencode\ul-addendum-asan-x64' --config Debug --target review_legacy_listener review_shared_cases --parallel 4 -- /verbosity:quiet /nologo
```

The SDK arguments are inputs to a generic external hook, not hardcoded production CMake targets. No repository source or build definition was modified.

### Harness setup failures, explicitly separated from project findings

1. The first invocation left two dotted SDK `-D` values unquoted in PowerShell. They were split, producing an incorrect dependency name and a missing include. Quoting the full definitions corrected this setup error.
2. Initially instrumenting only selected libraries caused MSVC `annotate_string/vector/optional` link mismatches with the uninstrumented tracer. Consistent C++ instrumentation resolved them.
3. A temporary override of CMAKE_CXX_FLAGS omitted the normal `/EHsc` flag, causing unwind warnings and a Boost throw-exception link error. Restoring the standard flags alongside ASan corrected this. These failed attempts were not treated as production defects and no probe ran from them.

The final configure and both probe builds succeeded. Remaining diagnostics were temporary-directory MSB8029 and existing vendor conversion/deprecation warnings. The existing production five-version build was not repeated as a separate validation exercise.

## Probe details and actual output

### Legacy listener routing

`review_legacy_listener` includes the real `Impl/ListenerRegistrar.hxx` and selected `IStats.h`, and links `universelan-lib-x64-1.73.0`. A plain manually registered leaderboard listener stays alive through dispatch and unregistration. Its callbacks only increment counters; they do not inspect the misdelivered argument. The actual registrar is asked to deliver a time-played success, matching the callback type used by Stats.

```text
leaderboard_tag=26 playtime_tag=26 incompatible_matches=1
wrong_leaderboard_success_calls=1
probe_exit=0
```

The incompatible-match counter uses dynamic_cast as an independent observation, not as a replacement for production dispatch. The wrong-callback count comes from the actual production `NotifyAllNow`. Full Init/SignIn/Stats/ProcessData was not executed; its route to this dispatcher is source-traced in ABI.MD. Other affected legacy versions and x86 remain static analysis.

### Quota adapter

The probe uses a filesystem-container subclass overriding the existing virtual space-query methods with 100 GiB total, 20 GiB used and 80 GiB available. The production SharedFileUtils adapters perform all narrowing/clamping.

```text
reported_total=4294967295 reported_used=4294967295 computed_free=0 available_helper=4294967295
probe_exit=0
```

This demonstrates the exact adapter pair used by CloudStorage's listing callback. It does not claim that a full game declined a save. No real volume was filled or resized.

### Metadata namespace

In a new temporary container, save data and a metadata tag for `save`. Then create data and a tag for `save.metadata/part` and call the real `save_metadata`. The metadata representation requires the same filesystem component to be both file and directory.

```text
second_metadata_saved=0
probe_exit=0
```

The first save was checked for success. No permissions, disk-full condition or concurrent operation was needed. The actual observed second operation returned false rather than throwing; the report permits either failure mechanism in other filesystem states.

### Borrowed-key mechanism under ASan

Using a real AchievementsAndStatsContainer, add a short key, obtain its map-owned c_str through the actual locked accessor, erase it through the real EraseRichPresence, then construct the real RichPresenceChangeMessage from that saved pointer. This isolates the erase-then-copy sequence in Friends::DeleteRichPresence; it is not a full public Friends call.

Relevant diagnostic excerpt, with process addresses omitted:

```text
ERROR: AddressSanitizer: heap-use-after-free
READ of size 1, thread T0
  strlen
  std::_Narrow_char_traits<char, int>::length
  std::basic_string<char>::basic_string(char const*)
  main: shared_cases.cxx:29
freed by:
  universelan::AchievementsAndStatsContainer::EraseRichPresence
  AchievementsAndStatsContainer.cxx:162
previously allocated by:
  universelan::AchievementsAndStatsContainer::SetRichPresence
  AchievementsAndStatsContainer.cxx:152
ABORTING
probe_exit=1
```

This establishes local allocation lifetime failure for that sequence. It does not settle the SDK's undocumented borrowed-key aliasing permission, so ADD-API-001 stays a conditional investigation outside confirmed totals. Snapshotting the key before erasure is the straightforward defensive remedy.

## Limits and integrity

No whole-suite ASan, ThreadSanitizer, UBSan, Application Verifier, Page Heap, Release, x86, native-GOG, service or game test is claimed. The remaining concurrency and callback scenarios are source-supported findings with proposed focused regressions. No machine-wide diagnostic configuration was changed.

`git diff --name-only b30e83872c0006e8240c8b4f565da5351bf10080 -- Source CMakeLists.txt ':!*.review.MD'` stayed empty. Probe files/artifacts and generated build outputs remain outside the review documents. Review coverage, links, metadata and ID accounting are checked separately by `.ai/review-baseline/verify_review.py`; semantic coverage is supported by the owner ledgers, not inferred from a script counting files.
