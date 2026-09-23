# Fresh baseline review — UniverseLAN.hxx

- Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`.
- Coverage: entire file, lines 1–137; static review only.

## Specific checked notes

- Enumerated every `InterfaceInstances` owner and its feature guard; compared the members with allocation/reset code and client/game-server accessors.
- The SDK interface objects are individually owned by `unique_ptr`; other implementations borrow the graph/registrar, so API-returned pointers are valid only during the corresponding runtime lifetime.
- Checked the include cycle with `Client.hxx`: the forward declaration precedes use and `#pragma once` prevents recursive expansion. Complete implementation types are included later for ownership/destructor definitions.
- Declaration order matters: implicit member destruction removes `delay_runner` and `notification` before interfaces such as custom networking. The explicit reset uses a safer order. The destructor stops only the ENet client before member destruction; implicit teardown of a still-running runtime and Windows loader-lock behavior need targeted validation.
- The `init(..., bool is_gameserver = false)` default is correct for the client but is wrongly used by the game-server caller (`BASE-CORE-004`).

## Findings and limits

No independent declaration/ABI defect was confirmed. Runtime graph destruction during active callbacks is fully documented as `BASE-CORE-003` in `UniverseLAN.cxx.review.MD`. This header's ownership declarations participate in that finding; they are not counted again. Export/vtable layout was inspected at source level only, without binary ABI validation.
