# Fresh baseline review: CloudStorage.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Entire file read, lines 1–366. Windows-oriented static review; no build/runtime checks.

## File-specific inspection

- Checked the full public surface against the latest SDK and the legacy metadata-index contract, including upload argument feature guards, savegame defaults, hash buffer methods, and callback-only getters.
- `DeleteFile` correctly brackets the Windows macro with push/undef/pop in the declaration; the implementation does likewise. No Windows macro-collision defect is reported.
- The interface owns neither `InterfaceInstances`, `ListenerRegistrarImpl`, nor `SharedFileUtils`; the normal `InterfaceInstances::reset` order keeps dependencies alive while the implementation is destroyed. The shared subcontainer captured by streaming download also preserves its filesystem parent through that operation.
- Separate recursive mutexes protect structural access to the last list and metadata vector. They do not associate either vector with a pending callback. The single members at lines 51–55 explain BASE-STORAGE-007, detailed in `CloudStorage.cxx.review.MD`.
- The plain group flag and atomic counter at lines 57–58 do not form an atomic group state. Sequential group-ID reuse is established by BASE-STORAGE-006; concurrent open/close/upload needs the same state-machine fix, not merely a stronger atomic ordering on the counter.
- Public nullable hash and timestamp defaults were traced through implementation. Missing hash calculation, conflict deletion, metadata decoding, and I/O handling are detailed as BASE-STORAGE-001 through BASE-STORAGE-005 and BASE-STORAGE-008 in the implementation sidecar.
- Raw per-operation listener parameters have SDK cancellation obligations despite being non-owning pointers. BASE-STORAGE-009 covers the concrete pending-operation lifetime violation. Holding caller-owned buffers until completion is explicitly required by the SDK, so asynchronous buffer retention alone is not called a defect.

## Findings disposition and limits

No additional declaration-only defect is counted. Full defect sections are in the implementation sidecar, where the failing control flow resides. This is a scoped observation, not proof of correctness. Guards were read statically across the file; no claim of compiling every SDK variant or of binary/behavioral equivalence is made. The legacy comments contain outdated parameter descriptions, but no style-only defect is added.

Recommended validation: cloud variants before/after metadata removal, savegame introduction, and hashing introduction; cancellation and nested callback enumeration; Windows save replacement failure paths. See the implementation sections for exact verification scenarios.

## Source-first re-review addendum — 2026-09-24

Full `1-366` reread completed before baseline comparison. Latest SDK and 1.148.6 legacy callback/metadata signatures were checked with the actual feature gates. Caller buffer lifetime through completion remains an explicit precondition, while `WriteFunc` has signed-int chunk extents. The header's bool/counter pair still needs a compound synchronized savegroup state (BASE-STORAGE-006 addendum). New implementation details are ADD-STORAGE-001 (per-invocation scratch), 002 (owning data/metadata generation), and 003 (consistent quota pair), all canonical in `CloudStorage.cxx.review.MD`. No extra declaration-only ID or claim of all-version compilation is made.
