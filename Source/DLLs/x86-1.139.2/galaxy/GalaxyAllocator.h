#ifndef GALAXY_I_ALLOCATOR_H
#define GALAXY_I_ALLOCATOR_H

/**
 * @file
 * Contains definition of custom memory allocator.
 */

#include <cstdint>
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
		using GalaxyMalloc = void* (*)(uint32_t size, const char* typeName);

		/**
		 * Reallocate function.
		 *
		 * @param [in] ptr Pointer to the memory block to be reallocated.
		 * @param [in] newSize New, requested size of allocation.
		 * @param [in] typeName String which identifies the type of allocation.
		 * @return Pointer to memory block or nullptr if it goes out of memory.
		 */
		using GalaxyRealloc = void* (*)(void* ptr, uint32_t newSize, const char* typeName);

		/**
		 * Free function.
		 *
		 * @param [in] ptr Pointer to memory block requested to be freed.
		 */
		using GalaxyFree = void (*)(void* ptr);

		/**
		 * Custom memory allocator for GOG Galaxy SDK.
		 */
		struct GalaxyAllocator
		{
			/**
			 * GalaxyAllocator default constructor.
			 */
			GalaxyAllocator()
				: galaxyMalloc(nullptr)
				, galaxyRealloc(nullptr)
				, galaxyFree(nullptr)
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
	}
}

#endif