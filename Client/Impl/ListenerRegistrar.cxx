#include "ListenerRegistrar.hxx"

#include <Tracer.hxx>

#include <iostream>
#include <mutex>
#include <stdexcept>

namespace universelan::client {
	using namespace galaxy::api;
	ListenerRegistrarImpl::ListenerRegistrarImpl(InterfaceInstances* intf) :
		intf{ intf },
		listeners{}
	{
		tracer::Trace trace{ __FUNCTION__ };
	}

	ListenerRegistrarImpl::~ListenerRegistrarImpl()
	{
		tracer::Trace trace{ __FUNCTION__ };

		for (int t = LISTENER_TYPE_BEGIN; t < LISTENER_TYPE_END; ++t) {
			if (listeners[t].set.size()) {
				std::cerr << "Listeners have not been unregistered: " << t << '\n';
			}
		}
	}

	void ListenerRegistrarImpl::Register(ListenerType listenerType, IGalaxyListener* listener) {
		tracer::Trace trace{ __FUNCTION__ };

		lock_t lock{ listeners[listenerType].mtx };
		listeners[listenerType].set.insert(listener);
	}

	void ListenerRegistrarImpl::Unregister(ListenerType listenerType, IGalaxyListener* listener) {
		tracer::Trace trace{ __FUNCTION__ };

		lock_t lock{ listeners[listenerType].mtx };
		listeners[listenerType].set.erase(listener);
	}

	bool ListenerRegistrarImpl::ExecuteForListenerType(ListenerType listenerType, std::function<void(const std::set<IGalaxyListener*>& listeners)> code)
	{
		tracer::Trace trace{ __FUNCTION__"1"};

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
		tracer::Trace trace{ __FUNCTION__"1"};

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
		tracer::Trace trace{ __FUNCTION__"2"};

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
		tracer::Trace trace{ __FUNCTION__"2"};

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