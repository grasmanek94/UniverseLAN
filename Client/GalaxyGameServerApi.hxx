#ifndef LSFDRMFG_GALAXY_GAME_SERVER_API_H
#define LSFDRMFG_GALAXY_GAME_SERVER_API_H

/**
 * @file
 * Contains the main interface for controlling the Galaxy Game Server.
 */

#include "InterfaceInstances.hxx"

#include <GalaxyGameServerApi.h>

namespace universelan::client {
	using namespace galaxy::api;
	extern InterfaceInstances gameserver_intf_inst;
}

#endif