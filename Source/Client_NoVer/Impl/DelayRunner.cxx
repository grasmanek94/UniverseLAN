#include "DelayRunner.hxx"

namespace universelan::client {
	DelayRunner::DelayRunner() : queue{} {}
	DelayRunner::~DelayRunner() {}

	void DelayRunner::Run() {
		func_t func;
		while (queue.try_pop(func)) {
			// REVIEW: A callback exception aborts this loop and escapes through
			// ProcessData, leaving later callbacks queued and potentially
			// terminating the host at the ABI boundary. Define whether callbacks
			// are isolated/logged or whether failure must be propagated.
			func();
		}
	}

	void DelayRunner::Add(const func_t& func) {
		queue.push(func);
	}
}
