# API — fresh baseline review notebook

## Executive summary

Baseline: **`b30e83872c0006e8240c8b4f565da5351bf10080`**. Reviewed independently from implementation and SDK contracts; no superseded review consulted. The checked-out HEAD is the planned incorporating merge, `40265aed370464569e873692ef5d53fbdb12679b`. Read-only Git comparisons found no differences in the assigned inputs or the implementation/SDK/vendor context paths listed under execution checks below.

**Assigned coverage complete: 10/10 files, 4,614 source lines read in full; 10 new sidecars created.** Seventeen confirmed static defects: **2 High, 14 Medium, 1 Low; no Critical**. One additional **Informational** investigation, BASE-API-018, is not counted as a confirmed supported-path defect. Confirmed categories: Correctness 8, API/ABI 6, Concurrency 2, Memory Safety 1. All confirmed findings have High confidence in the static evidence; none is represented as runtime-reproduced.

The strongest risks are Friends Copy APIs that can read freed string storage and WebSocket operation callbacks that survive documented listener cancellation. Other findings concern chat response correlation, search filters, refresh/rollback/session state, P2P listener queue identity and callback-visible WebSocket lifetime. Existing locking, owned packet snapshots and version-aware signatures provide useful foundations, but this subsystem is not ready for a correctness sign-off until those paths receive fixes and focused validation.

## Assigned coverage and reports

All paths below were read from beginning to end, including feature branches. Each new report contains file-specific inspection notes. Detailed findings are locally contained in the owning sidecar rather than depending on this index.

| Reviewed path | Lines | Report / findings |
| --- | ---: | --- |
| `Source/Client/Impl/Chat.cxx` | 400 | [Chat.cxx.review.MD](../../Source/Client/Impl/Chat.cxx.review.MD): BASE-API-001 |
| `Source/Client/Impl/Chat.hxx` | 198 | [Chat.hxx.review.MD](../../Source/Client/Impl/Chat.hxx.review.MD): BASE-API-018 investigation |
| `Source/Client/Impl/Friends.cxx` | 699 | [Friends.cxx.review.MD](../../Source/Client/Impl/Friends.cxx.review.MD): BASE-API-002–005 |
| `Source/Client/Impl/Friends.hxx` | 644 | [Friends.hxx.review.MD](../../Source/Client/Impl/Friends.hxx.review.MD): declarations/ownership/contracts; no independent added defect |
| `Source/Client/Impl/Matchmaking.cxx` | 1,159 | [Matchmaking.cxx.review.MD](../../Source/Client/Impl/Matchmaking.cxx.review.MD): BASE-API-006–012 |
| `Source/Client/Impl/Matchmaking.hxx` | 638 | [Matchmaking.hxx.review.MD](../../Source/Client/Impl/Matchmaking.hxx.review.MD): filter/cache/ABI contracts; no independent added defect |
| `Source/Client/Impl/Networking.cxx` | 170 | [Networking.cxx.review.MD](../../Source/Client/Impl/Networking.cxx.review.MD): BASE-API-013–014 |
| `Source/Client/Impl/Networking.hxx` | 245 | [Networking.hxx.review.MD](../../Source/Client/Impl/Networking.hxx.review.MD): channel bounds, ownership and listener contract; no independent added defect |
| `Source/Client/Impl/CustomNetworking.cxx` | 295 | [CustomNetworking.cxx.review.MD](../../Source/Client/Impl/CustomNetworking.cxx.review.MD): BASE-API-015–017 |
| `Source/Client/Impl/CustomNetworking.hxx` | 166 | [CustomNetworking.hxx.review.MD](../../Source/Client/Impl/CustomNetworking.hxx.review.MD): Channel ownership/lifecycle and SDK surface; no independent added defect |

No assigned file has incomplete read coverage. Header observations without an independent defect are scoped findings of inspection, not proof of correctness.

## Finding index

| ID | Severity | Category | Finding / owning sidecar |
| --- | --- | --- | --- |
| BASE-API-002 | High | Concurrency | Friends persona/presence Copy getters do not protect string copying; `Friends.cxx.review.MD` |
| BASE-API-015 | High | Memory Safety | WebSocket operation listener pointers remain callable after Unregister/destruction; `CustomNetworking.cxx.review.MD` |
| BASE-API-001 | Medium | Correctness | Live chat fan-out can complete an unrelated history request; `Chat.cxx.review.MD` |
| BASE-API-003 | Medium | API/ABI | IsFriend contradicts successful friend-list enumeration; `Friends.cxx.review.MD` |
| BASE-API-004 | Medium | Correctness | Null rich-presence values create empty keys instead of removing them; `Friends.cxx.review.MD` |
| BASE-API-005 | Medium | API/ABI | Friend-list / existing-lobby-member persona retrieval is not automatic; `Friends.cxx.review.MD` |
| BASE-API-006 | Medium | Correctness | Near-value lobby filter is a no-op; `Matchmaking.cxx.review.MD` |
| BASE-API-007 | Medium | API/ABI | Legacy list requests include full lobbies; `Matchmaking.cxx.review.MD` |
| BASE-API-008 | Medium | API/ABI | Friends-only lobbies appear in discovery results; `Matchmaking.cxx.review.MD` |
| BASE-API-009 | Medium | Correctness | Lobby refresh omits structural fields on existing entries; `Matchmaking.cxx.review.MD` |
| BASE-API-010 | Medium | Correctness | Rejected structural setters retain optimistic cache changes; `Matchmaking.cxx.review.MD` |
| BASE-API-011 | Medium | API/ABI | Invalid-lobby Copy calls leave stale output instead of an empty string; `Matchmaking.cxx.review.MD` |
| BASE-API-012 | Medium | Correctness | Joined session state survives connection loss/reconnect; `Matchmaking.cxx.review.MD` |
| BASE-API-013 | Medium | Correctness | Activating P2P listeners with a backlog mismatches announced packet and Peek data; `Networking.cxx.review.MD` |
| BASE-API-016 | Medium | Correctness | WebSocket channel publication/cleanup outruns queued notifications; `CustomNetworking.cxx.review.MD` |
| BASE-API-017 | Medium | Concurrency | Local and worker close paths race on close-listener state; `CustomNetworking.cxx.review.MD` |
| BASE-API-014 | Low | API/ABI | Ordinary/immediate P2P sends lack the documented scheduling distinction; `Networking.cxx.review.MD` |
| BASE-API-018 | Informational, unconfirmed contract reachability | Memory Safety | Nested chat dispatch does not restore the borrowed message view; `Chat.hxx.review.MD` |

## Architecture and contract tracing

### Runtime map

1. Version-selected Galaxy interfaces call the five implementations. Feature macros adapt signatures and listener availability; public SDK headers, not implementation comments alone, define expected observable behavior.
2. Chat/Friends/Matchmaking/Networking serialize Shared message objects into `GalaxyNetworkClient::SendAsync`. A background Client tick services ENet. API `ProcessData` drains received events into `ClientNetworkHandlers`, which updates local caches and normally invokes synchronous completion listeners. Deferred `NotifyAll` events run afterward through DelayRunner.
3. The Server is authoritative for lobby membership and properties and owns chat rooms. Shared snapshots are serialized values, not cross-process shared objects. The client retains additional derived maps: all-known lobbies, filtered results and joined lobbies. These need explicit snapshot, rollback and session-loss policies; a successful response alone does not ensure all cached fields are coherent.
4. P2P messages retain the public uint8 channel in the wire object; the API uses independent owned queues for all 256 values. Listener mode requires the announced packet, callback Peek view and automatic removal to describe the same packet.
5. CustomNetworking bypasses the LAN Server and owns one IXWebSocket worker per Channel. It concatenates received bytes into a protected deque and posts SDK notifications to DelayRunner. Worker lifetime, registry lifetime, incoming-data lifetime and listener cancellation are separate obligations; the current atomic cleanup flag only covers one of them.

### Dependencies actually inspected

These are contract/caller context, not additional owned whole-subsystem review targets. Full reads are distinguished from selected ranges/symbol searches.

**Full context reads:**

- `Source/Server/ServerHandlers.cxx` (including complete lobby/chat/P2P/user-data/rich-presence handlers and disconnect processing).
- `Source/Client/ClientNetworkHandlers.cxx`, `Source/Client/Client.cxx`, `Source/Client/UniverseLAN.cxx`, `Source/Client/UniverseGameServer.cxx`.
- `Source/Client/Impl/ListenerRegistrar.cxx`, `Source/Client/Impl/ListenerRegistrar.hxx`.
- `Source/Client_NoVer/Impl/NotificationParamScopeExtender.hxx`, `Source/Client_NoVer/Impl/DelayRunner.cxx`.
- `Source/Shared/Lobby.cxx`, `Source/Shared/Lobby.hxx`, `Source/Shared/LobbyManager.cxx`, `Source/Shared/LobbyManager.hxx`.
- `Source/Shared/ChatRoom.cxx`, `Source/Shared/ChatRoom.hxx`, `Source/Shared/ChatRoomManager.cxx`, `Source/Shared/ChatMessage.cxx`, `Source/Shared/ChatMessage.hxx`.
- `Source/Shared/GalaxyUserData.cxx`, `Source/Shared/GalaxyUserData.hxx`.
- `Source/Shared/Networking/Networking.cxx`, `Source/Shared/Networking/Networking.hxx`.
- `Source/Shared/Networking/Messages/P2PNetworkPacketMessage.hxx`.
- `Source/Shared/Networking/Messages/RequestChatRoomMessagesMessage.hxx`, `Source/Shared/Networking/Messages/RequestChatRoomWithUserMessage.hxx`, `Source/Shared/Networking/Messages/SendToChatRoomMessage.hxx`.
- `Source/Shared/Networking/Messages/RequestSpecificUserDataMessage.hxx`.
- `Source/Shared/Networking/Messages/JoinLobbyMessage.hxx`, `Source/Shared/Networking/Messages/LeaveLobbyMessage.hxx`, `Source/Shared/Networking/Messages/RequestLobbyDataMessage.hxx`, `Source/Shared/Networking/Messages/RequestLobbyListMessage.hxx`.
- `Source/Shared/Networking/Messages/SetLobbyJoinableMessage.hxx`, `Source/Shared/Networking/Messages/SetLobbyMaxMembersMessage.hxx`, `Source/Shared/Networking/Messages/SetLobbyTypeMessage.hxx`.
- `Source/Shared_NoVer/AchievementsAndStatsContainer.hxx`, `Source/Shared_NoVer/SafeStringCopy.hxx`, `Source/Shared_NoVer/Networking/MessageUniqueID.cxx`, `Source/Shared_NoVer/Networking/MessageUniqueID.hxx`.
- `Source/DLLs/1.152.11/galaxy/IChat.h`, `Source/DLLs/1.152.11/galaxy/IMatchmaking.h`, `Source/DLLs/1.152.11/galaxy/INetworking.h`, `Source/DLLs/1.152.11/galaxy/ICustomNetworking.h`.
- `Source/SystemTests/Host/CustomNetworking.cxx` (context only).

**Selected context reads/searches:**

- `Source/Client/GalaxyDLL.cxx:115-190`: public interface lookup and pump.
- `Source/Client/Impl/User.cxx:288-330,440-673`: user-data publication, shared cache lookup and connection-state processing.
- `Source/Shared_NoVer/AchievementsAndStatsContainer.cxx:110-172`: reference-returning accessors, presence mutation/erasure and lock scopes.
- `Source/Shared/IniData.hxx` / `Source/Shared/IniData.cxx`: symbol lookup establishing `GetCustomPersonaName` returns a const reference; no config/credential data files read.
- `Source/DLLs/1.152.11/galaxy/IFriends.h:620-1034` plus callback/change-flag searches.
- `Source/DLLs/1.152.11/galaxy/IListenerRegistrar.h:132-242`: cancellation and self-registration.
- `Source/DLLs/1.152.11/galaxy/GalaxyApi.h:298-327,440-474`: general thread safety and ProcessData.
- `Source/DLLs/1.57.0/galaxy/IMatchmaking.h:294-356` and enum/search results: legacy filters/fullness.
- `Source/DLLs/1.124.0/galaxy/GalaxyApi.h:152-200`: legacy ServerNetworking routing.
- `Source/galaxy_sdk_features.cmake:38-114,170-257` and feature searches: version gates relevant to this assignment.
- `Source/Vendor/IXWebSocket-12.0.1/ixwebsocket/IXWebSocket.cpp:175-464` and lifecycle symbol search: worker start/join, connection and dispatch contracts. Vendor source used only as dependency context.
- `Source/SystemTests/Host/Chat.cxx:83-205`, `Source/SystemTests/Host/Friends.cxx:100-202`; targeted searches of `Source/SystemTests/Host/P2P.cxx` and `Source/SystemTests/Host/Lobby.cxx`.

No coverage claim is made for unread portions of these contextual files. The assigned ten files are the only first-party source paths counted as completed ownership for this task.

### Cross-owner remediation dependencies

- BASE-API-001 needs coordinated Shared wire/Server fan-out changes or an equivalently unambiguous reply/event design.
- BASE-API-002 needs synchronization shared with User and Shared user-data writers, not a getter-only lock.
- BASE-API-005 needs Friends, Matchmaking and hello-data dispatch agreement about persona availability and notifications.
- BASE-API-010 needs a consistent client optimistic-update policy and the Server's currently unused rollback callback addressed.
- BASE-API-012 needs CORE disconnect dispatch to invoke API session-loss handling; reconnecting ENet alone cannot restore membership.
- BASE-API-015–017 should be resolved together around cancellation-aware event tokens, channel state, registry publication and dispatch-bound cleanup. Adding a mutex to a raw listener pointer alone is insufficient.

## Execution and evidence checks

Instructions read: `.ai/review-baseline/PLAN.MD`, `.ai/SKILLS/CppReviewer.md`, `.ai/ai-instructions-review.txt`. The present assignment's restrictions governed this review; no older branch/setup/credential suggestions were acted upon. Repository AGENTS filename search returned no matches.

Read-only Git commands actually executed from `C:\Development\AI\UL`:

```text
git rev-parse HEAD
git diff b30e83872c0006e8240c8b4f565da5351bf10080 -- Source/Client/Impl/Chat.cxx Source/Client/Impl/Chat.hxx Source/Client/Impl/Friends.cxx Source/Client/Impl/Friends.hxx Source/Client/Impl/Matchmaking.cxx Source/Client/Impl/Matchmaking.hxx Source/Client/Impl/Networking.cxx Source/Client/Impl/Networking.hxx Source/Client/Impl/CustomNetworking.cxx Source/Client/Impl/CustomNetworking.hxx
git diff --quiet b30e83872c0006e8240c8b4f565da5351bf10080 -- Source/Client Source/Shared Source/Shared_NoVer Source/Client_NoVer Source/Server Source/galaxy_sdk_features.cmake
git diff --quiet b30e83872c0006e8240c8b4f565da5351bf10080 -- Source/DLLs/1.152.11/galaxy Source/DLLs/1.57.0/galaxy/IMatchmaking.h Source/DLLs/1.124.0/galaxy/GalaxyApi.h Source/Vendor/IXWebSocket-12.0.1/ixwebsocket/IXWebSocket.cpp
```

Results: HEAD matched the plan; assigned-file diff was empty; both broader quiet comparisons returned 0. Read/Glob/Grep tools provided source and contract evidence. A metadata search over only the newly written owned sidecars checked baseline markers, IDs, severity and verification sections. All writes used `apply_patch` and consist of the ten sidecars plus this notebook. No production edits, builds, runtime tests, sanitizer/analyzer execution, Git mutations, credential reads or external network probes were performed.

Final read-only validation also ran `git status --short --untracked-files=all` restricted to the eleven output paths, repeated the assigned-source comparison with `git diff --quiet` (result 0), and counted report headings with `rg --count --glob '{Chat,Friends,Matchmaking,Networking,CustomNetworking}.{cxx,hxx}.review.MD' '^### \[BASE-API-' Source/Client/Impl`. The heading counts were 1 Chat implementation + 1 Chat header investigation + 4 Friends + 7 Matchmaking + 2 Networking + 3 CustomNetworking = 18 entries. Status showed all eleven new reports as untracked alongside the index's staged deletions of the superseded ten sidecars, consistent with the baseline reset; this review did not alter the index.

## Testing, platform and assessment limits

- **Static review completed; dynamic validation incomplete by task constraint.** All verification scenarios in the sidecars are proposed tests, not test results.
- Existing SystemTests context includes orderly WebSocket echo/close, explicit persona retrieval/rich-presence propagation, chat live/history retrieval, polling P2P/channel 255 and a string lobby filter. This was selective context inspection, not an exhaustive test-suite coverage audit, and no existing test pass was assumed.
- Windows is the runtime/data-model focus. No Linux build or runtime claim, no complete x86/x64 binary ABI check, and no all-SDK feature-matrix compilation. Build manifests/CI are owned elsewhere and are not certified here.
- Nested ProcessData support was not established. The chat borrowed-view interleaving is explicitly BASE-API-018 informational; out-of-callback getter misuse was excluded from confirmed defect counts.
- SDK proximity tie-breaking, multi-near priority and malformed numeric-filter behavior remain open. No undocumented policy was invented. Unsupported avatars/overlay/persistent GOG services and intentional LAN trust are not classified as vulnerabilities merely because they differ from hosted GOG.
- No load/latency or unbounded-buffer resource measurements were taken. No exploitability conclusion is made for ordinary trusted-LAN peers.

## Positive practices and next steps

Owned shared packets survive queue removal; the full uint8 channel range is allocated; binary lobby message copying obeys byte-count semantics; list filter snapshots are request-scoped; joins use Server snapshots before callbacks; chat history insertion deduplicates message IDs; deferred constant string arguments are copied; normal WebSocket teardown joins workers before destroying Channel state.

Recommended order: (1) repair BASE-API-002 and BASE-API-015, coordinating all writers/cancellation paths; (2) unify WebSocket lifecycle state and lobby snapshot/rollback/session transitions; (3) repair chat request correlation and P2P callback packet identity; (4) close the filter, friend/presence and output-contract gaps with focused Windows regression cases. Establish nested-pump expectations before promoting BASE-API-018 beyond an investigation. No assigned source coverage remains incomplete; execution and exhaustive version validation remain outstanding.
