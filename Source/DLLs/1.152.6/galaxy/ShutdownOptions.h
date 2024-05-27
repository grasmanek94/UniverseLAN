#ifndef GALAXY_SHUTDOWN_OPTIONS_H
#define GALAXY_SHUTDOWN_OPTIONS_H

/**
 * @file
 * Contains class that holds Galaxy shutdown parameters.
 */

namespace galaxy
{
	namespace api
	{
		/**
		 * @addtogroup api
		 * @{
		 */

		 /**
		 * The group of options used for Shutdown options.
		 */
		struct ShutdownOptions
		{
			/**
			 * ShutdownOptions constructor.
			 *
			 * @param [in] _preserveStaticObjects Set for preserving static objects for consecutive initialization.
			 */
			ShutdownOptions(bool _preserveStaticObjects = false)
				: preserveStaticObjects(_preserveStaticObjects)
			{}


			bool preserveStaticObjects;
		};

		 /** @} */
	}
}

#endif
