# Fresh review — Host/P2P.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–202. Static review.

## Inspection notes
- Traced two-peer exchange, three-peer directed routing/observer silence, channel 255 with a 1200-byte patterned payload, post-leave routing denial and offline metadata queries.
- Positive receives verify sender, reported size and bytes. Payloads contain binary NUL/high values and channels are uint8_t, matching the public interface.
- Three-peer and leave scenario manifests were read as scheduling context. Gates order send attempts and leave observations, but the 750 ms quiet window is a finite negative observation, not proof against arbitrary delay.
- Post-leave send ignores the scheduling return intentionally to allow either local rejection or server drop. The examined client does queue that route, so the scenario can exercise the server's shared-lobby gate; a no-send mutation would require a positive control to distinguish it.
- Offline-recipient currently checks GetConnectionType/GetPing only; it is not an offline packet-delivery test. These scenarios address user IDs, not the lobby-directed bypass **BASE-SERVER-004**.

## Result
No independent confirmed implementation defect. Recommended expansion is a member/outsider/post-leave lobby-ID routing test plus explicit packet-delivery barriers where possible.
