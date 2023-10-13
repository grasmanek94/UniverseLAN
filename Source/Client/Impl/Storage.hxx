#pragma once

#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE

/**
 * @file
 * Contains data structures and interfaces related to storage activities.
 */

#include "ListenerRegistrar.hxx"

#include <Networking/Messages/FileRequestMessage.hxx>
#include <Networking/Messages/FileShareMessage.hxx>
#include <Networking/Messages/FileShareResponseMessage.hxx>
#include <SharedFileUtils.hxx>

#include <IStorage.h>
#include <GalaxyID.h>
#include <IListenerRegistrar.h>

namespace universelan::client {
	using namespace galaxy::api;
	struct InterfaceInstances;

	/**
	 * @addtogroup api
	 * @{
	 */

	 /**
	  * The interface for managing of cloud storage files.
	  */
	class StorageImpl : public IStorage
	{
	private:
		InterfaceInstances* intf;
		ListenerRegistrarImpl* listeners;

#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
		ListenersRequestHelper<IFileShareListener*> file_upload_requests;
		ListenersRequestHelper<ISharedFileDownloadListener*> file_download_requests;
#endif

		SharedFileUtils sfu;
	public:
		StorageImpl(InterfaceInstances* intf);
		virtual ~StorageImpl();

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
		virtual void FileWrite(const char* fileName, const void* data, uint32_t dataSize) override;

		/**
		 * Reads file content into the buffer.
		 *
		 * @param [in] fileName The name of the file in the form of a path (see the description of FileWrite()).
		 * @param [in, out] data The output buffer.
		 * @param [in] dataSize The size of the output buffer.
		 * @return The number of bytes written to the buffer.
		 */
		virtual uint32_t FileRead(const char* fileName, void* data, uint32_t dataSize) override;

		/**
		 * Deletes the file.
		 *
		 * @param [in] fileName The name of the file in the form of a path (see the description of FileWrite()).
		 */
		virtual void FileDelete(const char* fileName) override;

		/**
		 * Returns if the file exists
		 *
		 * @param [in] fileName The name of the file in the form of a path (see the description of FileWrite()).
		 * @return If the file exist.
		 */
		virtual bool FileExists(const char* fileName) override;

		/**
		 * Returns the size of the file.
		 *
		 * @param [in] fileName The name of the file in the form of a path (see the description of FileWrite()).
		 * @return The size of the file.
		 */
		virtual uint32_t GetFileSize(const char* fileName) override;

		/**
		 * Returns the timestamp of the last file modification.
		 *
		 * @param [in] fileName The name of the file in the form of a path (see the description of FileWrite()).
		 * @return The time of file's last modification.
		 */
		virtual uint32_t GetFileTimestamp(const char* fileName) override;

		/**
		 * Returns number of the files in the storage.
		 *
		 * @return The number of the files in the storage.
		 */
		virtual uint32_t GetFileCount() override;

		/**
		 * Returns name of the file.
		 *
		 * @param [in] index Index as an integer in the range of [0, number of files).
		 * @return The name of the file.
		 */
		virtual const char* GetFileNameByIndex(uint32_t index) override;

		/**
		 * Copies the name of the file to a buffer.
		 *
		 * @param [in] index Index as an integer in the range of [0, number of files).
		 * @param [in, out] buffer The output buffer.
		 * @param [in] bufferLength The size of the output buffer.
		 */
		virtual void GetFileNameCopyByIndex(uint32_t index, char* buffer, uint32_t bufferLength) override;

		/**
		 * Uploads the file for sharing.
		 *
		 * This call is asynchronous. Responses come to the IFileShareListener.
		 *
		 * @param [in] fileName The name of the file in the form of a path (see the description of FileWrite()).
		 * @param [in] listener The listener for specific operation.
		 */
		virtual void FileShare(const char* fileName
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
			, IFileShareListener* const listener = NULL
#endif
		) override;

		/**
		 * Downloads previously shared file.
		 *
		 * This call is asynchronous. Responses come to the ISharedFileDownloadListener.
		 *
		 * @param [in] sharedFileID The ID of the shared file.
		 * @param [in] listener The listener for specific operation.
		 */
		virtual void DownloadSharedFile(SharedFileID sharedFileID
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
			, ISharedFileDownloadListener* const listener = NULL
#endif
		) override;

		/**
		 * Gets name of downloaded shared file.
		 *
		 * @pre Download the file first by calling DownloadSharedFile().
		 *
		 * @param [in] sharedFileID The ID of the shared file.
		 * @return The name of the shared file.
		 */
		virtual const char* GetSharedFileName(SharedFileID sharedFileID) override;

		/**
		 * Copies the name of downloaded shared file to a buffer.
		 *
		 * @pre Download the file first by calling DownloadSharedFile().
		 *
		 * @param [in] sharedFileID The ID of the shared file.
		 * @param [in, out] buffer The output buffer.
		 * @param [in] bufferLength The size of the output buffer.
		 */
		virtual void GetSharedFileNameCopy(SharedFileID sharedFileID, char* buffer, uint32_t bufferLength) override;

		/**
		 * Gets size of downloaded shared file.
		 *
		 * @pre Download the file first by calling DownloadSharedFile().
		 *
		 * @param [in] sharedFileID The ID of the shared file.
		 * @return The size of the shared file.
		 */
		virtual uint32_t GetSharedFileSize(SharedFileID sharedFileID) override;

		/**
		 * Gets the owner of downloaded shared file.
		 *
		 * @pre Download the file first by calling DownloadSharedFile().
		 *
		 * @param [in] sharedFileID The ID of the shared file.
		 * @return The owner of the shared file.
		 */
		virtual GalaxyID GetSharedFileOwner(SharedFileID sharedFileID) override;

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
		virtual uint32_t SharedFileRead(SharedFileID sharedFileID, void* data, uint32_t dataSize, uint32_t offset = 0) override;

		/**
		 * Closes downloaded shared file and frees the memory.
		 *
		 * The content of the file will not be available until next download.
		 *
		 * @pre Download the file first by calling DownloadSharedFile().
		 *
		 * @param [in] sharedFileID The ID of the shared file.
		 */
		virtual void SharedFileClose(SharedFileID sharedFileID) override;

		/**
		 * Returns the number of open downloaded shared files.
		 *
		 * @return The number of open downloaded shared files.
		 */
		virtual uint32_t GetDownloadedSharedFileCount() override;

		/**
		 * Returns the ID of the open downloaded shared file.
		 *
		 * @param [in] index Index as an integer in the range of [0, number of open downloaded shared files).
		 * @return The ID of the shared file.
		 */
		virtual SharedFileID GetDownloadedSharedFileByIndex(uint32_t index) override;

		virtual void FileDownloaded(const std::shared_ptr<FileRequestMessage>& data);
		virtual void FileUploaded(const std::shared_ptr<FileShareResponseMessage>& data);
	};

	/** @} */
}

#endif
