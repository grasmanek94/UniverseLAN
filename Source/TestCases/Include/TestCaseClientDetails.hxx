#pragma once

#include <array>
#include <chrono>
#include <format>
#include <functional>
#include <memory>
#include <string>
#include <string_view>
#include <thread>
#include <vector>

#include <magic_enum/magic_enum.hpp>

namespace galaxy::api {
	using namespace std::string_view_literals;

#ifndef GALAXY_SDK_CLIENT_ID
	// these are public and published by GOG themselves for everyone to use
	constexpr std::string_view CLIENT_ID = "50225266424144145";
	constexpr std::string_view CLIENT_SECRET = "45955f1104f99b625a5733fa1848479b43d63bdb98f0929e37c9affaf900e99f";
#else
	constexpr std::string_view CLIENT_ID = GALAXY_SDK_CLIENT_ID;
	constexpr std::string_view CLIENT_SECRET = GALAXY_SDK_CLIENT_SECRET;
#endif

	// List of all in-game achievements api keys
	constexpr std::array ACHIEVEMENTS_LIST = {
		"launchTheGame"sv,
		"putBlack"sv,
		"putBlue"sv,
		"putBrown"sv,
		"putGreen"sv,
		"putPink"sv,
		"putRed"sv,
		"putYellow"sv,
		"winSPRound"sv,
		"win2PRound"sv,
		"draw2PRound"sv,
		"winMPRound"sv,
		"drawMPRound"sv,
		"loseMPRound"sv
	};

	//  all in-game statistics api keys
	constexpr std::array STATISTICS_FLOAT_LIST = {
		"lastScore"sv,
		"highestScore"sv
	};

	//  all in-game statistics api keys
	constexpr std::array STATISTICS_INT_LIST = {
		"fouls"sv,
		"shotsTaken"sv
	};

	//  all in-game leaderboards api keys
	constexpr std::array LEADERBOARDS_LIST = {
		"fouls"sv,
		"highestScore"sv,
		"shotsTaken"sv
	};


#ifndef GALAXY_SDK_USER_CREDENTIALS_USER1_NAME
	constexpr std::array USER_CREDENTIALS = {
		std::array{""sv,""sv}
	};

#else
	constexpr std::array USER_CREDENTIALS = {
		std::array{GALAXY_SDK_USER_CREDENTIALS_USER1_NAME,GALAXY_SDK_USER_CREDENTIALS_USER1_PASSWORD},
		std::array{GALAXY_SDK_USER_CREDENTIALS_USER2_NAME,GALAXY_SDK_USER_CREDENTIALS_USER2_PASSWORD}
	};
#endif

	constexpr std::array LOBBY_TEST_DATA = {
		std::array{"string_test"sv,"abbcccddddz--xyz"sv},
		std::array{"string_test2"sv,"0123456789"sv},
		std::array{"reverse"sv,"9876543210"sv},
		std::array{"long"sv,"00000000000000000000000000000000000000000000000000000000000aaaaaaaaaaaaa0a0a0aaa0a0aa0aa0aa0aa0a0a0aaa0a0a0a0a00000000000000aaaaaaaaaaaaaaaaaa0a0a00a0aa0"sv}
	};
}

#include <GalaxyApi.h>
#include <Tracer.hxx>

namespace tracer = universelan::tracer;

namespace galaxy::api {
#if !GALAXY_BUILD_FEATURE_HAS_LOBBYTOPOLOGYTYPE_ENUM
	enum LobbyTopologyType
	{
		DEPRECATED_LOBBY_TOPOLOGY_TYPE_FCM_HOST_MIGRATION = 0, ///< All users are connected with each other. Disconnection of lobby owner results in choosing a new one. Deprecated: use LOBBY_TOPOLOGY_TYPE_FCM_OWNERSHIP_TRANSITION instead.
		LOBBY_TOPOLOGY_TYPE_FCM = 1, ///< All users are connected with each other. Disconnection of lobby owner results in closing the lobby.
		LOBBY_TOPOLOGY_TYPE_STAR = 2, ///< All users are connected with lobby owner. Disconnection of lobby owner results in closing the lobby.
		LOBBY_TOPOLOGY_TYPE_CONNECTIONLESS = 3, ///< All users are connected only with server. Disconnection of lobby owner results in choosing a new one.
		LOBBY_TOPOLOGY_TYPE_FCM_OWNERSHIP_TRANSITION = 4 ///< All users are connected with each other. Disconnection of lobby owner results in choosing a new one.
};
#endif

#if !GALAXY_BUILD_FEATURE_HAS_ISTORAGE
	using SharedFileID = uint64_t;
#endif


#if !GALAXY_BUILD_FEATURE_HAS_ILOBBYDATARETRIEVELISTENER
	namespace ILobbyDataRetrieveListener {
		enum FailureReason
		{
			FAILURE_REASON_UNDEFINED, ///< Unspecified error.
			FAILURE_REASON_LOBBY_DOES_NOT_EXIST, ///< Specified lobby does not exist.
		};
	}
#endif

#if !GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LIST_RESULT
	enum LobbyListResult
	{
		LOBBY_LIST_RESULT_SUCCESS,
		LOBBY_LIST_RESULT_ERROR,
		LOBBY_LIST_RESULT_CONNECTION_FAILURE
	};
#endif

#if !GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LEAVE_REASON
	enum LobbyLeaveReason
	{
		LOBBY_LEAVE_REASON_UNDEFINED,
		LOBBY_LEAVE_REASON_USER_LEFT,
		LOBBY_LEAVE_REASON_LOBBY_CLOSED,
		LOBBY_LEAVE_REASON_CONNECTION_LOST
	};
#endif

}

namespace galaxy::api {

#if GALAXY_BUILD_FEATURE_GALAXYID_HAS_IDTYPE
	using IDType = GalaxyID::IDType;
#else
	enum IDType {
		ID_TYPE_UNASSIGNED,
		ID_TYPE_LOBBY,
		ID_TYPE_USER
	};
#endif
	/**
	 * Returns the type of the ID.
	 *
	 * @return The type of the ID.
	 */
	inline IDType GetIDType(uint64_t value)
	{
		return static_cast<IDType>(value >> 56);
	}

	/**
	 * Returns the type of the ID.
	 *
	 * @return The type of the ID.
	 */
	inline IDType GetIDType(GalaxyID value)
	{
		return static_cast<IDType>(value.ToUint64() >> 56);
	}

	inline GalaxyID FromRealID(IDType type, uint64_t value)
	{
		/**
		 * The numerical value used when the instance of GalaxyID is not valid.
		 */
		static const uint64_t UNASSIGNED_VALUE = 0;

		assert(type != IDType::ID_TYPE_UNASSIGNED);
		assert(value != UNASSIGNED_VALUE);
		assert(static_cast<IDType>(value >> 56) == IDType::ID_TYPE_UNASSIGNED);
		return GalaxyID(static_cast<uint64_t>(type) << 56 | value);
	}

	inline uint64_t GetRealID(const GalaxyID& id)
	{
		return id.ToUint64() & 0x00ffffffffffffffULL;
	}
}

template <>
struct std::formatter<galaxy::api::GalaxyID> : std::formatter<std::string> {
	auto format(galaxy::api::GalaxyID p, format_context& ctx) const {
		return formatter<string>::format(
			std::format("{}({})", GetRealID(p), magic_enum::enum_name(galaxy::api::GetIDType(p))), ctx);
	}
};

using namespace galaxy::api;


template<typename T>
bool compare_equal(const char* const data, const std::vector<T>& vec) {
	for (size_t i = 0; i < vec.size(); ++i) {
		if ((T)data[i] != vec[i]) {
			return false;
		}
	}

	return true;
}

bool compare_equal(const char* const data, unsigned char value, size_t size) {
	for (size_t i = 0; i < size; ++i) {
		if ((unsigned char)data[i] != value) {
			return false;
		}
	}

	return true;
}

bool compare_equal(const char* const data, const std::string& str) {
	for (size_t i = 0; i < str.length() + 1; ++i) {
		if (data[i] != str.c_str()[i]) {
			return false;
		}
	}

	return true;
}

#if GALAXY_BUILD_FEATURE_HAS_IGALAXY
#define GET_GALAXY_API(what) galaxy_api->Get ## what
#define GET_GALAXY_API_AS_IS(what) galaxy_api->what

galaxy::api::IGalaxy* galaxy_api = nullptr;
#else
#define GET_GALAXY_API(what) galaxy::api::what
#define GET_GALAXY_API_AS_IS(what) galaxy::api::what
#endif

#if GALAXY_BUILD_FEATURE_HAS_IGALAXY && GALAXY_BUILD_FEATURE_HAS_INITOPTIONS
#define GALAXY_INIT() \
try { \
	galaxy_api = galaxy::api::GalaxyFactory::CreateInstance(); \
	galaxy::api::InitOptions options(galaxy::api::CLIENT_ID.data(), galaxy::api::CLIENT_SECRET.data()); \
	GET_GALAXY_API_AS_IS(Init(options)); \
} \
catch (const IError& err) { \
	std::cerr << err.GetMsg() << std::endl; \
}
#endif

#if GALAXY_BUILD_FEATURE_HAS_IGALAXY && !GALAXY_BUILD_FEATURE_HAS_INITOPTIONS
#define GALAXY_INIT() \
try { \
	galaxy_api = galaxy::api::GalaxyFactory::CreateInstance(); \
	GET_GALAXY_API_AS_IS(Init(galaxy::api::CLIENT_ID.data(), galaxy::api::CLIENT_SECRET.data())); \
} \
catch (const IError& err) { \
	std::cerr << err.GetMsg() << std::endl; \
}
#endif

#if !GALAXY_BUILD_FEATURE_HAS_IGALAXY && GALAXY_BUILD_FEATURE_HAS_INITOPTIONS
#define GALAXY_INIT() \
try { \
	galaxy::api::InitOptions options(galaxy::api::CLIENT_ID.data(), galaxy::api::CLIENT_SECRET.data()); \
	GET_GALAXY_API_AS_IS(Init(options)); \
} \
catch (const IError& err) { \
	std::cerr << err.GetMsg() << std::endl; \
}
#endif

#if !GALAXY_BUILD_FEATURE_HAS_IGALAXY && !GALAXY_BUILD_FEATURE_HAS_INITOPTIONS
#define GALAXY_INIT() \
try { \
	GET_GALAXY_API_AS_IS(Init(galaxy::api::CLIENT_ID.data(), galaxy::api::CLIENT_SECRET.data())); \
} \
catch (const IError& err) { \
	std::cerr << err.GetMsg() << std::endl; \
}
#endif

#define GALAXY_DEINIT() GET_GALAXY_API_AS_IS(Shutdown())

#if !GALAXY_BUILD_FEATURE_SIGNIN_RENAMED_TO_SIGNINGALAXY
#define SignInGalaxy SignIn
#endif

#if !GALAXY_BUILD_FEATURE_SIGNIN_RENAMED_TO_SIGNINCREDENTIALS
#define SignInCredentials SignIn
#endif

#include "TestCaseDelayRunner.hxx"
#include "TestCaseAuthListener.hxx"
#include "TestCaseAccessTokenListener.hxx"
#include "TestCaseAchievementChangeListener.hxx"
#include "TestCaseChatRoomMessageSendListener.hxx"
#include "TestCaseChatRoomMessagesListener.hxx"
#include "TestCaseChatRoomMessagesRetrieveListener.hxx"
#include "TestCaseChatRoomWithUserRetrieveListener.hxx"
#include "TestCaseConnectionCloseListener.hxx"
#include "TestCaseConnectionDataListener.hxx"
#include "TestCaseConnectionOpenListener.hxx"
#include "TestCaseEncryptedAppTicketListener.hxx"
#include "TestCaseFileShareListener.hxx"
#include "TestCaseFriendAddListener.hxx"
#include "TestCaseFriendDeleteListener.hxx"
#include "TestCaseFriendInvitationListRetrieveListener.hxx"
#include "TestCaseFriendInvitationListener.hxx"
#include "TestCaseFriendInvitationRespondToListener.hxx"
#include "TestCaseFriendInvitationSendListener.hxx"
#include "TestCaseFriendListListener.hxx"
#include "TestCaseGameInvitationReceivedListener.hxx"
#include "TestCaseGameJoinRequestedListener.hxx"
#include "TestCaseGogServicesConnectionStateListener.hxx"
#include "TestCaseLeaderboardEntriesRetrieveListener.hxx"
#include "TestCaseLeaderboardRetrieveListener.hxx"
#include "TestCaseLeaderboardScoreUpdateListener.hxx"
#include "TestCaseLeaderboardsRetrieveListener.hxx"
#include "TestCaseLobbyCreatedListener.hxx"
#include "TestCaseLobbyDataListener.hxx"
#include "TestCaseLobbyDataRetrieveListener.hxx"
#include "TestCaseLobbyEnteredListener.hxx"
#include "TestCaseLobbyLeftListener.hxx"
#include "TestCaseLobbyListListener.hxx"
#include "TestCaseLobbyMemberStateListener.hxx"
#include "TestCaseLobbyMessageListener.hxx"
#include "TestCaseLobbyOwnerChangeListener.hxx"
#include "TestCaseNatTypeDetectionListener.hxx"
#include "TestCaseNetworkingListener.hxx"
#include "TestCaseNotificationListener.hxx"
#include "TestCaseOperationalStateChangeListener.hxx"
#include "TestCaseOtherSessionStartListener.hxx"
#include "TestCaseOverlayInitializationStateChangeListener.hxx"
#include "TestCaseOverlayStateChangeListener.hxx"
#include "TestCaseOverlayVisibilityChangeListener.hxx"
#include "TestCasePersonaDataChangedListener.hxx"
#include "TestCaseRichPresenceChangeListener.hxx"
#include "TestCaseRichPresenceListener.hxx"
#include "TestCaseRichPresenceRetrieveListener.hxx"
#include "TestCaseSendInvitationListener.hxx"
#include "TestCaseSentFriendInvitationListRetrieveListener.hxx"
#include "TestCaseServerNetworkingListener.hxx"
#include "TestCaseSharedFileDownloadListener.hxx"
#include "TestCaseSpecificUserDataListener.hxx"
#include "TestCaseStatsAndAchievementsStoreListener.hxx"
#include "TestCaseTelemetryEventSendListener.hxx"
#include "TestCaseUserDataListener.hxx"
#include "TestCaseUserFindListener.hxx"
#include "TestCaseUserInformationRetrieveListener.hxx"
#include "TestCaseUserStatsAndAchievementsRetrieveListener.hxx"
#include "TestCaseUserTimePlayedRetrieveListener.hxx"
#include "TestCaseInitListener.hxx"
