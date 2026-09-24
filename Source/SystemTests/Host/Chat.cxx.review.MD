# Fresh review — Host/Chat.cxx

Baseline: `b30e83872c0006e8240c8b4f565da5351bf10080`. Read completely: lines 1–327. Static review.

## Inspection notes
- Traced message-delivery sender/receiver listeners, room reuse, negative unknown-room send, two-message history/cursor retrieval and duplicate callback observation windows.
- History tests preserve distinct message IDs and request exclusive older/newest entries; callbacks read content while the SDK's callback-scoped message view is valid.
- Current scenarios do not overlap independently correlated history/room requests from multiple participants, so they do not cover **BASE-SERVER-008**. Offline participant reconnection and persistent history are also outside these assertions.
- Fixed buffers are sized for the known local test payloads; checking returned lengths before constructing a string would make the oracle more robust against a broken provider, but no out-of-bounds read was established with the actual bounded-payload implementation.

### [BASE-SERVER-014] Early chat SDK hosts compile references to a nonexistent ChatMessageType

- **Severity:** Medium
- **Confidence:** High (source/SDK contract comparison; no compile attempted)
- **Category:** Build
- **Location:** `Source/SystemTests/Host/Chat.cxx:8–30`; target inclusion `Source/SystemTests/CMakeLists.txt:35–48`.
- **Affected scope:** Opt-in SystemTests host builds for typed-ID chat SDKs before ChatMessageType, notably 1.106.0 and 1.109.0.

**Evidence.** The outer guard requires HAS_ICHAT and GALAXYID_HAS_IDTYPE. Feature definitions enable those at 1.104.3 and 1.106.0 respectively, but HAS_ICHAT_MESSAGETYPE starts at 1.110.0 (`Source/galaxy_sdk_features.cmake:94,101,108`). Lines 24,28–29 unconditionally declare ChatMessageType, use its enumerators and call the newer message-index signature. The 1.109.0 SDK's `IChat.h:293` instead takes `(index, messageID, senderID, sendTime, buffer, length)` with no type argument.

**Failure mechanism.** These host translation units are always added to the versioned host. On the affected versions the outer guard is true, so parsing fails even if CMake does not register the message-delivery scenario. Runtime unsupported-scenario checks cannot repair a compile error.

**Impact.** Selecting an affected legacy SDK with SystemTests enabled prevents that host target, and its dependent runner, from building. Production-only builds with SystemTests off are unaffected.

**Alternatives / recommendation.** Guard the listener/body and matching dispatch with HAS_ICHAT_MESSAGETYPE, or adapt argument lists/type assertions using the established feature macros. Prefer compatibility branches where delivery semantics can still be meaningfully tested. Do not hardcode a single SDK target.

**Verification.** After remediation, configure/build the requested feature-matrix boundary targets (e.g. 1.106.0, 1.109.0, 1.112.2 and a modern SDK) with SystemTests enabled on Windows x86/x64. Confirm unsupported scenarios are omitted/rejected consistently and supported host sources compile. Not executed.

## Follow-up addendum — 2026-09-24

### [BASE-SERVER-014] Addendum — source/SDK boundary reconfirmed

Retain **Medium / High confidence / Build**. Full reread of all 327 lines and the full SystemTests CMake manifest confirms `Host/Chat.cxx` is compiled independently of scenario registration. `Source/galaxy_sdk_features.cmake:94–108` enables chat plus typed IDs before message types; `1.109.0/galaxy/IChat.h:293` has no message-type output. The unguarded listener therefore still prevents the affected opt-in legacy host build. No compile was performed.

The history listener's in-callback message read is not condemned as invalid native usage merely from the getter's short remark: SDK `1.152.11/galaxy/IChat.h:158–167` explicitly instructs `OnChatRoomMessagesRetrieveSuccess` to call `GetChatRoomMessageByIndex`. That supports the test's retrieval callback use. Unknown room ID zero remains a UniverseLAN negative-input scenario, not proof that a proprietary SDK promises the same forbidden callback for every invalid argument. The correlation test gap is specifically equal IDs in matching listener types (BASE-SERVER-008 addendum). Successful `_Exit` paths exclude graceful SDK teardown.
