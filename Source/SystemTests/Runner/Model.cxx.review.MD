# Fresh review — Runner/Model.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–252. Static review.

## Inspection notes
- Traced strict allowed-field/type checks, provider selection, time bounds, role/identity uniqueness, persistence-group identity reuse, apps/DLC keys, declared signal uniqueness and dependency/peer references.
- Persistence groups are explicitly constrained against dots, but roles use only generic tokens. Case-sensitive std::set uniqueness does not establish unique Windows directories.
- Dependency references are validated, not graph acyclicity; cycles currently produce a bounded scenario timeout rather than a false PASS. Integer values are narrowed before range checks in several fields, a robustness limitation for manually malformed manifests; no unbounded execution was inferred from it.
- No credential data was read. Profile tokens are merely validated identifiers.

### [BASE-SERVER-013] Validated role names can escape or alias isolated Windows directories

- **Severity:** Medium
- **Confidence:** High
- **Category:** Testing
- **Location:** `Source/SystemTests/Runner/Model.cxx:127–130`; consumers `Runner/Main.cxx:72–76,93–102,116–136`; generic token predicate `Common/Protocol.cxx:8–14`.
- **Affected scope:** Isolation and scheduling of custom SystemTests manifests on Windows.

**Evidence.** Role validation permits `.` and `..` and uses case-sensitive uniqueness. The role is appended directly to root to locate its executable, INI and stdout.log. Internal sibling directories are named `server`, `control` and `persistence` without reservation. Roles `Alice` and `alice` compare distinct in the model but ordinarily address the same Windows directory.

**Failure mechanism.** A role `..` stages configuration and executables in the parent shared test directory. A role `server` collides with the already-started server's directory/log. Case-only duplicate roles reuse a log and control paths, allowing truncation and cross-release or mixed protocol state. These are accepted schemas, not OS path traversal via disallowed separators.

**Impact.** Broken isolation, misleading failures and files staged outside the per-run cleanup boundary. The manifest is a local test input, so this is a harness correctness defect, not an asserted remote vulnerability.

**Alternatives / recommendation.** Validate role-specific safe filename components, reject dot segments/trailing-dot aliases/reserved Windows names and internal directory names, and enforce Windows-equivalent uniqueness. Prefer generated numeric staging directories with a separate role-to-directory map so event tokens need not become filesystem identities.

**Verification.** Reject or safely isolate `.`, `..`, `server`, `control`, `persistence`, Windows device names and case-only/trailing-dot aliases. Valid multi-host scenarios must produce distinct logs/control files, with every staged file confined to the run root.

## Follow-up addendum — 2026-09-24

### [BASE-SERVER-013] Addendum — persistence-group aliases share the same defect

- **Disposition:** Retain Medium / High confidence / Testing; extend scope without a new ID.
- **Location:** `Source/SystemTests/Runner/Model.cxx:131–154`; `Runner/Configuration.cxx:64–86`; `Runner/Main.cxx:28–38,93–102`.
- **Evidence:** Groups reject dots but still allow case-equivalent Windows names. `identityGroups` / `persistenceGroupIdentities` and `persistenceReady` use case-sensitive strings. Two distinct users with groups `SaveA` and `savea`, distinct safe roles, and `saveAchievementsAndStats=true` pass these group/identity checks. Their storage/configuration paths ordinarily name the same Windows directory; staging writes all host configs before launch. The scheduler considers the groups different and permits concurrent execution.
- **Mechanism/impact:** Cross-group configuration overwrite and shared persistence occur even after role-name validation alone is fixed. Both children can consume the later host's identity configuration and collide at authentication or modify each other's saves. This is the existing logical-token/filesystem-identity mismatch, with a second consumer; it remains a local harness correctness issue.
- **Possible solutions:** Use generated directories for groups as well as roles, or validate/canonicalize both using Windows-equivalent identity and reserve device/internal names.
- **Recommended resolution:** Keep explicit maps from validated logical roles/groups to unique staging paths. Enforce the one-group/one-user invariant on the physical storage identity used by staging and scheduling.
- **Verification:** Add two otherwise valid hosts with case-only-different groups and distinct users; reject the manifest or give them provably distinct stores. Retain same-group sequential writer/reader behavior and all role cases from the original finding. Proposed only.

Fresh full re-read also confirmed that undeclared dependencies/duplicate signals are rejected, while dependency cycles and integer narrowing before range checks remain local manifest robustness limits. No source or manifest was changed and no parser was executed.
