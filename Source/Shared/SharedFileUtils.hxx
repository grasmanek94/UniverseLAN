#pragma once

#include <GalaxyVersionedTypes.hxx>
#include <GalaxyApi.h>

#include <filesystem_container/filesystem_container.hxx>

#include <filesystem>
#include <fstream>
#include <vector>

namespace universelan {
	class SharedFileUtils {

		using fs_container_ptr = filesystem_container::fs_container_ptr;

	public:
		SharedFileUtils(const SharedFileUtils& other);
		SharedFileUtils(const std::filesystem::path& basepath);

		const fs_container_ptr storage;
		const fs_container_ptr shared;
		const fs_container_ptr cloud;
		const fs_container_ptr avatars;

		galaxy::api::SharedFileID GetSharedFileID(const fs_container_ptr& container, const char* filename) const;
		std::filesystem::path GetSharedFileName(const fs_container_ptr& container, galaxy::api::SharedFileID id) const;

		std::fstream Open(const fs_container_ptr& container, galaxy::api::SharedFileID id, std::ios::openmode mode) const;
		std::fstream Open(const fs_container_ptr& container, const char* file_name, std::ios::openmode mode) const;

		bool Exists(const fs_container_ptr& container, galaxy::api::SharedFileID id) const;
		bool Exists(const fs_container_ptr& container, const char* file_name) const;

		bool Remove(const fs_container_ptr& container, galaxy::api::SharedFileID id) const;
		bool Remove(const fs_container_ptr& container, const char* file_name) const;

		bool Write(const fs_container_ptr& container, galaxy::api::SharedFileID id, const char* data, size_t data_length) const;
		bool Write(const fs_container_ptr& container, const char* file_name, const char* data, size_t data_length) const;

		std::vector<char> Read(const fs_container_ptr& container, galaxy::api::SharedFileID id) const;
		std::vector<char> Read(const fs_container_ptr& container, const char* file_name) const;
		uint32_t Read(const fs_container_ptr& container, const char* file_name, char* data, size_t data_length, size_t offset = 0) const;
		uint32_t Read(const fs_container_ptr& container, galaxy::api::SharedFileID id, char* data, size_t data_length, size_t offset = 0) const;

		uint32_t GetSize(const fs_container_ptr& container, const char* file_name) const;
		uint32_t GetSize(const fs_container_ptr& container, galaxy::api::SharedFileID id) const;

		uint32_t GetTimestamp(const fs_container_ptr& container, const char* file_name) const;
		uint32_t GetTimestamp(const fs_container_ptr& container, galaxy::api::SharedFileID id) const;

		uint32_t GetFileCount(const fs_container_ptr& container) const;

		galaxy::api::SharedFileID GetSharedIDByIndex(const fs_container_ptr& container, uint32_t index) const;
		std::filesystem::path GetFileNameByIndex(const fs_container_ptr& container, uint32_t index) const;

		bool CopyFromLocalToShared(const char* file_name, galaxy::api::SharedFileID id) const;
		bool CopyFromSharedToLocal(const char* file_name) const;

		uint32_t GetTotalDiskSpace(const fs_container_ptr& container) const;
		uint32_t GetAvailableDiskSpace(const fs_container_ptr& container) const;
		uint32_t GetUsedDiskSpace(const fs_container_ptr& container) const;

		std::vector<filesystem_container::fs_entry_ptr> GetDirectoryFileList(const fs_container_ptr& container) const;
	};
}
