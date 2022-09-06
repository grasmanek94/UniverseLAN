/**
 * @file
 * Contains classes representing exceptions.
 */

#include "GalaxyExport.h"
#include "Errors.h"

namespace galaxy
{
	namespace api
	{
		/**
		 * Retrieves error connected with the last API call on the local thread.
		 *
		 * @return Either the last API call error or NULL if there was no error.
		 */
		GALAXY_DLL_EXPORT const IError* GALAXY_CALLTYPE GetError() {
			return nullptr;
		}

		/** @} */
	}
}
