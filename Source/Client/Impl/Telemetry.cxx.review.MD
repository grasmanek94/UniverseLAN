# Fresh baseline review: Telemetry.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Entire file read, lines 1–211; baseline diff empty. Windows static review, no builds/tests run.

## File-specific inspection

- Read construction/path creation, optional local storage, every parameter writer, send/anonymous-send, callback arguments, visit ID methods, and destruction/flush behavior.
- SDK `ITelemetry.h` explicitly permits null parameter names for array elements. `SendTelemetryEvent` event type is not documented nullable; no separate confirmed defect is based on an invalid null event type.
- This is a local textual trace of telemetry calls, not an implementation of a remote telemetry protocol or structured event tree. Missing remote sampling/transport and fixed initial visit ID are capability limits, not claimed security failures.
- Event IDs use an atomic increment. The outgoing event-type string is a local `std::string`, but `NotifyAll` extends the lifetime of its `const char*` argument, so this is not a dangling-string finding. Specific listeners inherit CORE's generic deferred cancellation issue.
- Most writes lock `mtx`; pre-lock checks of mutable stream state are outside that protection. Concurrent writes/error checks need validation against the SDK's general thread-safe promise. Constructor `create_directories` can throw on inaccessible paths and the destructor cannot report a final flush failure; these are operational limits, not runtime-tested crashes.
- `TelemetryStore` defaults false in `IniData.cxx:448`. `Host/Telemetry.cxx` checks the completion's event type/ID but neither parameter arrays nor stored output bytes/disk failure.

## Findings

### [BASE-STORAGE-021] Legal anonymous array elements pass null names to C-string insertion

- **Severity:** Medium
- **Confidence:** High — legal input reaches invalid stream insertion; exact diagnostic depends on the Windows standard library.
- **Category:** Correctness / nullability
- **Location:** `Source/Client/Impl/Telemetry.cxx:58–122`, all `Add*Param` name insertions.
- **Affected scope:** Telemetry local storage enabled and array elements or nested anonymous objects/arrays.

**Evidence:** Every parameter method inserts `name` directly into `std::ofstream`. SDK `ITelemetry.h:91,104,117,130,147,163` explicitly permits `NULL` when adding an array element. There is no conversion to an empty/anonymous marker before the C-string insertion.

**Failure mechanism:** With a healthy opened log, call `AddArrayParam("items")`, then `AddIntParam(nullptr, 1)` and `CloseParam`. The second call streams a null C-string. A checked MSVC implementation can mark the stream bad; other implementations/configurations can diagnose or fault. Subsequent `if (!telemetry_file)` checks can then suppress all further output and send completions fail. This is a valid SDK usage, not malformed caller data.

**Impact:** One legal array element can disable local telemetry for the remaining instance lifetime, and portable C++ behavior is not safe to rely on. The Windows outcome is not represented as a universally reproduced crash.

**Possible solutions:** Normalize null names to a textual anonymous marker; encode array elements without a key; or build a structured event representation that inherently distinguishes keyed and anonymous values.

**Recommended resolution:** Handle null explicitly in every parameter method, preserving array semantics. For the current trace-only backend, a consistent escaped marker is sufficient to avoid the invalid insertion; a full event implementation should represent unnamed elements structurally.

**Verification:** With storage enabled, add each primitive type, object, and nested array using null element names. Verify complete output and that a later named event still succeeds. Check Debug and Release MSVC behavior and callback counts; no credential or remote service is needed.

### [BASE-STORAGE-023] Stream truthiness is mistaken for an open, successfully written telemetry sink

- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness / I/O error handling
- **Location:** `Source/Client/Impl/Telemetry.cxx:16–24,159–175`.
- **Affected scope:** Disabled local telemetry and first writes failing on a previously healthy stream.

**Evidence:** The constructor returns with a default-constructed `std::ofstream` when storage is disabled. Such a stream can have `goodbit` while `is_open()` is false. `SendTelemetryEvent` checks only `if (!telemetry_file)` before insertion and unconditionally queues success afterward. No post-write/flush check is made.

**Failure mechanism:** In a fresh instance with the default `Telemetry.Store=false`, make `SendTelemetryEvent` the first telemetry write. The good stream-state check passes, insertion into the unopened file fails, and success is still queued. A second call sees the failure state and reports failure, producing inconsistent policy for identical calls. With storage enabled, an actual write/flush error can similarly occur after the only check and be acknowledged as success.

**Impact:** Games receive a success for data that was never stored, and disabled telemetry alternates behavior depending on prior calls. This is bounded local telemetry reliability, not loss of game saves.

**Possible solutions:** Track enabled/open/failed state explicitly; require `is_open()` and successful I/O; or implement a documented disabled/no-op policy that consistently acknowledges or rejects events independently of stream flags.

**Recommended resolution:** Separate storage policy from stream error state, check both under the mutex, and determine completion only after the selected persistence boundary succeeds. If success means locally stored, verify write and flush. If disabled means intentionally discarded success, implement that explicitly and consistently without touching the closed stream.

**Verification:** On a fresh disabled instance, send two events before/after pumping and require the same documented outcome. Repeat with enabled healthy storage, failed open, and injected write/flush failure; verify output bytes and callback result agree. Existing callback-only tests do not prove storage success.

## Source-first re-review addendum — 2026-09-24

Read all `Telemetry.cxx:1-211` and `Telemetry.hxx:1-232` before baseline comparison. BASE-STORAGE-021 is retained: SDK-valid null array names are distinct from an invalid null event type or null required string value. The original section appropriately avoids asserting a universal MSVC crash. BASE-STORAGE-023 is retained and expanded below. `GetVisitIDCopy`/Reset use the same lock; retaining a pointer across Reset is not promoted to an independent defect without a stronger lifetime contract. Unsigned event-counter wrap is defined, and no realistic simultaneous-ID exhaustion defect is claimed.

### BASE-STORAGE-023 — ADDENDUM CORRECTION: stream-state checks are outside the sink lock

- **Disposition:** Retained and expanded under the existing sink-state ID; the baseline inspection note is made concrete, not assigned a duplicate new ID.
- **Severity:** Medium (unchanged)
- **Confidence:** High
- **Category:** Concurrency / Correctness
- **Location:** `Source/Client/Impl/Telemetry.cxx:61-66,72-77,83-88,94-99,105-110,116-121,127-143,150-155,165-173`; `Telemetry.hxx:34-43`.
- **Affected scope:** Supported concurrent telemetry API calls with an insertion setting stream failure state, including a closed disabled sink's first write or an actual I/O failure.

**Evidence:** Every writer tests `!telemetry_file` before acquiring `mtx`. A different caller can be inside a locked insertion that sets that same stream's error bits. The mutex therefore does not protect all reads of the mutable stream state. SDK `Source/DLLs/1.152.11/galaxy/GalaxyApi.h:310-314` promises general thread safety; these scalar/void methods are not pointer-return exceptions. Atomic event IDs do not synchronize the ofstream.

**Failure mechanism:** A begins writing under the lock and encounters a stream error; B simultaneously executes its pre-lock state test. The failed write modifies the state being read outside synchronization. Independent of that race, B can pass the check, wait for A to fail, then unconditionally queue success after its own failed insertion. This refines the original finding: not every healthy insertion is asserted to race on state; the concrete trigger is a state-changing failure.

**Impact:** Undefined concurrent stream-state access and incorrect local event results. The finding remains bounded telemetry reliability, not a claim that this local trace provides remote telemetry delivery.

**Possible solutions:** Put enabled/open/error checks and write/result determination inside one lock; use a serialized sink queue; or make a disabled backend a consistent explicit no-op policy independent of stream bits.

**Recommended resolution:** Protect the whole sink-state transition, including preconditions and post-write/flush status, with one synchronization scheme. Preserve event ID/type correlation and dispatch listeners outside that critical section. CORE's Logger stream-state finding has an analogous pattern in a different sink; coordinate the rule without merging unrelated objects' fixes.

**Verification:** Proposed barrier-controlled two-writer failure and first-use-disabled cases; inspect state synchronization and verify deterministic failure/no-op policy, bytes, and callbacks. Keep single-thread first/second-event controls. No tests, analyzer, or stream experiments were executed.
