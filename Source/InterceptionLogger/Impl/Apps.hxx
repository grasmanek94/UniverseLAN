#pragma once

#if GALAXY_BUILD_FEATURE_HAS_IAPPS
/**
 * @file
 * Contains data structures and interfaces related to application activities.
 */

#include <GalaxyFunctional.hxx>

#include <GalaxyExport.h>
#include <IApps.h>
#include <IListenerRegistrar.h>

namespace universelan::client {
	using namespace galaxy::api;
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
	class AppsImpl : public IApps
	{
	public:
		using FuncT = functional::xt<std::function<GALAXY_DLL_EXPORT IApps* GALAXY_CALLTYPE(void)>>;
		using FuncPtr = typename FuncT::PTR;

	private:
		FuncT::F intf;
		IListenerRegistrar* notifications;
		bool force_dlc_check;

	public:
		AppsImpl(FuncT::F intf, IListenerRegistrar* notifications, bool force_dlc_check);

		virtual ~AppsImpl() override;

		/**
		 * Checks if specified DLC is installed.
		 *
		 * @param [in] productID The ID of the DLC to check.
		 * @return true if specified DLC is installed, false otherwise.
		 */
		virtual bool IsDlcInstalled(ProductID productID) override;

#if GALAXY_BUILD_FEATURE_HAS_GETCURRENTGAMELANGUAGE
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
#endif

#if GALAXY_BUILD_FEATURE_HAS_IAPPS_LANGUAGECODE
		/**
		 * Returns current game language code for given product ID.
		 *
		 * Language code consists of ISO-639 language code and ISO-3166 country code, ex. "en-US", "pl-PL".
		 *
		 * @param [in] productID The ID of the game or DLC to check.
		 * @return current game language code for given product ID. Zero means the base game itself.
		 */
		virtual const char* GetCurrentGameLanguageCode(ProductID productID = 0) override;

		/**
		 * Copies the current game language code for given product ID to a buffer.
		 *
		 * Language code consists of ISO-639 language code and ISO-3166 country code, ex. "en-US", "pl-PL".
		 *
		 * @param [in, out] buffer The output buffer.
		 * @param [in] bufferLength The size of the output buffer.
		 * @param [in] productID The ID of the game or DLC to check. Zero means the base game itself.
		 */
		virtual void GetCurrentGameLanguageCodeCopy(char* buffer, uint32_t bufferLength, ProductID productID = 0) override;
#endif

#if GALAXY_BUILD_FEATURE_HAS_IAPPS_ISDLCOWNED
		virtual void IsDlcOwned(ProductID productID, IIsDlcOwnedListener* const listener) override;
#endif
	};
	/** @} */
}

#endif
