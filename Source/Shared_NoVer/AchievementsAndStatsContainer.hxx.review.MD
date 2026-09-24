# Fresh baseline review: AchievementsAndStatsContainer.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Entire file read independently (105 lines). Static Windows-focused review, followed by coordinator runtime reproduction of BASE-UTIL-001. IDs are indexed in `.ai/review-baseline/UTIL.MD`.

## Checked
- Examined the union's raw 32-bit persistence, all four recursive-mutex callback wrappers, reference-returning APIs, atomic counter, and clock representation.
- Traced Cereal 1.3.2 input forwarding and arithmetic loading, `UserHelloDataMessage`, `RequestSpecificUserDataMessage`, server forwarding, and client stats assignment.
- The stat union intentionally transports the integer representation of float bits on the supported MSVC targets. Its inactive-member access is a portability limit; no Linux-runtime finding is asserted.
- The callback locks protect only callback execution. The synchronization defect and supported scalar/Copy callers are detailed as BASE-UTIL-002 in the implementation sidecar; an atomic PlayTime does not protect BootTime or the maps.

## Findings

### BASE-UTIL-001 — Deserialization discards the persisted play-time counter
- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Shared_NoVer/AchievementsAndStatsContainer.hxx:51-55`, `serialize`
- **Affected scope:** Client/server user snapshots and remote `GetUserTimePlayed`.

**Evidence / mechanism:** `ar(..., BootTime, PlayTime.load(), ...)` passes a temporary integer. Cereal's input archive accepts forwarding references, passes the named argument as an lvalue, and loads arithmetic bytes into that temporary (`cereal.hpp:728-731,850-854`; `portable_binary.hpp:275-283`). It never stores the value back into the atomic. This is a data-loss defect, not a compilation failure. A freshly received container retains PlayTime zero while receiving the sender's BootTime. The server stores this state and forwards it to other clients (`ServerHandlers.cxx:132-195`).

**Impact:** Previously accumulated play time loaded from Stats.ini is lost in network snapshots; peers see approximately the current session instead of total play time. A reused input object retains its previous counter instead.

**Possible fixes:** Split save/load and load through a local integer; or archive a local integer in `serialize` and conditionally store it for input archives. Keep the existing field width/order if wire compatibility is required.

**Recommended fix:** Explicit save/load functions with a local `uint32_t` and `PlayTime.store` after successful input. Coordinate snapshot locking with BASE-UTIL-002 and clock semantics with BASE-UTIL-003.

**Verification:** The coordinator serialized a real container with PlayTime 123456 through the bundled PortableBinary archives into a fresh container, linked against the built baseline no-version library. Output was `before=123456 after=0` on MSVC x64 Debug: the counter loss is reproduced. Prepopulated-object and end-to-end network cases remain proposed checks. See `.ai/review-baseline/VERIFICATION.MD` for the execution record.

## Thorough re-review addendum — BASE-UTIL-001 testing correction and retained disposition (2026-09-24)

- **Disposition / severity / confidence / category:** Retained; Medium / High / Correctness. Exact production location remains `Source/Shared_NoVer/AchievementsAndStatsContainer.hxx:51-55`.
- **Fresh mechanism check:** Bundled Cereal's input `operator()` forwards arguments (`cereal.hpp:728-731`), then passes the named argument to `processImpl` as an lvalue (`850-854`). Its arithmetic loader writes through that reference (`archives/portable_binary.hpp:275-283`). Loading into the temporary from `PlayTime.load()` is well-formed but never calls `PlayTime.store`. The atomic does not make input serialization self-updating. Field order/width must be preserved if the split load/save fix is wire-compatible.
- **Clearly labeled testing correction:** The assertion is **already present** in `Source/UnitTests/Shared/Networking/UserHelloDataMessageTests.cxx:13-28` and `RequestSpecificUserDataMessageTests.cxx:16-33`: both set play time to 12 and expect 12 after roundtrip. `MessageSerializationTestUtils.hxx:11-23` uses **BinaryOutputArchive/BinaryInputArchive**, while the network uses PortableBinary (`Shared/Networking/Networking.hxx:46-56,78-82`). `UnitTests/Versioned.cmake:6-22` includes those tests in the versioned shared target and registers discovery. Do not repeat an absent-serialization-test claim or imply these existing assertions use the production portable archive.
- **Options / recommended resolution:** Retain the original explicit input-store fix and complete snapshot-lock recommendation. Treat execution/enforcement of the existing assertions as immediate validation; adding a parallel PortableBinary/prepopulated-object case supplements existing coverage rather than replacing an allegedly missing test.
- **Verification status:** This pass read the two actual tests, helper and test wiring as context only. It performed no build/test. The baseline coordinator's reproduction above is preserved as prior evidence, not claimed as fresh execution. Proposed checks also load into a destination with a distinct nonzero PlayTime to prove the received field replaces it instead of merely retaining old state.
