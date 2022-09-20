#ifndef LSFDRMFG_IMPL_DELAY_RUNNER_H
#define LSFDRMFG_IMPL_DELAY_RUNNER_H

#include <functional>
#include <mutex>
#include <concurrent_queue.h>

namespace universelan::client {
	/**
	 * @addtogroup api
	 * @{
	 */

	 /**
	  * The interface for handling telemetry.
	  */
	class DelayRunner
	{
	public:
		using mtx_t = std::recursive_mutex;
		using lock_t = std::scoped_lock<mtx_t>;
		using func_t = std::function<void(void)>;

	private:
		concurrency::concurrent_queue<func_t> queue;

	public:
		DelayRunner();
		virtual ~DelayRunner();

		virtual void Run();
		virtual void Add(const func_t& func);
	};

	/** @} */
}

#endif
