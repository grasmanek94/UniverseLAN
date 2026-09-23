# Fresh baseline review — NotificationParamScopeExtender.cxx

- Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`.
- Coverage: entire file, lines 1–34; static lifetime review.

## Specific checked notes

- Null input preserves a disengaged optional, distinct from a present empty string. Conversion returns null only for the disengaged state.
- C-string and `std::string` constructors make owned copies. Copy construction duplicates the storage, and pass-by-value assignment swaps it safely, including self-assignment.
- In the move constructor, the optional member is default-constructed before `swap`; it is not an uninitialized string. With the standard string allocator, the swap supports the declared nonthrowing move behavior.
- Conversion returns a pointer into owned storage. Traced its use during `std::invoke` while the bound callable/extender remains alive; it does not promise pointer validity after the callback.
- Default destructor releases the optional/string normally; no independent resource leak was found.

## Findings and limits

No confirmed defect in this file. Null, empty, long-string, copy/move, and assignment behavior were reasoned about statically, not tested. This class extends character-data lifetime, not listener-object lifetime (`BASE-CORE-001`).
