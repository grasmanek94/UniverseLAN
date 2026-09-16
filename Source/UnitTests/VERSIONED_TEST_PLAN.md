# Version-Specific Unit Test Plan

## Implemented

| Version | Production header | Test file | Covered behavior |
| --- | --- | --- | --- |
| All configured SDK versions | `Shared/DynamicReturn.hxx` | `Shared/DynamicReturnTests.cxx` | Boolean and generic return conversion |
| All configured SDK versions | `Shared/GalaxyID.hxx` | `Shared/GalaxyIDTests.cxx` | Type bits, real-ID mask, hashing; uses `GALAXY_BUILD_FEATURE_GALAXYID_HAS_IDTYPE` for the SDK enum change |
| All configured SDK versions | `Shared/GalaxyIDSerialization.hxx` | `Shared/GalaxyIDSerializationTests.cxx` | Minimal save/load round trip |
| All configured SDK versions | `Shared/GalaxyUserData.hxx` | `Shared/GalaxyUserDataTests.cxx` | Initial profile state and hashed user lookup |
| SDKs with `HAS_ICHAT` | `Shared/ChatMessage.hxx` | `Shared/ChatMessageTests.cxx` | Constructor and default state; uses `HAS_ICHAT_MESSAGETYPE` for the signature and type API change |
| SDKs with `HAS_ICHAT` | `Shared/ChatRoom.hxx` | `Shared/ChatRoomTests.cxx` | Member uniqueness, messages, longest-message tracking, and read state; uses `HAS_ICHAT_MESSAGETYPE` for message construction |
| SDKs with `HAS_ICHAT` | `Shared/ChatRoomManager.hxx` | `Shared/ChatRoomManagerTests.cxx` | Create, lookup, remove, and duplicate copied-room handling |
| All configured SDK versions | `Shared/Lobby.hxx` | `Shared/LobbyTests.cxx` | Membership, capacity boundaries, lobby/member data, bounded member-message retrieval, and forced-local-member index ordering |
| All configured SDK versions | `Shared/LobbyManager.hxx` | `Shared/LobbyManagerTests.cxx` | Creation, configured state, lookup, and removal |
| All configured SDK versions | `Shared/SharedFileUtils.hxx` | `Shared/SharedFileUtilsTests.cxx` | File I/O by name and shared ID, bounded reads, cleanup, and invalid input handling |
| All configured SDK versions | `Shared/Networking/Messages/*.hxx` except marker messages | `Shared/Networking/*Tests.cxx` | Binary serialization round trips for all 30 substantive networking messages, including populated lobby, lobby-list, user-data, user-hello, and chat response graphs; feature-gated chat coverage follows `HAS_ICHAT` |
| All configured SDK versions | `Shared/Networking/Messages/EventConnect.hxx`, `EventDisconnect.hxx`, `ConnectionAcceptedMessage.hxx` | None | Empty marker messages have no serialized state to validate |
| All configured SDK versions | `Client/Impl/Errors.hxx` | `Client/ErrorsTests.cxx` | Generic error details and each public error type |
| All configured SDK versions | `Client/Impl/ListenerRegistrar.hxx` | `Client/ListenerRegistrarTests.cxx` | Registration, one-time and registered-listener execution, invalid-type rejection, request-listener duplicate rejection, removal, retained extra state, and unregister cleanup |
| All configured SDK versions | `Client/Impl/InitOptionsModern.hxx` | `Client/InitOptionsModernTests.cxx` | Default option values across feature-dependent fields |

## Next Batches

| Component | Planned focus |
| --- | --- |
| Shared value types | `GalaxyUserData`, chat and lobby values, feature-gated defaults and copying |
| Client implementation | Additional listener registration and in-memory state transitions without a real server |
| Other supported versions | Feature-boundary tests for the earliest and latest relevant SDK versions |

## Planned Work

1. Audit every existing unit test for meaningful behavioral coverage, including ownership, lifetime, boundary, and failure paths. In particular, extend `NotificationParamScopeExtender` coverage to prove that an extended `const char*` remains valid and retains its content after the original allocation is deleted.
2. Add isolated unit coverage for `Shared/IniData.hxx`, using the available root configuration directories where appropriate, and for currently uncovered `Tracer` components.
3. CMake test configuration is separated:
   - `-DBUILD_UNIVERSELAN_TEST_CASES=1` builds test cases and Enet tests only.
   - `-DBUILD_UNIVERSELAN_UNIT_TESTS=1` enables all unit tests and GoogleTest only.
   - `-DBUILD_ALL_TESTS=1` enables both options.
