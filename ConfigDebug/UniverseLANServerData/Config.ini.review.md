# Review: `ConfigDebug/UniverseLANServerData/Config.ini`

## Finding — debug server is exposed with upload enabled

- **Severity:** Medium
- **Evidence:** The debug server binds `0.0.0.0`, allows 1024 connections, and
  enables file uploads by default.
- **Impact:** Running the debug configuration on an untrusted network exposes a
  resource-consuming upload service; the shared authentication key in the
  companion debug base config compounds the exposure.
- **Suggested fix:** Default debug runs to loopback, require explicit opt-in
  for LAN binding/uploads, and use a unique authentication key.
