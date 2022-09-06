/**
 * @file
 * Contains data structures and interfaces related to callback listeners.
 */

#include "stdint.h"
#include <stdlib.h>
#include "GalaxyExport.h"
#include "IListenerRegistrar.h"

namespace galaxy
{
	namespace api
	{
		/**
		 * @addtogroup Peer
		 * @{
		 */

		/**
		 * Returns an instance of IListenerRegistrar.
		 *
		 * @return An instance of IListenerRegistrar.
		 */
		GALAXY_DLL_EXPORT IListenerRegistrar* GALAXY_CALLTYPE ListenerRegistrar() {
			return nullptr;
		}

		/** @} */

		/**
		 * @addtogroup GameServer
		 * @{
		 */

		/**
		 * Returns an instance of IListenerRegistrar interface the for Game Server entity.
		 *
		 * @return An instance of IListenerRegistrar.
		 */
		GALAXY_DLL_EXPORT IListenerRegistrar* GALAXY_CALLTYPE GameServerListenerRegistrar() {
			return nullptr;
		}
	}
}
