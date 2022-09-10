#include "ListenerRegistrar.hxx"

namespace galaxy
{
	namespace api
	{
		ListenerRegistrar::~ListenerRegistrar()
		{
		}

		void ListenerRegistrar::Register(ListenerType listenerType, IGalaxyListener* listener) {
		}


		void ListenerRegistrar::Unregister(ListenerType listenerType, IGalaxyListener* listener) {

		}

		GALAXY_DLL_EXPORT IListenerRegistrar* GALAXY_CALLTYPE ListenerRegistrar() {
			return nullptr;
		}

		GALAXY_DLL_EXPORT IListenerRegistrar* GALAXY_CALLTYPE GameServerListenerRegistrar() {
			return nullptr;
		}
	}
}
