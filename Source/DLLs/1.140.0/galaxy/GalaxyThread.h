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
			 */
			virtual void Join() = 0;

			virtual ~IGalaxyThread() {};
		};

		/**
		 * Custom thread spawner for the Galaxy SDK.
		 */
		class IGalaxyThreadFactory
		{
		public:

			/*
			 * Spawn new internal Galaxy SDK thread.
			 *
			 * A new thread shall start from the provided ThreadEntryFunction accepting provided ThreadEntryParam.
			 *
			 * @note The very same allocator shall be used for thread objects allocations as specified in the InitOptions::galaxyAllocator.
			 *
			 * @param [in] entryPoint The wrapper for the entry point function.
			 * @param [in] param The parameter for the thread entry point.
			 */
			virtual IGalaxyThread* SpawnThread(ThreadEntryFunction const entryPoint, ThreadEntryParam param) = 0;

			virtual ~IGalaxyThreadFactory() {};
		};

		/** @} */
	}
}

#endif
