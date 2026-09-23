# Fresh baseline review — Client.hxx

- Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`.
- Coverage: entire file, lines 1–41; static inspection only.

## Specific checked notes

- Checked MessageReceiver inheritance, virtual destruction, generated handler declarations, and the private Tick/public Start/Stop/ProcessEvents split against definitions.
- The class owns its thread and connection, but borrows `InterfaceInstances`; the owner must outlive every worker and handler. Explicit graph reset meets the worker-stop requirement before normal destruction.
- `std::atomic_bool` protects the run flag only. It does not guard the thread object, graph pointer, or lifetime during a callback-time reset.
- `GetConnection` returns a const borrowed reference; traced consumers use the connection's const `SendAsync` and atomic connection-state API. Const qualification does not imply deep immutability of internal queues.
- `std::thread`/atomic members prevent implicit copying; no unintended copyable thread-owner path was identified.

## Findings and limits

No independent header/signature defect. Cross-file lifetime failure is `BASE-CORE-003` in `UniverseLAN.cxx.review.MD`. SDK ABI validation concerns the returned interface implementations; this internal class layout is not the public Galaxy interface layout.
