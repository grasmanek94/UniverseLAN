#include "ListenerRegistrar.hxx"

#include "UniverseLAN.hxx"

#include <Tracer.hxx>

#include <iostream>
#include <mutex>
#include <stdexcept>

namespace universelan::client {
	using namespace galaxy::api;
	ListenerRegistrarImpl::ListenerRegistrarImpl(InterfaceInstances* intf, DelayRunner* delay_runner) :
		intf{ intf }, delay_runner{ delay_runner },
		listeners{}
	{
		tracer::Trace trace { nullptr, __FUNCTION__ };
	}

	ListenerRegistrarImpl::~ListenerRegistrarImpl()
	{
		tracer::Trace trace { nullptr, __FUNCTION__ };

		for (int t = LISTENER_TYPE_BEGIN; t < LISTENER_TYPE_END; ++t) {
			if (listeners[t].set.size()) {
				std::cerr << "Listeners have not been unregistered: " << t << '\n';
			}
		}
	}

	void ListenerRegistrarImpl::Register(ListenerTypeImpl listenerType, IGalaxyListener* listener) {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		if (listener != nullptr) {
			std::cout << __FUNCTION__ << ":" << std::dec << listenerType << " @" << std::hex << (size_t)listener << std::dec << std::endl;

			lock_t lock{ listeners[listenerType].mtx };
			listeners[listenerType].set.insert(listener);
		}
	}

	void ListenerRegistrarImpl::Unregister(ListenerTypeImpl listenerType, IGalaxyListener* listener) {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		lock_t lock{ listeners[listenerType].mtx };
		listeners[listenerType].set.erase(listener);
	}

	bool ListenerRegistrarImpl::ExecuteForListenerType(ListenerType listenerType, std::function<void(const std::set<IGalaxyListener*>& listeners)> code)
	{
		tracer::Trace trace{ "1" };

		lock_t lock{ listeners[listenerType].mtx };

		listener_set& set = listeners[listenerType].set;
		if (set.size() == 0) {
			return false;
		}

		code(set);

		return true;
	}

	bool ListenerRegistrarImpl::ExecuteForListenerTypePerEntry(ListenerType listenerType, std::function<void(IGalaxyListener* listeners)> code)
	{
		tracer::Trace trace{ "1" };

		lock_t lock{ listeners[listenerType].mtx };

		listener_set& set = listeners[listenerType].set;
		if (set.size() == 0) {
			return false;
		}

		for (auto& entry : set) {
			code(entry);
		}

		return true;
	}

	bool ListenerRegistrarImpl::ExecuteForListenerType(ListenerType listenerType, IGalaxyListener* extra, std::function<void(const std::set<IGalaxyListener*>& listeners)> code)
	{
		tracer::Trace trace{ "2" };

		lock_t lock{ listeners[listenerType].mtx };

		listener_set& set = listeners[listenerType].set;
		bool added = false;
		if (extra != nullptr) {
			added = set.emplace(extra).second;
		}

		if (set.size() == 0) {
			assert(added == false);

			return false;
		}

		code(set);

		if (added) {
			set.erase(extra);
		}

		return true;
	}

	bool ListenerRegistrarImpl::ExecuteForListenerTypePerEntry(ListenerType listenerType, IGalaxyListener* extra, std::function<void(IGalaxyListener* listeners)> code)
	{
		tracer::Trace trace{ "2" };

		lock_t lock{ listeners[listenerType].mtx };

		listener_set& set = listeners[listenerType].set;

		if (extra != nullptr) {
			code(extra);
		}

		for (auto& entry : set) {
			if ((entry != extra) && (entry != nullptr)) {
				code(entry);
			}
		}

		return (set.size() > 0) || (extra != nullptr);
	}
}
