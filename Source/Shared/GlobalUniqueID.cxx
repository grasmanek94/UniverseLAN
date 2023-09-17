#include "GlobalUniqueID.hxx"

#include <atomic>

namespace {
	std::atomic_uint64_t unique_global_counter{ 1 };
}

namespace universelan {
	uint64_t GlobalUniqueID::get()
	{
		return unique_global_counter.fetch_add(1);
	}
}
