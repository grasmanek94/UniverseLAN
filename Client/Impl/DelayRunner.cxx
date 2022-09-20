#include "DelayRunner.hxx"

namespace universelan::client {
	DelayRunner::DelayRunner() 
		: queue{}
	{}

	DelayRunner::~DelayRunner() 
	{}

	void DelayRunner::Run() {
		func_t func;
		while (queue.try_pop(func)) {
			func();
		}
	}

	void DelayRunner::Add(const func_t& func) {
		queue.push(func);
	}
}
