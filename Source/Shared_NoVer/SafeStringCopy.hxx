#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <format>
#include <iterator>
#include <string>

namespace universelan::util {

	// Precondition: source and destination ranges must not overlap.
	// Returns amount of bytes written, including the null terminator.
	inline uint32_t safe_copy_str_n(const std::string& data, char* const buffer, const uint32_t buffer_len) noexcept {
		if ((buffer == nullptr) || (buffer_len < 1)) {
			return 0;
		}

		const uint32_t copy_size = (uint32_t)std::min(data.size(), (size_t)(buffer_len - 1U));

		std::copy_n(data.c_str(), copy_size, buffer);
		buffer[copy_size] = '\0';

		return copy_size + 1;
	}

	// Preconditions:
	// - data points to a valid null-terminated string.
	// - source and destination ranges must not overlap.
	// Returns amount of bytes written, including the null terminator.
	inline uint32_t safe_copy_str_n(const char* const data, char* const buffer, const uint32_t buffer_len) noexcept {
		if ((data == nullptr) || (buffer == nullptr) || (buffer_len < 1)) {
			return 0;
		}

		const uint32_t copy_size = (uint32_t)std::min(std::strlen(data), (size_t)(buffer_len - 1U));

		std::copy_n(data, copy_size, buffer);
		buffer[copy_size] = '\0';

		return copy_size + 1;
	}

	// Precondition: source and destination ranges must not overlap.
	// Returns amount of bytes written.
	inline uint32_t safe_copy_binary_n(const std::string& data, char* const buffer, const uint32_t buffer_len) noexcept {
		if ((buffer == nullptr) || (buffer_len < 1)) {
			return 0;
		}

		const uint32_t copy_size = (uint32_t)std::min(data.length(), (size_t)buffer_len);

		std::copy_n(data.data(), copy_size, buffer);

		return copy_size;
	}

	// Precondition: source and destination ranges must not overlap.
	// Returns amount of bytes written.
	inline uint32_t safe_copy_binary_n(const char* const data, uint32_t data_len, char* const buffer, const uint32_t buffer_len) noexcept {
		if ((data == nullptr) || (buffer == nullptr) || (buffer_len < 1)) {
			return 0;
		}

		const uint32_t copy_size = std::min(data_len, buffer_len);

		std::copy_n(data, copy_size, buffer);

		return copy_size;
	}

	inline const char* safe_fix_null_char_ptr(const char*& value) noexcept {
		if (value == nullptr) {
			value = "";
		}
		return value;
	}

	inline const char* safe_fix_null_char_ptr_ret(const char* const value) noexcept {
		if (value == nullptr) {
			return "";
		}
		return value;
	}

	inline const char* safe_fix_null_char_ptr_annotate_ret(const char* const value) noexcept {
		if (value == nullptr) {
			return "!!(nullptr)";
		}
		return value;
	}

	inline size_t bounded_strlen(const char* const str, const size_t maximum) noexcept
	{
		if (str == nullptr || maximum == 0) {
			return 0;
		}

		const void* const terminator =
			std::memchr(str, '\0', maximum);

		if (terminator == nullptr) {
			return maximum;
		}

		return (size_t)(static_cast<const char*>(terminator) - str);
	}

	inline std::string safe_fix_null_char_ptr_annotate(const char* const buffer, uint32_t buffer_len) {
		if (buffer == nullptr) {
			return "!!(nullptr)";
		}
		return std::string(buffer, bounded_strlen(buffer, (size_t)buffer_len));
	}

	inline std::string bytes_to_hex(const void* const data, const uint32_t dataSize) {
		if (data == nullptr) {
			return "";
		}

		std::string hex{};
		hex.reserve((size_t)(dataSize) * 2U);

		for (uint32_t i = 0; i < dataSize; ++i) {
			std::format_to(std::back_inserter(hex), "{:02x}", ((const unsigned char*)data)[i]);
		}

		return hex;
	}
}
