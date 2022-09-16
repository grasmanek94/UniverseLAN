#ifndef LSFDRMFG_IMPL_APPS_H
#define LSFDRMFG_IMPL_APPS_H

/**
 * @file
 * Contains data structures and interfaces related to application activities.
 */
#include <IApps.h>

#include "InterfaceInstances.hxx"

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
		class AppsImpl : public IApps
		{
		private:
			InterfaceInstances* intf;

		public:
			AppsImpl(InterfaceInstances* intf);

			virtual ~AppsImpl() override;

			/**
			 * Checks if specified DLC is installed.
			 *
			 * @param [in] productID The ID of the DLC to check.
			 * @return true if specified DLC is installed, false otherwise.
			 */
			virtual bool IsDlcInstalled(ProductID productID) override;

			/**
			 * Returns current game language for given product ID.
			 *
			 * @param [in] productID The ID of the game or DLC to check.
			 * @return current game language for given product ID.
			 */
			virtual const char* GetCurrentGameLanguage(ProductID productID = 0) override;

			/**
			 * Copies the current game language for given product ID to a buffer.
			 *
			 * @param [in, out] buffer The output buffer.
			 * @param [in] bufferLength The size of the output buffer.
			 * @param [in] productID The ID of the game or DLC to check.
			 * @return current game language for given product ID.
			 */
			virtual void GetCurrentGameLanguageCopy(char* buffer, uint32_t bufferLength, ProductID productID = 0) override;
		};

		/** @} */
	}
}

#endif
