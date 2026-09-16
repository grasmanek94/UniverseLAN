# `IListenerRegistrar.h` Header Coverage

## Selected SDK

| Declaration group | Practical coverage | Boundary |
| --- | --- | --- |
| `ListenerRegistrar`, listener type awareness, `SelfRegisteringListener` | Existing indirect lifecycle coverage | Controlled P2P, lobby, chat, and auth scenarios construct global listeners, pump callbacks, destroy them before shutdown, and retain symbolic lifecycle facts. |
| Explicit `Register`/`Unregister` | Trigger-blocked | No standalone safe callback source; direct registration requires a listener type and controlled trigger. |
| Unregister pending-operation behavior | Trigger-blocked | Requires an owned asynchronous operation and callback source. |
| Game-server registrar/aliases | Header-gated | No selected behavior scenario uses the Game Server listener registrar. |
| Registrar/listener destructors | Lifecycle-only | Never directly destroy accessor-owned registrar; listener scope destruction is covered only through public callback scenarios. |

## Safety Rules

- Register listeners before their owned trigger and destroy/unregister before shutdown.
- Never manufacture listener types, callback events, IDs, credentials, timestamps, or runtime artifacts.
- Do not infer direct `Register`/`Unregister` semantics from self-registering alias behavior.
