# Fresh baseline review — GalaxyApiFactory.cxx

- Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`.
- Coverage: entire file, lines 1–212; static inspection of legacy SDK contracts.

## Specific checked notes

- Compared `GalaxyImpl`'s virtual methods with 1.57.0 and 1.114.9 `IGalaxy.h`, including the added InitOptions, chat, utilities, storage, and custom-networking slots. Compiling against each version's base interface is useful source-level checking; emitted vtables were not inspected.
- `FACTORY_CALLTYPE` follows the matrix's historical calling-convention transition. Both the oldest and later factory contracts were read rather than assuming uniform semantics.
- Traced string overloads through `InitOptionsImpl` and the normalization constructor. The explicit `throwExceptions` argument is discarded; the options constructor also discards the old SDK field, and `ErrorManager::GetLastError` always returns null. Full defect `BASE-CORE-005` is in `GalaxyDLL.cxx.review.MD`.
- Factory pointer publication/reset uses ordinary process-static pointers without synchronization; the error-manager allocation is never reclaimed here. Concurrent creation/reset and DLL-unload ownership remain explicit validation/architecture limits, without an additional concurrency ID.
- Deleting `GalaxyImpl` alone does not shut down the global runtime. Normal `Factory.cxx::Shutdown` invokes runtime shutdown first, which was accounted for when evaluating ownership.

## Confirmed finding

### BASE-CORE-005 — Factory overloads ignore exception settings and cannot publish last errors

- **Severity:** Medium
- **Confidence:** High
- **Category:** API/ABI
- **Location:** `Source/Client/GalaxyApiFactory.cxx:40–65,138–139,154–156`.
- **Affected scope:** Legacy factory SDK initialization/error retrieval. Canonical full boundary analysis: `GalaxyDLL.cxx.review.MD`; counted once.

**Evidence**

Both legacy string overloads accept `throwExceptions` but leave it unused. The error manager always returns null, as does the forwarded facade GetError. SDK 1.57.0 and 1.114.9 document the boolean's exception-control purpose, and the later SDK provides last-error retrieval for the nonthrowing path.

**Failure mechanism**

Call Init or InitLocal with exceptions disabled and a configuration whose server host cannot resolve. The internal Client constructor throws, and the common Init wrapper rethrows without consulting the ignored flag. Querying either error access path still reports no error.

**Impact**

Recoverable initialization errors cross the game's expected nonthrowing SDK boundary; conventional error handling cannot recover or diagnose correctly.

**Possible solutions**

Pass the requested policy into normalized initialization and translate failures into a thread-local error store, or consolidate all legacy adapters through one policy-aware boundary.

**Recommendation**

Make both legacy overloads preserve policy and share error state with the public factory error manager; pair this change with the normalizer/runtime fix. Keep old throwing behavior compatible with SDK exception interfaces when explicitly enabled.

**Verification**

For representative pre-options and legacy-options SDKs, force synthetic DNS failure with both flag values and verify error retrieval, thread independence, and exception type/policy. Proposed only; no execution occurred.

### BASE-CORE-007 — GetInstance creates an object in SDK versions where it must be a query

- **Severity:** Low
- **Confidence:** High
- **Category:** API/ABI
- **Location:** `Source/Client/GalaxyApiFactory.cxx:166–174`.
- **Affected scope:** Later factory SDK contracts, explicitly verified at 1.64.0 and 1.114.9.

**Evidence**

`GetInstance` allocates `new GalaxyImpl()` when `instance` is null. SDK 1.64.0 and 1.114.9 `GalaxyFactory.h:30–39` require the existing instance or null; their `CreateInstance` is the separate creating operation. SDK 1.57.0 instead explicitly allows `GetInstance` to create, so the implementation is only correct for that older contract.

**Failure mechanism**

An application probes `GalaxyFactory::GetInstance()` before initialization or after `ResetInstance()`. It receives a newly allocated non-null facade instead of null, although the backing runtime interfaces may still be absent. Header wrappers such as `Shutdown` also lose their intended null/no-op guard and can enter `InterfaceInstances::reset`, which initializes configuration/tracing through `internal_reset` even when no runtime was started.

**Impact**

Initialization-state checks become misleading and nominally passive queries/shutdown probes gain allocation or configuration side effects. The ordinary initialize/use/shutdown path generally still works, so severity is Low.

**Possible solutions**

1. Gate creating versus non-creating `GetInstance` behavior with the historical SDK capability.
2. Keep `CreateInstance` as the only allocator for later versions and preserve legacy behavior only where documented.

**Recommendation**

Represent the contract transition in the existing feature mechanism and implement the two query behaviors explicitly. Avoid changing the older ABI's documented creation semantics.

**Verification**

In fresh processes, check `GetInstance` before create, after create, and after reset for 1.57.0, 1.64.0, and 1.114.9. Later versions must return null without creating runtime/config state; the oldest creating contract should remain intact. Not executed.
