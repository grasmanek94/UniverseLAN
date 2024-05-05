#include "ListenersContainer.hxx"

#include <IListenerRegistrar.h>

#include <stdexcept>

namespace universelan::client {
	using namespace galaxy::api;

	ListenersContainer::ListenersContainer(IListenerRegistrar* registrar) : listeners{}, registrar{ registrar } {
		if (registrar == nullptr) {
			throw std::invalid_argument("registrar==nullptr");
		}
	}

	ListenersContainer::~ListenersContainer() { UnregisterAllListeners(); }

	void ListenersContainer::RegisterListener(IGalaxyListener* listener, ListenerType type) {
		registrar->Register(type, listener);
	}

	void ListenersContainer::UnregisterAllListeners() {
		while (listeners.size() > 0) {
			auto item = *listeners.begin();
			registrar->Unregister(item.second, item.first);
			listeners.erase(listeners.begin());
		}
	}
}
