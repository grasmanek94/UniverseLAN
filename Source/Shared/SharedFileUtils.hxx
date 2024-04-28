#pragma once

#include <GalaxyVersionedTypes.hxx>
#include <IniData.hxx>

#include <GalaxyApi.h>

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace universelan {
	class SharedFileUtils {
		std::filesystem::path basepath;

	public:
		static const std::string ROOT_LOCAL;
		static const std::string ROOT_CLOUD;
		static const std::string ROOT_SHARED;
		static const std::string ROOT_AVATARS;
		static const std::string ROOT_LOGGING;
		static const std::string ROOT_TELEMETRY;
		static const std::string ROOT_FILENAME_TO_ID;
		static const std::string ROOT_ID_TO_FILENAME;

		SharedFileUtils(const std::string& basepath);
		bool InitSharedFileStorage(const std::string& filename, galaxy::api::SharedFileID id) const;
		bool UnlinkSharedFileStorage(const std::string& filename, galaxy::api::SharedFileID id) const;
		bool UnlinkSharedFileStorage(galaxy::api::SharedFileID id) const;
		bool UnlinkSharedFileStorage(const std::string& filename) const;
		galaxy::api::SharedFileID GetSharedFileID(const std::string& filename) const;
		std::string GetSharedFileName(galaxy::api::SharedFileID id) const;

		std::fstream OpenShared(galaxy::api::SharedFileID id, std::ios::openmode mode) const;
		std::fstream OpenShared(const std::string& file_name, std::ios::openmode mode) const;
		std::fstream OpenLocal(const std::string& file_name, std::ios::openmode mode) const;
		std::fstream OpenAvatar(const std::string& file_name, std::ios::openmode mode) const;
		std::fstream Open(const std::string& root, const std::string& file_name, std::ios::openmode mode) const;

		std::filesystem::path GetPathShared(galaxy::api::SharedFileID id) const;
		std::filesystem::path GetPathShared(const std::string& file_name) const;
		std::filesystem::path GetPathLocal(const std::string& file_name) const;
		std::filesystem::path GetPathAvatar(const std::string& file_name) const;
		std::filesystem::path GetPath(const std::string& root, const std::string& file_name) const;

		bool ExistsShared(galaxy::api::SharedFileID id) const;
		bool ExistsShared(const std::string& file_name) const;
		bool ExistsLocal(const std::string& file_name) const;
		bool ExistsAvatar(const std::string& file_name) const;
		bool Exists(const std::string& root, const std::string& file_name) const;

		bool RemoveShared(galaxy::api::SharedFileID id) const;
		bool RemoveShared(const std::string& file_name) const;
		bool RemoveLocal(const std::string& file_name) const;
		bool RemoveAvatar(const std::string& file_name) const;
		bool Remove(const std::string& root, const std::string& file_name) const;

		bool WriteShared(galaxy::api::SharedFileID id, const char* data, size_t data_length) const;
		bool WriteShared(const std::string& file_name, const char* data, size_t data_length) const;
		bool WriteLocal(const std::string& file_name, const char* data, size_t data_length) const;
		bool WriteAvatar(const std::string& file_name, const char* data, size_t data_length) const;
		bool Write(const std::string& root, const std::string& file_name, const char* data, size_t data_length) const;

		std::vector<char> ReadShared(galaxy::api::SharedFileID id) const;
		std::vector<char> ReadShared(const std::string& file_name) const;
		std::vector<char> ReadLocal(const std::string& file_name) const;
		std::vector<char> ReadAvatar(const std::string& file_name) const;
		std::vector<char> Read(const std::string& root, const std::string& file_name) const;

		uint32_t ReadShared(galaxy::api::SharedFileID id, char* data, size_t data_length, size_t offset = 0) const;
		uint32_t ReadShared(const std::string& file_name, char* data, size_t data_length, size_t offset = 0) const;
		uint32_t ReadLocal(const std::string& file_name, char* data, size_t data_length, size_t offset = 0) const;
		uint32_t ReadAvatar(const std::string& file_name, char* data, size_t data_length, size_t offset = 0) const;
		uint32_t Read(const std::string& root, const std::string& file_name, char* data, size_t data_length, size_t offset = 0) const;

		uint32_t GetSizeShared(galaxy::api::SharedFileID id) const;
		uint32_t GetSizeShared(const std::string& file_name) const;
		uint32_t GetSizeLocal(const std::string& file_name) const;
		uint32_t GetSizeAvatar(const std::string& file_name) const;
		uint32_t GetSize(const std::string& root, const std::string& file_name) const;

		uint32_t GetTimestampShared(galaxy::api::SharedFileID id) const;
		uint32_t GetTimestampShared(const std::string& file_name) const;
		uint32_t GetTimestampLocal(const std::string& file_name) const;
		uint32_t GetTimestampAvatar(const std::string& file_name) const;
		uint32_t GetTimestamp(const std::string& root, const std::string& file_name) const;

		uint32_t GetFileCountShared() const;
		uint32_t GetFileCountLocal() const;
		uint32_t GetFileCountAvatar() const;
		uint32_t GetFileCount(const std::string& root) const;

		galaxy::api::SharedFileID GetSharedIDByIndex(uint32_t index) const;
		std::string GetFileNameByIndexShared(uint32_t index) const;
		std::string GetFileNameByIndexLocal(uint32_t index) const;
		std::string GetFileNameByIndexAvatar(uint32_t index) const;
		std::string GetFileNameByIndex(const std::string& root, uint32_t index) const;

		bool Copy(const std::string& root_from, const std::string& root_to, const std::string& file_name) const;
		bool CopyFromLocalToShared(const std::string& file_name) const;
		bool CopyFromSharedToLocal(const std::string& file_name) const;
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
}
