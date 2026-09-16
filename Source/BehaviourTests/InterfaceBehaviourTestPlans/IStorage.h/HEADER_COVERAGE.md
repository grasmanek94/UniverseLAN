# `IStorage.h` Header Coverage

## Selected SDK

This matrix covers `Source/DLLs/1.152.11/galaxy/IStorage.h`. It is the authoritative selected-header inventory; declaration plans for older SDK snapshots remain historical and are not evidence for `1.152.11`.

| Selected declaration | Coverage status | Boundary / next action |
| --- | --- | --- |
| `GetDownloadedSharedFileCount` | Strict two-lane CTest | Initial no-open-download relation only; do not infer shared-file behavior. |
| `GetFileCount` | Two-lane characterization | Storage content is title/environment state; only zero/nonzero is retained. |
| `FileExists` | Two-lane characterization | One fresh portable relative path is queried without creation; only existence is retained. |
| `FileRead`, `GetFileSize`, `GetFileTimestamp`, `GetFileNameByIndex`, `GetFileNameCopyByIndex` | Fixture-blocked | Require a scenario-owned known file and, for indexed forms, an in-range index. |
| `GetDownloadedSharedFileByIndex`, `GetSharedFileName`, `GetSharedFileNameCopy`, `GetSharedFileSize`, `GetSharedFileOwner`, `SharedFileRead`, `SharedFileClose` | Fixture-blocked | Require a completed, scenario-owned shared-file download and its opaque ID. |
| `DownloadSharedFile` and its callbacks | Fixture-blocked | Require a controlled valid shared-file ID; success opens downloaded state. |
| `FileWrite`, `FileDelete`, `FileShare` and its callbacks | Mutation-blocked | Create, delete, or publish persistent storage state. Use only an isolated fixture with explicit cleanup. |
| `~IStorage` | Lifecycle-only | Interfaces are accessor-owned; direct destruction is invalid. Exercise only public `Storage()` and SDK shutdown. |

## Historical Plans

Plans `004`, `008`, `012`, `014`, `017`, `020`, `021`, `023`, `025`, `029`, `031`, `034`, `035`, `036`, and `038` describe removed overloads, callbacks, or parameter-name variants from older snapshots. They are intentionally not exercised by the selected `1.152.11` host.

## Safety Rules

- Never invent file names, shared-file IDs, indexes, or downloaded-file state as compatibility inputs.
- Do not enumerate, read, write, delete, share, synchronize, or retain file names, paths, contents, counts, IDs, credentials, timestamps, or runtime artifacts without an explicit isolated fixture.
- A fixture must be public-SDK-only, owned by the scenario, bounded, and fully cleaned up before any mutation or callback coverage is promoted.
