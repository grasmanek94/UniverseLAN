#ifndef GALAXY_THREAD_H
#define GALAXY_THREAD_H

namespace galaxy
{
	namespace api
	{

		/**
		 * @addtogroup api
		 * @{
		 */

		/**
		 * The parameter for the thread entry point.
		 */
		typedef void* ThreadEntryParam;

		/**
		 * The entry point function which shall be started in a new thread.
		 */
		typedef void (*ThreadEntryFunction)(ThreadEntryParam);

		/**
		 * The interface representing a thread object.
		 */
		class IGalaxyThread
		{
		public:

			/**
			 * Join the thread.
			 *
			 * Wait until IGalaxyThread execution is finished. Internal callers of this function are blocked until the function returns.
			 */
			virtual void Join() = 0;

			/**
			 * Checks if the IGalaxyThread is ready to Join().
			 *
			 * @return true if the thread is ready to Join().
			 */
			virtual bool Joinable() = 0;

			/**
			 * Detach the thread.
			 *
			 * Separate the thread of execution from the IGalaxyThread object, allowing execution to continue independently.
			 */
			virtual void Detach() = 0;

			virtual ~IGalaxyThread() {};
		};

		/**
		 * Custom thread spawner for the Galaxy SDK.
		 */
		class IGalaxyThreadFactory
		{
		public:

			/**
			 * Spawn new internal Galaxy SDK thread.
			 *
			 * A new thread shall start from the provided ThreadEntryFunction accepting provided ThreadEntryParam.
			 *
			 * @note The very same allocator shall be used for thread objects allocations as specified in the InitOptions::galaxyAllocator.
			 *
			 * @param [in] entryPoint The wrapper for the entry point function.
			 * @param [in] param The parameter for the thread entry point.
			 * @return New thread object.
			 */
			virtual IGalaxyThread* SpawnThread(ThreadEntryFunction const entryPoint, ThreadEntryParam param) = 0;

			virtual ~IGalaxyThreadFactory() {};
		};

		/** @} */
	}
}

#endif
