# `virtual void SignIn(bool requireOnline = false, IAuthListener* listener = NULL) = 0;`

## Declaration and applicability

- Header: `IUser.h`
- Exact declaration/signature:
```cpp
virtual void SignIn(bool requireOnline = false, IAuthListener* listener = NULL) = 0;
```
- Observed snapshot availability: 1.124.0.
- Relevant build matrix gate: GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS.
- Existing coverage: No grounded existing coverage identified in `Source/BehaviourTests/COVERAGE.md`.

## Fact boundary

- Documented fact: the selected public header declares the signature above. Any adjacent header precondition, return description, or callback statement may be asserted verbatim.
- Characterization required: result values, error category, callback delivery/count/order/thread, timing, cross-client visibility, pointer lifetime, and behavior for inputs not explicitly documented. Do not promote these observations to SDK guarantees.

## Expected observations

- Registration before the trigger, callback argument relations, multiplicity, same-interface order, destruction, and absence after destruction are independently recorded.
- Delivery, cross-host timing, and cross-interface ordering remain characterization unless the header documents them.

## Public-SDK-only plan

1. Construct/register the listener before a deterministic public trigger and verify registration through only public calls or the callback itself.
2. Trigger one legal event, pump to a bounded deadline, and record callback arguments, multiplicity, and same-interface order without retaining undocumented callback-owned data.
3. Destroy/unregister the listener before a second bounded trigger and before shutdown; record post-destruction delivery as characterization and complete cleanup.

## Result placeholders

- UniverseLAN server + 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized listener result: `<documented facts and characterization observations>`.
- Official GOG 2 clients: `[ ] Not-run` `[ ] Pass` `[ ] Fail`; sanitized listener result: `<documented facts and characterization observations>`.
## Verdict and next step

- `[ ] Pass` `[ ] Fail` `[x] Not-run`
- Least-feasible next step: run the smallest valid `SignIn` probe in both lanes, then add only the documented boundary or lifecycle observation needed to explain a difference.
