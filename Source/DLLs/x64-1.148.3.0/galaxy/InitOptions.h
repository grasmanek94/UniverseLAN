#ifndef GALAXY_INIT_OPTIONS_H
#define GALAXY_INIT_OPTIONS_H

/**
 * @file
 * Contains class that holds Galaxy initialization parameters.
 */
#include "GalaxyAllocator.h"
#include "GalaxyThread.h"

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
			 * @param [in] _galaxyAllocator The custom memory allocator. The same instance has to be passed to both Galaxy Peer and Game Server.
			 * @param [in] _storagePath Path to a directory that can be used for storing internal SDK data. Used only on Android devices. See remarks for more information.
			 * @param [in] _host The local IP address this peer would bind to.
			 * @param [in] _port The local port used to communicate with GOG Galaxy Multiplayer server and other players.
			 * @param [in] _galaxyThreadFactory The custom thread factory used by GOG Galaxy SDK to spawn internal threads.
			 */
			InitOptions(
				const char* _clientID,
				const char* _clientSecret,
				const char* _configFilePath = ".",
				GalaxyAllocator* _galaxyAllocator = NULL,
				const char* _storagePath = NULL,
				const char* _host = NULL,
				uint16_t _port = 0,
				IGalaxyThreadFactory* _galaxyThreadFactory = NULL
			)
				: clientID(_clientID)
				, clientSecret(_clientSecret)
				, configFilePath(_configFilePath)
				, storagePath(_storagePath)
				, galaxyAllocator(_galaxyAllocator)
				, galaxyThreadFactory(_galaxyThreadFactory)
				, host(_host)
				, port(_port)
			{
			}

			const char* clientID; ///< The ID of the client.
			const char* clientSecret; ///< The secret of the client.
			const char* configFilePath; ///< The path to folder which contains configuration files.
			const char* storagePath; ///< The path to folder for storing internal SDK data. Used only on Android devices.
			GalaxyAllocator* galaxyAllocator; ///< The custom memory allocator used by GOG Galaxy SDK.
			IGalaxyThreadFactory* galaxyThreadFactory; ///< The custom thread factory used by GOG Galaxy SDK to spawn internal threads.
			const char* host; ///< The local IP address this peer would bind to.
			uint16_t port; ///< The local port used to communicate with GOG Galaxy Multiplayer server and other players.
		};

		/** @} */
	}
}

#endif