/**
 * @file
 * Contains data structures and interfaces related to storage activities.
 */

#include "IStorage.h"
#include "GalaxyID.h"
#include "IListenerRegistrar.h"

#include "Storage.hxx"

namespace galaxy
{
	namespace api
	{
		/**
		 * @addtogroup api
		 * @{
		 */

		 /**
		  * The interface for managing of cloud storage files.
		  */
		Storage::~Storage()
		{
		}

		/**
		 * Writes data into the file.
		 *
		 * @pre The name that specifies the file has to be provided in the form of a relative path that uses slashes
		 * as separators and is a valid UTF-8 string. Every part of the path must must be portable,
		 * i.e. it cannot refer to any special or restricted name on any of the supported platforms.
		 * Backslashes are not allowed. The files created using this method will be stored in GOG Galaxy internal
		 * directory and should be accessed only via Galaxy SDK methods.
		 *
		 * @param [in] fileName The name of the file in the form of a path (see the description of the method).
		 * @param [in] data The data to write.
		 * @param [in] dataSize The size of the data to write.
		 */
		void Storage::FileWrite(const char* fileName, const void* data, uint32_t dataSize) {

		}

		/**
		 * Reads file content into the buffer.
		 *
		 * @param [in] fileName The name of the file in the form of a path (see the description of FileWrite()).
		 * @param [in, out] data The output buffer.
		 * @param [in] dataSize The size of the output buffer.
		 * @return The number of bytes written to the buffer.
		 */
		uint32_t Storage::FileRead(const char* fileName, void* data, uint32_t dataSize) {
			return 0;
		}

		/**
		 * Deletes the file.
		 *
		 * @param [in] fileName The name of the file in the form of a path (see the description of FileWrite()).
		 */
		void Storage::FileDelete(const char* fileName) {

		}

		/**
		 * Returns if the file exists
		 *
		 * @param [in] fileName The name of the file in the form of a path (see the description of FileWrite()).
		 * @return If the file exist.
		 */
		bool Storage::FileExists(const char* fileName) {
			return false;
		}

		/**
		 * Returns the size of the file.
		 *
		 * @param [in] fileName The name of the file in the form of a path (see the description of FileWrite()).
		 * @return The size of the file.
		 */
		uint32_t Storage::GetFileSize(const char* fileName) {
			return 0;
		}

		/**
		 * Returns the timestamp of the last file modification.
		 *
		 * @param [in] fileName The name of the file in the form of a path (see the description of FileWrite()).
		 * @return The time of file's last modification.
		 */
		uint32_t Storage::GetFileTimestamp(const char* fileName) {
			return 0;
		}

		/**
		 * Returns number of the files in the storage.
		 *
		 * @return The number of the files in the storage.
		 */
		uint32_t Storage::GetFileCount() {
			return 0;
		}

		/**
		 * Returns name of the file.
		 *
		 * @param [in] index Index as an integer in the range of [0, number of files).
		 * @return The name of the file.
		 */
		const char* Storage::GetFileNameByIndex(uint32_t index) {
			return "";
		}

		/**
		 * Copies the name of the file to a buffer.
		 *
		 * @param [in] index Index as an integer in the range of [0, number of files).
		 * @param [in, out] buffer The output buffer.
		 * @param [in] bufferLength The size of the output buffer.
		 */
		void Storage::GetFileNameCopyByIndex(uint32_t index, char* buffer, uint32_t bufferLength) {

		}

		/**
		 * Uploads the file for sharing.
		 *
		 * This call is asynchronous. Responses come to the IFileShareListener.
		 *
		 * @param [in] fileName The name of the file in the form of a path (see the description of FileWrite()).
		 * @param [in] listener The listener for specific operation.
		 */
		void Storage::FileShare(const char* fileName, IFileShareListener* const listener) {

		}

		/**
		 * Downloads previously shared file.
		 *
		 * This call is asynchronous. Responses come to the ISharedFileDownloadListener.
		 *
		 * @param [in] sharedFileID The ID of the shared file.
		 * @param [in] listener The listener for specific operation.
		 */
		void Storage::DownloadSharedFile(SharedFileID sharedFileID, ISharedFileDownloadListener* const listener) {

		}

		/**
		 * Gets name of downloaded shared file.
		 *
		 * @pre Download the file first by calling DownloadSharedFile().
		 *
		 * @param [in] sharedFileID The ID of the shared file.
		 * @return The name of the shared file.
		 */
		const char* Storage::GetSharedFileName(SharedFileID sharedFileID) {
			return "";
		}

		/**
		 * Copies the name of downloaded shared file to a buffer.
		 *
		 * @pre Download the file first by calling DownloadSharedFile().
		 *
		 * @param [in] sharedFileID The ID of the shared file.
		 * @param [in, out] buffer The output buffer.
		 * @param [in] bufferLength The size of the output buffer.
		 */
		void Storage::GetSharedFileNameCopy(SharedFileID sharedFileID, char* buffer, uint32_t bufferLength) {

		}

		/**
		 * Gets size of downloaded shared file.
		 *
		 * @pre Download the file first by calling DownloadSharedFile().
		 *
		 * @param [in] sharedFileID The ID of the shared file.
		 * @return The size of the shared file.
		 */
		uint32_t Storage::GetSharedFileSize(SharedFileID sharedFileID) {
			return 0;
		}

		/**
		 * Gets the owner of downloaded shared file.
		 *
		 * @pre Download the file first by calling DownloadSharedFile().
		 *
		 * @param [in] sharedFileID The ID of the shared file.
		 * @return The owner of the shared file.
		 */
		GalaxyID Storage::GetSharedFileOwner(SharedFileID sharedFileID) {
			return 0;
		}

		/**
		 * Reads downloaded shared file content into the buffer.
		 *
		 * @pre Download the file first by calling DownloadSharedFile().
		 *
		 * @param [in] sharedFileID The ID of the shared file.
		 * @param [in, out] data The output buffer.
		 * @param [in] dataSize The size of the output buffer.
		 * @param [in] offset The number of bytes to skip from the beginning of the file.
		 * @return The number of bytes written to the buffer.
		 */
		uint32_t Storage::SharedFileRead(SharedFileID sharedFileID, void* data, uint32_t dataSize, uint32_t offset) {
			return 0;
		}

		/**
		 * Closes downloaded shared file and frees the memory.
		 *
		 * The content of the file will not be available until next download.
		 *
		 * @pre Download the file first by calling DownloadSharedFile().
		 *
		 * @param [in] sharedFileID The ID of the shared file.
		 */
		void Storage::SharedFileClose(SharedFileID sharedFileID) {

		}

		/**
		 * Returns the number of open downloaded shared files.
		 *
		 * @return The number of open downloaded shared files.
		 */
		uint32_t Storage::GetDownloadedSharedFileCount() {
			return 0;
		}

		/**
		 * Returns the ID of the open downloaded shared file.
		 *
		 * @param [in] index Index as an integer in the range of [0, number of open downloaded shared files).
		 * @return The ID of the shared file.
		 */
		SharedFileID Storage::GetDownloadedSharedFileByIndex(uint32_t index) {
			return 0;
		}

		/** @} */
	}
}


