#if GALAXY_BUILD_FEATURE_HAS_ICHAT 

#include "Chat.hxx"

#include "Listeners/ChatListener.hxx"

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

	ChatImpl::ChatImpl(FuncT::F intf, IListenerRegistrar* notifications) :
		intf{ intf },
		notifications{ notifications },
		listeners{ notifications } {
		listeners.AddListener<ChatRoomWithUserRetrieveListener>();
		listeners.AddListener<ChatRoomMessageSendListener>();
		listeners.AddListener<ChatRoomMessagesListener>();
		listeners.AddListener<ChatRoomMessagesRetrieveListener>();
	}

	ChatImpl::~ChatImpl() {
		listeners.UnregisterAllListeners();
	}

	void ChatImpl::RequestChatRoomWithUser(GalaxyID userID
#if GALAXY_BUILD_FEATURE_HAS_ICHAT_ROOMLISTENERS
		, IChatRoomWithUserRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
#if GALAXY_BUILD_FEATURE_HAS_ICHAT_ROOMLISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		intf()->RequestChatRoomWithUser(userID
#if GALAXY_BUILD_FEATURE_HAS_ICHAT_ROOMLISTENERS
			, listener
#endif
			);
	}

	void ChatImpl::RequestChatRoomMessages(ChatRoomID chatRoomID, uint32_t limit, ChatMessageID referenceMessageID
#if GALAXY_BUILD_FEATURE_HAS_ICHAT_ROOMLISTENERS
		, IChatRoomMessagesRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("chatRoomID: {}", chatRoomID));
			trace.write_all(std::format("limit: {}", limit));
			trace.write_all(std::format("referenceMessageID: {}", referenceMessageID));
#if GALAXY_BUILD_FEATURE_HAS_ICHAT_ROOMLISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		intf()->RequestChatRoomMessages(chatRoomID, limit, referenceMessageID
#if GALAXY_BUILD_FEATURE_HAS_ICHAT_ROOMLISTENERS
			, listener
#endif
		);
	}

	uint32_t ChatImpl::SendChatRoomMessage(ChatRoomID chatRoomID, const char* msg
#if GALAXY_BUILD_FEATURE_HAS_ICHAT_ROOMLISTENERS
		, IChatRoomMessageSendListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("chatRoomID: {}", chatRoomID));
			trace.write_all(std::format("msg: {}", util::safe_fix_null_char_ptr_annotate_ret(msg)));
#if GALAXY_BUILD_FEATURE_HAS_ICHAT_ROOMLISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		auto result = intf()->SendChatRoomMessage(chatRoomID, msg
#if GALAXY_BUILD_FEATURE_HAS_ICHAT_ROOMLISTENERS
			, listener
#endif
		);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	uint32_t ChatImpl::GetChatRoomMessageByIndex(uint32_t index, ChatMessageID& messageID, ChatMessageType& messageType, GalaxyID& senderID, uint32_t& sendTime, char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("index: {}", index));
			trace.write_all(std::format("buffer: {}", (void*)buffer));
			trace.write_all(std::format("bufferLength: {}", bufferLength));
		}

		auto result = intf()->GetChatRoomMessageByIndex(index, messageID, messageType, senderID, sendTime, buffer, bufferLength);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
			trace.write_all(std::format("messageID: {}", messageID));
			trace.write_all(std::format("messageType: {}", magic_enum::enum_name(messageType)));
			trace.write_all(std::format("senderID: {}", senderID));
			trace.write_all(std::format("sendTime: {}", sendTime));
			trace.write_all(std::format("buffer: {}", util::safe_fix_null_char_ptr_annotate(buffer, bufferLength)));
		}

		return result;
	}

	uint32_t ChatImpl::GetChatRoomMemberCount(ChatRoomID chatRoomID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("chatRoomID: {}", chatRoomID));
		}

		auto result = intf()->GetChatRoomMemberCount(chatRoomID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	GalaxyID ChatImpl::GetChatRoomMemberUserIDByIndex(ChatRoomID chatRoomID, uint32_t index) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("chatRoomID: {}", chatRoomID));
			trace.write_all(std::format("index: {}", index));
		}

		auto result = intf()->GetChatRoomMemberUserIDByIndex(chatRoomID, index);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	uint32_t ChatImpl::GetChatRoomUnreadMessageCount(ChatRoomID chatRoomID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("chatRoomID: {}", chatRoomID));
		}

		auto result = intf()->GetChatRoomUnreadMessageCount(chatRoomID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	void ChatImpl::MarkChatRoomAsRead(ChatRoomID chatRoomID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("chatRoomID: {}", chatRoomID));
		}

		intf()->GetChatRoomUnreadMessageCount(chatRoomID);
	}
}
#endif
