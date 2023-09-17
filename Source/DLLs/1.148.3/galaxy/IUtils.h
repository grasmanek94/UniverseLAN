#ifndef GALAXY_I_UTILS_H
#define GALAXY_I_UTILS_H

/**
 * @file
 * Contains data structures and interfaces related to common activities.
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
		 * The ID of the notification.
		 */
		typedef uint64_t NotificationID;

		/**
		 * State of the overlay
		 */
		enum OverlayState
		{
			OVERLAY_STATE_UNDEFINED, ///< Overlay state is undefined.
			OVERLAY_STATE_NOT_SUPPORTED, ///< Overlay is not supported.
			OVERLAY_STATE_DISABLED, ///< Overlay is disabled by the user in the Galaxy Client.
			OVERLAY_STATE_FAILED_TO_INITIALIZE, ///< Galaxy Client failed to initialize the overlay or inject it into the game.
			OVERLAY_STATE_INITIALIZED ///< Overlay has been successfully injected into the game.
		};

		/**
		 * Listener for the event of changing overlay visibility.
		 */
		class IOverlayVisibilityChangeListener : public GalaxyTypeAwareListener<OVERLAY_VISIBILITY_CHANGE>
		{
		public:

			/**
			 * Notification for the event of changing overlay visibility.
			 *
			 * @param [in] overlayVisible Indicates if overlay is in front of the game.
			 */
			virtual void OnOverlayVisibilityChanged(bool overlayVisible) = 0;
		};

		/**
		 * Globally self-registering version of IOverlayStateChangeListener.
		 */
		typedef SelfRegisteringListener<IOverlayVisibilityChangeListener> GlobalOverlayVisibilityChangeListener;

		/**
		 * Listener for the event of changing overlay state.
		 */
		class IOverlayInitializationStateChangeListener : public GalaxyTypeAwareListener<OVERLAY_INITIALIZATION_STATE_CHANGE>
		{
		public:

			/**
			 * Notification for the event of changing overlay state change.
			 *
			 * @param [in] overlayState Indicates current state of the overlay.
			 */
			virtual void OnOverlayStateChanged(OverlayState overlayState) = 0;
		};

		/**
		 * Globally self-registering version of IOverlayInitializationStateChangeListener.
		 */
		typedef SelfRegisteringListener<IOverlayInitializationStateChangeListener> GlobalOverlayInitializationStateChangeListener;

		/**
		 * Listener for the event of receiving a notification.
		 */
		class INotificationListener : public GalaxyTypeAwareListener<NOTIFICATION_LISTENER>
		{
		public:

			/**
			 * Notification for the event of receiving a notification.
			 *
			 * To read the message you need to call IUtils::GetNotification().
			 *
			 * @param [in] notificationID The ID of the notification.
			 * @param [in] typeLength The size of the type of the notification.
			 * @param [in] contentSize The size of the content of the notification.
			 */
			virtual void OnNotificationReceived(NotificationID notificationID, uint32_t typeLength, uint32_t contentSize) = 0;
		};

		/**
		 * Globally self-registering version of INotificationListener.
		 */
		typedef SelfRegisteringListener<INotificationListener> GlobalNotificationListener;

		/**
		 * State of connection to the GOG services.
		 */
		enum GogServicesConnectionState
		{
			GOG_SERVICES_CONNECTION_STATE_UNDEFINED, ///< Connection state is undefined.
			GOG_SERVICES_CONNECTION_STATE_CONNECTED, ///< Connection to the GOG services has been established.
			GOG_SERVICES_CONNECTION_STATE_DISCONNECTED, ///< Connection to the GOG services has been lost.
			GOG_SERVICES_CONNECTION_STATE_AUTH_LOST ///< Connection to the GOG services has been lost due to lose of peer authentication.
		};

		/**
		 * Listener for the event of GOG services connection change.
		 */
		class IGogServicesConnectionStateListener : public GalaxyTypeAwareListener<GOG_SERVICES_CONNECTION_STATE_LISTENER>
		{
		public:

			/**
			 * Notification of the GOG services connection changed.
			 *
			 * @param [in] connectionState Current connection state.
			 */
			virtual void OnConnectionStateChange(GogServicesConnectionState connectionState) = 0;
		};

		/**
		 * Globally self-registering version of IGogServicesConnectionStateListener.
		 */
		typedef SelfRegisteringListener<IGogServicesConnectionStateListener> GlobalGogServicesConnectionStateListener;


		/**
		 * Globally self-registering version of IGogServicesConnectionStateListener for the Game Server.
		 */
		typedef SelfRegisteringListener<IGogServicesConnectionStateListener, GameServerListenerRegistrar> GameServerGlobalGogServicesConnectionStateListener;

		/**
		 * The interface for managing images.
		 */
		class IUtils
		{
		public:

			virtual ~IUtils()
			{
			}

			/**
			 * Reads width and height of the image of a specified ID.
			 *
			 * @param [in] imageID The ID of the image.
			 * @param [out] width The width of the image.
			 * @param [out] height The height of the image.
			 */
			virtual void GetImageSize(uint32_t imageID, int32_t& width, int32_t& height) = 0;

			/**
			 * Reads the image of a specified ID.
			 *
			 * @pre The size of the output buffer should be 4 * height * width * sizeof(char).
			 *
			 * @param [in] imageID The ID of the image.
			 * @param [in, out] buffer The output buffer.
			 * @param [in] bufferLength The size of the output buffer.
			 */
			virtual void GetImageRGBA(uint32_t imageID, void* buffer, uint32_t bufferLength) = 0;

			/**
			 * Register for notifications of a specified type.
			 *
			 * @remark Notification types starting "__" are reserved and cannot be used.
			 *
			 * @param [in] type The name of the type.
			 */
			virtual void RegisterForNotification(const char* type) = 0;

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
			virtual uint32_t GetNotification(NotificationID notificationID, bool& consumable, char* type, uint32_t typeLength, void* content, uint32_t contentSize) = 0;

			/**
			 * Shows web page in the overlay.
			 *
			 * @pre For this call to work, the overlay needs to be initialized first.
			 * To check whether the overlay is initialized, call GetOverlayState().
			 *
			 * @param [in] url The URL address of a specified web page with the limit of 2047 bytes.
			 */
			virtual void ShowOverlayWithWebPage(const char* url) = 0;

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
			virtual bool IsOverlayVisible() = 0;

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
			virtual OverlayState GetOverlayState() = 0;

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
			virtual void DisableOverlayPopups(const char* popupGroup) = 0;

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
			virtual GogServicesConnectionState GetGogServicesConnectionState() = 0;
		};

		/** @} */
	}
}

#endif
