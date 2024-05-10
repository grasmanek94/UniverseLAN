#include "filesystem_container.hxx"
#include "filesystem_container_utils.hxx"

#include <cassert>
#include <filesystem>
#include <fstream>
#include <limits>

namespace filesystem_container {
	namespace {
		const std::filesystem::path files_modifier = "files";
		const std::filesystem::path metadata_modifier = "metadata";
	}

	filesystem_container::filesystem_container(const std::filesystem::path& container_basepath) :
		rel_basepath{ sanitize_relative_path(container_basepath) },
		basepath{ sanitize_path(container_basepath) },
		basepath_data{ sanitize_path(container_basepath) / files_modifier },
		basepath_metadata{ sanitize_path(container_basepath) / metadata_modifier },
		mtx_filename_to_entry{}, mtx_shareid_to_entry{},
		filename_to_entry{}, shareid_to_entry{},
		mtx_fs_entry_index{}, fs_entry_index_dirty{ true }, fs_entry_index{},
		mtx_subcontainers{}, named_subcontainers{}, nameless_subcontainer{ nullptr }
	{
		std::error_code ec;
		std::filesystem::create_directories(basepath_data, ec);
		std::filesystem::create_directories(basepath_metadata, ec);

		auto files = recurse_list_files(basepath_data);
		for (auto& file : files) {
			auto decoded_filename = filename_decode(file);
			auto full_file_path = get_path(decoded_filename);
			if (std::filesystem::is_regular_file(full_file_path)) {
				auto entry_ptr = std::make_shared<filesystem_entry>(this, decoded_filename);

				filename_to_entry.emplace(entry_ptr->get_path(), entry_ptr);
				if (entry_ptr->get_share_id()) {
					shareid_to_entry.emplace(entry_ptr->get_share_id(), entry_ptr);
				}
			}
		}

		refresh_index();
	}

	filesystem_container::~filesystem_container() {

	}

	fs_entry_ptr filesystem_container::get(const std::filesystem::path& root, const std::filesystem::path& file_name) const
	{
		return get(root / file_name);
	}

	fs_entry_ptr filesystem_container::get(uint64_t share_id) const
	{
		fs_entry_ptr ptr = nullptr;
		{
			lock_t lock{ mtx_shareid_to_entry };

			auto entry = shareid_to_entry.find(share_id);
			if (entry == shareid_to_entry.end()) {
				return nullptr;
			}

			ptr = entry->second;
		}

		if (!ptr->exists()) {
			ptr->unlink();
			return nullptr;
		}

		return ptr;
	}

	fs_entry_ptr filesystem_container::get(const std::filesystem::path& file_name) const
	{
		auto p = sanitize_relative_path(file_name);
		auto abs = get_path(p);

		bool exists = std::filesystem::exists(abs);
		bool found = false;
		fs_entry_ptr ptr = nullptr;

		{
			lock_t lock{ mtx_filename_to_entry };
			auto entry = filename_to_entry.find(p);
			if (entry == filename_to_entry.end()) {
				assert(exists == found);
				return nullptr;
			}

			ptr = entry->second;
		}

		if (!exists) {
			ptr->unlink();
			return nullptr;
		}

		return ptr;
	}


	fs_entry_ptr filesystem_container::get_or_create(const std::filesystem::path& root, const std::filesystem::path& file_name)
	{
		return get_or_create(root / file_name);
	}

	fs_entry_ptr filesystem_container::get_or_create(const std::filesystem::path& file_name)
	{
		std::unique_lock<mutex_t> lk1(mtx_fs_entry_index, std::defer_lock);
		std::unique_lock<mutex_t> lk2(mtx_filename_to_entry, std::defer_lock);

		std::lock(lk1, lk2);

		auto p = sanitize_relative_path(file_name);


		auto found_filename_entry = filename_to_entry.find(p);
		if (found_filename_entry != filename_to_entry.end()) {
			found_filename_entry->second->create_empty_file_if_not_exist();
			return found_filename_entry->second;
		}

		fs_entry_ptr entry = std::make_shared<filesystem_entry>(this, p);
		entry->create_empty_file_if_not_exist();
		filename_to_entry.emplace(p, entry);
		fs_entry_index.push_back(entry);

		return entry;
	}

	fs_entry_ptr filesystem_container::create_shared(const std::filesystem::path& root, const std::filesystem::path& file_name, uint64_t share_id)
	{
		return create_shared(root / file_name, share_id);
	}

	fs_entry_ptr filesystem_container::create_shared(const std::filesystem::path& file_name, uint64_t share_id)
	{
		if (share_id == 0) {
			return nullptr;
		}

		std::unique_lock<mutex_t> lk1(mtx_fs_entry_index, std::defer_lock);
		std::unique_lock<mutex_t> lk2(mtx_filename_to_entry, std::defer_lock);
		std::unique_lock<mutex_t> lk3(mtx_shareid_to_entry, std::defer_lock);

		std::lock(lk1, lk2, lk3);

		auto p = sanitize_relative_path(file_name);

		fs_entry_ptr entry = nullptr;

		auto found_shareid_iter = shareid_to_entry.find(share_id);
		if (found_shareid_iter != shareid_to_entry.end()) {
			entry = found_shareid_iter->second;

			if (p != entry->get_path()) {
				assert(p != entry->get_path());

				// shared id already taken and has a different filename
				return nullptr;
			}

			return entry;
		}

		auto found_filename_entry = filename_to_entry.find(p);
		if (found_filename_entry != filename_to_entry.end()) {
			entry = found_filename_entry->second;

			if (entry->get_share_id() != 0) {
				assert(entry->get_share_id() == 0);

				// shared id already taken and has a different filename
				return nullptr;
			}

			// "Share" the current entry
			entry->set_share_id(share_id);
			entry->save_metadata();
			return entry;
		}

		entry = std::make_shared<filesystem_entry>(this, p, share_id);
		entry->create_empty_file_if_not_exist();
		shareid_to_entry.emplace(share_id, entry);
		filename_to_entry.emplace(p, entry);
		fs_entry_index.push_back(entry);
		entry->save_metadata();

		return entry;
	}

	bool filesystem_container::exists(const std::filesystem::path& root, const std::filesystem::path& file_name) const
	{
		return exists(get(root, file_name));
	}

	bool filesystem_container::exists(const std::filesystem::path& file_name) const
	{
		return exists(get(file_name));
	}

	bool filesystem_container::exists(uint64_t share_id) const
	{
		return exists(get(share_id));
	}

	bool filesystem_container::remove(const std::filesystem::path& root, const std::filesystem::path& file_name)
	{
		return remove(get(root, file_name), false);
	}

	bool filesystem_container::remove(const std::filesystem::path& file_name)
	{
		return remove(get(file_name), false);
	}

	bool filesystem_container::remove(uint64_t share_id)
	{
		return remove(get(share_id), false);
	}

	std::filesystem::path filesystem_container::get_path(const std::filesystem::path& root, const std::filesystem::path& file_name) const
	{
		return sandbox_secure_path_concat(basepath_data, filename_encode(root), filename_encode(file_name));
	}

	std::filesystem::path filesystem_container::get_path(const std::filesystem::path& file_name) const
	{
		return sandbox_secure_path_concat(basepath_data, filename_encode(file_name));
	}

	std::filesystem::path filesystem_container::get_path_metadata(const std::filesystem::path& root, const std::filesystem::path& file_name) const
	{
		return sandbox_secure_path_concat(basepath_metadata, filename_encode(root), filename_encode(file_name).concat(".metadata"));
	}

	std::filesystem::path filesystem_container::get_path_metadata(const std::filesystem::path& file_name) const
	{
		return sandbox_secure_path_concat(basepath_metadata, filename_encode(file_name).concat(".metadata"));
	}

	void filesystem_container::notify_file_copied(fs_entry_ptr entry)
	{
		if (entry == nullptr) {
			return;
		}

		{
			lock_t lock{ mtx_filename_to_entry };
			if (filename_to_entry.find(entry->get_path()) != filename_to_entry.end()) {
				return;
			}
		}

		std::unique_lock<mutex_t> lk1(mtx_fs_entry_index, std::defer_lock);
		std::unique_lock<mutex_t> lk2(mtx_filename_to_entry, std::defer_lock);
		std::unique_lock<mutex_t> lk3(mtx_shareid_to_entry, std::defer_lock);

		if (entry->get_share_id()) {
			std::lock(lk1, lk2, lk3);
		}
		else {
			std::lock(lk1, lk2);
		}

		filename_to_entry.emplace(entry->get_path(), entry);
		fs_entry_index.push_back(entry);

		if (entry->get_share_id()) {
			shareid_to_entry.emplace(entry->get_share_id(), entry);
		}
	}

	bool filesystem_container::remove(fs_entry_ptr entry, bool unlink_performed)
	{
		if (entry == nullptr) {
			return false;
		}

		if (!unlink_performed) {
			entry->unlink();
		}

		std::unique_lock<mutex_t> lk1(mtx_fs_entry_index, std::defer_lock);
		std::unique_lock<mutex_t> lk2(mtx_filename_to_entry, std::defer_lock);
		std::unique_lock<mutex_t> lk3(mtx_shareid_to_entry, std::defer_lock);

		if (entry->get_share_id()) {
			std::lock(lk1, lk2, lk3);
		}
		else {
			std::lock(lk1, lk2);
		}

		size_t erased_elements = filename_to_entry.erase(entry->get_path());
		if (entry->get_share_id()) {
			erased_elements += shareid_to_entry.erase(entry->get_share_id());
		}

		if (erased_elements) {
			for (size_t i = 0; i < fs_entry_index.size(); ++i) {
				if (fs_entry_index[i] == entry) {
					fs_entry_index.erase(fs_entry_index.begin() + i);
					break;
				}
			}
		}

		return erased_elements > 0;
	}

	bool filesystem_container::exists(fs_entry_ptr entry) const
	{
		if (!entry) {
			return false;
		}
		return entry->exists();
	}

	uint64_t filesystem_container::get_total_disk_space() const
	{
		std::error_code ec;
		return std::filesystem::space(basepath, ec).capacity;
	}

	uint64_t filesystem_container::get_available_disk_space() const
	{
		std::error_code ec;
		return std::filesystem::space(basepath, ec).available;
	}

	uint64_t filesystem_container::get_used_disk_space() const
	{
		std::error_code ec;
		const std::filesystem::space_info si = std::filesystem::space(basepath, ec);
		return si.capacity - si.available;
	}

	size_t filesystem_container::get_file_count() const
	{
		lock_t lock{ mtx_filename_to_entry };
		return filename_to_entry.size();
	}

	bool filesystem_container::is_index_out_of_sync()
	{
		return fs_entry_index_dirty;
	}

	void filesystem_container::refresh_index()
	{
		std::unique_lock<mutex_t> lk1(mtx_fs_entry_index, std::defer_lock);
		std::unique_lock<mutex_t> lk2(mtx_filename_to_entry, std::defer_lock);
		std::lock(lk1, lk2);

		fs_entry_index.clear();
		for (auto& entry : filename_to_entry) {
			fs_entry_index.push_back(entry.second);
		}

		fs_entry_index_dirty = false;
	}

	void filesystem_container::refresh_index_if_out_of_sync()
	{
		if (is_index_out_of_sync()) {
			refresh_index();
		}
	}

	uint64_t filesystem_container::get_shared_id_by_index(size_t index) const
	{
		lock_t lock{ mtx_fs_entry_index };

		if (index >= fs_entry_index.size()) {
			return 0;
		}

		return fs_entry_index[index]->get_share_id();
	}

	std::filesystem::path filesystem_container::get_file_name_by_index(size_t index) const
	{
		lock_t lock{ mtx_fs_entry_index };

		if (index >= fs_entry_index.size()) {
			return std::filesystem::path();
		}

		return fs_entry_index[index]->get_path();
	}

	fs_entry_ptr filesystem_container::get_file_by_index(size_t index) const
	{
		lock_t lock{ mtx_fs_entry_index };

		if (index >= fs_entry_index.size()) {
			return nullptr;
		}

		return fs_entry_index[index];
	}

	std::vector<fs_entry_ptr> filesystem_container::get_file_list() const
	{
		lock_t lock{ mtx_fs_entry_index };
		return fs_entry_index;
	}

	std::filesystem::path filesystem_container::get_basepath() const
	{
		return rel_basepath;
	}

	fs_container_ptr filesystem_container::get_subcontainer(const char* name)
	{
		const std::string no_name_containers_name = "nameless_container";
		const std::string named_containers_name = "named_containers";

		lock_t lock{ mtx_subcontainers };

		if (name == nullptr || name[0] == '\0') {
			if (nameless_subcontainer == nullptr) {
				nameless_subcontainer = std::make_shared<filesystem_container>(basepath / no_name_containers_name);
				nameless_subcontainer->rel_basepath = rel_basepath / no_name_containers_name;
			}

			return nameless_subcontainer;
		}

		std::string container{ filename_encode_with_slashes(std::string(name))};

		auto entry = named_subcontainers.find(container);
		if (entry != named_subcontainers.end()) {
			return entry->second;
		}

		named_subcontainers.emplace(container, std::make_shared<filesystem_container>(basepath / named_containers_name / container));
		nameless_subcontainer->rel_basepath = rel_basepath / named_containers_name / container;

		return nullptr;
	}
}
