# Friends.hxx — fresh baseline review

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. All 644 lines read; Windows-focused static review.

## File-specific inspection

- Checked every override and its conditional surface: avatar buffer type, avatar criteria alias, rich-presence bool/void return adapter, optional operation listeners, name/avatar copies, friend/invitation methods, richer presence enumeration, game invites and same-game checks.
- Matched modern persona/presence/list contracts to `Source/DLLs/1.152.11/galaxy/IFriends.h:620-1028`; traced the implementation, User cache accessor, Server user-data exchanges and Shared storage rather than treating this header's copied documentation as independent evidence.
- `mtx_reachable_peers` is mutable, so the const same-game getter can lock the set. This lock protects the set, not `GalaxyUserData` strings or `avatar_criteria`. The consequential supported Copy-API race is detailed in BASE-API-002 beside the implementation.
- Operation listeners are borrowed SDK objects, not owned here. Deferred `const char*` arguments receive string lifetime extension in the registrar. Unregister handling itself is a dependency, not a new declaration finding in this file.
- The header promises coherent friend enumeration/predicates, automatic persona refresh and null-as-delete semantics; the respective implementation mismatches are BASE-API-003, BASE-API-005 and BASE-API-004, with full local evidence in `Friends.cxx.review.MD`.

No additional independent declaration defect was confirmed. Feature branches were read, but all SDK variants were not compiled or individually ABI-compared. Avatar/overlay and persistent GOG friendship service completeness remain explicit scope limitations; no security inference was drawn from the LAN-peer model. No build or test executed.
