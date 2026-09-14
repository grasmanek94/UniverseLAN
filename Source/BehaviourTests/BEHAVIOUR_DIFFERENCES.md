# Behaviour Difference Log

Use one entry per candidate, confirmed, accepted beneficial difference, or
matched live baseline. Do not add credentials, raw Galaxy IDs, runtime logs, or
copied trace artifacts. Retain the failed run's local normalized report and
refer to its public observation only.

For `Simple/session-id-repeatability`, add a candidate only after a mismatched
focused live CTest. Record the official and UniverseLAN `user1`/`user2` boolean
equality observations and the retained local report reference only; never record
either session ID, a zero/nonzero classification, user ID, persona, timestamp,
credentials, or internals.

## Template

### `<scenario>` on `<sdk>/<arch>`

- Date:
- Classification: candidate difference | confirmed incompatibility | accepted difference | accepted beneficial difference | accepted beneficial variation | official-environment variation | unresolved | matched live baseline
- Public observation:
- Official normalized result:
- UniverseLAN normalized result:
- Reproduction command/test name:
- Follow-up:

## Recorded Differences

The recorded accepted lobby convergence result passes because eventual-list retry
timing is explicitly excluded from lane equality. Matched live baselines remain
strict for every public fact they record.

### `Simple/public-lobby-create-list-join-leave` on `1.152.11/x64`

- Date: 2026-09-13
- Classification: accepted beneficial variation
- Public observation: filtered public-list convergence completed after two bounded attempts for official `user2` and one bounded attempt for UniverseLAN `user2`; every lane-equivalent public role fact matched.
- Official normalized result: selected one valid candidate, joined it successfully, and completed the required two-member and leave relations after two list attempts.
- UniverseLAN normalized result: selected one valid candidate, joined it successfully, and completed the same required relations after one list attempt.
- Reproduction command/test name: `universelan-behaviour-simple-public-lobby-create-list-join-leave-x64-1.152.11`.
- Follow-up: attempt count/retry use remains retained and individually bounded diagnostic context, but is not a lane-equivalence relation because public listing is eventually consistent. The observed faster UniverseLAN convergence is accepted. Cleanup was acknowledged by all four hosts; do not copy the run-root path, token, IDs, logs, or artifacts here.

### `Simple/gog-services-state` on `1.152.11/x64`

- Date: 2026-09-13
- Classification: accepted beneficial difference
- Public observation: post-auth `IUtils::GetGogServicesConnectionState()` symbolic state, characterized immediately, after one `ProcessData`, and after ten settled pumps; symbolic global service-state-listener events are phase-tagged relative to auth.
- Official normalized result: `user1`: immediate `undefined`, one-pump `undefined`, settled `undefined` (`10` pumps, `100-249ms` bucket), events `[]`; `user2`: immediate `undefined`, one-pump `undefined`, settled `undefined` (`10` pumps, `100-249ms` bucket), events `[]`.
- UniverseLAN normalized result: `user1`: immediate `connected`, one-pump `connected`, settled `connected` (`10` pumps, `100-249ms` bucket), events `[before:connected]`; `user2`: immediate `connected`, one-pump `connected`, settled `connected` (`10` pumps, `100-249ms` bucket), events `[before:connected]`.
- Reproduction command/test name: `universelan-behaviour-simple-gog-services-state-x64-1.152.11`; use explicit runner `--characterize-gog-services-state` mode only to refresh the broader public observation.
- Follow-up: the strict comparator accepts only the declared same-profile pair `GOG undefined` and `UniverseLAN connected`. It requires exact equality for every other record and state, and does not accept listener differences because the strict contract registers no listener. Retain local characterization reports; do not copy sensitive artifacts here.

## Matched Live Baseline

### `Simple/chat-room-message-delivery` on `1.152.11/x64`

- Date: 2026-09-14
- Classification: matched live baseline
- Public observation: official-only characterization observed one successful symbolic room request, terminal send, and callback-local matching receive path. The strict four-host comparison matched the same role-local public facts in UniverseLAN.
- Official normalized result: sender completed one valid symbolic room relation and one successful send terminal tied to its returned index; receiver completed one callback-local matching chat-message/type/token relation.
- UniverseLAN normalized result: matched the official sender room/send and receiver callback-local symbolic relations.
- Reproduction command/test name: `--characterize-official-gog-chat-room-message-delivery`; `universelan-behaviour-simple-chat-room-message-delivery-x64-1.152.11`; portable `RunBehaviorCTest.cmake` with `BEHAVIOUR_TEST_LABEL="^chat-room-message-delivery$"`.
- Follow-up: the approved official profiles being friends with messaging privacy permitting friends is an external test-environment precondition, not a product root-cause claim or comparison exception. All official-only and four-host chat hosts exited; one-time relays, controls, runtime output, and token-bearing artifacts were redacted. No raw ID, room ID, message ID, token, or run-root path is recorded here.

### `Advanced/multiple-lobby-membership-and-message-isolation` on `1.152.11/x64`

- Date: 2026-09-14
- Classification: matched live baseline
- Public observation: the first official-GOG-only characterization observed `L0`, `L1` message delivery and the second observed `L1`, `L0`; all required create, configuration, discovery, join, payload, sender, and cleanup facts succeeded in both. The first focused comparison consequently reported a strict joiner message-order mismatch (`GOG L1,L0`, `UniverseLAN L0,L1`) with acknowledged cleanup. This is retained as an observed unstable official cross-lobby callback sequence, not an inferred root cause.
- Official normalized result: supported concurrent multiple membership and the requested adjacent operations. The public lobby-message callback/read API has no message-type field; this is recorded as unavailable, not treated as a product difference.
- UniverseLAN normalized result: matched every required symbolic fact and reverse joiner-first cleanup. Its observed joiner message sequence was `L0`, `L1`; the sequence remains in its trace/report but is not equality-required because official characterization was not stable.
- Reproduction command/test name: explicit `--characterize-multiple-lobby-membership-and-message-isolation`; `universelan-behaviour-advanced-multiple-lobby-membership-and-message-isolation-x64-1.152.11`.
- Follow-up: no product mismatch is accepted or hidden: the first strict mismatch and both official sequence observations are recorded above. A later mismatch in any stable fact remains strict. Do not copy a run-root path, tag, payload, raw ID, message ID, metadata value, or timestamp here.

### `Simple/public-lobby-create-list-join-leave` on `1.152.11/x64`

- Date: 2026-09-13
- Classification: matched live baseline
- Public observation: public/joinable two-member FCM creation, automatic enter, metadata update, filtered list/join identity relation, two-member and post-leave owner snapshots, and joiner-first leave callbacks.
- Official normalized result: matched the UniverseLAN result for `user1` and `user2`.
- UniverseLAN normalized result: matched the official result for `user1` and `user2`.
- Reproduction command/test name: `universelan-behaviour-simple-public-lobby-create-list-join-leave-x64-1.152.11`.
- Follow-up: all four hosts acknowledged cleanup and the successful private root was removed. Add a candidate entry if a later live comparison mismatches; never copy the private token or artifacts here.

### `Simple/public-lobby-data-propagation` on `1.152.11/x64`

- Date: not recorded in the existing live-baseline register
- Classification: matched live baseline
- Public observation: after post-join observer arming, owner lobby-data update succeeded; the joined-lobby listener received the update with invalid symbolic member ID and public copied-value visibility in the callback and after bounded pumping.
- Official normalized result: matched UniverseLAN for required create/list/join, data-update, callback-validity, copied-value, and joiner-first cleanup facts.
- UniverseLAN normalized result: matched official GOG for the same required facts.
- Reproduction command/test name: `universelan-behaviour-simple-public-lobby-data-propagation-x64-1.152.11`.
- Follow-up: list convergence, callback multiplicity, and callback-gate discovery order remain diagnostic only. The comparison matched and cleanup was acknowledged by all four hosts; no candidate difference was recorded.
