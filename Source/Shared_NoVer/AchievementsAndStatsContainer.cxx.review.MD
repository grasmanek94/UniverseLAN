# Fresh baseline review: AchievementsAndStatsContainer.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Entire file read independently (172 lines). Static review; no build/test execution.

## Checked
- Followed construction, copy/assignment, all map insert/update/erase paths, lock release points, and elapsed-time arithmetic.
- Assignment uses deferred locks and `std::lock`; mutexes are recursive, so self-assignment is not alleged to deadlock merely because the same mutex is acquired twice.
- Traced Stats scalar access and achievement mutation, User/Friends Copy access, INI save/reset, and hello/request snapshot creation and receipt.
- Examined `GalaxyApi.h:279-283`: the SDK generally promises thread safety, with explicit exclusions for pointer-returning methods. Findings below use scalar/Copy/snapshot operations, not consumers retaining excluded API pointers.

## Findings

### BASE-UTIL-002 — Locks do not cover value reads, achievement mutation, or snapshot construction
- **Severity:** High
- **Confidence:** High
- **Category:** Concurrency
- **Location:** `Source/Shared_NoVer/AchievementsAndStatsContainer.cxx:14-19,57-83,109-117,138-146`; related header `serialize` and callback APIs
- **Affected scope:** Supported parallel stats, user-data, rich-presence, and snapshot operations.

**Evidence / mechanism:** The copy constructor copies all maps without acquiring source mutexes. GetStat/GetUserData/GetRichPresence return references after their callback lock is released, and GetAchievementData returns a mutable pointer. `StatsImpl::GetStatInt` reads `.i` after unlock while `SetStatInt` can write it under a lock; locking only the writer is insufficient. `UserImpl::GetUserDataCopy:348-357` copies an unlocked string while `SetUserData` can reallocate it. `FriendsImpl::GetRichPresenceCopy:477-484` has the same gap. `StatsImpl::SetAchievement:104-112` mutates achievement fields outside the mutex used by INI save/reset. `StoreStatsAndAchievements:134-136` and connection acceptance construct a UserHelloDataMessage by the unlocked copy constructor while another supported API thread can update/insert a stat.

**Impact:** Data races and undefined behavior, inconsistent snapshots, and possible crashes while copying changing strings/maps. Both objects can remain alive for the entire interleaving. No post-Shutdown or prohibited retained-pointer lifetime is needed or claimed. Network handlers run through ProcessData, not automatically on the transport worker; a concurrent API caller is the relevant second thread.

**Possible fixes:** Return owned value snapshots; add locked value-copy and achievement-mutation operations; or make callers execute complete operations inside callbacks. Snapshot copy/serialization needs an agreed all-map lock policy. Changing just the copy constructor leaves escaped-reference reads unsafe.

**Recommended fix:** Introduce value-returning internal reads and locked achievement updates, and acquire the source's four mutexes with a deadlock-safe multi-lock for a coherent snapshot. Ensure BootTime reads/assignment share a lock or immutable snapshot representation. Preserve documented non-thread-safe public pointer APIs separately if compatibility requires them.

**Verification:** Coordinate parallel SetStat/GetStatInt, SetUserData/GetUserDataCopy, SetAchievement/save, and map insertion/snapshot construction using barriers; run race instrumentation where supported. Confirm Copy APIs never access the source after unlocking. Not executed.

### BASE-UTIL-003 — Play time depends on adjustable and remote wall clocks
- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Shared_NoVer/AchievementsAndStatsContainer.cxx:10,25-30,50-51`; header `time_point` and serialization
- **Affected scope:** Local persisted play time and remote user-time reporting.

**Evidence / mechanism:** BootTime is a system-clock timestamp, transported to peers. GetPlayTime subtracts it from the receiving machine's system clock and converts signed seconds directly to `uint32_t`. A backwards clock adjustment larger than the session, or a sender clock ahead of the receiver, yields a negative duration and modular unsigned conversion. Forward clock changes are counted as play time. INI save persists the resulting value.

**Impact:** Inflated/wrapped totals or incorrect elapsed time; this remains after fixing BASE-UTIL-001.

**Possible fixes:** Use a steady-clock session anchor locally and transport accumulated durations; alternatively clamp wall-clock deltas, which prevents wrap but not skew or forward jumps.

**Recommended fix:** Separate persisted elapsed seconds from a local steady-clock anchor. Transmit a duration snapshot rather than a foreign wall-clock anchor, and define whether remote play time continues advancing. Version the wire representation if changed.

**Verification:** Inject backwards/forwards wall-clock changes and two peers with different system clocks; elapsed play time should remain monotonic and independent of skew. Test numeric boundary handling. Not executed.
