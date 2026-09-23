# Fresh baseline review — InitOptionsModern.hxx

- Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`.
- Coverage: entire file, lines 1–62; static normalization/ABI review.

## Specific checked notes

- Traced three SDK input paths: native modern `InitOptions.h`, legacy options in `IGalaxy.h`, and the internal oldest-SDK carrier. The alias follows the feature matrix.
- Credentials and paths are held as owning strings, which is appropriate for retaining values after public Init returns; this internal struct does not overwrite or reinterpret the public SDK struct layout.
- Allocator/thread-factory pointers are intentionally borrowed, with storage gated to SDK versions that declare them. Host/port fields are likewise conditionally present.
- `throwExceptions` exists independently of the input version but lacks preservation/enforcement in the conversion/runtime path (`BASE-CORE-005`).
- Call tracing found the normalized options stored on the interface graph, while this client networking startup uses project configuration and `std::thread` directly. Stored options should not be confused with implemented allocator, thread-factory, or bind-address behavior.

## Findings and limits

No independent layout/signature defect confirmed. Custom-hook and bind/config option compatibility is an integration observation requiring host expectations and runtime validation; it is not inflated into a demonstrated heap/ABI failure. No compiled ABI test was performed.
