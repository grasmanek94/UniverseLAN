#ifndef GALAXY_GALAXY_FACTORY_H
#define GALAXY_GALAXY_FACTORY_H

/**
 * @file
 * Contains GalaxyFactory, which creates an instance of IGalaxy that allows to
 * control the Galaxy Peer.
 */

#include <IGalaxy.h>
#include <Errors.h>
#include <GalaxyExport.h>

#include <cstdint>

namespace galaxy
{
	namespace api
	{
		class GALAXY_DLL_EXPORT IErrorManager
		{
		public:

			// maybe something like 'cause exception when error occurred'
			virtual int Unknown1() = 0;
			virtual IErrorManager* Unknown2() = 0;
			virtual int Unknown3() = 0;
			virtual ~IErrorManager() {}
		};

		/**
		 * @addtogroup api
		 * @{
		 */

		/**
		 * The singleton factory that creates an instance of IGalaxy that allows to
		 * control the Galaxy Peer.
		 */
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
			static IGalaxy* GALAXY_CALLTYPE GetInstance(
				//uint32_t a, uint32_t b
			);

			/**
			 * Returns the instance of error manager. Creates it if it does not exists yet.
			 *
			 * @return instance of error manager.
			 */
			static IErrorManager* GALAXY_CALLTYPE GetErrorManager(void);

			/**
			 * Removes the created instance of IGalaxy.
			 *
			 * @remark Instead of using this method directly, you probably should use
			 * the Shutdown() method defined in GalaxyApi.h.
			 */
			static void GALAXY_CALLTYPE ResetInstance(void);

			/**
			 * Returns the instance of IGalaxy. Creates it if it does not exist yet.
			 *
			 * @remark Instead of using this method directly, you probably should use
			 * methods defined in GalaxyApi.h.
			 *
			 * @return The instance of IGalaxy.
			 */
			static IGalaxy* GALAXY_CALLTYPE CreateInstance(void);

		private:

			static IGalaxy* instance; ///< The instance of IGalaxy.
			static IErrorManager* errorManager; ///< The instance of Error Manager.
		};

		/** @} */
	}
}

#endif
