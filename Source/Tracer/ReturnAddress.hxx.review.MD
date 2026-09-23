# Fresh review — ReturnAddress.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–18. Static review.

## Inspection notes
- MSVC uses the intrinsic declaration; GNU/Clang use return-address extraction at depth zero; unsupported compilers yield null.
- Traced delegating Trace constructors: they supply their caller address rather than letting the delegated constructor report its own frame. Optimized/inlined addresses remain diagnostic approximations.
- This reports a current return address, not an exception instruction pointer. Its use in fabricated minidump context is part of **BASE-SERVER-009**, not evidence of the original crash location.

## Result
No independent header defect. Non-Windows alternatives were inspected statically only.
