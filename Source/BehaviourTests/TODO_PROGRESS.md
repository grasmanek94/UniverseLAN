# BehaviourTests Progress And TODO

This is the status register for documentation and implementation planning. It
does not turn a characterization or a candidate mismatch into a passing result.
See [COVERAGE.md](COVERAGE.md) for exact contracts and
[BEHAVIOUR_DIFFERENCES.md](BEHAVIOUR_DIFFERENCES.md) for live observations.

## Completed

| Item | Status and result |
| --- | --- |
| Framework | Implemented for x64 `1.152.11`: separate official/UniverseLAN hosts, concurrent or sequential lanes, isolated roots, credentials preflight, trace normalization, comparison reports, and opt-in CTest registration. |
| Non-mutating identity scenarios | `initialize-and-sign-in`, `session-id-repeatability`, and `gog-services-state` are implemented. The service-state contract accepts only official `undefined` versus UniverseLAN `connected`; all other records remain strict. |
| Temporary lobby lifecycle | `public-lobby-create-list-join-leave` is implemented and had a matched live baseline on 2026-09-13. Official list convergence took two bounded attempts and UniverseLAN one; this is an accepted timing/convergence difference, not exact cross-lane equality. |
| Owner-close lobby lifecycle | `public-lobby-owner-close-lifecycle` is implemented with two official-only characterizations followed by a strict four-host matched baseline. Official GOG empirically reported creator `user-left`, joiner `lobby-closed`, tagged-list absence, and no targeted prior-owner member-state callback; UniverseLAN now matches that narrow FCM-close behavior. The header generically documents member notifications, so the absence remains an empirical compatibility fact. Final callback presence/absence follows all scenario pumps plus a bounded settle window; cleanup ack requires a confirmed terminal leave or safe confirmed retry. |
| Temporary lobby data | `public-lobby-data-propagation` is implemented, characterized, and recorded as a matched live baseline. Callback multiplicity and cross-host gate discovery order remain diagnostic only. |
| Advanced multiple-lobby membership | `multiple-lobby-membership-and-message-isolation` is implemented. The first 2026-09-14 official-GOG-only characterization and later comparison supported two adjacent create requests, explicit public/joinable/capacity-two setup, two tagged discoveries and adjacent join requests, symbolic isolated messages, and reverse joiner-first cleanup. The first strict focused comparison exposed opposite official/UniverseLAN cross-lobby joiner message sequences; a second official characterization showed the official sequence itself is not stable, so the retained sequence is diagnostic rather than equality-required. |
| Temporary chat delivery | The strict and characterization paths are implemented. The 2026-09-14 official-only characterization and strict four-host comparison matched the symbolic room-request, send, and callback-local receive path. The approved official profiles must remain friends with messaging privacy permitting friends as an external test-environment precondition; this does not assert a product root cause. |
| Friends peer information | `friends-peer-information-retrieval` is implemented with official-only characterization and strict comparison. Three clean official-only trials on 2026-09-14 matched terminal success, available information, nonempty copied name, symbolic `offline` peer state, and filtered requested-peer `name-avatar`, then `none` persona-change events for both profiles. A later official `none`-only variation makes that event sequence diagnostic. The focused full two-lane CTest accepts only observed `GOG offline` versus `UniverseLAN online` persona state, consistent with the documented service-state environment; it is an accepted beneficial environmental difference, not an SDK guarantee. Terminal success, availability, copied-name, callback-peer, and every other role-local fact remain strict. Retrieval has no friendship or direct-message privacy precondition. |
| Diagnostics | Explicit runner modes exist for GOG-service state, lobby-data propagation, chat-message delivery, and official-GOG-only multiple-lobby membership. They collect public observations without deciding lane equality. |

## Remaining Work

| Priority | Work |
| --- | --- |
| Maintain | Rerun direct chat only with the approved official profiles as friends and messaging privacy permitting friends. Treat that as an external environment precondition and record a new candidate only if a stable public mismatch recurs. |
| Maintain | Rerun friends peer information with approved signed-in profiles only. Do not create friendships or mutate social data; record a candidate only for a stable public mismatch. |
| Expand Simple coverage | Characterize and add contracts for matchmaking failure/lifecycle paths, networking, friends, stats, storage, cloud, custom networking, apps, telemetry, and utils only when account/application mutation and cleanup rules are approved. |
| Add Advanced coverage | The first Advanced lobby scenario is complete. Add further Advanced scenarios only after their constituent Simple public contracts are characterized and stable. |
| Version/platform matrix | Expand beyond x64 `1.152.11` only after repeatable official comparisons establish the baseline. |
| Hygiene | Keep scenario manifests, the plan, coverage, this register, and the difference log synchronized after every live run or characterization. |

## Required Validation

Before documenting a new or changed scenario:

1. Confirm the host uses only public selected-version SDK APIs and that traces omit credentials, private values, raw IDs, timestamps, and runtime output.
2. Configure and build the x64 `1.152.11` framework with `BUILD_UNIVERSELAN_BEHAVIOUR_TESTS=ON` and `LIMIT_VERSIONS="1.152.11"`.
3. Run the appropriate explicit diagnostic before defining or changing a strict public contract; preserve only its sanitized local report reference.
4. With approved credentials, runtime artifacts, authenticated official environment, and network access, configure with `ENABLE_UNIVERSELAN_GOG_BEHAVIOUR_TESTS=ON` and run the focused CTest label through `RunBehaviorCTest.cmake`.
5. Verify cleanup: all temporary-lobby hosts acknowledge cleanup; chat hosts complete bounded exit. Treat retained failure roots as sensitive and inspect them locally only.
6. Update `COVERAGE.md`, `BEHAVIOUR_DIFFERENCES.md`, and `BEHAVIOUR_TEST_PLAN.md` with the actual result and classification, then run `git diff --check`.
