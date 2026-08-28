# Review: `ConfigDebug/UniverseLANData/Config.ini`

## Finding — debug sign-in credentials are committed in configuration

- **Severity:** High
- **Evidence:** `[Interceptor]` enables `OverrideInitKeys` and `OverrideSignIn`
  and stores a client secret, account identifier, and password in the tracked
  debug file.
- **Impact:** Anyone with the repository can reuse the values or mistake them
  for production credentials. They are also copied into test/debug output.
- **Suggested fix:** Keep credentials outside the repository and load them from
  a protected local/CI secret source; ship a redacted example with overrides
  disabled.
