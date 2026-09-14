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

### Listener P2P Configuration Correction

The three historical listener P2P no-delivery entries below are superseded as
passing comparison policy. Listener contracts now require exact expected-channel
delivery and two callback-local peeks in both lanes; no no-delivery pair is
accepted as product behavior. On 2026-09-14, all registered CTest commands
received the verified channel-8 `msvc-18` overlay and both official hosts staged
its SHA-256, but the full suite finished 18/21 with the three listener contracts
still observing the historical non-target callback. GOG documents that modern
SDKs load the peer from installed client redistributables, so the local
side-by-side overlay is not proof of runtime selection. This is an unresolved
official-environment prerequisite, not an accepted UniverseLAN difference. See
`README.md` for the manifest, download, and hash verification procedure; no
downloaded binary is retained in the repo.

### `Simple/custom-networking-loopback-roundtrip-close` on `1.152.11/x64`

- Date: 2026-09-14
- Classification: unresolved
- Public observation: two official-GOG-only trials signed in both approved profiles, then each independently issued public `ICustomNetworking::OpenConnection` to a runner-owned ephemeral loopback binary echo endpoint. Each host received an open failure terminal; no send, data, peek, read, or close operation was issued. A later symbolic URL-form diagnostic observed both valid WebSocket forms reach asynchronous `connection-failure` with no synchronous API error, while the omitted-scheme diagnostic set synchronous `invalid-argument` and produced no bounded terminal callback.
- Official normalized result: both profiles had successful initialization/sign-in/self-state records. The initial trials had `openTerminal=failure`, `dataRoundtripRelationsComplete=false`, and `closeTerminal=not-issued`; the URL-form run retained only form labels and public terminal/failure/API-error categories.
- UniverseLAN normalized result: not run; a strict comparison is not justified without successful repeatable official open/roundtrip/close evidence.
- Reproduction command/test name: `--characterize-official-gog-custom-networking-loopback-roundtrip-close`; no CTest is registered.
- Follow-up: retain the sanitized local characterization report only. The runner endpoint returns opaque binary frames unchanged and is not behavior evidence. Do not infer an SDK cause from the open failure or promote any send/peek/read/close relation before a successful official baseline. No connection ID, endpoint URL/port, payload bytes/lengths, credential, timestamp, control, runtime output, or artifact path is recorded.

### `Simple/bidirectional-lobby-member-data-propagation` on `1.152.11/x64`

- Date: 2026-09-14
- Classification: matched live baseline
- Public observation: two clean official-GOG-only trials created the safe initially nonjoinable tagged public capacity-two FCM lobby, explicitly observed joinability, established public two-member state, armed both `GlobalLobbyDataListener` instances, and released one member-data update per host. The selected header's void setter completed through a successful member-data operation callback. Both hosts observed symbolic self and other callback targets with callback-local visible/equal copies and nonempty equal settled self/other copies.
- Official normalized result: both profiles completed successful self-targeted operation terminals, valid shared-lobby self/other callback relations, callback-local private equality/visibility, settled self/other copies, and terminal leaves. Both trials retained local `self, other` callback target order with two callbacks per host.
- UniverseLAN normalized result: the focused four-host comparison matched every strict setup, terminal, target, callback-local copy, settled-copy, and cleanup fact. It retained creator `self, other` and joiner `other, self` local target orders while matching all strict relations.
- Reproduction command/test name: `--characterize-official-gog-bidirectional-lobby-member-data-propagation`; `universelan-behaviour-simple-bidirectional-lobby-member-data-propagation-x64-1.152.11`; portable `RunBehaviorCTest.cmake` with `BEHAVIOUR_TEST_LABEL="^bidirectional-lobby-member-data-propagation$"`.
- Follow-up: callback count and local target order are visible per-host diagnostic context only because both member updates start after the shared gate. The contract remains strict for operation terminal, callback lobby/member self/other, changed-data visibility, private equality/nonempty, settled copies, and cleanup. No raw ID, lobby ID, key, marker, token, value, timestamp, control, runtime output, or artifact path is recorded.

### `Simple/reliable-p2p-after-lobby-leave` on `1.152.11/x64`

- Date: 2026-09-14
- Classification: matched live baseline
- Public observation: two official-only trials used a temporary tagged public capacity-two FCM lobby. User2 armed a public networking listener, confirmed local `user-left`, and remained alive. User1 observed the targeted member `left`, settled as the sole member/owner, then scheduled one reliable opaque send to the former valid user ID. The former member received no networking callback and made no peek in either trial.
- Official normalized result: confirmed leave/member/sole-owner relations, scheduled `true`, zero callback/expected-channel/non-target callback counts, zero peeks, listener destruction, and terminal creator leave.
- UniverseLAN normalized result: matched every required relation directly, including zero post-leave networking callback and peek observations.
- Reproduction command/test name: `--characterize-official-gog-reliable-p2p-after-lobby-leave`; `universelan-behaviour-simple-reliable-p2p-after-lobby-leave-x64-1.152.11`; portable `RunBehaviorCTest.cmake` with `BEHAVIOUR_TEST_LABEL="^reliable-p2p-after-lobby-leave$"`.
- Follow-up: no accepted LAN benefit is claimed. `SendP2PPacket` reports scheduling rather than delivery, and this narrow post-leave absence is empirical rather than a general SDK guarantee. No raw ID, lobby ID, marker, token, payload byte, length, timestamp, control, runtime output, or artifact path is recorded.

### `Simple/bidirectional-lobby-message-delivery` on `1.152.11/x64`

- Date: 2026-09-14
- Classification: matched live baseline
- Public observation: two clean official-GOG-only trials created an initially nonjoinable tagged public/capacity-two FCM lobby, wrote the public collision marker, explicitly observed joinability before discovery, armed both public `GlobalLobbyMessageListener` instances before the exchange release, and scheduled one distinct opaque binary lobby message from each member. Both roles observed exactly one symbolic self sender and one other sender with callback-local shared-lobby, read-sender, directional-payload, and message-size relations. Both official trials retained local `self, other` callback order and terminal cleanup acknowledgements.
- Official normalized result: the focused official lane again completed both scheduled sends, two callback-local self/other relations per host, all strict payload/size/symbolic-lobby facts, and terminal leaves. Its creator and joiner callback orders were `self, other`.
- UniverseLAN normalized result: matched every strict setup, scheduling, cardinality, symbolic-lobby, self/other sender, callback-local payload/size, and cleanup fact. Creator order was `self, other`; joiner order was `other, self`.
- Reproduction command/test name: `--characterize-official-gog-bidirectional-lobby-message-delivery`; `universelan-behaviour-simple-bidirectional-lobby-message-delivery-x64-1.152.11`; portable `RunBehaviorCTest.cmake` with `BEHAVIOUR_TEST_LABEL="^bidirectional-lobby-message-delivery$"`.
- Follow-up: the joiner ordering variation is retained in the normalized report as independent-sender diagnostic context. It is not hidden and does not fail the contract because the two sends are independent after the shared gate; no cross-host or sender-global order is an SDK promise. The contract remains strict for exactly one scheduled send per host, exactly two callback-local messages per host, and each symbolic lobby/sender/payload/size relation. No raw ID, lobby/message ID, marker, payload bytes, length, timestamp, control, runtime log, or artifact path is recorded.

### `Simple/reliable-p2p-listener-peek` on `1.152.11/x64`

- Date: 2026-09-14
- Classification: superseded runtime-configuration observation
- Public observation: three clean official-GOG-only trials created an initially nonjoinable tagged public/capacity-two FCM lobby, configured its public collision marker, explicitly observed joinable before discovery, armed `GlobalNetworkingListener`, completed the post-arm settling window, and scheduled one reliable send to the current public-query-discovered member. Every official joiner observed exactly one symbolic non-target callback, no expected-channel callback, and no peeks. Both terminal leaves and cleanup acknowledgements completed in all three trials.
- Official normalized result: strict setup, membership, listener construction, post-arm settling, sender scheduling, listener destruction, and terminal leaves succeeded. The exact accepted delivery record is one non-target callback with no expected-channel callback and no peeks.
- UniverseLAN normalized result: the focused four-host comparison completed the exact expected-channel callback/size relation, two equivalent successful non-consuming peeks, valid non-self creator sender and opaque payload/length relations, clean listener destruction, and matching local leaves.
- Reproduction command/test name: `--characterize-official-gog-reliable-p2p-listener-peek`; `universelan-behaviour-simple-reliable-p2p-listener-peek-x64-1.152.11`; portable `RunBehaviorCTest.cmake` with `BEHAVIOUR_TEST_LABEL="^reliable-p2p-listener-peek$"`.
- Follow-up: superseded by the strict channel-8-overlay contract. A true `SendP2PPacket` result still reports scheduling and peek remains non-consuming, but the comparator now requires exact delivery/two-peek records in both lanes. No raw IDs, lobby IDs, payload bytes, marker value, message length, control, runtime output, or run-root path is recorded.

### `Simple/bidirectional-reliable-p2p-listener-peek` on `1.152.11/x64`

- Date: 2026-09-14
- Classification: superseded runtime-configuration observation
- Public observation: three clean official-GOG-only trials used a public, initially nonjoinable, tagged capacity-two FCM lobby, explicitly observed joinability before filtered list/join, publicly queried each current other member, armed and settled both `GlobalNetworkingListener` instances, and synchronized exactly one reliable opaque payload per direction. Every trial scheduled both directions, then each host observed one symbolic non-target callback with no expected-channel callback and no callback-local peeks. Both listener destructions and fresh-deadline terminal leaves completed.
- Official normalized result: `user1` to `user2` and independently `user2` to `user1` scheduled once, had the exact no-expected-channel-callback-or-peek result, retained the symbolic non-target callback, and completed all strict setup, public-peer, channel/payload, listener, and cleanup facts.
- UniverseLAN normalized result: both matching directions scheduled once, delivered one expected-channel callback, and made exactly two equivalent callback-local non-consuming peeks with symbolic expected-peer, payload, and size relations. All strict setup and cleanup facts matched.
- Reproduction command/test name: `--characterize-official-gog-bidirectional-reliable-p2p-listener-peek`; `universelan-behaviour-simple-bidirectional-reliable-p2p-listener-peek-x64-1.152.11`; portable `RunBehaviorCTest.cmake` with `BEHAVIOUR_TEST_LABEL="^bidirectional-reliable-p2p-listener-peek$"`.
- Follow-up: superseded by the strict channel-8-overlay contract. `P2P_SEND_RELIABLE` still reports scheduling and listener peeks remain non-consuming, but both independent directions now require exact delivery/two-peek records in both lanes. No raw ID, lobby ID, marker, token, payload byte, length, control, runtime output, or artifact path is recorded.

### `Simple/bidirectional-reliable-p2p-poll-read` on `1.152.11/x64`

- Date: 2026-09-14
- Classification: matched live baseline
- Public observation: three clean official-GOG-only trials created the temporary public capacity-two FCM lobby, synchronized listener-free polling paths, and scheduled one reliable directional send per host. Each direction observed expected-channel availability after `ProcessData`, one exact-size read, symbolic expected sender/payload relations, and no expected-channel availability immediately after that read. No `INetworkingListener` was constructed; every terminal leave completed.
- Official normalized result: both profiles established valid public two-member state, scheduled once, retained `listenerConstructed=false`, called availability from every polling iteration, read once only after availability, matched symbolic peer/payload/size relations, and observed queue consumption.
- UniverseLAN normalized result: the focused four-host strict comparison matched every required public setup, polling, delivery, symbolic relation, post-read empty-availability, and cleanup fact.
- Reproduction command/test name: `--characterize-official-gog-bidirectional-reliable-p2p-poll-read`; `universelan-behaviour-simple-bidirectional-reliable-p2p-poll-read-x64-1.152.11`; portable `RunBehaviorCTest.cmake` with `BEHAVIOUR_TEST_LABEL="^bidirectional-reliable-p2p-poll-read$"`.
- Follow-up: this is a listener-free polling contract only. `SendP2PPacket` still reports scheduling rather than a general delivery guarantee. Listener-mode P2P tests remain callback-local non-consuming peek tests and retain their separately documented no-delivery diagnostics. No raw ID, lobby ID, marker, token, payload byte, length, timestamp, control, runtime output, or artifact path is recorded.

### `Simple/bidirectional-unreliable-p2p-listener-peek` on `1.152.11/x64`

- Date: 2026-09-14
- Classification: superseded runtime-configuration observation
- Public observation: three clean official-GOG-only trials used the safe public, initially nonjoinable, tagged capacity-two FCM lobby, explicitly observed joinability before filtered list/join, publicly queried each current other member, armed and settled both `GlobalNetworkingListener` instances, and synchronized exactly one distinct opaque `P2P_SEND_UNRELIABLE` payload per direction. Every trial scheduled both directions, then each host observed one symbolic non-target callback with no expected-channel callback and no callback-local peeks. Both listener destructions and fresh-deadline terminal leaves completed.
- Official normalized result: `user1` to `user2` and independently `user2` to `user1` each scheduled once and had the exact one-non-target/no-expected-callback/zero-peek result while retaining all public peer, channel, payload, listener, and cleanup facts.
- UniverseLAN normalized result: the focused four-host comparison scheduled both matching directions, delivered one expected-channel callback, and made exactly two equivalent callback-local non-consuming peeks with symbolic expected-peer, payload, and size relations. All strict setup and cleanup facts matched.
- Reproduction command/test name: `--characterize-official-gog-bidirectional-unreliable-p2p-listener-peek`; `universelan-behaviour-simple-bidirectional-unreliable-p2p-listener-peek-x64-1.152.11`; portable `RunBehaviorCTest.cmake` with `BEHAVIOUR_TEST_LABEL="^bidirectional-unreliable-p2p-listener-peek$"`.
- Follow-up: superseded by the strict channel-8-overlay contract. `P2P_SEND_UNRELIABLE` remains UDP-like and its true return reports scheduling, but both independent directions now require exact delivery/two-peek records in both lanes. No raw ID, lobby ID, marker, token, payload byte, length, control, runtime output, or artifact path is recorded.

### `Simple/public-lobby-owner-close-lifecycle` on `1.152.11/x64`

- Date: 2026-09-14
- Classification: matched live baseline
- Public observation: two official-GOG-only characterizations observed the creator's normal `LeaveLobby` local callback with symbolic `user-left`; the joiner observed global symbolic `lobby-closed` and subsequent tagged-list absence. The armed targeted prior-owner member-state listener received no callback in either official run.
- Official normalized result: all setup/list/join relations succeeded; the target-lobby sequence contained only the global closure callback. The `LeaveLobby` header generically documents other-member notifications, so this FCM-close absence is an empirical compatibility fact, not a header guarantee.
- UniverseLAN normalized result: matched creator leave, joiner global closure, targeted prior-owner callback absence, tagged-list absence, and all setup relations.
- Reproduction command/test name: `--characterize-official-gog-public-lobby-owner-close-lifecycle`; `universelan-behaviour-simple-public-lobby-owner-close-lifecycle-x64-1.152.11`; portable `RunBehaviorCTest.cmake` with `BEHAVIOUR_TEST_LABEL="^public-lobby-owner-close-lifecycle$"`.
- Follow-up: target-lobby callback sequence and cross-listener ordering remain diagnostic, but any non-`lobby-closed` target global leave reason fails. Presence/absence is finalized after post-close listing and a bounded final settling window. Creator cleanup acknowledgement requires a confirmed `user-left` terminal callback; a failed or timed-out initial leave may acknowledge only after a safe, bounded retry confirms it. All hosts acknowledged cleanup; retained artifacts are sanitized and no token, ID, data, timestamp, log, or private control is recorded here.

### `Simple/public-lobby-owner-ownership-transition` on `1.152.11/x64`

- Date: 2026-09-14
- Classification: matched live baseline
- Public observation: two official-only trials observed creator local `user-left`; joiner prior-owner `left` and owner-change-to-self relationships; self as the sole valid member and owner; successful token-derived promoted-owner `SetLobbyData` with copied visibility; joiner local `user-left`; and tagged-list absence after the lobby emptied.
- Official normalized result: all stable setup, filtered-list/join, initial two-member owner, ownership transition, authorization, terminal leave, and absence relations succeeded. Both trials delivered owner-change before member-state, but cross-listener sequence remains diagnostic. Initial list convergence varied from one to two attempts.
- UniverseLAN normalized result: the focused strict four-host comparison matched every stable official relation with acknowledged cleanup.
- Reproduction command/test name: `--characterize-official-gog-public-lobby-owner-ownership-transition`; `universelan-behaviour-simple-public-lobby-owner-ownership-transition-x64-1.152.11`; portable `RunBehaviorCTest.cmake` with `BEHAVIOUR_TEST_LABEL="^public-lobby-owner-ownership-transition$"`.
- Follow-up: listener-class ordering, multiplicity, and bounded list-attempt count remain retained diagnostic context, not equality requirements. The former owner waits for the joiner's post-empty token-filtered probe. No raw ID, tag, token-derived value, timestamp, relay, control, configuration, or runtime output is recorded.

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

## Matched Live Baselines And Accepted Differences

### `Simple/public-lobby-not-joinable-behavior` on `1.152.11/x64`

- Date: 2026-09-14
- Classification: matched live baseline
- Public observation: two official-only trials created public tagged capacity-two FCM lobbies, explicitly completed `SetLobbyJoinable(false)`, and verified public configuration/tag visibility. Each marker-filtered non-full list completed successfully with no candidate selected, therefore no join was issued. The creator stayed sole owner/member, its terminal leave completed under a fresh deadline, and the post-delete filtered list was absent.
- Official normalized result: exact stable public branch is successful zero-candidate list, no selected relationship, no join terminal, no direct-ID/member/member-data/send access, creator sole ownership, and successful post-delete absence.
- UniverseLAN normalized result: the initial focused comparison exposed the nonjoinable lobby and allowed a selected join; after excluding nonjoinable lobbies from ordinary client list results, the focused strict comparison matched every stable official public fact with acknowledged cleanup.
- Reproduction command/test name: `--characterize-official-gog-public-lobby-not-joinable-behavior`; `universelan-behaviour-simple-public-lobby-not-joinable-behavior-x64-1.152.11`; portable `RunBehaviorCTest.cmake` with `BEHAVIOUR_TEST_LABEL="^public-lobby-not-joinable-behavior$"`.
- Follow-up: direct-ID join behavior, join failure reason, callbacks, list order, and any list-exposed branch remain uncharacterized and are not contract assertions. No raw ID, marker value, configuration value, timestamp, control, runtime output, or artifact path is recorded.

### `Simple/public-lobby-full-join-failure` on `1.152.11/x64`

- Classification: matched live baseline
- Public observation: two official-only characterizations and the focused strict comparison observed one filtered full-lobby candidate, one asynchronous terminal `full` join result, no entry, creator sole owner/member state after that failure, terminal creator cleanup, and post-empty tagged-list absence.
- Official normalized result: matched every required public setup, full-list, public-state, terminal, non-entry, creator-state, and cleanup relation.
- UniverseLAN normalized result: matched the official symbolic terminal and all required state and cleanup relations.
- Reproduction command/test name: `--characterize-official-gog-public-lobby-full-join-failure`; `universelan-behaviour-simple-public-lobby-full-join-failure-x64-1.152.11`; portable `RunBehaviorCTest.cmake` with `BEHAVIOUR_TEST_LABEL="^public-lobby-full-join-failure$"`.
- Follow-up: member-data, member enumeration, and lobby-message APIs remain structurally absent from the rejected joiner. The creator uses a fresh cleanup deadline and acknowledges only a matching terminal leave; the nonmember joiner records completion only after the post-empty absence probe. No raw ID, marker, configuration value, timestamp, control, runtime output, or artifact path is recorded.

### `Simple/friends-peer-information-retrieval` on `1.152.11/x64`

- Date: 2026-09-14
- Classification: accepted beneficial difference
- Public observation: three clean official-only trials matched terminal success, callback-peer=requested-peer valid non-self relation, post-terminal availability, nonempty copied persona name, symbolic `offline` peer state, and filtered requested-peer persona changes `name-avatar`, then `none`, for both profiles. A later full comparison observed only terminal `none` for one official profile.
- Official normalized result: all required role-local `IFriends` facts matched. The requested-peer listener sequence is retained as diagnostic context after the later official variation, not strict equality.
- UniverseLAN normalized result: both profiles reported symbolic `online` peer state while matching the required terminal success, callback-peer, availability, copied-name, and self-state facts after adding per-peer information-retrieval state and first-retrieval `name-avatar` notification.
- Reproduction command/test name: `--characterize-official-gog-friends-peer-information-retrieval`; `universelan-behaviour-simple-friends-peer-information-retrieval-x64-1.152.11`; portable `RunBehaviorCTest.cmake` with `BEHAVIOUR_TEST_LABEL="^friends-peer-information-retrieval$"`.
- Follow-up: the comparator accepts only the observed same-profile pair `GOG offline` and `UniverseLAN online`, consistent with the documented service-state environment where official GOG has no GOG Galaxy service while UniverseLAN provides its LAN service. This is an accepted beneficial environmental difference, not an SDK guarantee; every other required record and terminal/availability/name/callback-peer fact remains strict. Requested-peer listener events remain diagnostic after the official variation. Retrieval has no friendship or direct-message privacy precondition. `AVATAR_TYPE_NONE` does not assert absent avatar callback activity because default avatar criteria may apply. Every self/peer ID relay is one-time and removed; failure artifacts retain only symbolic traces/reports and staged binaries, never controls, configuration, relays, or runtime output.

### `Simple/chat-room-message-delivery` on `1.152.11/x64`

- Date: 2026-09-14
- Classification: matched live baseline
- Public observation: official-only characterization observed one successful symbolic room request, terminal send, and callback-local matching receive path. The strict four-host comparison matched the same role-local public facts in UniverseLAN.
- Official normalized result: sender completed one valid symbolic room relation and one successful send terminal tied to its returned index; receiver completed one callback-local matching chat-message/type/token relation.
- UniverseLAN normalized result: matched the official sender room/send and receiver callback-local symbolic relations.
- Reproduction command/test name: `--characterize-official-gog-chat-room-message-delivery`; `universelan-behaviour-simple-chat-room-message-delivery-x64-1.152.11`; portable `RunBehaviorCTest.cmake` with `BEHAVIOUR_TEST_LABEL="^chat-room-message-delivery$"`.
- Follow-up: the approved official profiles being friends with messaging privacy permitting friends is an external test-environment precondition, not a product root-cause claim or comparison exception. All official-only and four-host chat hosts exited; one-time relays, controls, runtime output, and token-bearing artifacts were redacted. No raw ID, room ID, message ID, token, or run-root path is recorded here.

### `Simple/bidirectional-chat-room-message-delivery` on `1.152.11/x64`

- Date: 2026-09-14
- Classification: matched live baseline
- Public observation: two clean official-only trials completed public listener arming, user1 initiation followed by user2 one-to-one room resolution, two-member self/peer room validation, one send terminal per direction, and one matching callback-local self and other chat-message relation per host. The first trial included batching/cardinality variation and the self/other local order differed again in the second trial.
- Official normalized result: symbolic room, peer, directional send, callback-local chat type, and token-derived payload/size relations succeeded. Self echoes were present, while callback cardinality/batching and local self/other order were not stable.
- UniverseLAN normalized result: the focused four-host contract matched every strict symbolic relation after the server stopped publishing a newly created room before both members were added.
- Reproduction command/test name: `--characterize-official-gog-bidirectional-chat-room-message-delivery`; `universelan-behaviour-simple-bidirectional-chat-room-message-delivery-x64-1.152.11`; portable `RunBehaviorCTest.cmake` with `BEHAVIOUR_TEST_LABEL="^bidirectional-chat-room-message-delivery$"`.
- Follow-up: callback cardinality, self-echo presence, batching, self/other order, and token-mismatched prior-room messages remain sanitized same-host diagnostics only. Prior messages are read only in their callback and never satisfy the fresh directional token relation. The focused strict test and full 16-test portable behavior suite passed. No cross-host/global send/receive order, raw room deletion, raw ID, room ID, message ID, token, payload, length, timestamp, control, relay, runtime output, or artifact path is recorded.

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
- Follow-up: all four hosts acknowledged cleanup and the successful private root was removed. Add a candidate entry if a later live comparison mismatches; never copy the public collision-marker value or artifacts here.

### `Simple/public-lobby-string-filtering` on `1.152.11/x64`

- Date: 2026-09-14
- Classification: matched live baseline with declared intentional UniverseLAN relaxed-filter policy
- Public observation: official characterization created two temporary public capacity-two FCM lobbies sequentially while nonjoinable, configured distinct opaque marker-derived values under one fixed public key, then explicitly made both joinable. User2's equality-filtered list established symbolic target appearance, predicate match, selected target, and unmatched-candidate exclusion; user2 joined only that target, observed public two-member/non-self-owner state, then left; user1 acknowledged both cleanup leaves.
- Official normalized result: stable official GOG requires the symbolic unmatched candidate to be absent after every candidate is privately classified. Retry remains diagnostic only, not a cross-lane equality fact.
- UniverseLAN normalized result: this characterization also excluded the unmatched candidate, so the exact two-lobby variant did not exercise the permitted relaxed superset. The comparator nevertheless intentionally accepts that symbolic UniverseLAN-only superset while requiring target appearance, predicate match, selected join, membership, and lifecycle cleanup. It never accepts a malformed filter or an unmatched candidate being selected or joined.
- Reproduction command/test name: `--characterize-public-lobby-string-filtering`; `universelan-behaviour-simple-public-lobby-string-filtering-x64-1.152.11`; portable `RunBehaviorCTest.cmake` with `BEHAVIOUR_TEST_LABEL="^public-lobby-string-filtering$"`.
- Follow-up: no raw ID, lobby ID, fixed-key string, filter value, candidate count, index, timestamp, control, runtime output, or artifact path is retained. `GetLobbyByIndex` remains callback-local. The policy is narrow to this equality-filter scenario: official stable exclusion is strict, while only UniverseLAN's symbolic unmatched-candidate presence/exclusion is diagnostic.

### `Simple/public-lobby-data-propagation` on `1.152.11/x64`

- Date: not recorded in the existing live-baseline register
- Classification: matched live baseline
- Public observation: after post-join observer arming, owner lobby-data update succeeded; the joined-lobby listener received the update with invalid symbolic member ID and public copied-value visibility in the callback and after bounded pumping.
- Official normalized result: matched UniverseLAN for required create/list/join, data-update, callback-validity, copied-value, and joiner-first cleanup facts.
- UniverseLAN normalized result: matched official GOG for the same required facts.
- Reproduction command/test name: `universelan-behaviour-simple-public-lobby-data-propagation-x64-1.152.11`.
- Follow-up: list convergence, callback multiplicity, and callback-gate discovery order remain diagnostic only. The comparison matched and cleanup was acknowledged by all four hosts; no candidate difference was recorded.
