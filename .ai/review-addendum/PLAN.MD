# Thorough follow-up review plan

## Baseline and scope

Working branch: `feature/ai-review`, initially `48cea8c6c48fa41fddd348a0119129cc5643fc8b`. Production baseline remains `b30e83872c0006e8240c8b4f565da5351bf10080` on `feature/fix-issues`; remote refs and the scoped source comparison agree. Existing reports and the test-coverage supplement are retained.

The same 529 first-party `.cxx`, `.hxx`, `.cmake`, and `.txt` inputs are in scope. User exclusions remain in force: nested vendor source and SDK headers are dependency/contract context only, and the named test/tool trees are not implementation review targets. SystemTests is included. InterceptionLogger retains its shallow serious-defect scope. Windows is the execution focus; no Linux builds or credential access.

Read `.ai/SKILLS/CppReviewer.md`. This pass must reread source, follow supported SDK contracts, and then compare with existing evidence. Do not manufacture additional IDs for an already reported mechanism, or promote invalid caller behavior/unproven native lifetimes to confirmed production failures. Explicitly record realistic interleavings, trust boundaries, version gates and counterevidence.

## Assignments

- CORE: 30 Client lifecycle/facade/registrar/logger/thread/init and Client_NoVer files, as in the baseline allocation.
- API: 10 Client Impl Chat/Friends/Matchmaking/Networking/CustomNetworking sources and headers.
- STORAGE: 14 Client Impl Apps/CloudStorage/Stats/Storage/Telemetry/User/Utils sources and headers.
- NET: all 59 Shared inputs, every protocol schema included.
- UTIL: all 40 Shared_NoVer inputs.
- SERVER: all 43 Server/SystemTests/Tracer/Version inputs.
- INTERCEPT: all 73 InterceptionLogger inputs.
- BUILD: all 260 root/Source feature/build inputs, per-version DLL wrappers/dispatch/manifests, and direct Vendor manifests.

## Artifacts and work rules

Each owner writes `.ai/review-addendum/<owner>.MD` with exact per-file coverage, fresh inspection notes, new/corrected/retained evidence and comparison with its baseline finding IDs. Read unique implementations fully; equivalent empty markers/dispatchers may use verified content identity with individual coverage records. Unfinished files must be listed, never marked complete by report generation alone.

Append full finding sections to responsible existing sidecars for confirmed additions using `ADD-<owner>-NNN` IDs. Include severity, confidence, category, location, evidence, failure mechanism, impact, possible solutions, recommended resolution and proposed or actually executed verification. Improvements to existing findings retain BASE IDs and are described in a clearly identified addendum, with no duplicate accounting. Do not remove or silently rewrite previous conclusions; hand disagreements to the coordinator for disposition.

Delegates must not edit production code, run builds/tests, mutate Git, inspect credentials, or edit other owners' reports. Use `apply_patch` for all report edits. The coordinator owns cross-component reconciliation, focused fresh Windows probes where useful, final accounting and verification. Existing successful builds need not be repeated merely to inflate validation; different failure paths require focused checks.

## Status

All 529 assigned inputs have been rereviewed with exact owner coverage. Existing findings are retained with clarifications. Independent reconciliation plus the local ABI handoff yields 23 distinct confirmed additions and four new conditional/latent records, with three duplicate additions mapped to existing groups. Local Windows checks are complete. Coverage, finding accounting, links, whitespace and production-source integrity are verified by the review checker. See `SUMMARY.MD` and `VERIFICATION.MD` for outcomes and limits. No absence-of-defects guarantee is implied by coverage.

## User clarification during validation

The remaining validation is limited to ordinary local C++ correctness, memory/resource safety, API compatibility and regression coverage. Use isolated filesystem/SDK harnesses and compiler diagnostics. No adversarial network exercise, live-service probing, or credential work is part of this pass. Preexisting static trust-boundary observations remain historical review evidence; the addendum's new shared-counter and snapshot issues are described through ordinary state ownership and recipient contracts, without operational attack instructions.
