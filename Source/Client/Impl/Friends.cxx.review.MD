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

## Thorough follow-up addendum — 2026-09-24

All 699 implementation lines and all 644 header lines were reread before comparison with the baseline reports. Production input is still `b30e83872c0006e8240c8b4f565da5351bf10080`. The original sections above are preserved. This pass is static; all verification below is proposed, not executed.

### [ADD-API-001] NEW — Deleting a presence key returned by the API reads it after erasing its storage

- **Severity:** Informational (conditional compatibility finding; potential High memory-safety impact)
- **Confidence:** Medium for SDK-permitted aliasing; High for the source mechanism, reproduced locally with ASan
- **Category:** Memory Safety
- **Location:** `Source/Client/Impl/Friends.cxx:363-380,558-570`, `DeleteRichPresence` / `GetRichPresenceKeyByIndex`.
- **Affected scope:** Same-thread, signed-in presence enumeration and deletion; the direct key-getter reproducer is available from SDK 1.148.2 (`galaxy_sdk_features.cmake:208`). Windows x86/x64; no concurrency or invalid caller-owned allocation is required.

**Evidence.** `GetRichPresenceKeyByIndex` returns `ref->first.c_str()` from the local presence map. `DeleteRichPresence` first calls `stats.EraseRichPresence(key)` at line 372 and only afterward constructs `RichPresenceChangeMessage{..., ACTION_DELETE, key}` at line 380. The Shared_NoVer eraser actually destroys the map node (`AchievementsAndStatsContainer.cxx:160-164`). Its `const std::string&` parameter receives a temporary copy of the incoming C string, but that copy is confined to the erase call's full expression; it does not repair the outer `const char* key`. The wire constructor then copies from that original pointer (`Shared/Networking/Messages/RichPresenceChangeMessage.hxx:39-40`). SDK `1.152.11/galaxy/IFriends.h:926-936,1005-1016` exposes both operations and only marks the pointer getter as non-thread-safe, not forbidden as input to a subsequent same-thread operation.

**Failure mechanism.** With just the valid `status` property present and local presence retrieved, execute `DeleteRichPresence(GetRichPresenceKeyByIndex(0))`. The pointer is valid at the call boundary. The callee erases the exact node that owns it, then reads through it during implicit `std::string` construction for the network message. Even a short, small-string-optimized key is inside the freed map node. Request-listener bookkeeping between erasure and serialization can reuse the allocation. The application neither retains the pointer after deletion nor frees any storage itself.

**Impact.** Heap use-after-free while constructing an otherwise valid request: crash, corrupted outgoing key, or local deletion that is not propagated correctly. This is distinct from BASE-API-002's concurrent Copy-getter race: adding a lock around this entire operation does not make the already erased pointer valid.

**Alternatives.** Copy the key at API entry; alternatively construct an owning outgoing request before changing the cache and use that request's owned key for both operations. Documenting a new caller-side no-alias rule would change compatibility and leaves other mutation-before-serialization paths fragile.

**Recommended fix.** Snapshot the normalized key before erasure, then use the snapshot for both `EraseRichPresence` and wire construction. Preserve missing-key no-op semantics and one completion. Audit other setters that mutate API-owned string storage before serializing borrowed arguments, without assuming every pointer getter already has this exact failure.

**Verification.** The coordinator's Windows x64 ASan helper reproduced the exact real-container erasure followed by real-message string construction: `heap-use-after-free`, with the free at `AchievementsAndStatsContainer.cxx:162` and the read during `std::string` construction. This is a mechanism reproduction, not a full Friends API/native-SDK test. The SDK header does not explicitly settle borrowed-pointer lifetime across a mutating API call, so the original supported-input assertion is qualified and this ID is excluded from confirmed totals. An owned-key control and a native/version-specific contract check remain proposed. See `.ai/review-addendum/VERIFICATION.MD`.

### [ADD-API-002] NEW — Default local rich-presence retrieval publishes the invalid input sentinel as a user identity

- **Severity:** Informational (conditional callback-contract finding; potential Medium impact)
- **Confidence:** Medium; emitted zero is established, but native zero-means-self callback convention is unresolved
- **Category:** API/ABI
- **Location:** `Source/Client/Impl/Friends.cxx:444-457`; default declaration `Friends.hxx:479-483`.
- **Affected scope:** `RequestRichPresence()` using its SDK-default `GalaxyID()` argument; global presence listeners from 1.74.0, and operation-specific retrieval listeners from 1.126.0.

**Evidence.** SDK `1.152.11/galaxy/IFriends.h:947-956` supplies the default `GalaxyID()`. Its presence-update and retrieval-success callbacks identify the user (`433-462`). `GalaxyID.h:63-68,143-145` explicitly defines that default object as invalid. `ClientIniData::IsSelfUserID` maps zero to the configured local user (`Shared/IniData.cxx:921-926`), and `UserImpl::GetGalaxyUserData` resolves it to local storage (`User.cxx:578-583`). Nevertheless, both deferred notifications pass the original zero `userID`, not the resolved local ID. Explicit-local-ID calls and server-originated remote updates pass concrete IDs.

**Failure mechanism.** A signed-in caller invokes the defaulted API. The operation succeeds locally, then `OnRichPresenceRetrieveSuccess` and `OnRichPresenceUpdated` report an invalid ID. A globally registered listener keyed by the actual `User()->GetGalaxyID()` cannot associate the update with that user; using the invalid result as a remote target is also not equivalent to the original local-selection argument.

**Impact.** Default and explicit-self requests produce different identity domains for the same cached data, causing missed self updates or a bogus user entry in application caches. This is not a complaint about an arbitrary invalid ID supplied to an API lacking a default.

**Alternatives.** Resolve the local selector before notification; or retain both requested selector and resolved identity internally while publishing the latter. Changing general GalaxyID equality or treating every zero callback as self throughout an application would conceal the boundary error.

**Recommended fix.** Resolve the self branch to the configured API ID before queuing both callbacks. Keep the same storage lookup semantics for defaulted getters. Do not automatically extend zero-as-self to `GetFriendPersonaState`, `IsUserInTheSameGame`, or other methods whose SDK declarations require a concrete ID.

**Verification.** Register global and operation listeners, compare a default request with an explicit local-ID request after sign-in, and require valid, equal callback IDs plus equal presence content. Verify remote requests retain the remote ID. Cover the pre-1.126 global-only branch separately. A native-SDK differential check would additionally pin exact legacy callback conventions. Not executed.

**Reconciled qualification.** The callback wording alone does not exclude a zero-means-self convention. The preceding mechanism and consequences are conditional until stronger SDK evidence establishes normalization. This is retained for investigation, not counted as a confirmed compatibility defect.

### Existing BASE findings — retained evidence and qualified additions

- **BASE-API-002 retained (High):** the map-level lock in `User.cxx:585-591` does not protect nickname/availability fields after lookup. `AchievementsAndStatsContainer::operator=` locks presence while replacing it (`33-52`), so indexed presence copies holding that same lock are useful counterevidence, not another race. `IsUserInformationAvailable` reads the plain availability flag concurrently with `RequestUserInformationProcessed`; include it in the existing per-user synchronization fix, not a new ID.
- **BASE-API-003 retained (Medium):** only coherent LAN-peer friendship is requested; persistent GOG friendship/invitation capability is not inferred.
- **BASE-API-004 retained (Medium):** null deletion is explicitly permitted, unlike arbitrary null arguments elsewhere. Snapshotting the key for ADD-API-001 is required if the null-as-delete fix routes borrowed keys through deletion.
- **BASE-API-005 retained (Medium):** hello snapshots update User data, not Friends availability/persona notifications. Additionally, `RequestFriendList` has no initial-peer-snapshot completion barrier: Server acceptance is sent before existing-online-peer messages (`ServerHandlers.cxx:93-109`), while list success can be queued immediately. A request from auth success may complete before those peer events have arrived. Include that startup ordering in validation of the existing retrieval/publication path rather than count another success-without-retrieval ID. A stable multi-call friend-list snapshot under arbitrary concurrent peer churn is not explicitly promised by the inspected SDK and is not reported as a separate defect.
- **Persona refresh qualification:** subsequent successful Friends responses can change `nickname` but emit only `PERSONA_CHANGE_NONE` because the NAME flag is conditional on first retrieval (`76-99`). Server reconnection/hello processing can also update that name through User first. Include actual-name-change/unchanged refresh cases when consolidating BASE-API-005's persona publication logic; no extra accounting for the same incomplete publication path.
