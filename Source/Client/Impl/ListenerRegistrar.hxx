#ifndef UNIVERSELAN_IMPL_LISTENER_H
#define UNIVERSELAN_IMPL_LISTENER_H

#include "DelayRunner.hxx"

/**
 * @file
 * Contains data structures and interfaces related to callback listeners.
 */

#include "NotificationParamScopeExtender.hxx"

#include <Tracer.hxx>

#include <stdint.h>
#include <stdlib.h>
#include <GalaxyExport.h>

#include <IListenerRegistrar.h>
#include <GalaxyApi.h>

#include <magic_enum/magic_enum.hpp>

#include <any>
#include <array>
#include <concepts>
#include <format>
#include <functional>
#include <memory>
#include <mutex>
#include <optional>
#include <set>
#include <string>
#include <unordered_map>

namespace universelan::client {
	using namespace galaxy::api;
	struct InterfaceInstances;

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
		using mutex_t = std::recursive_mutex;
		using lock_t = std::scoped_lock<mutex_t>;
		using listener_set = std::set<IGalaxyListener*>;
		using request_helper_entry_t = std::pair<IGalaxyListener*, std::any>;
		using request_helper_map_t = std::unordered_map<uint64_t, request_helper_entry_t>;
		using unregister_helper_map_t = std::unordered_map<IGalaxyListener*, uint64_t>;

		struct data {

			mutex_t mtx;
			listener_set set;

			data() : mtx{}, set{}
			{}
		};

		struct InternalRequestHelper {
			mutex_t mtx;
			request_helper_map_t requests;
			unregister_helper_map_t listeners;

			inline InternalRequestHelper() : mtx{}, requests{}, listeners{} {}

			inline void run_locked(std::function<void()> func) {
				lock_t lock{ mtx };
				func();
			}

			template <typename U=void>
			bool emplace(uint64_t request_id, IGalaxyListener* listener, std::shared_ptr<U> extra = nullptr) {
				lock_t lock{ mtx };
				if (!requests.emplace(request_id, request_helper_entry_t{ listener, std::any(extra) }).second) {
					return false;
				}

				listeners.emplace(listener, request_id);
				return true;
			}

			template <typename T>
			bool pop(uint64_t request_id, T*& listener) {
				lock_t lock{ mtx };
				auto it = requests.find(request_id);
				if (it == requests.end()) {
					listener = nullptr;
					return false;
				}

				listener = (T*)it->second.first;

				listeners.erase(it->second.first);
				requests.erase(it);

				return true;
			}

			template <typename T, typename U>
			bool pop(uint64_t request_id, T*& listener, std::shared_ptr<U>& extra) {
				lock_t lock{ mtx };
				auto it = requests.find(request_id);
				if (it == requests.end()) {
					listener = nullptr;
					return false;
				}

				listener = (T*)it->second.first;
				extra = std::any_cast<std::shared_ptr<U>>(it->second.second);

				listeners.erase(it->second.first);
				requests.erase(it);

				return true;
			}

			inline bool unregister(IGalaxyListener* listener) {
				lock_t lock{ mtx };
				auto it = listeners.find(listener);
				if (it == listeners.end()) {
					return false;
				}

				requests.erase(it->second);
				listeners.erase(it);

				return true;
			}
		};

	private:
		InterfaceInstances* intf;
		DelayRunner* delay_runner;
		std::array<data, LISTENER_TYPE_END> listeners;
		std::array<InternalRequestHelper, LISTENER_TYPE_END> request_helpers;

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

			tracer::Trace trace{ "::nl", __FUNCTION__, tracer::Trace::NOTIFICATION_INVOCATIONS };

			if (trace.has_flags(tracer::Trace::HIGH_FREQUENCY_CALLS | tracer::Trace::ARGUMENTS)) {
				trace.write_all(std::format("FuncT: {}", typeid(FuncT).name()));
			}

			return ExecuteForListenerTypePerEntry((ListenerType)T::GetListenerType(), [&](IGalaxyListener* listener) {
				//T* casted_listener = dynamic_cast<T*>(listener);
				T* casted_listener = (T*)(listener);
				assert(casted_listener != nullptr);

				std::invoke(std::forward<FuncT>(Function), casted_listener, notification_param_push_identity(Arguments)...);
				});
		}

		template <typename T, class FuncT, class... ArgTypes>
		bool NotifyAllNow(T* one_time_specific_listener, FuncT&& Function, ArgTypes&&... Arguments) {
			using BaseT = extract_class_from_member_function_ptr<FuncT>::type;

			if (one_time_specific_listener == nullptr) {
				return NotifyAllNow(std::forward<FuncT>(Function), std::forward<ArgTypes>(Arguments)...);
			}

			tracer::Trace trace{ "::hl", __FUNCTION__, tracer::Trace::NOTIFICATION_INVOCATIONS };

			if (trace.has_flags(tracer::Trace::HIGH_FREQUENCY_CALLS | tracer::Trace::ARGUMENTS)) {
				trace.write_all(std::format("FuncT: {}", typeid(FuncT).name()));
			}

			return ExecuteForListenerTypePerEntry((ListenerType)BaseT::GetListenerType(), one_time_specific_listener, [&](IGalaxyListener* listener) {
				//BaseT* casted_listener = dynamic_cast<BaseT*>(listener);
				BaseT* casted_listener = (BaseT*)(listener);
				assert(casted_listener != nullptr);

				std::invoke(std::forward<FuncT>(Function), casted_listener, notification_param_push_identity(Arguments)...);
				});
		}

		template <typename T, class FuncT, class... ArgTypes>
		bool NotifyAllNowSpecificOnly(T* one_time_specific_listener, FuncT&& Function, ArgTypes&&... Arguments) {
			using BaseT = extract_class_from_member_function_ptr<FuncT>::type;

			if (one_time_specific_listener == nullptr) {
				return false;
			}

			tracer::Trace trace{ "::so", __FUNCTION__, tracer::Trace::NOTIFICATION_INVOCATIONS };

			BaseT* casted_listener = (BaseT*)(one_time_specific_listener);
			assert(casted_listener != nullptr);

			std::invoke(std::forward<FuncT>(Function), casted_listener, notification_param_push_identity(Arguments)...);

			return true;
		}


#ifndef NDEBUG
		template <class FuncT, class... ArgTypes>
		bool NotifyAllNowSimulate(FuncT&& Function, ArgTypes&&... Arguments) {
			using T = extract_class_from_member_function_ptr<FuncT>::type;

			tracer::Trace trace{ "::nl", __FUNCTION__, tracer::Trace::NOTIFICATION_INVOCATIONS };

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

			tracer::Trace trace{ "::hl", __FUNCTION__, tracer::Trace::NOTIFICATION_INVOCATIONS };

			return ExecuteForListenerTypePerEntry((ListenerType)BaseT::GetListenerType(), one_time_specific_listener, [&](IGalaxyListener* listener) {
				BaseT* casted_listener = (BaseT*)(listener);

				assert(casted_listener != nullptr);

				// no invoke
				});
		}
#endif

		template <typename... ArgTypes>
		void NotifyAll(ArgTypes... Arguments)
		{
			tracer::Trace trace{ nullptr, tracer::Trace::NOTIFICATION_INVOCATIONS };

#ifndef NDEBUG
			// this is handy for catching invalid parameters to a later invocation
			//this->NotifyAllNowSimulate(std::forward<decltype(Arguments)>(Arguments)...);
#endif

			delay_runner->Add(std::bind_front([this](auto&&... args) {
				this->NotifyAllNow(std::forward<decltype(args)>(args)...);
				}, notification_param_extend_life<decltype(Arguments)>(std::move(Arguments))...));
		}

		template <typename... ArgTypes>
		void NotifyAllSpecificOnly(ArgTypes... Arguments)
		{
			tracer::Trace trace{ nullptr, tracer::Trace::NOTIFICATION_INVOCATIONS };

			delay_runner->Add(std::bind_front([this](auto&&... args) {
				this->NotifyAllNowSpecificOnly(std::forward<decltype(args)>(args)...);
				}, notification_param_extend_life<decltype(Arguments)>(std::move(Arguments))...));
		}

		template <typename T, typename U=void>
		bool AddRequestListener(uint64_t request_id, T* listener, std::shared_ptr<U> extra = nullptr) {
			tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::LISTENERREGISTRAR | tracer::Trace::HIGH_FREQUENCY_CALLS };

			if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
				trace.write_all(std::format("request_id: {}", request_id));
				trace.write_all(std::format("listener: {}", (void*)listener));
			}

			if (listener == nullptr) {
				return false;
			}

			auto listener_type_id = T::GetListenerType();

			if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
				trace.write_all(std::format("listenerType: {}", magic_enum::enum_name((ListenerType)listener_type_id)));
			}

			return request_helpers[(size_t)listener_type_id].emplace(request_id, (IGalaxyListener*)listener, extra);
		}

		template <typename T>
		bool PopRequestListener(uint64_t request_id, T*& listener) {
			tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::LISTENERREGISTRAR | tracer::Trace::HIGH_FREQUENCY_CALLS };

			auto listener_type_id = T::GetListenerType();

			if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
				trace.write_all(std::format("request_id: {}", request_id));
				trace.write_all(std::format("listenerType: {}", magic_enum::enum_name((ListenerType)listener_type_id)));
			}

			return request_helpers[(size_t)listener_type_id].pop(request_id, listener);
		}

		template <typename T, typename U>
		bool PopRequestListener(uint64_t request_id, T*& listener, std::shared_ptr<U>& extra) {
			tracer::Trace trace{ "::extra", __FUNCTION__, tracer::Trace::LISTENERREGISTRAR | tracer::Trace::HIGH_FREQUENCY_CALLS};

			auto listener_type_id = T::GetListenerType();

			if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
				trace.write_all(std::format("request_id: {}", request_id));
				trace.write_all(std::format("listenerType: {}", magic_enum::enum_name((ListenerType)listener_type_id)));
			}

			return request_helpers[(size_t)listener_type_id].pop(request_id, listener, extra);
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
