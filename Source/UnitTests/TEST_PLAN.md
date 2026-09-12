# Unit Test Plan

## Stage 1: implemented

| Production header | Test file | Covered behavior |
| --- | --- | --- |
| `Shared_NoVer/ConstHash.hxx` | `Shared_NoVer/ConstHashTests.cxx` | Known FNV-1a vectors, empty input, explicit byte counts, custom seed |
| `Shared_NoVer/ContainerGetByIndex.hxx` | `Shared_NoVer/ContainerGetByIndexTests.cxx` | Sequential access, empty containers, end boundary, fallback value |
| `Shared_NoVer/MemoryInputBuffer.hxx` | `Shared_NoVer/MemoryInputBufferTests.cxx` | Byte order and empty input EOF |
| `Shared_NoVer/MemoryInputStream.hxx` | `Shared_NoVer/MemoryInputStreamTests.cxx` | Pointer/span construction, embedded nulls, empty input EOF |
| `Shared_NoVer/ConcurrentQueue.hxx` | `Shared_NoVer/ConcurrentQueueTests.cxx` | Empty queue, lvalue/rvalue push, FIFO order |

## Remaining _NoVer headers

| Component | Production headers | Planned focus |
| --- | --- | --- |
| Shared string utilities | `SafeStringCopy.hxx` | Null pointers, zero/small buffers, truncation, binary data, bounded length, hex output |
| Shared achievement and statistics state | `AchievementData.hxx`, `AchievementsAndStatsContainer.hxx` | Defaults, dirty state, getters/setters, copy isolation, stat and metadata lookup behavior |
| Shared identifiers and message helpers | `GlobalUniqueID.hxx`, `Networking/MessageUniqueID.hxx`, `Networking/SendableEventMessage.hxx` | Monotonic uniqueness, explicit IDs, serialization, compile-time class identifier macro |
| Shared filesystem metadata | `filesystem_container_metadata.hxx` | Metadata conversion, defaults, copying, reset, timestamps |
| Shared filesystem paths | `filesystem_container_utils.hxx` | Traversal resistance, encoding round trips, empty directories, file enumeration, paths with spaces |
| Shared filesystem storage | `filesystem_container.hxx`, `filesystem_container_entry.hxx` | Temporary-directory lifecycle, file I/O, copying, metadata persistence, sharing and removal |
| Shared configuration and environment | `EnvUtils.hxx`, `DefaultConfigFiles.hxx` | Isolated environment variables, generated config contents, error handling |
| Shared system integration | `MachineInfo.hxx`, `SharedLibUtils.hxx`, `ConsoleCoutRedirector.hxx`, `CustomConsole.hxx` | Platform-guarded, deterministic portions only; avoid machine/global console side effects where impractical |
| Shared preprocessor support | `PreprocessorControlIf.hxx` | Compile-time macro expansion cases |
| Client generic scheduling | `Client_NoVer/Impl/DelayRunner.hxx` | FIFO execution, queue draining, callbacks added during execution |
| Client notification lifetime | `Client_NoVer/Impl/NotificationParamScopeExtender.hxx` | Null and string construction, copy/move/assignment, identity forwarding, pointer lifetime |
