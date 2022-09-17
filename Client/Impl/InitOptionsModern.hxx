#ifndef LSFDRMFG_IMPL_INIT_OPTIONS_H
#define LSFDRMFG_IMPL_INIT_OPTIONS_H

#include <InitOptions.h>
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
		InitOptionsModern(const InitOptions& initOptions) :
			clientID{ initOptions.clientID },
			clientSecret{ initOptions.clientSecret },
			configFilePath{ initOptions.configFilePath != nullptr ? initOptions.configFilePath : "" },
			storagePath{ initOptions.storagePath != nullptr ? initOptions.storagePath : "" },
			galaxyAllocator{ initOptions.galaxyAllocator },
			galaxyThreadFactory{ initOptions.galaxyThreadFactory },
			host{ initOptions.host != nullptr ? initOptions.host : "" },
			port{ initOptions.port }
		{ }

		const std::string clientID; ///< The ID of the client.
		const std::string clientSecret; ///< The secret of the client.
		const std::string configFilePath; ///< The path to folder which contains configuration files.
		const std::string storagePath; ///< The path to folder for storing internal SDK data. Used only on Android devices.
		const GalaxyAllocator* galaxyAllocator; ///< The custom memory allocator used by GOG Galaxy SDK.
		const IGalaxyThreadFactory* galaxyThreadFactory; ///< The custom thread factory used by GOG Galaxy SDK to spawn internal threads.
		const std::string host; ///< The local IP address this peer would bind to.
		const uint16_t port; ///< The local port used to communicate with GOG Galaxy Multiplayer server and other players.
	};

	/** @} */
}

#endif
