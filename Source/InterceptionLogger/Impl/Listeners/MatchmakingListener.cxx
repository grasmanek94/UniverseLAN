#include "MatchmakingListener.hxx"

#include <GalaxyID.hxx>
#include <Tracer.hxx>
#include <SafeStringCopy.hxx>

#include <magic_enum/magic_enum.hpp>

#include <format>

namespace universelan::client {
	using namespace galaxy::api;

	namespace {
		const auto TraceContext = tracer::Trace::IMATCHMAKING;
	}

	void LobbyListListener::OnLobbyList(uint32_t lobbyCount, LobbyListResult result)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyCount: {}", lobbyCount));
			trace.write_all(std::format("result: {}", magic_enum::enum_name(result)));
		}
	}

	void LobbyListListener::OnLobbyList(uint32_t lobbyCount, bool ioFailure) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyCount: {}", lobbyCount));
			trace.write_all(std::format("ioFailure: {}", ioFailure));
		}
	}
	
	void LobbyCreatedListener::OnLobbyCreated(const GalaxyID& lobbyID, LobbyCreateResult result)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyID: {}", lobbyID));
			trace.write_all(std::format("result: {}", magic_enum::enum_name(result)));
		}
	}

	void LobbyEnteredListener::OnLobbyEntered(const GalaxyID& lobbyID, LobbyEnterResult result)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyID: {}", lobbyID));
			trace.write_all(std::format("result: {}", magic_enum::enum_name(result)));
		}
	}

	void LobbyLeftListener::OnLobbyLeft(const GalaxyID& lobbyID, LobbyLeaveReason leaveReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyID: {}", lobbyID));
			trace.write_all(std::format("leaveReason: {}", magic_enum::enum_name(leaveReason)));
		}
	}

	void LobbyLeftListener::OnLobbyLeft(const GalaxyID& lobbyID, bool ioFailure)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyID: {}", lobbyID));
			trace.write_all(std::format("ioFailure: {}", ioFailure));
		}
	}

	void LobbyDataListener::OnLobbyDataUpdated(const GalaxyID& lobbyID, const GalaxyID& memberID)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyID: {}", lobbyID));
			trace.write_all(std::format("memberID: {}", memberID));
		}
	}

#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
	void LobbyDataUpdateListener::OnLobbyDataUpdateSuccess(const GalaxyID& lobbyID)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyID: {}", lobbyID));
		}
	}

	void LobbyDataUpdateListener::OnLobbyDataUpdateFailure(const GalaxyID& lobbyID, FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyID: {}", lobbyID));
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}
	}

	void LobbyMemberDataUpdateListener::OnLobbyMemberDataUpdateSuccess(const GalaxyID& lobbyID, const GalaxyID& memberID)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyID: {}", lobbyID));
			trace.write_all(std::format("memberID: {}", memberID));
		}
	}

	void LobbyMemberDataUpdateListener::OnLobbyMemberDataUpdateFailure(const GalaxyID& lobbyID, const GalaxyID& memberID, FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyID: {}", lobbyID));
			trace.write_all(std::format("memberID: {}", memberID));
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_ILOBBYDATARETRIEVELISTENER
	void LobbyDataRetrieveListener::OnLobbyDataRetrieveSuccess(const GalaxyID& lobbyID)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyID: {}", lobbyID));
		}
	}

	void LobbyDataRetrieveListener::OnLobbyDataRetrieveFailure(const GalaxyID& lobbyID, FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyID: {}", lobbyID));
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}
	}
#endif

	void LobbyMemberStateListener::OnLobbyMemberStateChanged(const GalaxyID& lobbyID, const GalaxyID& memberID, LobbyMemberStateChange memberStateChange)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyID: {}", lobbyID));
			trace.write_all(std::format("memberID: {}", memberID));
			trace.write_all(std::format("memberStateChange: {}", magic_enum::enum_name(memberStateChange)));
		}
	}

	void LobbyOwnerChangeListener::OnLobbyOwnerChanged(const GalaxyID& lobbyID, const GalaxyID& newOwnerID)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyID: {}", lobbyID));
			trace.write_all(std::format("newOwnerID: {}", newOwnerID));
		}
	}

	void LobbyMessageListener::OnLobbyMessageReceived(const GalaxyID& lobbyID, const GalaxyID& senderID, uint32_t messageID, uint32_t messageLength)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyID: {}", lobbyID));
			trace.write_all(std::format("senderID: {}", senderID));
			trace.write_all(std::format("messageID: {}", messageID));
			trace.write_all(std::format("messageLength: {}", messageLength));
		}
	}
}
