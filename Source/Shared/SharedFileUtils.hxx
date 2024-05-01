#pragma once

#include <GalaxyVersionedTypes.hxx>
#include <IniData.hxx>

#include <GalaxyApi.h>

#include <exception>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace universelan {
	class SharedFileUtils {
	private:
		std::filesystem::path basepath;

	public:
		static const std::filesystem::path ROOT_LOCAL;
		static const std::filesystem::path ROOT_CLOUD;
		static const std::filesystem::path ROOT_CLOUD_METADATA;
		static const std::filesystem::path ROOT_SHARED;
		static const std::filesystem::path ROOT_AVATARS;
		static const std::filesystem::path ROOT_LOGGING;
		static const std::filesystem::path ROOT_TELEMETRY;
		static const std::filesystem::path ROOT_FILENAME_TO_ID;
		static const std::filesystem::path ROOT_ID_TO_FILENAME;

		SharedFileUtils(const std::filesystem::path& basepath);
		bool InitSharedFileStorage(const std::filesystem::path& filename, galaxy::api::SharedFileID id) const;
		bool UnlinkSharedFileStorage(const std::filesystem::path& filename, galaxy::api::SharedFileID id) const;
		bool UnlinkSharedFileStorage(galaxy::api::SharedFileID id) const;
		bool UnlinkSharedFileStorage(const std::filesystem::path& filename) const;
		galaxy::api::SharedFileID GetSharedFileID(const std::filesystem::path& filename) const;
		std::filesystem::path GetSharedFileName(galaxy::api::SharedFileID id) const;

		std::fstream OpenShared(galaxy::api::SharedFileID id, std::ios::openmode mode) const;
		std::fstream OpenShared(const std::filesystem::path& file_name, std::ios::openmode mode) const;
		std::fstream OpenLocal(const std::filesystem::path& file_name, std::ios::openmode mode) const;
		std::fstream OpenAvatar(const std::filesystem::path& file_name, std::ios::openmode mode) const;
		std::fstream Open(const std::filesystem::path& root, const std::filesystem::path& file_name, std::ios::openmode mode) const;

		std::filesystem::path GetPathShared(galaxy::api::SharedFileID id) const;
		std::filesystem::path GetPathShared(const std::filesystem::path& file_name) const;
		std::filesystem::path GetPathLocal(const std::filesystem::path& file_name) const;
		std::filesystem::path GetPathAvatar(const std::filesystem::path& file_name) const;
		std::filesystem::path GetPathCloud(const std::filesystem::path& container, const std::filesystem::path& file_name) const;
		std::filesystem::path GetPath(const std::filesystem::path& root, const std::filesystem::path& file_name) const;
		std::filesystem::path GetPath(const std::filesystem::path& root, const std::filesystem::path& container, const std::filesystem::path& file_name) const;

		bool ExistsShared(galaxy::api::SharedFileID id) const;
		bool ExistsShared(const std::filesystem::path& file_name) const;
		bool ExistsLocal(const std::filesystem::path& file_name) const;
		bool ExistsAvatar(const std::filesystem::path& file_name) const;
		bool ExistsCloud(const std::filesystem::path& container, const std::filesystem::path& file_name) const;
		bool Exists(const std::filesystem::path& root, const std::filesystem::path& file_name) const;

		bool RemoveShared(galaxy::api::SharedFileID id) const;
		bool RemoveShared(const std::filesystem::path& file_name) const;
		bool RemoveLocal(const std::filesystem::path& file_name) const;
		bool RemoveAvatar(const std::filesystem::path& file_name) const;
		bool RemoveCloud(const std::filesystem::path& container, const std::filesystem::path& file_name) const;
		bool Remove(const std::filesystem::path& root, const std::filesystem::path& file_name) const;

		bool WriteShared(galaxy::api::SharedFileID id, const char* data, size_t data_length) const;
		bool WriteShared(const std::filesystem::path& file_name, const char* data, size_t data_length) const;
		bool WriteLocal(const std::filesystem::path& file_name, const char* data, size_t data_length) const;
		bool WriteAvatar(const std::filesystem::path& file_name, const char* data, size_t data_length) const;
		bool WriteCloud(const std::filesystem::path& container, const std::filesystem::path& file_name, const char* data, size_t data_length) const;
		bool Write(const std::filesystem::path& root, const std::filesystem::path& file_name, const char* data, size_t data_length) const;

		std::vector<char> ReadShared(galaxy::api::SharedFileID id) const;
		std::vector<char> ReadShared(const std::filesystem::path& file_name) const;
		std::vector<char> ReadLocal(const std::filesystem::path& file_name) const;
		std::vector<char> ReadAvatar(const std::filesystem::path& file_name) const;
		std::vector<char> ReadCloud(const std::filesystem::path& container, const std::filesystem::path& file_name) const;
		std::vector<char> Read(const std::filesystem::path& root, const std::filesystem::path& file_name) const;

		uint32_t ReadShared(galaxy::api::SharedFileID id, char* data, size_t data_length, size_t offset = 0) const;
		uint32_t ReadShared(const std::filesystem::path& file_name, char* data, size_t data_length, size_t offset = 0) const;
		uint32_t ReadLocal(const std::filesystem::path& file_name, char* data, size_t data_length, size_t offset = 0) const;
		uint32_t ReadAvatar(const std::filesystem::path& file_name, char* data, size_t data_length, size_t offset = 0) const;
		uint32_t ReadCloud(const std::filesystem::path& container, const std::filesystem::path& file_name, char* data, size_t data_length, size_t offset = 0) const;
		uint32_t Read(const std::filesystem::path& root, const std::filesystem::path& file_name, char* data, size_t data_length, size_t offset = 0) const;

		uint32_t GetSizeShared(galaxy::api::SharedFileID id) const;
		uint32_t GetSizeShared(const std::filesystem::path& file_name) const;
		uint32_t GetSizeLocal(const std::filesystem::path& file_name) const;
		uint32_t GetSizeAvatar(const std::filesystem::path& file_name) const;
		uint32_t GetSizeCloud(const std::filesystem::path& container, const std::filesystem::path& file_name) const;
		uint32_t GetSize(const std::filesystem::path& root, const std::filesystem::path& file_name) const;

		uint32_t GetTimestampShared(galaxy::api::SharedFileID id) const;
		uint32_t GetTimestampShared(const std::filesystem::path& file_name) const;
		uint32_t GetTimestampLocal(const std::filesystem::path& file_name) const;
		uint32_t GetTimestampAvatar(const std::filesystem::path& file_name) const;
		uint32_t GetTimestampCloud(const std::filesystem::path& container, const std::filesystem::path& file_name) const;
		uint32_t GetTimestamp(const std::filesystem::path& root, const std::filesystem::path& file_name) const;

		uint32_t GetFileCountShared() const;
		uint32_t GetFileCountLocal() const;
		uint32_t GetFileCountAvatar() const;
		uint32_t GetFileCountCloud(const std::filesystem::path& container) const;
		uint32_t GetFileCount(const std::filesystem::path& root) const;

		galaxy::api::SharedFileID GetSharedIDByIndex(uint32_t index) const;
		std::filesystem::path GetFileNameByIndexShared(uint32_t index) const;
		std::filesystem::path GetFileNameByIndexLocal(uint32_t index) const;
		std::filesystem::path GetFileNameByIndexAvatar(uint32_t index) const;
		std::filesystem::path GetFileNameByIndexCloud(const std::filesystem::path& container, uint32_t index) const;
		std::filesystem::path GetFileNameByIndex(const std::filesystem::path& root, uint32_t index) const;

		bool Copy(const std::filesystem::path& root_from, const std::filesystem::path& root_to, const std::filesystem::path& file_name) const;
		bool CopyFromLocalToShared(const std::filesystem::path& file_name) const;
		bool CopyFromSharedToLocal(const std::filesystem::path& file_name) const;

		static std::filesystem::path FilterBadFilenameChars(std::filesystem::path file_name);

		uint32_t GetTotalDiskSpace() const;
		uint32_t GetAvailableDiskSpace() const;
		uint32_t GetUsedDiskSpace() const;

		std::vector<std::filesystem::path> GetDirectoryFileListCloud(const std::filesystem::path& container, bool recurse = false) const;
		std::vector<std::filesystem::path> GetDirectoryFileList(const std::filesystem::path& root, const std::filesystem::path& directory, bool recurse = false) const;
	};

	inline bool inside_basepath(
		const std::filesystem::path& basepath,
		const std::filesystem::path& relpath) {

		const auto baseabspath = std::filesystem::weakly_canonical(basepath);
		const auto abspath = std::filesystem::weakly_canonical(basepath / relpath);

		const auto index = abspath.string().rfind(baseabspath.string(), 0);
		if (index != 0) {
			return false;
		}
		return true;
	}

	inline std::filesystem::path sandbox_secure_path_concat(const std::filesystem::path& secure_basepath, const std::filesystem::path& untrusted_file_name) {
		if (inside_basepath(secure_basepath, untrusted_file_name)) {
			return (secure_basepath / untrusted_file_name);
		}

		if (untrusted_file_name == "/") {
			return secure_basepath;
		}

		throw std::runtime_error("Security Exception: Path traversal outside sandbox: " + untrusted_file_name.string());
	}
}
