# Fresh review — GalaxyID.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read all 68 lines, including legacy IDType fallback.

## Inspection notes
- Hash uses the full 64-bit ID; equality/hash consistency is maintained. High byte denotes type; extraction/masking uses unsigned 64-bit operations.
- FromRealID masks the lower 56 bits before OR-ing the type. It intentionally does not validate enum values or forbid real ID zero; authorization/type checks belong to consumers.
- Formatter displays the real ID and enum name using owning temporary strings within the format call; no dangling formatter argument identified.
- Windows x86 hash truncation may increase collisions but is not an ID-equivalence error.

## Result
No file-local defect established. Invalid identity acceptance in server handlers is a separate contract question; no authentication claim is inferred from these helpers.
