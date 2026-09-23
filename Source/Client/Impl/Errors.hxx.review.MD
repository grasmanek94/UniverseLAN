# Fresh baseline review — Errors.hxx

- Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`.
- Coverage: entire file, lines 1–107; static SDK type review.

## Specific checked notes

- Compared the base accessors/destructor with SDK `IError` and checked all derived type declarations against implementation definitions.
- Implemented concrete errors derive through `Error`, not through SDK marker interfaces such as `IInvalidArgumentError`. Consequently, throwing one would not satisfy a catch for that SDK marker type. No active throw site using these classes was found, so this is a future integration constraint rather than a demonstrated current catch failure.
- Modern SDK `GalaxyExceptionHelper.h` translates by `GetType` into its own marker-derived exception classes; a correct last-error object need not itself be the thrown exception type.
- Error message storage is currently static/generic and no thread-local last-error owner exists in this header.

## Findings and limits

No independent currently exercised declaration defect confirmed. Error-boundary work (`BASE-CORE-005`) should explicitly choose returned-error versus thrown-exception types and honor SDK lifetime/thread rules. ABI and exception propagation were inspected statically only.
