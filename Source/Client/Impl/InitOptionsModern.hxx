#pragma once

#if GALAXY_BUILD_FEATURE_HAS_INITOPTIONS

#if GALAXY_BUILD_FEATURE_HAS_INITOPTIONS_MODERN
#include <InitOptions.h>
#else
#include <IGalaxy.h>
#endif

#else
#include "InitOptionsFactory.hxx"
#endif

#include <string>

namespace universelan::client {

	// this is to help intellisense complaining about ambiguous classes, compilation works fine though
#if GALAXY_BUILD_FEATURE_HAS_INITOPTIONS	
	using InitOptionsImpl = galaxy::api::InitOptions;
#else
	using InitOptionsImpl = galaxy::api::InitOptionsFactory;
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
		InitOptionsModern();

		std::string clientID; ///< The ID of the client.
		std::string clientSecret; ///< The secret of the client.
		std::string configFilePath; ///< The path to folder which contains configuration files.
		std::string storagePath; ///< The path to folder for storing internal SDK data. Used only on Android devices.
		bool throwExceptions;
#if GALAXY_BUILD_FEATURE_ALLOCATOR
		galaxy::api::GalaxyAllocator* galaxyAllocator;
#endif
#if GALAXY_BUILD_FEATURE_HAS_IGALAXYTHREADFACTORY
		galaxy::api::IGalaxyThreadFactory* galaxyThreadFactory; ///< The custom thread factory used by GOG Galaxy SDK to spawn internal threads.
#endif
#if (GALAXY_VERSION) > 11240
		std::string host; ///< The local IP address this peer would bind to.
		uint16_t port; ///< The local port used to communicate with GOG Galaxy Multiplayer server and other players.
#endif
	};

	/** @} */
}
