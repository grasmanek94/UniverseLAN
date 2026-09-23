# Fresh baseline review: Stats.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Entire file read, lines 1–640. Static Windows-focused review; no compilation or execution.

## File-specific inspection

- Checked all declarations, default self IDs, optional per-operation listeners, remote completion hooks, visibility variants, and leaderboard signature feature guards against implementation and SDK context.
- The class is a thin facade with non-owning interface/registrar dependencies. Its mutex aliases do not introduce a member mutex or enforce synchronization. BASE-STORAGE-012 in `Stats.cxx.review.MD` identifies the actual unsafe accesses through Shared container views.
- The average-rate method's count/session delta contract at lines 107–118 makes scalar rate addition invalid; full finding BASE-STORAGE-010 resides in the implementation sidecar.
- The store/reset comments explicitly promise persistence and listener completion. BASE-STORAGE-011 traces the missing error channel through the void configuration save helper.
- Fully inspected leaderboard declarations: range indexes are zero-based; around-user ranges must shift to preserve size when possible; result getters are callback-scoped; `forceUpdate` permits a worse score; detail payloads have a 3071-byte input limit and truncating output contract. Implementation never produces a successful leaderboard request. No independent ranking/indexing error is claimed merely from unimplemented getters whose documented preconditions cannot be satisfied.
- Copy and pointer-returning name/description methods have distinct lifetime/thread-safety contracts. A public `Copy` suffix must cover the entire copy, not just map lookup. See implementation synchronization analysis.
- Achievement enumeration operates on an unordered map. Order is not promised stable across mutations in this header; no unsupported stable-order requirement is invented.

## Findings disposition and verification limits

No additional declaration-only defect counted. Canonical full sections: BASE-STORAGE-010, BASE-STORAGE-011, BASE-STORAGE-012 in `Stats.cxx.review.MD`. Feature branches were inspected textually; compiler/ABI coverage of every SDK version remains unverified. Recommended validation follows those sections, plus explicit capability tests requiring leaderboard failure callbacks rather than fabricated sorted data.
