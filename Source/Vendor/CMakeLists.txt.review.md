# Review: `Source/Vendor/CMakeLists.txt`

## Scope and findings

This file is an integration manifest, not third-party implementation code. The
explicitly excluded vendor directories remain outside the code review; the
custom `Enet++` wrapper and these integration scripts are reviewed.

- **Low — dependency targets are registered globally without capability
  checks.** The manifest always adds Enet-IPv6, Enet++, boost, and Detours
  before selecting optional wrappers. Make missing or unsupported dependencies a
  clear configure-time error, especially for non-MSVC builds where StackWalker
  is skipped.
- **Low — wrapper source discovery is delegated to broad globs.** The
  dependency-specific sidecars record the target input risks; prefer explicit
  source lists for reproducible integration.
