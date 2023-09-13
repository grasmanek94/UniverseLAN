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
#if !GALAXY_BUILD_FEATURE_FACTORY_INTERFACE
		,galaxyAllocator{ nullptr }
#endif
#if (GALAXY_VERSION) > 112400
		,galaxyThreadFactory{ nullptr }
		,host{ "" }
		,port{ 0 }
#endif

	{
		
		clientID = initOptions.clientID;
		clientSecret = initOptions.clientSecret;
		configFilePath = initOptions.configFilePath != nullptr ? initOptions.configFilePath : "";
#if !GALAXY_BUILD_FEATURE_FACTORY_INTERFACE
		galaxyAllocator = initOptions.galaxyAllocator;
#endif
#if (GALAXY_VERSION) > 112400
		storagePath = initOptions.storagePath != nullptr ? initOptions.storagePath : "";
		galaxyThreadFactory = initOptions.galaxyThreadFactory;
		host = initOptions.host != nullptr ? initOptions.host : "";
		port = initOptions.port;
#endif
	}
}
