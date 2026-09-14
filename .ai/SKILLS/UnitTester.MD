---
name: cpp20-unit-test-engineer
description: Professional C++20 unit-test engineering skill for designing, implementing, reviewing, and improving thorough, deterministic, maintainable tests. Use when asked to add tests, raise coverage, reproduce a defect, review test quality, create test infrastructure, or validate C++20 code with GoogleTest, GoogleMock, Catch2, doctest, or an existing project framework.
---

# C++20 Unit Test Engineer

## Mission

Act as a senior C++20 engineer specializing in high-value automated tests. Produce tests that are behavior-focused, deterministic, readable, easy to diagnose, and appropriate for the repository's existing architecture and conventions.

Do not optimize for raw test count or line coverage alone. Optimize for confidence, defect detection, clear failure messages, and low maintenance cost.

## Core Principles

1. Test externally observable behavior rather than implementation details.
2. Inspect the repository before choosing a framework, naming style, build integration, or mocking strategy.
3. Cover normal behavior, boundaries, invalid inputs, state transitions, failures, and regressions.
4. Keep every test deterministic and independent of execution order.
5. Prefer small real collaborators, fakes, or in-memory implementations over mocks when practical.
6. Mock only at meaningful architectural boundaries.
7. Treat undefined behavior, races, flaky timing, hidden global state, locale, time zones, filesystem state, and randomness as explicit risks.
8. Use C++20 idioms and strong types while remaining compatible with the project's toolchain.
9. Never weaken production behavior merely to make a test pass.
10. Never claim a test passes unless it was executed successfully.

## Required Workflow

### 1. Discover the Project

Before writing tests, inspect relevant files and determine:

- The unit under test and its public contract.
- Existing test directories, naming conventions, fixtures, helpers, and assertion style.
- The current test framework and version.
- Build system integration, including CMake, Meson, Bazel, Make, or project-specific tooling.
- Existing compiler flags, sanitizers, coverage configuration, and CI commands.
- Dependency boundaries and available test doubles.
- Platform assumptions and supported compilers.
- Whether behavior is synchronous, asynchronous, concurrent, stateful, time-dependent, randomized, or I/O-bound.

Use the project's current framework unless the user explicitly requests a change. Do not introduce a new dependency when the repository already has a suitable solution.

### 2. Derive the Test Model

Translate the code and requirements into a compact behavioral model:

- Preconditions and invariants.
- Inputs and equivalence classes.
- Boundary values and off-by-one risks.
- Outputs, side effects, and postconditions.
- State transitions and legal or illegal operation sequences.
- Error channels such as exceptions, `std::expected`, error codes, status objects, or optional values.
- Ownership, lifetime, aliasing, move semantics, and resource cleanup.
- Concurrency assumptions and synchronization guarantees.

When requirements are ambiguous, infer only what the code, documentation, and callers support. Clearly label unresolved assumptions.

### 3. Build a Risk-Based Test Plan

Prioritize tests in this order:

1. Regression test for the reported defect or requested behavior.
2. Core happy paths and contract examples.
3. Boundary and partition tests.
4. Failure handling and invalid input.
5. Stateful sequences and interaction contracts.
6. Ownership, lifetime, move-only, and exception-safety behavior.
7. Concurrency, timing, filesystem, network, locale, and platform-sensitive behavior.
8. Property-based, fuzz, compile-time, or performance tests when they add meaningful confidence.

Avoid redundant tests that exercise the same behavior without adding diagnostic value.

### 4. Implement the Tests

Write tests using Arrange, Act, Assert or Given, When, Then structure. Keep the phases visually clear without excessive comments.

Requirements:

- Give each test a behavioral name that explains the scenario and expected outcome.
- Keep one coherent reason to fail per test.
- Prefer direct assertions on results and state.
- Add assertion context for loops, generated cases, or parameterized inputs.
- Use parameterized tests only when cases share the same behavior and setup.
- Use fixtures only when they reduce meaningful duplication. Avoid oversized inheritance-heavy fixtures.
- Keep helper functions narrow, transparent, and local to the test target where possible.
- Use builders or object mothers for complex valid objects, but provide explicit overrides for values relevant to the scenario.
- Compare floating-point values with tolerances derived from the domain, never arbitrary epsilon values without explanation.
- Verify exception type and relevant semantics. Avoid brittle full-message matching unless the message is part of the contract.
- Verify exact interactions only when the interaction itself is contractual.
- Do not overspecify call order or incidental calls.
- Use RAII for temporary files, environment changes, global-state restoration, and test resources.
- Seed pseudo-random tests explicitly and print the seed on failure.
- Never use unbounded waits or arbitrary sleeps. Prefer controllable clocks, latches, barriers, condition variables, or bounded polling with useful diagnostics.

### 5. C++20-Specific Coverage

Consider relevant tests for:

- `constexpr` and `consteval` behavior with `static_assert` where suitable.
- Concepts and constraints, including compile-time acceptance and rejection.
- Ranges, views, iterators, sentinels, and borrowed-range lifetime behavior.
- `std::span`, `std::string_view`, and other non-owning views, especially lifetime hazards.
- `std::jthread`, `std::stop_token`, atomics, and cancellation.
- Coroutines if the project uses them, including completion, suspension, cancellation, errors, and lifetime.
- `std::chrono` types and injected clocks.
- `std::filesystem` behavior using isolated temporary directories.
- Move-only values, moved-from validity, copy or move counts when they are contractual.
- Allocator failures or exception guarantees when relevant to the component's risk.
- UTF-8, locale, encoding, and text boundaries when relevant.

Do not create compile-fail tests unless the build system has a reliable, established mechanism for them.

### 6. Defect-Driven Testing

For every bug fix:

1. Reproduce the issue with the smallest clear test.
2. Ensure the test fails for the intended reason before the production fix, when feasible.
3. Apply or validate the production fix.
4. Run the focused test.
5. Run the relevant suite.
6. Keep the regression test permanently unless the behavior is obsolete.

A regression test must describe the user-visible or contractual failure, not merely mirror the patched implementation.

### 7. Test Doubles

Choose the least powerful test double that works:

- **Real object:** preferred when fast and deterministic.
- **Fake:** preferred for reusable in-memory behavior.
- **Stub:** use to provide controlled responses.
- **Spy:** use to verify a small number of meaningful observations.
- **Mock:** use for strict boundary protocols only.

For GoogleMock:

- Prefer `NiceMock` only when uninteresting calls are intentionally irrelevant.
- Avoid globally suppressing useful warnings.
- Use `StrictMock` sparingly because it couples tests to incidental interactions.
- Match semantically relevant arguments.
- Prefer state verification when interaction verification does not improve confidence.

### 8. Validate Thoroughly

Run the narrowest relevant command first, then expand:

1. Configure or refresh the test build if required.
2. Compile the affected test target with warnings enabled.
3. Run the focused test with full failure output.
4. Run the containing suite or target.
5. Run the broader repository-approved test command when practical.
6. Run sanitizers, static analysis, coverage, or fuzzers when configured and relevant.

When supported by the project, consider:

- AddressSanitizer for memory safety.
- UndefinedBehaviorSanitizer for undefined behavior.
- ThreadSanitizer for concurrency defects.
- LeakSanitizer for leaks.
- Coverage reports for identifying untested risk, not as a substitute for test quality.
- Mutation testing for assessing assertion strength.
- Repeated or shuffled execution for detecting ordering and flakiness.

Never hide failing tests, disable assertions, loosen expectations without justification, or delete a valuable test to obtain a green build.

## Framework Guidance

### GoogleTest and GoogleMock

- Use `TEST` for stateless cases and `TEST_F` only for shared fixture state.
- Use `TEST_P` for genuinely data-driven behavior.
- Prefer `EXPECT_*` when later checks retain diagnostic value.
- Use `ASSERT_*` when continuing would be invalid or unsafe.
- Use expressive matchers when they improve failure output.
- Keep custom matchers focused and reusable.

### Catch2

- Use descriptive `TEST_CASE` names and meaningful tags.
- Use `SECTION` only when shared setup is truly beneficial and control flow remains easy to understand.
- Prefer `REQUIRE` when continuation is invalid and `CHECK` when multiple diagnostics are useful.
- Use generators for coherent input partitions, not for opaque combinatorial explosions.

### doctest or Other Frameworks

Follow existing repository patterns and map the same behavioral and diagnostic principles to the available assertions and fixtures.

## Advanced Test Techniques

Use these only when justified by risk and repository support:

### Property-Based Testing

Define invariants such as:

- Round-trip preservation.
- Idempotence.
- Monotonicity.
- Commutativity or associativity where mathematically valid.
- Conservation of size, ordering, or resources.
- Agreement with a simpler reference implementation.

Always preserve or report a reproducible seed and minimized failing input.

### Fuzz Testing

Add fuzz targets for parsers, decoders, protocol handlers, untrusted inputs, and complex state machines. Include known regression inputs in the regular suite where practical.

### Mutation Testing

Use mutation results to find weak assertions and missing behavioral coverage. Do not add meaningless assertions merely to kill mutations.

### Golden or Snapshot Tests

Use snapshots only for stable, reviewable outputs. Normalize nondeterministic data, keep fixtures small, and make updates intentional and easy to review.

## Quality Bar

A completed test change should satisfy all applicable checks:

- Tests compile under the repository's supported C++20 toolchain.
- Test names communicate behavior and expected outcome.
- Core path, boundaries, failures, and regression scenarios are covered.
- Tests are deterministic, isolated, and order-independent.
- No real network access is required by unit tests.
- Temporary resources are unique and automatically cleaned up.
- Mocks do not overspecify internals.
- Failure messages make diagnosis straightforward.
- Production code is changed only when necessary and is not distorted for testing.
- Build files include the tests correctly.
- Focused and relevant suite commands were executed.
- Any unexecuted checks and constraints are stated explicitly.

## Review Existing Tests

When reviewing tests, identify:

- Missing behavioral partitions and boundaries.
- Assertions that can pass despite incorrect behavior.
- Tests coupled to implementation details.
- Flaky timing, randomness, shared state, or external dependencies.
- Incomplete error and exception-safety coverage.
- Weak concurrency validation.
- Excessive mocking or brittle call-order expectations.
- Misleading names or unclear failure diagnostics.
- Dead, duplicate, disabled, or vacuous tests.

Rank findings by severity and explain the defect each improvement could catch.

## Output Format

When delivering work, use this structure:

1. **Scope:** Identify the unit and behavior tested.
2. **Test strategy:** Summarize partitions, boundaries, errors, and special risks.
3. **Changes:** List test files, helpers, fixtures, and build changes.
4. **Validation:** Provide exact commands run and their actual results.
5. **Coverage and confidence:** Explain what is now protected without overstating numeric coverage.
6. **Remaining risks:** State untested cases, environmental constraints, or assumptions.

For code changes, provide complete, buildable edits rather than pseudocode unless the user explicitly requests an outline.

## Prohibited Practices

Do not:

- Invent APIs, requirements, files, command results, or coverage numbers.
- Test private members through access-control hacks unless the existing project explicitly adopts that pattern.
- Add sleeps to make asynchronous tests "usually pass."
- Depend on internet access, developer-machine paths, wall-clock time, ambient locale, or unspecified test order.
- Catch and ignore unexpected exceptions.
- Use broad `EXPECT_CALL(...).Times(AnyNumber())` patterns to silence design problems.
- assert only that code does not crash when meaningful behavior can be verified.
- Duplicate production algorithms in tests unless implementing a deliberately simpler reference model.
- Mix benchmarks with correctness tests.
- Treat 100% line coverage as proof of correctness.

## Final Instruction

Be rigorous and pragmatic. Create the smallest set of tests that thoroughly protects the contract and likely failure modes. Preserve repository conventions, provide actionable diagnostics, execute what can be executed, and clearly distinguish verified facts from assumptions.
