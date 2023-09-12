#ifndef LSFDRMFG_IMPL_INIT_OPTIONS_H
#define LSFDRMFG_IMPL_INIT_OPTIONS_H

#if GALAXY_BUILD_FEATURE_FACTORY_INTERFACE
#include <stdint.h>
#include <cstddef>

namespace galaxy
{
	namespace api
	{
		/**
		 * @addtogroup api
		 * @{
		 */

		 /**
		 * The group of options used for Init configuration.
		 */
		struct InitOptions
		{
			/**
			 * InitOptions constructor.
			 *
			 * @remark On Android device Galaxy SDK needs a directory for internal storage (to keep a copy of system CA certificates).
			 * It should be an existing directory within the application file storage.
			 *
			 * @param [in] _clientID The ID of the client.
			 * @param [in] _clientSecret The secret of the client.
			 * @param [in] _configFilePath The path to folder which contains configuration files.
			 * @param [in] _galaxyAllocator The custom memory allocator. Shall only be set once for both Galaxy Peer and Game Server.
			 * @param [in] _storagePath Path to a directory that can be used for storing internal SDK data. Used only on Android devices. See remarks for more information.
			 */
			InitOptions(const char* _clientID, const char* _clientSecret, const char* _configFilePath = ".", void* _galaxyAllocator = NULL, const char* _storagePath = NULL)
				: clientID(_clientID)
				, clientSecret(_clientSecret)
				, configFilePath(_configFilePath)
				, storagePath(_storagePath)
			{
			}

			const char* clientID; ///< The ID of the client.
			const char* clientSecret; ///< The secret of the client.
			const char* configFilePath; ///< The path to folder which contains configuration files.
			const char* storagePath; ///< The path to folder for storing internal SDK data. Used only on Android devices.
		};

		/** @} */
	}
}
#else
#include <InitOptions.h>
#endif

#include <string>

namespace universelan::client {
	using namespace galaxy::api;

	/**
	 * @addtogroup api
	 * @{
	 */

	 /**
	 * The group of options used for Init configuration.
	 */
	struct InitOptionsModern
	{
		/**
		 * InitOptions constructor.
		 *
		 * @param [in] initOptions InitOptions passed from Init function.
		 */
		InitOptionsModern(const InitOptions& initOptions);

		std::string clientID; ///< The ID of the client.
		std::string clientSecret; ///< The secret of the client.
		std::string configFilePath; ///< The path to folder which contains configuration files.
		std::string storagePath; ///< The path to folder for storing internal SDK data. Used only on Android devices.
		GalaxyAllocator* galaxyAllocator; ///< The custom memory allocator used by GOG Galaxy SDK.
#if (GALAXY_VERSION) > 112400
		IGalaxyThreadFactory* galaxyThreadFactory; ///< The custom thread factory used by GOG Galaxy SDK to spawn internal threads.
		std::string host; ///< The local IP address this peer would bind to.
		uint16_t port; ///< The local port used to communicate with GOG Galaxy Multiplayer server and other players.
#endif
	};

	/** @} */
}

#endif
