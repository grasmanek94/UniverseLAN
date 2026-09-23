# Fresh review — Networking.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Coverage: all 236 lines; Windows x86/x64 static inspection. No build or runtime reproduction performed.

## Inspection notes
- Followed packet creation, archive framing, polymorphic dispatch, shared-pointer overloads, client queue ownership and server send/broadcast ownership into the actual Enet++ and ENet-IPv6 sources.
- Portable binary adds a one-byte endian marker before the eight-byte class ID. The eight-byte preliminary check is one byte short, but cereal catches that truncation; it is not an out-of-bounds read.
- Ordinary decode exceptions are caught; object allocation precedes the try block and handlers follow it. Raw booleans/enums, nullable object graphs and trailing bytes receive no semantic validation. Unknown class IDs are rejected. No production key material was accessed.
- Client failed sends destroy packets; ENet broadcast destroys an unreferenced packet. The single-peer server path has a different ownership obligation.

### [BASE-NET-001] Wire lengths allocate memory before authentication or payload validation
- **Severity:** High
- **Confidence:** High (mechanically established; not executed)
- **Category:** Security
- **Location:** `Source/Shared/Networking/Networking.hxx:25-63`, `MessageReceiver::ProcessEventFor`; dispatch in `Networking.cxx:33-78`.
- **Affected scope:** Windows client and server decoders; server exposure includes transport-connected, unauthenticated peers.

**Evidence / failure mechanism:** `iarchive(*var)` runs before `Handle`. Server authentication is in `ServerHandlers.cxx:12` and the handlers. Vendored cereal 1.3.2 `types/string.hpp:53-56` and `types/vector.hpp:54-58,78-83` resize from a 64-bit size tag before reading elements. `portable_binary.hpp:239-245` detects a short read only afterward. Map loading iterates and inserts; it does not provide a global allocation budget. ENet caps packet bytes at 32 MiB, with server waiting data set to 512 MiB and client waiting data defaulting to 32 MiB; none bounds allocations derived from a tiny packet's declared lengths.

**Reproduction conditions:** Establish ENet transport to a reachable server; do not answer the key challenge. Send a valid portable-binary header, the `FileShareMessage` class ID, request ID, and a filename length such as 256 MiB with no corresponding bytes. The string allocation/initialization precedes the truncation exception and the upload/authentication checks. Repeat for sustained allocator/CPU pressure. A configured hostile server can exercise the client decoder similarly.

**Impact:** Unauthenticated resource consumption and service stalls; memory-pressure failure is possible. Catching `bad_alloc` does not undo allocation work already performed. This is a parser exposure independent of whether the configured LAN key is public or private; it is not a claimed authentication bypass or demonstrated code execution.

**Alternatives / recommended resolution:** Gate message IDs by direction and handshake state before constructing their payloads, and use bounded decoding with per-field limits, checked size conversion, remaining-input checks and a cumulative decoded-memory/element budget. Authentication alone does not protect against a faulty admitted peer. An outer packet cap alone is insufficient. Prefer explicit bounded wire DTOs over unrestricted cereal object graphs at this boundary.

**Verification:** In a Windows decoder harness, inject short frames claiming large strings/vectors, oversized nested collections, invalid booleans/enums and nullable graphs before/after authentication. Assert bounded allocations, bounded work, rejection before handlers, and destruction of each receive packet exactly once. Include x86 size narrowing. These are proposed tests.

### [BASE-NET-002] A rejected file-sharing path throws past the network boundary and exits the server
- **Severity:** High
- **Confidence:** High (complete static failure path)
- **Category:** Correctness
- **Location:** `Source/Shared/Networking/Networking.hxx:58-63`, `ProcessEventFor` exception boundary; `Networking.cxx:16-105`.
- **Affected scope:** Server dispatch on Windows; analogous client handler exceptions escape the SDK pump.

**Evidence / failure mechanism:** Only deserialization is caught; `Handle(event.peer, var)` is outside that catch. `ServerHandlers.cxx:455-476` accepts an authenticated upload and calls `sfu.shared->create_shared(filename,id)`. `filesystem_container.cxx:144-204,242-245` reaches `sandbox_secure_path_concat`; `filesystem_container_utils.cxx:123-134` throws `std::runtime_error` for a path outside the container. `Server::Tick` and `Main.cxx:33-39` do not catch it. The receive guard frees the input packet while unwinding, but it cannot keep the process alive.

**Reproduction conditions:** Authenticate an ENet client to a server with uploads enabled. Send a correctly serialized `FileShareMessage` with filename `..\\outside.bin` and a small payload. Encoding leaves traversal components intact; canonical containment rejects it by throwing. This does not require an invalid cereal archive or a secret-key bypass.

**Impact:** One admitted peer can terminate the server through a correctly rejected filename. This is availability failure, not evidence that traversal can write outside the storage sandbox.

**Alternatives / recommended resolution:** Prefer translating expected path/input failures to a negative operation response in the file handler. Also define a per-event exception policy at the dispatch boundary that reports the failure and closes/quarantines the offending session without abandoning unrelated peers. Do not indiscriminately suppress arbitrary application callback exceptions or continue after partially committed state without rollback.

**Verification:** On Windows send traversal, invalid-path and injected filesystem-error requests with uploads enabled; assert a failure response or controlled disconnect, process survival, no outside file creation and exactly-once packet cleanup. Test a throwing client callback separately against the documented SDK exception policy.

### [BASE-NET-004] Server single-peer sends abandon packets when ENet rejects them
- **Severity:** Medium
- **Confidence:** High
- **Category:** Memory Safety
- **Location:** `Source/Shared/Networking/Networking.hxx:173-185`, `GalaxyNetworkServer::Send`.
- **Affected scope:** All typed server replies/relays on Windows.

**Evidence / failure mechanism:** The wrapper allocates a packet and directly returns `NetworkServer::Send`. Enet++ `enetpp.cxx:72-79` merely delegates to `enet_peer_send`. ENet `peer.c:93-117` explicitly leaves ownership with the caller on failure (disconnected peer, invalid channel or packet above `maximumPacketSize`), and further allocation/fragment failures also return without transferring ownership. The wrapper neither returns the packet nor destroys it. In contrast, client `DispatchQueuedPackets` destroys rejected packets.

**Reproduction conditions:** Send a serialized response larger than 32 MiB (for example a lobby-list snapshot after history accumulation), or invoke typed Send for a reset/disconnected peer. Each `-1` loses the allocated packet and backing data. Repeating the request repeats the leak.

**Impact:** Persistent server memory growth; large rejected replies accelerate exhaustion. Medium because the ordinary connected, size-compliant success path transfers ownership correctly.

**Alternatives / recommended resolution:** Hold the newly created packet in an RAII owner, releasing only after successful enqueue; alternatively explicitly destroy it on nonzero return. Keep broadcast's different ownership contract intact. Surface failed responses to callers rather than reporting completed work silently.

**Verification:** Inject each ENet rejection condition and count allocations/destructions; repeat an oversized response and verify stable memory. Confirm success and both broadcast variants never double-free.

### [BASE-NET-005] Identical message IDs admit incompatible SDK-dependent wire schemas
- **Severity:** Medium
- **Confidence:** High
- **Category:** API/ABI
- **Location:** `Source/Shared/Networking/Networking.hxx:46-56,79-82`; `Messages.hxx`; feature-gated serializers.
- **Affected scope:** Windows clients and servers built for differing Galaxy SDK schema groups and configured to use the same endpoint/key.

**Evidence / failure mechanism:** The frame contains an endian marker and a class-name hash, with no protocol/schema version. `UniqueClassId_Declare` in Shared_NoVer hashes only the class name. `SetLobbyDataMessage` and four related update schemas insert `fail_reason` only above `GALAXY_VERSION 11240`. `LeaveLobbyMessage` changes a bool to an enum at the leave-reason feature boundary; `ChatMessage` inserts a message type at SDK 1.110.0. Key challenge and acceptance carry no compatibility gate. Portable binary swaps numeric bytes; it does not reconcile member layouts.

**Reproduction conditions:** Connect a 1.124.0 client to a 1.125.2 server with matching key and perform a lobby-data update. The server reads the start of the key length as `fail_reason`, then shifts the string-length parsing. In the reverse direction a short/large misread or trailing data is possible. Versions spanning 1.133.0 also disagree on leave-reason width. Authentication can succeed before the mismatch is encountered.

**Impact:** Dropped requests, unresolved callbacks, misinterpreted fields and possible amplification of BASE-NET-001. This is a misconfiguration/compatibility failure, not a claim that all SDK versions must interoperate or that matching builds fail.

**Alternatives / recommended resolution:** Minimum: negotiate a protocol/schema fingerprint during handshake and explicitly reject incompatible peers. For intended cross-version operation, define version-independent wire enums/DTOs and adapt SDK APIs at the edges. Renaming message IDs for incompatible layouts is another option but still benefits from early handshake rejection.

**Verification:** Use paired encoders/decoders on both sides of 1.110.0, 1.124.0/1.125.2 and 1.133.0; assert either a supported round trip or deterministic rejection before application requests. Add opposite-endian archive fixtures without claiming big-endian Windows deployment support.

### [BASE-NET-007] Application packet queues bypass ENet's waiting-data budget
- **Severity:** Medium
- **Confidence:** High
- **Category:** Performance
- **Location:** `Source/Shared/Networking/Networking.hxx:124-125,142-153`; `Networking.cxx:123-132,146-167,219-226`.
- **Affected scope:** Windows client network worker and application-thread event pump.

**Evidence / failure mechanism:** Both concurrent queues are unbounded. The worker keeps pulling ENet events while the application processes them only through `Client::ProcessEvents` / `ProcessData`. ENet `peer.c:234-259` subtracts delivered packet bytes from `totalWaitingData`; moving the packet into Shared's queue therefore removes it from ENet's 32 MiB client waiting-data accounting while keeping its allocation alive. Every event, even an as-yet unparsed packet, refreshes `last_network_activity`. Outgoing producers likewise have no byte/count admission budget.

**Reproduction conditions:** Keep a valid session receiving relayed packets while the game pauses/slows `ProcessData` during loading or receives faster than it processes. Pings are handled by the worker/server, so the connection can stay active and the retained application queue continues growing. This is distinct from one malformed length tag and from persisted room history.

**Impact:** Memory pressure and large frame stalls when the backlog is drained; ENet's advertised waiting limit is not a process-memory bound.

**Alternatives / recommended resolution:** Track total queued bytes and events with configurable high-water limits. Define reliable-message overflow as a controlled disconnect/failure, and allow explicit dropping/coalescing only where protocol semantics permit it. Bound outbound admission too; a fixed item count alone poorly bounds variable-size packets.

**Verification:** Pause the Windows application pump while delivering size-compliant traffic; assert a bounded high-water mark and deterministic overflow behavior. Resume and check order, event fairness and exactly-once destruction during overflow, reconnect and shutdown.
