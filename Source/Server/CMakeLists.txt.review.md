# Review: `Source/Server/CMakeLists.txt`

## Finding — debugger working directory is hard-coded to Debug

- **Severity:** Low
- **Evidence:** Line 29 sets `VS_DEBUGGER_WORKING_DIRECTORY` to `bin/<version>/Debug/` for every configuration.
- **Impact:** Launching a Release (or another configuration) target from Visual Studio starts it in a directory that may not contain the matching configuration files, producing misleading runtime failures.
- **Suggested fix:** Use the active configuration directory (for example `$(Configuration)`/`$<CONFIG>`) or leave the property unset and use the target output directory.
