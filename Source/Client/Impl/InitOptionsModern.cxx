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
#if (GALAXY_VERSION) > 11240

		,host{ "" }
		,port{ 0 }
#endif

	{
		
		clientID = initOptions.clientID;
		clientSecret = initOptions.clientSecret;
		configFilePath = initOptions.configFilePath != nullptr ? initOptions.configFilePath : "";
#if GALAXY_BUILD_FEATURE_ALLOCATOR
		galaxyAllocator = initOptions.galaxyAllocator;
#endif
#if GALAXY_BUILD_FEATURE_HAS_IGALAXYTHREADFACTORY
		galaxyThreadFactory = initOptions.galaxyThreadFactory;
#endif
#if (GALAXY_VERSION) > 11240
		storagePath = initOptions.storagePath != nullptr ? initOptions.storagePath : "";
		host = initOptions.host != nullptr ? initOptions.host : "";
		port = initOptions.port;
#endif
	}
}
