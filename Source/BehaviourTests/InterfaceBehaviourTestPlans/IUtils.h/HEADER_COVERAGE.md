# `IUtils.h` Header Coverage

## Selected SDK

This matrix covers `Source/DLLs/1.152.11/galaxy/IUtils.h`. It is the authoritative selected-header inventory; older declaration plans are historical and are not evidence for `1.152.11`.

| Selected declaration | Coverage status | Boundary / next action |
| --- | --- | --- |
| `GetGogServicesConnectionState` | Strict two-lane CTest and diagnostic characterization | Strict policy accepts the documented environment-specific GOG/UniverseLAN state pair; callback phasing remains diagnostic. |
| `OnConnectionStateChange` | Diagnostic characterization | Global listener is exercised by `gog-services-state characterization`; delivery/order are not a strict contract. |
| `GetOverlayState` | Two-lane characterization | Environment-dependent state only; official was `undefined` and UniverseLAN `disabled`. |
| `RegisterForNotification` | Runtime-blocked | Both listener and registration-only probes exited before trace output in both lanes. Do not rerun automatically or classify a product difference without a controlled notification fixture. |
| `GetNotification`, `OnNotificationReceived` | Fixture-blocked | Require an ID and lengths supplied by a genuine public notification callback; never manufacture an ID. |
| `GetImageSize`, `GetImageRGBA` | Fixture-blocked | Require a known valid public image ID and, for RGBA, dimensions from the fixture. |
| `IsOverlayVisible`, `ShowOverlayWithWebPage`, `OnOverlayStateChanged`, `OnOverlayVisibilityChanged` | Overlay-precondition-blocked | The header requires an initialized overlay, which is not established in either lane. |
| `DisableOverlayPopups` | Overlay-control-blocked | Changes client behavior and requires initialized overlay. Require an isolated fixture and restoration policy. |
| `~IUtils` | Lifecycle-only | Interface is accessor-owned; direct destruction is invalid. Exercise public `Utils()` and SDK shutdown only. |

## Historical Plans

Plans `005`, `006`, `007`, `009`, `012`, `015`, `016`, and `018` describe removed signatures or callback forms from older snapshots. They are intentionally not exercised by the selected `1.152.11` host.

## Safety Rules

- Never invent image IDs, notification IDs, notification types, payload buffers, overlay transitions, or URLs as compatibility inputs.
- Do not display overlays, change popup behavior, read notification payloads, or retain image data, notification data, IDs, credentials, timestamps, or runtime artifacts without an explicit public fixture.
- A future fixture must be public-SDK-only, bounded, and restore any client-visible state before a method can move from blocked to executable coverage.
