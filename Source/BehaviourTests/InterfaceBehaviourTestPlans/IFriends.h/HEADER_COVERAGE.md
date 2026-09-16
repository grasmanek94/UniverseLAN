# `IFriends.h` Header Coverage

## Selected SDK

| Declaration group | Practical coverage | Boundary |
| --- | --- | --- |
| Peer-information request, availability, persona name/state, persona callback | Existing two-lane coverage | Non-mutating baseline; current official offline versus UniverseLAN online relation is explicitly classified. |
| Friend list, friendship, user find, invitation list/index access | Approved-social-fixture-blocked | No disposable relationship fixture or reset contract. |
| Friend add/delete/invitation send/respond and callbacks | Relationship-mutation-blocked | Persistent relationship workflow and cleanup are required. |
| Rich presence read/write/delete/clear/index/callbacks | Owned-key-fixture-blocked | Requires unique owned keys, remote observer, and restore/delete cleanup. |
| Game invitation, join callbacks, overlay invite dialog, avatar controls | External/UI-fixture-blocked | Require approved two-account invite flow or initialized overlay. |
| Destructor/listener aliases | Lifecycle-only | Accessor-owned; direct destruction is invalid. |

## Safety Rules

- Never create friendships, invitations, rich-presence state, or overlay actions outside an explicit disposable fixture.
- Never retain user IDs, names, invitations, rich-presence values, connection strings, credentials, timestamps, or runtime artifacts.
