# `IUser.h` Header Coverage

## Selected SDK

This matrix covers `Source/DLLs/1.152.11/galaxy/IUser.h`. It is the authoritative selected-header inventory; older declaration plans are historical and are not evidence for `1.152.11`.

| Selected declaration group | Coverage status | Boundary / next action |
| --- | --- | --- |
| Credential sign-in, auth callbacks, `SignedIn`, `GetGalaxyID`, `IsLoggedOn`, `GetSessionID` | Existing behavior coverage | Public sign-in/self/session relations are sanitized; token and persona content are excluded. |
| `RequestUserData(default self)`, user-data availability/callbacks | Runtime-blocked | A key-free default-self request exited before trace output in both lanes. Do not rerun automatically or classify a product difference. |
| User-data key/index accessors | Fixture-blocked | Require a known scenario-owned key or controlled data set; arbitrary index enumeration can disclose data. |
| User-data mutations | Mutation-blocked | `SetUserData` and `DeleteUserData` change persistent profile state and require cleanup. |
| Access/refresh/ID tokens, encrypted tickets, invalid-token reporting | Sensitive-data prohibited | Do not request, copy, report, classify, or retain credentials or ticket material. |
| OpenID/PlayFab/platform/launcher authentication | External-authentication or secret-blocked | Require platform credentials, launch environment, title secrets, or JWT material. |
| Sign-out and session/loss/operational callbacks | Control-trigger-blocked | Deliberate triggers mutate session state or require another session/runtime event. |
| `~IUser` | Lifecycle-only | Interface is accessor-owned; direct destruction is invalid. Use public shutdown only. |

## Historical Plans

Legacy generic sign-in overloads, removed platform forms, older no-listener user-data/ticket forms, and parameter-name variants are historical-only. They are intentionally not exercised by the selected `1.152.11` host.

## Safety Rules

- Never retain user IDs, session IDs, persona strings, tokens, tickets, keys, values, counts, credentials, timestamps, or runtime artifacts.
- Do not mutate user data, create sessions, sign out, or exercise platform/external sign-in without an isolated public fixture and cleanup policy.
- A default-self user-data probe must remain key-free and stop at availability/callback relation.
