#include "Storage.hxx"

namespace galaxy
{
	namespace api
	{
		Storage::~Storage()
		{
		}

		void Storage::FileWrite(const char* fileName, const void* data, uint32_t dataSize) {

		}

		uint32_t Storage::FileRead(const char* fileName, void* data, uint32_t dataSize) {
			return 0;
		}

		void Storage::FileDelete(const char* fileName) {

		}

		bool Storage::FileExists(const char* fileName) {
			return false;
		}

		uint32_t Storage::GetFileSize(const char* fileName) {
			return 0;
		}

		uint32_t Storage::GetFileTimestamp(const char* fileName) {
			return 0;
		}

		uint32_t Storage::GetFileCount() {
			return 0;
		}

		const char* Storage::GetFileNameByIndex(uint32_t index) {
			return "";
		}

		void Storage::GetFileNameCopyByIndex(uint32_t index, char* buffer, uint32_t bufferLength) {

		}

		void Storage::FileShare(const char* fileName, IFileShareListener* const listener) {

		}

		void Storage::DownloadSharedFile(SharedFileID sharedFileID, ISharedFileDownloadListener* const listener) {

		}

		const char* Storage::GetSharedFileName(SharedFileID sharedFileID) {
			return "";
		}

		void Storage::GetSharedFileNameCopy(SharedFileID sharedFileID, char* buffer, uint32_t bufferLength) {

		}

		uint32_t Storage::GetSharedFileSize(SharedFileID sharedFileID) {
			return 0;
		}

		GalaxyID Storage::GetSharedFileOwner(SharedFileID sharedFileID) {
			return 0;
		}

		uint32_t Storage::SharedFileRead(SharedFileID sharedFileID, void* data, uint32_t dataSize, uint32_t offset) {
			return 0;
		}

		void Storage::SharedFileClose(SharedFileID sharedFileID) {

		}

		uint32_t Storage::GetDownloadedSharedFileCount() {
			return 0;
		}

		SharedFileID Storage::GetDownloadedSharedFileByIndex(uint32_t index) {
			return 0;
		}
	}
}


