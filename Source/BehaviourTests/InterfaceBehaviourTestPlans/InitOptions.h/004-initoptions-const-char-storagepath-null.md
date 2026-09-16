# `InitOptions(const char* _clientID, const char* _clientSecret, const char* _configFilePath = ".", GalaxyAllocator* _galaxyAllocator = NULL, const char* _storagePath = NULL)`

## Declaration and applicability

- Header: `InitOptions.h`
- Exact declaration/signature:
```cpp
InitOptions(const char* _clientID, const char* _clientSecret, const char* _configFilePath = ".", GalaxyAllocator* _galaxyAllocator = NULL, const char* _storagePath = NULL)
```
- Observed snapshot availability: 1.124.0, 1.125.2, 1.126.1, 1.127.0, 1.128.3, 1.130.0, 1.131.3.
- Relevant build matrix gate: GALAXY_BUILD_FEATURE_HAS_INITOPTIONS_STORAGEPATH.
- Existing coverage: No grounded existing coverage identified in `Source/BehaviourTests/COVERAGE.md`.

## Fact boundary

- Documented fact: the selected public header declares the signature above. Any adjacent header precondition, return description, or callback statement may be asserted verbatim.
- Characterization required: result values, error category, callback delivery/count/order/thread, timing, cross-client visibility, pointer lifetime, and behavior for inputs not explicitly documented. Do not promote these observations to SDK guarantees.

## Expected observations

- Ownership, callback argument lifetime, allocation/free pairing or thread join/detach state, and concurrency are tested only where this signature documents them.
- Allocation success, callback thread, ordering, and unsupported ownership transfers are characterization, not expected outcomes.

## Public-SDK-only plan

1. Supply a minimal instrumented public callback/factory with caller-owned state, invoke `InitOptions` only through its documented consumer, and record calls without retaining raw addresses or payloads.
2. Use barriers and bounded joins only for documented thread operations; test allocation/free or spawn/join/detach lifetime pairing where exposed, not undocumented concurrent calls.
3. Keep callback state alive through the documented completion point, release it once, destroy listeners, and finish normal shutdown cleanup.

## Result placeholders

- UniverseLAN server + 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized callback-thread result: `<documented facts and characterization observations>`.
- Official GOG 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized callback-thread result: `<documented facts and characterization observations>`.
## Verdict and next step

- `[ ] Pass` `[ ] Fail` `[x] Not-run`
- Least-feasible next step: run the smallest valid `InitOptions` probe in both lanes, then add only the documented boundary or lifecycle observation needed to explain a difference.
