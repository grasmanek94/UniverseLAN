# Review: `ConfigDebug/UniverseLAN.ini`

## Finding — debug configuration retains the shared authentication key

- **Severity:** High
- **Evidence:** The debug base configuration commits the same fallback
  `[Authentication]` key as the normal configuration.
- **Impact:** A debug server left reachable with its default settings accepts
  the same known credential as every other checkout.
- **Suggested fix:** Generate a per-installation key for debug deployments too,
  or make the debug server refuse network exposure until an explicit key is
  supplied.
