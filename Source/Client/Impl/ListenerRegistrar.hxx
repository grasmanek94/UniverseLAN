#ifndef LSFDRMFG_IMPL_LISTENER_H
#define LSFDRMFG_IMPL_LISTENER_H

#include "DelayRunner.hxx"

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

	using ListenerTypeImpl =
#if (GALAXY_VERSION) > 112400
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
		DelayRunner* delay_runner;
		std::array<data, LISTENER_TYPE_END> listeners;

	public:

		ListenerRegistrarImpl(InterfaceInstances* intf, DelayRunner* delay_runner);
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

		bool ExecuteForListenerType(ListenerType listenerType, std::function<void(const std::set<IGalaxyListener*>& listeners)> code);
		bool ExecuteForListenerTypePerEntry(ListenerType listenerType, std::function<void(IGalaxyListener* listeners)> code);
		bool ExecuteForListenerType(ListenerType listenerType, IGalaxyListener* extra, std::function<void(const std::set<IGalaxyListener*>& listeners)> code);
		bool ExecuteForListenerTypePerEntry(ListenerType listenerType, IGalaxyListener* extra, std::function<void(IGalaxyListener* listeners)> code);

		//primary template 
		template<typename> struct extract_class_from_member_function_ptr;

		template <typename RET_T, typename CLASS, class... ArgTypes>
		struct extract_class_from_member_function_ptr<RET_T(CLASS::*)(ArgTypes...)> {
			using type = CLASS;
		};

		template <typename RET_T, typename CLASS, class... ArgTypes>
		struct extract_class_from_member_function_ptr<RET_T(CLASS::* const)(ArgTypes...)> {
			using type = CLASS;
		};

		template <typename RET_T, typename CLASS, class... ArgTypes>
		struct extract_class_from_member_function_ptr<RET_T(CLASS::*&)(ArgTypes...)> {
			using type = CLASS;
		};

		template <typename RET_T, typename CLASS, class... ArgTypes>
		struct extract_class_from_member_function_ptr<RET_T(CLASS::* const&)(ArgTypes...)> {
			using type = CLASS;
		};

		template <class FuncT, class... ArgTypes>
		bool NotifyAllNow(FuncT&& Function, ArgTypes&&... Arguments) {
			using T = extract_class_from_member_function_ptr<FuncT>::type;
			return ExecuteForListenerTypePerEntry((ListenerType)T::GetListenerType(), [&](IGalaxyListener* listener) {
				//T* casted_listener = dynamic_cast<T*>(listener);
				T* casted_listener = (T*)(listener);
				assert(casted_listener != nullptr);

				std::invoke(std::forward<FuncT>(Function), casted_listener, std::forward<ArgTypes>(Arguments)...);
				});
		}

		template <typename T, class FuncT, class... ArgTypes>
		bool NotifyAllNow(T* one_time_specific_listener, FuncT&& Function, ArgTypes&&... Arguments) {
			using BaseT = extract_class_from_member_function_ptr<FuncT>::type;

			if (one_time_specific_listener == nullptr) {
				return NotifyAllNow(std::forward<FuncT>(Function), std::forward<ArgTypes>(Arguments)...);
			}

			return ExecuteForListenerTypePerEntry((ListenerType)BaseT::GetListenerType(), one_time_specific_listener, [&](IGalaxyListener* listener) {
				//BaseT* casted_listener = dynamic_cast<BaseT*>(listener
				BaseT* casted_listener = (BaseT*)(listener);
				assert(casted_listener != nullptr);

				std::invoke(std::forward<FuncT>(Function), casted_listener, std::forward<ArgTypes>(Arguments)...);
				});
		}

#ifndef NDEBUG
		template <class FuncT, class... ArgTypes>
		bool NotifyAllNowSimulate(FuncT&& Function, ArgTypes&&... Arguments) {
			using T = extract_class_from_member_function_ptr<FuncT>::type;
			return ExecuteForListenerTypePerEntry((ListenerType)T::GetListenerType(), [&](IGalaxyListener* listener) {
				T* casted_listener = (T*)(listener);

				assert(casted_listener != nullptr);

				// no invoke
				});
		}

		template <typename T, class FuncT, class... ArgTypes>
		bool NotifyAllNowSimulate(T* one_time_specific_listener, FuncT&& Function, ArgTypes&&... Arguments) {
			using BaseT = extract_class_from_member_function_ptr<FuncT>::type;

			if (one_time_specific_listener == nullptr) {
				return NotifyAllNowSimulate(std::forward<FuncT>(Function), std::forward<ArgTypes>(Arguments)...);
			}

			return ExecuteForListenerTypePerEntry((ListenerType)BaseT::GetListenerType(), one_time_specific_listener, [&](IGalaxyListener* listener) {
				BaseT* casted_listener = (BaseT*)(listener);

				assert(casted_listener != nullptr);

				// no invoke
				});
		}
#endif

		template <typename... ArgTypes>
		void NotifyAll(ArgTypes&&... Arguments)
		{
#ifndef NDEBUG
			this->NotifyAllNowSimulate(std::forward<decltype(Arguments)>(Arguments)...);
#endif

			delay_runner->Add(std::bind_front([this](auto&&... args) {
				this->NotifyAllNow(std::forward<decltype(args)>(args)...);
				}, std::forward<ArgTypes>(Arguments)...));
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

			T ret_val = it->second;
			map.erase(it);

			return ret_val;
		}
	};
}

#endif
