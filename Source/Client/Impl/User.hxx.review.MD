# Fresh baseline review: User.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Entire file read, lines 1–814. Windows-focused static review; all conditional text inspected, no version-matrix compilation.

## File-specific inspection

- Inspected the complete authentication overload matrix and renaming macros, pointer-type aliases, optional listener defaults, user-data methods, token/ticket types, sign-out contract, PlayFab/OpenID signatures, and internal response/state helpers.
- `waiting_auth_listeners` is a private raw-pointer set separate from registrar bookkeeping. The mutex at line 81 protects the set's structure, not registration lifetime. Full BASE-STORAGE-017 in `User.cxx.review.MD` establishes the concrete unregister/use-after-free sequence.
- `logged_on` and `connected` are plain booleans. Their reads/writes and the sign-in check-then-enqueue sequence are not one protected state transition. Runtime auth-state synchronization deserves targeted multithread validation as part of the BASE-STORAGE-018/019 redesign; no executed race test is claimed.
- `SignInGalaxy` preserves the SDK's offline/online distinction and default timeout in its declaration, but the implementation discards them (BASE-STORAGE-019). `SignedIn`, `IsLoggedOn`, and `SignOut` describe runtime facts rather than configuration policy (BASE-STORAGE-018).
- `SignInAuthorizationCode` defaults its listener to null. Optional PlayFab arguments and listeners are also explicitly modeled. The implementation's nullable-listener inconsistency is BASE-STORAGE-020, rather than a caller precondition failure.
- The user-data copy contract is materially different from the pointer getter; BASE-STORAGE-022 identifies the lock/lifetime gap. Output enumeration keeps its lock through both copies and accepts bounds/length arguments consistently with implementation.
- The fixed token/ticket/session facade and ignored platform credentials are emulation limitations. The header does not establish that UniverseLAN authenticates to real third-party services; no such security finding is invented.
- The non-owning interface pointer is valid in the normal initialized object graph read as context. General null interface access before initialization belongs to CORE lifecycle/accessor review.

## Findings disposition and validation

No additional declaration-only defect counted. Full findings: BASE-STORAGE-017, 018, 019, 020, and 022 in `User.cxx.review.MD`. This scoped review does not certify ABI compatibility or all runtime interleavings. Prioritize cancellation/destruction, late authentication results after sign-out/timeout, documented null listener defaults, and concurrent copy/update validation.

## Source-first re-review addendum — 2026-09-24

Full `1-814` reread completed before baseline comparison, including all renamed and historical auth forms. ADD-STORAGE-005 in `User.cxx.review.MD` distinguishes the older global listener type from the newer per-call listener parameter gate. The BASE-STORAGE-019 addendum supplies a concrete lost-admission interleaving for the already-noted unlocked state check, alongside its version-specific timeout failure. UserData copying still needs the container lock through the actual copy (022); index copying already holds it. Empty-value deletion and documented nullable listener defaults were verified against SDK context rather than assumed from method names.
