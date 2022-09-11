#ifndef LSFDRMFG_GALAXY_API_H
#define LSFDRMFG_GALAXY_API_H

/**
 * @file
 * Includes all other files that are needed to work with the Galaxy library.
 */

#include "GalaxyApi.h"

#include "GalaxyGameServerApi.hxx"
#include "Impl/Apps.hxx"
#include "Impl/Chat.hxx"
#include "Impl/CustomNetworking.hxx"
#include "Impl/Errors.hxx"
#include "Impl/Friends.hxx"
#include "Impl/InitOptionsModern.hxx"
#include "Impl/ListenerRegistrar.hxx"
#include "Impl/Logger.hxx"
#include "Impl/Matchmaking.hxx"
#include "Impl/Networking.hxx"
#include "Impl/Stats.hxx"
#include "Impl/Storage.hxx"
#include "Impl/Telemetry.hxx"
#include "Impl/User.hxx"
#include "Impl/Utils.hxx"

#include <memory>

namespace galaxy
{
	namespace api
	{
		extern std::unique_ptr<InitOptionsModern> init_options;
	}
}

#endif