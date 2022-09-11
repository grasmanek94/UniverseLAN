#include "Storage.hxx"

namespace galaxy
{
	namespace api
	{
		StorageImpl::~StorageImpl()
		{
		}

		void StorageImpl::FileWrite(const char* fileName, const void* data, uint32_t dataSize) {

		}

		uint32_t StorageImpl::FileRead(const char* fileName, void* data, uint32_t dataSize) {
			return 0;
		}

		void StorageImpl::FileDelete(const char* fileName) {

		}

		bool StorageImpl::FileExists(const char* fileName) {
			return false;
		}

		uint32_t StorageImpl::GetFileSize(const char* fileName) {
			return 0;
		}

		uint32_t StorageImpl::GetFileTimestamp(const char* fileName) {
			return 0;
		}

		uint32_t StorageImpl::GetFileCount() {
			return 0;
		}

		const char* StorageImpl::GetFileNameByIndex(uint32_t index) {
			return "";
		}

		void StorageImpl::GetFileNameCopyByIndex(uint32_t index, char* buffer, uint32_t bufferLength) {

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


