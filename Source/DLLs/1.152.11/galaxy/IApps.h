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
		 * Listener for the result of IsDLCOwned method.
		 */
		class IIsDlcOwnedListener : public GalaxyTypeAwareListener<IS_DLC_OWNED>
		{
		public:

			/**
			 * Notification for the result fetched.
			 *
			 * @param[in] productId Product ID of DLC was queried.
			 * @param[in] isOwned Set if user has the licence for specific DLC.
			 */
			virtual void OnDlcCheckSuccess(ProductID productId, bool isOwned) = 0;

			/**
			 * Reason of fetching result failure.
			 */
			enum FailureReason
			{
				FAILURE_REASON_UNDEFINED, ///< Undefined error.
				FAILURE_REASON_GALAXY_SERVICE_NOT_SIGNED_IN, ///< Galaxy Service is not signed in properly.
				FAILURE_REASON_CONNECTION_FAILURE, ///< Unable to communicate with backend services.
				FAILURE_REASON_EXTERNAL_SERVICE_FAILURE ///< Unable to communicate with external service.
			};

			/**
			 * Notification for the fail on fetching result.
			 *
			 * @param[in] productId Product ID of DLC was queried.
			 * @param[in] failureReason The cause of the failure.
			 */
			virtual void OnDlcCheckFailure(ProductID productId, FailureReason failureReason) = 0;
		};

		/**
		 * The interface for managing application activities.
		 *
		 * @remark This interface is fully functional in any situation when
		 * Init() reports an error except IsDlcOwned() method which requires to be
		 * logged via GalaxyClient (signed in and logged in).
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
			 * @param [in] productID The ID of the DLC to check.
			 * @return true if specified DLC is installed, false otherwise.
			 */
			virtual bool IsDlcInstalled(ProductID productID) = 0;

			/**
			 * Check if user has license for specified DLC.
			 *
			 * Note: this method requires user to be signed in and logged in
			 * with Galaxy Client.
			 *
			 * @param[in] productID Product ID of DLC to check.
			 * @param[in] listener Listener for asynchronous response.
			 */
			virtual void IsDlcOwned(ProductID productID, IIsDlcOwnedListener* const listener) = 0;

			/**
			 * Returns current game language for given product ID.
			 *
			 * Language name is returned in lowercase, ex. "english", "polish".
			 *
			 * @param [in] productID The ID of the game or DLC to check. Zero means the base game itself.
			 * @return current game language for given product ID.
			 */
			virtual const char* GetCurrentGameLanguage(ProductID productID = 0) = 0;

			/**
			 * Copies the current game language for given product ID to a buffer.
			 *
			 * Language name is returned in lowercase, ex. "english", "polish".
			 * 
			 * @param [in, out] buffer The output buffer.
			 * @param [in] bufferLength The size of the output buffer.
			 * @param [in] productID The ID of the game or DLC to check. Zero means the base game itself.
			 */
			virtual void GetCurrentGameLanguageCopy(char* buffer, uint32_t bufferLength, ProductID productID = 0) = 0;

			/**
			 * Returns current game language code for given product ID.
			 *
			 * Language code consists of ISO-639 language code and ISO-3166 country code, ex. "en-US", "pl-PL".
			 * 
			 * @param [in] productID The ID of the game or DLC to check.
			 * @return current game language code for given product ID. Zero means the base game itself.
			 */
			virtual const char* GetCurrentGameLanguageCode(ProductID productID = 0) = 0;

			/**
			 * Copies the current game language code for given product ID to a buffer.
			 *
			 * Language code consists of ISO-639 language code and ISO-3166 country code, ex. "en-US", "pl-PL".
			 *
			 * @param [in, out] buffer The output buffer.
			 * @param [in] bufferLength The size of the output buffer.
			 * @param [in] productID The ID of the game or DLC to check. Zero means the base game itself.
			 */
			virtual void GetCurrentGameLanguageCodeCopy(char* buffer, uint32_t bufferLength, ProductID productID = 0) = 0;
		};

		/** @} */
	}
}

#endif
