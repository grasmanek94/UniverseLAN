# `typedef void (*ThreadEntryFunction)(ThreadEntryParam);`

## Declaration and applicability

- Header: `GalaxyThread.h`
- Exact declaration/signature:
```cpp
typedef void (*ThreadEntryFunction)(ThreadEntryParam);
```
- Observed snapshot availability: 1.140.0, 1.142.0, 1.144.1, 1.148.1, 1.148.2, 1.148.3, 1.148.5, 1.148.6, 1.148.7, 1.148.11, 1.148.14, 1.149.0, 1.150.0, 1.151.0, 1.152.1, 1.152.2, 1.152.6, 1.152.9, 1.152.11.
- Relevant build matrix gate: No dedicated feature gate; compile only where this exact declaration is present.
- Existing coverage: No grounded existing coverage identified in `Source/BehaviourTests/COVERAGE.md`.

## Fact boundary

- Documented fact: the selected public header declares the signature above. Any adjacent header precondition, return description, or callback statement may be asserted verbatim.
- Characterization required: result values, error category, callback delivery/count/order/thread, timing, cross-client visibility, pointer lifetime, and behavior for inputs not explicitly documented. Do not promote these observations to SDK guarantees.

## Expected observations

- Ownership, callback argument lifetime, allocation/free pairing or thread join/detach state, and concurrency are tested only where this signature documents them.
- Allocation success, callback thread, ordering, and unsupported ownership transfers are characterization, not expected outcomes.

## Public-SDK-only plan

1. Supply a minimal instrumented public callback/factory with caller-owned state, invoke `void` only through its documented consumer, and record calls without retaining raw addresses or payloads.
2. Use barriers and bounded joins only for documented thread operations; test allocation/free or spawn/join/detach lifetime pairing where exposed, not undocumented concurrent calls.
3. Keep callback state alive through the documented completion point, release it once, destroy listeners, and finish normal shutdown cleanup.

## Result placeholders

- UniverseLAN server + 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized callback-thread result: `<documented facts and characterization observations>`.
- Official GOG 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized callback-thread result: `<documented facts and characterization observations>`.
## Verdict and next step

- `[ ] Pass` `[ ] Fail` `[x] Not-run`
- Least-feasible next step: run the smallest valid `void` probe in both lanes, then add only the documented boundary or lifecycle observation needed to explain a difference.
