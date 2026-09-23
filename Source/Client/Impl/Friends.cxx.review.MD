# Friends.cxx — fresh baseline review

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. All 699 lines read. Windows-focused static review; no execution of builds/tests.

## File-specific inspection

Reviewed persona availability and refresh, pointer/copy getters, online-peer friend enumeration, invitation stubs and delivery, rich-presence mutation/retrieval/enumeration, local-user branches, callbacks and guards. Traced `UserImpl::GetGalaxyUserData`, server hello/user-data/rich-presence handlers, shared user data, `AchievementsAndStatsContainer`, string-copy helpers, and delayed notification capture. SDK context is `Source/DLLs/1.152.11/galaxy/IFriends.h:620-1028` plus general thread safety in `GalaxyApi.h:310-314`.

`GetPersonaName` returns a pointer into a reference-returning config accessor, not a temporary string. Likewise, the presence getter returns a container-backed reference. Their explicitly non-thread-safe pointer contracts are not independently reported as defects. `NotifyAll` copies `const char*` invitation arguments through `NotificationParamScopeExtender`, so a temporary caller connection string is not itself a delayed string use-after-free. Indexed rich-presence copies hold the container lock through copying. Avatar/overlay/friend-invitation service stubs were noted as unsupported functionality, without treating missing GOG services or the LAN-peer friendship model as security defects.

## Findings

### [BASE-API-002] Thread-safe copy getters read mutable strings without protecting the copy

- **Severity:** High
- **Confidence:** High
- **Category:** Concurrency
- **Location:** `Source/Client/Impl/Friends.cxx:147-154,477-485`; writers at `76-83,418-431,524-529`.
- **Affected scope:** `GetFriendPersonaNameCopy`, `GetRichPresenceCopy`, concurrent application API calls / event processing on Windows.

**Evidence.** Persona copy reads `GalaxyUserData::nickname` with no string-level lock. Its response handlers assign the same string without one. `User.cxx:578-591` protects only map lookup, then returns a shared pointer to the mutable object. Presence copy constructs a `std::string` from `stats.GetRichPresence(key)`. The latter returns `const std::string&` after its `run_locked_richpresence` callback has returned (`Shared_NoVer/AchievementsAndStatsContainer.cxx:138-169`); the lock is released before the caller copies. SDK `IFriends.h:703-724,958-981` explicitly contrasts these Copy methods with unsafe pointer getters; `GalaxyApi.h:310-314` states general API thread safety.

**Failure mechanism.** Thread A obtains the presence reference and exits the container lock. Thread B calls `DeleteRichPresence`/`ClearRichPresence`, destroying the referenced string, or replaces its allocation through a set/update. A then copies a destroyed or concurrently modified string. For persona, a response processed on B replaces a long nickname while A is copying it. Owning the `GalaxyUserData` object does not keep erased map elements or replaced string storage alive.

**Impact.** Data races, torn strings, and heap use-after-free in APIs explicitly intended for threaded callers. This is stronger than a stale snapshot issue.

**Alternatives / recommended resolution.** Copy presence data inside `run_locked_richpresence`, as the indexed Copy path already does, or add a value-returning snapshot accessor whose copy occurs under the lock. Protect nickname and associated availability state with a shared per-user synchronization policy covering all writers, including `UserImpl`; a private lock used only by this getter is insufficient. Preserve the documented distinction between pointer and Copy APIs.

**Verification.** With a retrieved local/remote entry, repeatedly copy long strings while another thread sets, erases, clears and processes refresh responses. Force the presence interleaving at the accessor-return boundary and verify no dangling read. Use Windows ASan for lifetime failures and synchronization-aware instrumentation for races. Not executed.

### [BASE-API-003] IsFriend rejects every user exposed by the friend list

- **Severity:** Medium
- **Confidence:** High
- **Category:** API/ABI
- **Location:** `Source/Client/Impl/Friends.cxx:209-246,665-685`.
- **Affected scope:** SDK versions with `IsFriend` and friend-list APIs.

**Evidence.** `RequestFriendList` reports success; `GetFriendCount` and `GetFriendByIndex` enumerate `reachable_peers`. `ChangeOnlineStatus` populates that set and announces friend additions. `IsFriend` nevertheless unconditionally returns false. SDK `IFriends.h:797-833` defines the enumeration and predicate in terms of the same friend list, with the same request prerequisite.

**Failure mechanism.** After another LAN peer comes online, request the list, enumerate a valid peer ID in the success callback, then ask `IsFriend` for that exact ID. Enumeration says it is a friend while the predicate says it is not.

**Impact.** Games that check membership before enabling invites, friend-only UI or social actions reject peers that the emulator itself advertised. This is an internal contract inconsistency, not an objection to representing LAN peers as friends.

**Alternatives / recommended resolution.** Use the existing locked peer set in `IsFriend`, or deliberately provide a separate coherent friend relation across all list/predicate callbacks. Prefer the former for the current LAN model.

**Verification.** Request a list with one reachable peer, verify `IsFriend(GetFriendByIndex(0))`, then process its departure and verify false and a matching count. Include an unknown ID. Not executed.

### [BASE-API-004] Null rich-presence values create empty entries instead of deleting them

- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Client/Impl/Friends.cxx:342-360`, `SetRichPresence`.
- **Affected scope:** Local and remotely propagated rich-presence state.

**Evidence.** SDK `IFriends.h:904-924` explicitly specifies “Passing NULL value removes the entry.” The implementation normalizes null to `""`, calls the container setter, and sends `ACTION_SET`. `SafeStringCopy.hxx:73-78` confirms that normalization; `AchievementsAndStatsContainer.cxx:148-169` inserts/assigns even an empty string and only erases through a distinct operation. `ServerHandlers.cxx:923-956` faithfully applies and broadcasts the selected action.

**Failure mechanism.** Set an entry, then call `SetRichPresence(key, nullptr)`. Local, server and peer containers retain the key with an empty value. On an absent key this deletion request actually adds a key.

**Impact.** Presence counts and enumeration disagree with the SDK removal contract, and absence-sensitive UI/game state remains published despite successful completion.

**Alternatives / recommended resolution.** Detect null before normalization and route to the existing `DeleteRichPresence` path, preserving its listener and single completion. Alternatively encode deletion explicitly in the outgoing action. Do not equate all empty strings with deletion without separate SDK evidence.

**Verification.** Test null on existing and absent keys; inspect count and indexed keys locally and on another client after completion. Avoid using the current missing-key getter as the only assertion because its container accessor inserts an empty entry. Not executed.

### [BASE-API-005] Friend-list success omits the promised automatic persona retrieval

- **Severity:** Medium
- **Confidence:** High
- **Category:** API/ABI
- **Location:** `Source/Client/Impl/Friends.cxx:209-222,665-685`; related entry path `Matchmaking.cxx:343-374`.
- **Affected scope:** Clients relying on automatic friend/fellow-member information rather than explicit `RequestUserInformation` calls.

**Evidence.** SDK `IFriends.h:645-655` promises automatic user-information requests after friend-list retrieval and lobby entry, with persona notifications to follow. `RequestFriendList` queues only list success; `ChangeOnlineStatus` only updates membership and friend notifications. `JoinLobbyProcessed` caches the snapshot without requesting information for existing members; only the later member-enter event does so (`Matchmaking.cxx:1123-1128`). Server hello exchange creates `RequestSpecificUserDataMessage` with its default `RequestTypeUserData` (`ServerHandlers.cxx:145-167`; message header `37-39`). Dispatch routes that to `UserImpl`, whose handler updates nickname/stats but neither sets `friend_information_retrieved` nor sends persona notifications (`User.cxx:297-319`).

**Failure mechanism.** A client connects while another peer is already present and successfully retrieves the friend list. Hello exchange may fill its nickname, but no automatic Friends request/response occurs. `IsUserInformationAvailable` stays false and a game waiting for `OnPersonaDataChanged` receives nothing. Entering a lobby containing existing users has the same omission.

**Impact.** Friend/member displays can remain unpopulated or wait indefinitely under a documented SDK usage pattern. The explicit-request path works, masking the gap in callers that always request information themselves.

**Alternatives / recommended resolution.** Request persona data for a snapshot of enumerated friends and existing lobby members, outside collection locks, with deduplication. Alternatively route the already received full hello data through a common persona-cache update/notification function. Prefer shared update logic so availability and notifications cannot diverge; retain feature guards for older SDKs.

**Verification.** Connect two clients, request only the friend list, and require eventual persona availability plus a persona notification without a manual information request. Repeat for a new entrant to a populated lobby and for a later member join. Not executed.
