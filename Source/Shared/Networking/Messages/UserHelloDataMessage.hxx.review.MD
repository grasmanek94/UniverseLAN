# Fresh review — UserHelloDataMessage.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read all 30 lines.

## Inspection notes
- Wire order: claimed ID, full AchievementsAndStatsContainer, nickname. All constructors initialize fields; stats-only updates deliberately leave ID/nickname empty.
- Server ignores the supplied ID for authority, updates the mapped user's stats and only sets an initially empty nickname. Repeated stats hello also re-sends peer data and lobby snapshots.
- Nested stats include dynamic maps and strings, covered by decoder budgeting (BASE-NET-001). Shared_NoVer `PlayTime.load()` in serialize decodes into a temporary rather than storing the atomic; this concrete dependency issue is handed off in NET.MD.
- Copying the stats payload invokes its dependency's copy constructor; per-map locks are not automatically taken by this schema.

## Result
No independent field-order/initialization defect in this message. Stats copy/serialization correctness remains a cross-owner dependency, not a falsely claimed complete subsystem pass.
