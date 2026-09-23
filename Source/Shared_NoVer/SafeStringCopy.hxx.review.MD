# Fresh baseline review: SafeStringCopy.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Entire file read independently (131 lines). Static review only.

## Checked
- String copies guard null/zero capacity before subtracting one, cap copied bytes before uint32_t conversion, write a terminator and count it. Binary copies cap to output length without appending a terminator.
- const-char string overload requires a valid NUL-terminated source and scans it with strlen; the annotation helper instead uses bounded_strlen/memchr. All require valid nonoverlapping source/destination extents as stated.
- Checked null pointer repair variants, bounded empty/null cases, exact-length binary input and bytes_to_hex unsigned-byte formatting/growth.
- Traced Storage/cloud/Stats/User/Friends callers. String lifetime races in Copy APIs arise before/while reading their source and are BASE-UTIL-002, not a bounds bug in this helper.

## Result and limits
No confirmed standalone helper defect. On x86 an extreme doubled reserve can wrap, but append still grows the string safely rather than indexing an undersized raw buffer; no memory-corruption claim is made. No tests/benchmarks executed.
