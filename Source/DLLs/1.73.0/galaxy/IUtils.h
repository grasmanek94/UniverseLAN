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
		 * Listener for the event of changing overlay state.
		 */
		class IOverlayStateChangeListener : public GalaxyTypeAwareListener<OVERLAY_STATE_CHANGE>
		{
		public:

			/**
			 * Notification for the event of changing overlay state.
			 *
			 * @param overlayIsActive Indicates if overlay is in front of the game.
			 */
			virtual void OnOverlayStateChanged(bool overlayIsActive) = 0;
		};

		/**
		 * Globally self-registering version of IOverlayStateChangeListener.
		 */
		typedef SelfRegisteringListener<IOverlayStateChangeListener> GlobalOverlayStateChangeListener;

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
			 * @param imageID The ID of the image.
			 * @param width The width of the image.
			 * @param height The height of the image.
			 */
			virtual void GetImageSize(uint32_t imageID, int32_t& width, int32_t& height) = 0;

			/**
			 * Reads the image of a specified ID.
			 *
			 * @remark The size of the output buffer should be 4 * height * width * sizeof(char).
			 *
			 * @param imageID The ID of the image.
			 * @param buffer The output buffer.
			 * @param bufferLength The size of the output buffer.
			 */
			virtual void GetImageRGBA(uint32_t imageID, unsigned char* buffer, uint32_t bufferLength) = 0;
		};

		/** @} */
	}
}

#endif
