# Review: `package-release.ps1`

## Finding — packaging failures are not propagated

- **Severity:** High
- **Evidence:** The `7z.exe` invocation at line 60 is not followed by a `$LASTEXITCODE` check, and the script does not set `$ErrorActionPreference = 'Stop'`. Missing `bin`/release inputs or a failed archive can therefore leave a zero-success script result.
- **Impact:** CI can publish a missing or incomplete release archive while reporting success.
- **Suggested fix:** Use terminating error handling, validate `bin` and every expected artifact, check `$LASTEXITCODE` immediately after 7-Zip, and fail if no package was produced.

## Finding — release names are not reproducible across checkouts

- **Severity:** Medium
- **Evidence:** Line 19 derives the public build number from `git rev-list HEAD --count`.
- **Impact:** The same commit has different counts in shallow or differently-rooted clones, so archive names are not stable across CI/rebuild environments.
- **Suggested fix:** Use an immutable tag/commit-derived version (or fetch and verify the full history) and pass it explicitly to packaging.
