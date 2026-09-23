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
