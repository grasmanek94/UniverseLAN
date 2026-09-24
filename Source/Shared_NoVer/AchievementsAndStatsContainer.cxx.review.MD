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

## Thorough re-review addendum — retained IDs and concurrency/clock refinements (2026-09-24)

### BASE-UTIL-002 — retained, High / High confidence / Concurrency

**Location:** `Source/Shared_NoVer/AchievementsAndStatsContainer.cxx:14-19,25-30,33-54,57-83,109-117,138-146`; header `51-55,60-82`.

**Fresh evidence / exact schedules:** T1 finishes `GetStat`'s locked callback and pauses before the caller reads `.i`; T2 `SetStat` writes the same stored scalar; T1 reads without sharing the mutex. The concrete callers remain `Client/Impl/Stats.cxx:63-84`. For user data, T1 obtains a reference at `User.cxx:356`; T2 `SetUserData` updates/reallocates that same string; T1's `safe_copy_str_n` at 357 reads it after unlock. Friends' intermediate owning string at `Friends.cxx:483` does not fix the race: constructing it reads the source after the source getter released its lock. For snapshots, `UserHelloDataMessage.hxx:27-28` invokes the unlocked copy constructor during `Stats.cxx:136` or `ClientNetworkHandlers.cxx:85-89`, while another API thread can insert/update a source map. Assignment writes BootTime under the four map locks; `GetPlayTime` reads it under none.

**Counterevidence / clarification:** Assignment itself uses deadlock-avoiding eight-lock acquisition; the mutexes are recursive, so duplicate acquisition during self-assignment is not a demonstrated deadlock. `unordered_map` rehash does not itself invalidate references/pointers to elements. The demonstrated problem is concurrent value access/map copying (and erase/assignment where applicable), not a blanket "every insert invalidates pointers" claim. The SDK's pointer-returning API exclusions do not excuse scalar/Copy calls (`GalaxyApi.h:279-283`). No assertion that transport workers directly invoke these handlers is needed.

**Impact, options and recommendation:** Retain the original data-race/UB assessment. Value-returning internal reads must perform the copy while locked; locked achievement updates and a complete source snapshot lock are both needed. Give BootTime a coherent ownership/locking policy. Serializing an already detached immutable snapshot is different from serializing a live container; repair snapshot creation first, rather than adding an archive-only mutex that writers never take.

**Verification:** Barrier tests for the schedules above; preserve the already locked `FriendsImpl::GetRichPresenceByIndex:497-512` path as a positive comparison. Existing unit tests only exercise sequential access/copy. No concurrency test or sanitizer was run in this pass.

### BASE-UTIL-003 — retained, Medium / High confidence / Correctness

**Location:** `Source/Shared_NoVer/AchievementsAndStatsContainer.cxx:10,21-30,50-51`; header `31,45-54`.

**Clarification:** A negative elapsed duration first converts modulo 2^32, then participates in the unsigned addition. Depending on the persisted base, the final result may decrease or wrap to a large value; it is not necessarily huge for every one-second backward adjustment. This correction narrows the symptom, not the defect. Forward jumps and a foreign serialized BootTime still count clock skew as play time independently of BASE-UTIL-001.

**Options / recommendation / verification:** Keep accumulated duration separate from a local monotonic anchor and transmit a duration snapshot. Clamping is a limited compatibility workaround, not a cure for forward/remote skew. Verify both small backward deltas with a nonzero base and deltas exceeding that base, plus clock skew and normal elapsed progression. No runtime clock manipulation or test was performed.
