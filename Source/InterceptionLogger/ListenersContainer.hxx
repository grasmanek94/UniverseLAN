#pragma once

#include <IListenerRegistrar.h>

#include <map>

namespace universelan::client {
	using namespace galaxy::api;

	class ListenersContainer {
	public:
		using map_t = std::map<IGalaxyListener*, ListenerType>;
	private:
		IListenerRegistrar* registrar;
		map_t listeners;

		void RegisterListener(IGalaxyListener* listener, ListenerType type);

	public:
		ListenersContainer(IListenerRegistrar* registrar);
		~ListenersContainer();

		void UnregisterAllListeners();

		template<typename T>
		void AddListener() {
			T* listener = new T();
			listeners.emplace(listener, T::GetListenerType());
			RegisterListener(listener, T::GetListenerType());
		}
	};
}
