# Advanced Behaviour Scenarios

`multiple-lobby-membership-and-message-isolation` is the opt-in x64 `1.152.11`
contract. It first characterizes official GOG only, then compares the four-host
UniverseLAN/GOG run. It creates and joins `L0` and `L1` back-to-back before
`ProcessData`, explicitly sets each lobby public, joinable, and capacity two,
and checks symbolic per-lobby message isolation.

The public `ILobbyMessageListener`/`GetLobbyMessage` header has no message-type
field. The scenario records that unavailable public field while validating the
public callback, sender, byte payload, and symbolic lobby relation. Follow the
authoring and validation rules in [`../../DEVELOPER_GUIDE.md`](../../DEVELOPER_GUIDE.md)
and record future runs in [`../../TODO_PROGRESS.md`](../../TODO_PROGRESS.md).
