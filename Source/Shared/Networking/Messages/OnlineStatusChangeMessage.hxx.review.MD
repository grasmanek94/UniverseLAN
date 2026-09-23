# Fresh review — OnlineStatusChangeMessage.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read all 25 lines.

## Inspection notes
- Fixed ID/bool payload initialized by both constructors. Server emits status around identity acceptance and disconnect; client updates user cache.
- Client-sent status does not directly mutate server state because its server handler performs no action beyond authentication/activity checking.
- ENet broadcast includes transport-connected peers; there is no confidential-presence guarantee merely because some receivers have not authenticated. Under the stated LAN model this is context, not a separately claimed leak vulnerability.

## Result
No schema-local finding established. Timeout retirement (BASE-NET-003) can delay/suppress status changes through the lifecycle caller.
