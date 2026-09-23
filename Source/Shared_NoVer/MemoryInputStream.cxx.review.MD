# Fresh baseline review: MemoryInputStream.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Entire file read independently (31 lines). Static review only.

## Checked
- Pointer constructor maps null to an empty span even for nonzero size; nonnull pointer/span constructors delegate to the same buffer setup.
- buffer_ precedes stream_ construction; the returned istream reference targets the owned stream, not a temporary.
- Traced stack-scoped packet parsing and Cereal input errors. Input bytes are borrowed only for the parser lifetime; exceptions unwind stream/buffer before the packet guard frees bytes.

## Result and limits
No confirmed defect on current callers. Constructor noexcept also covers standard-library stream initialization; extraordinary initialization-allocation failure was not tested. No seeking or owning-byte-copy promise is made.
