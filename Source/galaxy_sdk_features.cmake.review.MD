# Fresh baseline review: Source/galaxy_sdk_features.cmake

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. All 306 lines reviewed.

## Inspection notes
- Inspected every declared version interval and the inclusive MIN/MAX implementation. Repeated declarations for discontinuous features union their enabled ranges instead of a later disabled interval overwriting a prior enabled result.
- Checked PUBLIC compile definitions and global per-version properties; each recorded feature becomes 0 or 1 and UVV/TARGET are inherited in function scope.
- Cross-checked factory/direct transition, specific-listener introductions, game-server Utils/Telemetry, cloud/hash/savegroup and later thread/shutdown/OpenID changes against consumers and representative SDK headers reviewed by the subsystem owners.
- NEAR_FILTER_ENUM is deliberately never enabled for the current matrix. The real near-filter API being a no-op is documented as BASE-API-006 in Matchmaking.cxx.review.MD, not an invented missing SDK enum.
- RED prefix is gated to 1.149.12–1.149.16; none of the current 69 input directories falls in that interval. The no-version loader issue is latent (BASE-UTIL-015), not a current generated-target failure.

## Findings and validation
No independent confirmed defect in interval composition. Consumers sometimes use the wrong otherwise-correct gate; see BASE-INTERCEPT-006/007. The five-version Windows x64 Debug production/interceptor build passed. No exhaustive binary ABI comparison or Linux compilation was performed.

## Follow-up static matrix audit — 2026-09-24

All 306 lines were reread. The 158 interval rows define 154 distinct flags. A read-only Python evidence sidecar, `.ai/review-addendum/BUILD-static-audit.py`, evaluates their OR-of-inclusive-interval semantics for all 69 selected versions: 10,626 values. Its explicit declaration-sentinel mapping compares 152 flags against comment-stripped SDK headers over 10,371 applicable cells, with zero remaining discrepancies. The three factory-only concepts are checked within their 30-version domain, rather than falsely demanding a GalaxyFactory declaration in modern SDKs. `USER_DATA_LISTENERS` and `USER_SIGNIN_CROSSPLATFORM` have no production readers and lack a sufficiently specific documented semantic contract to certify their named thresholds; their values are evaluated, but they are not marked declaration-verified. This is a lexical/static audit, not a C++ parser or binary ABI proof.

Important probe corrections made from actual declarations: `HAS_PERSONASTATE_ENUM` means the exact `PersonaState` type, not the older `PersonaStateChange`; `HAS_LISTENERTYPE` selects the registrar parameter type, not first existence of the enum; invitation failure reasons must be checked in the responding listener rather than the sending listener; `HAS_IUSERTIMEPLAYEDRETRIEVELISTENER_UPDATE` matches the corrected inherited listener tag and global helper introduced in 1.76.0. These distinctions prevented false feature-table findings.

The entire SDK listener-declaration sweep found one repeated-tag family: 1.73.0/1.74.0/1.75.0 declare both `ILeaderboardRetrieveListener` and `IUserTimePlayedRetrieveListener` with `LEADERBOARD_RETRIEVE`. The update flag is correctly false there; production Stats dispatch nevertheless uses the older type through an unchecked registrar cast. This is handed to CORE/STORAGE in the BUILD notebook, not charged as a defect in this correct interval table or silently repaired in excluded SDK headers.

The production feature-read audit found `GALAXY_BUILD_FEATURE_HAS_IFRIENDS_ONPERSONADATACHANGED` at `Client/Impl/User.cxx:67,655`, while the defined name is `GALAXY_BUILD_FEATURE_IFRIENDS_ONPERSONADATACHANGED`. Both bodies are compiled out under the normal definitions. The BUILD notebook records the STORAGE handoff and the limit on inferring a promised sign-in notification from that fact alone. Existing incorrect interceptor gates retain BASE-INTERCEPT-006/007 and the other owner's ADD-INTERCEPT-002. No new BUILD ID is assigned to them.

Detailed mappings, hashes, exact coverage equality and proposed verification are in `.ai/review-addendum/BUILD.MD`. No source, SDK, build or test changes were made.
