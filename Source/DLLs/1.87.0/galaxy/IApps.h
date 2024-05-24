#ifndef GALAXY_I_APPS_H
#define GALAXY_I_APPS_H

/**
* @file
* Contains data structures and interfaces related to application activities.
*/

#include "IListenerRegistrar.h"

namespace galaxy
{
	namespace api
	{
		/**
		 * @addtogroup api
		 * @{
		 */

		 /**
		  * The ID of the DLC.
		  */
		typedef uint64_t ProductID;

		/**
		* The interface for managing application activities.
		*/
		class IApps
		{
		public:

			virtual ~IApps()
			{
			}

			/**
			 * Checks if specified DLC is installed.
			 *
			 * @param productID The ID of the DLC to check.
			 * @return true if specified DLC is installed, false otherwise.
			 */
			virtual bool IsDlcInstalled(ProductID productID) = 0;
		};

		/** @} */
	}
}

#endif
