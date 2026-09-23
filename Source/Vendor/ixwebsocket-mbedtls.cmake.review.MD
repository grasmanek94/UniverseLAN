# Fresh baseline review: ixwebsocket-mbedtls.cmake

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. All 165 lines reviewed.

## Inspection notes
- Checked global include guard, static-only options, generated/program/test disabling and temporary suppression/restoration of Python discovery.
- Inspected target fallback selection for mbedTLS, x509 and TF-PSA-Crypto/legacy crypto, with explicit fatal diagnostics for absent targets.
- BUILD_INTERFACE include extraction removes already-wrapped generator expressions to avoid double wrapping in IXWebSocket. Current target include paths resolve to the three bundled trees during actual configure; arbitrary future complex expressions would require reevaluation.
- Legacy MBEDTLS variables and explicit IXWEBSOCKET_USE_MBED_TLS_MIN_VERSION_3 account for skipping the dependency's find_package branch.

## Findings and validation
No independent confirmed defect for the bundled versions. The actual Windows build successfully compiled IXSocketMbedTLS and linked mbedTLS 4.2.0/TF-PSA-Crypto. TLS handshakes/certificate validation were not exercised and vendor cryptography was not audited.
