# Fresh review — Runner/Process.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–176. Windows-focused static review.

## Inspection notes
- Traced log creation/inheritance, CreateProcessW arguments and working directory, thread-handle closure, exit-code polling, forced shutdown/wait and handle closure.
- `readLines` snapshots file length, advances by actual bytes read and retains partial lines across polls. File-size truncation is not handled; ordinary operation creates one log per role, while model path aliases can break that assumption (**BASE-SERVER-013**).
- handleLine rejects undeclared/duplicate events, duplicate PASS and malformed SYSTEM_TEST records. Non-protocol diagnostics are ignored intentionally. Terminal log drain is the caller's responsibility: **BASE-SERVER-012**.
- quoteWindows is not a general CRT backslash/quote encoder. Actual generated arguments are constrained tokens or a control path with a fixed final component, so the trailing-backslash/embedded-quote counterexample is not established on the current call path and is not separately reported.
- POSIX branches were read for conditional compilation only; no Linux execution or review finding is asserted.

### [BASE-SERVER-015] Windows child arguments round-trip native paths through incompatible encodings

- **Severity:** Low
- **Confidence:** High (conditional on a non-UTF-8 Windows native narrow code page)
- **Category:** Portability
- **Location:** `Source/SystemTests/Runner/Process.cxx:39–41`; producer `Source/SystemTests/Runner/Main.cxx:119–121`.
- **Affected scope:** Windows test runs with non-ASCII executable/temp/control-directory paths.

**Evidence.** The executable is narrowed with `executable.string()`, and the control-directory argument is built with `(root / "control").string()`. The combined narrow command is then interpreted explicitly as UTF-8 by `fs::u8path(command).wstring()`. These conversions do not constitute a native-wide round trip on a Windows code page such as 1252.

**Failure mechanism.** An accented user/temp path can yield native narrow bytes that are not valid UTF-8; conversion throws or creates a different path. Supplying the correct wide executable separately to CreateProcessW does not repair the corrupted control-directory argument, which the child needs to locate its release file.

**Impact.** SystemTests fail setup or time out for affected local Windows paths; ASCII paths and UTF-8-native configurations are unaffected. Production DLL/server protocol behavior is unaffected.

**Alternatives / recommendation.** Build and quote the Windows command line as UTF-16 from native paths, with explicit UTF-8-to-wide conversion for textual arguments; alternatively make every narrow path producer consistently UTF-8. A complete Windows argument encoder should accompany that cleanup.

**Verification.** On Windows with a non-UTF-8 active code page, run from an isolated path and TEMP containing accented characters and spaces. Confirm the child receives the exact control path and finds its release file; retain ASCII and UTF-8-code-page cases.

## Follow-up addendum — 2026-09-24

### [BASE-SERVER-015] Addendum — encoding and caller constraints retained

Retain **Low / High confidence / Portability**, conditional on native narrow paths not being UTF-8. The current runner supplies `.string()` paths and reparses the assembled command through `u8path`, while CreateProcessW's separate native executable argument cannot repair the control-directory text. A complete fix must define both sides of the argument encoding (including the child's narrow `argv` to `u8path` conversion), not just change the API name to a W variant.

Fresh resource trace confirms normal CreateProcess success/failure closes the log and thread handles and `stopChild` closes stored process handles. The local log HANDLE is not RAII-protected if command conversion/allocation throws after creation; runner process exit bounds that failure-path leak, so it is not a separate new ID. The simplistic backslash quoting is not generalized into a current-path failure: generated tokens and the fixed final `control` path component do not establish a trailing-backslash/quote trigger. POSIX branches were read only, with no Linux execution. BASE-SERVER-012 remains the caller's final-drain defect.
