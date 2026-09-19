# UniverseLAN Review Summary

## Scope And Method

Static review covered 529 in-scope `.cxx`, `.hxx`, `.cmake`, and `.txt` files: the first-party Client, Shared, Server, SystemTests, Tracer, Version, DLL wrapper/build matrix, InterceptionLogger, root CMake files, and root Vendor CMake manifests. SDK headers/binaries, nested vendor source, and the explicitly excluded test trees were not reviewed. Every reviewed file has a sibling `<filename>.review.MD` status report. No build, test, sanitizer, or static analyzer was run.

## Architecture

UniverseLAN has a clear primary split: version-independent utilities in `Shared_NoVer`, Galaxy-version-gated protocol/models in `Shared`, server-side ENet dispatch/state in `Server`, and SDK facades in `Client`. The version matrix is generated consistently from `Source/DLLs` and `galaxy_sdk_features.cmake`. The main systemic risks are that network payloads are trusted before bounded decoding, asynchronous client work has no unified shutdown ownership, and the interception facade has incomplete forwarding and proxy lifetime management.

## Findings

44 confirmed defects were recorded: 21 High, 20 Medium, and 3 Low.

### [CLIENT-001] Initialization failure is caught and then dereferenced

- **Severity:** High
- **Location:** `Source/Client/GalaxyDLL.cxx:35-69`, `Init`
- **Description:** Construction failures are caught, then `intf_inst.client->Start()` is called despite a null client.
- **Impact:** An unavailable server or invalid setup crashes the host instead of returning initialization failure.
- **Resolution:** Return after cleanup and preserve the SDK initialization error; test with an unreachable endpoint.

### [CLIENT-002] Standalone game-server initialization uses client-global state

- **Severity:** High
- **Location:** `Source/Client/UniverseGameServer.cxx:24-40`, `InitGameServer`
- **Description:** It initializes `gameserver_intf_inst` but accesses `intf_inst.config`.
- **Impact:** The documented standalone server API can dereference null before startup.
- **Resolution:** Use the game-server instance consistently and initialize it as a game server.

### [CLIENT-003] Detached file-share work outlives storage

- **Severity:** High
- **Location:** `Source/Client/Impl/Storage.cxx:128-136`, `StorageImpl::FileShare`
- **Description:** A detached worker captures `this` and other shutdown-owned objects.
- **Impact:** Shutdown concurrent with file I/O causes use-after-free.
- **Resolution:** Own/cancel/join file-share tasks before destroying storage and listeners.

### [CLIENT-004] Callback queue is destroyed before its producers stop

- **Severity:** High
- **Location:** `Source/Client/UniverseLAN.cxx:91-99`, `InterfaceInstances::reset`
- **Description:** `delay_runner` is destroyed before the client/WebSocket producers are stopped.
- **Impact:** A late producer writes through a dangling callback queue pointer.
- **Resolution:** Stop and join all producers, then destroy the registrar and queue under a shutdown state.

### [CLIENT-005] Unregister leaves queued single-shot callbacks live

- **Severity:** High
- **Location:** `Source/Client/Impl/ListenerRegistrar.hxx:319-321`, `NotifyAll`
- **Description:** Queued callables capture raw specific-listener pointers; unregister cannot retract them.
- **Impact:** Destroying a listener after unregister can produce a callback use-after-free.
- **Resolution:** Queue a registration token/shared dispatch state and validate registration at delivery.

### [CLIENT-006] Galaxy thread destructor can terminate the process

- **Severity:** High
- **Location:** `Source/Client/Impl/GalaxyThread.cxx:49-58`, `GalaxyThreadImpl::~GalaxyThreadImpl`
- **Description:** It unconditionally calls `std::thread::detach()`, which throws for an already non-joinable thread.
- **Impact:** A normal Join/Destroy lifecycle invokes `std::terminate`.
- **Resolution:** Check `joinable()` and establish explicit ownership/join behavior.

### [CLIENT-007] WebSocket receive buffer has a data race

- **Severity:** High
- **Location:** `Source/Client/Impl/CustomNetworking.cxx:76-88,243-250`
- **Description:** The callback locks the deque for inserts but `GetAvailableDataSize()` reads it unlocked.
- **Impact:** Concurrent network/game threads have undefined behavior and can corrupt the deque.
- **Resolution:** Lock every buffer access; validate with TSan.

### [CLIENT-008] Unknown lobby-list response dereferences null request state

- **Severity:** Medium
- **Location:** `Source/Client/Impl/Matchmaking.cxx:210-245`, `RequestLobbyListProcessed`
- **Description:** An unmatched response ID produces null state then dereferences it.
- **Impact:** A stale or malformed server response crashes the client.
- **Resolution:** Reject unmatched IDs before use and log the protocol violation.

### [CLIENT-009] Invalid custom-network connection IDs crash SendData

- **Severity:** Medium
- **Location:** `Source/Client/Impl/CustomNetworking.cxx:235-241`, `SendData`
- **Description:** A nullable channel result is dereferenced.
- **Impact:** Invalid or closed public connection IDs crash the host.
- **Resolution:** Return the SDK invalid-state/argument error when no channel exists.

### [CLIENT-010] Closed custom-network channels are retained indefinitely

- **Severity:** Medium
- **Location:** `Source/Client/Impl/CustomNetworking.cxx:149-164,211-215`
- **Description:** Cleanup runs only while opening another connection.
- **Impact:** Open/close cycles grow retained channel state until shutdown.
- **Resolution:** Run synchronized cleanup after close or during normal processing.

### [CLIENT-011] Empty P2P queue pop is undefined behavior

- **Severity:** Medium
- **Location:** `Source/Client/Impl/Networking.cxx:107-112`, `PopP2PPacket`
- **Description:** `std::queue::pop()` is called without checking `empty()`.
- **Impact:** Empty public API calls can corrupt/crash.
- **Resolution:** Make empty pop a locked no-op.

### [CLIENT-012] Cloud buffer download reverses capacity behavior

- **Severity:** Medium
- **Location:** `Source/Client/Impl/CloudStorage.cxx:214-240`, `GetFile`
- **Description:** Read byte count is compared to capacity, so larger buffers fail and full truncated buffers succeed.
- **Impact:** Cloud saves can silently truncate or spuriously fail.
- **Resolution:** Compare capacity to file size before read and report buffer-too-small only when incomplete.

### [CLIENT-013] Streamed cloud hashing includes stale final-buffer bytes

- **Severity:** Medium
- **Location:** `Source/Client/Impl/CloudStorage.cxx:578-585`, `CalculateHash`
- **Description:** The final chunk hashes `buffer_size`, not the actual `read_size`.
- **Impact:** Hashes differ for the same non-aligned content.
- **Resolution:** Hash `read_size` and validate callback bounds.

### [CLIENT-014] SignOut leaves local authentication state unchanged

- **Severity:** Medium
- **Location:** `Source/Client/Impl/User.cxx:253-259`, `SignOut`
- **Description:** It queues callbacks but does not change state read by `SignedIn()`/`IsLoggedOn()`.
- **Impact:** Games continue treating a signed-out user as authenticated.
- **Resolution:** Transition state and cancel/fail pending authenticated work before notifications.

### [CLIENT-015] Public GetError is a permanent null stub

- **Severity:** Medium
- **Location:** `Source/Client/GalaxyDLL.cxx:180-185`, `GetError`
- **Description:** The exported error API always returns null.
- **Impact:** Consumers cannot distinguish invalid API calls from success.
- **Resolution:** Maintain/reset a thread-local last error at public API boundaries.

### [CLIENT-016] Legacy factory Init ignores contract arguments

- **Severity:** Medium
- **Location:** `Source/Client/GalaxyApiFactory.cxx:40-65`
- **Description:** Exception mode, peer path, and supplied configuration path are ignored.
- **Impact:** Legacy SDK consumers receive silent incompatible behavior.
- **Resolution:** Model and honor each parameter or return an explicit unsupported error.

### [CLIENT-017] Windows process-path log uses an impossible success test

- **Severity:** Low
- **Location:** `Source/Client/GalaxyDLL.cxx:26-32`
- **Description:** `GetModuleFileName()` success is compared to zero.
- **Impact:** Normal path diagnostics are suppressed.
- **Resolution:** Treat nonzero as success and handle capacity-length truncation.

### [SHARED-001] Default configuration publishes a universal authentication key

- **Severity:** High
- **Location:** `Source/Shared/IniData.cxx:307-315`; `Source/Shared_NoVer/DefaultConfigFiles.cxx:23-37,231-246`
- **Description:** Every default deployment uses the same source-visible key while the server binds all interfaces.
- **Impact:** Any peer can compute the challenge response and impersonate a user.
- **Resolution:** Generate a cryptographically random per-installation secret and use a standard MAC challenge response.

### [SHARED-002] Network decoding and received-event queue are unbounded

- **Severity:** High
- **Location:** `Source/Shared/Networking/Networking.hxx:25-64,124-125`; `Networking.cxx:165,219-226`
- **Description:** Cereal payload collection sizes and queued events have no byte/count limits.
- **Impact:** A peer can exhaust memory/CPU through oversized frames or flooding.
- **Resolution:** Enforce packet/field/allocation/queue budgets and disconnect or rate-limit violations.

### [SHARED-003] Connection state races between polling and callers

- **Severity:** High
- **Location:** `Source/Shared/Networking/Networking.hxx:127-135`; `Networking.cxx:152-159,177-180,229-230`
- **Description:** `is_connected` is a plain bool read and written by different threads.
- **Impact:** Undefined behavior and unreliable lifecycle state.
- **Resolution:** Confine state to one thread or make synchronization and transition ownership explicit.

### [SHARED-004] Linux default Galaxy IDs collide

- **Severity:** High
- **Location:** `Source/Shared_NoVer/MachineInfo.cxx:570-572`; `DefaultConfigFiles.cxx:180-199`; `IniData.cxx:589-601`
- **Description:** Non-Windows uses a literal MAC address to derive the default identity.
- **Impact:** Fresh Linux clients impersonate/collide with one another.
- **Resolution:** Use real adapters or a persistent random per-user installation ID.

### [SHARED-005] Escaped filesystem entries retain a dangling parent pointer

- **Severity:** High
- **Location:** `Source/Shared_NoVer/filesystem_container/filesystem_container_entry.hxx:19-31`; `filesystem_container_entry.cxx:91-113,145`
- **Description:** Shared entry objects store a raw owning-container pointer.
- **Impact:** Retained entries can use freed container memory.
- **Resolution:** Move shared state behind shared/weak ownership and fail safely after destruction.

### [SHARED-006] A real disconnect delivers two notifications

- **Severity:** Medium
- **Location:** `Source/Shared/Networking/Networking.cxx:158-165,186-199`
- **Description:** Both the ENet disconnect and a synthetic disconnect are queued.
- **Impact:** Consumers duplicate cleanup/reconnect work.
- **Resolution:** Emit exactly one event per transition.

### [SHARED-007] Concurrent file copies can duplicate index entries

- **Severity:** Medium
- **Location:** `Source/Shared_NoVer/filesystem_container/filesystem_container.cxx:257-288`
- **Description:** The map absence check and index insertion use separate lock windows.
- **Impact:** Concurrent copy completion makes enumeration/removal inconsistent.
- **Resolution:** Perform check-and-insert atomically and append only on successful map insertion.

### [SHARED-008] Stats synchronization excludes copies and serialization

- **Severity:** Medium
- **Location:** `Source/Shared_NoVer/AchievementsAndStatsContainer.hxx:50-54`; `AchievementsAndStatsContainer.cxx:14-19,33-43`
- **Description:** Mutexes protect setters but not archive/copy access.
- **Impact:** Concurrent mutations race with map traversal and archive generation.
- **Resolution:** Lock snapshots/copies in a documented global order and expose safe snapshots.

### [SHARED-009] Float stats serialize an inactive union member

- **Severity:** Medium
- **Location:** `Source/Shared_NoVer/AchievementsAndStatsContainer.hxx:12-21`
- **Description:** Float storage activates `f`, while serialization reads `i`.
- **Impact:** This relies on nonportable union-punning behavior.
- **Resolution:** Preserve the wire bits with `std::bit_cast` and fixed-width storage.

### [SHARED-010] One corrupt metadata sidecar prevents container startup

- **Severity:** Medium
- **Location:** `Source/Shared_NoVer/filesystem_container/filesystem_container_entry.cxx:31-53`; `filesystem_container.cxx:29-44`
- **Description:** Metadata parse failure propagates out of startup enumeration.
- **Impact:** A single damaged sidecar makes unrelated stored files unavailable.
- **Resolution:** Quarantine/rebuild malformed metadata and write sidecars atomically.

### [SHARED-011] INI trimming passes signed chars to isspace

- **Severity:** Low
- **Location:** `Source/Shared/IniData.cxx:36-49`
- **Description:** Plain negative `char` values are passed to `isspace`.
- **Impact:** Non-ASCII configuration can invoke undefined behavior.
- **Resolution:** Cast to `unsigned char` before classification.

### [SERVER-001] Lobby-addressed P2P packets lack membership authorization

- **Severity:** High
- **Location:** `Source/Server/ServerHandlers.cxx:398-424`
- **Description:** Any authenticated peer can send a packet to a lobby owner without being a member.
- **Impact:** Outsiders can inject application traffic into arbitrary lobby hosts.
- **Resolution:** Require `lobby->IsMember(sender)` before forwarding.

### [SERVER-002] Windows crash handler can deadlock on a recursive fault

- **Severity:** High
- **Location:** `Source/Tracer/Stacker.cxx:102-110,207-220`
- **Description:** Nested crash handling waits for the outer handler that cannot resume.
- **Impact:** Crashed processes hang and emit misleading dump context.
- **Resolution:** Fail fast on recursion, never wait in the fault path, and pass supplied exception pointers to the dump writer.

### [SERVER-003] Non-joinable lobbies still admit users

- **Severity:** Medium
- **Location:** `Source/Server/ServerHandlers.cxx:558-575`
- **Description:** Join checks absence/fullness but not `IsJoinable()`.
- **Impact:** Owners cannot close admission before a match.
- **Resolution:** Reject non-joinable lobby entry before mutation.

### [SERVER-004] Server destruction leaks connected peer state

- **Severity:** Medium
- **Location:** `Source/Server/Server.cxx:196-199`; `Source/Server/Peer.cxx:31-49`
- **Description:** Peer data is allocated through `ENetPeer::data` and only disconnect frees it.
- **Impact:** Graceful/in-process shutdown leaks state and skips cleanup.
- **Resolution:** Add explicit shutdown cleanup or make mapper ownership RAII-based.

### [SERVER-005] Authentication verifier is logged

- **Severity:** Medium
- **Location:** `Source/Server/Server.cxx:90-104`
- **Description:** The verifier-equivalent authentication material is printed at startup.
- **Impact:** Log readers can authenticate as arbitrary users.
- **Resolution:** Remove credential/verifier output and treat the existing scheme as LAN-only until replaced.

### [SERVER-006] Lobby configuration updates broadcast to unrelated peers

- **Severity:** Medium
- **Location:** `Source/Server/ServerHandlers.cxx:709-752`
- **Description:** Lobby state update helper uses host-wide broadcast.
- **Impact:** Outsiders receive unrelated updates and can corrupt local caches.
- **Resolution:** Send only to current lobby members.

### [BUILD-001] Resource generation dirties the source checkout

- **Severity:** Medium
- **Location:** `Source/DLLs/CMakeLists.txt:43-45,191,193-194`
- **Description:** CMake writes generated resource files and deployed config under the source tree.
- **Impact:** Builds are non-hermetic, fail read-only checkouts, and conflict across build trees.
- **Resolution:** Generate under the binary tree and make deployment/install destinations configurable.

### [BUILD-002] Test binary staging wrongly depends on interceptor builds

- **Severity:** Medium
- **Location:** `Source/DLLs/CMakeLists.txt:153-184`
- **Description:** Client/server test copies are nested inside `BUILD_INTERCEPTOR`.
- **Impact:** Normal test-only configurations lack required staged binaries.
- **Resolution:** Move client/server copy commands outside the interceptor conditional.

### [BUILD-003] Compatibility manifest has an invalid version token

- **Severity:** Low
- **Location:** `Source/DLLs/1.149.0/compat_list.txt:13`
- **Description:** The manifest records `1.150.0?` rather than the wrapper version.
- **Impact:** External manifest consumers may not resolve/package 1.150.0.
- **Resolution:** Replace it with `1.150.0` or a supported comment syntax.

### [INTERCEPT-001] Successful factory initialization can dereference null error

- **Severity:** High
- **Location:** `Source/InterceptionLogger/Impl/Errors.cxx:57-60`; `UniverseLANInterceptor.cxx:216-221`
- **Description:** `HasError()` tests callback presence rather than the returned `IError*`.
- **Impact:** Successful native initialization or `GetError()` crashes on null.
- **Resolution:** Invoke and null-check the wrapped getter before error access.

### [INTERCEPT-002] Interception shutdown omits or calls invalid native teardown

- **Severity:** High
- **Location:** `Source/InterceptionLogger/GalaxyDLL.cxx:72-76`; `UniverseGameServer.cxx:38-44`; `UniverseLANInterceptor.cxx:301-302`
- **Description:** Client shutdown skips native shutdown; game-server shutdown clears and then invokes it.
- **Impact:** Reinitialization leaks native state or throws from an exported API.
- **Resolution:** Preserve the callable, invoke it once before clearing wrappers, then clear state.

### [INTERCEPT-003] Authentication-success callbacks are dropped

- **Severity:** High
- **Location:** `Source/InterceptionLogger/Impl/Listeners/UserListener.cxx:27-46`
- **Description:** Proxy success/lost callbacks only trace instead of forwarding/cleaning up.
- **Impact:** Games wait forever for sign-in and leak proxies.
- **Resolution:** Forward both callbacks through the correct single-shot lifecycle.

### [INTERCEPT-004] Single-shot proxy map loses concurrent operations

- **Severity:** High
- **Location:** `Source/InterceptionLogger/Impl/Listeners/ProxifySingleShotListener.hxx:39-47`; `.cxx:9-14`; `ListenerRegistrar.cxx:43-52`
- **Description:** One map key per caller listener silently drops a second proxy.
- **Impact:** Unregister/destroy leaves a pending proxy that can call freed memory.
- **Resolution:** Own every proxy per real listener and cancel all atomically.

### [INTERCEPT-005] Rich-presence key copy calls persona-name API

- **Severity:** High
- **Location:** `Source/InterceptionLogger/Impl/Friends.cxx:738-753`
- **Description:** It ignores key arguments and forwards `GetPersonaNameCopy`.
- **Impact:** Rich-presence key enumeration is functionally broken.
- **Resolution:** Forward the requested rich-presence method with all arguments.

### [INTERCEPT-006] Cloud delete discards expected hash

- **Severity:** High
- **Location:** `Source/InterceptionLogger/Impl/CloudStorage.cxx:295-313`
- **Description:** The conditional-delete `expectedHash` is logged but not forwarded.
- **Impact:** Changed cloud files can be deleted despite compare-before-delete intent.
- **Resolution:** Forward the hash in hashing-enabled builds.

### [INTERCEPT-007] Factory error manager is a null stub

- **Severity:** High
- **Location:** `Source/InterceptionLogger/GalaxyApiFactory.cxx:155-169`
- **Description:** `GetLastError()` always returns null despite a native manager being bound.
- **Impact:** Enabled public error-manager API is unusable.
- **Resolution:** Proxy the native error manager or remove the advertised path.

## Recommended Order

1. Fix initialization/shutdown use-after-free/crash paths: CLIENT-001 through CLIENT-007 and INTERCEPT-001 through INTERCEPT-004.
2. Bound and authorize the network boundary: SHARED-001 through SHARED-003 and SERVER-001/003/006.
3. Correct public API compatibility defects, then add focused regression tests for every identifier.
4. Run Windows limited-version Debug/Release builds plus ASan/TSan-equivalent lifecycle and protocol-fuzz tests before release.
