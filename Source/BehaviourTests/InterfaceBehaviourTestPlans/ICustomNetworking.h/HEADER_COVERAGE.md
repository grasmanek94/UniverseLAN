# `ICustomNetworking.h` Header Coverage

## Selected SDK

| Declaration group | Practical coverage | Boundary |
| --- | --- | --- |
| WebSocket `OpenConnection` and open-failure callback | Existing official-only diagnostic | Numeric-loopback and localhost forms failed asynchronously; omitted scheme was synchronously invalid. |
| Open success, valid connection ID, send/data callback, availability/peek/read/pop | Success-gated runner endpoint fixture | The private echo endpoint is transport scaffolding, not behavior evidence; no success-path fact exists. |
| Close and close callback | Success-gated lifecycle | No valid connection was opened, so close was not issued. |
| Invalid IDs, null/undersized buffers, arbitrary payloads/URLs | Unsafe/uncharacterized | Do not manufacture handles, pointers, or boundary forms. |
| Destructor/global listener aliases | Lifecycle-only | Accessor-owned; direct destruction is invalid. |

## Safety Rules

- Use WebSocket URLs only, as required by the selected header.
- Never retain URLs, connection IDs, payloads, buffer data, credentials, timestamps, or runtime artifacts.
- Do not classify runner endpoint behavior as Galaxy/UniverseLAN behavior.
