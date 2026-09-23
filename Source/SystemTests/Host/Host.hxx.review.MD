# Fresh review — Host.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–238. Static review.

## Inspection notes
- Reviewed argument ownership, SDK import/export setup, factory versus free-function Api accessors and all feature-gated scenario declarations against implementation and dispatch.
- `pumpUntil` processes SDK data before checking completion, sleeps in bounded intervals and performs a final process/check after its deadline. Listeners are owned by the calling scenario while pumping.
- Timeouts are per operation; the runner supplies a separate overall scenario bound. A pump deadline is not a guarantee against a blocking SDK ProcessData call.
- The header's chat feature guards do not guarantee every type used in Chat.cxx exists; **BASE-SERVER-014** documents the concrete early-SDK mismatch.

## Result
No independent header defect. API accessors were assessed as test scaffolding, not reviewed as replacement SDK implementations.
