#include "InitOptionsModern.hxx"

#include <assert.h>
#include <malloc.h>
#include <string>

namespace universelan::client {
	using namespace galaxy::api;

	InitOptionsModern::InitOptionsModern(const InitOptionsImpl& initOptions) :
		clientID{""}
		,clientSecret{ ""}
		,configFilePath{ "" }
		,storagePath{  "" }
#if GALAXY_BUILD_FEATURE_ALLOCATOR
		,galaxyAllocator{ nullptr }
#endif
#if GALAXY_BUILD_FEATURE_HAS_IGALAXYTHREADFACTORY
		, galaxyThreadFactory{ nullptr }
#endif
#if GALAXY_BUILD_FEATURE_HAS_INITOPTIONS_HOST_PORT
		,host{ "" }
		,port{ 0 }
#endif

	{
		// REVIEW: clientID/clientSecret are assigned to std::string without null
		// checks, unlike configFilePath. A null Galaxy option is undefined behavior;
		// normalize both required strings (and copy throwExceptions) explicitly.
		clientID = initOptions.clientID;
		clientSecret = initOptions.clientSecret;
		configFilePath = initOptions.configFilePath != nullptr ? initOptions.configFilePath : "";
#if GALAXY_BUILD_FEATURE_ALLOCATOR
		galaxyAllocator = initOptions.galaxyAllocator;
#endif
#if GALAXY_BUILD_FEATURE_HAS_IGALAXYTHREADFACTORY
		galaxyThreadFactory = initOptions.galaxyThreadFactory;
#endif
#if GALAXY_BUILD_FEATURE_HAS_INITOPTIONS_STORAGEPATH
		storagePath = initOptions.storagePath != nullptr ? initOptions.storagePath : "";
#endif

#if GALAXY_BUILD_FEATURE_HAS_INITOPTIONS_HOST_PORT
		host = initOptions.host != nullptr ? initOptions.host : "";
		port = initOptions.port;
#endif
	}

	InitOptionsModern::InitOptionsModern() :
		clientID{ "" }
		, clientSecret{ "" }
		, configFilePath{ "" }
		, storagePath{ "" }
		, throwExceptions{ false }
#if GALAXY_BUILD_FEATURE_ALLOCATOR
		, galaxyAllocator{ nullptr }
#endif
#if GALAXY_BUILD_FEATURE_HAS_IGALAXYTHREADFACTORY
		, galaxyThreadFactory{ nullptr }
#endif
#if GALAXY_BUILD_FEATURE_HAS_INITOPTIONS_HOST_PORT
		, host{ "" }
		, port{ 0 }
#endif

	{}
}
