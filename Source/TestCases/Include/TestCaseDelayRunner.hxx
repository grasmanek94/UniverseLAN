#pragma once

#include "TestCaseConcurrentQueue.hxx"

#include <functional>
#include <mutex>

class DelayRunner
{
public:
	using func_t = std::function<void(void)>;

private:
	Concurrency::concurrent_queue<func_t> queue;

public:
	DelayRunner() : queue{} {}
	virtual ~DelayRunner() {}

	void Run() {
		func_t func;
		while (queue.try_pop(func)) {
			func();
		}
	}

	void Add(const func_t& func) {
		queue.push(func);
	}
};
