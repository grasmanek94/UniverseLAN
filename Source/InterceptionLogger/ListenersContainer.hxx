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
			// REVIEW: If RegisterListener throws, this raw allocation is never
			// reclaimed. Use ownership/rollback so failed registration cannot leak T.
			T* listener = new T();
			listeners.emplace(listener, (ListenerType)T::GetListenerType());
			RegisterListener(listener, (ListenerType)T::GetListenerType());
		}
	};
}
