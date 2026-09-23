# Fresh baseline review: ContainerGetByIndex.hxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Entire file read independently (65 lines). Static review only.

## Checked
- Bounds checks precede iterator advance; value-return forms copy rather than expose temporary references; iterator-return forms leave lifetime/locking to the owner.
- Forced-zero enumeration excludes the selected key from later slots. If the key is absent, zero returns end and the virtual sequence is not a complete map enumeration.
- Traced Lobby and MatchmakingImpl::GetLobbyMemberByIndex: it tests IsMember(self) under the matchmaking lock and uses ordinary indexing when absent, so the incomplete absent-key virtual sequence is not a current caller defect.
- Stats/User/Friends by-index copies run inside container callbacks. Unordered-map order is unspecified but not required to be sorted by these helpers. Linked/map lookup is O(n), not O(1).

## Result and limits
No confirmed defect for current contracts/callers. Caller mutation can invalidate iterators; returned raw SDK pointers have separate documented lifetime restrictions. No runtime verification performed.
