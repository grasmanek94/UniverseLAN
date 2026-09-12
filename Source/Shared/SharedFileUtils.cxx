#include "SharedFileUtils.hxx"

#include "filesystem_container/filesystem_container.hxx"

#include <filesystem>
#include <limits>

namespace universelan {
	using fs_container = filesystem_container::filesystem_container;

	namespace {
		const std::filesystem::path ROOT_LOCAL = "Local";
		const std::filesystem::path ROOT_CLOUD = "Cloud";
		const std::filesystem::path ROOT_SHARED = "Shared";
		const std::filesystem::path ROOT_AVATARS = "Avatars";
	}

	SharedFileUtils::SharedFileUtils(const SharedFileUtils& other) :
		storage{ other.storage },
		shared{ other.shared },
		cloud{ other.cloud },
		avatars{ other.avatars }
	{}

	SharedFileUtils::SharedFileUtils(const std::filesystem::path& basepath) :
		storage{ std::make_shared<fs_container>(std::filesystem::current_path() / basepath / ROOT_LOCAL) },
		shared{ std::make_shared<fs_container>(std::filesystem::current_path() / basepath / ROOT_SHARED) },
		cloud{ std::make_shared<fs_container>(std::filesystem::current_path() / basepath / ROOT_CLOUD) },
		avatars{ std::make_shared<fs_container>(std::filesystem::current_path() / basepath / ROOT_AVATARS) }
	{ }

	galaxy::api::SharedFileID SharedFileUtils::GetSharedFileID(const fs_container_ptr& container, const char* const file_name) const
	{
		if ((container == nullptr) || (file_name == nullptr) || (file_name[0] == '\0')) {
			return 0;
		}

		auto result = container->get(file_name);
		if (!result) {
			return 0;
		}

		return result->get_share_id();
	}

	std::filesystem::path SharedFileUtils::GetSharedFileName(const fs_container_ptr& container, const galaxy::api::SharedFileID id) const
	{
		if ((container == nullptr) || (id == 0)) {
			return {};
		}

		auto result = container->get(id);
		if (!result) {
			return {};
		}

		return result->get_path();
	}

	std::fstream SharedFileUtils::Open(const fs_container_ptr& container, const galaxy::api::SharedFileID id, const std::ios::openmode mode) const
	{
		if ((container == nullptr) || (id == 0)) {
			return std::fstream{};
		}

		auto result = container->get(id);
		if (!result) {
			return std::fstream{};
		}

		return result->open(mode);
	}

	std::fstream SharedFileUtils::Open(const fs_container_ptr& container, const char* const file_name, const std::ios::openmode mode) const
	{
		if ((container == nullptr) || (file_name == nullptr) || (file_name[0] == '\0')) {
			return std::fstream{};
		}

		auto result = container->get(file_name);
		if (!result) {
			return std::fstream{};
		}

		return result->open(mode);
	}

	bool SharedFileUtils::Exists(const fs_container_ptr& container, const galaxy::api::SharedFileID id) const
	{
		if ((container == nullptr) || (id == 0)) {
			return false;
		}

		auto result = container->get(id);
		if (!result) {
			return false;
		}

		return result->exists();
	}

	bool SharedFileUtils::Exists(const fs_container_ptr& container, const char* const file_name) const
	{
		if ((container == nullptr) || (file_name == nullptr) || (file_name[0] == '\0')) {
			return false;
		}

		auto result = container->get(file_name);
		if (!result) {
			return false;
		}

		return result->exists();
	}

	bool SharedFileUtils::Remove(const fs_container_ptr& container, const galaxy::api::SharedFileID id) const
	{
		if ((container == nullptr) || (id == 0)) {
			return false;
		}

		auto result = container->get(id);
		if (!result) {
			return false;
		}

		return result->unlink();
	}

	bool SharedFileUtils::Remove(const fs_container_ptr& container, const char* const file_name) const
	{
		if ((container == nullptr) || (file_name == nullptr) || (file_name[0] == '\0')) {
			return false;
		}

		auto result = container->get(file_name);
		if (!result) {
			return false;
		}

		return result->unlink();
	}

	bool SharedFileUtils::Write(const fs_container_ptr& container, const galaxy::api::SharedFileID id, const char* const data, const size_t data_length) const
	{
		if ((container == nullptr) || (id == 0) || (data == nullptr)) {
			return false;
		}

		auto result = container->get(id);
		if (!result) {
			return false;
		}

		return result->write(data, data_length);
	}

	bool SharedFileUtils::Write(const fs_container_ptr& container, const char* const file_name, const char* const data, const size_t data_length) const
	{
		if ((container == nullptr) || (file_name == nullptr) || (file_name[0] == '\0') || (data == nullptr)) {
			return false;
		}

		auto result = container->get_or_create(file_name);
		if (!result) {
			return false;
		}

		return result->write(data, data_length);
	}

	std::vector<char> SharedFileUtils::Read(const fs_container_ptr& container, const galaxy::api::SharedFileID id) const
	{
		if ((container == nullptr) || (id == 0)) {
			return {};
		}

		auto result = container->get(id);
		if (!result) {
			return {};
		}

		return result->read();
	}

	std::vector<char> SharedFileUtils::Read(const fs_container_ptr& container, const char* const file_name) const
	{
		if ((container == nullptr) || (file_name == nullptr) || (file_name[0] == '\0')) {
			return {};
		}

		auto result = container->get(file_name);
		if (!result) {
			return {};
		}

		return result->read();
	}

	uint32_t SharedFileUtils::Read(const fs_container_ptr& container, const char* const file_name, char* const data, const size_t data_length, const size_t offset) const
	{
		if ((container == nullptr) || (file_name == nullptr) || (file_name[0] == '\0') || (data == nullptr) || (data_length == 0)) {
			return 0;
		}

		auto result = container->get(file_name);
		if (!result) {
			return 0;
		}

		return (uint32_t)result->read(data, data_length, offset);
	}

	uint32_t SharedFileUtils::Read(const fs_container_ptr& container, const galaxy::api::SharedFileID id, char* const data, const size_t data_length, const size_t offset) const
	{
		if ((container == nullptr) || (id == 0) || (data == nullptr) || (data_length == 0)) {
			return 0;
		}

		auto result = container->get(id);
		if (!result) {
			return 0;
		}

		return (uint32_t)result->read(data, data_length, offset);
	}

	uint32_t SharedFileUtils::GetSize(const fs_container_ptr& container, const char* const file_name) const
	{
		if ((container == nullptr) || (file_name == nullptr) || (file_name[0] == '\0')) {
			return 0;
		}

		auto result = container->get(file_name);
		if (!result) {
			return 0;
		}

		return (uint32_t)std::min(result->get_size(), (size_t)std::numeric_limits<uint32_t>::max());
	}

	uint32_t SharedFileUtils::GetSize(const fs_container_ptr& container, const galaxy::api::SharedFileID id) const
	{
		if ((container == nullptr) || (id == 0)) {
			return 0;
		}

		auto result = container->get(id);
		if (!result) {
			return 0;
		}

		return (uint32_t)std::min(result->get_size(), (size_t)std::numeric_limits<uint32_t>::max());
	}

	uint32_t SharedFileUtils::GetTimestamp(const fs_container_ptr& container, const char* const file_name) const
	{
		if ((container == nullptr) || (file_name == nullptr) || (file_name[0] == '\0')) {
			return 0;
		}

		auto result = container->get(file_name);
		if (!result) {
			return 0;
		}

		return (uint32_t)std::min(result->get_timestamp(), (size_t)std::numeric_limits<uint32_t>::max());
	}

	uint32_t SharedFileUtils::GetTimestamp(const fs_container_ptr& container, const galaxy::api::SharedFileID id) const
	{
		if ((container == nullptr) || (id == 0)) {
			return 0;
		}

		auto result = container->get(id);
		if (!result) {
			return 0;
		}

		return (uint32_t)std::min(result->get_timestamp(), (size_t)std::numeric_limits<uint32_t>::max());
	}

	uint32_t SharedFileUtils::GetFileCount(const fs_container_ptr& container) const
	{
		if (container == nullptr) {
			return 0;
		}

		return (uint32_t)std::min(container->get_file_count(), (size_t)std::numeric_limits<uint32_t>::max());
	}


	galaxy::api::SharedFileID SharedFileUtils::GetSharedIDByIndex(const fs_container_ptr& container, const uint32_t index) const
	{
		if (container == nullptr) {
			return 0;
		}

		return container->get_shared_id_by_index(index);
	}

	std::filesystem::path SharedFileUtils::GetFileNameByIndex(const fs_container_ptr& container, const uint32_t index) const
	{
		if (container == nullptr) {
			return {};
		}

		return container->get_file_name_by_index(index);
	}

	bool SharedFileUtils::CopyFromLocalToShared(const char* const file_name, const galaxy::api::SharedFileID id) const
	{
		if ((file_name == nullptr) || (file_name[0] == '\0') || (id == 0)) {
			return 0;
		}

		auto shared_file = shared->create_shared(file_name, id);
		if (!shared_file) {
			return false;
		}

		auto local_file = storage->get(file_name);
		if (!local_file) {
			return false;
		}

		return local_file->copy_to(shared_file);
	}

	bool SharedFileUtils::CopyFromSharedToLocal(const char* const file_name) const
	{
		if ((file_name == nullptr) || (file_name[0] == '\0')) {
			return 0;
		}

		auto shared_file = shared->get(file_name);
		if (!shared_file) {
			return false;
		}

		auto local_file = storage->get_or_create(file_name);
		if (!local_file) {
			return false;
		}

		return shared_file->copy_to(local_file);
	}

	uint32_t SharedFileUtils::GetTotalDiskSpace(const fs_container_ptr& container) const
	{
		if (container == nullptr) {
			return 0;
		}

		return (uint32_t)std::min(container->get_total_disk_space(), (size_t)std::numeric_limits<uint32_t>::max());
	}

	uint32_t SharedFileUtils::GetAvailableDiskSpace(const fs_container_ptr& container) const
	{
		if (container == nullptr) {
			return 0;
		}

		return (uint32_t)std::min(container->get_available_disk_space(), (size_t)std::numeric_limits<uint32_t>::max());
	}

	uint32_t SharedFileUtils::GetUsedDiskSpace(const fs_container_ptr& container) const
	{
		if (container == nullptr) {
			return 0;
		}

		return (uint32_t)std::min(container->get_used_disk_space(), (size_t)std::numeric_limits<uint32_t>::max());
	}

	std::vector<filesystem_container::fs_entry_ptr> SharedFileUtils::GetDirectoryFileList(const fs_container_ptr& container) const
	{
		if (container == nullptr) {
			return {};
		}

		return container->get_file_list();
	}
}
