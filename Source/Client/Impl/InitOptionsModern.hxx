#pragma once

#if GALAXY_BUILD_FEATURE_FACTORY_INTERFACE
#include "InitOptionsFactory.hxx"
#else
#include <InitOptions.h>
#endif

#include <string>

namespace universelan::client {
	using namespace galaxy::api;

	// this is to help intellisense complaining about ambiguous classes, compilation works fine though
#if GALAXY_BUILD_FEATURE_FACTORY_INTERFACE
	using InitOptionsImpl = InitOptionsFactory;
#else
	using InitOptionsImpl = InitOptions;
#endif

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
		InitOptionsModern(const InitOptionsImpl& initOptions);

		std::string clientID; ///< The ID of the client.
		std::string clientSecret; ///< The secret of the client.
		std::string configFilePath; ///< The path to folder which contains configuration files.
		std::string storagePath; ///< The path to folder for storing internal SDK data. Used only on Android devices.
#if !GALAXY_BUILD_FEATURE_FACTORY_INTERFACE
		GalaxyAllocator* galaxyAllocator;
#endif
#if (GALAXY_VERSION) > 112400
		IGalaxyThreadFactory* galaxyThreadFactory; ///< The custom thread factory used by GOG Galaxy SDK to spawn internal threads.
		std::string host; ///< The local IP address this peer would bind to.
		uint16_t port; ///< The local port used to communicate with GOG Galaxy Multiplayer server and other players.
#endif
	};

	/** @} */
}
