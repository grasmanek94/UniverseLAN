#pragma once

// Runtime unique ID

#include <cstdint>

namespace universelan {
	class GlobalUniqueID
	{
		GlobalUniqueID() = delete;
		~GlobalUniqueID() = delete;
	public:
		/* Thread safe */
		static uint64_t get();
	};
}
