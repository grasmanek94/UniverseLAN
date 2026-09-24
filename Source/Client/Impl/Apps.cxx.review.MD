# Fresh baseline review: Apps.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Entire file read, lines 1–133; current source matches baseline. Fresh Windows-focused static inspection, without builds or runtime tests.

## File-specific inspection

- Reviewed construction/destruction, DLC installed/owned queries, language/language-code pointer and copy forms, tracing, and every feature guard.
- Compared `Source/DLLs/1.152.11/galaxy/IApps.h` and followed configuration getters in `Source/Shared/IniData.cxx`. `GetLanguage` and `GetLanguageCode` return `const std::string&` to members, so the `.c_str()` expressions at lines 44 and 80 do not refer to temporaries. No dangling-language-pointer defect is established in the normal lifetime.
- Copy forms take an owning string snapshot and use the bounded copy helper. `SafeStringCopy.hxx` checks null destination/zero capacity and terminates nonempty-capacity results. `Host/Apps.cxx` checks expected values, exact-fit and truncated copies, plus specific/global DLC ownership notifications; inspected, not executed.
- DLC enable-all and configured installed/owned equivalence are explicit emulator policy. The latest SDK distinguishes installed from owned and requires login for ownership checks, while this implementation consults `SignedIn()` only. Because local ownership is configured rather than a real-service entitlement check, this is recorded as a compatibility boundary, not an asserted exploitable entitlement bypass.
- `IsDlcOwned` forwards its specific listener on both success and failure. A null specific listener is accepted by the registrar's global-listener path. The deferred callback carries value-type product ID/result, avoiding borrowed data lifetime concerns.
- Generic deferred specific-listener cancellation is a CORE registrar dependency (same mechanism described in BASE-STORAGE-009); no separate duplicate Apps finding is counted. User sign-out state defects can indirectly make this API report ownership-check success after auth loss; see BASE-STORAGE-018.
- `IsDLCInstalled` may insert an unknown DLC and save configuration-backed state. Its shared map/persistence synchronization and failure handling belong to NET's `IniData` review; the facade does not independently serialize that access.

## Findings disposition and limitations

No independent file-local defect confirmed under the configured LAN-emulation behavior inspected. This is not proof of correctness. Per-product language distinctions, initialization-failure availability promised by the SDK, concurrent unknown-DLC queries, and all version ABI variants need broader validation; availability after partial Init failure is owned by CORE accessors/initialization.

Recommended verification: configured enabled/disabled/unknown DLC values; both ownership listener modes; language pointer validity while configuration remains alive; copy capacities 0, 1, exact fit, and truncated; ownership queries across the repaired sign-out state transition. No actual credentials are required.

## Source-first re-review addendum — 2026-09-24

Full `1-133` reread completed before baseline comparison. `IniData.cxx:717-725` returns member references, confirming stable normal-lifetime language pointers; copies own their temporary snapshot. Product IDs remain uint64_t throughout this facade and no narrowing/negative-index calculation occurs. Both IsDlcOwned result paths forward the supplied listener. Unknown-DLC insertion/save at `IniData.cxx:817-829` still needs NET synchronization/error handling. The latest SDK requires signed-in/logged-in ownership checks, whereas this configured emulator checks only SignedIn: retain this explicit compatibility boundary without inventing real-service entitlement security. No new local ID; partial-Init availability and generic queued listener cancellation remain CORE dependencies.
