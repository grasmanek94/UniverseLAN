# Fresh review — Host/Main.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–575. Static review.

## Inspection notes
- Followed option parsing, loopback WebSocket URL validation, role release/action/completion files, protocol emission, version/architecture checking and every scenario selection/feature guard.
- Traced SDK initialization and sign-in variants: factory/free API, InitOptions presence, SignIn/SignInGalaxy/Credentials and optional IsLoggedOn polling. UniverseLAN initialization uses local configured identities; credential profiles apply only to the alternate provider.
- Credential macros were read as identifiers in source; no values/files were accessed. Missing profile support returns explicit failure rather than silently signing into another account.
- Success flushes PASS and calls `_Exit(0)`. This deliberately excludes Shutdown, DLL static teardown and destructor-based persistence from scenario guarantees. It contributes no missing-flush defect; the runner has the separate terminal-read race **BASE-SERVER-012**.
- The standalone timeout parser accepts a numeric prefix via stoi and does not itself cap at 600, but the normal runner passes a validated bounded decimal. That boundary is recorded rather than inflated into a remotely triggerable hang.
- `runtime-load` is not a supported dispatch scenario here and is not registered by the reviewed CMake; its manifest must not be counted as executed runtime-load coverage.

## Result
No independent confirmed defect. Provider/network behavior and SDK matrix have not been executed in this review.
