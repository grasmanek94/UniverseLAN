# `GalaxyGameServerApi.h` Header Coverage

## Selected SDK

| Declaration group | Practical coverage | Boundary |
| --- | --- | --- |
| Game-server init, process, shutdown, shutdown options | Lifecycle fixture needed | Requires global server initialization, pump, listener destruction, and terminal shutdown. |
| Server user, matchmaking, networking, utils, and logger accessors | Explicit server fixture needed | Client/factory-local interface scenarios do not establish global game-server API behavior. |
| Server telemetry and telemetry listener | Mutation/admin-policy-blocked | Sending telemetry requires explicit approval. |
| Authentication, operational state, service/session callbacks | External-platform-fixture-blocked | Require approved server credentials, authenticated official environment, and network. |
| Access tokens, encrypted tickets, user-data callbacks | Sensitive/mutation-policy-blocked | Do not generate or retain credentials, tickets, or user-data mutations. |
| Server lobby and P2P/NAT listener aliases | Explicit server-and-client fixture needed | Use owned server-created public non-host-migrating lobbies and controlled clients only. |
| Existing factory-local server-networking sender-identity scenario | Separate UniverseLAN-only characterization | It uses `InitLocal` and factory accessors, not the global API or its listener aliases. |

## Safety Rules

- Never retain server credentials, tokens, tickets, user IDs, lobby IDs, payloads, endpoints, timestamps, or runtime artifacts.
- Destroy server listeners before global shutdown and do not infer global API behavior from peer/client coverage.
