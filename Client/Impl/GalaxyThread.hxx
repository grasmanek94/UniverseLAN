#ifndef LSFDRMFG_IMPL_GALAXY_THREAD_H
#define LSFDRMFG_IMPL_GALAXY_THREAD_H

#include <thread>

#include <GalaxyAllocator.h>
#include <GalaxyThread.h>

namespace galaxy
{
	namespace api
	{
		/**
		 * The interface representing a thread object.
		 */
		class GalaxyThreadImpl : public IGalaxyThread
		{
		public:
			GalaxyThreadImpl(std::thread&& thread);
			/**
			 * Join the thread.
			 *
			 * Wait until IGalaxyThread execution is finished. Internal callers of this function are blocked until the function returns.
			 */
			virtual void Join() override;

			/**
			 * Checks if the IGalaxyThread is ready to Join().
			 *
			 * @return true if the thread is ready to Join().
			 */
			virtual bool Joinable() override;

			/**
			 * Detach the thread.
			 *
			 * Separate the thread of execution from the IGalaxyThread object, allowing execution to continue independently.
			 */
			virtual void Detach() override;

			virtual ~GalaxyThreadImpl();

		private:
			std::thread _thread;
		};

		/**
		 * Custom thread spawner for the Galaxy SDK.
		 */
		class GalaxyThreadFactory : public IGalaxyThreadFactory
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
			virtual IGalaxyThread* SpawnThread(ThreadEntryFunction const entryPoint, ThreadEntryParam param);

			virtual ~GalaxyThreadFactory();
		};

		/** @} */
	}
}

#endif
