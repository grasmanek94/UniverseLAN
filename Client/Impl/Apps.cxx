/**
 * @file
 * Contains data structures and interfaces related to application activities.
 */
#include <algorithm>

#include "IApps.h"
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
		 * Init() reports an error.
		 */
		class Apps : public IApps
		{
		public:

			virtual ~Apps() override
			{
			}

			/**
			 * Checks if specified DLC is installed.
			 *
			 * @param [in] productID The ID of the DLC to check.
			 * @return true if specified DLC is installed, false otherwise.
			 */
			virtual bool IsDlcInstalled(ProductID productID) override {
				return true;
			}

			/**
			 * Returns current game language for given product ID.
			 *
			 * @param [in] productID The ID of the game or DLC to check.
			 * @return current game language for given product ID.
			 */
			virtual const char* GetCurrentGameLanguage(ProductID productID = 0) override {
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
			virtual void GetCurrentGameLanguageCopy(char* buffer, uint32_t bufferLength, ProductID productID = 0) override {
				std::copy_n("english", std::min((size_t)bufferLength, strlen("english")), buffer);
			}
		};

		/** @} */
	}
}
