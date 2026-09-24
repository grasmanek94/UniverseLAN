# Friends.hxx — fresh baseline review

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. All 644 lines read; Windows-focused static review.

## File-specific inspection

- Checked every override and its conditional surface: avatar buffer type, avatar criteria alias, rich-presence bool/void return adapter, optional operation listeners, name/avatar copies, friend/invitation methods, richer presence enumeration, game invites and same-game checks.
- Matched modern persona/presence/list contracts to `Source/DLLs/1.152.11/galaxy/IFriends.h:620-1028`; traced the implementation, User cache accessor, Server user-data exchanges and Shared storage rather than treating this header's copied documentation as independent evidence.
- `mtx_reachable_peers` is mutable, so the const same-game getter can lock the set. This lock protects the set, not `GalaxyUserData` strings or `avatar_criteria`. The consequential supported Copy-API race is detailed in BASE-API-002 beside the implementation.
- Operation listeners are borrowed SDK objects, not owned here. Deferred `const char*` arguments receive string lifetime extension in the registrar. Unregister handling itself is a dependency, not a new declaration finding in this file.
- The header promises coherent friend enumeration/predicates, automatic persona refresh and null-as-delete semantics; the respective implementation mismatches are BASE-API-003, BASE-API-005 and BASE-API-004, with full local evidence in `Friends.cxx.review.MD`.

No additional independent declaration defect was confirmed. Feature branches were read, but all SDK variants were not compiled or individually ABI-compared. Avatar/overlay and persistent GOG friendship service completeness remain explicit scope limitations; no security inference was drawn from the LAN-peer model. No build or test executed.

## Thorough follow-up addendum — 2026-09-24

Full reread: lines 1-644 at production baseline `b30e8387`. Checked default/self-ID selectors against the actual SDK, not inferred defaults for every user-taking method. Indexed key pointer exposure from 1.148.2 and the defaulted presence request yield ADD-API-001 and ADD-API-002, detailed beside `Friends.cxx`. The mutable peer-set mutex protects each operation but does not establish a multi-call snapshot or a startup snapshot-complete barrier. Avatar criteria remains plain mutable state, but unsupported avatar acquisition was not promoted into a new serious capability finding. BASE-API-002 covers the consequential supported persona/presence synchronization gap; BASE-API-003–005 remain as qualified in the implementation addendum. No new header-only ID or ABI certification; no execution.
