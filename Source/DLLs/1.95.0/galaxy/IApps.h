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
		*
		* @remark This interface is fully functional in any situation when
		* IGalaxy::Init() reports an error.
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

			/**
			 * Returns current game language for given product ID.
			 *
			 * @param productID The ID of the game or DLC to check.
			 * @return current game language for given product ID.
			 */
			virtual const char* GetCurrentGameLanguage(ProductID productID = 0) = 0;

			/**
			 * Copies the current game language for given product ID to a buffer.
			 *
			 * @param buffer The output buffer.
			 * @param bufferLength The size of the output buffer.
			 * @param productID The ID of the game or DLC to check.
			 * @return current game language for given product ID.
			 */
			virtual void GetCurrentGameLanguageCopy(char* buffer, uint32_t bufferLength, ProductID productID = 0) = 0;
		};

		/** @} */
	}
}

#endif
