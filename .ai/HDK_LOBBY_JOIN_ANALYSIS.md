# HDK Lobby Join Analysis

## Inputs

- Working baseline: GOG Galaxy `1.100.2` x64.
- Failing lane: UniverseLAN `1.100.2` x64.
- Raw traces remain under `C:\Users\Rafal\Desktop\HDK\UniverseLANData\Interceptor`.
- Scope-aware collapsed copies are under `C:\Users\Rafal\Desktop\HDK\UniverseLANData\Interceptor\collapsed`.
- `collapse-interceptor-traces.mjs` parses nested `+`/`-` scopes, preserves partial final scopes, and collapses only adjacent structurally identical scopes at every nesting level.

## Trace Result

The public lobby join itself succeeds in both lanes:

1. The client discovers and retrieves the game lobby.
2. `JoinLobby` receives `LOBBY_ENTER_RESULT_SUCCESS`.
3. The client sees a two-member roster.
4. The host receives `LOBBY_MEMBER_STATE_CHANGED_ENTERED` for the client.

The first material divergence occurs immediately afterwards. GOG automatically surfaces the joining peer's persona-data transition; HDK then reconciles the peer and starts reliable-immediate channel-zero bootstrap packets. UniverseLAN emits the lobby-member callback but never performs or completes the corresponding user-information retrieval/persona transition. HDK therefore never enters its peer reconciliation path and neither side issues a bootstrap `SendP2PPacket`; both continue polling empty queues.

This is not evidence of a failed `JoinLobby`, rejected P2P send, invalid remote ID, or networking listener issue.

## Implemented Fix

`Source/Client/Impl/Matchmaking.cxx` now requests user information when a remote member enters a lobby that the local user has joined. The request occurs before the member-state callback is delivered to the game.

This implements the selected SDK documentation for `IFriends::RequestUserInformation`: user information is retrieved automatically for fellow lobby members after entering a lobby or receiving another-member join notification. The request is excluded for self and for merely cached/listed lobbies.

## Test Artifact

- Built target: `universelan-client-x64-1.100.2`, Debug x64.
- Output: `C:\Development\AI\UL\bin\1.100.2\Debug\ulan-RealGalaxy64.dll`.
- The original output name was intentionally removed after the requested rename; `Galaxy64.dll` is absent from that build directory.
- Validation: `universelan-client-x64-1.100.2-unit-tests` passed all 10 tests.

## Retest Expectations

1. Repeat the HDK host/client lobby join with the renamed DLL deployed as the game requires.
2. On the host, after the remote `ENTERED` event, expect user-information/persona callbacks followed by peer reconciliation and the first reliable-immediate channel-zero send.
3. On the client, expect a corresponding packet-available/read transition rather than indefinite empty polling.
4. Preserve raw traces and rerun the scope collapser if the behavior differs.

## Follow-up If Still Failing

- Confirm the server responds to the automatic `RequestSpecificUserDataMessage` with the remote user's nickname/profile data.
- Compare the exact persona callback sequence and first bootstrap packet ordering, without retaining raw account IDs, names, payloads, or timestamps.
- Do not change P2P transport or friend semantics until the new traces show a later divergence.
