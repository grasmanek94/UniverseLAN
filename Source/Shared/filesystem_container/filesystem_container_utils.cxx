#include "filesystem_container_utils.hxx"

#include <array>
#include <filesystem>
#include <stdexcept>
#include <sstream>

namespace filesystem_container {
	namespace {
		constexpr static const char escape_character = '%';
		constexpr static const std::array<const char, 8> bad_chars = { '"', escape_character, '*' , ':', '<', '>', '?', '|' };
		constexpr static const std::array<const char, 10> bad_chars_with_slashes = { '"', escape_character, '*' , '/', ':', '<', '>', '?', '\\', '|' };

		int filename_decode_piece_unchecked(std::string_view const str) noexcept {
			int res = 0;
			for (auto ch : str) {
				int mid_res = ch - '0';
				if (mid_res >= 10) {
					mid_res = ch - 'A' + 10;
				}
				res = res * 16 + mid_res;
			}
			return res;
		}

		template <typename T>
		bool filename_encode_bad_char(std::ostringstream& escaped, const char c, const T& bad_chars_ref) {

			for (const auto b : bad_chars_ref) {
				[[unlikely]]
				if (b == c) {
					escaped << escape_character;
					escaped << std::uppercase;
					escaped << std::setw(2) << int((unsigned char)c);
					escaped << std::nouppercase;
					return true;
				}
			}

			[[unlikely]]
			if (c < 32) {
				escaped << escape_character;
				escaped << std::uppercase;
				escaped << std::setw(2) << int((unsigned char)c);
				escaped << std::nouppercase;
				return true;
			}

			[[likely]]
			return false;
		}

		template <typename T>
		std::vector<std::filesystem::path> generic_list_files(const std::filesystem::path& search_root_path) {
			std::vector<std::filesystem::path> file_list;
			auto entries = T(search_root_path);
			for (auto& entry : entries) {
				auto relative_path = std::filesystem::relative(entry, search_root_path);
				file_list.push_back(relative_path);
			}
			return file_list;
		}
	}

	bool inside_basepath(
		const std::filesystem::path& basepath,
		const std::filesystem::path& relpath) {

		const auto baseabspath = std::filesystem::weakly_canonical(basepath);
		const auto abspath = std::filesystem::weakly_canonical(basepath / relpath);

		const auto index = abspath.string().rfind(baseabspath.string(), 0);

		[[unlikely]]
		if (index != 0) {
			return false;
		}

		return true;
	}

	std::filesystem::path sandbox_secure_path_concat(const std::filesystem::path& secure_basepath, const std::filesystem::path& untrusted_directories, const std::filesystem::path& untrusted_file_name) {
		return sandbox_secure_path_concat(secure_basepath, untrusted_directories / untrusted_file_name);
	}

	std::filesystem::path sandbox_secure_path_concat(const std::filesystem::path& secure_basepath, const std::filesystem::path& untrusted_path) {
		[[likely]]
		if (inside_basepath(secure_basepath, untrusted_path)) {
			return sanitize_path(secure_basepath / untrusted_path);
		}

		if (untrusted_path == "/" || untrusted_path == "") {
			return secure_basepath;
		}

		[[unlikely]]
		throw std::runtime_error("Security Exception: Path traversal outside sandbox: " + untrusted_path.string());
	}

	std::filesystem::path sanitize_relative_path(const std::filesystem::path& relative_messy_path)
	{
		return relative_messy_path.lexically_normal().make_preferred();
	}

	std::filesystem::path sanitize_path(const std::filesystem::path& messy_path) {
		std::filesystem::path p = sanitize_relative_path(messy_path);
		if (!p.is_absolute()) {
			return std::filesystem::absolute(p);
		}

		return p;
	}

	std::string filename_encode(const std::string& value) {
		std::ostringstream escaped;
		escaped.fill('0');
		escaped << std::hex;

		for (const auto c : value) {
			[[likely]]
			if (!filename_encode_bad_char(escaped, c, bad_chars)) {
				escaped << c;
			}
		}

		return escaped.str();
	}

	std::string filename_encode_with_slashes(const std::string& value) {
		std::ostringstream escaped;
		escaped.fill('0');
		escaped << std::hex;

		for (const auto c : value) {
			[[likely]]
			if (!filename_encode_bad_char(escaped, c, bad_chars_with_slashes)) {
				escaped << c;
			}
		}

		return escaped.str();
	}

	std::string filename_decode(const std::string& value) {
		std::ostringstream unescaped;
		unescaped.fill('0');

		for (size_t i = 0; i < value.size(); ++i) {
			[[likely]]
			if (value[i] != escape_character) {
				unescaped << value[i];
				continue;
			}

			std::string_view v = std::string_view(value).substr(i + 1, 2);
			char c = (char)filename_decode_piece_unchecked(v);
			unescaped << c;
			i += 2;
		}

		return unescaped.str();
	}

	std::filesystem::path filename_encode(const std::filesystem::path& value) {
		return filename_encode(value.string());
	}

	std::filesystem::path filename_decode(const std::filesystem::path& value) {
		return filename_decode(value.string());
	}

	std::vector<std::filesystem::path> recurse_list_files(const std::filesystem::path& search_root_path) {
		return generic_list_files<std::filesystem::recursive_directory_iterator>(search_root_path);
	}

	std::vector<std::filesystem::path> list_files(const std::filesystem::path& search_root_path) {
		return generic_list_files<std::filesystem::directory_iterator>(search_root_path);
	}
}
