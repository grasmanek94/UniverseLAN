# Fresh review — Tracer.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–419. Static Windows review.

## Inspection notes
- Followed initialization publication, per-thread lazy file creation, scope Enter/Exit/depth accounting, global/console osyncstream output, flag updates and exception callback output.
- Each thread owns its local stream; scopes retain enable state across global toggles. Temporary path C strings passed to InitTracing are consumed synchronously.
- Crash callback strings/frames originate in Stacker; original-context loss is **BASE-SERVER-009**, and dump-only configuration is **BASE-SERVER-017**.
- No concurrent InitTracing call was established from the inspected startup flow. That function is not generally safe for unsynchronized reinitialization; this is a contract limit rather than a separately assumed race.

### [BASE-SERVER-010] Direct global-file flushes bypass osyncstream synchronization

- **Severity:** Medium
- **Confidence:** High
- **Category:** Concurrency
- **Location:** `Source/Tracer/Tracer.cxx:98,389–415`, especially `global_trace_file.flush()` at 400 and 415.
- **Affected scope:** Multithreaded Windows tracing with AlwaysFlush enabled; exception logging concurrent with ordinary traces.

**Evidence.** Ordinary global output is emitted through local osyncstreams, but Exit directly flushes the wrapped ofstream while its own syncstream still exists. Exception logging also directly flushes `file` after emission, including the global file. A single ofstream/filebuf is shared across threads; direct flush has no shared lock.

**Failure mechanism.** Thread A's syncstream destructor emits to the filebuf while thread B calls the direct global flush, or two Exit calls directly flush simultaneously. The syncbuf emission lock does not protect operations performed directly on the wrapped stream. Concurrent unsynchronized mutation of its buffer/stream state is outside the osyncstream guarantee.

**Impact.** Racy diagnostic output and undefined stream behavior under concurrent tracing. This is not a server-main-loop race (that loop is single-threaded), and no runtime corruption is claimed to have been observed.

**Alternatives / recommendation.** Keep all shared file emission and flushing within the same synchronization regime. Use synchronized emit-and-flush operations, or one explicit mutex shared by every output/flush path. Do not retain direct flushes merely in addition to osyncstream::flush; the latter's pending flush is emitted with the sync buffer.

**Verification.** Enable AlwaysFlush and have multiple Windows threads create/destroy Trace scopes while logging messages; inspect complete records and instrument synchronization. Exercise exception-output flush concurrently. Require one locking discipline for all global-file operations; a clean stress run alone is not proof of race freedom.

### [BASE-SERVER-011] Existing same-second trace directory is mistaken for creation failure

- **Severity:** Low
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Tracer/Tracer.cxx:191–207`, `Trace::InitTracing`.
- **Affected scope:** Two processes/restarts sharing a tracing root within one second.

**Evidence.** Directory names use only `%Y-%m-%d_%H-%M-%S`. `create_directories` returns false if the directory already exists, and false is treated as fatal setup failure before tracing and exception callback configuration.

**Failure mechanism.** First process creates the timestamp directory; a second launch in the same second sees the existing directory and exits InitTracing early. The callers shown do not recover by selecting a different directory.

**Impact.** Missing traces and exception configuration for one launch. This is bounded observability loss; a second process using a distinct data root is unaffected.

**Alternatives / recommendation.** Use a unique session directory (PID plus high-resolution timestamp or an atomic suffix retry) and distinguish existence from filesystem error. Merely accepting the existing directory would risk truncating/interleaving `all.trace` from two processes.

**Verification.** Launch two isolated processes against one tracing root within the same second. Both must initialize into distinct directories with intact independent logs; also verify genuine permission failures remain visible.

## Follow-up addendum — 2026-09-24

All 419 lines re-read with the other seven Tracer inputs.

### [BASE-SERVER-010] Addendum — retained synchronization boundary

Retain **Medium / High confidence / Concurrency**. The relevant interleaving is emission through one thread's syncbuf versus another thread's raw wrapped-file flush at 98/400/415. TLS logging and the counter in Stacker do not serialize that shared filebuf. A scope captures `enabled`, so merely toggling tracing during a live scope does not itself unbalance Enter/Exit; that is useful counterevidence. No concurrent initialization or configuration setter was established from the inspected call path, so ordinary non-atomic setup fields are not independently counted as races. Use one emission/flush discipline and retain the proposed multithreaded Windows verification.

### [BASE-SERVER-011] Addendum — retained filesystem return contract

Retain **Low / High confidence / Correctness**. `create_directories` returning false for an existing directory is distinct from failure; the second-resolution path still aliases same-root same-second launches. Do not fix this by silently accepting the directory and truncating its shared `all.trace`. Proposed two-process verification remains outstanding.

### Resource limits

Trace's implicitly nonthrowing destructor calls allocating string/format/stream operations; initialization and lazy per-thread file setup can also throw or fail. No allocation-failure experiment or repeated initialization was run, and no new production-fatal finding is inferred solely from those possibilities. Best-effort/no-throw exit logging is appropriate when hardening diagnostics. TLS depth/file ownership and synchronous consumption of constructor path strings were checked. Crash-report truncation is now precisely demonstrated in **ADD-SERVER-003**, rather than generalized to an assumed native UEF recursion.
