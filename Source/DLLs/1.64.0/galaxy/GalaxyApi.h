#ifndef GALAXY_API_H
#define GALAXY_API_H

/**
 * @file
 * Includes all other files that are needed to work with the Galaxy library.
 */

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
		 * @mainpage Introduction
		 *
		 * @tableofcontents
		 *
		 * @section getting-started Getting started
		 *
		 * Developing a game with Galaxy needs to start from linking your application
		 * to the following libraries:
		 *  * Galaxy.lib on Windows
		 *  * libGalaxy.dylib on MacOSX
		 *  * libGalaxy.so on Linux
		 *
		 * All libraries are loaded dynamically, so they have to be placed in the same
		 * folder as your executable.
		 *
		 * @section client-credentials Client credentials
		 *
		 * In order to use the Galaxy API, you should request special client credentials
		 * from GOG.com for each game you develop. You will be provided with a pair of
		 * Client ID and Client Secret that are to be used when calling IGalaxy::Init().
		 *
		 * Client credentials identify your game within Galaxy. Only Galaxy Peers that
		 * use the same Client ID can interact with each other.
		 *
		 * @section overview Overview
		 *
		 * The Galaxy API is divided into multiple header files. You can either include
		 * only the header files with the data structures and interfaces you need, or
		 * simply include the file called GalaxyApi.h that includes all the other files.
		 *
		 * You can control your Galaxy Peer with an instance of the IGalaxy, that you
		 * can acquire by calling GalaxyFactory::GetInstance(). The IGalaxy interface
		 * lets you control your Galaxy Peer by providing interfaces for specific
		 * feature sets, e.g. IUser, IMatchmaking, INetworking,
		 * IFriends, IListenerRegistrar, ILogger.
		 *
		 * For your convenience, there are global functions called GalaxyMatchmaking(),
		 * GalaxyNetworking(), FacadeListenerRegistrar(), etc. What they do is call
		 * GalaxyFactory::GetInstance(), acquire appropriate interface from it, and
		 * return it.
		 *
		 * For every frame you should call IGalaxy::ProcessData() or GalaxyProcessData()
		 * to process input and output streams.
		 *
		 * @section errors Error Handling
		 *
		 * The Galaxy API has two ways of handling errors.
		 * The first one is by throwing errors as exceptions. This is the default.
		 * The second one is to check if there were any errors during last operation by
		 * calling GetError(), which should return NULL if there was no error. Every call
		 * to an API method resets last stored error, therefore you should check for errors
		 * after each call.
		 * You can set the way of handling errors with the Init() method.
		 *
		 * @section listeners Listeners
		 *
		 * Since many method calls are asynchronous, there is a mechanism for receiving
		 * responses within a callback that is based on implementing special interfaces
		 * called listeners that derive from the IGalaxyListener interface.
		 *
		 * Listeners need to be registered in the IListenerRegistrar in order to
		 * receive a notification via a callback when an event of specific type has
		 * occurred. For convenience, there is a basic implementation for each listener
		 * that registers and unregisters automatically.
		 *
		 * Listeners are called during the phase of processing data, i.e. during the
		 * call to IGalaxy::ProcessData().
		 *
		 * @section authentication Authentication
		 *
		 * You need to initialize the Galaxy Peer by signing in the user. To do that,
		 * you need to get an instance of IUser from the IGalaxy and call
		 * IUser::SignIn().
		 *
		 * In case of limited availability of Galaxy backend services it might happen
		 * that the user gets signed in within local Galaxy Service, yet still does not
		 * manage to log on to Galaxy backend services. In that case the Galaxy Peer
		 * offers only some of its functionality.
		 *
		 * Having successfully signed in the user, you may want to check that the user
		 * is logged on to Galaxy backend services by calling IUser::IsLoggedOn().
		 *
		 * @section matchmaking Matchmaking
		 *
		 * To play a match with other users, the users needs to join them in a so called
		 * lobby. The user can either join an existing lobby or create one. All this is
		 * done with the IMatchmaking interface.
		 *
		 * Typically you will set appropriate filters by calling e.g.
		 * IMatchmaking::AddRequestLobbyListStringFilter() or
		 * IMatchmaking::AddRequestLobbyListNumericalFilter(), then retrieve the list
		 * of available lobbies by calling IMatchmaking::RequestLobbyList(), and
		 * than make the user join one of the lobbies by calling
		 * IMatchmaking::JoinLobby(). Alternatively the user might want to create
		 * a lobby, in which case you will need to call
		 * IMatchmaking::CreateLobby().
		 *
		 * @section lobbies Lobbies
		 *
		 * Users need to stay present in the lobby for the whole match, until it ends.
		 *
		 * When the user is the owner of a lobby, its Galaxy Peer needs to act as the
		 * game host.
		 *
		 * @subsection lobbies-messaging Messaging
		 *
		 * You can broadcast messages to all Galaxy Peers in the lobby by calling
		 * IMatchmaking::SendLobbyMessage(). Each recipient should be registered
		 * for notifications about incoming messages with dedicated listener, and on the
		 * occurrence of such notification call IMatchmaking::GetLobbyMessage().
		 *
		 * @section networking P2P Networking
		 *
		 * You can communicate with other Galaxy Peers that are in the same lobby using
		 * the INetworking interface. This way of communication is meant to be
		 * used for sending data that is directed to certain Galaxy Peers, especially
		 * for sending large amount of date in case of audio and video communication.
		 * Use it also for sending any other game data that is not crucial, yet needs to
		 * be delivered quickly.
		 *
		 * @subsection networking-sending Sending P2P packets
		 *
		 * To send a P2P packet call INetworking::SendP2PPacket().
		 *
		 * You can send packets to specific users by explicitly providing their IDs, or
		 * implicitly to the lobby owner (game host) by providing the ID of the lobby as
		 * the recipient.
		 *
		 * @subsection networking-receiving Receiving P2P packets
		 *
		 * To receive the packets that come to your Galaxy Peer as a regular lobby
		 * member, get the instance of INetworking by calling
		 * IGalaxy::GetNetworking().
		 *
		 * To receive the packets that come to your Galaxy Peer as a lobby owner, so
		 * that you can process them as the game host, get the instance o
		 * INetworking by calling IGalaxy::GetServerNetworking().
		 *
		 * @section statistics Statistics, Achievements and Leaderboards
		 * The Galaxy API allows you for storing information about statistic counters
		 * and unlocked achievements using the IStats interface.
		 *
		 * You can retrieve statistics and achievements of the user who is currently
		 * signed in, or other user that he interacts with, by calling
		 * IStats::RequestUserStatsAndAchievements().
		 *
		 * Having retrieved statistics and achievement of your user, you can both read
		 * and update them. After making edits to statistics and achievements you will
		 * need to store them by calling IStats::StoreStatsAndAchievements().
		 *
		 * You can retrieve leaderboards by calling IStats::RequestLeaderboards().
		 *
		 * Having retrieved leaderboard definitions you can change user's score by using
		 * IStats::SetLeaderboardScore() and retrieve leaderboard entries with scores and
		 * ranks of competing users by calling IStats::RequestLeaderboardEntriesGlobal(),
		 * IStats::RequestLeaderboardEntriesAroundUser(), or IStats::RequestLeaderboardEntriesForUsers().
		 */

		/** @} */
	}
}

#include "IGalaxy.h"
#include "IUser.h"
#include "IFriends.h"
#include "IMatchmaking.h"
#include "INetworking.h"
#include "IStats.h"
#include "IListenerRegistrar.h"
#include "ILogger.h"
#include "Errors.h"
#include "GalaxyFactory.h"

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
		 * Calls IGalaxy::Init() on the singleton instance of IGalaxy.
		 */
		static void GALAXY_CALLTYPE Init(const char* clientID, const char* clientSecret, bool throwExceptions = true)
		{
			try
			{
				GalaxyFactory::CreateInstance()->Init(clientID, clientSecret, throwExceptions);
				if (GalaxyFactory::GetErrorManager()->GetLastError())
					GalaxyFactory::ResetInstance();
				return;
			}
			catch (...)
			{
				GalaxyFactory::ResetInstance();
				throw;
			}
		}

		/**
		 * Calls IGalaxy::InitLocal() on the singleton instance of IGalaxy.
		 */
		static void GALAXY_CALLTYPE InitLocal(const char* clientID, const char* clientSecret, const char* galaxyPeerPath = ".", bool throwExceptions = true)
		{
			try
			{
				GalaxyFactory::CreateInstance()->InitLocal(clientID, clientSecret, galaxyPeerPath, throwExceptions);
				if (GalaxyFactory::GetErrorManager()->GetLastError())
					GalaxyFactory::ResetInstance();
				return;
			}
			catch (...)
			{
				GalaxyFactory::ResetInstance();
				throw;
			}
		}

		/**
		 * Calls IGalaxy::Shutdown() on the singleton instance of IGalaxy and then frees the instance.
		 */
		static void GALAXY_CALLTYPE Shutdown()
		{
			if (!GalaxyFactory::GetInstance())
				return;

			GalaxyFactory::GetInstance()->Shutdown();
			GalaxyFactory::ResetInstance();
		}

		/**
		 * Calls IGalaxy::ProcessData() on the singleton instance of IGalaxy.
		 */
		static void GALAXY_CALLTYPE ProcessData()
		{
			if (!GalaxyFactory::GetInstance())
				return;

			GalaxyFactory::GetInstance()->ProcessData();
		}

		/**
		 * Calls IGalaxy::GetUser() on the singleton instance of IGalaxy.
		 */
		static IUser* GALAXY_CALLTYPE User()
		{
			if (!GalaxyFactory::GetInstance())
				return NULL;

			return GalaxyFactory::GetInstance()->GetUser();
		}

		/**
		 * Calls IGalaxy::GetFriends() on the singleton instance of IGalaxy.
		 */
		static IFriends* GALAXY_CALLTYPE Friends()
		{
			if (!GalaxyFactory::GetInstance())
				return NULL;

			return GalaxyFactory::GetInstance()->GetFriends();
		}

		/**
		 * Calls IGalaxy::GetMatchmaking() on the singleton instance of IGalaxy.
		 */
		static IMatchmaking* GALAXY_CALLTYPE Matchmaking()
		{
			if (!GalaxyFactory::GetInstance())
				return NULL;

			return GalaxyFactory::GetInstance()->GetMatchmaking();
		}

		/**
		 * Calls IGalaxy::GetNetworking() on the singleton instance of IGalaxy.
		 */
		static INetworking* GALAXY_CALLTYPE Networking()
		{
			if (!GalaxyFactory::GetInstance())
				return NULL;

			return GalaxyFactory::GetInstance()->GetNetworking();
		}

		/**
		 * Calls IGalaxy::GetServerNetworking() on the singleton instance of IGalaxy.
		 */
		static INetworking* GALAXY_CALLTYPE ServerNetworking()
		{
			if (!GalaxyFactory::GetInstance())
				return NULL;

			return GalaxyFactory::GetInstance()->GetServerNetworking();
		}

		/**
		 * Calls IGalaxy::GetStats() on the singleton instance of IGalaxy.
		 */
		static IStats* GALAXY_CALLTYPE Stats()
		{
			if (!GalaxyFactory::GetInstance())
				return NULL;

			return GalaxyFactory::GetInstance()->GetStats();
		}

		/**
		 * Calls IGalaxy::GetListenerRegistrar() on the singleton instance of IGalaxy.
		 */
		static IListenerRegistrar* GALAXY_CALLTYPE ListenerRegistrar()
		{
			if (!GalaxyFactory::GetInstance())
				return NULL;

			return GalaxyFactory::GetInstance()->GetListenerRegistrar();
		}

		/**
		 * Calls IGalaxy::GetLogger() on the singleton instance of IGalaxy.
		 */
		static ILogger* GALAXY_CALLTYPE Logger()
		{
			if (!GalaxyFactory::GetInstance())
				return NULL;

			return GalaxyFactory::GetInstance()->GetLogger();
		}

		/**
		 * Calls IGalaxy::GetError() on singleton instance of IGalaxy.
		 */
		static const IError* GALAXY_CALLTYPE GetError()
		{
			return GalaxyFactory::GetErrorManager()->GetLastError();
		}

		/** @} */
	}
}

#endif
