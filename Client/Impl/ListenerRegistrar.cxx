#include "ListenerRegistrar.hxx"

#include <iostream>
#include <mutex>
#include <stdexcept>

namespace universelan::client {
	using namespace galaxy::api;
	ListenerRegistrarImpl::ListenerRegistrarImpl(InterfaceInstances* intf) :
		intf{ intf },
		listeners{}
	{ }

	ListenerRegistrarImpl::~ListenerRegistrarImpl()
	{
		for (int t = LISTENER_TYPE_BEGIN; t < LISTENER_TYPE_END; ++t) {
			if (listeners[t].set.size()) {
				std::cerr << "Listeners have not been unregistered: " << t << '\n';
			}
		}
	}

	void ListenerRegistrarImpl::Register(ListenerType listenerType, IGalaxyListener* listener) {
		std::scoped_lock<mutex_t> lock(listeners[listenerType].mtx);
		listeners[listenerType].set.insert(listener);
	}

	void ListenerRegistrarImpl::Unregister(ListenerType listenerType, IGalaxyListener* listener) {
		std::scoped_lock<mutex_t> lock(listeners[listenerType].mtx);
		listeners[listenerType].set.erase(listener);
	}

	void ListenerRegistrarImpl::ExecuteForListenerType(ListenerType listenerType, std::function<void(const std::set<IGalaxyListener*>& listeners)> code)
	{
		std::scoped_lock<mutex_t> lock(listeners[listenerType].mtx);
		code(listeners[listenerType].set);
	}

	void ListenerRegistrarImpl::ExecuteForListenerTypePerEntry(ListenerType listenerType, std::function<void(IGalaxyListener* listeners)> code)
	{
		std::scoped_lock<mutex_t> lock(listeners[listenerType].mtx);
		for (auto& entry : listeners[listenerType].set) {
			code(entry);
		}
	}

	void ListenerRegistrarImpl::ExecuteForListenerType(ListenerType listenerType, IGalaxyListener* extra, std::function<void(const std::set<IGalaxyListener*>& listeners)> code)
	{
		std::scoped_lock<mutex_t> lock(listeners[listenerType].mtx);

		listener_set& set = listeners[listenerType].set;
		auto item = set.emplace(extra);

		code(set);

		if (item.second) {
			set.erase(item.first);
		}
	}

	void ListenerRegistrarImpl::ExecuteForListenerTypePerEntry(ListenerType listenerType, IGalaxyListener* extra, std::function<void(IGalaxyListener* listeners)> code)
	{
		std::scoped_lock<mutex_t> lock(listeners[listenerType].mtx);

		if (extra != nullptr) {
			code(extra);
		}

		for (auto& entry : listeners[listenerType].set) {
			if ((entry != extra) && (entry != nullptr)) {
				code(entry);
			}
		}
	}
}