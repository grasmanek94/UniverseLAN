# Matchmaking.hxx — fresh baseline review

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. All 638 lines read; Windows-focused static inspection.

## File-specific inspection

- Reviewed every API override, optional lobby listeners, legacy bool/modern void return adapter, char/void message input variants, callback processing entry points and the complete documented output contracts.
- Traced the integer/string variant filter representation, per-request filter snapshots, result-count/fullness fields and `ListenersRequestHelper` locking. Recording filters under a recursive mutex and retaining a separate snapshot per request is a sound starting point for overlapping queries.
- `lobby_list_filtered` is an unordered map. It represents membership but cannot directly express an ordered proximity result; the concrete no-op near-filter defect and required ordered-result consideration are BASE-API-006 in `Matchmaking.cxx.review.MD`.
- The three shared-pointer maps do not guarantee identical object identity after refresh. Current joined-map consumers were inspected before concluding whether that mattered; no independent “different pointers” finding was counted. Missing session invalidation is detailed as BASE-API-012 beside the implementation.
- Compared SDK `1.152.11/galaxy/IMatchmaking.h` in full and legacy `1.57.0` list/filter declarations. The empty-output requirement for Copy getters and the non-thread-safe pointer getter remarks are genuine SDK contracts, not merely comments copied into this header.
- Traced serialized Shared lobby fields and Server responses for creation, join, leave, list/data refresh, structural/property updates and lobby messages. Successful callbacks generally expose cached state before notifying callers; automatic information retrieval for existing members is the separate cross-component BASE-API-005.

No independent header-only defect is added. Implementation findings BASE-API-006 through BASE-API-012 have complete evidence, fixes and verification beside `Matchmaking.cxx`. All conditional branches were read, but this review does not certify every SDK ABI or compile configuration. No build or test executed; no-findings-in-declarations is a scoped observation.

## Thorough follow-up addendum — 2026-09-24

Full reread: lines 1-638 at production baseline `b30e8387`. All three lobby maps, per-request filters and processed-event declarations traced into Client/Shared/Server. Multi-lobby membership is intentional and supported by Server code; different snapshot object identity is not sufficient evidence of lost membership or messages. The actual newly demonstrated issue is event/cache ordering, ADD-API-003 beside `Matchmaking.cxx`. SDK result limits are explicitly nonzero, and modern GetLobbyByIndex is callback-scoped; tests using zero limits or that getter outside its callback are not supported-path proof. BASE-API-009's proposed nonmember owner check is narrowed by the SDK return-value precondition. No independent header-only ID, tests or builds.
