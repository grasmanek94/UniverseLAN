#pragma once

#if GALAXY_BUILD_FEATURE_HAS_IUTILS

/**
 * @file
 * Contains data structures and interfaces related to common activities.
 */

#include "ListenerRegistrar.hxx"

#include <IUtils.h>
#include <IListenerRegistrar.h>

namespace universelan::client {

#if GALAXY_BUILD_FEATURE_GetImageRGBA_CHAR_TO_VOID
	using GetImageRGBABufferType = void;
#else
	using GetImageRGBABufferType = unsigned char;
#endif

	using namespace galaxy::api;
	struct InterfaceInstances;

	/**
	 * @addtogroup api
	 * @{
	 */

	 /**
	  * The interface for managing images.
	  */
	class UtilsImpl : public IUtils
	{
	private:
		InterfaceInstances* intf;
		ListenerRegistrarImpl* listeners;

	public:

		UtilsImpl(InterfaceInstances* intf);
		virtual ~UtilsImpl();

		/**
		 * Reads width and height of the image of a specified ID.
		 *
		 * @param [in] imageID The ID of the image.
		 * @param [out] width The width of the image.
		 * @param [out] height The height of the image.
		 */
		virtual void GetImageSize(uint32_t imageID, int32_t& width, int32_t& height) override;

		/**
		 * Reads the image of a specified ID.
		 *
		 * @pre The size of the output buffer should be 4 * height * width * sizeof(char).
		 *
		 * @param [in] imageID The ID of the image.
		 * @param [in, out] buffer The output buffer.
		 * @param [in] bufferLength The size of the output buffer.
		 */
		virtual void GetImageRGBA(uint32_t imageID, GetImageRGBABufferType* buffer, uint32_t bufferLength) override;

		/**
		 * Register for notifications of a specified type.
		 *
		 * @remark Notification types starting "__" are reserved and cannot be used.
		 *
		 * @param [in] type The name of the type.
		 */
		virtual void RegisterForNotification(const char* type) override;

		/**
		 * Reads a specified notification.
		 *
		 * @param [in] notificationID The ID of the notification.
		 * @param [out] consumable Indicates if the notification should be consumed.
		 * @param [in, out] type The output buffer for the type of the notification.
		 * @param [in] typeLength The size of the output buffer for the type of the notification.
		 * @param [in, out] content The output buffer for the content of the notification.
		 * @param [in] contentSize The size of the output buffer for the content of the notification.
		 * @return The number of bytes written to the content buffer.
		 */
		virtual uint32_t GetNotification(NotificationID notificationID
#if (GALAXY_VERSION) > 11240
			, bool& consumable
#endif
			, char* type, uint32_t typeLength, void* content, uint32_t contentSize) override;

		/**
		 * Shows web page in the overlay.
		 *
		 * @pre For this call to work, the overlay needs to be initialized first.
		 * To check whether the overlay is initialized, call GetOverlayState().
		 *
		 * @param [in] url The URL address of a specified web page with the limit of 2047 bytes.
		 */
		virtual void ShowOverlayWithWebPage(const char* url) override;

#if GALAXY_BUILD_FEATURE_OVERLAYSTATE_ENUM
		/**
		 * Return current visibility of the overlay
		 *
		 * @remark IOverlayVisibilityChangeListener might be used to track the overlay
		 * visibility change.
		 *
		 * @pre For this call to work, the overlay needs to be initialized first.
		 * To check whether the overlay is initialized successfully, call GetOverlayState().
		 *
		 * @return true if the overlay is in front of the game.
		 */
		virtual bool IsOverlayVisible() override;

		/**
		 * Return current state of the overlay
		 *
		 * @remark Basic game functionality should not rely on the overlay state, as the overlay
		 * may either be switched off by the user, not supported, or may fail to initialize.
		 *
		 * @remark IOverlayInitializationStateChangeListener might be used to track
		 * the overlay initialization state change.
		 *
		 * @pre In order for the overlay to be initialized successfully, first it must be enabled
		 * by the user in the Galaxy Client, and then successfully injected into the game.
		 *
		 * @return State of the overlay.
		 */
		virtual OverlayState GetOverlayState() override;
#endif

#if GALAXY_BUILD_FEATURE_HAS_DISABLEOVERLAYPOPUPS
		/**
		 * Disable overlay pop-up notifications.
		 *
		 * Hides overlay pop-up notifications based on the group specified below:
		 * - "chat_message" - New chat messages received.
		 * - "friend_invitation" - Friend request received, new user added to the friend list.
		 * - "game_invitation" - Game invitation sent or received.
		 *
		 * @pre For this call to work, the overlay needs to be initialized first.
		 * To check whether the overlay is initialized successfully, call IUtils::GetOverlayState().
		 *
		 * @param [in] popupGroup - The name of the notification pop-up group.
		 */
		virtual void DisableOverlayPopups(const char* popupGroup) override;
#endif
		/**
		 * Return current state of the connection to GOG services.
		 *
		 * @remark IGogServicesConnectionStateListener might be used to track
		 * the GOG services connection state.
		 *
		 * @remark Before successful login connection state is undefined.
		 *
		 * @return Current GOG services connection state.
		 */
#if (GALAXY_VERSION) > 11240
		virtual GogServicesConnectionState GetGogServicesConnectionState() override;
#endif

		virtual void ConnectionStateChangeReceived(bool connected);
	};

	/** @} */
}

#endif
