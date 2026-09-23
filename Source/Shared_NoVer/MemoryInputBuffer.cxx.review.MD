# Fresh baseline review: MemoryInputBuffer.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Entire file read independently (22 lines). Static review only.

## Checked
- Empty/null spans use null get pointers without computing null + size. Nonempty spans install begin/current/end consistently.
- The const_cast satisfies streambuf's char-pointer interface but no put area is installed; normal extraction reads without mutating the source. Mismatching putback uses the default failure path.
- Traced Cereal sequential sgetn use in ProcessEvent/ProcessEventFor. Packet bytes remain owned until the surrounding packet cleanup guard after parsing, so no reachable packet-buffer use-after-free is established.

## Result and limits
No confirmed defect under valid span lifetime/extent. Seeking is unsupported and input is non-owning; inspected callers do not seek or retain the buffer beyond packet lifetime. Empty/NUL-byte unit tests were read, not run.
