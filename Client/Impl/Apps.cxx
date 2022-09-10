/**
 * @file
 * Contains data structures and interfaces related to application activities.
 */
#include <algorithm>

#include "IApps.h"
#include "IListenerRegistrar.h"

#include "Apps.hxx"

namespace galaxy
{
	namespace api
	{
		/**
		 * @addtogroup api
		 * @{
		 */

		 /**
		  * The interface for managing application activities.
		  *
		  * @remark This interface is fully functional in any situation when
		  * Init() reports an error.
		  */
		Apps::~Apps()
		{
		}

		/**
		 * Checks if specified DLC is installed.
		 *
		 * @param [in] productID The ID of the DLC to check.
		 * @return true if specified DLC is installed, false otherwise.
		 */
		bool Apps::IsDlcInstalled(ProductID productID) {
			return true;
		}

		/**
		 * Returns current game language for given product ID.
		 *
		 * @param [in] productID The ID of the game or DLC to check.
		 * @return current game language for given product ID.
		 */
		const char* Apps::GetCurrentGameLanguage(ProductID productID) {
			return "english";
		}

		/**
		 * Copies the current game language for given product ID to a buffer.
		 *
		 * @param [in, out] buffer The output buffer.
		 * @param [in] bufferLength The size of the output buffer.
		 * @param [in] productID The ID of the game or DLC to check.
		 * @return current game language for given product ID.
		 */
		void Apps::GetCurrentGameLanguageCopy(char* buffer, uint32_t bufferLength, ProductID productID) {
			std::copy_n("english", std::min((size_t)bufferLength, strlen("english")), buffer);
		}

		/** @} */
	}
}
