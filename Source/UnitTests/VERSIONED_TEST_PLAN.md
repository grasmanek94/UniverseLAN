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

## Next Batches

| Component | Planned focus |
| --- | --- |
| Shared value types | `GalaxyUserData`, chat and lobby values, feature-gated defaults and copying |
| Shared networking messages | Serialization round trips and feature-gated message fields |
| Client implementation | Error handling, listener registration, options, and in-memory state transitions without a real server |
| Other supported versions | Feature-boundary tests for the earliest and latest relevant SDK versions |
