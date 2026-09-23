# Test-coverage gaps in feature/fix-issues

## Scope and conclusion

Assessed commit range: `816bf2184664c0737061ecb461bd06fed7facf22..b30e83872c0006e8240c8b4f565da5351bf10080`, from the inspected `master` baseline to `feature/fix-issues`.

**All 27 branch commits contain no test additions, test modifications, or test-registration changes.** They change 28 production files. Three commits are comment/TODO-only; the other 24 contain code changes. No changes in this range were found under UnitTests, SystemTests, BehaviourTests, TestCases, TestCommon, EnetTest, or `.github`; root/test-enabling CMake files were also unchanged.

This is not equivalent to saying every fix is entirely untested. Existing tests cover some normal operations and at least one demonstrated regression. Git history cannot establish whether the author ran existing tests locally. The missing-coverage conclusions below are based on the changed code, test registration, targeted executable-test searches, and relevant existing test bodies, not a numerical coverage measurement or an exhaustive audit of every historical test.

This assessment was read-only. No implementation, test, build configuration, credential file or review finding was changed during the inspection; no tests/builds were run for it. This document subsequently saves that assessment at the user's request.

## Important correction: play-time serialization already has regression assertions

The change in `8fa9650b` archives `PlayTime.load()` rather than loading back into the atomic counter. The baseline review's runtime probe demonstrated that a nonzero counter is lost during deserialization.

**Two existing tests already assert the necessary behavior:**

- [`UserHelloDataMessageTests.cxx:20–28`](../../Source/UnitTests/Shared/Networking/UserHelloDataMessageTests.cxx): sets play time to 12, round-trips the message and expects restored play time to equal 12.
- [`RequestSpecificUserDataMessageTests.cxx:25–33`](../../Source/UnitTests/Shared/Networking/RequestSpecificUserDataMessageTests.cxx): the corresponding nonzero response round-trip assertion.

They are included through the versioned Shared test glob in [`Versioned.cmake:6–22`](../../Source/UnitTests/Versioned.cmake). They should detect the reproduced regression when built and executed. They were not executed during this coverage assessment, so this document does not claim an observed GTest failure.

**Immediate gap: run and enforce the existing tests, rather than add a duplicate assertion.** Earlier review language suggesting that play-time archive round-trip coverage was absent was too broad. The standalone container tests are limited, but these message-level tests must be included in the coverage assessment.

## Missing regression coverage by fix area

| Fix area and commits | Existing coverage | Missing focused verification |
|---|---|---|
| Initialization failure and standalone game-server initialization — `487d9883`, `d13dbfab` | Basic initialization scenarios and init-option unit tests | Inject construction/DNS/transport failures; verify SDK-visible error behavior, cleanup after partial initialization, restored stdout, successful retry, and game-server-only initialization without client initialization. |
| File-share workers and shutdown order — `0381a94b`, `198a11db` | File-share round trips and policy-denial cases; basic callback-queue tests | Block a worker during shutdown; cancel/destroy its listener before registration/completion; deliver a late event during teardown; verify worker joining without deadlock, no post-shutdown callbacks and no use-after-free. |
| Custom networking synchronization and defensive checks — `6e0d8920`, `26bfdb2e` | WebSocket echo and orderly close | Sustained receive/poll/read overlap; invalid and closed IDs; null/zero-length defensive cases; remote close racing local close; shutdown with queued events. An ordinary echo does not reliably exercise the problematic interleavings. |
| Missing lobby-list request state — `16184c82` | Normal discovery/filter scenarios | Inject unknown/duplicate response IDs, missing filter state and null lobby entries. Assert callback/cache semantics as well as crash prevention. Cover zero and limited result counts. |
| P2P empty pop and output-buffer behavior — `b00909d0`, `b30e8387` | Normal packet exchange and channel-255 coverage | Empty/repeated pop; smaller/exact/larger destination buffers; full message-size output despite truncation; destination canaries; optional-output handling; Peek retaining versus Read consuming a packet. Existing receive helpers allocate the advertised full size. |
| Cloud metadata/list locking and buffer-size correction — `c4c0c7ca`, `9453c036` | One sequential cloud round trip using an exactly sized buffer | Multiple pending requests for different containers/files; callback-specific snapshots; concurrent list/metadata access; smaller/exact/larger download buffers; missing/malformed metadata across all retrieval overloads. |
| Streamed cloud hashing — `13ad0f2e`, `ae679191` | Low-level FNV helper tests | Actual CalculateHash API tests around 2048-byte chunk boundaries, irregular chunks, binary data, consecutive calls, concurrent calls and reentrant callbacks. Compare streamed and contiguous results. Testing the primitive alone does not catch passing it the wrong chunk length. |
| Atomic connection state — `d938c8b9` | Normal networking scenarios | Concurrent state queries through connect/disconnect/retry/shutdown; failed initial connection; timeout retirement and exactly-once transitions. Atomic fields alone do not validate the state machine. |
| Filesystem locking and error handling — `08f053e0`, `f42ac3c0` | Sequential create/read/share/delete and metadata persistence | Concurrent copies to one destination; no duplicate indexes; lock-order/deadlock checks; directory enumeration with inaccessible/disappearing entries. |
| Stats assignment locking and atomic play time — `8fa9650b` | Scalar access, basic copy construction, and the existing play-time serialization assertions above | Concurrent assignment/copy/update/serialization; self-assignment; opposite-direction assignments; coherent snapshots. Run the existing serialization cases first. |
| Interceptor shutdown — `7894b9ae`, `ac6f1e70` | No dedicated interceptor regression target in inspected unit-test registration | A fake native SDK verifies exactly one shutdown call, internal observer detachment before native shutdown, safe partial-init cleanup, reinitialization, and option forwarding through the exported extended shutdown API. |
| Interceptor proxy ownership — `fa0b1051` | Ordinary client registrar tests, not the interceptor proxy implementation | Multiple operations sharing one listener; cancellation before completion; self-unregister; completion racing cancellation; exactly-once destruction; one listener reused across client and game-server sessions. Priority ASan cases. |
| Interceptor forwarding — `4c822fd5`, `ca3cae7f` | No targeted forwarding tests found | A fake SDK verifies the exact rich-presence method and every argument, including non-local user/nonzero index. Verify matching/stale/null expectedHash forwarding and relevant feature-gated signatures. |
| Process-path logging and character classification — `904473ec`, `02698819` | No targeted tests found | Normal/truncated/failed process-path retrieval; trimming empty/all-whitespace strings and high-bit bytes. Lower priority than lifecycle and data preservation. |

“No targeted tests found” is scoped to the inspected registrations and relevant searches, not a claim that no external/manual test exists. Defensive argument tests must distinguish documented legal inputs from robustness behavior on invalid inputs.

## The three comment/TODO-only commits

### e30ef34a — lobby admission/joinability

The non-joinability admission check remains commented out. This commit is not a completed behavior fix. A `public-lobby-not-joinable-behavior` scenario and characterization route already exist in BehaviourTests. The gap includes executing the relevant scenario, establishing the intended contract, then making any actual correction and enforcing the result. Do not duplicate the existing scenario just because no new test accompanied this commit.

### 9f4da7b6 — native cloud conditional deletion

The native implementation still has a TODO for checking the expected hash. Missing behavior/test pair: a stale hash rejects deletion and preserves the file; a matching hash allows deletion; null-hash semantics remain deliberate. The interceptor forwarding correction is a separate path.

### d2734a6a — shared-file download handling

The download comment remains a TODO. Tests should distinguish a valid zero-byte file, missing file, transport failure and local write failure. Existing nonempty round trips and policy-denial cases do not establish those distinctions.

## Evidence in the existing suite

- [`AchievementsAndStatsContainerTests.cxx`](../../Source/UnitTests/Shared_NoVer/AchievementsAndStatsContainerTests.cxx) covers scalar values, basic copying and a local play-time getter; the two message tests supply the separate serialization assertions.
- [`ListenerRegistrarTests.cxx`](../../Source/UnitTests/Client/ListenerRegistrarTests.cxx) covers ordinary registration, one-time dispatch and request-map removal, including removing multiple pending requests. It does not exercise the interceptor proxy map or completion/cancellation ownership race.
- [`DelayRunnerTests.cxx`](../../Source/UnitTests/Client_NoVer/DelayRunnerTests.cxx) covers an empty queue, FIFO order and callbacks enqueued during execution. It does not test destroying the owning runtime while a callback is executing.
- [`filesystem_containerTests.cxx`](../../Source/UnitTests/Shared_NoVer/filesystem_container/filesystem_containerTests.cxx) and [`filesystem_container_entryTests.cxx`](../../Source/UnitTests/Shared_NoVer/filesystem_container/filesystem_container_entryTests.cxx) provide sequential happy-path file/index/metadata coverage, not simultaneous copy completion or denied/deferred filesystem operations.
- [`ConstHashTests.cxx`](../../Source/UnitTests/Shared_NoVer/ConstHashTests.cxx) tests the hash primitives and known values, not CloudStorage's read-callback/chunk-buffer integration.
- [`SystemTests/Host/CloudStorage.cxx`](../../Source/SystemTests/Host/CloudStorage.cxx) passes an explicit hash and uses a download buffer equal to the payload size; requests are pumped sequentially.
- [`SystemTests/Host/CustomNetworking.cxx`](../../Source/SystemTests/Host/CustomNetworking.cxx) exercises normal echo/close; [`P2P.cxx`](../../Source/SystemTests/Host/P2P.cxx) allocates receive buffers from the advertised size.
- [`SystemTests/Host/Storage.cxx`](../../Source/SystemTests/Host/Storage.cxx) covers nonempty file sharing, offsets, invalid IDs and server-policy denials; it does not force worker teardown or valid empty downloads.
- [`UnitTests/CMakeLists.txt`](../../Source/UnitTests/CMakeLists.txt) and [`Versioned.cmake`](../../Source/UnitTests/Versioned.cmake) register common/Client/Shared tests, not a dedicated interceptor unit-test target.
- [`BehaviourTests/CMakeLists.txt`](../../Source/BehaviourTests/CMakeLists.txt) registers the existing opt-in non-joinable-lobby behavior scenario under its prerequisites. Configuration text was inspected; credential files were not read and the configuration was not executed.

## Recommended execution order

1. **Run existing tests first**, particularly both play-time serialization cases. Capture failures and fix them without weakening assertions to fit the regression.
2. Add **lifecycle, worker and interceptor proxy tests** using deterministic barriers plus Windows ASan. Assert callback counts, cancellation and exactly-once destruction; ASan supplements those behavioral checks.
3. Add **small deterministic boundary/contract tests** for streamed hashing, P2P/cloud buffer lengths and exact interceptor forwarding.
4. Add **concurrency and filesystem failure scenarios** with bounded timeouts, controlled interleavings and fault injection rather than timing-only sleeps.
5. Run affected tests across the relevant SDK feature boundaries; include x86/x64 and Debug/Release as appropriate. Configure targets through the existing per-version mechanism, without hardcoded version-specific CMake targets.

For each behavioral fix, aim for a regression that demonstrably detects the old failure and passes only when the intended contract holds. A compilation pass, absence of a crash on one run, or a test that merely mirrors the implementation is insufficient evidence.

## What was previously executed versus what remains

The baseline review's **15 successful builds were compilation/linkage checks with test targets disabled**. Its three temporary runtime probes reproduced defects; they are not committed automated regression tests. See [VERIFICATION.MD](VERIFICATION.MD) for exact commands and results. Those results do not establish that the existing GTest, system or behavior suites pass on this branch.

No unit/system/behavior suite or sanitizer pass was executed for this coverage assessment. Test execution and regression additions remain pending. This coverage supplement does not add new production-defect IDs to the baseline review's counts.

## Repository status at assessment

`git ls-remote` confirmed both local and remote `feature/ai-review` at `cf07a0645ef167c46e68e7f34ffb1a1c76ade62a`, and remote `feature/fix-issues` at the assessed `b30e8387` baseline. The worktree was clean before saving this document. This is a historical synchronization check, not a claim that this newly saved supplement has already been committed or pushed.
