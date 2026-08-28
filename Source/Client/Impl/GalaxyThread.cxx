#if GALAXY_BUILD_FEATURE_HAS_IGALAXYTHREADFACTORY

#include "GalaxyThread.hxx"

#include <Tracer.hxx>

#include <thread>

namespace universelan::client {
	using namespace galaxy::api;
	/**
	 * The interface representing a thread object.
	 */

	GalaxyThreadImpl::GalaxyThreadImpl(std::thread&& thread) :
		_thread(std::move(thread))
	{
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IGALAXYTHREAD };
	}
	/**
	 * Join the thread.
	 *
	 * Wait until IGalaxyThread execution is finished. Internal callers of this function are blocked until the function returns.
	 */
	void GalaxyThreadImpl::Join() {
		// REVIEW: std::thread::join throws when the wrapper was already joined,
		// detached, or never started. The interface method is called by SDK code
		// where an invalid lifecycle state should be handled explicitly rather
		// than allowing an exception to escape through the ABI.
		_thread.join();
	}

#if GALAXY_BUILD_FEATURE_IGALAXYTHREAD_JOINABLE_DETACH
	/**
	 * Checks if the IGalaxyThread is ready to Join().
	 *
	 * @return true if the thread is ready to Join().
	 */
	bool GalaxyThreadImpl::Joinable() {
		return _thread.joinable();
	}

	/**
	 * Detach the thread.
	 *
	 * Separate the thread of execution from the IGalaxyThread object, allowing execution to continue independently.
	 */
	void GalaxyThreadImpl::Detach() {
		// REVIEW: detach() also throws for a non-joinable thread. Check
		// joinable() (or make repeated detach idempotent) before calling it so
		// lifecycle races do not terminate the process from a noexcept boundary.
		_thread.detach();
	}
#endif

	GalaxyThreadImpl::~GalaxyThreadImpl() {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IGALAXYTHREAD };

		/*if (_thread.joinable()) {
			_thread.join();
		}*/

		// REVIEW: A destructor must not unconditionally detach: std::thread
		// throws if it is not joinable, and this implicitly-noexcept destructor
		// then terminates the process. More importantly, detaching leaves SDK
		// work running after the wrapper is destroyed; join or coordinate
		// shutdown, and only act when joinable().
		_thread.detach();
	};

	/**
	 * Custom thread spawner for the Galaxy SDK.
	 */

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
	IGalaxyThread* GalaxyThreadFactory::SpawnThread(ThreadEntryFunction const entryPoint, ThreadEntryParam param) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IGALAXYTHREAD };

		// TODO: use GalaxyAllocator
		return new GalaxyThreadImpl(std::thread(entryPoint, param));
	}

	GalaxyThreadFactory::~GalaxyThreadFactory() {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IGALAXYTHREAD };
	};

	/** @} */
}
#endif
