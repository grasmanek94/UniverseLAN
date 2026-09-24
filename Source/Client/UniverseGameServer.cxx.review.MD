# Fresh baseline review — UniverseGameServer.cxx

- Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`.
- Coverage: entire file, lines 1–123; static Windows-focused review.

## Specific checked notes

- Traced separate game-server interface ownership, initialization, worker start, getters, explicit reset, and event/notification pumping.
- The pre-1.135 networking accessor selects `server_networking`; later builds return `networking`. This version split is significant to the defect below.
- Feature conditions for utilities and telemetry were compared with `galaxy_sdk_features.cmake` and modern SDK declarations. No additional source-level virtual signature mismatch was established.
- Error rethrow behavior shares `BASE-CORE-005` with the client entry point; immediate callback-time reset shares `BASE-CORE-003`. Both are counted at their canonical reports.

## Confirmed finding

### BASE-CORE-004 — Game-server initialization selects the client packet role

- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Client/UniverseGameServer.cxx:25–28,74–80`.
- **Affected scope:** Game-server networking in SDK builds from 1.135.0 onward, where `HAS_ISERVERNETWORKING` is false.

**Evidence**

`gameserver_intf_inst.init(initOptions)` omits the `is_gameserver` argument. `UniverseLAN.hxx:98` defaults it to false; `UniverseLAN.cxx:56` consequently creates `NetworkingImplType::Client`. The modern game-server getter returns that instance. `Networking.cxx:56–63` chooses `P2PServerNetworkPacketMessage` only for Server/GameServer roles. SDK 1.152.11 `GalaxyGameServerApi.h:63–64,123–129` defines this interface as the lobby-host interface.

**Failure mechanism**

A dedicated game server sends to a particular lobby member via `GameServerNetworking()->SendP2PPacket(memberID, ...)`. With the client role it sends the ordinary peer message. `Server/ServerHandlers.cxx:429–452` relays that message with the sender's user ID. The intended server-message path at lines 336–358 relays it with the lobby ID. Sending to the lobby ID can appear to work because the ordinary handler has a post-1.134 owner-broadcast special case; that does not fix direct-member addressing.

**Impact**

Clients that identify dedicated-server traffic by lobby ID can reject or misclassify direct replies; transport behavior differs according to addressing mode. Older builds using `server_networking` already select the Server role, so the demonstrated routing error is scoped to the newer branch.

**Possible solutions**

1. Pass `true` from the game-server initializer.
2. Replace the boolean/default with an explicit runtime-role enum and require each initializer to specify it.

**Recommendation**

Pass the correct game-server role now, then use an explicit role parameter to make accidental defaulting harder. Keep host packet semantics consistent across SDK versions.

**Verification**

For 1.139.2 and 1.152.11, create a dedicated-server lobby and send both to a member ID and the lobby ID; assert identical lobby-sender identity at the receiving client and correct payload/channel. Include a 1.134.10 control. No network or game-server execution was performed.

### BASE-CORE-005 — Game-server Init rethrows implementation errors instead of publishing SDK errors

- **Severity:** Medium
- **Confidence:** High
- **Category:** API/ABI
- **Location:** `Source/Client/UniverseGameServer.cxx:25–37`.
- **Affected scope:** Game-server initialization; same error-boundary root cause as `GalaxyDLL.cxx.review.MD`, counted once.

**Evidence**

The initializer catches `std::exception`, displays/logs it, and rethrows. The shared Client constructor throws on ENet/host lookup failure, while the public GetError implementation always returns null. SDK error documentation defines per-thread GetError retrieval; `GalaxyGameServerApi.h:78–81` explicitly allows partial initialization failure and subsequent shutdown.

**Failure mechanism**

A game server uses a configured hostname that cannot resolve. Its Client constructor fails, and the exported InitGameServer call leaks `std::runtime_error` instead of making the SDK error available to the calling thread.

**Impact**

A dedicated host expecting SDK-style error handling can terminate rather than recover, and the shared error accessor provides no cause.

**Possible solutions**

Translate errors in a common client/game-server entry-point boundary or use a shared helper that records thread-local SDK error objects while preserving legal partial-init cleanup.

**Recommendation**

Apply the same nonthrowing modern SDK error policy to both runtimes. A client-only fix would leave the dedicated-server path incompatible.

**Verification**

Force game-server host-lookup failure using synthetic configuration; require no implementation exception, a runtime SDK error on the calling thread, and safe ShutdownGameServer after partial initialization. Not executed.

## Full-reread addendum — 2026-09-24

### [ADD-CORE-003] Client and game-server runtimes reuse one configured identity and the relay rejects the second

- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness / runtime isolation
- **Exact location:** `Source/Client/UniverseGameServer.cxx:25–28,53`; shared construction `Source/Client/UniverseLAN.cxx:18–25,38–49`; identity submission `Source/Client/ClientNetworkHandlers.cxx:60–71`.
- **Affected scope:** SDK builds exposing Game Server (feature threshold 1.120.0), with the ordinary client and game-server initialized against the same UniverseLAN relay and unchanged configuration in one process. Also relevant to separate same-machine processes sharing an unchanged identity, but that broader configuration case is not the counted trigger.

**Evidence**

The client singleton and embedded game-server `InterfaceInstances` each construct the same parameterless `ClientIniData`. No runtime role, independent identity, or per-graph configuration root is supplied. `ClientIniData` reads the same Client/User settings (`Source/Shared/IniData.cxx:420–478`); default identity is the local adapter MAC hash and offset zero, while a fixed `@Custom` value is an equally deterministic example. `GetApiGalaxyID` always converts the configured real ID into a user ID (`777–795`). Both connection handlers submit that ID in their challenge reply, and hello uses it again (`ClientNetworkHandlers.cxx:85–89`). `GameServerUser()->SignInAnonymous` just forwards to the common SignIn (`Impl/User.cxx:135–144`); it does not assign a separate identity.

The relay's challenge handler inserts the ID into `user_data` and accepts only a new insertion (`Source/Server/ServerHandlers.cxx:84–94`). An already occupied ID reaches the rejection/disconnect at `125–129`. `peer::Data::link` additionally enforces unique ID mapping (`Source/Server/Peer.cxx:71–88`). This is concrete application-level rejection, not an assumed ENet address conflict.

SDK 1.152.11 `GalaxyGameServerApi.h:43–56` describes a separate anonymously authenticated Game Server object. `InitOptions.h:37` explicitly discusses an allocator shared by both Peer and Game Server, supporting their coexistence rather than treating a second graph as misuse.

**Failure mechanism / real trigger**

Using one unchanged, valid local configuration (for example `GalaxyIDType=@Custom`, one nonzero ID and zero offset), initialize the ordinary client and pump until relay acceptance. Initialize the game-server runtime, request anonymous sign-in, and pump both entry points. The second runtime answers its challenge with the first runtime's ID. The relay's insertion fails, so the second cannot become accepted/logged on; anonymous SignIn cannot change the ID. Reversing initialization order reverses which runtime can acquire that identity. No concurrent Init calls, malformed packet, or application-created duplicate listener is required.

**Impact**

A game using both public runtimes cannot establish both relay sessions with the normal shared configuration. Dedicated hosting combined with a local player can remain in a login/reconnect loop. This is not proof of identity spoofing or a security bypass. The documented requirement for unique IDs across separately configured players does not provide independent identity selection for these two graphs reading the same configuration.

**Possible solutions**

1. Make runtime role part of identity/configuration construction and allocate a collision-resistant separate game-server identity.
2. Support explicit per-runtime identity overrides or a server-assigned anonymous identity, preserving the client's configured identity.
3. If coexistence is deliberately unsupported, detect and report it explicitly rather than starting an inevitably rejected second connection; this would remain a documented SDK compatibility limit.

**Recommended resolution**

Propagate an explicit role into graph/configuration initialization and isolate the game-server session identity. Define persistence, concurrent-server-instance and collision behavior; an unchecked numeric increment is insufficient. Preserve relay uniqueness checks. Merely passing `true` to fix BASE-CORE-004 changes packet-envelope role at `UniverseLAN.cxx:56–58`; it does **not** change `ClientIniData` or the handshake identity, so both fixes are necessary.

**Verification — proposed, not executed**

Use synthetic configuration, disabled tracing to isolate setup, and a matching-version local relay. In one host process initialize client plus Game Server in each order, pump both, and assert two distinct accepted identities, both login completions, and independent shutdown. Create a server lobby and connect the local client as an integration follow-up. Include game-server-only and two explicitly distinct-configured-process controls. Exercise 1.134.10 and 1.152.11 to demonstrate independence from the old/new networking-role split. No actual connection or credentials were used.

**Baseline comparison**

The baseline left configuration identity/coexistence as an open architecture question. Source tracing now reaches a definite duplicate-ID rejection. BASE-CORE-004 instead concerns the sender identity of **packets after a successful session**, so this pre-acceptance failure is a distinct addition.
