#ifndef GALAXY_I_CLOUDSTORAGE_H
#define GALAXY_I_CLOUDSTORAGE_H

/**
 * @file
 * Contains data structures and interfaces related to cross-platform cloud storage activities.
 */

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
		 * Listener for the event of downloading a list of files stored in cloud storage.
		 */
		class ICloudStorageGetFileListListener : public GalaxyTypeAwareListener<CLOUD_STORAGE_GET_FILE_LIST>
		{
		public:

			/**
			 * Notification for the event of a success in downloading a list of files.
			 * 
			 * In order to read subsequent files' info call ICloudStorage::GetFile*ByIndex().
			 *
			 * @param [in] fileCount File count on the list.
			 * @param [in] quota Total quota bytes.
			 * @param [in] quota Used quota.
			 *
			 * @remark File info data is available at the time this notification comes.
			 */
			virtual void OnGetFileListSuccess(uint32_t fileCount, uint32_t quota, uint32_t quotaUsed) = 0;

			/**
			 * The reason of a failure in downloading a list of files.
			 */
			enum FailureReason
			{
				FAILURE_REASON_UNDEFINED, ///< Unspecified error.
				FAILURE_REASON_UNAUTHORIZED, ///< Authorization lost.
				FAILURE_REASON_FORBIDDEN, ///< No access to specified container.
				FAILURE_REASON_NOT_FOUND, ///< Container not found.
				FAILURE_REASON_UNAVAILABLE, ///< Service unavailable.
				FAILURE_REASON_ABORTED, ///< Request aborted.
				FAILURE_REASON_CONNECTION_FAILURE ///< Unable to communicate with backend services.
			};

			/**
			 * Notification for the event of a failure in downloading a list of files.
			 *
			 * @param [in] failureReason The cause of the failure.
			 */
			virtual void OnGetFileListFailure(FailureReason failureReason) = 0;
		};

		/**
		 * Listener for the event of downloading a file stored in cloud storage.
		 */
		class ICloudStorageGetFileListener : public GalaxyTypeAwareListener<CLOUD_STORAGE_GET_FILE>
		{
		public:

			/**
			 * Notification for the event of a success in downloading a file.
			 *
			 * In order to read metadata of downloaded file call
			 * ICloudStorage::GetFileMetadataKeyByIndex()/ICloudStorage::GetFileMetadataValueByIndex().
			 * 
			 * @param [in] container The name of the containter.
			 * @param [in] name The name of the file downloaded.
			 * @param [in] fileSize The size of downloaded data.
			 * @param [in] metadataKeys The array of tags names, ends with NULL.
			 * @param [in] metadataCount The number of metadata pairs (tag/value) for downloaded file.
			 */
			virtual void OnGetFileSuccess(
				const char* container,
				const char* name,
				uint32_t fileSize,
				uint32_t metadataCount
			) = 0;

			/**
			 * The reason of a failure in downloading a file.
			 */
			enum FailureReason
			{
				FAILURE_REASON_UNDEFINED, ///< Unspecified error.
				FAILURE_REASON_CONNECTION_FAILURE, ///< Unable to communicate with backend services.
				FAILURE_REASON_NOT_FOUND, ///< File not found.
				FAILURE_REASON_BUFFER_TOO_SMALL, ///< Buffer passed to ICloudStorage::GetFile() is too small to fit the file content.
				FAILURE_REASON_WRITE_FUNC_ERROR ///< Function writeFunc passed to ICloudStorage::GetFile() returned an error.
			};

			/**
			 * Notification for the event of a failure in downloading a file.
			 *
			 * @param [in] container The name of the containter.
			 * @param [in] name The name of the file to be downloaded.
			 * @param [in] failureReason The cause of the failure.
			 */
			virtual void OnGetFileFailure(const char* container, const char* name, FailureReason failureReason) = 0;
		};

		/**
		 * Listener for the event of uploading a local file to the cloud storage.
		 */
		class ICloudStoragePutFileListener : public GalaxyTypeAwareListener<CLOUD_STORAGE_PUT_FILE>
		{
		public:

			/**
			 * Notification for the event of a success in uploading a file.
			 *
			 * @param [in] container The name of the containter.
			 * @param [in] name The name of the file uploaded.
			 */
			virtual void OnPutFileSuccess(const char* container, const char* name) = 0;

			/**
			 * The reason of a failure in uploading a file.
			 */
			enum FailureReason
			{
				FAILURE_REASON_UNDEFINED, ///< Unspecified error.
				FAILURE_REASON_CONNECTION_FAILURE, ///< Unable to communicate with backend services.
				FAILURE_REASON_READ_FUNC_ERROR, ///< Function readFunc passed to ICloudStorage::PutFile() returned an error.
				FAILURE_REASON_QUOTA_EXCEEDED ///< Unable to upload the file because there is no free space on cloud storage.
			};

			/**
			 * Notification for the event of a failure in uploading a file.
			 *
			 * @param [in] container The name of the containter.
			 * @param [in] name The name of the file to be uploaded.
			 * @param [in] failureReason The cause of the failure.
			 */
			virtual void OnPutFileFailure(const char* container, const char* name, FailureReason failureReason) = 0;

		};

		/**
		 * Listener for the event of deleting a file stored in cloud storage.
		 */
		class ICloudStorageDeleteFileListener : public GalaxyTypeAwareListener<CLOUD_STORAGE_DELETE_FILE>
		{
		public:

			/**
			 * Notification for the event of a success in deleting a file.
			 *
			 * @param [in] container The name of the containter.
			 * @param [in] name The name of the deleted file.
			 */
			virtual void OnDeleteFileSuccess(const char* container, const char* name) = 0;

			/**
			 * The reason of a failure in deleting a file.
			 */
			enum FailureReason
			{
				FAILURE_REASON_UNDEFINED, ///< Unspecified error.
				FAILURE_REASON_CONNECTION_FAILURE ///< Unable to communicate with backend services.
			};

			/**
			 * Notification for the event of a failure in deleting a file.
			 *
			 * @param [in] container The name of the containter.
			 * @param [in] name The name of the file to be deleted.
			 */
			virtual void OnDeleteFileFailure(const char* container, const char* name, FailureReason failureReason) = 0;
		};

		/**
		 * The interface for cross-platform CloudStorage file management.
		 */
		class ICloudStorage
		{
		public:
		
			virtual ~ICloudStorage() {}

			/**
			 * Function used to get a list of files stored in cloud storage.
			 *
			 * This call is asynchronous. Responses come to the ICloudStorageGetFileListListener.
			 *
			 * @param [in] container The name of the containter.
			 * @param [in] listener The listener for specific operation.
			 */
			virtual void GetFileList(const char* container, ICloudStorageGetFileListListener* listener) = 0;

			/**
			 * Function used to get file name from retrieved list of files stored in cloud storage.
			 * 
			 * Call for this function is allowed inside ICloudStorageGetFileListListener::OnGetFileListSuccess() only.
			 * 
			 * @param [in] index Index of the file on list.
			 * @return Name of the file. This pointer is valid inside ICloudStorageGetFileListListener::OnGetFileListSuccess() only.
			 */
			virtual const char* GetFileNameByIndex(uint32_t index) const = 0;

			/**
			 * Function used to get file size from retrieved list of files stored in cloud storage.
			 *
			 * Call for this function is allowed inside ICloudStorageGetFileListListener::OnGetFileListSuccess() only.
			 *
			 * @param [in] index Index of the file on list.
			 * @return Size of the file.
			 */
			virtual uint32_t GetFileSizeByIndex(uint32_t index) const = 0;

			/**
			 * Function used to get file timestamp from retrieved list of files stored in cloud storage.
			 *
			 * Call for this function is allowed inside ICloudStorageGetFileListListener::OnGetFileListSuccess() only.
			 *
			 * @param [in] index Index of the file on list.
			 * @return Time stamp of the file (Unix timestamp).
			 */
			virtual uint32_t GetFileTimestampByIndex(uint32_t index) const = 0;

			/**
			 * Function used to write the downloaded data.
			 *
			 * @param [in] userParam The parameter passed to the GetFile() method.
			 * @param [in] data The downloaded data to be written.
			 * @param [in] size The size of the downloaded data to be written.
			 * @return Number of bytes written; a negative value indicates an error.
			 */
			typedef int (*WriteFunc)(void* userParam, char* data, int size);

			/**
			 * Download a file from cloud storage
			 *
			 * This call is asynchronous. Responses come to the ICloudStorageGetFileListener.
			 *
			 * This version of the GetFile method uses (userParam, writeFunc) parameters
			 * as an abstraction of a data sink for the downloaded data. writeFunc will be
			 * called with userParam passed to the method along with the data to be written.
			 *
			 * @param [in] container The name of the containter.
			 * @param [in] name The name of the file in cloud storage.
			 * @param [in] userParam The parameter passed to writeFunc on every call.
			 * @param [in] writeFunc The function called for chunks of the downloaded data.
			 * @param [in] listener The listener for specific operation.
			 */
			virtual void GetFile(const char* container, const char* name, void* userParam, WriteFunc writeFunc, ICloudStorageGetFileListener* listener) = 0;

			/**
			 * Download a file from cloud storage
			 *
			 * This call is asynchronous. Responses come to the ICloudStorageGetFileListener.
			 *
			 * This version of the GetFile method uses the buffer and bufferLength parameters to store the downloaded data.
			 * The buffer should be big enough to fit the whole file. Required size can be obtained by GetFileList().
			 *
			 * Caller is responsible for setting up a lifetime for the buffer: it should be accessible until
			 * the operation is finished (any of the listener methods is called).
			 *
			 * @param [in] container The name of the containter.
			 * @param [in] name The name of the file in cloud storage.
			 * @param [in] buffer The buffer for the downloaded data.
			 * @param [in] bufferLength The size of the buffer for the downloaded data.
			 * @param [in] listener The listener for the specific operation.
			 */
			virtual void GetFile(const char* container, const char* name, void* buffer, uint32_t bufferLength, ICloudStorageGetFileListener* listener) = 0;

			/**
			 * Get a file metadata from cloud storage
			 *
			 * This call is asynchronous. Responses come to the ICloudStorageGetFileListener.
			 *
			 * This method gets metadata for specified file only.
			 *
			 * @param [in] container The name of the containter.
			 * @param [in] name The name of the file in cloud storage.
			 * @param [in] listener The listener for specific operation.
			 */
			virtual void GetFileMetadata(const char* container, const char* name, ICloudStorageGetFileListener* listener) = 0;

			/**
			 * Function used to get metadata key of retrieved file.
			 * 
			 * Call for this function is allowed inside ICloudStorageGetFileListListener::OnGetFileSuccess() only.
			 * 
			 * @param [in] index Index of the metadata key.
			 * @return Metadata key.
			 */
			virtual const char* GetFileMetadataKeyByIndex(uint32_t index) const = 0;

			/**
			 * Function used to get metadata value of retrieved file.
			 *
			 * Call for this function is allowed inside ICloudStorageGetFileListListener::OnGetFileSuccess() only.
			 *
			 * @param [in] index Index of the metadata value.
			 * @return Metadata value.
			 */
			virtual const char* GetFileMetadataValueByIndex(uint32_t index) const = 0;

			/**
			 * Function used to read the data to be uploaded.
			 *
			 * @param [in] userParam The parameter passed to the PutFile() method.
			 * @param [in] data The buffer for the data read.
			 * @param [in] size The size of the buffer for data.
			 * @return Number of bytes read: 0 (for size > 0) means end-of-data (no more data to read); a negative value indicates an error.
			 */
			typedef int (*ReadFunc)(void* userParam, const char* data, int size);

			/**
			 * The phase of reading data to be uploaded.
			 */
			enum ReadPhase
			{
				CHECKSUM_CALCULATING, ///< Checksum calculating phase.
				UPLOADING ///< Uploading phase.
			};

			/**
			 * Function used to restart read data process.
			 */
			typedef int (*RewindFunc)(void* userParam, ReadPhase phase);

			/**
			 * Upload a file to the cloud storage
			 *
			 * This call is asynchronous. Responses come to the ICloudStoragePutFileListener.
			 *
			 * This version of the PutFile method uses (userParam, readFunc) parameters
			 * as an abstraction of a data source for the uploaded data. readFunc will be
			 * called with userParam passed to the method along with the buffer for the data to be read.
			 * rewindFunc will be called on start reading data phase and should set the read pointer at 
			 * the begining of the data stream.
			 * 
			 * metadataKeys and metadataValues are opitonal, may by NULL if there are no tags to add.
			 * If present the size of both arrays should be equal and the last elements should be NULL.
			 *
			 * @param [in] container The name of the containter.
			 * @param [in] name The name of the file in cloud storage.
			 * @param [in] userParam The parameter passed to readFunc on every call.
			 * @param [in] readFunc The function called to obtain data chunks for upload.
			 * @param [in] rewindFunc The function called to rewind read pointer to the begining of the data stream.
			 * @param [in] listener The listener for the specific operation.
			 * @param [in] metadataKeys The array of tags names, ends with NULL.
			 * @param [in] metadataValues The array of tags values, ends with NULL. The size is equal to metadataKeys' size.
			 */
			virtual void PutFile(
				const char* container, 
				const char* name, 
				void* userParam, 
				ReadFunc readFunc, 
				RewindFunc rewindFunc, 
				ICloudStoragePutFileListener* listener,
				const char* const* metadataKeys = NULL,
				const char* const* metadataValues = NULL
			) = 0;

			/**
			 * Upload a file to the cloud storage
			 *
			 * This call is asynchronous. Responses come to the ICloudStoragePutFileListener.
			 *
			 * This version of the PutFile method uploads the data pointed by the buffer parameter, 
			 * where bufferLength indicates the file length.
			 * 
			 * Caller is responsible for setting up a lifetime for the buffer: it should be accessible until
			 * the operation is finished (any of the listener methods is called).
			 *
			 * metadataKeys and metadataValues are opitonal, may by NULL if there are no tags to add.
			 * If present the size of both arrays should be equal and the last elements should be NULL.
			 *
			 * @param [in] container The name of the containter.
			 * @param [in] name The name of the file in cloud storage.
			 * @param [out] data The buffer for the data to be read.
			 * @param [in] size The size of the buffer for the data.
			 * @param [in] listener The listener for the specific operation.
			 * @param [in] metadataKeys The array of tags names, ends with NULL.
			 * @param [in] metadataValues The array of tags values, ends with NULL. The size is equal to metadataKeys' size.
			 */
			virtual void PutFile(
				const char* container, 
				const char* name, 
				const void* buffer,
				uint32_t bufferLength, 
				ICloudStoragePutFileListener* listener,
				const char* const* metadataKeys = NULL,
				const char* const* metadataValues = NULL
			) = 0;

			/**
			 * Delete a file from cloud storage
			 *
			 * This call is asynchronous. Responses come to the ICloudStorageDeleteFileListener.
			 *
			 * @param [in] container The name of the containter.
			 * @param [in] name The name of the file in cloud storage.
			 * @param [in] listener The listener for the specific operation.
			 */
			virtual void DeleteFile(const char* container, const char* name, ICloudStorageDeleteFileListener* listener) = 0;

		};

		/** @} */
	}
}
#endif
