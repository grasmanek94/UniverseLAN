#ifndef UNIVERSELAN_IMPL_LISTENER_H
#define UNIVERSELAN_IMPL_LISTENER_H

#include <GalaxyExport.h>

#include <IListenerRegistrar.h>

#include <GalaxyFunctional.hxx>

#include <stdint.h>

namespace universelan::client {
	using namespace galaxy::api;

	using ListenerTypeImpl =
#if GALAXY_BUILD_FEATURE_HAS_LISTENERTYPE
		ListenerType;
#else
		uint32_t;
#endif
	/**
	 * The class that enables and disables global registration of the instances of
	 * specific listeners. You can either use it explicitly, or implicitly by
	 * inheriting from a self-registering basic listener of desired type.
	 */
	class ListenerRegistrarImpl : public IListenerRegistrar
	{
	public:
		using FuncT = functional::xt<std::function<GALAXY_DLL_EXPORT IListenerRegistrar* GALAXY_CALLTYPE(void)>>;
		using FuncPtr = FuncT::PTR;

	private:
		FuncT::F intf;

	public:

		ListenerRegistrarImpl(FuncT::F intf);
		virtual ~ListenerRegistrarImpl();

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
		virtual void Register(ListenerTypeImpl listenerType, IGalaxyListener* listener) override;

		/**
		 * Unregisters a listener previously globally registered with Register()
		 * or registered for specific action.
		 *
		 * Call Unregister() unregisters listener from all pending asynchonous calls.
		 *
		 * @param [in] listenerType The type of the listener. A value of ListenerType.
		 * @param [in] listener The specific listener of the specified type.
		 */
		virtual void Unregister(ListenerTypeImpl listenerType, IGalaxyListener* listener) override;

	};
}

#endif
