# Fresh review — FileRequestMessage.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read all 34 lines.

## Inspection notes
- Dual request/response includes request ID, share ID, filename and full byte vector. Request constructor leaves response fields empty; all defaults are defined.
- Server first looks up ID, then optional filename; client ordinarily requests by ID. Response filename reaches client storage container and can throw on rejected paths.
- No independent success flag distinguishes empty successful file data from failure; actual Client Storage currently rejects zero-length payloads. That API/protocol contract limitation is recorded for the STORAGE owner rather than inventing missing byte data.
- Whole-file vector transfer must fit ENet's 32 MiB packet cap including framing; no streaming protocol exists here.

## Result
No additional schema-local finding counted. Decoder limits and exception boundaries are BASE-NET-001/002; zero-byte and failure-response policy need caller resolution.
