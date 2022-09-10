#ifndef LSFDRMFG_GALAXY_API_H
#define LSFDRMFG_GALAXY_API_H

/**
 * @file
 * Includes all other files that are needed to work with the Galaxy library.
 */

#include "GalaxyApi.h"

#include "Impl/User.hxx"
#include "Impl/Friends.hxx"
#include "Impl/Chat.hxx"
#include "Impl/Matchmaking.hxx"
#include "Impl/Networking.hxx"
#include "Impl/Stats.hxx"
#include "Impl/Utils.hxx"
#include "Impl/Apps.hxx"
#include "Impl/Storage.hxx"
#include "Impl/CustomNetworking.hxx"
#include "Impl/Logger.hxx"
#include "Impl/Telemetry.hxx"
#include "Impl/Errors.hxx"
#include "GalaxyGameServerApi.hxx"

namespace galaxy
{
	namespace api
	{
		/**
		 * @addtogroup api
		 * @{
		 */

		/**
		 * @addtogroup Peer
		 * @{
		 */

		 /**
		  * Returns an instance of IListenerRegistrar.
		  *
		  * @return An instance of IListenerRegistrar.
		  */
		GALAXY_DLL_EXPORT IListenerRegistrar* GALAXY_CALLTYPE ListenerRegistrar();

		/** @} */

		/**
		 * @addtogroup GameServer
		 * @{
		 */

		 /**
		  * Returns an instance of IListenerRegistrar interface the for Game Server entity.
		  *
		  * @return An instance of IListenerRegistrar.
		  */
		GALAXY_DLL_EXPORT IListenerRegistrar* GALAXY_CALLTYPE GameServerListenerRegistrar();

		/**
		 * Retrieves error connected with the last API call on the local thread.
		 *
		 * @return Either the last API call error or NULL if there was no error.
		 */
		GALAXY_DLL_EXPORT const IError* GALAXY_CALLTYPE GetError();
	}
}

#endif