#include "Storage.hxx"

#include "UniverseLAN.hxx"

#include <PathSecurity.hxx>

#include <chrono>
#include <filesystem>
#include <fstream>

namespace galaxy
{
	namespace api
	{
		std::fstream StorageImpl::open(const char* filename, std::ios::openmode mode) {
			std::filesystem::path basepath(intf->config->GetGameDataPath());
			basepath /= "Local";

			if (inside_basepath(basepath, filename)) {
				return std::fstream{ (basepath / filename).string(), mode };
			}

			return std::fstream{};
		}

		StorageImpl::StorageImpl(InterfaceInstances* intf) :
			intf{ intf }, listeners{ intf->listener_registrar_impl.get() }
		{}

		StorageImpl::~StorageImpl()
		{
		}

		void StorageImpl::FileWrite(const char* fileName, const void* data, uint32_t dataSize) {
			std::fstream file{ open(fileName, std::ios::app | std::ios::binary) };
			if (file) {
				file.write((const char*)data, dataSize);
			}
			else {
				std::cerr << __FUNCTION__ << " fail: " << fileName << "\n";
			}
		}

		uint32_t StorageImpl::FileRead(const char* fileName, void* data, uint32_t dataSize) {
			std::fstream file{ open(fileName, std::ios::in | std::ios::binary) };
			if (file) {
				file.read((char*)data, dataSize);
				return (uint32_t)file.tellg();
			}
			else {
				std::cerr << __FUNCTION__ << " fail: " << fileName << "\n";
				return 0;
			}
		}

		void StorageImpl::FileDelete(const char* fileName) {
			std::fstream file{ open(fileName, std::ios::in | std::ios::binary) };
			if (file) {
				file.close();
				std::filesystem::remove(std::filesystem::path(intf->config->GetGameDataPath()) / "Local" / fileName);
			}
			else {
				std::cerr << __FUNCTION__ << " fail: " << fileName << "\n";
			}
		}

		bool StorageImpl::FileExists(const char* fileName) {
			return std::filesystem::exists(std::filesystem::path(intf->config->GetGameDataPath()) / "Local" / fileName);
		}

		uint32_t StorageImpl::GetFileSize(const char* fileName) {
			return (uint32_t)std::filesystem::file_size(std::filesystem::path(intf->config->GetGameDataPath()) / "Local" / fileName);
		}

		uint32_t StorageImpl::GetFileTimestamp(const char* fileName) {
			return (uint32_t)(std::filesystem::last_write_time(std::filesystem::path(intf->config->GetGameDataPath()) / "Local" / fileName).time_since_epoch() / std::chrono::seconds(1));
		}

		static std::size_t number_of_files_in_directory(std::filesystem::path path) {
			using std::filesystem::directory_iterator;
			return std::distance(directory_iterator(path), directory_iterator{});
		}

		uint32_t StorageImpl::GetFileCount() {
			return (uint32_t)number_of_files_in_directory(std::filesystem::path(intf->config->GetGameDataPath()) / "Local");
		}

		const char* StorageImpl::GetFileNameByIndex(uint32_t index) {
			static thread_local char buffer[256];

			GetFileNameCopyByIndex(index, buffer, sizeof(buffer));

			return buffer;
		}

		void StorageImpl::GetFileNameCopyByIndex(uint32_t index, char* buffer, uint32_t bufferLength) {
			using std::filesystem::directory_iterator;

			directory_iterator it = directory_iterator(std::filesystem::path(intf->config->GetGameDataPath()) / "Local");
			while (index--)
			{
				it++;
			}

			std::string path = it->path().string();

			std::copy_n(path.c_str(), std::min((size_t)bufferLength, path.length()), buffer);
		}

		void StorageImpl::FileShare(const char* fileName, IFileShareListener* const listener) {

		}

		void StorageImpl::DownloadSharedFile(SharedFileID sharedFileID, ISharedFileDownloadListener* const listener) {

		}

		const char* StorageImpl::GetSharedFileName(SharedFileID sharedFileID) {
			return "";
		}

		void StorageImpl::GetSharedFileNameCopy(SharedFileID sharedFileID, char* buffer, uint32_t bufferLength) {

		}

		uint32_t StorageImpl::GetSharedFileSize(SharedFileID sharedFileID) {
			return 0;
		}

		GalaxyID StorageImpl::GetSharedFileOwner(SharedFileID sharedFileID) {
			return 0;
		}

		uint32_t StorageImpl::SharedFileRead(SharedFileID sharedFileID, void* data, uint32_t dataSize, uint32_t offset) {
			return 0;
		}

		void StorageImpl::SharedFileClose(SharedFileID sharedFileID) {

		}

		uint32_t StorageImpl::GetDownloadedSharedFileCount() {
			return 0;
		}

		SharedFileID StorageImpl::GetDownloadedSharedFileByIndex(uint32_t index) {
			return 0;
		}
	}
}


