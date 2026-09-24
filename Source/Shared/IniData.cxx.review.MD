# Fresh review — IniData.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. All 980 lines read, including every constructor, INI section, getter and save/reset path. Windows-only runtime analysis; no actual user configuration or credentials read.

## Inspection notes
- Traced selection into `MachineInfo`: existing boot file precedence is working directory, library directory, executable directory, per-game AppData, temporary directory; fallback chooses per-game operating storage plus global/per-game boot file, or plain AppData without a game ID. This is selection, not layered merging.
- `GetPath` joins operating path with an already resolved base; normal absolute Windows paths replace the left operand, so this is not a demonstrated doubled-path defect. Absolute `GameDataPath`/`ServerDataPath` are deliberate path overrides. Environment game-data prefix is string concatenation, reread on each access, not a directory join.
- Wide `path::c_str()` reaches SimpleIni's Windows wide-file overload. The separate UTF-8 value conversion defect below does not imply that every non-ASCII boot-file location fails.
- ID construction masks to 56 bits and sets the user tag. Default/public LAN key is a deployment convention, not itself a finding. Port/count/tick/timeout values have weak upper-bound validation; tick zero is clamped in Server/Main. Extreme numeric overflow needs additional operational validation rather than an inflated severity claim.
- Float stat bit-pattern persistence was traced through `StatsDataContainer`; dependency serialization/play-time concerns are recorded as cross-owner context in NET.MD. Empty lobby/user-data values are not assumed to mean erased map entries without SDK evidence.

### [BASE-NET-008] Failed achievement saves clear the only retry marker
- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Shared/IniData.cxx:835-861`, `ClientIniData::SaveStatsAndAchievements`.
- **Affected scope:** Windows local achievement persistence; Stats and User callers.

**Evidence / failure mechanism:** For each dirty achievement, `ResetDirty()` executes before populating the temporary INI and before `SaveFile`; its return value is ignored. `AchievementData` setters mark dirty, and later saves emit only dirty achievement entries. `StatsImpl::StoreStatsAndAchievements` calls this method and then schedules success regardless of the file result.

**Reproduction conditions:** Unlock/change an achievement with saving enabled. Make `Achievements.ini` temporarily unwritable (read-only attribute, denied ACL, or a sharing-mode conflict), then save. Restore write access and save again without modifying the achievement. The second save reloads the old file and skips the now-clean achievement, permanently losing this update on restart.

**Impact:** Silent loss of unlocked/reset achievement state after a transient I/O failure. Stats/DLC/user-data saves also ignore failures, but the dirty-filtered achievement path uniquely suppresses later retry.

**Alternatives / recommended resolution:** Check INI mutation/save errors and acknowledge dirtiness only after successful persistence. Prefer a versioned snapshot and temporary-file/atomic-replace commit so concurrent edits remain dirty and partial writes cannot destroy prior state. Merely moving `ResetDirty` after an unchecked save is insufficient. An unconditional full achievement snapshot is simpler but still needs error propagation and transaction serialization.

**Verification:** Windows failure injection for denied write, short write and rename/sharing failure; retry without another setter, restart and verify saved state. Race two saves with an intervening achievement edit and ensure neither clears an unsaved revision. Proposed, not executed.

### [BASE-NET-009] UTF-8 INI path values are interpreted as Windows ANSI paths
- **Severity:** Medium
- **Confidence:** High
- **Category:** Portability
- **Location:** `Source/Shared/IniData.cxx:283-301,350-357`.
- **Affected scope:** Windows installations with non-UTF-8 active code page and non-ASCII configured storage paths.

**Evidence / failure mechanism:** `CSimpleIniA::SetUnicode()` returns UTF-8 values (vendor `SimpleIni.h:488-498`). `GameDataPath` and `ServerDataPath` are stored as `std::string` and implicitly converted to `std::filesystem::path` by `/`. MSVC narrow path conversion uses the native narrow encoding rather than treating these bytes as UTF-8. The wide file-open overload cannot repair a path already converted incorrectly.

**Reproduction conditions:** On a Windows process whose active code page is not UTF-8, put a UTF-8 path such as `C:\\UL-data\\é` in the INI and create the intended directory/config. Initialization addresses a different wide-character path (or fails conversion) instead of that directory. ASCII defaults and UTF-8-ACP processes do not trigger this case.

**Impact:** Missing configuration, storage in an unintended directory or initialization failure for legitimate localized paths. This is not a traversal/security finding.

**Alternatives / recommended resolution:** Decode UTF-8 configuration values explicitly into native paths (`char8_t`/UTF-8 path construction or a checked UTF-8-to-UTF-16 conversion). Define the environment prefix's encoding separately before combining it with the configured path. Using CSimpleIniW is an alternative if string consumers are consistently adapted.

**Verification:** Windows ACP 1252 and a non-Latin ACP, UTF-8 ACP, relative/absolute/UNC paths, accented/CJK characters and invalid UTF-8. Assert exact resolved paths and successful save/reload, not merely successful directory creation.

### [BASE-NET-010] First-run boot/config provisioning excludes plain AppData fallback
- **Severity:** Low
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Shared/IniData.cxx:193-237,296-298,435-436`.
- **Affected scope:** Standalone Windows server first run and clients without discoverable game metadata.

**Evidence / failure mechanism:** `CheckDefaultConfig` creates `UniverseLAN.ini` only if operating path equals `local_appdata_game_directory`. `MachineInfo` deliberately selects plain `local_appdata_directory` when no game ID exists. `CheckDefaultServerConfig` handles that plain directory for the server-specific config, but no corresponding boot-file creation exists. `CheckDefaultClientConfig` also recognizes only the per-game directory.

**Reproduction conditions:** Start with no boot INI in any search location and no discoverable `goggame-*.info`, with normal writable LocalAppData. Server gets a generated server Config.ini but missing boot INI; a client in the same selection mode also misses its client Config.ini. Repeated starts repeat load warnings and fallback behavior.

**Impact:** Broken first-run provisioning and warning dialogs; users cannot edit the expected generated settings until creating files manually. Normal execution may continue on defaults, so Low is appropriate.

**Alternatives / recommended resolution:** Have path selection explicitly return whether it selected a default-managed location, then provision absent files for both per-game and plain AppData (and a documented last-resort path policy). Alternatively add the missing plain-AppData condition consistently. Preserve existing-file precedence and report creation failures accurately.

**Verification:** Fresh Windows test directories with/without game metadata, with/without global boot file, and with a higher-priority working-directory INI; verify exact files created and absence of repeated missing-file warnings.

### [BASE-NET-011] Identity selectors validate the computer name instead of their selected identity
- **Severity:** Low
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Shared/IniData.cxx:492-505,565-586`.
- **Affected scope:** Optional Windows account-name and installation-ID selectors.

**Evidence / failure mechanism:** `@WindowsAccountName`/`@WindowsAccountNameHash` test `GetLocalMachineName()` then use `GetLocalUserName()`. The GalaxyID `@MachineIDHash` branch also tests machine name but hashes `GetInstallationID()`. MachineInfo collects these independently, and failed account/registry lookups leave empty strings.

**Reproduction conditions:** Choose an affected selector while the selected lookup fails but computer-name lookup succeeds, using an injected MachineInfo fixture or a Windows environment with the corresponding query denied. The empty value is accepted/hashed instead of rejected. The inverse lookup failure can reject a usable selected identity.

**Impact:** Empty/suffix-only names or repeated hash-derived IDs causing collisions and connection rejection. It is a local configuration/environment edge case, not remote identity takeover.

**Alternatives / recommended resolution:** Validate the exact retrieved value once and then use that value. An explicit documented fallback identity is possible, but must not silently hash missing data.

**Verification:** Independently fail each identity source and vary the configured selector; only the source actually selected should determine validation success.

### [BASE-NET-012] DLC ID parsing accepts a numeric prefix as a complete product ID
- **Severity:** Low
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Shared/IniData.cxx:649-663`.
- **Affected scope:** Windows `DLC.ini` loading.

**Evidence / failure mechanism:** `std::from_chars` status is checked but `result.ptr` is not compared with the input end. A key such as `123junk` parses successfully as 123; `0x123` parses the leading zero. The resulting entry can alias a real numeric product ID, with insertion order deciding duplicate handling.

**Reproduction conditions:** Load `[DLC]` with `123junk=true` and query product 123 (or combine it with `123=false`). No invalid-argument error is raised for the trailing characters.

**Impact:** Incorrect local DLC selection from a malformed/hand-edited configuration. No remote or license-security impact is claimed.

**Alternatives / recommended resolution:** Require both a clear error code and full input consumption, after any explicitly supported whitespace normalization. Supporting hexadecimal IDs would require a deliberate grammar rather than accidental decimal-prefix parsing.

**Verification:** Valid decimal extrema, overflow, blank key, negative key, `123junk`, `123 ` and `0x123`; reject every unsupported spelling without inserting an alias.

## Second-read addendum — original findings preserved

### [BASE-NET-008] Correction/evidence addendum: SaveFile success is weaker than a checked disk commit

- **Status / accounting:** Retained with a remediation correction and concrete concurrent-save evidence; no new finding count.
- **Severity:** Medium, unchanged.
- **Confidence:** High, static caller/vendor trace.
- **Category:** Correctness.
- **Location:** `Source/Shared/IniData.cxx:843-860,885-912`; vendored `simpleini-4.22/SimpleIni.h:389-396,2568-2600,2749`.
- **Affected scope:** Windows local persistence, including the achievement dirty-marker path and all four SaveFile calls.

**Evidence:** SimpleIni FileWriter discards `fputs`' return. Its Windows wide-path SaveFile opens with `wb`, calls Save, discards `fclose`'s result, and returns the serialization result. Save returns SI_OK after emitting content without checking the FILE error state. Thus the baseline recommendation to check SaveFile is necessary for open/conversion errors but insufficient for write/flush/close failures. Actual User SetUserData and Stats Store callers call the same Shared persistence method (`User.cxx:361-381`, `Stats.cxx:127-142`).

**Failure mechanism:** A file can open successfully yet fail while writing or at close; the caller can observe SI_OK despite missing/truncated bytes. Achievement dirtiness was already cleared. Independently, saves A and B can both load the old file; A snapshots a dirty achievement and clears it, B then sees it clean. If A commits and B later saves its older INI successfully, B removes A's update. Map-level locking does not serialize this load/snapshot/write transaction. This is an extension of the same persistence-acknowledgment defect, not a separate race count.

**Impact:** A return-code-only fix can still lose acknowledged data. The original read-only/ACL failure scenario remains valid; the correction adds post-open failures and successful-but-stale writes, without claiming they were reproduced.

**Possible solutions:** Serialize to memory then write through a checked Windows file/stream path; alternatively own the FILE lifecycle and check write/error, flush and close results. Use a serialized/revision-aware snapshot plus temporary-file replacement. If crash durability is promised, also define the required flush/durability contract.

**Recommended resolution:** Make a checked commit operation the condition for acknowledging exactly the saved revisions. Keep unsaved or concurrently modified achievements dirty. Propagate storage failure to the SDK operation rather than announcing unconditional success.

**Verification (proposed):** Inject post-open short-write/flush/close failures and force A-load/B-load/A-snapshot/B-snapshot/A-save/B-save ordering. Restart from the resulting file; verify no acknowledged update disappears and a retry without another setter persists it. Include Windows sharing-denied replacement and partial-file recovery.

### [ADD-NET-002] Plain INI persistence changes valid user-data strings on reload

- **Severity:** Medium.
- **Confidence:** High, complete setter/save/parser/load trace.
- **Category:** Correctness.
- **Location:** `Source/Shared/IniData.cxx:692-709,898-912`, UserData load/save; `Client/Impl/User.cxx:361-381`.
- **Affected scope:** Windows clients with SaveAchievementsAndStats enabled; legitimate local user-data values containing line breaks or significant edge whitespace.

**Evidence:** Save constructs default `CSimpleIniA`, calls only SetUnicode, and passes unencoded keys/values to SetValue. The default constructor has multiline disabled (`SimpleIni.h:470-474`) and quote parsing defaults false (1382). Save writes ordinary values verbatim unless those options apply (2722-2740). FindEntry ends a value at CR/LF and trims edge whitespace (1729-1755). Shared reload inserts those parsed values back into the user-data map. The actual User setter accepts the strings and immediately persists them; `AchievementsAndStatsContainer.cxx:119-128` preserves their bytes in memory. SDK 1.152.11 `IUser.h:617-628` permits a property value up to 4095 bytes and does not impose a single-line/trimmed-value precondition.

**Failure mechanism:** Call SetUserData with key `note` and value `first\nsecond=2` (where `\n` denotes an actual newline). The in-memory/network value remains one string. Saved UserData.ini contains `note = first` followed by `second=2`. A fresh ClientIniData loads `note` as `first` and adds a separate `second` entry. A value such as ` padded ` also loses spaces on reload. All inputs are non-null and well below documented size limits; no I/O failure, malformed network frame or hand-edited INI is needed.

**Impact:** Successful saves fail the user-data round-trip invariant and may introduce unintended properties. This is local data corruption, not a claim of credential/config-file takeover; the demonstrated path writes the dedicated UserData.ini. Similar key/section-name encoding and case-folding constraints deserve a broader persistence-format audit, but are not separately counted here.

**Possible solutions:** Introduce an explicitly tagged, reversible string encoding within INI, or store API data in a format with proper string escaping. Configuring matching multiline/quote parsing on both read and write can cover common values, but fixed multiline terminators, newline normalization and arbitrary keys need collision/compatibility analysis. Simply rejecting ordinary SDK-valid strings changes API behavior.

**Recommended resolution:** Use an unambiguous versioned encoding for API-owned user-data strings while accepting legacy files through a documented migration path. Preserve human-authored configuration semantics separately from byte-preserving data storage.

**Verification (proposed):** Through the public setter, persist and restart with LF, CRLF, leading/trailing spaces, `=`, section-looking text, literal `END_OF_TEXT`, Unicode and near-limit values. Compare exact value bytes, keys and entry counts before/after reload. Test old files and repeat saves; no round-trip experiment was executed in this review.
