#pragma once

#if !GALAXY_BUILD_FEATURE_HAS_INITOPTIONS
#include <stdint.h>
#include <cstddef>

namespace galaxy
{
	namespace api
	{
		/**
		 * @addtogroup api
		 * @{
		 */

		 /**
		 * The group of options used for Init configuration.
		 */
		struct InitOptionsFactory
		{
			/**
			 * InitOptions constructor.
			 *
			 * @remark On Android device Galaxy SDK needs a directory for internal storage (to keep a copy of system CA certificates).
			 * It should be an existing directory within the application file storage.
			 *
			 * @param [in] _clientID The ID of the client.
			 * @param [in] _clientSecret The secret of the client.
			 * @param [in] _configFilePath The path to folder which contains configuration files.
			 * @param [in] _storagePath Path to a directory that can be used for storing internal SDK data. Used only on Android devices. See remarks for more information.
			 */
			InitOptionsFactory(const char* _clientID, const char* _clientSecret, const char* _configFilePath = ".", void* _unused = NULL, const char* _storagePath = NULL)
				: clientID(_clientID)
				, clientSecret(_clientSecret)
				, configFilePath(_configFilePath)
				, storagePath(_storagePath)
				, galaxyPeerPath("")
			{
			}

			const char* clientID; ///< The ID of the client.
			const char* clientSecret; ///< The secret of the client.
			const char* configFilePath; ///< The path to folder which contains configuration files.
			const char* storagePath; ///< The path to folder for storing internal SDK data. Used only on Android devices.
			const char* galaxyPeerPath; ///< The path to folder for storing internal SDK data. Used only on Android devices.
		};

		/** @} */
	}
}
#endif
