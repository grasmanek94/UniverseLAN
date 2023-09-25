#pragma once

#include <GalaxyApi.h>

#include <cstddef>
#include <cstdint>

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
}
