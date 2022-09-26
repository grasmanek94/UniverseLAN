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

#include <array>
#include <functional>
#include <mutex>
#include <set>
#include <unordered_map>

#include <GalaxyAPI.h>

namespace universelan::client {
	using namespace galaxy::api;
	struct InterfaceInstances;

	/**
	 * The class that enables and disables global registration of the instances of
	 * specific listeners. You can either use it explicitly, or implicitly by
	 * inheriting from a self-registering basic listener of desired type.
	 */
	class ListenerRegistrarImpl : public IListenerRegistrar
	{
	private:
		using mutex_t = std::recursive_mutex;
		using lock_t = std::scoped_lock<mutex_t>;
		using listener_set = std::set<IGalaxyListener*>;

		struct data {

			mutex_t mtx;
			listener_set set;

			data() : mtx{}, set{}
			{}
		};

		InterfaceInstances* intf;
		std::array<data, LISTENER_TYPE_END> listeners;

	public:

		ListenerRegistrarImpl(InterfaceInstances* intf);
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


		bool ExecuteForListenerType(ListenerType listenerType, std::function<void(const std::set<IGalaxyListener*>& listeners)> code);
		bool ExecuteForListenerTypePerEntry(ListenerType listenerType, std::function<void(IGalaxyListener* listeners)> code);
		bool ExecuteForListenerType(ListenerType listenerType, IGalaxyListener* extra, std::function<void(const std::set<IGalaxyListener*>& listeners)> code);
		bool ExecuteForListenerTypePerEntry(ListenerType listenerType, IGalaxyListener* extra, std::function<void(IGalaxyListener* listeners)> code);

		template <typename T, class _Fx, class... _Types>
		bool NotifyAll(_Fx&& _Func, _Types&&... _Args) {	
			return ExecuteForListenerTypePerEntry(T::GetListenerType(), [&](IGalaxyListener* listener) {
				T* casted_listener = dynamic_cast<T*>(listener);
				if (casted_listener) {
					std::invoke(std::forward<_Fx>(_Func), casted_listener, std::forward<_Types>(_Args)...);
				}
				});
		}

		template <typename T, class _Fx, class... _Types>
		bool NotifyAll(T* extra, _Fx&& _Func, _Types&&... _Args) {
			return ExecuteForListenerTypePerEntry(T::GetListenerType(), extra, [&](IGalaxyListener* listener) {
				T* casted_listener = dynamic_cast<T*>(listener);
				if (casted_listener) {
					std::invoke(std::forward<_Fx>(_Func), casted_listener, std::forward<_Types>(_Args)...);
				}
				});
		}
	};

	template<typename T>
	struct ListenersRequestHelper {
		using mutex_t = std::recursive_mutex;
		using lock_t = std::scoped_lock<mutex_t>;

		mutex_t mtx;
		std::unordered_map<uint64_t, T> map;

		void run_locked(std::function<void()> func) {
			lock_t lock(mtx);
			func();
		}

		void emplace(uint64_t request_id, T listener) {
			lock_t lock(mtx);
			map.emplace(request_id, listener);
		}

		T pop(uint64_t request_id) {
			lock_t lock(mtx);
			auto it = map.find(request_id);
			if (it == map.end()) {
				return nullptr;
			}
			map.erase(it);
			return it->second;
		}
	};
}

#endif
