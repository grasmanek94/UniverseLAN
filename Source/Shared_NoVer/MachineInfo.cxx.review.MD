# Fresh baseline review: MachineInfo.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Entire file read independently (691 lines). Windows runtime focus; other platform guards inspected incidentally. No execution.

## Checked
- Followed adapter-buffer sizing/reallocation, both HeapAlloc outputs, HeapFree paths, registry handle closure, known-folder CoTaskMem allocation, module lookup flags, and dynamic GetModuleFileNameW growth.
- Traced working/library/executable/appdata/game/temp discovery, bounded-size JSON input, rootGameId/gameId fallback, ancestor walk termination, boot-file preference and default-creation callers in IniData.
- Examined GetUserName versus GetComputerName length conventions. The repository's normal build does not enable UNICODE globally; TCHAR-to-char casts are still a configuration/encoding limit, not the basis of the confirmed length finding.
- GetDebugID serializes selection, uses exclusive Windows opens, caches one ID and deliberately retains the successful handle for the process lifetime. It loses the handle value and has no release policy on DLL unload. No repeated-per-call leak or shutdown use-after-free is alleged; module-unload ownership deserves explicit documentation/RAII if unloading is supported.
- Known-folder memory and registry handles are released on normal paths; allocation/path exceptions are not uniformly RAII-protected. Adapter address-length/filter/order stability, registry value type/length validation, and unavailable-temp fallback merit fault-injection. These are recorded limits, not additional demonstrated normal-path failures.
- User identity consumers in IniData use the first available MAC and configurable machine-name/hash alternatives; IDs are compatibility identifiers, not cryptographic identities. Existing MachineInfo test checks process/path consistency only.

## Findings

### BASE-UTIL-013 — Computer names lose their final character before identity hashing
- **Severity:** Medium
- **Confidence:** High
- **Category:** Correctness
- **Location:** `Source/Shared_NoVer/MachineInfo.cxx:511-523`, successful GetComputerName branch
- **Affected scope:** `@ComputerName` / `@ComputerNameHash` persona and Galaxy ID configuration on Windows.

**Evidence / mechanism:** GetComputerName returns the number of copied characters excluding the terminator. The code nevertheless assigns `bufCharCount - 1` characters. In contrast, subtracting one is appropriate for the preceding GetUserName API. Machines named `GAMEPC1` and `GAMEPC2` both become `GAMEPC`, and a one-character name becomes empty. IniData hashes this truncated value for `@ComputerNameHash` (`IniData.cxx:573-578,601`).

**Impact:** Wrong display names and deterministic user-ID collisions for distinct machines with a common prefix; a one-character name can cause configured name-based initialization to fail. Default MAC-based IDs are unaffected, so this is a configuration-dependent Medium.

**Possible fixes:** Use the complete returned character count with explicit GetComputerNameA; or use GetComputerNameW plus deliberate UTF-8 conversion to avoid TCHAR-dependent interpretation.

**Recommended fix:** Read the full API-reported name, choose an explicit A/W encoding policy, and document that correcting name-derived IDs changes identities previously generated from truncated names. Reference consulted: https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-getcomputernamea .

**Verification:** Supply one-character and `GAMEPC1`/`GAMEPC2` API results; verify exact names and different derived IDs. Compare directly with GetComputerNameW on Windows. Not run.

### BASE-UTIL-014 — MAC output allocation is dereferenced without checking failure
- **Severity:** Low
- **Confidence:** High
- **Category:** Memory Safety
- **Location:** `Source/Shared_NoVer/MachineInfo.cxx:97-105`, `RetriveLocalMacAddress`
- **Affected scope:** MachineInfo construction during Windows initialization under allocation failure.

**Evidence / mechanism:** After successful adapter enumeration and counting a nonempty list, the second output-buffer HeapAlloc result is assigned to `*pszAddress` without a null check. The loop immediately performs pointer arithmetic and RtlCopyMemory into it. The input adapter allocation paths are checked; this output allocation is not.

**Impact:** Access violation instead of a controlled unavailable-MAC/error result under low-memory/fault-injection conditions. Low severity reflects the rare allocation-failure trigger, not uncertainty about the null dereference.

**Possible fixes:** Check the allocation and free the enumeration buffer before returning failure; or replace manual output allocation with a checked RAII buffer/vector and explicit status.

**Recommended fix:** Use a single ownership abstraction for both buffers, validate the nonzero allocation, and propagate an error without returning a positive address count. Keep caller fallback/diagnostics deliberate.

**Verification:** Force the output HeapAlloc to fail after GetAdaptersAddresses succeeds; verify no copy is attempted, no allocation is leaked, and initialization reports/falls back cleanly. Not run.
