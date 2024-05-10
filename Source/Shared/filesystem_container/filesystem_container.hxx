#pragma once

#include "filesystem_container_entry.hxx"

#include <atomic>
#include <cstdint>
#include <filesystem>
#include <map>
#include <memory>
#include <mutex>
#include <vector>

namespace filesystem_container {
	using fs_container_ptr = std::shared_ptr<filesystem_container>;

	class filesystem_container {
	public:
		friend class filesystem_entry;

		using mutex_t = std::recursive_mutex;
		using lock_t = std::scoped_lock<mutex_t>;

	private:
		std::filesystem::path rel_basepath;
		std::filesystem::path basepath;
		std::filesystem::path basepath_data;
		std::filesystem::path basepath_metadata;

		mutable mutex_t mtx_filename_to_entry;
		mutable mutex_t mtx_shareid_to_entry;

		std::map<std::filesystem::path, fs_entry_ptr> filename_to_entry;
		std::map<uint64_t, fs_entry_ptr> shareid_to_entry;

		mutable mutex_t mtx_fs_entry_index;
		std::atomic<bool> fs_entry_index_dirty;
		std::vector<fs_entry_ptr> fs_entry_index;

		mutable mutex_t mtx_subcontainers;
		std::map<std::string, fs_container_ptr> named_subcontainers;
		fs_container_ptr nameless_subcontainer;

		std::filesystem::path get_path(const std::filesystem::path& root, const std::filesystem::path& file_name) const;
		std::filesystem::path get_path(const std::filesystem::path& file_name) const;
		std::filesystem::path get_path_metadata(const std::filesystem::path& root, const std::filesystem::path& file_name) const;
		std::filesystem::path get_path_metadata(const std::filesystem::path& file_name) const;

		void notify_file_copied(fs_entry_ptr entry);
		bool remove(fs_entry_ptr entry, bool unlink_performed);
		bool exists(fs_entry_ptr entry) const;

		bool is_index_out_of_sync();
		void refresh_index();
		void refresh_index_if_out_of_sync();

	public:
		filesystem_container(const std::filesystem::path& container_basepath);
		virtual ~filesystem_container();

		fs_entry_ptr get(const std::filesystem::path& root, const std::filesystem::path& file_name) const;
		fs_entry_ptr get(const std::filesystem::path& file_name) const;
		fs_entry_ptr get(uint64_t share_id) const;

		fs_entry_ptr get_or_create(const std::filesystem::path& root, const std::filesystem::path& file_name);
		fs_entry_ptr get_or_create(const std::filesystem::path& file_name);

		fs_entry_ptr create_shared(const std::filesystem::path& root, const std::filesystem::path& file_name, uint64_t share_id);
		fs_entry_ptr create_shared(const std::filesystem::path& file_name, uint64_t share_id);

		bool exists(const std::filesystem::path& root, const std::filesystem::path& file_name) const;
		bool exists(const std::filesystem::path& file_name) const;
		bool exists(uint64_t share_id) const;

		bool remove(const std::filesystem::path& root, const std::filesystem::path& file_name);
		bool remove(const std::filesystem::path& file_name);
		bool remove(uint64_t share_id);

		virtual uint64_t get_total_disk_space() const;
		virtual uint64_t get_available_disk_space() const;
		virtual uint64_t get_used_disk_space() const;

		size_t get_file_count() const;

		uint64_t get_shared_id_by_index(size_t index) const;
		std::filesystem::path get_file_name_by_index(size_t index) const;
		fs_entry_ptr get_file_by_index(size_t index) const;
		std::vector<fs_entry_ptr> get_file_list() const;

		std::filesystem::path get_basepath() const;

		fs_container_ptr get_subcontainer(const char* name);
	};
}
