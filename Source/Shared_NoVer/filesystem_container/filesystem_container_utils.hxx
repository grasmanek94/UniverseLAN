#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace filesystem_container {
	bool inside_basepath(const std::filesystem::path& basepath, const std::filesystem::path& relpath);

	std::filesystem::path sandbox_secure_path_concat(const std::filesystem::path& secure_basepath, const std::filesystem::path& untrusted_directories, const std::filesystem::path& untrusted_file_name);
	std::filesystem::path sandbox_secure_path_concat(const std::filesystem::path& secure_basepath, const std::filesystem::path& untrusted_file_name);

	// Resolves all relative links lexically first, then weakly canonical, converts to default path separators and makes the path absolute
	std::filesystem::path sanitize_path(const std::filesystem::path& messy_path);

	// Resolves all relative links lexically first, converts to default path separators but keeps the path relative
	std::filesystem::path sanitize_relative_path(const std::filesystem::path& relative_messy_path);

	std::string filename_decode(const std::string& value);
	std::string filename_encode(const std::string& value);
	std::filesystem::path filename_decode(const std::filesystem::path& value);
	std::filesystem::path filename_encode(const std::filesystem::path& value);

	std::string filename_encode_with_slashes(const std::string& value);

	std::vector<std::filesystem::path> recurse_list_files(const std::filesystem::path& search_root_path);
	std::vector<std::filesystem::path> list_files(const std::filesystem::path& search_root_path);

	uint64_t file_time_now_since_epoch();
}
