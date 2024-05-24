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

		/** @} */
	}
}

#endif
