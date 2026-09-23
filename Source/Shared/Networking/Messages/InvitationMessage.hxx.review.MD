# Fresh review — InvitationMessage.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read all 36 lines.

## Inspection notes
- Request ID, user ID and owned connection string are initialized/serialized consistently. User ID means target outbound, authenticated sender after server relay.
- Server requires authentication and resolves the target before replacing sender; nonexistent target currently results in no response, a caller/protocol-completion concern.
- Connection string is application data in this message; no shell/process execution occurs here. Client auto-accept is configurable LAN behavior and is not alone evidence of injection.

## Result
No independent schema-local finding. Dynamic-string decoding and trusted-server consumption still require the boundary protections covered elsewhere.
