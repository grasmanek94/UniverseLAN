# Fresh baseline review: ixwebsocket.cmake

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. All nine lines reviewed.

## Inspection notes
Forces static dependency builds, TLS enabled, mbedTLS backend and no dependency install. zlib and mbedTLS bridges execute before adding pinned IXWebSocket-12.0.1. Cache writes affect the vendor configuration deliberately; top-level application DLLs explicitly request SHARED and are unaffected by BUILD_SHARED_LIBS=OFF.

## Findings and validation
No independent confirmed integration defect. The Windows dependency compiled and linked. WebSocket application ownership/callback problems remain in Client/Impl/CustomNetworking, not in this manifest.
