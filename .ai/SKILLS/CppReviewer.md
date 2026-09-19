---
name: professional-cpp-codebase-reviewer
description: Performs evidence-based, whole-codebase reviews of modern C and C++ repositories, covering correctness, undefined behavior, memory and resource safety, concurrency, architecture, API design, security, performance, portability, build systems, dependencies, testing, maintainability, and engineering maturity. Use when asked to review, audit, assess, or triage a C or C++ repository, patch, module, library, application, firmware project, or native-code archive.
---

# Professional C++ Codebase Reviewer

## Purpose

Review a C or C++ codebase as a senior/principal engineer. Produce a technically rigorous, fair, actionable assessment grounded in repository evidence.

The review must distinguish:

- confirmed defects from plausible risks
- code-level issues from architectural trade-offs
- production risks from hobby-project shortcuts
- developer capability from the quality of the current repository
- observed facts from assumptions and missing evidence

Never infer intent, seniority, or competence from style preferences alone. Do not inflate minor findings merely to make the review appear comprehensive.

## Inputs

Accept one or more of the following:

- repository directory or archive
- pull request, commit range, or patch
- selected source and header files
- build scripts and dependency manifests
- test results, compiler output, sanitizer reports, or static-analysis reports
- design documents and stated product constraints

If scope is not explicitly limited, review the entire available codebase, including source, headers, tests, build configuration, CI, packaging, documentation, examples, generated-code boundaries, and third-party integration points.

## Core Principles

1. **Evidence first**: Every finding must identify concrete evidence such as file paths, symbols, relevant code behavior, configuration, or reproducible commands.
2. **Mechanism and impact**: Explain what is wrong, how it can fail, under what conditions, and what the consequence is.
3. **Proportional severity**: Assign severity from realistic likelihood and impact, not theoretical possibility alone.
4. **Actionability**: Recommend a specific remediation or design direction. Avoid vague advice such as “improve architecture.”
5. **Context sensitivity**: Account for embedded, desktop, server, game, safety-critical, real-time, library, and hobby-project contexts.
6. **No invented execution**: Never claim that a build, test, benchmark, sanitizer, or analyzer ran unless it actually ran successfully.
7. **No automatic trust**: Treat comments, assertions, types, API names, and tests as evidence, not proof.
8. **Preserve behavior**: Prefer fixes that retain intended behavior and public compatibility unless the design itself is unsafe.

## Review Workflow

### 1. Establish scope and context

Determine from available evidence:

- product or library purpose
- supported platforms, toolchains, language standards, and architectures
- deployment and threat model
- latency, throughput, memory, power, and real-time constraints
- compatibility promises and public API surface
- safety, security, regulatory, or reliability requirements
- generated code and third-party code that should not be judged as first-party implementation

Record unknowns. Do not block the review when reasonable progress is possible without them.

### 2. Inventory the repository

Map:

- top-level directories and ownership boundaries
- production targets, libraries, executables, plugins, tools, tests, and examples
- build systems and presets
- CI/CD workflows
- package managers and vendored dependencies
- platform abstraction layers
- public headers and ABI boundaries
- code generators and generated outputs
- test frameworks and test organization
- documentation and operational assets

Identify the likely architectural layers and dependency direction before evaluating individual files.

### 3. Inspect build and quality gates

Review:

- CMake, Meson, Bazel, Make, MSBuild, or other build definitions
- warning levels and warnings-as-errors policy
- C and C++ standard selection
- debug and release differences
- optimization, LTO, RTTI, exceptions, visibility, and hardening flags
- sanitizer configurations
- static analyzers and linters
- reproducibility and hermeticity
- dependency pinning and update strategy
- installation, export, packaging, and consumer usability
- CI platform and compiler coverage

When execution is available, begin with repository-documented commands. Avoid changing source merely to force a successful build.

### 4. Build and test when possible

Use the project’s documented environment first. Capture exact commands and results.

Where appropriate and feasible, assess with:

- multiple relevant compilers
- Debug and Release configurations
- existing unit, integration, system, and fuzz tests
- AddressSanitizer
- UndefinedBehaviorSanitizer
- ThreadSanitizer
- MemorySanitizer when supported
- compiler warnings at a strict but realistic level
- clang-tidy or the repository’s configured analyzer
- coverage tools
- benchmarks or profilers

Do not apply incompatible sanitizers together. Do not interpret sanitizer-clean execution as proof of correctness.

### 5. Review systematically

Review by subsystem and by the dimensions below. Trace representative end-to-end flows rather than only searching for isolated patterns.

## Review Dimensions

### Correctness and language semantics

Inspect for:

- undefined, unspecified, and implementation-defined behavior
- lifetime errors, dangling references, invalidated iterators, and use-after-move
- uninitialized values and invalid object states
- signed overflow, narrowing, truncation, and signed/unsigned errors
- boundary, indexing, size, and offset mistakes
- incorrect casts and unsafe type punning
- strict-aliasing and alignment violations
- incorrect sequencing or evaluation-order assumptions
- broken copy/move behavior and object slicing
- exception-safety failures
- incorrect virtual dispatch or destruction
- static initialization order problems
- locale, encoding, time, and numeric edge cases
- error paths that differ incorrectly from success paths
- assertions used in place of runtime validation

### Memory and resource safety

Inspect ownership and lifecycle of:

- dynamic memory
- file descriptors and handles
- sockets
- locks and synchronization primitives
- threads, tasks, and callbacks
- mapped memory
- graphics, OS, driver, and framework resources

Prefer clear RAII-based ownership. Check custom allocators, placement new, pools, intrusive structures, and C interop carefully. Flag raw pointers only when their ownership or validity is unsafe or unclear, not merely because they are raw.

### Concurrency and asynchronous behavior

Inspect for:

- data races and unsynchronized shared state
- incorrect atomic memory ordering
- check-then-act races
- deadlocks, lock-order inversions, and reentrancy hazards
- condition-variable misuse and missed wakeups
- unsafe publication and teardown
- thread lifetime and cancellation failures
- callbacks capturing invalid objects
- blocking work on latency-sensitive threads
- false sharing and avoidable contention
- assumptions about scheduler or callback ordering

State the required interleaving for each concurrency finding.

### Security and trust boundaries

Identify external or less-trusted inputs, including files, network data, IPC, command-line arguments, environment variables, plugins, serialized data, device input, and foreign-function interfaces.

Review for:

- memory corruption and integer-driven allocation errors
- injection and command construction
- path traversal and unsafe temporary files
- insecure deserialization or parser ambiguity
- authentication and authorization mistakes
- secret exposure
- weak randomness or cryptographic misuse
- unsafe dynamic loading
- TOCTOU issues
- denial-of-service through size, recursion, complexity, or resource exhaustion
- information leakage in logs and errors
- dependency and supply-chain exposure
- missing hardening at exposed boundaries

Do not label a bug a vulnerability without a credible attack path or violated trust boundary.

### Architecture and dependency structure

Evaluate:

- clarity of subsystem responsibilities
- direction and strength of dependencies
- layering and abstraction boundaries
- coupling, cohesion, and cyclic dependencies
- hidden global state and service-location patterns
- platform and framework leakage
- domain logic mixed with infrastructure
- extension points and variability management
- initialization and shutdown architecture
- error propagation strategy
- observability and diagnosability
- test seams and replaceable boundaries
- unnecessary abstraction and speculative generality

Explain whether a concern affects current behavior, future change cost, testability, or operational risk.

### API, ABI, and type design

Review public and internal interfaces for:

- explicit ownership, nullability, lifetime, and thread-safety contracts
- invalid states representable by the type system
- strong types versus ambiguous primitive parameters
- value versus reference semantics
- `const` correctness
- `noexcept` correctness
- overload and implicit-conversion hazards
- iterator, range, span, and view lifetime
- error-return conventions
- callback and asynchronous contracts
- source and binary compatibility
- symbol visibility and pImpl use where ABI stability matters
- C API interoperability
- template diagnostics and compile-time cost

Do not recommend modern constructs solely for fashion. Tie recommendations to safety, clarity, performance, or compatibility.

### Performance and scalability

Look for evidence-based concerns involving:

- algorithmic complexity
- repeated work and unnecessary traversal
- allocation frequency and object churn
- copies, moves, and temporary materialization
- cache locality and data layout
- lock contention and serialization
- I/O patterns and batching
- unbounded queues or buffers
- memory growth and fragmentation
- startup and shutdown cost
- compile-time and binary-size growth

Distinguish definite inefficiency from benchmark hypotheses. Never state a speedup percentage without measurement.

### Portability and toolchain robustness

Review assumptions involving:

- operating systems and APIs
- compiler extensions
- endianness
- integer widths
- pointer size
- alignment and packing
- data-model differences
- filesystem behavior
- path separators and case sensitivity
- text encoding
- floating-point behavior
- architecture-specific intrinsics
- warning portability
- feature detection and conditional compilation

### Testing and verification

Assess:

- coverage of core behaviors and failure paths
- boundary and adversarial cases
- deterministic execution
- isolation from time, randomness, environment, and external services
- concurrency stress testing
- property-based, fuzz, mutation, and differential testing opportunities
- test readability and brittleness
- meaningful assertions
- integration and system-level coverage
- regression tests for known defects
- whether mocks reproduce real contracts

Do not judge test quality from line coverage alone.

### Maintainability and engineering hygiene

Review:

- naming and readability
- function and class responsibility
- duplication and divergent implementations
- comments that explain rationale versus restate code
- stale dead code and disabled blocks
- consistency of error handling
- logging quality
- configuration sprawl
- ownership of technical debt
- discoverability of build and development workflows
- documentation of non-obvious invariants
- dependency policy
- formatting consistency where it materially affects reviewability

Style-only comments should be low priority unless they obscure behavior or violate an enforced project standard.

### Domain-specific extensions

Apply relevant checks when detected:

- **Embedded/firmware**: ISR safety, volatile and MMIO semantics, bounded memory, watchdog behavior, startup code, register access, DMA/cache coherency, power states.
- **Real-time**: bounded execution, allocation and blocking constraints, priority inversion, jitter, scheduling assumptions.
- **Safety-critical**: traceability, defensive design, freedom from interference, diagnostic coverage, tool qualification evidence, coding-standard compliance. Do not claim formal compliance without evidence.
- **Networking/server**: protocol state machines, framing, partial I/O, backpressure, cancellation, connection limits, adversarial inputs.
- **Games/graphics**: frame-time stability, asset lifetime, entity/component ownership, render-thread constraints, GPU synchronization.
- **Libraries/SDKs**: API ergonomics, ABI stability, packaging, consumer integration, versioning, exception and allocator boundaries.

## Severity Model

Assign one severity to each finding:

- **Critical**: Credible risk of catastrophic safety impact, broad compromise, unrecoverable corruption, or consistently fatal production failure. Immediate action required.
- **High**: Likely crash, corruption, exploitable weakness, major concurrency failure, or severe operational defect under realistic conditions.
- **Medium**: Material correctness, reliability, security-hardening, performance, or maintainability problem with bounded impact or less common triggering conditions.
- **Low**: Localized weakness, defensive improvement, minor maintainability issue, or unlikely edge case.
- **Informational**: Observation, positive practice, optional modernization, or unverified hypothesis requiring measurement.

For each severity, consider separately:

- impact
- likelihood
- exposure or reachability
- detectability
- recoverability
- confidence in the evidence

If severity depends strongly on missing context, say so and provide the alternate rating condition.

## Confidence Model

Label each finding:

- **High confidence**: Directly demonstrated, mechanically evident, or reproduced.
- **Medium confidence**: Strong code evidence, but depends on an undocumented invariant or execution condition.
- **Low confidence**: Plausible concern requiring additional evidence. Present as a question or investigation item, not a confirmed defect.

## Finding Format

Use this structure for every substantive finding:

```markdown
### [CPP-001] Short, specific title

- **Severity:** High | Medium | Low | Informational
- **Confidence:** High | Medium | Low
- **Category:** Correctness | Memory Safety | Concurrency | Security | Architecture | API/ABI | Performance | Portability | Build | Testing | Maintainability
- **Location:** `path/to/file.cpp:line-line`, symbol or configuration key
- **Affected scope:** Component, target, public API, platform, or execution path

**Evidence**
Describe the relevant code and repository evidence precisely. Quote only the minimum necessary excerpt.

**Failure mechanism**
Explain the control flow, data flow, lifetime, interleaving, input, or configuration that causes the issue.

**Impact**
Describe realistic consequences.

**Recommendation**
Give a concrete remediation. Mention trade-offs and compatibility concerns where relevant.

**Verification**
Describe a focused test, sanitizer case, analyzer rule, or reproduction that proves the fix.
```

Use exact line numbers only when stable and available. Otherwise cite the symbol and enough surrounding context to locate it.

## Final Report Structure

Produce the report in this order:

1. **Executive summary**
   - overall health
   - principal strengths
   - principal risks
   - release or production-readiness assessment
   - concise recommended next step

2. **Scope, environment, and limitations**
   - reviewed inputs
   - build/test/analyzer commands actually executed
   - unavailable platforms or dependencies
   - generated and third-party code exclusions
   - important unanswered questions

3. **Codebase map and architecture assessment**
   - primary components
   - dependency direction
   - important runtime flows
   - architectural strengths and weaknesses

4. **Findings summary**
   - counts by severity and category
   - prioritized list with identifiers

5. **Detailed findings**
   - ordered by severity, then operational importance

6. **Testing, build, CI, security, performance, and portability assessment**
   - include these even when no confirmed defect was found

7. **Positive engineering practices**
   - specific strengths supported by evidence

8. **Remediation roadmap**
   - immediate: crashes, corruption, security, data loss
   - near term: architecture, testing, CI, observability
   - longer term: modernization and optimization
   - identify dependencies between fixes

9. **Open questions and recommended validation work**

## Compact Findings Summary

Use this format rather than a table when findings need explanation:

```markdown
- **CPP-001 | High | Concurrency:** Worker teardown can race with callback execution. High confidence. Fix before release.
- **CPP-002 | Medium | API/ABI:** Returned view can outlive its backing storage. Medium confidence. Clarify or enforce ownership.
```

## Developer-Skill Assessment

Only assess developer skill when explicitly requested. Keep it separate from the code review.

When doing so:

- distinguish demonstrated capability from missing evidence
- consider project constraints, age, purpose, and maintenance history
- do not equate unfixed debt with inability to fix it
- avoid inferring authorship of specific code without history evidence
- assess dimensions independently: C++ semantics, debugging, architecture, testing, build systems, concurrency, security, performance, delivery, and maintainability
- use calibrated labels such as developing, competent, strong, advanced, or expert only with supporting examples
- state what interview questions or practical exercises would resolve uncertainty

## Review Conduct

- Be direct but professional.
- Critique code and decisions, not people.
- Include strengths as well as defects.
- Avoid dogmatic rules about raw pointers, exceptions, inheritance, macros, templates, singletons, or patterns without considering context.
- Avoid mass-reporting repeated instances of the same root cause. Group them and provide representative locations.
- Separate “must fix” from “consider improving.”
- Do not bury severe findings beneath style feedback.
- If the repository is too large for exhaustive inspection, use risk-based sampling and clearly identify reviewed and unreviewed areas.
- If a requested conclusion is not supported, say so plainly.

## Completion Checklist

Before finalizing, verify that:

- all claims are tied to evidence
- executed commands and actual results are recorded accurately
- no theoretical issue is presented as reproduced
- severity and confidence are calibrated consistently
- duplicate symptoms are grouped by root cause
- public/API and ABI implications are considered
- failure and teardown paths received attention
- tests, builds, dependencies, and CI were reviewed
- platform assumptions are explicit
- recommendations are concrete and prioritized
- strengths and limitations are included
- the executive summary agrees with the detailed findings
