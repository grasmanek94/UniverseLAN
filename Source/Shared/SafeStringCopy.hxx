#pragma once

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <string>

namespace universelan::util {
	inline uint32_t safe_copy_str_n(const std::string& data, char* buffer, uint32_t buffer_len) {
		if (buffer == nullptr) {
			return 0;
		}

		uint32_t data_size = (uint32_t)(data.length() + 1);
		uint32_t copy_size = std::min(data_size, buffer_len);
		
		std::copy_n(data.c_str(), copy_size, buffer);
		if (data_size > buffer_len) {
			buffer[buffer_len - 1] = '\0';
		}

		return copy_size;
	}

	inline uint32_t safe_copy_str_n(const char* const data, char* buffer, uint32_t buffer_len) {
		if (buffer == nullptr) {
			return 0;
		}

		uint32_t data_size = (uint32_t)(std::strlen(data) + 1);
		uint32_t copy_size = std::min(data_size, buffer_len);

		std::copy_n(data, copy_size, buffer);
		if (data_size > buffer_len) {
			buffer[buffer_len - 1] = '\0';
		}

		return copy_size;
	}

	inline uint32_t safe_copy_binary_n(const std::string& data, char* buffer, uint32_t buffer_len) {
		if (buffer == nullptr) {
			return 0;
		}

		uint32_t copy_size = std::min((uint32_t)(data.length()), buffer_len);

		std::copy_n(data.c_str(), copy_size, buffer);

		return copy_size;
	}

	inline uint32_t safe_copy_binary_n(const char* const data, uint32_t data_len, char* buffer, uint32_t buffer_len) {
		if (buffer == nullptr) {
			return 0;
		}

		uint32_t copy_size = std::min((uint32_t)(data_len), buffer_len);

		std::copy_n(data, copy_size, buffer);

		return copy_size;
	}

	inline const char* safe_fix_null_char_ptr(const char*& value) {
		if (value == nullptr) {
			value = "";
		}
		return value;
	}

	inline const char* safe_fix_null_char_ptr_ret(const char* value) {
		if (value == nullptr) {
			return "";
		}
		return value;
	}
}
