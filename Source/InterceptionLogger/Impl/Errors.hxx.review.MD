# Fresh baseline review — Impl/Errors.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–60. Static Windows review; shallow serious-defect scope.

## Checked
- Checked IError inheritance, virtual destructor, const accessors and getter alias returning `const IError*` with the SDK calling convention.
- Traced HasError as a wrapper extension rather than an SDK override; it does not change the inherited method signatures.
- Ownership of the real error remains with the SDK and changes with last-error state; this class owns only a function wrapper.

## Result
No independent serious declaration defect confirmed. Error lifetime/null-state behavior is limited by the real SDK contract and adjacent implementation, not guaranteed by this header.
