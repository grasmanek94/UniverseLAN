# Fresh baseline review: Utils.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Entire file read, lines 1–176. Static Windows-focused review, no version build matrix.

## File-specific inspection

- Checked the versioned RGBA buffer alias, legacy notification-ID alias, optional consumable output signature, overlay feature guards, virtual methods/destructor, service-state declaration, and non-owning dependencies.
- Image buffer size is a caller precondition based on width/height; the current implementation returns zero dimensions and writes no RGBA bytes. No bounds violation follows from this declaration alone.
- Overlay preconditions and the documented fact that basic game functionality should not rely on the overlay support the explicit disabled facade. Missing implementation is a compatibility boundary, not evidence of an exploitable defect.
- The service-state comment explicitly excludes a defined pre-login state. This prevents treating an initial transport/auth mismatch as a confirmed failure without an additional supported sequence.
- `GetNotification`'s output references and buffers need deterministic semantics when valid notification resources are implemented. The current file supplies no storage or ownership model for notifications, consistent with its no-op registration.
- Listener notification lifetime is delegated to the registrar; only value-state notifications originate in this class. Normal initialized/reset dependency lifetime was inspected in `InterfaceInstances`.

## Findings disposition and verification

No extra declaration-only defect counted. Full implementation inspection notes are in `Utils.cxx.review.MD`. Static review does not establish binary compatibility of all older SDK signatures. Validate the legacy ID/buffer variants when builds are permitted, and test connection-query/callback coherence after login, reconnect, and repaired sign-out.

## Source-first re-review addendum — 2026-09-24

Full `1-176` reread completed before baseline comparison. RGBA pointer alias, historical NotificationID, consumable-output gate, and overlay/state preconditions were rechecked against definitions and the latest SDK. The documented output-size expression is a caller precondition, not arithmetic performed by this implementation. General header pointer ownership and value-only global state notifications add no independent lifetime mechanism. No new header finding; complete disposition is recorded in `.ai/review-addendum/STORAGE.MD`.
