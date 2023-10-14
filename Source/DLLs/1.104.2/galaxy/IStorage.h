#ifndef GALAXY_I_STORAGE_H
#define GALAXY_I_STORAGE_H

/**
 * @file
 * Contains data structures and interfaces related to storage activities
 */

#include "GalaxyID.h"
#include "IListenerRegistrar.h"

namespace galaxy
{
	namespace api
	{
		/**
		 * @addtogroup api
		 * @{
		 */

		/**
		 * ID of a shared file.
		 */
		typedef uint64_t SharedFileID;

		/**
		 * Listener for the event of sharing a file.
		 */
		class IFileShareListener : public GalaxyTypeAwareListener<FILE_SHARE>
		{
		public:

			/**
			 * Notification for the event of a success in sharing a file.
			 *
			 * @param fileName The name of the file in the form of a path (see the description of IStorage::FileWrite()).
			 * @param sharedFileID The ID of the file.
			 */
			virtual void OnFileShareSuccess(const char* fileName, SharedFileID sharedFileID) = 0;

			/**
			 * The reason of a failure in sharing a file.
			 */
			enum FailureReason
			{
				FAILURE_REASON_UNDEFINED ///< Unspecified error.
			};

			/**
			 * Notification for the event of a failure in sharing a file.
			 *
			 * @param fileName The name of the file in the form of a path (see the description of IStorage::FileWrite()).
			 * @param failureReason The cause of the failure.
			 */
			virtual void OnFileShareFailure(const char* fileName, FailureReason failureReason) = 0;
		};

		/**
		 * Globally self-registering version of IFileShareListener.
		 */
		typedef SelfRegisteringListener<IFileShareListener> GlobalFileShareListener;

		/**
		 * Listener for the event of downloading a shared file.
		 */
		class ISharedFileDownloadListener : public GalaxyTypeAwareListener<SHARED_FILE_DOWNLOAD>
		{
		public:

			/**
			 * Notification for the event of a success in downloading a shared file.
			 *
			 * @param sharedFileID The ID of the file.
			 * @param fileName The name of the file in the form of a path (see the description of IStorage::FileWrite()).
			 */
			virtual void OnSharedFileDownloadSuccess(SharedFileID sharedFileID, const char* fileName) = 0;

			/**
			 * The reason of a failure in downloading a shared file.
			 */
			enum FailureReason
			{
				FAILURE_REASON_UNDEFINED ///< Unspecified error.
			};

			/**
			 * Notification for the event of a failure in downloading a shared file.
			 *
			 * @param sharedFileID The ID of the file.
			 * @param failureReason The cause of the failure.
			 */
			virtual void OnSharedFileDownloadFailure(SharedFileID sharedFileID, FailureReason failureReason) = 0;
		};

		/**
		 * Globally self-registering version of ISharedFileDownloadListener.
		 */
		typedef SelfRegisteringListener<ISharedFileDownloadListener> GlobalSharedFileDownloadListener;

		/**
		 * The interface for managing of cloud storage files.
		 */
		class IStorage
		{
		public:

			virtual ~IStorage()
			{
			}

			/**
			 * Writes data into the file.
			 *
			 * @remark The name that specifies the file can be provided in the form of a path that uses slashes
			 * as separators and is a valid UTF-8 string. Every part of the path must must be portable,
			 * i.e. it cannot refer to any special or restricted name on any of the supported platforms.
			 * Backslashes are not allowed.
			 *
			 * @param fileName The name of the file in the form of a path (see the description of the method).
			 * @param data The data to write.
			 * @param dataSize The size of the data to write.
			 */
			virtual void FileWrite(const char* fileName, const void* data, uint32_t dataSize) = 0;

			/**
			 * Reads file content into the buffer.
			 *
			 * @param fileName The name of the file in the form of a path (see the description of FileWrite()).
			 * @param data The output buffer.
			 * @param dataSize The size of the output buffer.
			 * @return The number of bytes written to the buffer.
			 */
			virtual uint32_t FileRead(const char* fileName, void* data, uint32_t dataSize) = 0;

			/**
			 * Deletes the file.
			 *
			 * @param fileName The name of the file in the form of a path (see the description of FileWrite()).
			 */
			virtual void FileDelete(const char* fileName) = 0;

			/**
			 * Returns if the file exists
			 *
			 * @param fileName The name of the file in the form of a path (see the description of FileWrite()).
			 * @return If the file exist.
			 */
			virtual bool FileExists(const char* fileName) = 0;

			/**
			 * Returns the size of the file.
			 *
			 * @param fileName The name of the file in the form of a path (see the description of FileWrite()).
			 * @return The size of the file.
			 */
			virtual uint32_t GetFileSize(const char* fileName) = 0;

			/**
			 * Returns the timestamp of the last file modification.
			 *
			 * @param fileName The name of the file in the form of a path (see the description of FileWrite()).
			 * @return The time of file's last modification.
			 */
			virtual uint32_t GetFileTimestamp(const char* fileName) = 0;

			/**
			 * Returns number of the files in the storage.
			 *
			 * @return The number of the files in the storage.
			 */
			virtual uint32_t GetFileCount() = 0;

			/**
			 * Returns name of the file.
			 *
			 * @param index Index as an integer in the range of [0, number of files).
			 * @return The name of the file.
			 */
			virtual const char* GetFileNameByIndex(uint32_t index) = 0;

			/**
			 * Copies the name of the file to a buffer.
			 *
			 * @param index Index as an integer in the range of [0, number of files).
			 * @param buffer The output buffer.
			 * @param bufferLength The size of the output buffer.
			 */
			virtual void GetFileNameCopyByIndex(uint32_t index, char* buffer, uint32_t bufferLength) = 0;

			/**
			 * Uploads the file for sharing.
			 *
			 * This call is asynchronous. Responses come to the IFileShareListener.
			 *
			 * @param fileName The name of the file in the form of a path (see the description of FileWrite()).
			 */
			virtual void FileShare(const char* fileName) = 0;

			/**
 			 * Downloads previously shared file.
			 *
			 * This call is asynchronous. Responses come to the ISharedFileDownloadListener.
			 *
			 * @param sharedFileID The ID of the shared file.
			 */
			virtual void DownloadSharedFile(SharedFileID sharedFileID) = 0;

			/**
			 * Gets name of downloaded shared file.
			 *
			 * @remark Download the file first by calling DownloadSharedFile().
			 *
			 * @param sharedFileID The ID of the shared file.
			 * @return The name of the shared file.
			 */
			virtual const char* GetSharedFileName(SharedFileID sharedFileID) = 0;

			/**
			 * Copies the name of downloaded shared file to a buffer.
			 *
			 * @remark Download the file first by calling DownloadSharedFile().
			 *
			 * @param sharedFileID The ID of the shared file.
			 * @param buffer The output buffer.
			 * @param bufferLength The size of the output buffer.
			 */
			virtual void GetSharedFileNameCopy(SharedFileID sharedFileID, char* buffer, uint32_t bufferLength) = 0;

			/**
			 * Gets size of downloaded shared file.
			 *
			 * @remark Download the file first by calling DownloadSharedFile().
			 *
			 * @param sharedFileID The ID of the shared file.
			 * @return The size of the shared file.
			 */
			virtual uint32_t GetSharedFileSize(SharedFileID sharedFileID) = 0;

			/**
			 * Gets the owner of downloaded shared file.
			 *
			 * @remark Download the file first by calling DownloadSharedFile().
			 *
			 * @param sharedFileID The ID of the shared file.
			 * @return The owner of the shared file.
			 */
			virtual GalaxyID GetSharedFileOwner(SharedFileID sharedFileID) = 0;

			/**
			 * Reads downloaded shared file content into the buffer.
			 *
			 * @remark Download the file first by calling DownloadSharedFile().
			 *
			 * @param sharedFileID The ID of the shared file.
			 * @param data The output buffer.
			 * @param dataSize The size of the output buffer.
			 * @param offset The number of bytes to skip from the beginning of the file.
			 * @return The number of bytes written to the buffer.
			 */
			virtual uint32_t SharedFileRead(SharedFileID sharedFileID, void* data, uint32_t dataSize, uint32_t offset = 0) = 0;

			/**
			 * Closes downloaded shared file and frees the memory.
			 *
			 * The content of the file will not be available until next download.
			 *
			 * @remark Download the file first by calling DownloadSharedFile().
			 *
			 * @param sharedFileID The ID of the shared file.
			 */
			virtual void SharedFileClose(SharedFileID sharedFileID) = 0;

			/**
		 	 * Returns the number of open downloaded shared files.
			 *
 			 * @return The number of open downloaded shared files.
			 */
			virtual uint32_t GetDownloadedSharedFileCount() = 0;

			/**
			 * Returns the ID of the open downloaded shared file.
			 *
			 * @param index Index as an integer in the range of [0, number of open downloaded shared files).
			 * @return The ID of the shared file.
			 */
			virtual SharedFileID GetDownloadedSharedFileByIndex(uint32_t index) = 0;
		};

		/** @} */
		}
	}

#endif
