# Fresh baseline review: Utils.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Entire file read, lines 1–97; baseline diff empty. Windows static review; no execution.

## File-specific inspection

- Reviewed both image methods, notification registration/retrieval variants, overlay URL/pop-up stubs, state queries, service-state translation, and deferred connection notifications.
- Compared the latest SDK `IUtils.h`. Overlay consistently reports disabled and invisible; `ShowOverlayWithWebPage` logs a URL without opening a browser or invoking a shell. No command-injection or unintended network-access finding is supported by this code.
- Image size outputs are initialized to zero. The RGBA method does not fill a buffer. Context `Friends.cxx:173–205` returns no avatar URL, image ID 0, and availability false. No valid avatar data path was found in that inspected producer; the unimplemented image facade is recorded as a capability limit rather than an invented reachable overflow.
- Notification retrieval returns zero and leaves ancillary outputs untouched. Registration is a no-op in this file. A meaningful valid-notification retrieval path was not established in this scope, so no confirmed uninitialized-output failure is assigned solely from these stubs.
- `GetGogServicesConnectionState` derives state from `UserImpl::IsLoggedOn`, while the notification helper receives transport connection state from `ClientNetworkHandlers.cxx:34–57`. Transport connection can precede accepted authentication. SDK `IUtils.h:245–255` explicitly says state is undefined before successful login, so startup differences alone are not counted as a defect. Reconnect and post-sign-out consistency need validation with the repaired User state machine (BASE-STORAGE-018).
- Deferred service notifications contain an enum value and use global listeners only, avoiding per-call listener captures at this site. Generic registrar concurrency still governs delivery.
- `Host/Utils.cxx` asserts disabled/invisible overlay state and no overlay callbacks across pumping; inspected, not executed. It provides no image/notification implementation evidence.

## Findings disposition and limits

No independent confirmed defect counted in this file under the supported stub behavior. This is not a correctness certification. Unsupported images, notification retrieval, and overlay interaction remain significant drop-in compatibility limits, and untouched outputs should be specified or explicitly rejected if these APIs become reachable with valid resources.

Recommended verification: overlay-disabled invariant, successful login/disconnect/reconnect state consistency, sign-out state integration, and explicit failure/empty-output behavior for unsupported image and notification calls. No Windows overlay injection or service behavior was executed.
