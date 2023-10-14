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
		 * For your convenience, there are global functions called Matchmaking(),
		 * Networking(), ListenerRegistrar(), etc. What they do is call
		 * GalaxyFactory::GetInstance(), acquire appropriate interface from it, and
		 * return it.
		 *
		 * For every frame you should call IGalaxy::ProcessData() to process input
		 * and output streams.
		 *
		 * @section errors Error handling
		 *
		 * The Galaxy API has two ways of handling errors.
		 *
		 * The first one is by throwing errors as exceptions. This is the default.
		 *
		 * The second one is to check if there were any errors during last operation
		 * by calling IGalaxy::GetError(), which returns NULL if there was no error.
		 * Every call to an API method resets last stored error, therefore you should
		 * check for errors after each call.
		 *
		 * You can set the way of handling errors with the IGalaxy::Init() method.
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
		 * As with any other asynchronous call, you will get the information about
		 * the result of your request via a dedicated listener. For that to happen,
		 * you already need to call IGalaxy::ProcessData() in a loop as mentioned earlier.
		 *
		 * In case of limited availability of Galaxy backend services it might happen
		 * that the user gets signed in within local Galaxy Service, yet still does not
		 * manage to log on to Galaxy backend services. In that case the Galaxy Peer
		 * offers only some of its functionality.
		 *
		 * Having successfully signed in the user, you may want to check that the user
		 * is logged on to Galaxy backend services by calling IUser::IsLoggedOn().
		 *
		 * Information about being signed in or signed out, as well as information
		 * about being logged on or logged off, determine the operational state
		 * of Galaxy Peer and both come to the IOperationalStateChangeListener.
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
		 * @section networking P2P networking
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
		 * @section statistics Statistics, achievements and leaderboards
		 *
		 * The Galaxy API allows you to store information about statistic counters
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
		 *
		 * @section friends Friends
		 *
		 * The Galaxy API allows you to download the list of your friends by calling
		 * IFriends::RequestFriendList().
		 *
		 * Having retrieved the friend list you can browse it by calling IFriends::GetFriendCount()
		 * and IFriends::GetFriendByIndex().
		 *
		 * The Galaxy API allows you to browse information about other users.
		 *
		 * You can retrieve information about a specific user by calling IFriends::RequestUserInformation().
		 *
		 * Having retrieved other user information you can read it by calling
		 * IFriends::GetFriendPersonaName() and IFriends::GetFriendAvatarUrl().
		 *
		 * Some operations, e.g. entering a lobby or requesting for the friend list, automatically retrieve
		 * information about lobby members or friends accordingly.
		 *
		 * @subsection invites Inviting friends
		 *
		 * The Galaxy API allows you to invite your friends to play together by calling IFriends::ShowOverlayInviteDialog().
		 * This require the connectionString which will allow other users to join your game.

		 * Typically the connectionString looks like "-connect-lobby-<id>".

		 * After the invitation receiver gets the notification, he can click the JOIN button, which
		 * will fire IGameJoinRequestedListener with connectionString, or will start the game with
		 * connectionString as a parameter.
		 *
		 * @subsection rich-presence RichPresence
		 *
		 * The Galaxy API allows you to set the RichPresence "status" and "connect" keys.
		 * "status" key will be visible to your friends inside the Galaxy Client chat and friend list.
		 * "connect" key will be visible to your friends as a JOIN button, which works exactly the same way
		 * as like the player would receive the game invitation.
		 *
		 * @section storage Storage
		 *
		 * The Galaxy API allows you to store files in Galaxy's backend services. The files are automatically synchronized
		 * by the Galaxy Client application. You can access the stored files using the IStorage interface.
		 *
		 * @section dlc-discovery DLC discovery
		 *
		 * There is an easy way of checking if a DLC has been installed by calling
		 * IApps::IsDlcInstalled() with the Product ID of the particular DLC.
		 * This feature does not require the user to be online, or Galaxy Client
		 * to be installed, or even Galaxy API to be fully initialized, however
		 * you still need to call IGalaxy::Init() first.
		 *
		 * @section language Game language
		 *
		 * There is an easy way of retrieving game or DLC language by calling
		 * IApps::GetCurrentGameLanguage() with the Product ID of the game
		 * (0 can be used to retrieve base game language) or particular DLC.
		 * This feature does not require the user to be online, or Galaxy Client
		 * to be installed, or even Galaxy API to be fully initialized, however
		 * you still need to call IGalaxy::Init() first.
		 *
		 * @section thread-safety Thread-safety
		 *
		 * The Galaxy API is thread-safe in general, however there are some methods that return pointers and therefore
		 * cannot be used in multi-threaded environments. In order to address the issue the similar methods of names with
		 * a suffix of "Copy" were introduced, e.g. compare IFriends::GetPersonaName() and IFriends::GetPersonaNameCopy().
		 *
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
#include "IUtils.h"
#include "IApps.h"
#include "IStorage.h"
#include "ICustomNetworking.h"
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
		 *
		 * @param clientID The ID of the client.
		 * @param clientSecret The secret of the client.
		 * @param throwExceptions Indicates if Galaxy should throw exceptions.
		 */
		static void GALAXY_CALLTYPE Init(const char* clientID, const char* clientSecret, bool throwExceptions = true)
		{
			GalaxyFactory::CreateInstance()->Init(clientID, clientSecret, throwExceptions);
		}

		/**
		 * Calls IGalaxy::Init() on the singleton instance of IGalaxy.
		 *
		 * @param initOptions The group of the init options.
		 */
		static void GALAXY_CALLTYPE Init(const InitOptions& initOptions)
		{
			GalaxyFactory::CreateInstance()->Init(initOptions);
		}

		/**
		 * Calls IGalaxy::InitLocal() on the singleton instance of IGalaxy.
		 *
		 * @param clientID The ID of the client.
		 * @param clientSecret The secret of the client.
		 * @param galaxyPeerPath Path to the galaxyPeer library location.
		 * @param throwExceptions indicates if Galaxy should throw exceptions.
		 */
		static void GALAXY_CALLTYPE InitLocal(const char* clientID, const char* clientSecret, const char* galaxyPeerPath = ".", bool throwExceptions = true)
		{
			GalaxyFactory::CreateInstance()->InitLocal(clientID, clientSecret, galaxyPeerPath, throwExceptions);
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
		 *
		 * This method should be called in a loop, preferably every frame,
		 * so that Galaxy is able to process input and output streams.
		 *
		 * @remark When this method is not called, any asynchronous calls to Galaxy API
		 * cannot be processed and any listeners will not be properly called.
		 */
		static void GALAXY_CALLTYPE ProcessData()
		{
			if (!GalaxyFactory::GetInstance())
				return;

			GalaxyFactory::GetInstance()->ProcessData();
		}

		/**
		 * Calls IGalaxy::GetUser() on the singleton instance of IGalaxy.
		 *
		 * @return An instance of IUser.
		 */
		static IUser* GALAXY_CALLTYPE User()
		{
			if (!GalaxyFactory::GetInstance())
				return NULL;

			return GalaxyFactory::GetInstance()->GetUser();
		}

		/**
		 * Calls IGalaxy::GetFriends() on the singleton instance of IGalaxy.
		 *
		 * @return An instance of IFriends.
		 */
		static IFriends* GALAXY_CALLTYPE Friends()
		{
			if (!GalaxyFactory::GetInstance())
				return NULL;

			return GalaxyFactory::GetInstance()->GetFriends();
		}

		/**
		 * Calls IGalaxy::GetMatchmaking() on the singleton instance of IGalaxy.
		 *
		 * @return An instance of IMatchmaking.
		 */
		static IMatchmaking* GALAXY_CALLTYPE Matchmaking()
		{
			if (!GalaxyFactory::GetInstance())
				return NULL;

			return GalaxyFactory::GetInstance()->GetMatchmaking();
		}

		/**
		 * Calls IGalaxy::GetNetworking() on the singleton instance of IGalaxy.
		 *
		 * @return An instance of INetworking.
		 */
		static INetworking* GALAXY_CALLTYPE Networking()
		{
			if (!GalaxyFactory::GetInstance())
				return NULL;

			return GalaxyFactory::GetInstance()->GetNetworking();
		}

		/**
		 * Calls IGalaxy::GetServerNetworking() on the singleton instance of IGalaxy.
		 *
		 * @return An instance of INetworking.
		 */
		static INetworking* GALAXY_CALLTYPE ServerNetworking()
		{
			if (!GalaxyFactory::GetInstance())
				return NULL;

			return GalaxyFactory::GetInstance()->GetServerNetworking();
		}

		/**
		 * Calls IGalaxy::GetStats() on the singleton instance of IGalaxy.
		 *
		 * @return An instance of IStats.
		 */
		static IStats* GALAXY_CALLTYPE Stats()
		{
			if (!GalaxyFactory::GetInstance())
				return NULL;

			return GalaxyFactory::GetInstance()->GetStats();
		}

		/**
		 * Calls IGalaxy::GetUtils() on the singleton instance of IGalaxy.
		 *
		 * @return An instance of IUtils.
		 */
		static IUtils* GALAXY_CALLTYPE Utils()
		{
			if (!GalaxyFactory::GetInstance())
				return NULL;

			return GalaxyFactory::GetInstance()->GetUtils();
		}

		/**
		 * Calls IGalaxy::GetApps() on the singleton instance of IGalaxy.
		 *
		 * @return An instance of IApps.
		 */
		static IApps* GALAXY_CALLTYPE Apps()
		{
			if (!GalaxyFactory::GetInstance())
				return NULL;

			return GalaxyFactory::GetInstance()->GetApps();
		}

		/**
		 * Calls IGalaxy::GetStorage() on the singleton instance of IGalaxy.
		 *
		 * @return An instance of IStorage.
		 */
		static IStorage* GALAXY_CALLTYPE Storage()
		{
			if (!GalaxyFactory::GetInstance())
				return NULL;

			return GalaxyFactory::GetInstance()->GetStorage();
		}

		/**
		* Calls IGalaxy::GetCustomNetworking() on the singleton instance of IGalaxy.
		*
		* @return An instance of ICustomNetworking.
		*/
		static ICustomNetworking* GALAXY_CALLTYPE CustomNetworking()
		{
			if (!GalaxyFactory::GetInstance())
				return NULL;

			return GalaxyFactory::GetInstance()->GetCustomNetworking();
		}

		/**
		 * Calls IGalaxy::GetListenerRegistrar() on the singleton instance of IGalaxy.
		 *
		 * @return An instance of IListenerRegistrar.
		 */
		static IListenerRegistrar* GALAXY_CALLTYPE ListenerRegistrar()
		{
			if (!GalaxyFactory::GetInstance())
				return NULL;

			return GalaxyFactory::GetInstance()->GetListenerRegistrar();
		}

		/**
		 * Calls IGalaxy::GetLogger() on the singleton instance of IGalaxy.
		 *
		 * @return An instance of ILogger.
		 */
		static ILogger* GALAXY_CALLTYPE Logger()
		{
			if (!GalaxyFactory::GetInstance())
				return NULL;

			return GalaxyFactory::GetInstance()->GetLogger();
		}

		/**
		 * Calls IGalaxy::GetError() on singleton instance of IGalaxy.
		 *
		 * @return Either the last API call error or NULL if there was no error.
		 */
		static const IError* GALAXY_CALLTYPE GetError()
		{
			return GalaxyFactory::GetErrorManager()->GetLastError();
		}

		/** @} */
	}
}

#endif
