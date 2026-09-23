# Fresh review — RichPresenceChangeMessage.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read all 44 lines.

## Inspection notes
- Reviewed all ACTION values and constructor overloads; success defaults false and absent key/value strings are initialized.
- Server replaces ID with mapped peer identity and performs set/delete/clear on that user's container. Enum validation is not provided by the serializer.
- Server switch has no default resetting client-supplied success for an unknown action; that is a handler validation concern, not an uninitialized field in this file.
- Dynamic strings and action semantics require bounded/validated input at dispatch; only known actions should be applied/notified.

## Result
No independent schema-local defect counted. The unknown-action case is recorded as a SERVER handoff; decoded sizes belong to BASE-NET-001.
