#ifndef LSFDRMFG_IMPL_LISTENER_H
#define LSFDRMFG_IMPL_LISTENER_H

/**
 * @file
 * Contains data structures and interfaces related to callback listeners.
 */

#include <stdint.h>
#include <stdlib.h>
#include <GalaxyExport.h>

#include <IListenerRegistrar.h>

namespace galaxy
{
	namespace api
	{
		/**
		 * The class that enables and disables global registration of the instances of
		 * specific listeners. You can either use it explicitly, or implicitly by
		 * inheriting from a self-registering basic listener of desired type.
		 */
		class ListenerRegistrar : public IListenerRegistrar
		{
		public:

			virtual ~ListenerRegistrar();

			/**
			 * Globally registers a callback listener that inherits from IGalaxyListener
			 * and is of any of the standard listener types specified in ListenerType.
			 *
			 * @remark Call Unregister() for all registered listeners before calling
			 * Shutdown().
			 *
			 * @param [in] listenerType The type of the listener. A value of ListenerType.
			 * @param [in] listener The specific listener of the specified type.
			 */
			virtual void Register(ListenerType listenerType, IGalaxyListener* listener) override;

			/**
			 * Unregisters a listener previously globally registered with Register()
			 * or registered for specific action.
			 *
			 * Call Unregister() unregisters listener from all pending asynchonous calls.
			 *
			 * @param [in] listenerType The type of the listener. A value of ListenerType.
			 * @param [in] listener The specific listener of the specified type.
			 */
			virtual void Unregister(ListenerType listenerType, IGalaxyListener* listener) override;
		};
	}
}

#endif
