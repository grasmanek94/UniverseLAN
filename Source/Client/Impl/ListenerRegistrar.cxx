#include "ListenerRegistrar.hxx"

#include "UniverseLAN.hxx"

#include <Tracer.hxx>

#include <format>
#include <iostream>
#include <mutex>
#include <stdexcept>

#include <magic_enum/magic_enum.hpp>

namespace universelan::client {
	using namespace galaxy::api;
	ListenerRegistrarImpl::ListenerRegistrarImpl(InterfaceInstances* intf, DelayRunner* delay_runner) :
		intf{ intf }, delay_runner{ delay_runner },
		listeners{}
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::LISTENERREGISTRAR };
	}

	ListenerRegistrarImpl::~ListenerRegistrarImpl()
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::LISTENERREGISTRAR };

		for (int t = LISTENER_TYPE_BEGIN; t < LISTENER_TYPE_END; ++t) {
			if (listeners[t].set.size()) {
				std::cerr << "Listeners have not been unregistered: " << magic_enum::enum_name((ListenerType)t) << '\n';
			}
		}
	}

	void ListenerRegistrarImpl::Register(ListenerTypeImpl listenerType, IGalaxyListener* listener) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::LISTENERREGISTRAR };

		if (listener == nullptr || listenerType < LISTENER_TYPE_BEGIN || listenerType >= LISTENER_TYPE_END) {
			return;
		}

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("listenerType: {}", magic_enum::enum_name((ListenerType)listenerType)));
			trace.write_all(std::format("listener: {}", (void*)listener));
		}

		lock_t lock{ listeners[listenerType].mtx };
		listeners[listenerType].set.insert(listener);
	}

	void ListenerRegistrarImpl::Unregister(ListenerTypeImpl listenerType, IGalaxyListener* listener) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::LISTENERREGISTRAR };

		if (listener == nullptr || listenerType < LISTENER_TYPE_BEGIN || listenerType >= LISTENER_TYPE_END) {
			return;
		}

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("listenerType: {}", magic_enum::enum_name((ListenerType)listenerType)));
			trace.write_all(std::format("listener: {}", (void*)listener));
		}

		{
			lock_t lock{ listeners[listenerType].mtx };
			listeners[listenerType].set.erase(listener);
		}

		request_helpers[listenerType].unregister(listener);
	}

	bool ListenerRegistrarImpl::ExecuteForListenerType(ListenerType listenerType, std::function<void(const std::set<IGalaxyListener*>& listeners)> code)
	{
		tracer::Trace trace{ "1s", __FUNCTION__, tracer::Trace::LISTENERREGISTRAR };

		if (trace.has_flags(tracer::Trace::HIGH_FREQUENCY_CALLS | tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("listenerType: {}", magic_enum::enum_name((ListenerType)listenerType)));
		}

		if (code == nullptr) {
			if (trace.has_flags(tracer::Trace::HIGH_FREQUENCY_CALLS | tracer::Trace::RETURN_VALUES)) {
				trace.write_all("code == nullptr");
			}
			return false;
		}

		listener_set set;
		{
			if (trace.has_flags(tracer::Trace::HIGH_FREQUENCY_CALLS | tracer::Trace::RETURN_VALUES)) {
				trace.write_all("locking...");
			}

			lock_t lock{ listeners[listenerType].mtx };

			if (trace.has_flags(tracer::Trace::HIGH_FREQUENCY_CALLS | tracer::Trace::RETURN_VALUES)) {
				trace.write_all("...locked");
			}

			auto& temp_set_ref = listeners[listenerType].set;

			if (trace.has_flags(tracer::Trace::HIGH_FREQUENCY_CALLS | tracer::Trace::RETURN_VALUES)) {
				trace.write_all(std::format("temp_set_ref.size(): ", temp_set_ref.size()));
			}

			if (temp_set_ref.size() == 0) {
				return false;
			}

			set = temp_set_ref; // COPY

			if (trace.has_flags(tracer::Trace::HIGH_FREQUENCY_CALLS | tracer::Trace::RETURN_VALUES)) {
				trace.write_all(std::format("set.size(): ", temp_set_ref.size()));
			}
		}

		code(set);

		return true;
	}

	bool ListenerRegistrarImpl::ExecuteForListenerTypePerEntry(ListenerType listenerType, std::function<void(IGalaxyListener* listener)> code)
	{
		tracer::Trace trace{ "1", __FUNCTION__, tracer::Trace::LISTENERREGISTRAR };

		if (trace.has_flags(tracer::Trace::HIGH_FREQUENCY_CALLS | tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("listenerType: {}", magic_enum::enum_name((ListenerType)listenerType)));
		}

		if (code == nullptr) {
			if (trace.has_flags(tracer::Trace::HIGH_FREQUENCY_CALLS | tracer::Trace::RETURN_VALUES)) {
				trace.write_all("code == nullptr");
			}
			return false;
		}

		return ExecuteForListenerType(listenerType, [&](const std::set<IGalaxyListener*>& listeners) -> void {
			for (auto& entry : listeners) {
				tracer::Trace trace2{ "1", "[loop lambda]", tracer::Trace::LISTENERREGISTRAR };

				if (trace2.has_flags(tracer::Trace::HIGH_FREQUENCY_CALLS | tracer::Trace::RETURN_VALUES)) {
					trace2.write_all(std::format("code(entry): {}", (void*)entry));
				}

				code(entry);
			}
			});
	}

	bool ListenerRegistrarImpl::ExecuteForListenerType(ListenerType listenerType, IGalaxyListener* extra, std::function<void(const std::set<IGalaxyListener*>& listeners)> code)
	{
		tracer::Trace trace{ "2s", __FUNCTION__, tracer::Trace::LISTENERREGISTRAR };

		if (trace.has_flags(tracer::Trace::HIGH_FREQUENCY_CALLS | tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("listenerType: {}", magic_enum::enum_name((ListenerType)listenerType)));
			trace.write_all(std::format("extra: {}", (void*)extra));
		}

		if (extra == nullptr && code == nullptr) {
			if (trace.has_flags(tracer::Trace::HIGH_FREQUENCY_CALLS | tracer::Trace::RETURN_VALUES)) {
				trace.write_all("extra == nullptr && code == nullptr");
			}
			return false;
		}

		listener_set set;
		{
			if (trace.has_flags(tracer::Trace::HIGH_FREQUENCY_CALLS | tracer::Trace::RETURN_VALUES)) {
				trace.write_all("locking...");
			}

			lock_t lock{ listeners[listenerType].mtx };

			if (trace.has_flags(tracer::Trace::HIGH_FREQUENCY_CALLS | tracer::Trace::RETURN_VALUES)) {
				trace.write_all("...locked");
			}

			auto& temp_set_ref = listeners[listenerType].set;

			if (trace.has_flags(tracer::Trace::HIGH_FREQUENCY_CALLS | tracer::Trace::RETURN_VALUES)) {
				trace.write_all(std::format("temp_set_ref.size(): ", temp_set_ref.size()));
			}

			if (set.size() == 0 && extra == nullptr) {

				if (trace.has_flags(tracer::Trace::HIGH_FREQUENCY_CALLS | tracer::Trace::RETURN_VALUES)) {
					trace.write_all("set.size() == 0 && extra == nullptr");
				}

				return false;
			}

			set = temp_set_ref; // COPY

			if (trace.has_flags(tracer::Trace::HIGH_FREQUENCY_CALLS | tracer::Trace::RETURN_VALUES)) {
				trace.write_all(std::format("set.size(): ", temp_set_ref.size()));
			}
		}

		if (extra != nullptr) {
			set.insert(extra);
		}

		code(set);

		return true;
	}

	bool ListenerRegistrarImpl::ExecuteForListenerTypePerEntry(ListenerType listenerType, IGalaxyListener* extra, std::function<void(IGalaxyListener* listener)> code)
	{
		tracer::Trace trace{ "2", __FUNCTION__, tracer::Trace::LISTENERREGISTRAR };

		if (trace.has_flags(tracer::Trace::HIGH_FREQUENCY_CALLS | tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("listenerType: {}", magic_enum::enum_name((ListenerType)listenerType)));
		}

		if (extra == nullptr && code == nullptr) {
			if (trace.has_flags(tracer::Trace::HIGH_FREQUENCY_CALLS | tracer::Trace::RETURN_VALUES)) {
				trace.write_all("extra == nullptr && code == nullptr");
			}
			return false;
		}

		return ExecuteForListenerType(listenerType, extra, [&](const std::set<IGalaxyListener*>& listeners) -> void {
			for (auto& entry : listeners) {
				tracer::Trace trace2{ "2", "[loop lambda]", tracer::Trace::LISTENERREGISTRAR};

				if (trace2.has_flags(tracer::Trace::HIGH_FREQUENCY_CALLS | tracer::Trace::RETURN_VALUES)) {
					trace2.write_all(std::format("code(entry): {}", (void*)entry));
				}

				code(entry);
			}
			});
	}
}
