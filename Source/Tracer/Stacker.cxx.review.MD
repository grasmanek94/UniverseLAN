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
