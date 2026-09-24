# ABI — targeted BUILD handoff verification

Date: 2026-09-24. Requested production baseline: **`b30e83872c0006e8240c8b4f565da5351bf10080`**. Observed HEAD: `48cea8c6c48fa41fddd348a0119129cc5643fc8b`. Read-only scoped Git diffs found no baseline differences in the production/SDK evidence paths listed below. Existing report content was preserved; changes are report-only appendices plus this notebook.

## Disposition

| Handoff | Result | Accounting / primary report |
| --- | --- | --- |
| 1.73.0/1.74.0/1.75.0 listener inheritance collision | **Confirmed new ADD-ABI-001 — High severity, High confidence, API/ABI / Memory Safety.** Correctly registered application listeners are downcast to an unrelated interface by production dispatch. | One new finding, primary [ListenerRegistrar.hxx.review.MD](../../Source/Client/Impl/ListenerRegistrar.hxx.review.MD); [Stats.cxx.review.MD](../../Source/Client/Impl/Stats.cxx.review.MD) has a coordination cross-reference. |
| Undefined persona macro in User | **Spelling/gating mismatch confirmed; distinct unconditional sign-in callback violation not established.** | **No ADD-ABI-002.** Appended [User.cxx.review.MD](../../Source/Client/Impl/User.cxx.review.MD) clarification; existing BASE-API-005 remains primary in [Friends.cxx.review.MD](../../Source/Client/Impl/Friends.cxx.review.MD). |

New counts from this task: High 1; Medium/Low/Critical 0. BUILD's unnumbered listener handoff and INTERCEPT's legacy-SDK anomaly note are not additional findings. BASE-CORE-001/002 deal with cancellation/lifetime; ADD-STORAGE-004 deals with unhydrated remote playtime. Neither mechanism explains or repairs this cached-self, live-listener type confusion.

**Coordinator execution update:** The actual SDK 1.73.0/production registrar was subsequently compiled in an isolated MSVC x64 ASan-enabled probe and executed. It selected one incompatible listener from equal tag 26 and delivered one wrong leaderboard success callback for a time-played event. The spy did not inspect the incorrectly typed argument. No full client/server session or x86 probe ran. [VERIFICATION.MD](VERIFICATION.MD) records commands, harness limits and observed output; owner-local static-only statements below describe the earlier stage.

## Scope and evidence limits

- Read all of production `ListenerRegistrar.hxx` (418 lines), `ListenerRegistrar.cxx` (239), `Stats.cxx` (504) and `User.cxx` (673). Read relevant Stats declarations, Friends implementation/SDK contracts, legacy API factory/pump, local-ID predicate, event routing, `DelayRunner`, argument lifetime extender and build feature definitions. Compared the existing CORE/Stats/User/Friends findings and BUILD handoff before assigning the new ID.
- SDKs are contract/ABI evidence. Fully read 1.73.0 `IStats.h`, `IListenerRegistrar.h`, `GalaxyID.h`, `GalaxyApi.h`, `IFriends.h`; independently read 1.74.0/1.75.0 colliding interfaces, request declarations, registrar enum/base and GalaxyID definitions; checked the fixed 1.76.0 interfaces/enum and request signatures. Persona contract context also includes 1.61.0 and 1.152.11 `IFriends.h`/`IUser.h` excerpts. No complete all-version SDK audit is claimed here.
- Static Read/Glob/Grep, read-only `git --no-optional-locks rev-parse HEAD` and scoped `git --no-optional-locks diff --exit-code <baseline> -- <paths>` were used. The source/SDK diffs emitted nothing and succeeded. External documentation/compiler source was fetched read-only for Microsoft ABI rules.
- **No configure, build, test, runtime probe, compiler layout dump, disassembly, native SDK execution, Git mutation or credential-file access.** Probe code below is a design recorded in this Markdown only. No executable/source probe file was created. No production or SDK source was patched.

## Exact listener/version evidence

| SDK | `IStats.h` leaderboard / time-played base | Success / failure declarations | Public request | Registrar IDs |
| --- | --- | --- | --- | --- |
| 1.73.0 | `276 / 313`: both `GalaxyTypeAwareListener<LEADERBOARD_RETRIEVE>` | leaderboard `291 / 307`; time `324 / 340` | `RequestUserTimePlayed(GalaxyID = GalaxyID())` at 777; contract 770-787 | `IListenerRegistrar.h:28-61`: leaderboard 26; no time-played enumerator |
| 1.74.0 | same, independently read | same | same signature at 780; contract 773-790 | `28-62`: leaderboard 26; no time-played enumerator |
| 1.75.0 | same, independently read | same | same signature at 780; contract 773-790 | `28-65`: leaderboard 26; no time-played enumerator |
| 1.76.0 control | `276 / 318`: leaderboard tag / **USER_TIME_PLAYED_RETRIEVE** | leaderboard `291 / 307`; time `329 / 345` | same signature at 785 | `28-66`: leaderboard 26, time-played **33** |

Paths in this table are `Source/DLLs/<version>/galaxy/<header>`. `GetListenerType()` is static: 1.73.0 registrar `79-92`, 1.74.0 `80-93`, 1.75.0 `83-96`. There is no hidden virtual type discriminator. The existing global leaderboard helper registers the inherited tag; the time-played global typedef first appears in the 1.76.0 control (`IStats.h:351`). Lack of the older typedef does not remove the declared `RequestUserTimePlayed` method or its listener interface.

`Source/galaxy_sdk_features.cmake` has the expected boundaries: leaderboard availability at 37, time-played availability at 52, corrected-time-listener UPDATE at 66, per-call Stats listeners at 135, typed Register enum parameter at 137. Consequently these three affected SDKs use `Register(uint32_t, IGalaxyListener*)`, global-only Stats requests, and the **enabled** time-played dispatch body. UPDATE being false does not suppress it.

## Exact supported client call/callback trace

Precondition: a normal initialized matching-version client, signed in through the public auth callback/pump sequence. This is a source trace, not an assertion that a native session was executed.

```text
L : ILeaderboardRetrieveListener, with both callbacks implemented and L kept alive
ListenerRegistrar()->Register(L::GetListenerType(), &L)          // correct tag 26
self = User()->GetGalaxyID()                                   // concrete local ID
Stats()->RequestUserTimePlayed(self)                           // ONE argument
ProcessData()
    -> queued time-played success dispatched via shared tag 26
    -> L.OnLeaderboardRetrieveSuccess(const char*)               // WRONG callback
ListenerRegistrar()->Unregister(L::GetListenerType(), &L)
```

1. The SDK's convenience calls use `GalaxyFactory::GetInstance()` (`1.73.0/GalaxyApi.h:294-310,357-365,390-398`). UniverseLAN's legacy `GalaxyImpl` forwards `GetStats`, `GetListenerRegistrar` and `ProcessData` at `Source/Client/GalaxyApiFactory.cxx:92-94,126-136`. `GalaxyDLL.cxx:92-94,120-122,176-178` returns the actual interface instances.
2. Initialization constructs the real registrar, User and Stats in `UniverseLAN.cxx:45-60`. `User.cxx:24-35` establishes local entries; `User.cxx:49-53` returns the configured ID. `Shared/IniData.cxx:921-926` recognizes that ID as self and `User.cxx:594-599` returns cache-present immediately. The documented default `GalaxyID()` also takes the self branch, but the primary trace deliberately uses the concrete ID.
3. `Stats.cxx:419-433` queues `&IUserTimePlayedRetrieveListener::OnUserTimePlayedRetrieveSuccess, userID`. The operation-specific argument is absent in these versions. There is no precondition to retrieve a leaderboard or remote statistics for this call; the SDK places the retrieval prerequisite on **GetUserTimePlayed**, not on this request. Registering only L is enough; if the game also registers a real time-played listener for completion, L is still incorrectly included.
4. `ListenerRegistrar.hxx:309-321` binds copied arguments into the production `DelayRunner`; `Client_NoVer/Impl/NotificationParamScopeExtender.hxx:26-37,61-70` retains the `GalaxyID` value semantics. `GalaxyDLL.cxx:166-173` runs delayed work after network events; `Client_NoVer/Impl/DelayRunner.cxx:7-10` invokes it.
5. `ListenerRegistrar.hxx:213-227` extracts `T = IUserTimePlayedRetrieveListener`, chooses inherited tag 26, C-casts L to that unrelated type, and invokes the time-played virtual member pointer. `ListenerRegistrar.cxx:34-47,88-117,137-145` stores and visits L without any actual-interface check. A non-null assertion leaves the invalid downcast undetected.

No concurrency is needed: **register -> request -> pump -> unregister**. No unregister occurs before dispatch. A listener registered between request and pump is also picked up because the global set is selected at delivery, but that timing variation is unnecessary. Cache hydration fixes and generation-bearing lifetime tokens alone leave this defect intact.

Other reachable slots/directions:

- Remote response: `ClientNetworkHandlers.cxx:107-109` -> `Stats.cxx:453-469` -> `NotifyAllNow(nullptr, ...)` -> global overload at `ListenerRegistrar.hxx:235-236`. Both success and failure use the shared tag.
- Reverse failure: explicitly register a real time-played listener using its SDK accessor; `Stats()->FindLeaderboard("board")` queues `OnLeaderboardRetrieveFailure` (`Stats.cxx:380-392`) and reaches the time-played failure slot. `FindOrCreateLeaderboard` has the same result (`395-415`); its legacy sort/display parameters are **const references**, as declared in these SDKs. No unsupported modern per-call listener argument is part of this sequence.
- The leaderboard stubs do not generate legitimate success results. Nevertheless, wrong-interface dispatch can invoke a leaderboard success callback; the Stats report now explicitly qualifies its earlier success-unreachable note.

## Signature slots and ABI deduction

For a concrete listener deriving normally from either of these single-inheritance SDK interfaces, the Microsoft C++ vftable has one inherited deleting-destructor function slot followed by the two callbacks. `GalaxyTypeAwareListener` contributes no further virtual methods.

| Zero-based function slot | Byte offset x86 / x64 | Leaderboard | Time played |
| --- | --- | --- | --- |
| 0 | 0 / 0 | virtual deleting destructor | virtual deleting destructor |
| 1 | 4 / 8 | `void (const char*)` success | `void (GalaxyID)` success |
| 2 | 8 / 16 | `void (const char*, LB::FailureReason)` failure | `void (GalaxyID, TP::FailureReason)` failure |

`LB` and `TP` abbreviate the respective SDK interfaces. A virtual-member pointer dispatches by the encoded slot; it does not look up the intended callback's name in the actual object's type. Both failure enums declare only `FAILURE_REASON_UNDEFINED`, value zero. Equal enum values do not compensate for the incompatible first parameter. These slot numbers count function entries, not any preceding RTTI metadata.

For completeness, counting the actual legacy **IStats** declarations (destructor slot 0) gives `FindLeaderboard` slot **30**, `FindOrCreateLeaderboard` **31**, `RequestUserTimePlayed` **32**, and `GetUserTimePlayed` **33** in all three affected headers. These public method calls reach matching overrides; the mismatch occurs later in the **listener** table at slots 1/2. The registrar bucket number **26** is a third, separate index, not a virtual-function slot.

### GalaxyID is not a plain integer argument

All three `GalaxyID.h` files have `#pragma pack(push, 1)` at 22, user-defined copy construction at `63-65`, assignment at `73-77`, and only the `uint64_t value` data member at 153. They specify an eight-byte nontrivially copy-constructible class with trivial destruction. The `void` callbacks have no hidden structure-return argument.

| ABI / call site | Supplied argument positions | Wrong receiver interpretation / consequence |
| --- | --- | --- |
| MSVC x64 time success -> leaderboard | `RCX=this`, `RDX=&GalaxyID_parameter_copy` | RDX becomes `name`; binary ID bytes mistaken for a C string. It is **not** the ID numeric value as a pointer. |
| MSVC x64 time failure -> leaderboard | as above, `R8D=TP::FailureReason` | same wrong string; reason remains in the matching machine argument position |
| MSVC x64 leaderboard failure -> time | `RCX=this`, `RDX=name`, `R8D=LB::FailureReason` | name buffer mistaken for a GalaxyID object; eight bytes interpreted as ID, possibly reading past a short string |
| MSVC x86 time success -> leaderboard | `ECX=this`; entry `[ESP+4]=ID low`, `[ESP+8]=ID high` | low word read as pointer; callee pops 4 argument bytes when the caller supplied 8 |
| MSVC x86 time failure -> leaderboard | low/high ID at `+4/+8`, reason at `+12` | low word read as pointer, high word read as reason; callee pops 8 instead of 12 bytes |
| MSVC x86 leaderboard failure -> time | name pointer at `+4`, reason at `+8` | those two words become ID; reads reason at unsupplied `+12`; callee pops 12 instead of 8 bytes |

The x86 table uses callee-entry ESP (return address at `[ESP]`), default nonvariadic `__thiscall`, and ordinary four-byte enums/pointers. The packed GalaxyID has no over-alignment requirement and is constructed in its stack argument area. The x64 table uses indirect passing for a class with this nontrivial copy constructor. The common x64 register shape avoids a stack-pop mismatch, but does not avoid C++ undefined behavior or invalid data/lifetime interpretation. Optimizations, stack-frame restoration and callback bodies affect the visible failure. Neither a guaranteed crash nor proprietary DLL behavior is inferred.

Read-only ABI corroboration:

- [Microsoft x64 calling convention](https://learn.microsoft.com/en-us/cpp/build/x64-calling-convention?view=msvc-170): register positions and argument layout. Its aggregate-size summary alone is insufficient to classify this nontrivial C++ parameter.
- [Microsoft `__thiscall`](https://learn.microsoft.com/en-us/cpp/cpp/thiscall?view=msvc-170): x86 ECX `this`, stack arguments and callee cleanup.
- [LLVM 19.1.7 MicrosoftCXXABI.cpp](https://github.com/llvm/llvm-project/blob/llvmorg-19.1.7/clang/lib/CodeGen/MicrosoftCXXABI.cpp), `MicrosoftCXXABI::getRecordArgABI`: records not passable in registers use `RAA_DirectInMemory` on ordinary x86, `RAA_Indirect` on x86_64. The destructor-layout notes also describe the single virtual-destructor table entry. This corroborates the Microsoft ABI deduction; it is not a compiler run on this project.

## Persona handoff: what is and is not established

**Confirmed mechanism:** `User.cxx:67,655` reads `GALAXY_BUILD_FEATURE_HAS_IFRIENDS_ONPERSONADATACHANGED`; the only feature-table name at `Source/galaxy_sdk_features.cmake:16` is `IFRIENDS_ONPERSONADATACHANGED`. The generator at `290-305` adds the standard `GALAXY_BUILD_FEATURE_` prefix and emits 0/1. Both undefined User `#if` expressions therefore exclude their bodies under the normal build. Source/build searches found no definition/alias for the misspelling. The correct flag starts at 1.61.0; neither branch is an interval-comparison failure.

**Contract check:** both removed calls notify local self with NONE after auth success (`User.cxx:55-73,642-660`), without a persona data mutation at either site. SDK 1.61.0 `IFriends.h:34-63,131-138` and 1.73.0 `IFriends.h:32-61,207-215` define change notifications and explicit user-information responses. 1.73.0 `IUser.h:225-263` and 1.152.11 `IUser.h:414-443` identify auth/operational listeners for sign-in. No unconditional post-sign-in self-persona promise was found in these contracts; an SDK-wide `IUser.h` search also found no persona-listener reference. This is not proof that native SDKs never send one.

**Positive obligation / counterevidence:** 1.152.11 `IFriends.h:645-667` promises explicit-request callbacks and automatic retrieval for friends/lobby peers; `58` defines NONE as no change. Production `Friends.cxx:38-54,87-99` uses the correct macro for its explicit retrieval notifications, including self. It also reports self information available (`103-107`). Thus the typo does not erase every persona notification or prove that explicitly requested self information cannot complete.

**Existing finding relationship:** BASE-API-005 covers missing automatic retrieval/publication and remote hello/nickname updates routed through `User.cxx:297-319`. Re-enabling a self/NONE notification at sign-in cannot fix remote readiness or change flags. The User appendix records the spelling mismatch, contract qualification and coordination with that existing ID. **ADD-ABI-002 is not assigned.** Future validation should separate unchanged sign-in, explicit self information retrieval and actual persona change, and use a matching native trace/product policy to settle the intended extra sign-in event.

## Small standalone Windows probe design — not built or executed

**Purpose:** demonstrate the actual SDK/production registrar dispatching a time-played success into a correctly registered leaderboard callback. Start with **MSVC x64 /Od**, so observing the wrong callback need not dereference a bogus name or return through the known x86 pop mismatch. This is a registrar/queue microprobe; the supported public Stats route into it is proven separately above.

**Build arrangement for a future authorized run:** one external executable, using a single selected SDK and the corresponding production `universelan-lib-<version>` static target plus its transitive dependencies, include directories and definitions (`Source/Client/CMakeLists.txt:8-17`, `Shared/CMakeLists.txt:19-36`, `Vendor/galaxy.cmake:8-13`). Match the target's MSVC architecture/configuration/CRT, C++20 and generated feature definitions. Keep probe source/output outside the checkout. Link the actual registrar and DelayRunner implementations, with the normal tracing implementation disabled at runtime; do not provide substitute SDK classes, registrar code or trace/link shims. Do not mix versions in one executable. The design needs no full client initialization, LAN server, configuration file or credentials. Reusing project target settings is important: the repository's root CMake uses `CMAKE_SOURCE_DIR`, so naively nesting it under an unrelated standalone root would change path resolution.

Suggested sole application translation unit (recorded here only):

```cpp
#include <Impl/ListenerRegistrar.hxx> // actual production header / selected SDK
#include <cstdio>
#include <type_traits>

using namespace galaxy::api;
using universelan::client::DelayRunner;
using universelan::client::ListenerRegistrarImpl;

struct BoardProbe : ILeaderboardRetrieveListener {
    unsigned success = 0, failure = 0;
    const char* seen = nullptr;
    __declspec(noinline) void OnLeaderboardRetrieveSuccess(const char* name) override {
        ++success;
        seen = name; // address observation only; never read or print as a string
    }
    __declspec(noinline) void OnLeaderboardRetrieveFailure(
        const char*, FailureReason) override { ++failure; }
};

int main() {
    static_assert(sizeof(GalaxyID) == 8);
    static_assert(!std::is_trivially_copy_constructible_v<GalaxyID>);
    universelan::tracer::Trace::SetTracingEnabled(false);
    DelayRunner queue;
    ListenerRegistrarImpl registrar(nullptr, &queue);
    BoardProbe board;
    const auto boardTag = ILeaderboardRetrieveListener::GetListenerType();
    const auto timeTag = IUserTimePlayedRetrieveListener::GetListenerType();
    std::printf("boardTag=%u timeTag=%u\n", unsigned(boardTag), unsigned(timeTag));
    registrar.Register(boardTag, &board); // genuine correct-type registration
    registrar.NotifyAll(
        &IUserTimePlayedRetrieveListener::OnUserTimePlayedRetrieveSuccess,
        GalaxyID(0x0102030405060708ULL)); // synthetic value; no network/API request
    if (board.success != 0 || board.failure != 0) {
        registrar.Unregister(boardTag, &board);
        return 2; // queue unexpectedly delivered synchronously
    }
    queue.Run();
    registrar.Unregister(boardTag, &board);
    std::printf("leaderboard-success=%u leaderboard-failure=%u\n",
                board.success, board.failure);
    return (board.success != 0 || board.failure != 0) ? 1 : 0;
}
```

The `nullptr` InterfaceInstances is deliberate: the inspected registrar constructor merely stores it (`ListenerRegistrar.cxx:16-21`); this registration/notification path never dereferences it. The real `DelayRunner` is supplied. BoardProbe is a plain manual SDK listener so its construction cannot auto-create a Galaxy singleton. Both objects outlive delivery and explicit unregistration precedes destruction. The synthetic ID serves only the isolated dispatch probe; the full-client reproducer uses the real signed-in self ID.

**Expected observations, not execution results:**

- 1.73.0/1.74.0/1.75.0 before a fix: tags `26/26`; under ordinary MSVC virtual dispatch, `leaderboard-success=1`, failure 0, exit 1. No time-played listener exists in the probe. The wrong callback counter itself is the evidence; dereferencing `seen` is unnecessary.
- 1.76.0 control: tags `26/33`; no receiver in the time bucket, both counters 0, exit 0. Verify an additional correctly typed time-played receiver actually gets its callback, to distinguish isolation from a broken queue.
- Debugger observation: break at BoardProbe's success entry; inspect the caller's virtual member dispatch and x64 RDX pointing to the copied GalaxyID. The supplied eight bytes contain no NUL, but the probe never treats them as a string. All value/address inspection should be while the parameter object remains alive.
- Additional small cases: time-played failure with board-only registration (wrong slot 2); a real time listener with board failure; both real listener types registered (each must receive only its intended result); normal leaderboard failure as a positive routing control. Keep each ABI-violating case in its own process.
- x86 follow-up: break at callback entry, verify ECX, stack words and 4/8 versus 8/12 byte cleanup obligations. Do not require normal exit as the reproduction signal; incorrect cleanup may disrupt return even if the callback ignores its arguments. A compiler/disassembly inspection would establish the exact generated instruction sequence, not just the ABI deduction.
- After correction: all three legacy versions must avoid cross-interface callbacks while retaining properly typed delivery under the chosen supported-client RTTI/type-information policy. Test full `RequestUserTimePlayed(self)` / `ProcessData` and actual `FindLeaderboard` failure separately to validate Stats integration. No source patch or invented modern listener parameter is needed to reproduce the original fault.

## Resolution priorities and completion record

1. Coordinate CORE/Stats ownership of ADD-ABI-001. Use verified interface discrimination/internal typed records while preserving SDK-facing numeric tags. `dynamic_cast` requires usable cross-module client RTTI; the public tag/erased pointer alone cannot distinguish these legacy interfaces. Define the support fallback when that information is unavailable; do not emit an equally unsafe failure through the shared tag.
2. Correct the persona reader spelling in future implementation work, but keep behavior/notification claims tied to actual retrieval/change guarantees. BASE-API-005 remains the owner of remote automatic persona publication.
3. Execute the proposed standalone probe only in a separately authorized Windows validation pass. This review establishes source-level reachability and ABI incompatibility, not a measured crash frequency or proprietary SDK dispatch implementation.

Reporting artifacts from this task: appended the full finding to `ListenerRegistrar.hxx.review.MD`, appended the Stats coordination note and User clarification, and added this notebook. Original findings were not rewritten or renumbered. The probe remains a small design inside the report.
