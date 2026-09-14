#include "Host.hxx"

#include <array>
#include <string>

namespace universelan::systemtest::host
{
#if GALAXY_BUILD_FEATURE_HAS_ICHAT && GALAXY_BUILD_FEATURE_GALAXYID_HAS_IDTYPE
namespace
{
constexpr const char chatRoomMessage[] = "universelan-system-chat-room-message-v1";
constexpr std::size_t chatRoomMessageLength = sizeof(chatRoomMessage) - 1;

struct ChatRoomMessagesListener final : galaxy::api::GlobalChatRoomMessagesListener
{
    ChatRoomMessagesListener(galaxy::api::IChat* chat, const galaxy::api::GalaxyID& expectedSender) : chat(chat), expectedSender(expectedSender) {}
    galaxy::api::IChat* chat;
    galaxy::api::GalaxyID expectedSender;
    bool received = false;
    void OnChatRoomMessagesReceived(galaxy::api::ChatRoomID chatRoomId, uint32_t messageCount, uint32_t longestMessageLength) override
    {
        if (chatRoomId == 0 || messageCount != 1 || longestMessageLength != chatRoomMessageLength) return;
        galaxy::api::ChatMessageID messageId = 0;
        galaxy::api::ChatMessageType messageType = galaxy::api::CHAT_MESSAGE_TYPE_UNKNOWN;
        galaxy::api::GalaxyID senderId;
        uint32_t sendTime = 0;
        std::array<char, chatRoomMessageLength + 1> contents{};
        const uint32_t length = chat->GetChatRoomMessageByIndex(0, messageId, messageType, senderId, sendTime, contents.data(), static_cast<uint32_t>(contents.size()));
        received = messageId != 0 && messageType == galaxy::api::CHAT_MESSAGE_TYPE_CHAT_MESSAGE && senderId == expectedSender
            && length == chatRoomMessageLength && std::string(contents.data(), length) == chatRoomMessage;
    }
};

struct ChatRoomWithUserListener final :
#if GALAXY_BUILD_FEATURE_HAS_ICHAT_ROOMLISTENERS
    galaxy::api::IChatRoomWithUserRetrieveListener
#else
    galaxy::api::GlobalChatRoomWithUserRetrieveListener
#endif
{
    explicit ChatRoomWithUserListener(const galaxy::api::GalaxyID& expectedPeer) : expectedPeer(expectedPeer) {}
    galaxy::api::GalaxyID expectedPeer;
    bool completed = false;
    bool succeeded = false;
    galaxy::api::ChatRoomID chatRoomId = 0;
    void OnChatRoomWithUserRetrieveSuccess(galaxy::api::GalaxyID peerId, galaxy::api::ChatRoomID receivedChatRoomId) override
    {
        completed = true;
        succeeded = peerId == expectedPeer && receivedChatRoomId != 0;
        if (succeeded) chatRoomId = receivedChatRoomId;
    }
    void OnChatRoomWithUserRetrieveFailure(galaxy::api::GalaxyID, FailureReason) override { completed = true; }
};

struct ChatRoomMessageSendListener final :
#if GALAXY_BUILD_FEATURE_HAS_ICHAT_ROOMLISTENERS
    galaxy::api::IChatRoomMessageSendListener
#else
    galaxy::api::GlobalChatRoomMessageSendListener
#endif
{
    explicit ChatRoomMessageSendListener(galaxy::api::ChatRoomID expectedChatRoomId) : expectedChatRoomId(expectedChatRoomId) {}
    galaxy::api::ChatRoomID expectedChatRoomId;
    uint32_t expectedMessageIndex = 0;
    bool completed = false;
    bool succeeded = false;
    galaxy::api::ChatMessageID messageId = 0;
    void OnChatRoomMessageSendSuccess(galaxy::api::ChatRoomID chatRoomId, uint32_t sentMessageIndex, galaxy::api::ChatMessageID messageId, uint32_t) override
    {
        completed = true;
        succeeded = chatRoomId == expectedChatRoomId && sentMessageIndex == expectedMessageIndex && messageId != 0;
        if (succeeded) this->messageId = messageId;
    }
    void OnChatRoomMessageSendFailure(galaxy::api::ChatRoomID, uint32_t, FailureReason) override { completed = true; }
};

#if GALAXY_BUILD_FEATURE_HAS_ICHAT_ROOMLISTENERS && GALAXY_BUILD_FEATURE_HAS_ICHATROOMMESSAGERETRIEVELISTENER && GALAXY_BUILD_FEATURE_HAS_ICHAT_MESSAGETYPE
constexpr const char chatHistoryOlderMessage[] = "universelan-system-chat-history-older-v1";
constexpr const char chatHistoryNewestMessage[] = "universelan-system-chat-history-newest-v1";
constexpr std::size_t chatHistoryOlderMessageLength = sizeof(chatHistoryOlderMessage) - 1;
constexpr std::size_t chatHistoryNewestMessageLength = sizeof(chatHistoryNewestMessage) - 1;

struct ChatHistoryLiveMessagesListener final : galaxy::api::GlobalChatRoomMessagesListener
{
    ChatHistoryLiveMessagesListener(galaxy::api::IChat* chat, const galaxy::api::GalaxyID& expectedSender) : chat(chat), expectedSender(expectedSender) {}
    galaxy::api::IChat* chat;
    galaxy::api::GalaxyID expectedSender;
    galaxy::api::ChatRoomID chatRoomId = 0;
    galaxy::api::ChatMessageID olderMessageId = 0;
    galaxy::api::ChatMessageID newestMessageId = 0;
    bool failed = false;
    bool ready() const { return !failed && chatRoomId != 0 && olderMessageId != 0 && newestMessageId != 0 && olderMessageId != newestMessageId; }
    void OnChatRoomMessagesReceived(galaxy::api::ChatRoomID receivedChatRoomId, uint32_t messageCount, uint32_t longestMessageLength) override
    {
        if (ready() || failed || receivedChatRoomId == 0 || messageCount != 1) return;
        galaxy::api::ChatMessageID messageId = 0;
        galaxy::api::ChatMessageType messageType = galaxy::api::CHAT_MESSAGE_TYPE_UNKNOWN;
        galaxy::api::GalaxyID senderId;
        uint32_t sendTime = 0;
        std::array<char, 128> contents{};
        const uint32_t length = chat->GetChatRoomMessageByIndex(0, messageId, messageType, senderId, sendTime, contents.data(), static_cast<uint32_t>(contents.size()));
        const std::string message(contents.data(), length);
        if (messageId == 0 || messageType != galaxy::api::CHAT_MESSAGE_TYPE_CHAT_MESSAGE || senderId != expectedSender
            || (message != chatHistoryOlderMessage && message != chatHistoryNewestMessage) || longestMessageLength != length) { failed = true; return; }
        if (chatRoomId == 0) chatRoomId = receivedChatRoomId;
        if (chatRoomId != receivedChatRoomId) { failed = true; return; }
        if (message == chatHistoryOlderMessage)
        {
            if (olderMessageId != 0 || newestMessageId != 0 || length != chatHistoryOlderMessageLength) { failed = true; return; }
            olderMessageId = messageId;
        }
        else
        {
            if (newestMessageId != 0 || olderMessageId == 0 || length != chatHistoryNewestMessageLength) { failed = true; return; }
            newestMessageId = messageId;
        }
    }
};

struct ChatHistoryRetrieveListener final : galaxy::api::IChatRoomMessagesRetrieveListener
{
    ChatHistoryRetrieveListener(galaxy::api::IChat* chat, galaxy::api::ChatRoomID expectedChatRoomId, galaxy::api::ChatMessageID expectedMessageId,
        const galaxy::api::GalaxyID& expectedSender, const char* expectedContents, uint32_t expectedLength)
        : chat(chat), expectedChatRoomId(expectedChatRoomId), expectedMessageId(expectedMessageId), expectedSender(expectedSender), expectedContents(expectedContents), expectedLength(expectedLength) {}
    galaxy::api::IChat* chat;
    galaxy::api::ChatRoomID expectedChatRoomId;
    galaxy::api::ChatMessageID expectedMessageId;
    galaxy::api::GalaxyID expectedSender;
    const char* expectedContents;
    uint32_t expectedLength;
    bool completed = false;
    bool succeeded = false;
    void OnChatRoomMessagesRetrieveSuccess(galaxy::api::ChatRoomID chatRoomId, uint32_t messageCount, uint32_t longestMessageLength) override
    {
        completed = true;
        if (chatRoomId != expectedChatRoomId || messageCount != 1 || longestMessageLength != expectedLength) return;
        galaxy::api::ChatMessageID messageId = 0;
        galaxy::api::ChatMessageType messageType = galaxy::api::CHAT_MESSAGE_TYPE_UNKNOWN;
        galaxy::api::GalaxyID senderId;
        uint32_t sendTime = 0;
        std::array<char, 128> contents{};
        const uint32_t length = chat->GetChatRoomMessageByIndex(0, messageId, messageType, senderId, sendTime, contents.data(), static_cast<uint32_t>(contents.size()));
        succeeded = messageId == expectedMessageId && messageType == galaxy::api::CHAT_MESSAGE_TYPE_CHAT_MESSAGE && senderId == expectedSender
            && length == expectedLength && std::string(contents.data(), length) == expectedContents;
    }
    void OnChatRoomMessagesRetrieveFailure(galaxy::api::ChatRoomID, FailureReason) override { completed = true; }
};
#endif
}

bool chatRoomMessageReceiver(Api& api, const Arguments& arguments)
{
    if (arguments.peerUserIds.size() != 1) return false;
    galaxy::api::IChat* chat = api.chat();
    if (chat == nullptr) return false;
    const galaxy::api::GalaxyID expectedSender = galaxy::api::GalaxyID::FromRealID(galaxy::api::GalaxyID::ID_TYPE_USER, arguments.peerUserIds.front());
    ChatRoomMessagesListener listener(chat, expectedSender);
    if (!emit(arguments, "receiver-ready")) return false;
    return pumpUntil(api, arguments.timeoutSeconds, [&listener] { return listener.received; }) && emit(arguments, "receiver-received");
}

bool chatRoomMessageSender(Api& api, const Arguments& arguments)
{
    if (arguments.peerUserIds.size() != 1) return false;
    galaxy::api::IChat* chat = api.chat();
    if (chat == nullptr) return false;
    const galaxy::api::GalaxyID peerId = galaxy::api::GalaxyID::FromRealID(galaxy::api::GalaxyID::ID_TYPE_USER, arguments.peerUserIds.front());
    ChatRoomWithUserListener roomListener(peerId);
#if GALAXY_BUILD_FEATURE_HAS_ICHAT_ROOMLISTENERS
    chat->RequestChatRoomWithUser(peerId, &roomListener);
#else
    chat->RequestChatRoomWithUser(peerId);
#endif
    if (!pumpUntil(api, arguments.timeoutSeconds, [&roomListener] { return roomListener.completed; }) || !roomListener.succeeded) return false;
    ChatRoomMessageSendListener sendListener(roomListener.chatRoomId);
#if GALAXY_BUILD_FEATURE_HAS_ICHAT_ROOMLISTENERS
    sendListener.expectedMessageIndex = chat->SendChatRoomMessage(roomListener.chatRoomId, chatRoomMessage, &sendListener);
#else
    sendListener.expectedMessageIndex = chat->SendChatRoomMessage(roomListener.chatRoomId, chatRoomMessage);
#endif
    if (!pumpUntil(api, arguments.timeoutSeconds, [&sendListener] { return sendListener.completed; }) || !sendListener.succeeded) return false;
    return emit(arguments, "sender-send-succeeded") && waitForCompletion(arguments);
}

#if GALAXY_BUILD_FEATURE_HAS_ICHAT_ROOMLISTENERS && GALAXY_BUILD_FEATURE_HAS_ICHATROOMMESSAGERETRIEVELISTENER && GALAXY_BUILD_FEATURE_HAS_ICHAT_MESSAGETYPE
bool chatRoomHistoryReceiver(Api& api, const Arguments& arguments)
{
    if (arguments.peerUserIds.size() != 1) return false;
    galaxy::api::IChat* chat = api.chat();
    if (chat == nullptr) return false;
    const galaxy::api::GalaxyID senderId = galaxy::api::GalaxyID::FromRealID(galaxy::api::GalaxyID::ID_TYPE_USER, arguments.peerUserIds.front());
    ChatHistoryLiveMessagesListener liveListener(chat, senderId);
    if (!emit(arguments, "receiver-ready") || !pumpUntil(api, arguments.timeoutSeconds, [&liveListener] { return liveListener.ready() || liveListener.failed; })
        || !liveListener.ready() || !emit(arguments, "receiver-live-context") || !waitForAction(arguments)) return false;
    ChatHistoryRetrieveListener newestListener(chat, liveListener.chatRoomId, liveListener.newestMessageId, senderId, chatHistoryNewestMessage, static_cast<uint32_t>(chatHistoryNewestMessageLength));
    chat->RequestChatRoomMessages(liveListener.chatRoomId, 1, 0, &newestListener);
    if (!pumpUntil(api, arguments.timeoutSeconds, [&newestListener] { return newestListener.completed; }) || !newestListener.succeeded) return false;
    ChatHistoryRetrieveListener olderListener(chat, liveListener.chatRoomId, liveListener.olderMessageId, senderId, chatHistoryOlderMessage, static_cast<uint32_t>(chatHistoryOlderMessageLength));
    chat->RequestChatRoomMessages(liveListener.chatRoomId, 1, liveListener.newestMessageId, &olderListener);
    if (!pumpUntil(api, arguments.timeoutSeconds, [&olderListener] { return olderListener.completed; }) || !olderListener.succeeded) return false;
    return chat->GetChatRoomUnreadMessageCount(liveListener.chatRoomId) == 2 && emit(arguments, "receiver-history-retrieved");
}

bool chatRoomHistorySender(Api& api, const Arguments& arguments)
{
    if (arguments.peerUserIds.size() != 1) return false;
    galaxy::api::IChat* chat = api.chat();
    if (chat == nullptr) return false;
    const galaxy::api::GalaxyID peerId = galaxy::api::GalaxyID::FromRealID(galaxy::api::GalaxyID::ID_TYPE_USER, arguments.peerUserIds.front());
    ChatRoomWithUserListener roomListener(peerId);
    chat->RequestChatRoomWithUser(peerId, &roomListener);
    if (!pumpUntil(api, arguments.timeoutSeconds, [&roomListener] { return roomListener.completed; }) || !roomListener.succeeded) return false;
    ChatRoomMessageSendListener olderSendListener(roomListener.chatRoomId);
    olderSendListener.expectedMessageIndex = chat->SendChatRoomMessage(roomListener.chatRoomId, chatHistoryOlderMessage, &olderSendListener);
    if (!pumpUntil(api, arguments.timeoutSeconds, [&olderSendListener] { return olderSendListener.completed; }) || !olderSendListener.succeeded) return false;
    ChatRoomMessageSendListener newestSendListener(roomListener.chatRoomId);
    newestSendListener.expectedMessageIndex = chat->SendChatRoomMessage(roomListener.chatRoomId, chatHistoryNewestMessage, &newestSendListener);
    if (!pumpUntil(api, arguments.timeoutSeconds, [&newestSendListener] { return newestSendListener.completed; }) || !newestSendListener.succeeded || olderSendListener.messageId == newestSendListener.messageId) return false;
    return emit(arguments, "sender-messages-persisted") && waitForCompletion(arguments);
}
#endif

bool chatRoomReuseRequester(Api& api, const Arguments& arguments)
{
    if (arguments.peerUserIds.size() != 1) return false;
    galaxy::api::IChat* chat = api.chat();
    if (chat == nullptr) return false;
    const galaxy::api::GalaxyID peerId = galaxy::api::GalaxyID::FromRealID(galaxy::api::GalaxyID::ID_TYPE_USER, arguments.peerUserIds.front());
    struct ChatRoomReuseListener final :
#if GALAXY_BUILD_FEATURE_HAS_ICHAT_ROOMLISTENERS
        galaxy::api::IChatRoomWithUserRetrieveListener
#else
        galaxy::api::GlobalChatRoomWithUserRetrieveListener
#endif
    {
        explicit ChatRoomReuseListener(const galaxy::api::GalaxyID& expectedPeer) : expectedPeer(expectedPeer) {}
        galaxy::api::GalaxyID expectedPeer;
        galaxy::api::ChatRoomID chatRoomId = 0;
        uint32_t successes = 0;
        bool failed = false;
        void OnChatRoomWithUserRetrieveSuccess(galaxy::api::GalaxyID peerId, galaxy::api::ChatRoomID receivedChatRoomId) override
        {
            if (peerId != expectedPeer || receivedChatRoomId == 0 || (chatRoomId != 0 && chatRoomId != receivedChatRoomId)) failed = true;
            else chatRoomId = receivedChatRoomId;
            ++successes;
        }
        void OnChatRoomWithUserRetrieveFailure(galaxy::api::GalaxyID, FailureReason) override { failed = true; }
    } listener(peerId);
#if GALAXY_BUILD_FEATURE_HAS_ICHAT_ROOMLISTENERS
    chat->RequestChatRoomWithUser(peerId, &listener);
#else
    chat->RequestChatRoomWithUser(peerId);
#endif
    if (!pumpUntil(api, arguments.timeoutSeconds, [&listener] { return listener.successes != 0 || listener.failed; }) || listener.failed || listener.successes != 1) return false;
#if GALAXY_BUILD_FEATURE_HAS_ICHAT_ROOMLISTENERS
    chat->RequestChatRoomWithUser(peerId, &listener);
#else
    chat->RequestChatRoomWithUser(peerId);
#endif
    return pumpUntil(api, arguments.timeoutSeconds, [&listener] { return listener.successes == 2 || listener.failed; })
        && !listener.failed && listener.successes == 2 && listener.chatRoomId != 0
        && emit(arguments, "requester-room-reused") && waitForCompletion(arguments);
}

bool chatRoomReusePeer(Api& api, const Arguments& arguments)
{
    (void)api;
    return arguments.peerUserIds.size() == 1 && emit(arguments, "peer-ready") && waitForCompletion(arguments);
}

struct ChatRoomUnexpectedMessagesListener final : galaxy::api::GlobalChatRoomMessagesListener
{
    uint32_t received = 0;
    void OnChatRoomMessagesReceived(galaxy::api::ChatRoomID, uint32_t, uint32_t) override { ++received; }
};

struct ChatRoomMessageFailureListener final :
#if GALAXY_BUILD_FEATURE_HAS_ICHAT_ROOMLISTENERS
    galaxy::api::IChatRoomMessageSendListener
#else
    galaxy::api::GlobalChatRoomMessageSendListener
#endif
{
    explicit ChatRoomMessageFailureListener(galaxy::api::ChatRoomID expectedChatRoomId) : expectedChatRoomId(expectedChatRoomId) {}
    galaxy::api::ChatRoomID expectedChatRoomId;
    uint32_t expectedMessageIndex = 0;
    uint32_t successes = 0;
    uint32_t failures = 0;
    galaxy::api::ChatRoomID failedChatRoomId = 1;
    uint32_t failedMessageIndex = 0;
    FailureReason failureReason = FAILURE_REASON_UNDEFINED;
    void OnChatRoomMessageSendSuccess(galaxy::api::ChatRoomID, uint32_t, galaxy::api::ChatMessageID, uint32_t) override { ++successes; }
    void OnChatRoomMessageSendFailure(galaxy::api::ChatRoomID chatRoomId, uint32_t messageIndex, FailureReason receivedFailureReason) override
    {
        ++failures;
        failedChatRoomId = chatRoomId;
        failedMessageIndex = messageIndex;
        failureReason = receivedFailureReason;
    }
};

bool chatRoomUnknownSendFailure(Api& api, const Arguments& arguments)
{
    galaxy::api::IChat* chat = api.chat();
    if (chat == nullptr || !arguments.peerUserIds.empty()) return false;
    constexpr galaxy::api::ChatRoomID unknownChatRoomId = 0;
    ChatRoomUnexpectedMessagesListener messagesListener;
    ChatRoomMessageFailureListener sendListener(unknownChatRoomId);
#if GALAXY_BUILD_FEATURE_HAS_ICHAT_ROOMLISTENERS
    sendListener.expectedMessageIndex = chat->SendChatRoomMessage(unknownChatRoomId, chatRoomMessage, &sendListener);
#else
    sendListener.expectedMessageIndex = chat->SendChatRoomMessage(unknownChatRoomId, chatRoomMessage);
#endif
    if (!pumpUntil(api, arguments.timeoutSeconds, [&sendListener] { return sendListener.successes + sendListener.failures != 0; })) return false;
    const auto deadline = std::chrono::steady_clock::now() + std::chrono::milliseconds(250);
    while (std::chrono::steady_clock::now() < deadline)
    {
        api.processData();
        if (sendListener.successes != 0 || sendListener.failures != 1 || messagesListener.received != 0) return false;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return sendListener.failedChatRoomId == unknownChatRoomId && sendListener.failedMessageIndex == sendListener.expectedMessageIndex
        && sendListener.failureReason == ChatRoomMessageFailureListener::FAILURE_REASON_FORBIDDEN
        && emit(arguments, "unknown-send-forbidden");
}
#endif
}
