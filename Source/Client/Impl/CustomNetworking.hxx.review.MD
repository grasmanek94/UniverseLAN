# CustomNetworking.hxx — fresh baseline review

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. All 166 lines read; Windows-focused static review.

## File-specific inspection

- Inspected all SDK overrides, operation-listener guards, the nested Channel object, IXWebSocket alias, incoming deque/lock, atomic cleanup flag and shared-pointer channel registry.
- Compared the complete `Source/DLLs/1.152.11/galaxy/ICustomNetworking.h`: connection IDs are opaque `uint64_t` values, incoming storage is a byte buffer and data callbacks report newly received byte counts. The API does not promise message-boundary-preserving reads.
- `enable_shared_from_this` does not itself retain a Channel during callbacks; current callbacks bind raw `this`, while the registry/shared local handles own the object. The destructor's explicit stop/join makes ordinary destruction materially safer, but queued SDK events have a separate lifetime from the worker and Channel.
- `cleanup` being atomic only publishes its flag. It does not synchronize `listener_close`, make listener cancellation visible, preserve registry entries for delayed events or prevent pointer-address ConnectionID reuse. The three distinct implementation defects are fully documented as BASE-API-015 through BASE-API-017 in `CustomNetworking.cxx.review.MD`.
- `listener_data` is initialized but not used; data callbacks correctly target globally registered data listeners because this SDK exposes no per-operation data-listener argument. That unused field is not counted as a defect.
- Traced normal interface reset ordering and IXWebSocket 12.0.1 lifecycle sections. Inspected the complete SystemTests CustomNetworking host file: its echo and orderly close cases retain listener objects and pump promptly, so those cases do not establish cancellation/delayed-cleanup safety.

No independent ABI/declaration defect is added. These observations do not certify every older experimental custom-networking SDK variant, concurrent shutdown behavior or runtime resource cleanup. No build or test executed.
