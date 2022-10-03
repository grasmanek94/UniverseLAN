#include "InitOptionsModern.hxx"

#include <assert.h>
#include <malloc.h>
#include <string>

namespace universelan::client {
	using namespace galaxy::api;

	InitOptionsModern::InitOptionsModern(const InitOptions& initOptions) :
		clientID{""}
		,clientSecret{ ""}
		,configFilePath{ "" }
		,storagePath{  "" }
		,galaxyAllocator{ nullptr }
#if (GALAXY_VERSION) > 112400
		,galaxyThreadFactory{ nullptr }
		,host{ "" }
		,port{ 0 }
#endif
	{
		
		clientID = initOptions.clientID;
		clientSecret = initOptions.clientSecret;
		configFilePath = initOptions.configFilePath != nullptr ? initOptions.configFilePath : "";
		storagePath = initOptions.storagePath != nullptr ? initOptions.storagePath : "";
		galaxyAllocator = initOptions.galaxyAllocator;
#if (GALAXY_VERSION) > 112400
		galaxyThreadFactory = initOptions.galaxyThreadFactory;
		host = initOptions.host != nullptr ? initOptions.host : "";
		port = initOptions.port;
#endif
	}
}
