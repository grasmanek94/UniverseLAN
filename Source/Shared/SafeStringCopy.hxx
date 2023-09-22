#pragma once

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <string>

namespace universelan::util {
	inline bool safe_copy_str_n(const std::string& data, char* buffer, uint32_t buffer_len) {
		uint32_t copy_size = std::min((uint32_t)(data.length() + 1), buffer_len);
		
		std::copy_n(data.c_str(), copy_size, buffer);

		return copy_size > data.length();
	}

	inline bool safe_copy_str_n(const char* const data, char* buffer, uint32_t buffer_len) {
		uint32_t data_size = (uint32_t)std::strlen(data);
		uint32_t copy_size = std::min((uint32_t)(data_size + 1), buffer_len);

		std::copy_n(data, copy_size, buffer);

		return copy_size > data_size;
	}

	inline uint32_t safe_copy_binary_n(const std::string& data, char* buffer, uint32_t buffer_len) {
		uint32_t copy_size = std::min((uint32_t)(data.length()), buffer_len);

		std::copy_n(data.c_str(), copy_size, buffer);

		return copy_size;
	}

	inline uint32_t safe_copy_binary_n(const char* const data, uint32_t data_len, char* buffer, uint32_t buffer_len) {
		uint32_t copy_size = std::min((uint32_t)(data_len), buffer_len);

		std::copy_n(data, copy_size, buffer);

		return copy_size;
	}
}
