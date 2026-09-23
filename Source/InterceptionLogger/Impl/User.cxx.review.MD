# Fresh baseline review — Impl/User.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–865. Static Windows review; shallow serious-defect scope. Only source text was inspected; no credential/config/environment values were accessed.

## Checked
- Read all versioned sign-in forms, credential override routing, optional auth proxy creation, user-data APIs, ticket sizes, tokens and OpenID forwards.
- Password-based login logs the password address rather than its contents; binary Steam/encrypted-ticket data is not decoded by these paths.
- Followed AuthListener encapsulation to the missing success callback (BASE-INTERCEPT-004 at UserListener.cxx). Optional listener nulls are preserved by encapsulation.
- Bounded output string tracing avoids unbounded scans; void output APIs still require error-state validation before consuming uninitialized output.

## BASE-INTERCEPT-011 — Authentication material is written verbatim to persistent call traces

- **Severity:** Medium
- **Confidence:** High
- **Category:** Security
- **Location:** `Source/InterceptionLogger/Impl/User.cxx:205–206,244–245,703–727,760–782,793–795,835–856`; additional token paths at 275–276 and 350–352.
- **Affected scope:** Applicable sign-in/token APIs with ARGUMENTS or RETURN_VALUES tracing enabled.

**Evidence and failure mechanism:** SignInToken logs refreshToken as a string; GetRefreshToken/GetRefreshTokenCopy log the returned token. Access/ID-token getters, authorization code, server key and PlayFab secret/player-secret arguments have the same behavior. SDK `1.152.11/galaxy/IUser.h:382–397,768–798` identifies the refresh token as an authentication credential and supports using it to sign in. `Tracer.hxx:85–89` formats it into text, and `Tracer.cxx:290–319` writes the text to per-thread/global files and optionally console. `UniverseLANInterceptor.cxx:110–118` selects the Interceptor tracing directory. This evidence contains no real secret values.

**Impact:** Diagnostic artifacts retain reusable authentication material and can expose it when logs are collected/shared or read by another principal. Severity is bounded by enabled trace masks and access to those artifacts; no unauthorized log reader or account compromise was demonstrated.

**Possible fixes:** Redact credential fields at each call site, or use a typed sensitive-value formatter applied consistently to arguments and results. A path-only log restriction does not protect shared diagnostics.

**Recommended resolution:** Log presence/type and safe non-secret metadata, never raw tokens/keys/codes; cover getter results as well as inputs. Preserve the existing password-redaction intent across feature versions.

**Verification:** Supply synthetic marker strings through every token/key/code path and its Copy variant, enable all trace masks and console output, and assert that no marker appears in any sink. No credentials or live authentication are needed. Proposed only.
