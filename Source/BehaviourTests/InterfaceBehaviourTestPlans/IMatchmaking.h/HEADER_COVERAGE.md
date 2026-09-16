# `IMatchmaking.h` Header Coverage

## Selected SDK

This matrix covers `Source/DLLs/1.152.11/galaxy/IMatchmaking.h` through the controlled public-lobby behavior suite.

| Declaration group | Practical coverage | Boundary |
| --- | --- | --- |
| Create/list/filter/join/leave and their callbacks | Existing strict and characterization coverage | Scenario-owned tagged public lobbies only; no raw lobby IDs or direct-ID discovery. |
| Lobby/member/owner/type/capacity/joinability accessors | Existing public-lobby coverage | Query only lobbies created or joined by the scenario. |
| Lobby/member data set/get/copy/delete and callbacks | Existing controlled coverage | Use temporary scenario-owned keys/values and cleanup; never retain content. |
| Lobby message send/get/callback | Existing controlled coverage | Bounded opaque payloads only within scenario-owned memberships. |
| Indexed lobby/member/data accessors | Existing focused coverage | In-range indices only after callback-local list/member facts establish them. |
| Direct-ID operations, arbitrary keys/values, foreign lobbies | Fixture-blocked | Do not invent lobby IDs, member IDs, keys, values, or ownership. |
| Destructor | Lifecycle-only | Accessor-owned; direct destruction is invalid. |

## Safety Rules

- All mutations occur only inside a tagged, scenario-owned lobby with terminal leave and absence cleanup.
- Never retain lobby IDs, user IDs, keys, values, payloads, counts, indices, timestamps, credentials, or runtime artifacts.
- Callback order and eventual-list visibility remain diagnostic unless an existing focused contract makes a narrower relation strict.
