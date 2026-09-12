# Unit Test Plan

## Stage 1: implemented

| Production header | Test file | Covered behavior |
| --- | --- | --- |
| `Shared_NoVer/ConstHash.hxx` | `Shared_NoVer/ConstHashTests.cxx` | Known FNV-1a vectors, empty input, explicit byte counts, custom seed |
| `Shared_NoVer/ContainerGetByIndex.hxx` | `Shared_NoVer/ContainerGetByIndexTests.cxx` | Sequential access, empty containers, end boundary, fallback value |
| `Shared_NoVer/MemoryInputBuffer.hxx` | `Shared_NoVer/MemoryInputBufferTests.cxx` | Byte order and empty input EOF |
| `Shared_NoVer/MemoryInputStream.hxx` | `Shared_NoVer/MemoryInputStreamTests.cxx` | Pointer/span construction, embedded nulls, empty input EOF |
| `Shared_NoVer/ConcurrentQueue.hxx` | `Shared_NoVer/ConcurrentQueueTests.cxx` | Empty queue, lvalue/rvalue push, FIFO order |
| `Shared_NoVer/SafeStringCopy.hxx` | `Shared_NoVer/SafeStringCopyTests.cxx` | Null pointers, zero/small buffers, truncation, binary data, bounded length, hex output |
| `Shared_NoVer/PreprocessorControlIf.hxx` | `Shared_NoVer/PreprocessorControlIfTests.cxx` | Compile-time and runtime true/false macro expansion |
| `Shared_NoVer/GlobalUniqueID.hxx` | `Shared_NoVer/GlobalUniqueIDTests.cxx` | Monotonic runtime identifiers |
| `Shared_NoVer/Networking/MessageUniqueID.hxx` | `Shared_NoVer/Networking/MessageUniqueIDTests.cxx` | Generated and explicit identifiers |
| `Shared_NoVer/AchievementData.hxx` | `Shared_NoVer/AchievementDataTests.cxx` | Defaults, setters, dirty-state reset |
| `Shared_NoVer/AchievementsAndStatsContainer.hxx` | `Shared_NoVer/AchievementsAndStatsContainerTests.cxx` | Achievement, stat, user-data, rich-presence, copy, play-time state |
| `Client_NoVer/Impl/DelayRunner.hxx` | `Client_NoVer/DelayRunnerTests.cxx` | Empty queue, FIFO callbacks, reentrant enqueueing |
| `Client_NoVer/Impl/NotificationParamScopeExtender.hxx` | `Client_NoVer/NotificationParamScopeExtenderTests.cxx` | Null/string construction, ownership, copy/move, identity helpers |
| `Shared_NoVer/EnvUtils.hxx` | `Shared_NoVer/EnvUtilsTests.cxx` | Missing and configured environment variables, game-data prefix |
| `Shared_NoVer/DefaultConfigFiles.hxx` | `Shared_NoVer/DefaultConfigFilesTests.cxx` | Nested directory creation and required default settings |
| `Shared_NoVer/filesystem_container/filesystem_container_metadata.hxx` | `Shared_NoVer/filesystem_container/filesystem_container_metadataTests.cxx` | Defaults, conversions, invalid values, reset state |
| `Shared_NoVer/filesystem_container/filesystem_container_utils.hxx` | `Shared_NoVer/filesystem_container/filesystem_container_utilsTests.cxx` | Filename escaping, traversal rejection, normalization, timestamps |
| `Shared_NoVer/filesystem_container/filesystem_container.hxx` | `Shared_NoVer/filesystem_container/filesystem_containerTests.cxx` | File lifecycle, binary I/O, sharing, removal |
| `Shared_NoVer/filesystem_container/filesystem_container_entry.hxx` | `Shared_NoVer/filesystem_container/filesystem_container_entryTests.cxx` | Metadata persistence, defaults, cache index state |
| `Shared_NoVer/Networking/SendableEventMessage.hxx` | `Shared_NoVer/Networking/SendableEventMessageTests.cxx` | Compile-time class-ID macro |
| `Shared_NoVer/SharedLibUtils.hxx` | `Shared_NoVer/SharedLibUtilsTests.cxx` | Invalid input before real-DLL loading |
| `Shared_NoVer/ConsoleCoutRedirector.hxx` | `Shared_NoVer/ConsoleCoutRedirectorTests.cxx` | Tee buffer forwarding |
| `Shared_NoVer/MachineInfo.hxx` | `Shared_NoVer/MachineInfoTests.cxx` | Process and known-path invariants |

## Remaining _NoVer headers

| Component | Production headers | Planned focus |
| --- | --- | --- |
| Shared custom console | `CustomConsole.hxx` | Windows console allocation has process-global side effects |
