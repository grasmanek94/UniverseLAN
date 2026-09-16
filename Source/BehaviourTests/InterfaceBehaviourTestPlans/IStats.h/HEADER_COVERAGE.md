# `IStats.h` Header Coverage

## Selected SDK

This matrix covers `Source/DLLs/1.152.11/galaxy/IStats.h`. It is the authoritative selected-header inventory; older declaration plans are historical and are not evidence for `1.152.11`.

| Selected declaration group | Coverage status | Boundary / next action |
| --- | --- | --- |
| `RequestUserStatsAndAchievements`, retrieve-success callback, `GetAchievementsNumber` | Strict self-callback CTest and characterization | Retrieval success/self relation is strict; count and catalog contents are never retained. |
| `RequestLeaderboards`, retrieve callbacks | Runtime-blocked | A terminal-only public request form exited before trace output in both lanes. Do not rerun automatically or classify a product difference. |
| `RequestUserTimePlayed`, retrieve callbacks, `GetUserTimePlayed` | Runtime-blocked | The combined default-self request form exited before trace output in both lanes; query remains gated on a successful callback. |
| Achievement catalog/state/name/visibility/description methods | Title-fixture-blocked | Require known achievement keys and successful retrieval. |
| Stat get methods | Title-fixture-blocked | Require known stat names and successful retrieval. |
| Leaderboard metadata/find/entry/access methods | Title-fixture-blocked | Require known leaderboard names and, for entries, retrieved definitions and controlled entry requests. |
| Achievement/stat/store/reset/leaderboard-create/score update methods and callbacks | Mutation-blocked | Change persistent player or leaderboard state. Require isolated fixture and cleanup policy. |
| Remaining retrieve/store/entry callbacks | Trigger-blocked | Observable only through their corresponding request or mutation; do not manufacture IDs, names, ranks, scores, or callbacks. |
| `~IStats` | Lifecycle-only | Interface is accessor-owned; direct destruction is invalid. Exercise public `Stats()` and SDK shutdown only. |

## Historical Plans

Plans `015`, `018`, `019`, `027`, `044`, `046`, `048`, `049`, `051`, `053`, `055`, `059`, `061`, and `064` describe superseded no-listener or older overload forms. They are intentionally not exercised by the selected `1.152.11` host.

## Safety Rules

- Never invent achievement keys, stat names, leaderboard names, IDs, ranks, scores, or user state as compatibility inputs.
- Never retain catalog content, stats, time-played seconds, scores, values, names, descriptions, IDs, credentials, timestamps, or runtime artifacts.
- A future title fixture must be public-SDK-only, isolated, bounded, and restore persistent state before a blocked method can move to executable coverage.
