#ifndef LSFDRMFG_GALAXY_GAME_SERVER_API_H
#define LSFDRMFG_GALAXY_GAME_SERVER_API_H

/**
 * @file
 * Contains the main interface for controlling the Galaxy Game Server.
 */

#include "GalaxyExport.h"
#include "InitOptions.h"
#include "IUser.h"
#include "IMatchmaking.h"
#include "INetworking.h"
#include "IUtils.h"
#include "ITelemetry.h"
#include "ILogger.h"
#include "Errors.h"

#include <cstddef>

namespace galaxy
{
	namespace api
	{
		/**
		 * @addtogroup api
		 * @{
		 */

		/**
		 *
		 * @section game-server-overview Overview
		 *
		 * Game Server API is structured in the same way as Galaxy Peer API,
		 * providing global functions called GameServerUser(), GameServerMatchmaking(),
		 * GameServerNetworking() e.t.c. defined in GalaxyGameServerApi.h header file.
		 *
		 * Objects, methods, or combinations of parameters that are not supposed to be used
		 * with Game Server, such as IUser::SetUserData(), IFriends::RequestFriendList(),
		 * IMatchmaking::SetLobbyMemberData() cause either IInvalidStateError or IInvalidArgumentError errors.
		 *
		 * Since Game Server is a separate object, and in fact operates in a separate thread,
		 * separate methods are provided to control it: InitGameServer(), ProcessGameServerData(),
		 * and ShutdownGameServer().
		 *
		 * @section game-server-listeners Listeners
		 *
		 * Corresponding global self-registering listeners are provided for all interfaces supported
		 * by the Game Server prefixed with 'GameServer': GameServerGlobalAuthListener(),
		 * GameServerGlobalLobbyEnteredListener() e.t.c.
		 *
		 * @section game-server-authentication Authentication
		 *
		 * Game Server is authenticated anonymously using the IUser::SignInAnonymous(). This method
		 * is not available for the Galaxy Peer.
		 *
		 * @section game-server-matchmaking Matchmaking and networking
		 *
		 * The Game Server is only allowed to create public non-host-migrating lobbies.
		 * Joining a specific lobby is not possible for the Game Server.
		 *
		 * While in a lobby, the Game Server operation on the server INetworking interface, so
		 * incomming packets should be handled by the IServerNetworkingListener.
		 */

		/**
		 * @addtogroup GameServer
		 * @{
		 */

		/**
		 * Initializes the Galaxy Game Server with specified credentials.
		 *
		 * @remark When you do not need the Game Server anymore, you should call
		 * ShutdownGameServer() in order to deactivate it and free its resources.
		 *
		 * @remark This method can succeed partially, in which case it leaves
		 * Game Server partially functional, hence even in case of an error, be
		 * sure to call ShutdownGameServer() when you do not need the Game Server anymore.
		 * See the documentation of specific interfaces on how they behave.
		 *
		 * @param [in] initOptions The group of the init options.
		 */
		GALAXY_DLL_EXPORT void GALAXY_CALLTYPE InitGameServer(const InitOptions& initOptions);

		/**
		 * Shuts down the Galaxy Game Server.
		 *
		 * The Game Server is deactivated and brought to the state it had when it
		 * was created and before it was initialized.
		 *
		 * @pre Delete all self-registering listeners before calling ShutdownGameServer().
		 */
		GALAXY_DLL_EXPORT void GALAXY_CALLTYPE ShutdownGameServer();

		/**
		 * Returns an instance of IUser interface for the Game Server entity.
		 *
		 * @return An instance of IUser.
		 */
		GALAXY_DLL_EXPORT IUser* GALAXY_CALLTYPE GameServerUser();

		/**
		 * Returns an instance of IMatchmaking interface for the Game Server entity.
		 *
		 * @return An instance of IMatchmaking.
		 */
		GALAXY_DLL_EXPORT IMatchmaking* GALAXY_CALLTYPE GameServerMatchmaking();

		/**
		 * Returns an instance of INetworking interface for the Game Server entity
		 * that allows to communicate as the lobby host.
		 *
		 * @return An instance of INetworking.
		 */
		GALAXY_DLL_EXPORT INetworking* GALAXY_CALLTYPE GameServerNetworking();

		/**
		 * Returns an instance of INetworking interface for the Server entity
		 * that allows to communicate as the lobby host.
		 *
		 * @return An instance of INetworking.
		 */
		GALAXY_DLL_EXPORT INetworking* GALAXY_CALLTYPE ServerNetworking();

		/**
		 * Returns an instance of IUtils interface for the Game Server entity.
		 *
		 * @return An instance of IUtils.
		 */
		GALAXY_DLL_EXPORT IUtils* GALAXY_CALLTYPE GameServerUtils();

		/**
		* Returns an instance of ITelemetry.
		*
		* @return An instance of ITelemetry.
		*/
		GALAXY_DLL_EXPORT ITelemetry* GALAXY_CALLTYPE GameServerTelemetry();

		/**
		 * Returns an instance of ILogger interface for the Game Server entity.
		 *
		 * @return An instance of ILogger.
		 */
		GALAXY_DLL_EXPORT ILogger* GALAXY_CALLTYPE GameServerLogger();

		/**
		 * Makes the Game Server process its input and output streams.
		 *
		 * During the phase of processing data, Game Server recognizes specific
		 * events and casts notifications for callback listeners immediately.
		 *
		 * This method should be called in a loop, preferably every frame,
		 * so that Galaxy is able to process input and output streams.
		 *
		 * @remark When this method is not called, any asynchronous calls to Galaxy API
		 * cannot be processed and any listeners will not be properly called.
		 */
		GALAXY_DLL_EXPORT void GALAXY_CALLTYPE ProcessGameServerData();

		/** @} */

		/** @} */
	}
}

#endif