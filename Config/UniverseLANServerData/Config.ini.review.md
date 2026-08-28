# Review: `Config/UniverseLANServerData/Config.ini`

## Finding — server binds all interfaces by default

- **Severity:** Medium
- **Evidence:** `[Storage]` enables `AllowFileSharingUpload = 1` at line 4; `[Server]` sets `BindAddress = 0.0.0.0` at line 11 and permits up to 1024 connections at line 13; the companion authentication configuration ships a shared public default key.
- **Impact:** Starting the server exposes its listener on every IPv4 interface, including networks the operator may not trust. Combined with the shared default key, unintended hosts can connect, upload files, and consume resources.
- **Suggested fix:** Default to loopback or an explicitly selected LAN address, require an explicit bind-address opt-in for exposure, and ensure the server refuses the known default authentication key.
