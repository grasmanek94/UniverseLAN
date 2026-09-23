# Fresh baseline review: ConstHash.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Entire file read independently (43 lines). Static review only.

## Checked
- FNV-1a offsets/primes, unsigned wrap semantics, unsigned-byte conversion, zero-length seed behavior, recursive string termination, and loop/data equivalence.
- The string overload hashes through c_str and stops at an embedded NUL; binary data uses the explicit-size variants. Authentication/config identifiers are strings; cloud hashing uses the iterative explicit-size routine.
- KeyChallenge hashes a fixed eight-byte value with the recursive data routine. No unbounded network-payload recursion caller was found; arbitrary local config-string length remains a recursion/performance limit.
- UniqueClassId_Declare intentionally calls the 32-bit hash with name length as its initial value and returns it widened; it is not calling a length-taking hash API. Existing wire IDs depend on this choice.

## Result and limits
No confirmed arithmetic defect in this utility. FNV is non-cryptographic and collisions are possible; authentication protocol design is outside this utility assignment and is not reclassified merely from the primitive name. No benchmarks/tests executed.
