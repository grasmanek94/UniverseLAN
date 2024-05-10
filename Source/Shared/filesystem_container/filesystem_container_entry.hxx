#pragma once

#include "filesystem_container_metadata.hxx"

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

namespace filesystem_container {
	class filesystem_container;
	class filesystem_entry;

	using fs_entry_ptr = std::shared_ptr<filesystem_entry>;

	class filesystem_entry : public std::enable_shared_from_this<filesystem_entry> {
	private:
		filesystem_container* parent_fc;

		std::filesystem::path path;
		std::filesystem::path abs_file_path;
		std::filesystem::path abs_metadata_path;

		file_entry_metadata metadata;

		bool notify_copy_start(const filesystem_entry& source);
		void notify_copy_done(const filesystem_entry& source, bool copied_file, bool copied_metadata);

	public:
		filesystem_entry(filesystem_container* parent_file_container, std::filesystem::path path);
		filesystem_entry(filesystem_container* parent_file_container, std::filesystem::path path, uint64_t share_id);
		~filesystem_entry();

		std::filesystem::path get_path() const;
		std::filesystem::path get_abs_path() const;
		std::filesystem::path get_abs_metadata_path() const;

		bool exists();
		bool unlink();

		[[deprecated("This function is unsecure and does not copy the linked metadata, use `bool copy_to(filesystem_entry& other_entry) const` instead")]]
		bool copy_to(const std::filesystem::path& other_file_path) const;
		[[deprecated("This function is unsecure and does not copy the linked file, use `bool copy_to(filesystem_entry& other_entry) const` instead")]]
		bool copy_metadata_to(const std::filesystem::path& other_file_path) const;
	
		bool copy_to(filesystem_entry& other_entry) const;
		bool copy_to(fs_entry_ptr other_entry) const;

		uint64_t get_timestamp() const;
		size_t get_size() const;

		std::fstream open(std::ios::openmode mode) const;
		std::vector<char> read();
		size_t read(char* data, size_t data_length, size_t offset = 0);
		bool write(const char* data, size_t data_length);
		bool write(const std::vector<char>& data);

		// Sharing functions
		uint64_t get_share_id() const;
		void set_share_id(uint64_t share_id);

		// "Cloud" functions
		uint64_t get_timestamp_metadata() const;
		void set_timestamp_metadata(int64_t timestamp);

		void set_metadata(const std::string& key, const std::string& value);
		std::string get_metadata(const std::string& key, const std::string& default_value = "") const;
		std::vector<std::string> get_metadata_keys() const;
		std::vector<std::string> get_metadata_values() const;
		file_entry_metadata_container_t get_metadata() const;

		bool save_metadata();

		void create_empty_file_if_not_exist();
	};
}
