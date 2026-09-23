# Fresh review — EventConnect.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read all 12 lines.

## Inspection notes
- Marker type has a class ID but no serializer; it is constructed from an ENet connect event, excluded from wire-dispatch cases.
- Client reports transport connectivity; server creates application peer state and sends the challenge. It does not itself mean authentication completed.
- No owned packet or peer lifetime is represented in the marker; the separate ENet event pointer supplies context.

## Result
No file-local defect established. Peer-slot reuse and queued-event generation semantics are discussed in Networking.cxx and NET.MD.
