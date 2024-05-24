#ifndef GALAXY_GALAXY_FACTORY_H
#define GALAXY_GALAXY_FACTORY_H

/**
 * @file
 * Contains GalaxyFactory, which creates an instance of IGalaxy that allows to
 * control the Galaxy Peer.
 */

#include "IGalaxy.h"
#include "Errors.h"
#include "GalaxyExport.h"

namespace galaxy
{
	namespace api
	{
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
			 * Returns the instance of IGalaxy.
			 *
			 * @remark Instead of using this method directly, you probably should use
			 * methods defined in GalaxyApi.h.
			 *
			 * @return The instance of IGalaxy or NULL if it has not been created yet.
			 */
			static IGalaxy* GetInstance();

			/**
			 * Returns the instance of error manager. Creates it if it does not exists yet.
			 *
			 * @return instance of error manager.
			 */
			static IErrorManager* GetErrorManager();

			/**
			 * Removes created galaxy instance
			 *
			 * @remark Instead of using this method directly, you probably should use
			 * the Shutdown() method defined in GalaxyApi.h.
			 */
			static void ResetInstance();

			/**
			 * Returns the instance of IGalaxy. Creates it if it does not exist yet.
			 *
			 * @remark Instead of using this method directly, you probably should use
			 * methods defined in GalaxyApi.h.
			 *
			 * @return The instance of IGalaxy.
			 */
			static IGalaxy* CreateInstance();

		private:

			static IGalaxy* instance; ///< The instance of IGalaxy.
			static IErrorManager* errorManager; ///< The instance of Error Manager.
		};

		/** @} */
	}
}

#endif
