#include <GalaxyFactory.h>

namespace galaxy::api {

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
			return nullptr;

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
			return nullptr;

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
			return nullptr;

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
			return nullptr;

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
			return nullptr;

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
			return nullptr;

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
			return nullptr;

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
			return nullptr;

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
			return nullptr;

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
			return nullptr;

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
			return nullptr;

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
			return nullptr;

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
}
