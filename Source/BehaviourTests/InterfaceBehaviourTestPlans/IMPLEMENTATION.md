# Interface Behaviour Test Implementation

## Scope

Implement one focused public-SDK contract at a time. A host may use only the selected `galaxy/` headers, public calls, callbacks, and state queries. Runner control files establish causal gates but never provide behavior evidence.

## Method

1. Select only declarations available for the chosen build according to `Source/galaxy_sdk_features.cmake`.
2. Reuse an existing safe topology when possible. Public lobby probes create a nonjoinable tagged temporary lobby, explicitly configure it, observe joinability, and acknowledge both cleanup paths.
3. Emit normalized relationships instead of raw IDs, credentials, marker values, tokens, payloads, URLs, timestamps, or logs.
4. Characterize the official-GOG lane before making undocumented observations strict. Keep callback count/order, timing, and peer-routing details diagnostic unless the header or repeatable characterization supports a contract.
5. Add exact trace validation and exclude only documented diagnostic context from cross-lane comparison.

## Execution

Build the selected x64 SDK framework with `BUILD_UNIVERSELAN_BEHAVIOUR_TESTS=ON` and the matching `LIMIT_VERSIONS` value. Live comparisons additionally require the ignored credentials file, matching official runtime artifacts, an authenticated official environment, and `ENABLE_UNIVERSELAN_GOG_BEHAVIOUR_TESTS=ON`.

Run a focused CTest scenario through `RunBehaviorCTest.cmake`. Retain only its sanitized comparison report. A failed environment preflight or unresolved official runtime prerequisite is not a product difference.

## Result Updates

For every implemented plan, record the exact host/runner scenario, selected SDK gate, command, lane topology, sanitized observations, and verdict. `Pass` requires evidence from UniverseLAN server plus two clients and official GOG two clients. `Fail` requires a measured mismatch. Otherwise retain `Not-run`.

Update `Source/BehaviourTests/COVERAGE.md`, `TODO_PROGRESS.md`, `BEHAVIOUR_DIFFERENCES.md`, and `BEHAVIOUR_TEST_PLAN.md` whenever a live run changes a classification. Run `git diff --check` before committing documentation or source changes.
