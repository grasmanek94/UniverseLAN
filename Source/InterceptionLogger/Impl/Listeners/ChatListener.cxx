#if GALAXY_BUILD_FEATURE_HAS_ICHAT 

#include "ChatListener.hxx"
#include "ProxifySingleShotListener.hxx"

#include <GalaxyID.hxx>
#include <Tracer.hxx>
#include <SafeStringCopy.hxx>

#include <magic_enum/magic_enum.hpp>

#include <format>

namespace universelan::client {
	using namespace galaxy::api;

	namespace {
		const auto TraceContext = tracer::Trace::ICHAT;
	}

	void ChatRoomWithUserRetrieveListener::OnChatRoomWithUserRetrieveSuccess(GalaxyID userID, ChatRoomID chatRoomID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("chatRoomID: {}", chatRoomID));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnChatRoomWithUserRetrieveSuccess(userID, chatRoomID));
	}

	void ChatRoomWithUserRetrieveListener::OnChatRoomWithUserRetrieveFailure(GalaxyID userID, FailureReason failureReason) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnChatRoomWithUserRetrieveFailure(userID, failureReason));
	}

	void ChatRoomMessageSendListener::OnChatRoomMessageSendSuccess(ChatRoomID chatRoomID, uint32_t sentMessageIndex, ChatMessageID messageID, uint32_t sendTime)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("chatRoomID: {}", chatRoomID));
			trace.write_all(std::format("sentMessageIndex: {}", sentMessageIndex));
			trace.write_all(std::format("messageID: {}", messageID));
			trace.write_all(std::format("sendTime: {}", sendTime));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnChatRoomMessageSendSuccess(chatRoomID, sentMessageIndex, messageID, sendTime));
	}

	void ChatRoomMessageSendListener::OnChatRoomMessageSendFailure(ChatRoomID chatRoomID, uint32_t sentMessageIndex, FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("chatRoomID: {}", chatRoomID));
			trace.write_all(std::format("sentMessageIndex: {}", sentMessageIndex));
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnChatRoomMessageSendFailure(chatRoomID, sentMessageIndex, failureReason));
	}

	void ChatRoomMessagesListener::OnChatRoomMessagesReceived(ChatRoomID chatRoomID, uint32_t messageCount, uint32_t longestMessageLenght)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("chatRoomID: {}", chatRoomID));
			trace.write_all(std::format("messageCount: {}", messageCount));
			trace.write_all(std::format("longestMessageLenght: {}", longestMessageLenght));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnChatRoomMessagesReceived(chatRoomID, messageCount, longestMessageLenght));
	}

#if GALAXY_BUILD_FEATURE_HAS_ICHATROOMMESSAGERETRIEVELISTENER
	void ChatRoomMessagesRetrieveListener::OnChatRoomMessagesRetrieveSuccess(ChatRoomID chatRoomID, uint32_t messageCount, uint32_t longestMessageLenght)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("chatRoomID: {}", chatRoomID));
			trace.write_all(std::format("messageCount: {}", messageCount));
			trace.write_all(std::format("longestMessageLenght: {}", longestMessageLenght));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnChatRoomMessagesRetrieveSuccess(chatRoomID, messageCount, longestMessageLenght));
	}

	void ChatRoomMessagesRetrieveListener::OnChatRoomMessagesRetrieveFailure(ChatRoomID chatRoomID, FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("chatRoomID: {}", chatRoomID));
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnChatRoomMessagesRetrieveFailure(chatRoomID, failureReason));
	}
#endif
}
#endif
