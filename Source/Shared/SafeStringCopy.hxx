#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <format>
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

	inline const char* safe_fix_null_char_ptr_annotate_ret(const char* value) {
		if (value == nullptr) {
			return "!!(nullptr)";
		}
		return value;
	}

#ifndef _WIN32
	size_t strnlen_s(const char* str, size_t strsz) {
		if (str == nullptr) {
			return 0;
		}
		return strnlen(str, strsz);
	}

#endif

	inline std::string safe_fix_null_char_ptr_annotate(const char* buffer, uint32_t buffer_len) {
		if (buffer == nullptr) {
			return "!!(nullptr)";
		}
		return std::string(buffer, std::min((size_t)buffer_len, strnlen_s(buffer, buffer_len)));
	}

	inline std::string bytes_to_hex(const void* data, uint32_t dataSize) {
		std::string hex;
		for (uint32_t i = 0; i < dataSize; ++i) {
			hex += std::format("{:02x}", ((const unsigned char*)data)[i]);
		}
		return hex;
	}
}
