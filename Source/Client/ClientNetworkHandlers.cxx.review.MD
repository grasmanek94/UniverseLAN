# Fresh baseline review — ClientNetworkHandlers.cxx

- Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`.
- Coverage: entire file, lines 1–281; static network-to-interface tracing.

## Specific checked notes

- Read all handler overloads, including deliberately ignored server-only requests and ping, authentication challenge/acceptance, connection events, all request-type switch arms, lobby events, storage, chat, user data, rich presence, and invitations.
- Confirmed handlers are called from the application's event pump via `GalaxyNetworkClient::ProcessEvents` and `MessageReceiver`, not directly from `Client::Tick`. Worker queues retain event/packet data until this phase.
- Traced transport-connect versus server-accept callbacks into `UserImpl`; the server acceptance path sends initial user data and sets authenticated/logged-on state separately from transport connection.
- Checked capability guards against the optional graph members. The request-type switch routes user data, stats/time played, friends, and rich presence to their intended interfaces.
- P2P payloads route to `networking`; server-envelope payloads route to `server_networking` only on versions with that interface, otherwise to the combined interface. Null nested packets are rejected downstream by `NetworkingImpl::AddPacket`.
- Compared these routes with both server relay handlers and the game-server getter. The demonstrated wrong outgoing game-server role originates in initialization (`BASE-CORE-004`), not in these inbound routes.
- Listener callbacks reached through these delegates inherit registrar cancellation/snapshot defects and pump teardown (`BASE-CORE-001`–`003`).

## Findings and limits

No independent defect confirmed in this routing file. Peer/event lifetime is supplied by ENet and the shared queue layer; parsing, subsystem semantics, and authentication policy are context dependencies rather than fully covered here. No malformed-packet, reconnect, or live transport testing was performed; intentional LAN trust is not classified as an exploit.
