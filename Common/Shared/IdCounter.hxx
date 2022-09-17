#pragma once

#include <cstdint>
#include <set>

namespace universelan {
	/*
	 * Counts ids from 1 (id 0 = invalid)
	 */
	class IdCounter
	{
		uint64_t max_id;
		std::set<uint64_t> free_ids;
	public:
		IdCounter();
		uint64_t GetNewId();
		bool FreeId(uint64_t id);
		uint64_t GetCurrentMaxId();
	};
}
