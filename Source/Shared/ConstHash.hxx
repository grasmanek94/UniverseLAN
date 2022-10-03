#pragma once

#include <cstdint>
#include <string>

namespace universelan {
	static_assert(sizeof(uint64_t) == 8, "You cannot compile this application for the chosen architecture");

	// compile time FNV-1a
	inline constexpr uint32_t const_hash(const char* const str, const uint32_t value = 0x811c9dc5) noexcept {
		return (str[0] == '\0') ? value : const_hash(&str[1], (value ^ uint32_t(str[0])) * 0x1000193);
	}

	inline constexpr uint32_t const_hash(const std::string& str, const uint32_t value = 0x811c9dc5) noexcept {
		return const_hash(str.c_str(), value);
	}

	inline constexpr uint64_t const_hash64(const char* const str, const uint64_t value = 0xcbf29ce484222325) noexcept {
		return (str[0] == '\0') ? value : const_hash64(&str[1], (value ^ uint64_t(str[0])) * 0x100000001b3);
	}

	inline constexpr uint64_t const_hash64(const std::string& str, const uint64_t value = 0x811c9dc5) noexcept {
		return const_hash64(str.c_str(), value);
	}

	inline constexpr uint64_t const_hash64_data(const char* data, size_t size, const uint64_t value = 0xcbf29ce484222325) noexcept {
		return (size == 0) ? value : const_hash64_data(&data[1], size - 1, (value ^ uint64_t(data[0])) * 0x100000001b3);
	}
}