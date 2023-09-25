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

	const std::string SharedFileUtils::ROOT_LOCAL = "Local";
	const std::string SharedFileUtils::ROOT_SHARED = "Shared";
	const std::string SharedFileUtils::ROOT_AVATARS = "Avatars";
	const std::string SharedFileUtils::ROOT_LOGGING = "Logging";
	const std::string SharedFileUtils::ROOT_TELEMETRY = "Telemetry";
	const std::string SharedFileUtils::ROOT_FILENAME_TO_ID = "/mapper/__filename_to_id__";
	const std::string SharedFileUtils::ROOT_ID_TO_FILENAME = "/mapper/__id_to_filename__";

	SharedFileUtils::SharedFileUtils(const std::string& basepath) : basepath{ basepath } {}

	bool SharedFileUtils::InitSharedFileStorage(const std::string& filename, SharedFileID id) const {
		std::error_code ec;

		const std::string str_shared_file_id{ std::to_string(id) };

		std::filesystem::path filename_to_id_basepath{ basepath / ROOT_SHARED / ROOT_FILENAME_TO_ID };
		std::filesystem::path id_to_filename_basepath{ basepath / ROOT_SHARED / ROOT_ID_TO_FILENAME };
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

		throw std::runtime_error("Security Exception: Path traversal outside sandbox: " + filename);
	}

	bool SharedFileUtils::UnlinkSharedFileStorage(const std::string& filename, SharedFileID id) const {
		std::error_code ec;

		const std::string str_shared_file_id{ std::to_string(id) };

		std::filesystem::path filename_to_id_basepath{ basepath / ROOT_SHARED / ROOT_FILENAME_TO_ID };
		std::filesystem::path id_to_filename_basepath{ basepath / ROOT_SHARED / ROOT_ID_TO_FILENAME };
		std::filesystem::path sharedfile_storage_basepath{ basepath / ROOT_SHARED };

		if (inside_basepath(sharedfile_storage_basepath, filename) && inside_basepath(filename_to_id_basepath, filename)) {
			std::filesystem::path id2filename_path = id_to_filename_basepath / str_shared_file_id;
			std::filesystem::path filename2id_path = filename_to_id_basepath / filename;
			std::filesystem::path storage_path = sharedfile_storage_basepath / filename;

			std::filesystem::remove(id2filename_path);
			std::filesystem::remove(filename2id_path);

			return RemoveShared(filename);
		}

		throw std::runtime_error("Security Exception: Path traversal outside sandbox: " + filename);
	}

	SharedFileID SharedFileUtils::GetSharedFileID(const std::string& filename) const {
		std::error_code ec;

		std::filesystem::path filename_to_id_basepath{ basepath / ROOT_SHARED / ROOT_FILENAME_TO_ID };
		std::filesystem::path sharedfile_storage_basepath{ basepath / ROOT_SHARED };

		if (inside_basepath(sharedfile_storage_basepath, filename) && inside_basepath(filename_to_id_basepath, filename)) {
			std::filesystem::path filename2id_path = filename_to_id_basepath / filename;

			std::string str_shared_file_id;

			std::fstream{ (filename2id_path).string(), std::ios::in } >> str_shared_file_id;

			return std::stoull(str_shared_file_id);
		}

		throw std::runtime_error("Security Exception: Path traversal outside sandbox: " + filename);
	}

	std::string SharedFileUtils::GetSharedFileName(SharedFileID id) const {
		std::error_code ec;

		const std::string str_shared_file_id{ std::to_string(id) };

		std::filesystem::path id_to_filename_basepath{ basepath / ROOT_SHARED / ROOT_ID_TO_FILENAME };
		std::filesystem::path id2filename_path = id_to_filename_basepath / str_shared_file_id;

		std::string filename;
		std::fstream{ (id2filename_path).string(), std::ios::in } >> filename;

		return filename;
	}

	std::fstream SharedFileUtils::Open(const std::string& root, const std::string& file_name, std::ios::openmode mode) const {
		std::error_code ec;
		auto path = GetPath(root, file_name);

		std::filesystem::create_directories(std::filesystem::path(path).remove_filename(), ec);

		return std::fstream{ path.string(), mode };
	}

	std::filesystem::path SharedFileUtils::GetPath(const std::string& root, const std::string& file_name) const {
		std::filesystem::path combined(basepath / root);

		if (inside_basepath(combined, file_name)) {
			return (combined / file_name);
		}

		if (file_name == "/") {
			return combined;
		}

		throw std::runtime_error("Security Exception: Path traversal outside sandbox: " + file_name);
	}

	bool SharedFileUtils::Exists(const std::string& root, const std::string& file_name) const {
		return std::filesystem::exists(GetPath(root, file_name));
	}

	bool SharedFileUtils::Remove(const std::string& root, const std::string& file_name) const {
		return std::filesystem::remove(GetPath(root, file_name));
	}

	bool SharedFileUtils::Write(const std::string& root, const std::string& file_name, const char* data, size_t data_length) const {
		auto file = Open(root, file_name, std::ios::out | std::ios::trunc | std::ios::binary);
		if (!file) {
			return false;
		}

		file.write(data, data_length);
		return true;
	}

	uint32_t SharedFileUtils::Read(const std::string& root, const std::string& file_name, char* data, size_t data_length, size_t offset) const {
		auto file = Open(root, file_name, std::ios::in | std::ios::binary);
		if (!file) {
			return 0;
		}

		file.seekg(offset);
		file.read(data, data_length);
		return (uint32_t)file.gcount();
	}

	std::vector<char> SharedFileUtils::Read(const std::string& root, const std::string& file_name) const {
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

	uint32_t SharedFileUtils::GetSize(const std::string& root, const std::string& file_name) const {
		try {
			return (uint32_t)std::filesystem::file_size(GetPath(root, file_name));
		}
		catch (std::filesystem::filesystem_error) {
			return 0;
		}
	}

	uint32_t SharedFileUtils::GetTimestamp(const std::string& root, const std::string& file_name) const {
		try {
			return (uint32_t)(std::filesystem::last_write_time(GetPath(root, file_name)).time_since_epoch() / std::chrono::seconds(1));
		}
		catch (std::filesystem::filesystem_error) {
			return 0;
		}
	}

	uint32_t SharedFileUtils::GetFileCount(const std::string& root) const {
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

	std::string SharedFileUtils::GetFileNameByIndex(const std::string& root, uint32_t index) const {
		using std::filesystem::directory_iterator;

		auto entries = directory_iterator(GetPath(root, "/"));
		for (auto& entry : entries) {
			if (index-- == 0) {
				return entry.path().string();
			}
		}

		return ".";
	}

	bool SharedFileUtils::Copy(const std::string& root_from, const std::string& root_to, const std::string& file_name) const {
		return std::filesystem::copy_file(GetPath(root_from, file_name), GetPath(root_to, file_name));
	}

	std::fstream SharedFileUtils::OpenShared(SharedFileID id, std::ios::openmode mode) const {
		return Open(ROOT_SHARED, GetSharedFileName(id), mode);
	}

	std::fstream SharedFileUtils::OpenShared(const std::string& file_name, std::ios::openmode mode) const {
		return Open(ROOT_SHARED, file_name, mode);
	}

	std::fstream SharedFileUtils::OpenLocal(const std::string& file_name, std::ios::openmode mode) const {
		return Open(ROOT_LOCAL, file_name, mode);
	}

	std::fstream SharedFileUtils::OpenAvatar(const std::string& file_name, std::ios::openmode mode) const {
		return Open(ROOT_AVATARS, file_name, mode);
	}

	std::filesystem::path SharedFileUtils::GetPathShared(SharedFileID id) const {
		return GetPath(ROOT_SHARED, GetSharedFileName(id));
	}

	std::filesystem::path SharedFileUtils::GetPathShared(const std::string& file_name) const {
		return GetPath(ROOT_SHARED, file_name);
	}

	std::filesystem::path SharedFileUtils::GetPathLocal(const std::string& file_name) const {
		return GetPath(ROOT_LOCAL, file_name);
	}

	std::filesystem::path SharedFileUtils::GetPathAvatar(const std::string& file_name) const {
		return GetPath(ROOT_AVATARS, file_name);
	}

	bool SharedFileUtils::ExistsShared(SharedFileID id) const {
		return Exists(ROOT_SHARED, GetSharedFileName(id));
	}

	bool SharedFileUtils::ExistsShared(const std::string& file_name) const {
		return Exists(ROOT_SHARED, file_name);
	}

	bool SharedFileUtils::ExistsLocal(const std::string& file_name) const {
		return Exists(ROOT_LOCAL, file_name);
	}

	bool SharedFileUtils::ExistsAvatar(const std::string& file_name) const {
		return Exists(ROOT_AVATARS, file_name);
	}

	bool SharedFileUtils::RemoveShared(SharedFileID id) const {
		return Remove(ROOT_SHARED, GetSharedFileName(id));
	}

	bool SharedFileUtils::RemoveShared(const std::string& file_name) const {
		return Remove(ROOT_SHARED, file_name);
	}

	bool SharedFileUtils::RemoveLocal(const std::string& file_name) const {
		return Remove(ROOT_LOCAL, file_name);
	}

	bool SharedFileUtils::RemoveAvatar(const std::string& file_name) const {
		return Remove(ROOT_AVATARS, file_name);
	}

	bool SharedFileUtils::WriteShared(SharedFileID id, const char* data, size_t data_length) const {
		return Write(ROOT_SHARED, GetSharedFileName(id), data, data_length);
	}

	bool SharedFileUtils::WriteShared(const std::string& file_name, const char* data, size_t data_length) const {
		return Write(ROOT_SHARED, file_name, data, data_length);
	}

	bool SharedFileUtils::WriteLocal(const std::string& file_name, const char* data, size_t data_length) const {
		return Write(ROOT_LOCAL, file_name, data, data_length);
	}

	bool SharedFileUtils::WriteAvatar(const std::string& file_name, const char* data, size_t data_length) const {
		return Write(ROOT_AVATARS, file_name, data, data_length);
	}

	uint32_t SharedFileUtils::ReadShared(SharedFileID id, char* data, size_t data_length, size_t offset) const {
		return Read(ROOT_SHARED, GetSharedFileName(id), data, data_length, offset);
	}

	uint32_t SharedFileUtils::ReadShared(const std::string& file_name, char* data, size_t data_length, size_t offset) const {
		return Read(ROOT_SHARED, file_name, data, data_length, offset);
	}

	uint32_t SharedFileUtils::ReadLocal(const std::string& file_name, char* data, size_t data_length, size_t offset) const {
		return Read(ROOT_LOCAL, file_name, data, data_length, offset);
	}

	uint32_t SharedFileUtils::ReadAvatar(const std::string& file_name, char* data, size_t data_length, size_t offset) const {
		return Read(ROOT_AVATARS, file_name, data, data_length, offset);
	}

	std::vector<char> SharedFileUtils::ReadShared(SharedFileID id) const {
		return Read(ROOT_SHARED, GetSharedFileName(id));
	}

	std::vector<char> SharedFileUtils::ReadShared(const std::string& file_name) const {
		return Read(ROOT_SHARED, file_name);
	}

	std::vector<char> SharedFileUtils::ReadLocal(const std::string& file_name) const {
		return Read(ROOT_LOCAL, file_name);
	}

	std::vector<char> SharedFileUtils::ReadAvatar(const std::string& file_name) const {
		return Read(ROOT_AVATARS, file_name);
	}

	uint32_t SharedFileUtils::GetSizeShared(SharedFileID id) const {
		return GetSize(ROOT_SHARED, GetSharedFileName(id));
	}

	uint32_t SharedFileUtils::GetSizeShared(const std::string& file_name) const {
		return GetSize(ROOT_SHARED, file_name);
	}

	uint32_t SharedFileUtils::GetSizeLocal(const std::string& file_name) const {
		return GetSize(ROOT_LOCAL, file_name);
	}

	uint32_t SharedFileUtils::GetSizeAvatar(const std::string& file_name) const {
		return GetSize(ROOT_AVATARS, file_name);
	}

	uint32_t SharedFileUtils::GetTimestampShared(SharedFileID id) const {
		return GetTimestamp(ROOT_SHARED, GetSharedFileName(id));
	}

	uint32_t SharedFileUtils::GetTimestampShared(const std::string& file_name) const {
		return GetTimestamp(ROOT_SHARED, file_name);
	}

	uint32_t SharedFileUtils::GetTimestampLocal(const std::string& file_name) const {
		return GetTimestamp(ROOT_LOCAL, file_name);
	}

	uint32_t SharedFileUtils::GetTimestampAvatar(const std::string& file_name) const {
		return GetTimestamp(ROOT_AVATARS, file_name);
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

	std::string SharedFileUtils::GetFileNameByIndexShared(uint32_t index) const {
		return GetFileNameByIndex(ROOT_SHARED, index);
	}

	std::string SharedFileUtils::GetFileNameByIndexLocal(uint32_t index) const {
		return GetFileNameByIndex(ROOT_LOCAL, index);
	}

	std::string SharedFileUtils::GetFileNameByIndexAvatar(uint32_t index) const {
		return GetFileNameByIndex(ROOT_AVATARS, index);
	}

	bool SharedFileUtils::CopyFromLocalToShared(const std::string& file_name) const {
		return std::filesystem::copy_file(GetPath(ROOT_LOCAL, file_name), GetPath(ROOT_SHARED, file_name));
	}

	bool SharedFileUtils::CopyFromSharedToLocal(const std::string& file_name) const {
		return std::filesystem::copy_file(GetPath(ROOT_SHARED, file_name), GetPath(ROOT_LOCAL, file_name));
	}

	bool SharedFileUtils::UnlinkSharedFileStorage(SharedFileID id) const {
		return UnlinkSharedFileStorage(GetSharedFileName(id), id);
	}

	bool SharedFileUtils::UnlinkSharedFileStorage(const std::string& filename) const {
		return UnlinkSharedFileStorage(filename, GetSharedFileID(filename));
	}
}
