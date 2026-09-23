# Fresh baseline review: Stats.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Entire file read, lines 1–504; source matches baseline. Windows static review, without builds or runtime reproductions.

## File-specific inspection

- Traced local/remote retrieval, request-listener registration/pop, stat mutations, achievement creation and persistence, visibility/name access, playtime caching, and achievement enumeration.
- Context: latest SDK `IStats.h` and `GalaxyApi.h` thread-safety contract; `UserImpl::GetGalaxyUserData`; Shared `IniData::SaveStatsAndAchievements`/reset; `AchievementsAndStatsContainer` and `AchievementData`; network request/response and `ProcessData` routing.
- `GetGalaxyUserData` creates a placeholder for unknown nonlocal IDs and returns the configured local object for self aliases. A missing remote user is therefore not a demonstrated null dereference at `GetStat*`. `GetAchievementData` also creates missing entries, so the apparent uninitialized-output branch of `GetAchievement` is not reachable through an ordinary missing name.
- Inspected every leaderboard method, including ascending/descending sort inputs, `forceUpdate`, global range indexes, around-user windows, selected-user requests, detail sizes, and count/getter calls. Definitions, retrieval, and updates all send failure; count is zero and getters are empty. There is no successful result population or sorting implementation. This is an explicit capability limit, not a confirmed wrong-sort/off-by-one defect. The SDK requires result getters inside a success callback, which this implementation never emits.
- Achievement indexes use a checked container helper; returned pointers are not claimed generally thread-safe. User-data/stat container synchronization is more limited than the interface promises, as detailed below.
- Float persistence writes/loads the union's integer representation in the Shared layer. The existing durable-persistence test compares float bits. This review does not mistake that representation for a numeric float-to-integer conversion or claim a reproduced Windows float-persistence failure. C++ union portability remains a UTIL concern.
- `Host/Stats.cxx` supplies meaningful restart persistence and peer propagation checks. It has no average-rate, persistence-failure, concurrent replacement, or successful leaderboard test path. Tests were read, not run.

## Findings

### [BASE-STORAGE-012] Stat and achievement accesses outlive their protecting locks

- **Severity:** High
- **Confidence:** High — concrete unsynchronized accesses and invalidation path; no runtime reproduction.
- **Category:** Concurrency / Memory Safety
- **Location:** `Source/Client/Impl/Stats.cxx:63–124,177–197,201–224`; remote replacement at `46–56,453–469`.
- **Affected scope:** Multithreaded SDK callers reading/updating stats or achievements while another API call or `ProcessData` updates the same user.

**Evidence:** `GetStatInt/Float` read `.i/.f` from a reference returned after `AchievementsAndStatsContainer::GetStat` releases its lock. Achievement getters/setters use a pointer returned after `GetAchievementData` releases its lock. `AchievementData` fields are plain values. A remote refresh performs `entry->stats = data->asuc`, whose assignment replaces the underlying maps under their locks. SDK `GalaxyApi.h:310–314` promises general API thread safety; ordinary numeric getters/mutators are not excluded pointer-returning APIs.

**Failure mechanism:** Thread A obtains a remote achievement pointer and pauses after container lookup. Thread B pumps a requested stats response and replaces the achievement map; removed entries can be freed. A resumes and reads a dead object. A simpler local path has `GetStatInt` reading the same union field that `SetStatInt` writes under a lock that A no longer holds. `SetAchievement` also changes `Dirty` outside the lock used by persistence, allowing races with dirty-state reset.

**Impact:** Data races, lost persistence updates, inconsistent achievement values, and possible use-after-free during remote refresh. This requires concurrent use of supported APIs; a strictly single-threaded game does not exercise this interleaving.

**Possible solutions:** Return value snapshots for numeric reads; execute complete mutations inside `run_locked_*`; or use immutable per-user snapshots with synchronized publication. Making individual fields atomic does not fix map replacement lifetime.

**Recommended resolution:** Keep the container lock through the entire field read/mutation and string copy, or return an owning value snapshot. Apply the rule to all internal borrowed references, coordinate with UTIL, and avoid holding those locks while invoking game listeners. Related user-data copy failure is BASE-STORAGE-022.

**Verification:** Use barriers to pause between lookup and use while another thread applies a remote response that removes the entry; verify no stale access with Windows ASan. Stress local read/set/store operations and inspect lock coverage, since ASan alone does not detect data races. Do not claim validation from a single-threaded roundtrip.

### [BASE-STORAGE-010] Average-rate updates add rates instead of averaging deltas

- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Client/Impl/Stats.cxx:87–91`, `UpdateAvgRateStat`.
- **Affected scope:** Games using average-rate statistics.

**Evidence:** The implementation stores `oldRate + countThisSession / sessionLength`. SDK `IStats.h:427–438` defines an average-rate update using a count delta and a session delta. The backing stat contains only the current scalar, with no accumulated count or duration.

**Failure mechanism:** Starting at zero, two equal updates `(10, 2)` produce 5 then 10. The rate over those intervals remains `(10 + 10) / (2 + 2) = 5`. Splitting one interval into two therefore changes the reported result. Unequal durations also require weighting that cannot be recovered from the stored scalar alone. Zero duration is an additional unvalidated input, but is not needed to demonstrate the defect.

**Impact:** Incorrect gameplay statistics and any decisions/displays based on them; results depend on how often a game submits updates.

**Possible solutions:** Persist cumulative numerator and denominator; introduce a dedicated average-rate record; or implement the SDK's documented aggregation semantics once independently verified. Simply averaging two rate values is incorrect for unequal durations.

**Recommended resolution:** Track both deltas under one lock and expose their ratio, with a migration policy for existing scalar values. Validate duration and finite inputs and define behavior for a zero accumulated duration. Preserve persistence across restart.

**Verification:** Compare a combined interval with equivalent split intervals, use unequal durations, and repeat after restart. Require equal rates within chosen floating-point tolerance; test zero/negative durations according to the chosen contract. No test executed in this review.

### [BASE-STORAGE-011] Store/reset acknowledge persistence despite disk failure

- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness / error handling
- **Location:** `Source/Client/Impl/Stats.cxx:127–161`; dependency `Source/Shared/IniData.cxx:835–913,929–944`.
- **Affected scope:** Enabled local stat/achievement persistence on Windows.

**Evidence:** `StoreStatsAndAchievements` and reset call void configuration helpers and always queue store success. The helper discards every `ini.SaveFile` result and clears achievement dirty flags at line 849 before saving at line 860. SDK `IStats.h:502–526` defines persistence and asynchronous completion. The inspected configuration defaults `SaveAchievementsAndStats` to true.

**Failure mechanism:** With a valid loaded profile, make the achievements INI unwritable, unlock an achievement, and store. The dirty flag is cleared, saving fails, and success is delivered. Restore write access and store again: the record is no longer dirty, so it is not necessarily re-emitted. Restart loses the unlock. Ordinary permission/read-only or full-volume failures suffice; intentionally disabling persistence is a different configuration policy.

**Impact:** Silent loss of progress and unreliable retry behavior. Peer propagation does not establish durable recovery of the local profile.

**Possible solutions:** Return aggregate/per-file persistence status; retain dirty records until confirmed durable; or commit all profile files transactionally with retry tracking.

**Recommended resolution:** Change the internal Shared helper to return meaningful status, acknowledge success only on the defined persistence boundary, and clear dirty state only for successfully committed versions. Account for mutations that occur while saving. Coordinate with NET's ownership of `IniData`; this ID covers the public caller and its end-to-end consequence.

**Verification:** Inject a write-denied achievement file with persistence enabled, assert failure callback, restore access and retry without re-unlocking, then restart and verify the unlock survives. Repeat for stats and reset. Existing healthy-filesystem restart tests are not sufficient for this failure path.
