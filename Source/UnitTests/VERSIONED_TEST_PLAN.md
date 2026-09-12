# Version-Specific Unit Test Plan

## Implemented

| Version | Production header | Test file | Covered behavior |
| --- | --- | --- | --- |
| All configured SDK versions | `Shared/DynamicReturn.hxx` | `Shared/Versioned/DynamicReturnTests.cxx` | Boolean and generic return conversion |
| All configured SDK versions | `Shared/GalaxyID.hxx` | `Shared/Versioned/GalaxyIDTests.cxx` | Type bits, real-ID mask, hashing; uses `GALAXY_BUILD_FEATURE_GALAXYID_HAS_IDTYPE` for the SDK enum change |
| All configured SDK versions | `Shared/GalaxyIDSerialization.hxx` | `Shared/Versioned/GalaxyIDSerializationTests.cxx` | Minimal save/load round trip |
| All configured SDK versions | `Shared/GalaxyUserData.hxx` | `Shared/Versioned/GalaxyUserDataTests.cxx` | Initial profile state and hashed user lookup |
| SDKs with `HAS_ICHAT` | `Shared/ChatMessage.hxx` | `Shared/Versioned/ChatMessageTests.cxx` | Constructor and default state; uses `HAS_ICHAT_MESSAGETYPE` for the signature and type API change |
| SDKs with `HAS_ICHAT` | `Shared/ChatRoom.hxx` | `Shared/Versioned/ChatRoomTests.cxx` | Member uniqueness, messages, longest-message tracking, and read state; uses `HAS_ICHAT_MESSAGETYPE` for message construction |
| SDKs with `HAS_ICHAT` | `Shared/ChatRoomManager.hxx` | `Shared/Versioned/ChatRoomManagerTests.cxx` | Create, lookup, remove, and duplicate copied-room handling |
| All configured SDK versions | `Shared/Lobby.hxx` | `Shared/Versioned/LobbyTests.cxx` | Membership, capacity boundaries, lobby/member data, and bounded member-message retrieval |
| All configured SDK versions | `Shared/LobbyManager.hxx` | `Shared/Versioned/LobbyManagerTests.cxx` | Creation, configured state, lookup, and removal |
| All configured SDK versions | `Shared/SharedFileUtils.hxx` | `Shared/Versioned/SharedFileUtilsTests.cxx` | File I/O by name and shared ID, bounded reads, cleanup, and invalid input handling |
| All configured SDK versions | `Shared/Networking/Messages/*.hxx` except marker messages | `Shared/Versioned/Networking/*Tests.cxx` | Binary serialization round trips for all 30 substantive networking messages, including populated lobby, lobby-list, user-data, user-hello, and chat response graphs; feature-gated chat coverage follows `HAS_ICHAT` |
| All configured SDK versions | `Shared/Networking/Messages/EventConnect.hxx`, `EventDisconnect.hxx`, `ConnectionAcceptedMessage.hxx` | None | Empty marker messages have no serialized state to validate |
| All configured SDK versions | `Client/Impl/Errors.hxx` | `Client/Versioned/ErrorsTests.cxx` | Generic error details and each public error type |
| All configured SDK versions | `Client/Impl/ListenerRegistrar.hxx` | `Client/Versioned/ListenerRegistrarTests.cxx` | Registration, one-time and registered-listener execution, invalid-type rejection, request-listener duplicate rejection, removal, retained extra state, and unregister cleanup |
| All configured SDK versions | `Client/Impl/InitOptionsModern.hxx` | `Client/Versioned/InitOptionsModernTests.cxx` | Default option values across feature-dependent fields |

## Next Batches

| Component | Planned focus |
| --- | --- |
| Shared value types | `GalaxyUserData`, chat and lobby values, feature-gated defaults and copying |
| Client implementation | Additional listener registration and in-memory state transitions without a real server |
| Other supported versions | Feature-boundary tests for the earliest and latest relevant SDK versions |

## Planned Work

1. Audit every existing unit test for meaningful behavioral coverage, including ownership, lifetime, boundary, and failure paths. In particular, extend `NotificationParamScopeExtender` coverage to prove that an extended `const char*` remains valid and retains its content after the original allocation is deleted.
2. Add isolated unit coverage for `Shared/IniData.hxx`, using the available root configuration directories where appropriate, and for currently uncovered `Tracer` components.
3. Separate CMake test-case and unit-test configuration:
   - Rename `BUILD_TEST_CASES` to `BUILD_UNIVERSELAN_TEST_CASES` throughout the repository. `-DBUILD_UNIVERSELAN_TEST_CASES=1` builds only test cases.
   - Add `-DBUILD_UNIVERSELAN_UNIT_TESTS=1` to enable all unit tests.
   - Add `-DBUILD_ALL_TESTS=1` to enable both options.
