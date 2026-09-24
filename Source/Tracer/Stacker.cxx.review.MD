# Fresh review — Stacker.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–264. Windows static review; no crash injection/debugger session.

## Inspection notes and recursive UEF reachability
- The active registration is `SetUnhandledExceptionFilter(OurCrashHandler)` at line 241; the terminate detour and hook body are comments. `GetInstance` has one function-static singleton and private Init. The saved previous filter is called only after the local KeepCount has been destroyed and the wait finishes.
- The active call graph has no explicit recursive call to OurCrashHandler. The callback's nested guard at 105–107 does not itself re-enter it. A same-thread recursive entry during an outer callback **would** encounter an outer entered_counter at line 216, but this is a conditional mechanism, not a confirmed reachable defect.
- Microsoft Learn's [SetUnhandledExceptionFilter contract](https://learn.microsoft.com/en-us/windows/win32/api/errhandlingapi/nf-errhandlingapi-setunhandledexceptionfilter) confirms fault-thread context and saved-filter chaining; it does not guarantee that an exception thrown inside a UEF recursively invokes the same UEF. No OS-version-specific repro was executed. Therefore **no confirmed recursive-UEF deadlock finding** is made. Registration chaining, callback exceptions and Windows nested-filter dispatch require isolated validation before such a claim.
- Concurrent crash callbacks can call DbgHelp-backed walking; cross-thread symbol-library serialization remains validation work. The counter wait is after callback completion and is not mutual exclusion. This review does not claim to have reproduced concurrent-fault corruption.

### [BASE-SERVER-009] Crash logging and minidumps discard the original Windows exception context

- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Tracer/Stacker.cxx:102–117,161–175,207–214`; `Source/Tracer/MiniDump.cxx:14–40,48–50,81–84`.
- **Affected scope:** Windows unhandled SEH crash reports and their minidumps.

**Evidence.** OurCrashHandler receives `EXCEPTION_POINTERS* ExceptionInfo` but calls StackerUnhandledExceptionCallback without it. That callback obtains `std::current_exception` and uses the default StackWalker plus `ShowCallstack()` without CONTEXT. The inspected dependency initializes this constructor as NonExcept (`StackWalker.cpp:792–795`), and a missing context causes a current-context capture (`989–1003`). MiniDump separately synthesizes exception code 0 and a context captured in GetExceptionPointers.

**Failure mechanism.** For a native access violation, the original record contains the fault instruction, registers and access information, but none are forwarded to logging/dump writing. A C++ current_exception is not a substitute for native ExceptionInfo. The stack walk starts in crash handling, and the dump's exception stream describes its helper with code zero rather than the original fault. Filtering helper frames cannot reconstruct the discarded register state.

**Impact.** Crash diagnosis can identify the handler instead of the fault and loses essential native fault details. Useful memory/other stack evidence may remain; this is degraded optional diagnostics, not proof that the crash reporter causes the original game crash.

**Alternatives / recommendation.** Pass the original exception pointers and fault thread ID through the internal crash path. Walk a copy of `*ExceptionInfo->ContextRecord` (walking may mutate context) and give the original record/context to MiniDumpWriteDump. Log SEH code/address/access details explicitly. Retain a separately named current-process snapshot operation if needed; do not label synthesized context as an original exception.

**Verification.** In an isolated Windows x86/x64 test process outside a debugger, fault at a known noinline instruction. Inspect `.exr -1` and `.ecxr` in the produced dump: code/address/registers must match the injected fault, not GetExceptionPointers. Test a C++ unhandled exception separately. Not executed.

### [BASE-SERVER-017] Enabling minidumps alone never reaches dump creation

- **Severity:** Low
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Tracer/Stacker.cxx:165–175,207–214`; `Source/Tracer/Tracer.cxx:163–171,217–224`.
- **Affected scope:** Configuration with MiniDumpOnUnhandledException=true and UnhandledExceptionLogging=false.

**Evidence.** InitTracing stores the two options independently. Disabling exception logging stores a null callback. OurCrashHandler calls the only dump-producing helper exclusively inside `if (cb != nullptr)`.

**Failure mechanism.** Even with the minidump flag true, a crash bypasses the helper because textual logging was disabled; the dump flag is never checked.

**Impact.** An explicitly requested diagnostic artifact is absent for this option combination. The feature is optional and off by default, so severity is Low.

**Alternatives / recommendation.** Drive crash processing when either dumps or logging are enabled, allowing a null textual callback, or explicitly couple/validate the settings and document the dependency. Prefer independent behavior because they are separate configuration keys.

**Verification.** Test all four logging/dump option combinations in isolated faulting processes. For dump-only, require a valid original-context dump and no textual exception log.

## Follow-up addendum — 2026-09-24

Fresh full source read: lines 1–264, plus Stacker/MiniDump/Tracer headers and implementations. Existing findings and original wording above are preserved.

### [ADD-SERVER-003] A long symbol source path throws before the crash report and dump

- **Severity:** Low
- **Confidence:** High (conditional mechanism established from dependency source; no fault injected)
- **Category:** Correctness
- **Location:** `Source/Tracer/Stacker.cxx:64–85,161–175,207–220`; `Source/Tracer/Stacker.hxx:12–21`.
- **Affected scope:** Windows exception diagnostics with an unfiltered frame whose symbol source-file path exceeds 260 characters; exception logging must be enabled to enter this callback.

**Evidence.** `CallEntryFile.path` is `boost::static_string<260>`. `MyStackWalker::OnCallstackEntry` implicitly constructs it from the entire `entry.lineFileName`, without truncation or a catch. The actual StackWalker dependency permits a 1024-byte filename field (`Source/Vendor/StackWalker/Main/StackWalker/StackWalker.h:133–157`) and copies the DbgHelp source filename into it (`StackWalker.cpp:1134–1142`). The vendored Boost null-terminated constructor calls range assign (`Source/Vendor/boost/boost/static_string/static_string.hpp:1235–1243`), which throws `std::length_error` when size exceeds capacity (`6681–6705`). PDB source names are diagnostic strings, not filenames opened by this code; no 260-character filesystem cap is imposed on them here.

**Failure mechanism.** A valid unfiltered 261–1023-character source path reaches line 85 during `ShowCallstack()`. Construction throws before the callback returns. The catch sequence at 113–159 protects only exception-type identification, not the later walk. Consequently the normal calls to textual logging (165), minidump creation (175) and saved-filter chaining (220) are not reached on that invocation. This is a direct C++ exception path; it does not require or establish recursive Windows UEF dispatch or a self-wait deadlock.

**Impact.** A long debug-info path can suppress the requested diagnostic artifact for an already-faulting process. Severity is Low because diagnostics are optional and the trigger requires such symbol information. The proven result is interrupted reporting, not a claim of causing the original crash or of a particular Windows nested-exception outcome.

**Possible solutions.** Bounded, explicit truncation with a marker; a larger fixed field plus a bounded conversion; or dynamically sized fields with an independent best-effort reporting fallback. Merely enlarging the field leaves other allocation/formatting failures able to skip the dump.

**Recommended resolution.** Make frame conversion explicitly bounded and nonthrowing for oversize text, record truncation, and isolate stack/text collection failure from the original-context dump path. Keep original exception preservation from BASE-SERVER-009. Avoid unbounded fault-handler allocation as the sole fix.

**Verification.** Proposed focused frame-conversion cases at lengths 259, 260, 261 and 1023; require bounded strings and a truncation indication without an exception. Then use an isolated Windows process/PDB with a long source path and require a report/dump even if symbolic walking fails. Check the original exception context separately. Nothing was built, executed or faulted in this pass.

### [BASE-SERVER-009] Addendum — retained against native contracts

Retain **Medium / High confidence / Correctness**. `ExceptionInfo` is still omitted from the callback and dump interface. The default dependency constructor selects `NonExcept` (`StackWalker.cpp:792–795`), and the no-context walk captures the handler's current context (`989–1003`). Microsoft's [MiniDumpWriteDump contract](https://learn.microsoft.com/en-us/windows/win32/api/minidumpapiset/nf-minidumpapiset-minidumpwritedump) defines `ExceptionParam` as the exception causing the dump and explicitly calls for capturing/passing the calling thread's prior state. Synthetic code zero and helper registers do not meet that purpose. Preserve the original pointers for synchronous writing or copy their records for any deferred work; do not retain borrowed native pointers beyond their established lifetime. Original proposed verification stands.

### [BASE-SERVER-017] Addendum — retained dump-only reachability

Retain **Low / High confidence / Correctness**. `Trace::SetUnhandledExceptionLogging(false)` still publishes a null callback; `OurCrashHandler` only calls the dump-containing helper inside `cb != nullptr`. Installing the UEF nevertheless does not make that helper reachable. Independent dump/log option handling is still required, including when textual stack collection fails (ADD-SERVER-003).

### Resource/concurrency limits, without additional finding counts

The singleton is process-lifetime and initialization is once per linked instance. `KeepCount` ends before its caller waits: the normal path does not wait on its own count. The [SetUnhandledExceptionFilter contract](https://learn.microsoft.com/en-us/windows/win32/api/errhandlingapi/nf-errhandlingapi-setunhandledexceptionfilter) documents fault-thread execution and previous-filter return values, not recursive reentry when this handler throws. No recursive-UEF deadlock or unload-time native use-after-free is established here. Concurrent callbacks would not be serialized by this counter; the dependency itself states it is not multithreading-enabled (`StackWalker.cpp:956–961`) and Microsoft requires DbgHelp serialization. Simultaneous-fault behavior remains proposed Windows validation, not reproduced corruption. The 128-entry check bounds collected frames, not the dependency's entire walking work. Minidump allocation/handle error paths are addressed in the companion addendum.
