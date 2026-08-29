#include "InitOptionsModern.hxx"

#include <assert.h>
#include <malloc.h>
#include <string>

namespace universelan::client {
	using namespace galaxy::api;

	InitOptionsModern::InitOptionsModern(const InitOptionsImpl& initOptions) :
		clientID{ "" }
		, clientSecret{ "" }
		, configFilePath{ "" }
		, galaxyPeerPath{ "" }
		, throwExceptions{ false }
		, storagePath{ "" }
		, galaxyAllocator{ nullptr }
		, galaxyThreadFactory{ nullptr }
		, host{ "" }
		, port{ 0 }
		, local_init { false }
	{
		SetClientID(initOptions.clientID);
		SetClientSecret(initOptions.clientSecret);
		SetConfigFilePath(initOptions.configFilePath != nullptr ? initOptions.configFilePath : ".");

#if GALAXY_BUILD_FEATURE_HAS_INITOPTIONS_GALAXYPEERPATH
		SetGalaxyPeerPath(initOptions.galaxyPeerPath != nullptr ? initOptions.galaxyPeerPath : "");
#endif

#if !GALAXY_BUILD_FEATURE_HAS_INITOPTIONS
		throwExceptions = initOptions.throwExceptions;
#endif

#if GALAXY_BUILD_FEATURE_HAS_INITOPTIONS_STORAGEPATH
		SetStoragePath(initOptions.storagePath != nullptr ? initOptions.storagePath : "");
#endif

#if GALAXY_BUILD_FEATURE_ALLOCATOR
		galaxyAllocator = initOptions.galaxyAllocator;
#endif
#if GALAXY_BUILD_FEATURE_HAS_IGALAXYTHREADFACTORY
		galaxyThreadFactory = initOptions.galaxyThreadFactory;
#endif

#if GALAXY_BUILD_FEATURE_HAS_INITOPTIONS_HOST_PORT
		SetHost(initOptions.host != nullptr ? initOptions.host : "");
		port = initOptions.port;
#endif
	}

	InitOptionsModern::InitOptionsModern() :
		clientID{ "" }
		, clientSecret{ "" }
		, configFilePath{ "" }
		, galaxyPeerPath{ "" }
		, throwExceptions{ true }
		, storagePath{ "" }
		, galaxyAllocator{ nullptr }
		, galaxyThreadFactory{ nullptr }
		, host{ "" }
		, port{ 0 }
		, local_init { false }
	{}

	void InitOptionsModern::SetClientID(const char* client_id) {
		if (client_id != nullptr) {
			clientID.emplace(client_id);
		}
		else {
			clientID.reset();
		}
	}

	void InitOptionsModern::SetClientSecret(const char* client_secret) {
		if (client_secret != nullptr) {
			clientSecret.emplace(client_secret);
		}
		else {
			clientSecret.reset();
		}
	}

	void InitOptionsModern::SetConfigFilePath(const char* config_file_path) {
		if (config_file_path != nullptr) {
			configFilePath.emplace(config_file_path);
		}
		else {
			configFilePath.reset();
		}
	}

	void InitOptionsModern::SetStoragePath(const char* storage_path) {
		if (storage_path != nullptr) {
			storagePath.emplace(storage_path);
		}
		else {
			storagePath.reset();
		}
	}

	void InitOptionsModern::SetGalaxyPeerPath(const char* galaxy_peer_path) {
		if (galaxy_peer_path == nullptr || *galaxy_peer_path == '\0') {
			galaxyPeerPath.emplace(".");
		}
		else {
			galaxyPeerPath.emplace(galaxy_peer_path);
		}
	}

	void InitOptionsModern::SetHost(const char* host_addr) {
		if (host_addr != nullptr) {
			host.emplace(host_addr);
		}
		else {
			host.reset();
		}
	}

	const char* InitOptionsModern::GetClientID() {
		return clientID.has_value() ? clientID->c_str() : nullptr;
	}

	const char* InitOptionsModern::GetClientSecret() {
		return clientSecret.has_value() ? clientSecret->c_str() : nullptr;
	}

	const char* InitOptionsModern::GetConfigFilePath() {
		return configFilePath.has_value() ? configFilePath->c_str() : nullptr;
	}

	const char* InitOptionsModern::GetStoragePath() {
		return storagePath.has_value() ? storagePath->c_str() : nullptr;
	}

	const char* InitOptionsModern::GetGalaxyPeerPath() {
		return galaxyPeerPath.has_value() ? galaxyPeerPath->c_str() : nullptr;
	}

	const char* InitOptionsModern::GetHost() {
		return host.has_value() ? host->c_str() : nullptr;
	}
}
