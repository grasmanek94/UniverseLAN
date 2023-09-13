#pragma once

#if GALAXY_BUILD_FEATURE_FACTORY_INTERFACE
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
		  * Allocate function.
		  *
		  * @param [in] size Requested size of allocation.
		  * @param [in] typeName String which identifies the type of allocation.
		  * @return Pointer to memory block or nullptr if it goes out of memory.
		  */
		typedef void* (*GalaxyMalloc)(uint32_t size, const char* typeName);

		/**
		 * Reallocate function.
		 *
		 * @param [in] ptr Pointer to the memory block to be reallocated.
		 * @param [in] newSize New, requested size of allocation.
		 * @param [in] typeName String which identifies the type of allocation.
		 * @return Pointer to memory block or nullptr if it goes out of memory.
		 */
		typedef void* (*GalaxyRealloc)(void* ptr, uint32_t newSize, const char* typeName);

		/**
		 * Free function.
		 *
		 * @param [in] ptr Pointer to memory block requested to be freed.
		 */
		typedef void (*GalaxyFree)(void* ptr);

		/**
		 * Custom memory allocator for GOG Galaxy SDK.
		 */
		struct GalaxyAllocator
		{
			/**
			 * GalaxyAllocator default constructor.
			 */
			GalaxyAllocator()
				: galaxyMalloc(NULL)
				, galaxyRealloc(NULL)
				, galaxyFree(NULL)
			{}

			/**
			 * GalaxyAllocator constructor.
			 *
			 * @param [in] _galaxyMalloc Allocation function.
			 * @param [in] _galaxyRealloc Reallocation function.
			 * @param [in] _galaxyFree Free function.
			 */
			GalaxyAllocator(GalaxyMalloc _galaxyMalloc, GalaxyRealloc _galaxyRealloc, GalaxyFree _galaxyFree)
				: galaxyMalloc(_galaxyMalloc)
				, galaxyRealloc(_galaxyRealloc)
				, galaxyFree(_galaxyFree)
			{}

			GalaxyMalloc galaxyMalloc; ///< Allocation function.
			GalaxyRealloc galaxyRealloc; ///< Reallocation function.
			GalaxyFree galaxyFree; ///< Free function.
		};

		/** @} */

		/**
		 * @addtogroup api
		 * @{
		 */

		 /**
		 * The group of options used for Init configuration.
		 */
		struct InitOptions
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
			 * @param [in] _galaxyAllocator The custom memory allocator. Shall only be set once for both Galaxy Peer and Game Server.
			 * @param [in] _storagePath Path to a directory that can be used for storing internal SDK data. Used only on Android devices. See remarks for more information.
			 */
			InitOptions(const char* _clientID, const char* _clientSecret, const char* _configFilePath = ".", GalaxyAllocator* _galaxyAllocator = NULL, const char* _storagePath = NULL)
				: clientID(_clientID)
				, clientSecret(_clientSecret)
				, configFilePath(_configFilePath)
				, galaxyAllocator(_galaxyAllocator)
				, storagePath(_storagePath)
			{
			}

			const char* clientID; ///< The ID of the client.
			const char* clientSecret; ///< The secret of the client.
			const char* configFilePath; ///< The path to folder which contains configuration files.
			const char* storagePath; ///< The path to folder for storing internal SDK data. Used only on Android devices.
			GalaxyAllocator* galaxyAllocator; ///< The custom memory allocator. Shall only be set once for both Galaxy Peer and Game Server.
		};

		/** @} */
	}
}
#endif
