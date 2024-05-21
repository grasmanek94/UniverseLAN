#pragma once

#include "TestCaseConcurrentQueue.hxx"

#include <chrono>
#include <functional>
#include <mutex>
#include <queue>

class DelayRunner
{
public:
	using func_t = std::function<void(void)>;
	using mutex_t = std::recursive_mutex;
	using lock_t = std::scoped_lock<mutex_t>;

private:
	struct TimedFuncT {
		std::chrono::steady_clock::time_point time;
		func_t func;

		bool operator <(const TimedFuncT& y) const {
			return y.time < time;
		}
	};

	Concurrency::concurrent_queue<func_t> queue;

	mutex_t							mtx_timed_queue;
	std::priority_queue<TimedFuncT> timed_queue;

public:
	DelayRunner() : queue{}, mtx_timed_queue{}, timed_queue {} {}
	virtual ~DelayRunner() {}

	void Run() {
		func_t func;
		while (queue.try_pop(func)) {
			func();
		}

		lock_t lock{ mtx_timed_queue };
		auto now = std::chrono::steady_clock::now();
		while (!timed_queue.empty() && now > timed_queue.top().time) {
			timed_queue.top().func();
			timed_queue.pop();
		}
	}

	void Add(const func_t& func) {
		queue.push(func);
	}

	void Add(std::chrono::milliseconds delay, const func_t& func) {
		auto now = std::chrono::steady_clock::now();
		auto exec_point = now + delay;

		lock_t lock{ mtx_timed_queue };
		timed_queue.push(TimedFuncT{ exec_point, func });
	}
};
