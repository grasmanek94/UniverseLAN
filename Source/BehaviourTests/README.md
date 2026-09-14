# BehaviourTests

BehaviourTests compare what an SDK client can observe from UniverseLAN with the
matching official GOG Galaxy runtime. They are compatibility contracts, not
UniverseLAN implementation tests. The authoritative lane is official GOG.

Start with [DEVELOPER_GUIDE.md](DEVELOPER_GUIDE.md) for the runnable tutorial,
then use these living registers:

| Document | Use it for |
| --- | --- |
| [BEHAVIOUR_TEST_PLAN.md](BEHAVIOUR_TEST_PLAN.md) | Architecture, comparison policy, and implemented scope. |
| [COVERAGE.md](COVERAGE.md) | Per-scenario status, observations, and comparison rules. |
| [BEHAVIOUR_DIFFERENCES.md](BEHAVIOUR_DIFFERENCES.md) | Live accepted differences, candidate mismatches, and matched baselines. |
| [TODO_PROGRESS.md](TODO_PROGRESS.md) | Completed milestones, remaining work, and required validation. |

## Non-Negotiable Rule

Host assertions may use only the selected SDK version's public `galaxy/`
headers and public calls, callbacks, and state queries. Do not include or
inspect UniverseLAN implementation headers, server state, protocol/configuration
files, generated files, or raw runtime output. Runner control files coordinate
processes only; they are never behavior evidence.

## Quick Start

The current framework supports x64 SDK `1.152.11` only. Build the framework
without registering live official-GOG tests:

```powershell
cmake -S . -B cmake-behaviour-15211-x64 -G "Visual Studio 18 2026" -A x64 -D BUILD_UNIVERSELAN_BEHAVIOUR_TESTS=ON -D LIMIT_VERSIONS="1.152.11"
cmake --build cmake-behaviour-15211-x64 --config Debug
```

Live comparisons are deliberately opt-in. After the local preflight described
in the guide succeeds, add
`-D ENABLE_UNIVERSELAN_GOG_BEHAVIOUR_TESTS=ON` to the configure command and
run the registered `behavior` label through `RunBehaviorCTest.cmake`.

Never commit or print credentials. The ignored
`Source/TestCommon/credentials.cmake` supplies two approved accounts plus the
client credentials. Matching official `Galaxy64.lib`, `Galaxy64.dll`, and
`GalaxyPeer64.dll`, an authenticated official environment, and network access
are also required. Missing prerequisites leave live tests unregistered rather
than making normal builds fail. The direct `IChat` scenario additionally needs
the approved official profiles to be friends with messaging privacy set to
friends. This is an external test-environment precondition, not a product
root-cause claim.

## How To Read A Result

Each scenario runs two synchronized lanes: UniverseLAN server plus two
UniverseLAN hosts, and two official-GOG hosts using the same profiles. Reports
compare normalized public traces. Opaque IDs, private tokens, timestamps, and
other server-assigned values are converted to local symbolic relationships.

`exact-equality` means the required normalized facts matched. An
`accepted-difference` is an intentionally narrow, documented exception that
still passes. A `candidate difference` remains a strict mismatch; it is not
accepted merely because it has been characterized. Current records include the
accepted GOG-service-state pair, accepted faster UniverseLAN lobby convergence,
and matched direct-chat and Advanced multiple-lobby baselines. See the
difference log for the exact public facts and reproduction commands.

Per-interface callback order is meaningful where a scenario says it is. Across
hosts or independent interfaces, only documented causal gates are compared;
elapsed timing and eventual-list retry counts are bounded diagnostics, not a
global ordering contract.

## Authoring And Validation

Author one focused Simple scenario at a time, characterize the official lane,
declare required/permitted/failing records and normalization rules in its
manifest and coverage entry, then add a strict contract only for stable public
facts. Advanced scenarios require characterized Simple prerequisites.

Temporary lobby and chat scenarios have special cleanup assumptions. Lobbies
must use a runner-generated private token, explicitly set public/joinable/capacity
before a peer joins, and prove all cleanup acknowledgements.
The public SDK has no chat-room delete API: chat participants exit after their
bounded callback contracts, and that bounded host exit is the agreed cleanup.
Details, diagnostics, artifact handling, and the required validation checklist
are in [DEVELOPER_GUIDE.md](DEVELOPER_GUIDE.md) and
[TODO_PROGRESS.md](TODO_PROGRESS.md).
