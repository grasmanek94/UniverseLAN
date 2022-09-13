#ifndef LSFDRMFG_GALAXY_GAME_SERVER_API_H
#define LSFDRMFG_GALAXY_GAME_SERVER_API_H

/**
 * @file
 * Contains the main interface for controlling the Galaxy Game Server.
 */

#include "Client.hxx"
#include "Impl/InitOptionsModern.hxx"

#include <IniData.hxx>

#include <GalaxyGameServerApi.h>

#include <memory>

namespace galaxy
{
	namespace api
	{
		namespace gameserver
		{
			extern std::unique_ptr <ClientIniData>		config;
			extern std::unique_ptr<InitOptionsModern>	init_options;
			extern std::unique_ptr<Client>				client;
		}
	}
}

#endif