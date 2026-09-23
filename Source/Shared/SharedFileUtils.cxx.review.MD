# Fresh review — SharedFileUtils.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read all 385 lines; static Windows review.

## Inspection notes
- Reviewed all null/empty/zero guards and overloads. Filename Write creates an entry; ID Write/Open require an existing indexed entry. Open's non-creating behavior matters to the server's counter-file caller.
- Container roots are joined to current_path; an absolute configured base overrides that prefix under Windows filesystem semantics. Filename traversal is checked by canonical containment in Shared_NoVer, not by these guards.
- Whole-file read returns owned vectors; buffer reads return actual lower-layer byte counts. Most SDK width conversions saturate (sizes, counts, timestamps, space), rather than silently wrapping.
- Copy-to-shared preserves the destination share ID through entry copy notification; pre-existing destination files are overwritten by the lower entry implementation. Failures propagate as bool at this wrapper.
- Followed `GetTimestamp` to `filesystem_entry::get_timestamp`: that dependency returns raw file-clock epoch seconds, which are not Unix seconds on MSVC. The wrapper's saturation cannot correct it. Recorded as a UTIL/STORAGE handoff, not a duplicate NET finding.
- Empty-vector data pointers and zero-byte file downloads need lower-layer/API policy; they are not evidence of a raw-buffer overflow here.

## Result
No independent wrapper-local finding beyond the concrete dependency/caller issues documented above. Path-rejection exceptions are fully reported as BASE-NET-002 at dispatch. No file I/O experiment performed.
