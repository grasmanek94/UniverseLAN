#include "SharedFileUtils.hxx"

#include <GalaxyVersionedTypes.hxx>
#include <GalaxyApi.h>

#include <exception>
#include <filesystem>
#include <fstream>
#include <iterator>

namespace universelan {
	using galaxy::api::SharedFileID;

	namespace {
		std::size_t number_of_files_in_directory(std::filesystem::path path) {
			using std::filesystem::directory_iterator;
			return std::distance(directory_iterator(path), directory_iterator{});
		}
	}

	const std::filesystem::path SharedFileUtils::ROOT_LOCAL = "Local";
	const std::filesystem::path SharedFileUtils::ROOT_CLOUD = "Cloud/files";
	const std::filesystem::path SharedFileUtils::ROOT_CLOUD_METADATA = "Cloud/metadata";
	const std::filesystem::path SharedFileUtils::ROOT_SHARED = "Shared/files/";
	const std::filesystem::path SharedFileUtils::ROOT_AVATARS = "Avatars";
	const std::filesystem::path SharedFileUtils::ROOT_LOGGING = "Logging";
	const std::filesystem::path SharedFileUtils::ROOT_TELEMETRY = "Telemetry";
	const std::filesystem::path SharedFileUtils::ROOT_FILENAME_TO_ID = "Shared/mapper/__filename_to_id__";
	const std::filesystem::path SharedFileUtils::ROOT_ID_TO_FILENAME = "Shared/mapper/__id_to_filename__";

	SharedFileUtils::SharedFileUtils(const std::filesystem::path& basepath) : basepath{ std::filesystem::current_path() / basepath } { }

	bool SharedFileUtils::InitSharedFileStorage(const std::filesystem::path& filename, SharedFileID id) const {
		std::error_code ec;

		const std::filesystem::path str_shared_file_id{ std::to_string(id) };

		std::filesystem::path filename_to_id_basepath{ basepath / ROOT_FILENAME_TO_ID };
		std::filesystem::path id_to_filename_basepath{ basepath / ROOT_ID_TO_FILENAME };
		std::filesystem::path sharedfile_storage_basepath{ basepath / ROOT_SHARED };

		if (inside_basepath(sharedfile_storage_basepath, filename) && inside_basepath(filename_to_id_basepath, filename)) {
			std::filesystem::path id2filename_path = id_to_filename_basepath / str_shared_file_id;
			std::filesystem::path filename2id_path = filename_to_id_basepath / filename;
			std::filesystem::path storage_path = sharedfile_storage_basepath / filename;

			std::filesystem::create_directories(std::filesystem::path(filename2id_path).remove_filename(), ec);
			std::filesystem::create_directories(std::filesystem::path(storage_path).remove_filename(), ec);

			std::fstream{ (id2filename_path).string(), std::ios::trunc } << filename;
			std::fstream{ (filename2id_path).string(), std::ios::trunc } << str_shared_file_id;

			return true;
		}

		throw std::runtime_error("Security Exception: Path traversal outside sandbox: " + filename.string());
	}

	bool SharedFileUtils::UnlinkSharedFileStorage(const std::filesystem::path& filename, SharedFileID id) const {
		std::error_code ec;

		const std::filesystem::path str_shared_file_id{ std::to_string(id) };

		std::filesystem::path filename_to_id_basepath{ basepath / ROOT_FILENAME_TO_ID };
		std::filesystem::path id_to_filename_basepath{ basepath / ROOT_ID_TO_FILENAME };
		std::filesystem::path sharedfile_storage_basepath{ basepath / ROOT_SHARED };

		if (inside_basepath(sharedfile_storage_basepath, filename) && inside_basepath(filename_to_id_basepath, filename)) {
			std::filesystem::path id2filename_path = id_to_filename_basepath / str_shared_file_id;
			std::filesystem::path filename2id_path = filename_to_id_basepath / filename;
			std::filesystem::path storage_path = sharedfile_storage_basepath / filename;

			std::filesystem::remove(id2filename_path);
			std::filesystem::remove(filename2id_path);

			return RemoveShared(filename);
		}

		throw std::runtime_error("Security Exception: Path traversal outside sandbox: " + filename.string());
	}

	SharedFileID SharedFileUtils::GetSharedFileID(const std::filesystem::path& filename) const {
		std::error_code ec;

		std::filesystem::path filename_to_id_basepath{ basepath / ROOT_FILENAME_TO_ID };
		std::filesystem::path sharedfile_storage_basepath{ basepath / ROOT_SHARED };

		if (inside_basepath(sharedfile_storage_basepath, filename) && inside_basepath(filename_to_id_basepath, filename)) {
			std::filesystem::path filename2id_path = filename_to_id_basepath / filename;

			std::filesystem::path str_shared_file_id;

			std::fstream{ (filename2id_path).string(), std::ios::in } >> str_shared_file_id;

			return std::stoull(str_shared_file_id);
		}

		throw std::runtime_error("Security Exception: Path traversal outside sandbox: " + filename.string());
	}

	std::filesystem::path SharedFileUtils::GetSharedFileName(SharedFileID id) const {
		std::error_code ec;

		const std::filesystem::path str_shared_file_id{ std::to_string(id) };

		std::filesystem::path id_to_filename_basepath{ basepath / ROOT_ID_TO_FILENAME };
		std::filesystem::path id2filename_path = id_to_filename_basepath / str_shared_file_id;

		std::filesystem::path filename;
		std::fstream{ (id2filename_path).string(), std::ios::in } >> filename;

		return filename;
	}

	std::fstream SharedFileUtils::Open(const std::filesystem::path& root, const std::filesystem::path& file_name, std::ios::openmode mode) const {
		std::error_code ec;
		auto path = GetPath(root, file_name);

		std::filesystem::create_directories(std::filesystem::path(path).remove_filename(), ec);

		return std::fstream{ path.string(), mode };
	}

	std::filesystem::path SharedFileUtils::GetPath(const std::filesystem::path& root, const std::filesystem::path& file_name) const {
		std::filesystem::path combined(basepath / root);

		return sandbox_secure_path_concat(combined, file_name);
	}

	std::filesystem::path SharedFileUtils::GetPath(const std::filesystem::path& root, const std::filesystem::path& container, const std::filesystem::path& file_name) const {
		std::filesystem::path combined(basepath / root);
		std::filesystem::path contained_file_name(std::filesystem::path(container) / file_name);

		return sandbox_secure_path_concat(combined, contained_file_name);
	}

	bool SharedFileUtils::Exists(const std::filesystem::path& root, const std::filesystem::path& file_name) const {
		return std::filesystem::exists(GetPath(root, file_name));
	}

	bool SharedFileUtils::Remove(const std::filesystem::path& root, const std::filesystem::path& file_name) const {
		return std::filesystem::remove(GetPath(root, file_name));
	}

	bool SharedFileUtils::Write(const std::filesystem::path& root, const std::filesystem::path& file_name, const char* data, size_t data_length) const {
		auto file = Open(root, file_name, std::ios::out | std::ios::trunc | std::ios::binary);
		if (!file) {
			return false;
		}

		file.write(data, data_length);
		return true;
	}

	uint32_t SharedFileUtils::Read(const std::filesystem::path& root, const std::filesystem::path& file_name, char* data, size_t data_length, size_t offset) const {
		auto file = Open(root, file_name, std::ios::in | std::ios::binary);
		if (!file) {
			return 0;
		}

		file.seekg(offset);
		file.read(data, data_length);
		return (uint32_t)file.gcount();
	}

	std::vector<char> SharedFileUtils::Read(const std::filesystem::path& root, const std::filesystem::path& file_name) const {
		auto file = Open(root, file_name, std::ios::in | std::ios::binary);
		if (!file) {
			return {};
		}

		// Stop eating new lines in binary mode!!!
		file.unsetf(std::ios::skipws);

		// get its size:
		std::streampos fileSize;

		file.seekg(0, std::ios::end);
		fileSize = file.tellg();
		file.seekg(0, std::ios::beg);

		// reserve capacity
		std::vector<char> vec;
		vec.reserve((size_t)fileSize);

		// read the data:
		vec.insert(vec.begin(),
			std::istream_iterator<char>(file),
			std::istream_iterator<char>());

		return vec;
	}

	uint32_t SharedFileUtils::GetSize(const std::filesystem::path& root, const std::filesystem::path& file_name) const {
		try {
			return (uint32_t)std::filesystem::file_size(GetPath(root, file_name));
		}
		catch (std::filesystem::filesystem_error) {
			return 0;
		}
	}

	uint32_t SharedFileUtils::GetTimestamp(const std::filesystem::path& root, const std::filesystem::path& file_name) const {
		try {
			return (uint32_t)(std::filesystem::last_write_time(GetPath(root, file_name)).time_since_epoch() / std::chrono::seconds(1));
		}
		catch (std::filesystem::filesystem_error) {
			return 0;
		}
	}

	uint32_t SharedFileUtils::GetFileCount(const std::filesystem::path& root) const {
		return (uint32_t)number_of_files_in_directory(GetPath(root, "/"));
	}

	SharedFileID SharedFileUtils::GetSharedIDByIndex(uint32_t index) const {
		using std::filesystem::directory_iterator;

		auto entries = directory_iterator(GetPath(ROOT_ID_TO_FILENAME, "/"));
		for (auto& entry : entries) {
			if (index-- == 0) {
				return std::stoull(entry.path().string());
			}
		}

		return 0;
	}

	std::filesystem::path SharedFileUtils::GetFileNameByIndex(const std::filesystem::path& root, uint32_t index) const {
		using std::filesystem::directory_iterator;

		auto entries = directory_iterator(GetPath(root, "/"));
		for (auto& entry : entries) {
			if (index-- == 0) {
				return entry.path();
			}
		}

		return "";
	}

	std::vector<std::filesystem::path> SharedFileUtils::GetDirectoryFileList(const std::filesystem::path& root, const std::filesystem::path& directory) const
	{
		std::vector<std::filesystem::path> file_list;
		using std::filesystem::recursive_directory_iterator;

		auto search_root_path = GetPath(root, directory);
		auto entries = recursive_directory_iterator(search_root_path);
		for (auto& entry : entries) {
			auto relative_path = std::filesystem::relative(entry, search_root_path);
			file_list.push_back(relative_path);
		}

		return file_list;
	}

	bool SharedFileUtils::Copy(const std::filesystem::path& root_from, const std::filesystem::path& root_to, const std::filesystem::path& file_name) const {
		return std::filesystem::copy_file(GetPath(root_from, file_name), GetPath(root_to, file_name));
	}

	std::fstream SharedFileUtils::OpenShared(SharedFileID id, std::ios::openmode mode) const {
		return Open(ROOT_SHARED, GetSharedFileName(id), mode);
	}

	std::fstream SharedFileUtils::OpenShared(const std::filesystem::path& file_name, std::ios::openmode mode) const {
		return Open(ROOT_SHARED, file_name, mode);
	}

	std::fstream SharedFileUtils::OpenLocal(const std::filesystem::path& file_name, std::ios::openmode mode) const {
		return Open(ROOT_LOCAL, file_name, mode);
	}

	std::fstream SharedFileUtils::OpenAvatar(const std::filesystem::path& file_name, std::ios::openmode mode) const {
		return Open(ROOT_AVATARS, file_name, mode);
	}

	std::filesystem::path SharedFileUtils::GetPathShared(SharedFileID id) const {
		return GetPath(ROOT_SHARED, GetSharedFileName(id));
	}

	std::filesystem::path SharedFileUtils::GetPathShared(const std::filesystem::path& file_name) const {
		return GetPath(ROOT_SHARED, file_name);
	}

	std::filesystem::path SharedFileUtils::GetPathLocal(const std::filesystem::path& file_name) const {
		return GetPath(ROOT_LOCAL, file_name);
	}

	std::filesystem::path SharedFileUtils::GetPathAvatar(const std::filesystem::path& file_name) const {
		return GetPath(ROOT_AVATARS, file_name);
	}

	std::filesystem::path SharedFileUtils::GetPathCloud(const std::filesystem::path& container, const std::filesystem::path& file_name)  const {
		return GetPath(ROOT_CLOUD, container, file_name);
	}

	bool SharedFileUtils::ExistsShared(SharedFileID id) const {
		return Exists(ROOT_SHARED, GetSharedFileName(id));
	}

	bool SharedFileUtils::ExistsShared(const std::filesystem::path& file_name) const {
		return Exists(ROOT_SHARED, file_name);
	}

	bool SharedFileUtils::ExistsLocal(const std::filesystem::path& file_name) const {
		return Exists(ROOT_LOCAL, file_name);
	}

	bool SharedFileUtils::ExistsAvatar(const std::filesystem::path& file_name) const {
		return Exists(ROOT_AVATARS, file_name);
	}

	bool SharedFileUtils::ExistsCloud(const std::filesystem::path& container, const std::filesystem::path& file_name) const {
		return Exists(GetPath(ROOT_CLOUD, container), file_name);
	}

	bool SharedFileUtils::RemoveShared(SharedFileID id) const {
		return Remove(ROOT_SHARED, GetSharedFileName(id));
	}

	bool SharedFileUtils::RemoveShared(const std::filesystem::path& file_name) const {
		return Remove(ROOT_SHARED, file_name);
	}

	bool SharedFileUtils::RemoveLocal(const std::filesystem::path& file_name) const {
		return Remove(ROOT_LOCAL, file_name);
	}

	bool SharedFileUtils::RemoveAvatar(const std::filesystem::path& file_name) const {
		return Remove(ROOT_AVATARS, file_name);
	}

	bool SharedFileUtils::RemoveCloud(const std::filesystem::path& container, const std::filesystem::path& file_name) const {
		return Remove(GetPath(ROOT_CLOUD, container), file_name);
	}

	bool SharedFileUtils::WriteShared(SharedFileID id, const char* data, size_t data_length) const {
		return Write(ROOT_SHARED, GetSharedFileName(id), data, data_length);
	}

	bool SharedFileUtils::WriteShared(const std::filesystem::path& file_name, const char* data, size_t data_length) const {
		return Write(ROOT_SHARED, file_name, data, data_length);
	}

	bool SharedFileUtils::WriteLocal(const std::filesystem::path& file_name, const char* data, size_t data_length) const {
		return Write(ROOT_LOCAL, file_name, data, data_length);
	}

	bool SharedFileUtils::WriteAvatar(const std::filesystem::path& file_name, const char* data, size_t data_length) const {
		return Write(ROOT_AVATARS, file_name, data, data_length);
	}

	bool SharedFileUtils::WriteCloud(const std::filesystem::path& container, const std::filesystem::path& file_name, const char* data, size_t data_length) const {
		return Write(GetPath(ROOT_CLOUD, container), file_name, data, data_length);
	}

	uint32_t SharedFileUtils::ReadShared(SharedFileID id, char* data, size_t data_length, size_t offset) const {
		return Read(ROOT_SHARED, GetSharedFileName(id), data, data_length, offset);
	}

	uint32_t SharedFileUtils::ReadShared(const std::filesystem::path& file_name, char* data, size_t data_length, size_t offset) const {
		return Read(ROOT_SHARED, file_name, data, data_length, offset);
	}

	uint32_t SharedFileUtils::ReadLocal(const std::filesystem::path& file_name, char* data, size_t data_length, size_t offset) const {
		return Read(ROOT_LOCAL, file_name, data, data_length, offset);
	}

	uint32_t SharedFileUtils::ReadAvatar(const std::filesystem::path& file_name, char* data, size_t data_length, size_t offset) const {
		return Read(ROOT_AVATARS, file_name, data, data_length, offset);
	}

	uint32_t SharedFileUtils::ReadCloud(const std::filesystem::path& container, const std::filesystem::path& file_name, char* data, size_t data_length, size_t offset) const {
		return Read(GetPath(ROOT_CLOUD, container), file_name, data, data_length);
	}

	std::vector<char> SharedFileUtils::ReadShared(SharedFileID id) const {
		return Read(ROOT_SHARED, GetSharedFileName(id));
	}

	std::vector<char> SharedFileUtils::ReadShared(const std::filesystem::path& file_name) const {
		return Read(ROOT_SHARED, file_name);
	}

	std::vector<char> SharedFileUtils::ReadLocal(const std::filesystem::path& file_name) const {
		return Read(ROOT_LOCAL, file_name);
	}

	std::vector<char> SharedFileUtils::ReadAvatar(const std::filesystem::path& file_name) const {
		return Read(ROOT_AVATARS, file_name);
	}

	std::vector<char> SharedFileUtils::ReadCloud(const std::filesystem::path& container, const std::filesystem::path& file_name) const {
		return Read(GetPath(ROOT_CLOUD, container), file_name);
	}

	uint32_t SharedFileUtils::GetSizeShared(SharedFileID id) const {
		return GetSize(ROOT_SHARED, GetSharedFileName(id));
	}

	uint32_t SharedFileUtils::GetSizeShared(const std::filesystem::path& file_name) const {
		return GetSize(ROOT_SHARED, file_name);
	}

	uint32_t SharedFileUtils::GetSizeLocal(const std::filesystem::path& file_name) const {
		return GetSize(ROOT_LOCAL, file_name);
	}

	uint32_t SharedFileUtils::GetSizeAvatar(const std::filesystem::path& file_name) const {
		return GetSize(ROOT_AVATARS, file_name);
	}

	uint32_t SharedFileUtils::GetSizeCloud(const std::filesystem::path& container, const std::filesystem::path& file_name) const {
		return GetSize(GetPath(ROOT_CLOUD, container), file_name);
	}

	uint32_t SharedFileUtils::GetTimestampShared(SharedFileID id) const {
		return GetTimestamp(ROOT_SHARED, GetSharedFileName(id));
	}

	uint32_t SharedFileUtils::GetTimestampShared(const std::filesystem::path& file_name) const {
		return GetTimestamp(ROOT_SHARED, file_name);
	}

	uint32_t SharedFileUtils::GetTimestampLocal(const std::filesystem::path& file_name) const {
		return GetTimestamp(ROOT_LOCAL, file_name);
	}

	uint32_t SharedFileUtils::GetTimestampAvatar(const std::filesystem::path& file_name) const {
		return GetTimestamp(ROOT_AVATARS, file_name);
	}

	uint32_t SharedFileUtils::GetTimestampCloud(const std::filesystem::path& container, const std::filesystem::path& file_name) const {
		return GetTimestamp(GetPath(ROOT_CLOUD, container), file_name);
	}

	uint32_t SharedFileUtils::GetFileCountShared() const {
		return GetFileCount(ROOT_SHARED);
	}

	uint32_t SharedFileUtils::GetFileCountLocal() const {
		return GetFileCount(ROOT_LOCAL);
	}

	uint32_t SharedFileUtils::GetFileCountAvatar() const {
		return GetFileCount(ROOT_AVATARS);
	}

	uint32_t SharedFileUtils::GetFileCountCloud(const std::filesystem::path& container) const {
		return GetFileCount(GetPath(ROOT_CLOUD, container));
	}

	std::filesystem::path SharedFileUtils::GetFileNameByIndexShared(uint32_t index) const {
		return GetFileNameByIndex(ROOT_SHARED, index);
	}

	std::filesystem::path SharedFileUtils::GetFileNameByIndexLocal(uint32_t index) const {
		return GetFileNameByIndex(ROOT_LOCAL, index);
	}

	std::filesystem::path SharedFileUtils::GetFileNameByIndexAvatar(uint32_t index) const {
		return GetFileNameByIndex(ROOT_AVATARS, index);
	}

	std::filesystem::path SharedFileUtils::GetFileNameByIndexCloud(const std::filesystem::path& container, uint32_t index) const {
		return GetFileNameByIndex(GetPath(ROOT_CLOUD, container), index);
	}

	bool SharedFileUtils::CopyFromLocalToShared(const std::filesystem::path& file_name) const {
		return std::filesystem::copy_file(GetPath(ROOT_LOCAL, file_name), GetPath(ROOT_SHARED, file_name));
	}

	bool SharedFileUtils::CopyFromSharedToLocal(const std::filesystem::path& file_name) const {
		return std::filesystem::copy_file(GetPath(ROOT_SHARED, file_name), GetPath(ROOT_LOCAL, file_name));
	}

	bool SharedFileUtils::UnlinkSharedFileStorage(SharedFileID id) const {
		return UnlinkSharedFileStorage(GetSharedFileName(id), id);
	}

	bool SharedFileUtils::UnlinkSharedFileStorage(const std::filesystem::path& filename) const {
		return UnlinkSharedFileStorage(filename, GetSharedFileID(filename));
	}

	uint32_t SharedFileUtils::GetTotalDiskSpace() const {
		std::error_code ec;
		const std::filesystem::space_info si = std::filesystem::space(basepath, ec);
		if (si.capacity >= std::numeric_limits<uint32_t>::max()) {
			return std::numeric_limits<uint32_t>::max();
		}

		return (uint32_t)si.capacity;
	}

	uint32_t SharedFileUtils::GetAvailableDiskSpace() const {
		std::error_code ec;
		const std::filesystem::space_info si = std::filesystem::space(basepath, ec);
		if (si.available >= std::numeric_limits<uint32_t>::max()) {
			return std::numeric_limits<uint32_t>::max();
		}

		return (uint32_t)si.available;
	}

	std::vector<std::filesystem::path> SharedFileUtils::GetDirectoryFileListCloud(const std::filesystem::path& container) const
	{
		return GetDirectoryFileList(GetPath(ROOT_CLOUD, container), "/");
	}

	std::filesystem::path SharedFileUtils::FilterBadFilenameChars(std::filesystem::path file_name) {
		// keep this sorted for more performance (helps cpu predictor)
		constexpr static const char bad_chars[] = { '"', '*' , '/', ':', '<', '>', '?', '\\', '|' };
		std::string fixed_filename{ "" };

		for (char c : file_name.string()) {
			for (const char b : bad_chars) {
				if (c < 32 || b == c) {
					c = '_';
				}
			}
			fixed_filename.push_back(c);
		}

		return fixed_filename;
	}
}
