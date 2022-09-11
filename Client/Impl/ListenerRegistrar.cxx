#include "ListenerRegistrar.hxx"

namespace galaxy
{
	namespace api
	{
		ListenerRegistrarImpl::~ListenerRegistrarImpl()
		{
		}

		void ListenerRegistrarImpl::Register(ListenerType listenerType, IGalaxyListener* listener) {
		}


		void ListenerRegistrarImpl::Unregister(ListenerType listenerType, IGalaxyListener* listener) {

		}

		GALAXY_DLL_EXPORT IListenerRegistrar* GALAXY_CALLTYPE ListenerRegistrar() {
			return nullptr;
		}

		GALAXY_DLL_EXPORT IListenerRegistrar* GALAXY_CALLTYPE GameServerListenerRegistrar() {
			return nullptr;
		}
	}
}
