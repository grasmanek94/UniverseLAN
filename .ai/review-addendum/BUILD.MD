# BUILD — complete 260-input follow-up static review

Date: 2026-09-24. Production baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Observed HEAD: `48cea8c6c48fa41fddd348a0119129cc5643fc8b`. Instructions: `.ai/SKILLS/CppReviewer.md` and this directory's `PLAN.MD`.

## Executive summary and accounting

**260/260 assigned paths reinspected, with exact set and content equality verified. One new BUILD-owned finding: ADD-BUILD-001, Medium / Build, High confidence in static evidence.** Individual interceptor-mode testcase targets do not depend on the production targets that stage their runtime DLLs. Full local finding: [`Source/DLLs/CMakeLists.txt.review.MD`](../../Source/DLLs/CMakeLists.txt.review.MD#add-build-001-individual-interceptor-mode-testcase-targets-do-not-build-or-stage-their-runtime-dependencies).

The baseline BUILD owner had **zero independent defect IDs**. This adds one, not a relabeling of an old BUILD finding. Counts: Critical 0; High 0; Medium 1; Low 0. Existing cross-component IDs and the two owner handoffs below are not additional BUILD counts. The historic no-build-defect conclusion is preserved; the optional individual-target deployment path was not exercised by the prior production builds.

The version/feature architecture is substantially supported by the expanded static checks: 154 flags across 69 versions; 152 declaration-sentinel mappings; all 138 architecture export lists; actual feature-reader and listener-inheritance checks. Main residual risk is the difference between compilable wrappers and the correct SDK/runtime contract, particularly historical listener types and dynamically resolved exports. These checks do not establish whole-product release readiness.

## Scope, environment and execution limits

- Reviewed the root `CMakeLists.txt`, `Source/CMakeLists.txt`, `Source/galaxy_sdk_features.cmake`, every `.cxx/.hxx/.cmake/.txt` recursively under `Source/DLLs` excluding the `galaxy` and `gog` trees, and only direct `Source/Vendor/*.cmake` / `*.txt`.
- SDK headers and `.def` files were dependency/ABI context. Component CMake definitions, public export facades, selected feature readers and optional target manifests were traced as integration context, not added to the 260 first-party coverage count. No nested vendor implementation or excluded test/tool implementation review is claimed.
- Windows x86/x64 static focus. **No configure, build, test, native DLL/EXE inspection or execution, sanitizer, Git write, source edit or credential access.** Existing 15 x64 Debug production builds for 1.57.0, 1.124.0, 1.139.2, 1.148.3 and 1.152.11 were not repeated. Their recorded success remains historical evidence only.
- Read/Glob/Grep supplied complete unique-input reads and focused contract context. The read-only evidence script [BUILD-static-audit.py](BUILD-static-audit.py) was authored with `apply_patch` and run with `python -B`; it computes hashes and parses source text, emits stdout, and creates no outputs. It is an audit sidecar, not a project test. Only BUILD reporting artifacts were edited by this owner; other owners' concurrent sidecar changes were left intact.
- Read-only Git operations: `rev-parse`, status, scoped baseline diff, `ls-tree`, `hash-object` without `-w`, and a `diff --no-index` of SDK 1.75.0/1.76.0 IStats declarations. A first broad diff also displayed existing reporting additions; it was narrowed to exclude `.MD` before determining production equality. Deliberate notebook comparison followed independent input inspection.

## Exact expanded 260-path coverage and equality proof

The exact set is the union of the **16 paths listed individually in the next section** and **all 244 paths** in the three fenced inventories of [baseline WRAPPER-COVERAGE.MD](../review-baseline/WRAPPER-COVERAGE.MD#exact-input-paths-69-empty-markers): 69 markers, 138 architecture dispatchers and 37 manifests. This is an explicit incorporation of every listed path, not a representative sample. The independent filesystem predicate above produced the same 260 paths as that ledger plus the baseline BUILD control list: **missing 0, extra 0**. All 244 existing wrapper sidecars' recorded blob IDs also match freshly calculated current input hashes.

`git ls-tree -r <baseline>` was compared with `git hash-object --stdin-paths` for **each of the 260 paths**. Result: **260 matches, 0 mismatches**. Thus all covered inputs retain the baseline content under Git's path-aware normalization. Additional raw-byte SHA-256 comparisons independently establish the repetitive-file identities.

| Class | Verified paths | Distinct Git blobs | Inspection method/result |
| --- | ---: | ---: | --- |
| Control inputs below | 16 | 16 | Complete fresh Read of every file; per-file notes below |
| Empty markers | 69: 30 Factory + 39 Dll | 1 | Every path hashed and read by audit; all zero-byte; filename/era checked individually |
| Dispatchers | 138: 69 x86 + 69 x64 | 1 | Every path hashed; shared three-line content read and traced through inherited directory/version/architecture scope |
| Compatibility manifests | 37 | 36 | Every file's entire contents read; all lines printed in source order, including the duplicate and uncertainty token |
| **Total** | **260** | **54** | **No unfinished assigned files** |

Reproducible evidence checksums (lowercase hex):

- Path-set SHA-256: `bb8a19191843d613397fae8f173471caf223c776d5ac7fbcb558ca52d7c78701`. Input is ASCII/UTF-8 repository-relative slash paths, Python lexicographic order, one LF after each path, including the last.
- Path/blob-pair SHA-256: `f716c2d76955751049621bc1a6e5e133042c4414f318ebd922050e4640e16f93`. Same order, each record `<path>\t<Git-blob-id>\n`.
- 69 empty-marker blob: `e69de29bb2d1d6434b8b29ae775ad8c2e48c5391`; raw SHA-256 `e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855`.
- 138 dispatcher blob: `2ea4783757bd44da55a293d7c6404e10ec8d0894`; raw SHA-256 `bdddfe7d56e9ac99fb289f91d4461a912df3e8fc5e4cd2b3e34e6c25e2e8b5e6`.
- All 37 manifests match their individually recorded baseline blobs. Only `Source/DLLs/1.139.2/compat_list.txt` and `Source/DLLs/1.139.5/compat_list.txt` share content: blob `576e2b84b7955b91bf86d1159071dee71ea5ee65`; raw SHA-256 `2f56184cad45572831ac5cb26ad223f1013c759f07946172b697a6155b27c858`. The other 35 are singleton classes.

Every one of the **69 version directories** has both architecture dispatchers and both `UniverseLAN.def` paths. Factory markers run through 1.114.9 (30); direct DLL markers start at 1.121.2 (39). All **1,450 SDK `.h` / `.def` context paths** independently hashed also match baseline (0 differences); this count is context, not an assertion of complete manual review of every SDK line. No native binaries were required.

Manifest notes applying to their individually enumerated paths: entries are human compatibility assertions, not inputs parsed by this generator. Duplicated 1.139.2/1.139.5 lists, the 1.142.1 token in the 1.144.1 list, and literal `1.150.0?` in 1.149.0 do not establish compatibility or break target generation. No ABI equivalence is inferred from those notes.

## Fresh per-file notes for all 16 unique control inputs

| Exact path | Fresh inspection and disposition |
| --- | --- |
| `CMakeLists.txt` | All 103 lines: C++20, default-disabled options, BUILD_ALL_TESTS forcing, testing enablement, experimental unity, MSVC architecture dispatch, non-MSVC flags, source-root output and LIMIT_VERSIONS. Empty means all; unknown selection can yield no matching version, a validation improvement rather than a proven valid-input failure. ROOT/bin and writable-source layout are intentional. No new direct defect. |
| `Source/CMakeLists.txt` | All 39 lines: vendor/common definitions precede per-version creation; BUILD_INTERCEPTOR gates both definition and call sites. Optional suites are independently gated. Declaration order creates no build dependency between testcase targets and the production staging producers: integration of ADD-BUILD-001. |
| `Source/galaxy_sdk_features.cmake` | All 306 lines: inclusive tuple comparisons, repeated-range union, local list initialization, inherited TARGET/UVV and explicit PUBLIC 0/1 flags plus per-version global properties. Full static matrix below; no new interval-composition defect. Reader and SDK-inheritance notes below. |
| `Source/DLLs/CMakeLists.txt` | All 228 lines: directory discovery/filtering, marker selection, SDK target graph, version extraction/resources, both `.def` inputs, naming, optional unet/unit/interceptor targets, config copies. ADD-BUILD-001. All current required defs exist, so appending a version before a hypothetical missing-def return is not a present failure. |
| `Source/DLLs/determine_galaxy_version_feature_definitions.cmake` | All 3 lines: relative include resolves in the normal DLL configure context; not evaluated as an arbitrary-directory standalone script. No new defect. |
| `Source/Vendor/CMakeLists.txt` | All 51 lines: dependency order, Windows-only StackWalker, opt-in GoogleTest, recursive unity exclusion. Cache settings have intended vendor-subproject effects. No new defect. |
| `Source/Vendor/cereal.cmake` | All 8 lines: header glob, dummy C translation unit, STATIC wrapper and PUBLIC include propagation. No implementation assumed from dummy target. No new defect. |
| `Source/Vendor/galaxy.cmake` | All 15 lines: per-version SDK tree, STATIC dummy target, PUBLIC correct include root / GALAXY_EXPORT / version-feature definitions. These flow through Shared to the client/interceptor and DLL, and explain why `.def` omissions alone are not missing-export findings. |
| `Source/Vendor/ixwebsocket.cmake` | All 9 lines: forces static dependencies, TLS/Mbed TLS; zlib/crypto bridges run before consuming IXWebSocket. No new defect in the current standalone build. |
| `Source/Vendor/ixwebsocket-mbedtls.cmake` | All 165 lines: include guard, disable vendor tools/tests, save/restore Python discovery setting, real target selection including TF-PSA-Crypto, BUILD_INTERFACE extraction, legacy variables and explicit IX TLS-version definition. Cross-checked actual consumer's skipped find-package branch and current target include expressions. No new integration defect. |
| `Source/Vendor/ixwebsocket-zlib.cmake` | All 68 lines: static zlib target/alias, legacy find variables, source+binary include intent. Actual IX consumer links ZLIB::ZLIB; real zlib target supplies generated-header includes. No new defect. |
| `Source/Vendor/json.cmake` | All 8 lines: header tree and dummy source with PUBLIC include path; STATIC wrapper. No new defect. |
| `Source/Vendor/magic_enum.cmake` | All 5 lines: STATIC dummy target with PUBLIC includes. No new defect. |
| `Source/Vendor/miniz-cpp.cmake` | All 5 lines: STATIC dummy target plus header/include path; reached through simpleini. No new defect. |
| `Source/Vendor/simpleini.cmake` | All 8 lines: UTF conversion translation unit, linked miniz wrapper, PUBLIC include requirements. No new defect. |
| `Source/Vendor/unet.cmake` | All 75 lines: opt-in versioned source/dependency graph, platform files and definitions, version flags. Its GALAXY_ARCH argument is intentionally an output suffix (`64` or empty). Static-library output lives in its binary target directory; the `bin/test` RUNTIME/LIBRARY properties do not establish a missing Windows runtime DLL. No nested unet implementation certification. |

## Entire-version feature, value and reader audit

`afvd` has **158 rows / 154 distinct names / 10,626 evaluated version-feature values**. Repeated ranges correctly OR: game-server telemetry, chat room listeners, storage file-share listeners and request-user-data listeners retain their isolated 1.134.x windows and later reintroductions. Both enabled and disabled lists are reinitialized for each call; values are not accidentally inherited from the preceding SDK target. PUBLIC flags propagate along the intended version-specific SDK/Shared/Client or InterceptionLogger chain.

The script's explicit probe table checks **152/154 flags, 10,371 applicable declaration cells, zero mismatches** after declaration-specific investigation. Three factory-only probes exclude 39 modern SDKs apiece (117 nonapplicable cells). Two flags, `USER_DATA_LISTENERS` and `USER_SIGNIN_CROSSPLATFORM`, are evaluated but not declaration-certified: there are no production readers, and their labels do not identify a precise change. Naive presence checks find the named concepts earlier, which is not enough to assign an unused-metadata defect. Sentinel checks cover a representative declaration for composite flags; they do not prove every signature in a composite feature.

- Feature-bit matrix SHA-256: `e926b2e5476d34db03d5c6bff95070be287487511e43f5d99ccaf1b1fb9ada33` (versions in numeric tuple order; feature names lexicographically sorted; `<version>\t<154 bits>\n`).
- Declaration-comparison matrix SHA-256: `586d467f7e2f9c36ca6e60a0d9f5ba4d066fe4c0dcad55535ffda5260b8a1596` (feature-major lexicographic order, then numeric versions; `<version>\t<feature>\t<expected>\t<observed>\n`, excluding stated nonapplicable/unresolved cells).
- Important false positives rejected by actual reads: `PersonaStateChange` is not `PersonaState`; the older existence of ListenerType does not make Register's parameter typed; invitation failure enums must be checked in the right listener; the time-played UPDATE flag describes inheritance/global-helper correction, not first existence of its callback signature. 1.100.2 lacks convenience GalaxyApi functions but retains IGalaxy::GetServerNetworking, so it does not contradict HAS_ISERVERNETWORKING.
- No selected version enables the RED or other bounded 1.149.1–1.149.16 branch flags. These receive negative declaration checks only; positive RED-branch behavior is outside the present matrix. NEAR_FILTER_ENUM stays false and the absent enum is not confused with the real near-filter method.

**Version value checks:** concatenation in `DLLs/CMakeLists.txt:10-34,48-65` yields **zero collisions among the 69 selected versions**, and zero among the **222 distinct normalized version tuples** obtained from directories, table interval endpoints and compatibility tokens (two-component tokens padded with patch 0, trailing `?` removed only for this arithmetic analysis). Concatenation is not order-preserving: 1.134.10 becomes 113410 and then 1.135.0 becomes 11350; similarly 1.148.14 → 1.149.0 reverses order. All **20 actual numeric comparison sites** in production are `>11240` (15 Shared schema sites, 5 Server handler sites); evaluating that predicate across all 69 versions matches the intended tuple boundary exactly. Thus this is a future robustness concern, not a current collision/mis-selection ID. Prefer existing named features or tuple comparisons for future gates.

**Reader checks:** scanned production Client, Client_NoVer, Shared, Shared_NoVer, Server, InterceptionLogger, Version and Tracer C++/CMake inputs for feature names, numeric version predicates, and defined/ifdef misuse. No production `#ifdef`/`defined` misuse of the emitted 0/1 feature flags was found. One undefined name occurs twice in User.cxx, discussed below. The once-compiled Shared_NoVer loader cannot acquire consumer feature definitions retroactively; its dormant RED handling remains BASE-UTIL-015 rather than a new BUILD issue.

## x86/x64 definitions, calls and resolver evidence

All **138 `.def` files / 2,894 entries** parsed, including files omitting explicit ordinals. No duplicate export names or explicit ordinals within a file, and no unparsed entry remained. All 69 Windows GalaxyExport headers select `__cdecl`; actual factory call-type transitions and free-export declarations were checked against x86/x64 decoration. Static factory functions are cdecl before and after adding the explicit macro; virtual member methods retain the SDK member convention. The interceptor's 14 interface getter function-pointer typedefs use GALAXY_CALLTYPE. `load` is C linkage with the default MSVC cdecl convention and a named def export. No new call-convention mismatch was established; no compiler or PE ABI check is claimed.

The source/header comparison evaluated both client and interceptor free-export facades across **all 39 direct-DLL versions**. No declared SDK free-export name is missing from either active implementation. Both additionally define GameServerUtils in the nine selected direct-DLL versions before 1.133.0; the client's extra entry point is not itself evidence of failure. The interceptor's mandatory native lookup under HAS_IUTILS is the already reported BASE-INTERCEPT-007 mechanism.

The definition/header differences are explicitly retained as context:

| Versions, both architectures | Declaration absent from `.def` |
| --- | --- |
| 1.57.0, 1.60.0, 1.61.0 | GalaxyFactory::CreateInstance; the early header has a `!GALAXY_LIB` helper declaration and the def exposes GetInstance/Reset |
| 1.133.0 | GameServerUtils |
| 1.134.8 | Telemetry |
| 1.134.9, 1.134.10 | Telemetry and GameServerTelemetry |

These **18 architecture/name omissions** are not charged as missing UniverseLAN exports: GALAXY_EXPORT propagates from the SDK target, the definitions are exported with dllexport (the factory class is exported), and other def-required functions pull those same translation units out of the static implementation archive. Listed modern def symbols otherwise match the SDK type-specific MSVC decorations. Actual proprietary export tables, automatic ordinal assignments and special-member emission remain unverified. In particular, a repository def omission cannot alone prove absence in a proprietary DLL.

The resolver audit evaluates **216 applicable version/architecture/session profiles and 2,814 requested-name lookups** against repository export lists. It finds 46 zero-match requests and no ambiguous match: early CreateInstance/ResetInstance, pre-1.133 GameServerUtils plus 1.133.0's list omission, client Telemetry at 1.134.8/.9/.10, and game-server Telemetry at 1.134.8/.9/.10/1.135.0. The header-supported boundaries corroborate BASE-INTERCEPT-007; the four header/def-disagreement versions need a symbol-only native export comparison before widening its confirmed native-failure scope. No duplicate BUILD ID is assigned. BASE-INTERCEPT-006's callback-result gates remain separate from mere optional operation-listener availability. The impossible `HAS_IGALAXY && HAS_INITOPTIONS_MODERN` forwarding branch is now covered by the other owner's ADD-INTERCEPT-002.

## Optional targets and output integration

ADD-BUILD-001 is limited to the missing target dependency/staging relationship. Normal non-interceptor testcase mode explicitly stages the official SDK under the imported DLL name. Versioned unit tests link static implementation libraries and use `bin/tests/<version>` runtime properties. System/behaviour runners receive target-file paths and depend on their hosts and selected production targets; their scenario staging is not replaced by the old testcase copy scheme. Behaviour targets have an explicit x64 restriction. Optional test implementation correctness and native prerequisites are outside this BUILD ownership.

Intentional writable-source resource generation and ROOT/bin outputs are retained as architecture constraints. There is no new defect for a read-only checkout, concurrent builds targeting identical artifacts, hypothetical missing defs, unsupported MinGW, or unpromised custom configurations. Debug/Release config copies and current MSVC suffixes were traced. No benchmark, security-boundary or performance defect was established in these manifests. This was not a dependency vulnerability or CI workflow audit.

## Notes for other source owners — no additional BUILD IDs

### CORE/STORAGE: supported SDK listener inheritance collides in 1.73.0–1.75.0

The sweep of **3,431 GalaxyTypeAwareListener class declarations** across all 69 SDKs finds precisely one collision family. `Source/DLLs/{1.73.0,1.74.0,1.75.0}/galaxy/IStats.h:276,313` gives both `ILeaderboardRetrieveListener` and `IUserTimePlayedRetrieveListener` the `LEADERBOARD_RETRIEVE` tag. In 1.76.0 the latter changes to USER_TIME_PLAYED_RETRIEVE and gains its global helper. The table's UPDATE boundary is correct.

Production `Client/Impl/Stats.cxx:419-433,453-469` nevertheless dispatches the time-played type whenever the older HAS_IUSERTIMEPLAYEDRETRIEVELISTENER flag is true. `Client/Impl/ListenerRegistrar.hxx:213-227,232-250` selects a set using the inherited static tag and C-casts every IGalaxyListener to the requested class; `ListenerRegistrar.cxx:34-47,137-145` stores/iterates that set. A correctly registered leaderboard-retrieve listener plus a legitimate cached-self RequestUserTimePlayed call is enough to select that leaderboard object as a time-played receiver. No intentionally misregistered listener or concurrent destruction is required. The callback signatures differ (`const char*` versus GalaxyID); the wrong downcast/invocation is statically unsafe and can present as a bad string pointer or x86 call-frame mismatch. Runtime crash manifestation is unexecuted.

**Handoff:** coordinate a first-party compatibility dispatch policy for these three bundled SDKs; discriminate actual listener types safely or adapt their registration/notification mapping without globally changing ABI identifiers. Merely enabling the UPDATE flag or editing excluded SDK headers is not a safe blanket fix. Proposed focused validation: register only a correctly typed leaderboard listener, request time played, pump, and require no wrong callback; then add both listener types and verify each result separately on the three affected versions and 1.76.0. This is outside BUILD-owned files and has not been assigned an extra BUILD ID; coordinator/CORE/STORAGE should disposition it against their full evidence.

### STORAGE: undefined persona feature read removes both intended sign-in notification bodies

`Client/Impl/User.cxx:67,655` reads `GALAXY_BUILD_FEATURE_HAS_IFRIENDS_ONPERSONADATACHANGED`; the table defines `GALAXY_BUILD_FEATURE_IFRIENDS_ONPERSONADATACHANGED` at line 16. The nonexistent macro evaluates to 0 under normal generated definitions, removing lines 68 and 656 for every version, including the 67 selected versions from 1.61.0 onward that support the listener. This is a confirmed spelling/gating mismatch, not a new feature-table interval error.

**Handoff:** STORAGE should correct the consumer name in a future implementation change and validate the intended notification contract. The suppressed calls use PERSONA_CHANGE_NONE during sign-in; this review does not assume that a particular game is contractually owed a persona-change callback merely because authentication succeeded. The preexisting/current User sidecar's auth lifetime/timeout IDs and ADD-STORAGE-005 concern other mechanisms. A read-set-minus-defined-set check would catch this spelling without native binaries.

## Comparison with preserved review and confidence

After independent input inspection, read baseline BUILD and WRAPPER-COVERAGE in full and checked their path sets and recorded identities mechanically. Their counts, equivalence classes and baseline input hashes agree. No wrapper conclusion was silently rewritten. The earlier representative SDK inspection is now supplemented by the full version/declaration/export/read evidence above. BASE-INTERCEPT-006/007, BASE-UTIL-015 and cross-owner addenda retain their identities; no prior build success is reclassified as a failed build.

High confidence: exact input coverage/equality, empty/dispatcher/manifest identities, implemented CMake interval algorithm, measured declaration-sentinel results, explicit export spellings, source target graph and the conditional ADD-BUILD-001 failure path. Limits: sentinel checks are not a full C++ preprocessor/type checker; two unused feature meanings remain unresolved; aggregate feature flags can cover more than the sentinel; SDK headers do not prove proprietary binary export/vtable/ordinal behavior; x86, Release, optional targets and full 69-version compilation remain unexecuted. No complete absence-of-defects claim is made.

## Verification record and prioritized next steps

Executed only static/read-only evidence modes, from the repository root:

```text
python -B .ai/review-addendum/BUILD-static-audit.py inventory
python -B .ai/review-addendum/BUILD-static-audit.py features
python -B .ai/review-addendum/BUILD-static-audit.py consumers
python -B .ai/review-addendum/BUILD-static-audit.py exports
python -B .ai/review-addendum/BUILD-static-audit.py notebooks
python -B .ai/review-addendum/BUILD-static-audit.py inheritance
python -B .ai/review-addendum/BUILD-static-audit.py numbers
python -B .ai/review-addendum/BUILD-static-audit.py resolvers
```

Earlier probe iterations intentionally surfaced differences for manual investigation; final counts/checksums above refer to the corrected declaration mappings. Export parsing includes ordinal-free entries and Errors.h's GetError declaration. No intermediate lexical mismatch is promoted directly to a defect.

Final read-only scoped production diff against the baseline was empty. `git diff --check` on the two amended BUILD-owned source sidecars produced no diagnostics. The report was read back, and the final feature/reader audit retained the recorded 10,371-cell checksum and single undefined reader name.

1. **Immediate owner follow-up:** disposition the historical listener collision and preserve exact supported-caller reproduction conditions.
2. **Near term:** make individual interceptor-mode testcase targets own a runtime-staging dependency; validate the graph and staged names as proposed in ADD-BUILD-001, without repeating the already successful 15 production builds merely as review evidence.
3. **Contract validation:** where a matching native SDK becomes available to its owner, compare names/ordinals only at the header/def disagreements and resolver boundaries. No credentials or SDK execution is necessary for an export-table check.
4. **Maintenance:** add a feature-reader-name check, preserve the two unresolved metadata flags as questions until their intended contracts are known, and prefer tuple/named-feature gates over future concatenated numeric thresholds.
