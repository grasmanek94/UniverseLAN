# `typedef void* (*GalaxyRealloc)(void* ptr, uint32_t newSize, const char* typeName);`

## Declaration and applicability

- Header: `GalaxyAllocator.h`
- Exact declaration/signature:
```cpp
typedef void* (*GalaxyRealloc)(void* ptr, uint32_t newSize, const char* typeName);
```
- Observed snapshot availability: 1.121.2, 1.124.0, 1.125.2, 1.126.1, 1.127.0, 1.128.3, 1.130.0, 1.131.3, 1.132.1, 1.133.0, 1.133.6, 1.135.0, 1.139.5, 1.139.6, 1.139.9, 1.140.0, 1.142.0, 1.144.1, 1.148.1, 1.148.2, 1.148.3, 1.148.5, 1.148.6, 1.148.7, 1.148.11, 1.148.14, 1.149.0, 1.150.0, 1.151.0, 1.152.1, 1.152.2, 1.152.6, 1.152.9, 1.152.11.
- Relevant build matrix gate: GALAXY_BUILD_FEATURE_ALLOCATOR.
- Existing coverage: No grounded existing coverage identified in `Source/BehaviourTests/COVERAGE.md`.

## Fact boundary

- Documented fact: the selected public header declares the signature above. Any adjacent header precondition, return description, or callback statement may be asserted verbatim.
- Characterization required: result values, error category, callback delivery/count/order/thread, timing, cross-client visibility, pointer lifetime, and behavior for inputs not explicitly documented. Do not promote these observations to SDK guarantees.

## Expected observations

- Ownership, callback argument lifetime, allocation/free pairing or thread join/detach state, and concurrency are tested only where this signature documents them.
- Allocation success, callback thread, ordering, and unsupported ownership transfers are characterization, not expected outcomes.

## Public-SDK-only plan

1. Define an instrumented `GalaxyRealloc` callback and supply it with matching `GalaxyMalloc` and `GalaxyFree` callbacks to `GalaxyAllocator`; consume that allocator through the documented `InitOptions` path, never by invoking the typedef as a standalone API.
2. Use barriers and bounded joins only for documented thread operations; test allocation/free or spawn/join/detach lifetime pairing where exposed, not undocumented concurrent calls.
3. Keep callback state alive through the documented completion point, release it once, destroy listeners, and finish normal shutdown cleanup.

## Result placeholders

- UniverseLAN server + 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized callback-thread result: `<documented facts and characterization observations>`.
- Official GOG 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized callback-thread result: `<documented facts and characterization observations>`.
## Verdict and next step

- `[ ] Pass` `[ ] Fail` `[x] Not-run`
- Least-feasible next step: run the smallest `GalaxyAllocator`/`InitOptions` consumer probe in both lanes, then add only the documented lifecycle observation needed to explain a difference.
