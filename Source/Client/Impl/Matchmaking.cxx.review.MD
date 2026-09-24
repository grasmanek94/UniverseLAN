# Matchmaking.cxx — fresh baseline review

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. All 1,159 lines read. Windows-focused static review; no build/test execution.

## File-specific inspection

Reviewed all create/list/filter/join/leave paths, local and server-driven mutations, public/member property enumeration and copying, lobby messages, membership and ownership changes. Traced `ServerHandlers.cxx:513-905`, Shared `Lobby`/`LobbyManager` and serialized requests, client event dispatch, notification registration, SDK `1.152.11/galaxy/IMatchmaking.h`, legacy `1.57.0` list contracts, and feature definitions.

Positive observations: list filters are copied per request ID and consumed once, so overlapping requests do not simply share the current filter vector. Result limiting is applied to accepted entries. Explicit nonjoinability is excluded from discovery. A successful join adopts the server snapshot before callbacks, and duplicate self-insertion does not clear member data. Create callbacks publish the cached lobby before announcing creation/entry. Normal leave and server closure remove the joined/list/filtered entries. Lobby-message copying uses the binary-copy helper and reports bytes written, consistent with its SDK contract.

`lobby_list`, `lobby_list_filtered` and `joined_lobbies` can hold different snapshot objects after a list refresh. In current code the joined map is primarily a membership/send gate; divergence alone was not counted as a separate defect without a demonstrated consumer. Numeric parsing is permissive (`stol`, fallback zero); precise SDK handling of malformed/missing numerical properties was not established, so no additional parsing finding was invented. SDK documentation does not settle proximity tie-breaking or multiple-near-filter precedence. Existing-member automatic persona refresh is documented in BASE-API-005 in `Friends.cxx.review.MD`.

## Findings

### [BASE-API-006] Near-value filters have no effect in supported SDK builds

- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Client/Impl/Matchmaking.cxx:198-201,303-307`; result construction `231-259`.
- **Affected scope:** `AddRequestLobbyListNearValueFilter` across currently supported versions.

**Evidence.** The method only records a filter under `GALAXY_BUILD_FEATURE_NEAR_FILTER_ENUM`. `Source/galaxy_sdk_features.cmake:249` enables that feature starting at the placeholder version `9.999.0`. Even if enabled, `ShouldFilterOut`'s NEAR case does nothing. Results are stored in `LobbyManager::lobbies_t`, an unordered map (`Shared/LobbyManager.hxx:17-18`). SDK `1.152.11/galaxy/IMatchmaking.h:536-546` and `1.57.0/galaxy/IMatchmaking.h:340-350` expose and describe the near-value filter independently of an enum constant.

**Failure mechanism.** Calling the public near-filter method returns without recording its key or target. The next list request uses the same unordered iteration and count limiting as if the filter had never been called. Enabling the guard alone cannot supply proximity ordering because neither comparison nor ordered result storage implements it.

**Impact.** Games selecting lobbies by nearby numeric properties receive unrelated results; a count limit can discard desirable candidates before proximity is considered.

**Alternatives / recommended resolution.** Represent proximity criteria separately from the SDK comparison enum. Collect qualifying candidates, implement the documented proximity behavior, and apply result limiting at the appropriate stage using an order-preserving result vector. An internal tagged filter is another option. Validate exact ordering, ties and combined-near semantics against the target SDK before committing that policy; the confirmed defect is complete absence of any effect, not a claimed undocumented ranking rule.

**Verification.** For each supported filter signature, use lobbies with widely separated numeric values and change the requested target; verify the retained/result ordering responds according to the established SDK behavior, including a small count limit, multiple filters and consumption on the following request. Not executed.

### [BASE-API-007] Legacy no-argument lobby searches include full lobbies

- **Severity:** Medium
- **Confidence:** High
- **Category:** API/ABI
- **Location:** `Source/Client/Impl/Matchmaking.cxx:97-110,244-250`.
- **Affected scope:** Versions before `HAS_REQUESTLOBBYLIST_ARGS_ALLOWFULL` (feature introduced at 1.82.0).

**Evidence.** In the no-argument branch, `RequestLobbyList` sets `lobby_list_filters.allow_full = true`. The response handler skips a full lobby only when that flag is false. SDK `Source/DLLs/1.57.0/galaxy/IMatchmaking.h:297-312` explicitly states full lobbies are never included and provides no override parameter. The feature boundary is `galaxy_sdk_features.cmake:78`; `Lobby::IsFull` compares actual members with capacity (`Shared/Lobby.cxx:125-130`).

**Failure mechanism.** With a full, joinable public lobby, the legacy call takes the forced-true branch and includes it in successful results. The Server sends the complete map and performs no compensating fullness filtering (`ServerHandlers.cxx:532-540`).

**Impact.** Legacy games present/select unusable sessions, then receive `LOBBY_IS_FULL` from JoinLobby. This can also crowd out usable lobbies under the result cap.

**Alternatives / recommended resolution.** Use false when the SDK has no allow-full argument. Retain the explicit argument for newer versions; their copied “never” remark conflicts with the documented override and is not a basis for removing that override.

**Verification.** With one full and one non-full public lobby, test the legacy signature excludes the full lobby. Test modern default/false excludes it and explicit true includes it. Not executed.

### [BASE-API-008] Discovery ignores the friends-only lobby visibility contract

- **Severity:** Medium
- **Confidence:** High
- **Category:** API/ABI
- **Location:** `Source/Client/Impl/Matchmaking.cxx:231-254`, `RequestLobbyListProcessed`.
- **Affected scope:** SDK versions exposing friends-only lobby types; ordinary LAN search results.

**Evidence.** SDK `Source/DLLs/1.152.11/galaxy/IMatchmaking.h:21-30` explicitly defines `LOBBY_TYPE_FRIENDS_ONLY` as “not in lobby list.” Filtering checks only maximum count, fullness, supplied property filters and joinability; it never checks `GetType()`. `ServerHandlers.cxx:532-540` returns `lobby_manager.GetLobbies()`, and `Shared/LobbyManager.cxx:28-30` returns the complete stored map. No layer removes friends-only lobbies.

**Failure mechanism.** Create a joinable, non-full friends-only lobby and issue an unfiltered search from another client. It passes every condition and is enumerated through `GetLobbyByIndex`, regardless of the explicit SDK exclusion.

**Impact.** Search UI exposes sessions intended for a different discovery route. This is a compatibility/visibility finding, not a claim of a security boundary in an intentionally trusted LAN deployment.

**Alternatives / recommended resolution.** Enforce the SDK's searchable type set before count limiting, with version guards. The Server may instead provide a discovery-only filtered response, but that requires a separate authoritative cache/update path. Prefer preserving existing full snapshot semantics while adding an explicit discovery predicate. Private-lobby authorization is a separate Server concern and is not assessed as an exploit here.

**Verification.** Create one lobby of every supported type with identical metadata and spare capacity. Verify a friends-only lobby is absent while public and explicitly searchable invisible-to-friends lobbies follow the SDK enum contracts. Confirm direct ID lookup remains separate. Not executed.

### [BASE-API-009] Successful lobby refresh does not refresh structural lobby state

- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Client/Impl/Matchmaking.cxx:735-759`, `RequestLobbyDataProcessed`.
- **Affected scope:** Existing cached entries, including partial entries created by broadcasts to nonmembers.

**Evidence.** For an existing entry, the handler copies only `GetAllData()` and `GetAllMemberData()`; it ignores the received owner, capacity, type and joinability. The Server response contains the entire `Lobby` (`ServerHandlers.cxx:613-630`); serialization includes all these structural fields (`Shared/Lobby.hxx:54-60`). SDK `IMatchmaking.h:597-605,638-670,672-684` explicitly directs nonmembers to RequestLobbyData before reading capacity/type/joinability.

**Failure mechanism.** A connected observer sees a setter broadcast for a newly created lobby it has not listed. The setter completion creates `Lobby(lobby_id)`, initially owner/capacity zero and default type (`Matchmaking.cxx:679-685`; `Shared/Lobby.cxx:24-26`). Its subsequent valid RequestLobbyData gets a full snapshot, but because an entry already exists, only properties/membership are copied. The success callback can still observe zero capacity and the wrong type. Similarly, a nonmember's cached owner can remain stale after ownership migration and explicit refresh.

**Impact.** Successful refresh fails to repair incomplete/stale lobby metadata, producing invalid lobby detail displays and decisions based on wrong structural state.

**Alternatives / recommended resolution.** Merge all authoritative snapshot fields under the matchmaking lock, preserving any client-only state deliberately. Alternatively replace the cached object and consistently rebind related maps. Prefer an explicit snapshot-application helper shared with join/list paths to document which data, especially messages, survives.

**Verification.** Make an observer learn a new lobby first through a joinability broadcast, then RequestLobbyData. In its success callback compare owner, capacity, type, joinability, members and properties with the Server snapshot. Repeat for ownership migration observed through explicit refresh. Not executed.

### [BASE-API-010] Rejected structural updates leave the optimistic value committed locally

- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Client/Impl/Matchmaking.cxx:436-503,552-618,635-699`.
- **Affected scope:** Capacity/type/joinability setters whose requests are rejected by the Server.

**Evidence.** Each setter changes the cached lobby before sending. Each processed handler writes the response's proposed field before checking `success`. `ServerHandlers.cxx:703-745` sets `success=false` and sends the original request on missing-lobby/nonowner failure; its `rollback_data` callback is never invoked. Callers provide rollback lambdas at `748-797`, but those lambdas therefore do not replace the proposed value with authoritative state. SDK `IMatchmaking.h:247-274` distinguishes success from failure, and structural getters report the lobby's actual properties.

**Failure mechanism.** An ordinary member attempts a structural change, or an outstanding update reaches the Server after the lobby is closed. The cache is optimistically changed. The failure response contains the same requested value and the client writes it again, then emits failure. There is no retained acknowledged value or invalidation to restore actual state. Merely moving the response assignment into the success branch leaves the initial optimistic mutation behind.

**Impact.** After an explicit failure, local type/capacity/joinability differs from the Server and other members, and nonexistent lobby entries may be retained. This is local cache corruption, not a Server authorization bypass.

**Alternatives / recommended resolution.** Prefer applying structural changes only after successful acknowledgement, or maintain separately versioned optimistic and acknowledged state. If immediate local visibility is required, provide authoritative rollback values for existing lobbies and invalidate missing ones; account for several in-flight updates so an older failure cannot roll back a newer success. Coordinate the Server helper correction with the client policy.

**Verification.** As a nonowner, request changes to each structural field and check that failure restores/preserves acknowledged values. Also close the lobby with an update in flight and exercise two outstanding updates with different results. Not executed.

### [BASE-API-011] Copy getters leave stale output for an unknown lobby

- **Severity:** Medium
- **Confidence:** High
- **Category:** API/ABI
- **Location:** `Source/Client/Impl/Matchmaking.cxx:782-793,927-938`.
- **Affected scope:** `GetLobbyDataCopy` and `GetLobbyMemberDataCopy` on SDKs providing Copy methods.

**Evidence.** Both methods return immediately when `lobby_list.find` fails, leaving the supplied buffer untouched. SDK `Source/DLLs/1.152.11/galaxy/IMatchmaking.h:702-715,798-814` expressly requires copying an empty string for invalid lobby IDs. This is a documented supported error-output contract, not an invented null-pointer expectation.

**Failure mechanism.** Reuse a buffer containing a previous property's value and call either Copy method for an unknown or just-left lobby. No bytes are written and there is no return status. The caller sees the old text as the current result. An uninitialized destination need not become null-terminated.

**Impact.** Stale UI/state and possible caller over-read if it relies on the required empty C string. The implementation performs no direct out-of-bounds write; severity reflects the output contract violation.

**Alternatives / recommended resolution.** Clear a nonempty valid destination on entry, or call `safe_copy_str_n("", buffer, bufferLength)` in each missing-lobby branch. The existing helper already handles zero capacity/null destinations. Prefer one shared lookup/copy routine to keep lobby and member behavior aligned.

**Verification.** Prefill outputs with nonempty sentinels and test unknown lobby, left lobby, missing property and nonmember IDs. Verify byte zero is null for a nonzero buffer, one-byte destinations work, and zero capacity changes nothing. Not executed.

### [BASE-API-012] Connection loss leaves joined-lobby state alive across reconnect

- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Client/Impl/Matchmaking.cxx:394-421,1065-1076`; state declarations `Matchmaking.hxx:82-88`.
- **Affected scope:** Existing interface instance losing and re-establishing the LAN Server connection.

**Evidence.** Cache removal handles only explicit user-left/lobby-closed reasons; the documented `LOBBY_LEAVE_REASON_CONNECTION_LOST` is omitted. More fundamentally, actual disconnect dispatch (`ClientNetworkHandlers.cxx:47-58`) calls Utils/User only. `User.cxx:624-671` updates operational state without resetting matchmaking. The Server removes the disconnected peer from its lobbies (`ServerHandlers.cxx:50-74,845-920`); reconnect hello transfers data but does not rejoin it (`132-173`). `joined_lobbies` survives until an explicit leave response or interface destruction and gates SendLobbyMessage. The SDK's loss reason and leave semantics are explicit (`IMatchmaking.h:184-205,575-586`).

**Failure mechanism.** Join L, lose the Server connection, then reconnect using the same initialized API instance. The Server has removed this peer; locally `joined_lobbies` still contains L and cached getters can still show the old membership. A list refresh can replace the general cache but leaves the joined map untouched. Sends pass the local membership gate and are dropped by the Server's actual membership check (`ServerHandlers.cxx:640-642`), while games waiting for a lobby-left transition are not told to recover.

**Impact.** Multiplayer state remains falsely joined after transport recovery; games can keep operating on a session they no longer belong to. Cached presence can also remain stale in Friends because it receives no disconnect-wide reset; that is a related integration limitation rather than a second counted root cause here.

**Alternatives / recommended resolution.** Add a session-loss transition that atomically invalidates joined state and relevant cached/pending data, then emits each lobby's loss notification after releasing locks. Wire it to client disconnect and handle a received connection-lost leave reason identically. A session generation can reject late old-session replies. Transparent rejoin is an alternative only with an explicit protocol and SDK-compatible callbacks, not by retaining old map entries.

**Verification.** Join two lobbies, disconnect without destroying interfaces, and pump the loss event. Verify each joined session exits once, cache/getter state is coherent during callbacks, and reconnect does not silently restore membership. Explicit rejoin must restore operation. Include a pending list/data request at loss. Not executed.

## Thorough follow-up addendum — 2026-09-24

All 1,159 implementation lines and 638 header lines reread, including every feature branch, before baseline comparison. Production input remains `b30e8387`. Original conclusions above are preserved; the corrections below are explicitly additive.

### [ADD-API-003] NEW — Deferred membership/ownership callbacks are overtaken by later lobby events

- **Severity:** Medium
- **Confidence:** High for the demonstrated dispatch order and state mismatch
- **Category:** Correctness
- **Location:** `Source/Client/Impl/Matchmaking.cxx:1112-1157` versus synchronous notifications at `970-996,1079-1096,394-432`.
- **Affected scope:** Normally ordered lobby events accumulated between two API pumps; one application thread, valid membership, no recursive pump required. Applies to the old and modern callback signatures.

**Evidence.** `LobbyMemberStateChange` and `LobbyOwnerChange` change the cache immediately but call deferred `NotifyAll`. Member data, lobby messages, leave completion, creation and entry generally use `NotifyAllNow`. `GalaxyDLL.cxx:166-173` drains all Client events before running DelayRunner; `Shared/Networking/Networking.cxx:219-227` does not flush deferred callbacks between those events. The server emits entry before later member traffic (`ServerHandlers.cxx:577-592,633-656,800-842`) and emits migration/member departure in order (`880-897`). SDK `GalaxyApi.h:458-468` describes notifications when events are recognized; `IMatchmaking.h:356-404,419-429,563-579` defines the related transition and message events. This is an inversion introduced after receiving ordered events, not a claim that unrelated network channels must have a global order.

**Failure mechanism.** B joins a lobby owned by A and, after B's successful entry, sends a lobby message or updates member data. A pauses its application pump long enough for both reliable events to queue. A's next pump adds B, queues B's ENTERED callback, then invokes B's data/message callback synchronously. The application sees B's traffic before its member-added notification. If a later leave/close is in the same batch, A's state can already have removed B or the lobby when the earlier ENTERED callback finally runs. Similarly, a migration callback can arrive after later notifications observing the new owner. The callbacks' value arguments are owned; the problem is semantic ordering and callback-visible state, not dangling event strings.

**Impact.** Games that create per-member state on ENTERED can discard early traffic or fail peer lookup. State-transition callbacks can expose a later cache state rather than the state just announced. The existing SystemTests inspect membership inside callbacks but gate later actions until the earlier callback has been observed, avoiding this interleaving (`SystemTests/Host/Lobby.cxx:352-416`).

**Alternatives.** Notify membership/ownership synchronously after releasing the matchmaking lock, matching the other processed-event paths; or enqueue complete state-application-plus-notification events into a single ordered application dispatcher. Moving only callbacks to a shared queue while eagerly applying every later cache mutation does not by itself preserve callback-visible state.

**Recommended fix.** Preserve receive-event order for both cache application and associated notifications. Prefer the existing synchronous processed-event convention outside the cache lock, including automatic persona-request scheduling that cannot overtake the member event. Retain the SDK's immediate created-then-entered sequence.

**Verification.** Accumulate ENTERED then member-data then lobby-message events before one owner pump, and assert the application member-added callback precedes traffic. Repeat entry/exit in one batch, migration followed by data, and traffic in a second joined lobby to ensure one lobby's leave does not invalidate the other. All getters must be called within their SDK preconditions. Existing membership-gated tests should remain valid. Not executed.

### Corrections / additions to existing BASE IDs — no duplicate accounting

- **BASE-API-006 retained (Medium):** near filtering is compiled out on supported versions. In-range numerical and string predicates remain cumulative AND checks; no earlier false result is reset by a later filter. The result cap counts accepted entries, so ordinary reject predicates are not accidentally applied after the cap. Multiple-near priority, tie rules, malformed-number handling and same-key replacement precedence remain unestablished by the inspected SDK; no additional filter ID is warranted. On Windows, `stol` has a 32-bit `long`, so an LP64-only narrowing example is not evidence for this review.
- **BASE-API-007 retained (Medium):** pre-1.82 forced `allow_full=true` violates the older no-argument contract. The modern explicit `true` argument overrides the stale copied “never full” remark.
- **BASE-API-008 expanded (Medium):** the same missing lobby-type discovery predicate also exposes private lobbies in legacy 1.57.0, whose actual SDK `IMatchmaking.h:276-295` explicitly says private lobbies are omitted from RequestLobbyList. This is additional version-specific compatibility evidence under the same ID, not a new privacy/security root cause. Modern friends-only exclusion remains independently explicit.
- **BASE-API-009 retained with a supported-input correction (Medium):** owner/capacity/type/joinability really are omitted when refreshing an existing object. However, the earlier proposed nonmember owner assertion is not a sound supported-path oracle: modern `IMatchmaking.h:879-887` says the owner return is valid only when called by a member, despite the adjacent refresh precondition. Validate capacity/type/joinability from the nonmember partial-cache case and owner only from a valid member context. This does not remove the demonstrated structural-refresh defect.
- **BASE-API-010 retained (Medium):** the Server helper's `rollback_data` callable really is unused. Existing-lobby data-property rejection does return the current property (`ServerHandlers.cxx:678-685`), so do not generalize the structural rollback claim to every setter. Prefer an owner request losing ownership before server processing when testing rejection; that avoids relying on a method's forbidden nonowner use where an SDK imposes ownership.
- **BASE-API-011 retained (Medium):** the empty-output requirement for an invalid lobby is explicit; this remains a supported error-output defect, unlike arbitrary null-key input.
- **BASE-API-012 retained (Medium):** multi-lobby joins are implemented on both sides (`ServerHandlers.cxx:550`), and ordinary leave erases only the selected lobby in the client. Disconnect still has no API cache-loss transition. Do not manufacture an independent “list refresh always loses joined data/messages” defect: the Server returns all extant lobbies, Shared serialization includes messages, and the joined map's other pointer identity is currently only used for the send/leave gate. Filtering belongs in the discovery result, not in the all-known cache.
- **Invalidation counterevidence:** on a new `JoinLobbyProcessed` insertion the iterator is refound before reuse; assignment of an already existing unordered-map element does not insert/rehash; insertion into `joined_lobbies` cannot invalidate an iterator in `lobby_list`. The full source trace does not support an iterator-use-after-rehash finding here.
