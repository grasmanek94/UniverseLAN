# `IChat.h` Header Coverage

## Selected SDK

This matrix covers the selected `1.152.11` `IChat.h` public surface.

| Declaration group | Practical coverage | Boundary |
| --- | --- | --- |
| Controlled chat-room message retrieval, sending, unread state, and callbacks | Existing controlled chat scenarios | Use only scenario-owned room topology and bounded opaque payloads; never retain content or IDs. |
| Room-with-user creation and member enumeration | Friend-fixture-blocked | Require approved second-user/friend relationship; do not create friendships or manufacture user IDs. |
| Incoming-message callback | Second-user-fixture-blocked | Requires a controlled remote sender and callback lifecycle. |
| Send and mark-read controls | Mutation/control-bound | Exercise only in isolated scenario-owned rooms with explicit cleanup. |
| Listener aliases and destructor | Lifecycle-only | Register before trigger, destroy before shutdown, and never directly destroy the accessor-owned interface. |

## Safety Rules

- Never retain room IDs, message IDs, user IDs, message content, timestamps, credentials, or runtime artifacts.
- Do not create friendships, send messages outside scenario-owned topology, or infer social permissions from an unavailable fixture.
