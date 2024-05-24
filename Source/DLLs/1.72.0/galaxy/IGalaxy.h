#ifndef GALAXY_I_GALAXY_H
#define GALAXY_I_GALAXY_H

/**
 * @file
 * Contains IGalaxy, which is the main interface for controlling the Galaxy
 * Peer.
 */

#include "GalaxyExport.h"

namespace galaxy
{
	namespace api
	{
		/**
		 * @addtogroup api
		 * @{
		 */

		class IUser;
		class IFriends;
		class IMatchmaking;
		class INetworking;
		class IStats;
		class IListenerRegistrar;
		class ILogger;
		class IError;

		/**
		 * The main interface for controlling the Galaxy Peer.
		 */
		class GALAXY_DLL_EXPORT IGalaxy
		{
		public:

			virtual ~IGalaxy()
			{
			}

			/**
			 * Initializes the Galaxy Peer with specified credentials.
			 *
			 * @remark When you do not need the Galaxy Peer anymore, you should call
			 * Shutdown() in order to deactivate it and free its resources.
			 *
			 * @param clientID The ID of the client.
			 * @param clientSecret The secret of the client.
			 * @param throwExceptions Indicates if Galaxy should throw exceptions.
			 */
			virtual void Init(const char* clientID, const char* clientSecret, bool throwExceptions = true) = 0;

			/**
			 * Initializes the Galaxy Peer with specified credentials.
			 *
			 * @remark When you do not need the Galaxy Peer anymore, you should call
			 * Shutdown() in order to deactivate it and free its resources.
			 *
			 * @warning This method allows for using local Galaxy Peer library
			 * instead of the one provided by the desktop service Galaxy Client.
			 * In the future the method will be removed and loading of the library
			 * will rely solely on the desktop service.
			 *
			 * @param clientID The ID of the client.
			 * @param clientSecret The secret of the client.
			 * @param galaxyPeerPath Path to the galaxyPeer library location.
			 * @param throwExceptions indicates if Galaxy should throw exceptions.
			 */
			virtual void InitLocal(const char* clientID, const char* clientSecret, const char* galaxyPeerPath = ".", bool throwExceptions = true) = 0;

			/**
			 * Shuts down the Galaxy Peer.
			 *
			 * The Galaxy Peer is deactivated and brought to the state it had when it
			 * was created and before it was initialized.
			 *
			 * @remark Delete all self-registering listeners before calling
			 * Shutdown().
			 */
			virtual void Shutdown() = 0;

			/**
			 * Returns an instance of IUser.
			 *
			 * @return An instance of IUser.
			 */
			virtual IUser* GetUser() const = 0;

			/**
			 * Returns an instance of IFriends.
			 *
			 * @return An instance of IFriends.
			 */
			virtual IFriends* GetFriends() const = 0;

			/**
			 * Returns an instance of IMatchmaking.
			 *
			 * @return An instance of IMatchmaking.
			 */
			virtual IMatchmaking* GetMatchmaking() const = 0;

			/**
			 * Returns an instance of INetworking that allows to communicate
			 * as a regular lobby member.
			 *
			 * @return An instance of INetworking.
			 */
			virtual INetworking* GetNetworking() const = 0;

			/**
			 * Returns an instance of INetworking that allows to communicate
			 * as the lobby host.
			 *
			 * @return An instance of INetworking.
			 */
			virtual INetworking* GetServerNetworking() const = 0;

			/**
			 * Returns an instance of IStats.
			 *
			 * @return An instance of IStats.
			 */
			virtual IStats* GetStats() const = 0;

			/**
			 * Returns an instance of IListenerRegistrar.
			 *
			 * @return An instance of IListenerRegistrar.
			 */
			virtual IListenerRegistrar* GetListenerRegistrar() const = 0;

			/**
			 * Returns an instance of ILogger.
			 *
			 * @return An instance of ILogger.
			 */
			virtual ILogger* GetLogger() const = 0;

			/**
			 * Makes the Galaxy Peer process its input and output streams.
			 *
			 * During the phase of processing data, Galaxy Peer recognizes specific
			 * events and casts notifications for callback listeners immediately.
			 */
			virtual void ProcessData() = 0;

			/**
			 * Retrieves error connected with last api call
			 *
			 * @return last api call error or NULL if there was no error
			 */
			virtual const IError* GetError() const = 0;
		};

		/** @} */
	}
}

#endif
