# UniverseLAN — thorough follow-up addendum

## Executive result

Production baseline remains **`b30e83872c0006e8240c8b4f565da5351bf10080`**; review started at `feature/ai-review` commit `48cea8c6`. All **529 in-scope inputs** were re-inspected with fresh notes and cross-component tracing. Earlier findings and the test-coverage supplement remain available.

**23 distinct confirmed additions: 3 High, 19 Medium, 1 Low.** Combined with the preserved 103 baseline groups, the reconciled review contains **126 actionable groups: 24 High, 89 Medium, 13 Low**. Four additional conditional/latent records join the two baseline investigations, for **six informational records** outside those totals. Three initially proposed additions are aliases of existing groups and are not counted twice.

This follow-up focuses on C++ correctness, memory/resource lifetime, callback/API compatibility, persistence and build behavior. Per the user's clarification, validation used isolated local objects and temporary files. No live-service or adversarial network testing was performed. Complete accounting and evidence qualifications: [RECONCILIATION.MD](RECONCILIATION.MD).

## Most important new evidence

| ID | Result | Consequence |
|---|---|---|
| **ADD-ABI-001 — High** | Real SDK 1.73.0 and production registrar delivered a time-played event to a leaderboard listener in a local executable | Wrong virtual-interface dispatch for the colliding 1.73.0–1.75.0 listener tags; x64 routing reproduced, wider ABI consequences qualified |
| **ADD-UTIL-001 — High** | Source-established stale lookup/removal interleavings | A successful lookup/cleanup can remove newly published or replacement file data and desynchronize indexes |
| **ADD-SERVER-001 — High** | Source-established overlap between user filenames and internal counter storage | Ordinary file/state namespace collision can make numeric startup parsing fail; no service test executed |
| **ADD-STORAGE-003 — Medium** | Actual quota adapters returned total=used=UINT32_MAX for a 100/20/80-GiB fixture | Reported free headroom becomes zero despite available storage |
| **ADD-UTIL-006 — Medium** | Actual filesystem metadata save failed for the second of two valid relative names | User data names collide in the metadata file/directory representation |
| **ADD-API-001 — conditional** | ASan reported heap-use-after-free for the actual erase-then-copy helper sequence | The memory mechanism is real; SDK permission to feed a borrowed key into a mutating API remains unresolved, so it is not included in confirmed totals |

[VERIFICATION.MD](VERIFICATION.MD) records exact configuration, harness setup failures and corrections, observed output, instrumentation boundaries and unexecuted cases. A successful reproducer exit means it observed baseline-bug behavior, not that fixed behavior passed. This was not a whole-codebase sanitizer-clean run.

## Complete new-group index

Detailed sections are appended to the responsible `<filename>.review.MD` reports; owner notebooks link those sections and contain the full file-by-file ledger.

| Owner | Confirmed additions after reconciliation | Other dispositions | Notebook |
|---|---|---|---|
| CORE | 001 offline Apps unavailable after transport-init failure; 002 ignored local endpoint/thread-factory controls; 003 client/server identity collision | Three Medium | [CORE.MD](CORE.MD) |
| API | 003 lobby callbacks overtake earlier membership events; 004 legacy server-networking queue uses client-networking listener type | Two Medium; 001 borrowed-key use and 002 zero-selector callback convention conditional | [API.MD](API.MD) |
| STORAGE | 002 data/metadata generations diverge; 003 quota saturation; 004 play-time readiness inferred from incomplete user placeholder; 005 legacy global user-data completion gated out | Four Medium; 001 nested upload scratch-buffer reuse conditional on reentrancy contract | [STORAGE.MD](STORAGE.MD) |
| NET | 002 INI persistence changes valid strings; 003 disconnect cleanup leaves pending operations/filter state | Two Medium; 001 and 004 are baseline aliases | [NET.MD](NET.MD) |
| UTIL | 001 stale membership/removal race; 003 simultaneous metadata-save interference; 005 x86 large-file narrowing; 006 metadata namespace collision | One High, three Medium; 002 baseline alias, 004 dormant helper issue | [UTIL.MD](UTIL.MD) |
| SERVER | 001 administrative/user-file name overlap; 002 lobby snapshot fields exceed recipient API view; 003 long source paths interrupt diagnostic conversion | One High, one Medium, one Low | [SERVER.MD](SERVER.MD) |
| INTERCEPT | 001 factory public error manager returns null; 002 legacy InitOptions forwarding drops settings/policy; 003 forced DLC completion delivered inline | Three Medium | [INTERCEPT.MD](INTERCEPT.MD) |
| BUILD | 001 individually built interceptor testcase lacks runtime staging dependencies | One Medium, optional-target path | [BUILD.MD](BUILD.MD) |
| ABI | 001 incompatible listener types share the legacy registration tag | One High; undefined persona macro clarified without another ID | [ABI.MD](ABI.MD) |

IDs in each row use `ADD-<owner>-NNN`. The ABI row is targeted cross-owner verification, not additional source files beyond the 529-input inventory.

### Duplicate additions, excluded from the new count

- ADD-NET-001 → BASE-SERVER-019: application broadcast recipient selection.
- ADD-NET-004 → BASE-SERVER-008: chat request/event correlation.
- ADD-UTIL-002 → BASE-SERVER-007: repeated filename/new shared-ID collision, including its client-cache consequence.

The five baseline aliases and previously documented partial overlaps still apply. Finding IDs are stable even where a proposal becomes an alias or investigation; the checker derives canonical totals from the explicit map.

## Important updates to existing findings

- **Cancellation:** BASE-CORE-001 now includes cancellation between two already-popped callbacks of one lobby response. Fixing only deferred queue entries is insufficient.
- **Initialization:** BASE-CORE-005's error boundary must cover normalization and worker creation, which sit outside the existing try block.
- **API preconditions:** BASE-API-009's nonmember owner-query example was narrowed to the supported structural-cache claims. Pointer lifetimes, nested pumping and callback reentrancy are not assumed from general thread-safety wording.
- **Persistence:** BASE-NET-008's proposed remedy now accounts for the dependency's write/close status handling; a nominal SaveFile success is insufficient. Cloud completion-before-close, large signed callback extents and savegroup identity across instances are added evidence under their existing IDs.
- **Listener and module identity:** Interceptor proxy ownership is shared within the same interceptor module/session graph; distinct DLL copies and distinct multiple-inheritance listener subobjects are not assumed identical.
- **Tracing:** The existing BASE-INTERCEPT-005 gains a lower-severity, capacity-bounded unwritten-tail instance, while its original over-capacity examples retain High severity. The accounting checker now distinguishes such evidence addenda from canonical severity records.
- **Tests:** Existing Binary-archive message tests already assert nonzero play-time preservation; the earlier PortableBinary probe covered the production archive form. The [coverage supplement](../review-baseline/TEST-COVERAGE-GAPS.MD) remains the source for test-execution gaps.

No existing baseline finding was withdrawn by this pass. Some triggers, SDK contracts, proposed remedies and lower-severity instances were qualified. Owner-local candidate counts predate reconciliation; this summary and the reconciliation ledger determine the effective counts.

## Coverage and method

| Owner | Inputs re-inspected |
|---|---:|
| CORE | 30 |
| API | 10 |
| STORAGE | 14 |
| NET | 59 |
| UTIL | 40 |
| SERVER | 43 |
| INTERCEPT | 73 |
| BUILD | 260 |
| **Total** | **529** |

All distinct implementations were read, including feature branches. The empty markers and identical dispatchers were rechecked by individual path/content identity; BUILD's ledger explicitly incorporates the exact wrapper list after verification. Its read-only static audit additionally checks the 69-version feature/declaration/export matrix. Such lexical checks are not binary ABI certification. One owner disclosed early incidental exposure to old sidecar excerpts before its subsequent full source reread; the pass is not claimed perfectly blind.

The original exclusions remain: SDK/vendor/excluded test code is context only; SystemTests is in scope; InterceptionLogger remains shallow serious-defect review. Windows guards are reviewed statically without Linux execution. No credentials were accessed. No production implementation or repository CMake target was changed.

## Recommended next steps

1. Correct callback type discrimination at legacy version boundaries and generation-aware file membership/removal.
2. Separate administrative state from user-file namespaces, make metadata naming unambiguous, and commit coherent data/metadata generations.
3. Preserve operation identity and callback order through connection retirement, worker admission and user-cache hydration.
4. Correct the local runtime-option, legacy callback/InitOptions and factory-error integration gaps; add small contract-focused regressions.
5. Resolve the three conditional API conventions before turning those investigations into compatibility requirements. Keep the dormant helper issue out of current production-defect totals until a reachable caller is established.

All other proposed fault/concurrency/game/native-SDK tests remain unexecuted. The prior five-version production build results remain historical evidence. The follow-up's concrete execution consists of the recorded local ASan-enabled callback/filesystem probes.
