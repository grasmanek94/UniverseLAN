#if GALAXY_BUILD_FEATURE_HAS_IGALAXY

#define CLIENT_FACTORY

#include <SharedLibUtils.hxx>

#include <Errors.h>
#include <GalaxyExport.h>

#include <exception>
#include <functional>
#include <stdexcept>

namespace galaxy::api
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
	class IUtils;
	class IApps;
	class IStorage;
	class ICustomNetworking;
	class IListenerRegistrar;
	class ILogger;
	class IError;
	struct InitOptions;

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
		 * @remark This method can succeed partially, in which case it leaves
		 * Galaxy Peer partially functional, hence even in case of an error, be
		 * sure to call Shutdown() when you do not need the Galaxy Peer anymore.
		 * See the documentation of specific interfaces on how they behave.
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
		 * @remark This method can succeed partially, in which case it leaves
		 * Galaxy Peer partially functional, hence even in case of an error, be
		 * sure to call Shutdown() when you do not need the Galaxy Peer anymore.
		 * See the documentation of specific interfaces on how they behave.
		 *
		 * @param initOptions The group of the init options.
		 */
		virtual void Init(const InitOptions& initOptions) = 0;

		/**
		 * Initializes the Galaxy Peer with specified credentials.
		 *
		 * @remark When you do not need the Galaxy Peer anymore, you should call
		 * Shutdown() in order to deactivate it and free its resources.
		 *
		 * @remark This method can succeed partially, in which case it leaves
		 * Galaxy Peer partially functional, hence even in case of an error, be
		 * sure to call Shutdown() when you do not need the Galaxy Peer anymore.
		 * See the documentation of specific interfaces on how they behave.
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
		 * Returns an instance of IUtils.
		 *
		 * @return An instance of IUtils.
		 */
		virtual IUtils* GetUtils() const = 0;

		/**
		 * Returns an instance of IApps.
		 *
		 * @return An instance of IApps.
		 */
		virtual IApps* GetApps() const = 0;

		/**
		 * Returns an instance of IStorage.
		 *
		 * @return An instance of IStorage.
		 */
		virtual IStorage* GetStorage() const = 0;

		/**
		* Returns an instance of ICustomNetworking.
		*
		* @return An instance of ICustomNetworking.
		*/
		virtual ICustomNetworking* GetCustomNetworking() const = 0;

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
		 * Retrieves error connected with the last API call.
		 *
		 * @return Either the last API call error or NULL if there was no error.
		 */
		virtual const IError* GetError() const = 0;


#ifndef _DEBUG
		IGalaxy();
#endif
		IGalaxy(IGalaxy const& other);
		IGalaxy& operator=(IGalaxy const& other);
	};

#ifndef _DEBUG
	IGalaxy::IGalaxy() {}
#endif

	IGalaxy::IGalaxy(IGalaxy const& other)
	{
		typedef IGalaxy*(__thiscall* copy_constructor_def)(galaxy::api::IGalaxy*, IGalaxy const&);

		static copy_constructor_def real_copy_constructor = 
#ifdef _WIN64
			(copy_constructor_def)universelan::SharedLibUtils::get_func_ptr("??0IGalaxy@api@galaxy@@QEAA@AEBV012@@Z");
#else
			(copy_constructor_def)universelan::SharedLibUtils::get_func_ptr("??0IGalaxy@api@galaxy@@QAE@ABV012@@Z");
#endif

		throw std::runtime_error("Uh oh IGalaxy copy constructor not implemented/untested");

		real_copy_constructor(this, other);
	}

	IGalaxy& IGalaxy::operator=(IGalaxy const& other) {
		throw std::runtime_error("Uh oh IGalaxy assignment not implemented/untested");

		return (IGalaxy&)*this;
	}

	class GALAXY_DLL_EXPORT GalaxyFactory
	{
	public:

		/**
		 * Returns the created instance of IGalaxy.
		 *
		 * @remark Instead of using this method directly, you probably should use
		 * methods defined in GalaxyApi.h.
		 *
		 * @return The instance of IGalaxy or NULL if it has not been created yet.
		 */
		static IGalaxy* GALAXY_CALLTYPE GetInstance();

		/**
		 * Returns the instance of error manager. Creates it if it does not exists yet.
		 *
		 * @return instance of error manager.
		 */
		static IErrorManager* GALAXY_CALLTYPE GetErrorManager();

		/**
		 * Removes the created instance of IGalaxy.
		 *
		 * @remark Instead of using this method directly, you probably should use
		 * the Shutdown() method defined in GalaxyApi.h.
		 */
		static void GALAXY_CALLTYPE ResetInstance();

		/**
		 * Returns the instance of IGalaxy. Creates it if it does not exist yet.
		 *
		 * @remark Instead of using this method directly, you probably should use
		 * methods defined in GalaxyApi.h.
		 *
		 * @return The instance of IGalaxy.
		 */
		static IGalaxy* GALAXY_CALLTYPE CreateInstance();

		GalaxyFactory& operator=(GalaxyFactory const& other);
		GalaxyFactory& operator=(GalaxyFactory && other);
	private:

		static IGalaxy* instance; ///< The instance of IGalaxy.
		static IErrorManager* errorManager; ///< The instance of Error Manager.
	};

	GalaxyFactory& GalaxyFactory::operator=(GalaxyFactory const& other) {
		throw std::runtime_error("Uh oh GalaxyFactory assignment not implemented/untested");
		this->instance = other.instance;
		this->errorManager = other.errorManager;

		return (GalaxyFactory&)*this;
	}

	GalaxyFactory& GalaxyFactory::operator=(GalaxyFactory && other) {
		throw std::runtime_error("Uh oh GalaxyFactory assignment not implemented/untested");
		this->instance = other.instance;
		this->errorManager = other.errorManager;

		return (GalaxyFactory&)*this;
	}
}

#endif
