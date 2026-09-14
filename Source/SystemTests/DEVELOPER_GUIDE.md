# SystemTests Developer Guide

Use SystemTests when changing observable UniverseLAN Galaxy behavior across a
real client DLL, and, where needed, the matching local server. The default and
registered suite is `universelan`; it needs no real credentials or internet.
Read [`SYSTEM_TEST_PLAN.md`](SYSTEM_TEST_PLAN.md) for the complete framework
contract and the coverage registers before choosing a new scenario.

## Build And Run

Prerequisites: CMake 3.16+, a supported C++20 toolchain, the selected SDK
version under `Source/DLLs/<version>/`, and its matching client/server targets.
On Windows, select the architecture with the CMake generator platform. Keep
each architecture and version set in a separate build directory.

Configure a single-version x64 system-test build, then build it:

```powershell
cmake -S . -B cmake-system-1392-vs18-x64 -G "Visual Studio 18 2026" -A x64 -D BUILD_UNIVERSELAN_SYSTEM_TESTS=ON -D LIMIT_VERSIONS="1.139.2"
cmake --build cmake-system-1392-vs18-x64 --config Debug
```

Use a comma-separated `LIMIT_VERSIONS` value for a compatibility set; CMake
creates one runner and one host target per selected SDK version.

```powershell
cmake -S . -B cmake-system-matrix-vs18-x64 -G "Visual Studio 18 2026" -A x64 -D BUILD_UNIVERSELAN_SYSTEM_TESTS=ON -D LIMIT_VERSIONS="1.125.2,1.139.2,1.152.11"
cmake --build cmake-system-matrix-vs18-x64 --config Debug
```

`BUILD_ALL_TESTS=ON` also enables SystemTests, but use the dedicated option for
a focused system-test build. CMake only registers scenarios whose required
version features, architecture, and selected-version gates are available.

List, run the selected suite, or run one test by its generated name:

```powershell
ctest --test-dir cmake-system-1392-vs18-x64 -C Debug -N -L system
ctest --test-dir cmake-system-1392-vs18-x64 -C Debug --output-on-failure -L system
ctest --test-dir cmake-system-1392-vs18-x64 -C Debug --output-on-failure -R '^universelan-system-chat-room-message-delivery-x64-1\.139\.2$'
```

All registered tests have the `system` label, are serial, and share the
`universelan-system-network` resource lock. Do not try to parallelize the
suite by bypassing CTest.

## Credentials And Providers

UniverseLAN scenarios call local `SignInGalaxy` and do not need real GOG
credentials. Never put logins, passwords, client secrets, or arbitrary INI
settings in a manifest, command line, event, log, or committed file.

The optional ignored local file is `Source/TestCommon/credentials.cmake`; it
may define the two named profiles `user1` and `user2` plus the Galaxy client
credentials. A manifest may select only one of those profile tokens through
`identity.credentialProfile`. Treat the local file and all generated failure
directories as secret-bearing material; do not attach or commit them.

`runtimeProvider: "gog"` is opt-in only. It is not registered as CTest. It
requires the matching official runtime artifacts in
`Source/DLLs/<version>/gog/`, local credentials, an authenticated GOG Galaxy
environment, and network access. A GOG scenario cannot declare a UniverseLAN
server. The supplied `Scenarios/gog-credential-sign-in.example.json` is an
unregistered shape example; missing runtime artifacts produce a skip, not a
UniverseLAN failure.

## Framework Layout

`CMakeLists.txt` creates version- and architecture-specific host and runner
targets, and registers CTest tests. `Scenarios/*.json` declares topology and
safe configuration only. `Runner/` validates manifests, writes isolated files,
stages the selected DLL next to each host, starts processes, and interprets the
protocol. `Host/` contains the version-aware Galaxy API assertions. `Common/`
contains the narrow shared protocol and validation helpers.

For a run, the runner creates `%TEMP%\universelan-system-tests\<scenario>-<id>`
with `server/`, one directory per host role, and `control/`. Each process gets
its own working directory, generated `UniverseLAN.ini`, and private data path.
The runner uses loopback and selected ports, disables tracing and console
interaction, and stages the selected host executable and runtime DLL together.
Successful roots are removed; failed roots are retained.

## Add Or Change A Scenario

1. Define one observable behavior and its version-specific API contract. Reuse
   a nearby manifest and host implementation rather than testing internal
   details or timing sleeps.
2. Add the host behavior in the relevant `Host/*.cxx` unit. It must pump to a
   bounded deadline and emit exactly the declared `SYSTEM_TEST` events and one
   terminal PASS or FAIL.
3. Add `Scenarios/<name>.json`. Use `runtimeProvider: "universelan"` unless
   intentionally performing the manual official-provider work described above.
   Declare a server only when the contract needs one; a runner-owned loopback
   WebSocket is available through the constrained `websocket` block.
4. Choose runner gates by the ordering required by the behavior. `waitFor`
   delays a host's release until declared events exist. Have a host emit a
   `signals` event after listener/setup readiness. Use `actionAfter` when a
   running host must wait before performing a mutation, and `finishAfter` when
   a host must remain alive until a remote assertion completes. Every referenced
   event must be declared once; use events instead of arbitrary delays.
5. Register the CTest in `CMakeLists.txt` under the narrowest correct feature,
   SDK-version, and architecture gates. Follow existing `add_test` arguments
   and properties, including `LABELS system`, `RUN_SERIAL`, the resource lock,
   timeout, and skip expression. Do not add a hard-coded target for one SDK.
6. Let the runner generate configuration. Manifests may use only validated
   server settings, identities, `apps`, and `telemetry` fields. Do not copy
   repository configs, create shared paths, or add arbitrary INI injection.

`persistenceGroup` is only for a fresh-process persistence contract. Every
member must set `saveAchievementsAndStats: true`, use the same group and same
identity, and appears in execution order. Later members start only after every
earlier member in that group PASSes and exits successfully. All other hosts
must have distinct identities and private data paths.

## Diagnose Failures

Run the exact CTest name with `--output-on-failure`. A runner failure reports
`runDirectory=...`; inspect that retained root's `server/stdout.log` and each
`<role>/stdout.log`, generated configuration, `role.json`, and `control/`
files. `SYSTEM_TEST FAIL role=...` identifies a host assertion; malformed
events, duplicate PASS, a child exit, server exit, or deadline expiry fail the
runner. A successful run intentionally leaves no directory.

## Completion Checklist

- Update `SYSTEM_TEST_COVERAGE.md` with the behavior and supported matrix.
- Update `SYSTEM_TEST_FILE_COVERAGE.md` with the directly asserted production
  files, and `SYSTEM_TEST_GALAXY_API_COVERAGE.md` when interface coverage
  changes.
- Record a discovered product defect or its resolved regression in
  `FOUND_DEFECTS.md`; do not describe a test-only limitation as a product fix.
- Run the focused CTest, then `-L system` for every changed version and
  architecture gate that is available locally. Run the full intended matrix for
  a cross-version change.
- Before review, inspect only your intended documentation and test changes:

```powershell
git diff --check -- Source/SystemTests
git diff -- Source/SystemTests
git status --short
```

Do not commit local credentials, generated test roots, binaries, or another
developer's existing work.
