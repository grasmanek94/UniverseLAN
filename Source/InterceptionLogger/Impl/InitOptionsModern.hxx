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

#include <optional>
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
		using GalaxyAllocator_T =
#if GALAXY_BUILD_FEATURE_ALLOCATOR
			galaxy::api::GalaxyAllocator
#else
			void
#endif
			;

		using GalaxyThreadFactory_T =
#if GALAXY_BUILD_FEATURE_HAS_IGALAXYTHREADFACTORY
			galaxy::api::IGalaxyThreadFactory
#else 
			void
#endif
			;


		/**
		 * InitOptions constructor.
		 *
		 * @param [in] initOptions InitOptions passed from Init function.
		 */
		InitOptionsModern(const InitOptionsImpl& initOptions);
		InitOptionsModern();

		std::optional<const std::string> clientID; ///< The ID of the client.
		std::optional<const std::string> clientSecret; ///< The secret of the client.
		std::optional<const std::string> configFilePath; ///< The path to folder which contains configuration files.
		std::optional<const std::string> storagePath; ///< The path to folder for storing internal SDK data. Used only on Android devices.
		std::optional<const std::string> galaxyPeerPath;

		bool throwExceptions;

		GalaxyAllocator_T* galaxyAllocator;

		GalaxyThreadFactory_T* galaxyThreadFactory; ///< The custom thread factory used by GOG Galaxy SDK to spawn internal threads.

		std::optional<std::string> host; ///< The local IP address this peer would bind to.

		uint16_t port; ///< The local port used to communicate with GOG Galaxy Multiplayer server and other players.

		bool local_init;

		void SetClientID(const char* client_id);
		void SetClientSecret(const char* client_secret);
		void SetConfigFilePath(const char* config_file_path);
		void SetStoragePath(const char* storage_path);
		void SetGalaxyPeerPath(const char* galaxy_peer_path);
		void SetHost(const char* host_addr);

		const char* GetClientID();
		const char* GetClientSecret();
		const char* GetConfigFilePath();
		const char* GetStoragePath();
		const char* GetGalaxyPeerPath();
		const char* GetHost();
	};

	/** @} */
}
