# Fresh baseline review — Logger.cxx

- Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`.
- Coverage: entire file, lines 1–119; static Windows-focused review.

## Specific checked notes

- Checked directory creation/error reporting, per-instance file ownership, timestamp/thread/counter filename construction, all six logging levels, and destructor flush.
- The process-local counter is atomic. MSVC's thread-local CRT time storage was taken into account; the `localtime` call is not reported as a generic Linux-style shared-buffer race.
- The varargs path correctly uses `va_copy` for its sizing pass and ends both lists. Its output length is nevertheless used incorrectly below. Negative `vsnprintf` results and allocation failure handling remain additional robustness validation items, not separate counted findings.
- Each record's final insertion is locked, but the stream-state test is outside that lock. SDK 1.152.11 `GalaxyApi.h:310–314` states general API thread safety.

## Confirmed findings

### BASE-CORE-009 — Every formatted log record includes its terminating NUL byte

- **Severity:** Low
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Client/Impl/Logger.cxx:69–79`, shared logging macro.
- **Affected scope:** All ILogger levels whenever the log file is open.

**Evidence**

`vsnprintf` returns the character count excluding the terminator. The code allocates `iLen + 1` bytes, then constructs `std::string logstr(zc.data(), zc.size())`. Inserting that string into the stream writes its full size, including the terminating zero.

**Failure mechanism**

For `Info("hello")`, the vector holds six bytes (`hello` and NUL), and the string keeps all six. The logger writes that NUL before the newline. Empty messages also generate an embedded NUL record.

**Impact**

Nominal text logs contain binary bytes; text tools can classify them as binary, truncate displayed records, or mishandle parsing. This is a diagnostic-format defect rather than corruption of application data.

**Possible solutions**

1. Construct the string with the validated formatted length `iLen`.
2. Write exactly the successful formatter's returned byte count directly, excluding the terminator.

**Recommendation**

Validate formatting success and use the actual character count rather than buffer capacity. Preserve the existing prefix/newline format.

**Verification**

Log plain, formatted, empty, and long messages; inspect output bytes and assert no NUL unless explicitly requested by the caller's formatting. Not executed.

### BASE-CORE-010 — Stream-state reads race with another logging thread's failed write

- **Severity:** Medium
- **Confidence:** High
- **Category:** Concurrency
- **Location:** `Source/Client/Impl/Logger.cxx:62–79`, especially the line-63 state test before the line-78 lock.
- **Affected scope:** Concurrent calls to the same ILogger when file I/O fails.

**Evidence**

Every level executes `if (logfile)` without holding `mtx`. Final `logfile << ...` operations occur under the mutex, but a failed insertion can update the same stream's error-state bits read by `operator bool`. An `ofstream` does not make these concurrent accesses safe by itself.

**Failure mechanism**

Thread A passes the state check, locks, and writes. A full disk, failed flush of the file buffer, or another I/O error causes its insertion to set stream state. Thread B concurrently evaluates the unlocked state check before it reaches the mutex. The read and write of the stream state have no synchronization relationship. Locking only the insertion does not protect the earlier read.

**Impact**

A storage failure during otherwise supported multithreaded logging causes a C++ data race and undefined behavior, potentially compromising diagnostics when they are needed most. The demonstrated conflicting-state path requires I/O failure, which bounds likelihood and severity.

**Possible solutions**

1. Perform the stream-state check and insertion under the same mutex.
2. Format into local storage first, then lock once and check/write the stream; keep all mutable stream access inside that lock.

**Recommendation**

Choose the second approach if formatting contention matters; otherwise lock from the state check onward. Apply the same discipline to flush/close/error-state handling. Concurrent destruction still requires the API's object-lifetime protocol and is not solved by this local mutex.

**Verification**

Use two concurrent log callers with an injected failing stream buffer or controlled write failure and barriers around state access. Verify the locking protocol through instrumentation/a race detector where supported; run a Windows stress/fault-injection case for integration. No race detector or I/O-failure test ran in this review.
