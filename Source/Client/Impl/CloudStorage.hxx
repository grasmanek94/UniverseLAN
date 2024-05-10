#pragma once

#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE

/**
 * @file
 * Contains data structures and interfaces related to storage activities.
 */

#include "ListenerRegistrar.hxx"

//#include <Networking/Messages/FileRequestMessage.hxx>
//#include <Networking/Messages/FileShareMessage.hxx>
//#include <Networking/Messages/FileShareResponseMessage.hxx>
#include <filesystem_container/filesystem_container.hxx>
#include <SharedFileUtils.hxx>

#include <ICloudStorage.h>
#include <GalaxyID.h>
#include <IListenerRegistrar.h>

#include <string>
#include <vector>

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
	class CloudStorageImpl : public ICloudStorage
	{
	private:
		InterfaceInstances* intf;
		ListenerRegistrarImpl* listeners;

		SharedFileUtils* sfu;
		std::string last_container;
		filesystem_container::fs_container_ptr last_subcontainer_ref;

		filesystem_container::fs_filelist_contrainer_t container_file_list;
		filesystem_container::file_entry_metadata_vector_t last_metadata_request;

	public:
		CloudStorageImpl(InterfaceInstances* intf);
		virtual ~CloudStorageImpl();


		/**
		 * Function used to get a list of files stored in cloud storage.
		 *
		 * This call is asynchronous. Responses come to the ICloudStorageGetFileListListener.
		 *
		 * @param [in] container The name of the containter.
		 * @param [in] listener The listener for specific operation.
		 */
		virtual void GetFileList(const char* container, ICloudStorageGetFileListListener* listener) override;

		/**
		 * Function used to get file name from retrieved list of files stored in cloud storage.
		 *
		 * Call for this function is allowed inside ICloudStorageGetFileListListener::OnGetFileListSuccess() only.
		 *
		 * @param [in] index Index of the file on list.
		 * @return Name of the file. This pointer is valid inside ICloudStorageGetFileListListener::OnGetFileListSuccess() only.
		 */
		virtual const char* GetFileNameByIndex(uint32_t index) const  override;

		/**
		 * Function used to get file size from retrieved list of files stored in cloud storage.
		 *
		 * Call for this function is allowed inside ICloudStorageGetFileListListener::OnGetFileListSuccess() only.
		 *
		 * @param [in] index Index of the file on list.
		 * @return Size of the file.
		 */
		virtual uint32_t GetFileSizeByIndex(uint32_t index) const override;

		/**
		 * Function used to get file timestamp from retrieved list of files stored in cloud storage.
		 *
		 * Call for this function is allowed inside ICloudStorageGetFileListListener::OnGetFileListSuccess() only.
		 *
		 * @param [in] index Index of the file on list.
		 * @return Time stamp of the file (Unix timestamp).
		 */
		virtual uint32_t GetFileTimestampByIndex(uint32_t index) const override;

#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE_GETFILEHASHBYINDEX
		/**
		 * Function used to get a file hash from the retrieved list of files stored in cloud storage.
		 *
		 * Call for this function is allowed inside ICloudStorageGetFileListListener::OnGetFileListSuccess() only.
		 *
		 * @param [in] index Index of the file on the list.
		 * @return Hash of the file (as hexadecimal string).
		 */
		virtual const char* GetFileHashByIndex(uint32_t index) const override;
#endif

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
		virtual void GetFile(const char* container, const char* name, void* userParam, WriteFunc writeFunc, ICloudStorageGetFileListener* listener) override;

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
		virtual void GetFile(const char* container, const char* name, void* buffer, uint32_t bufferLength, ICloudStorageGetFileListener* listener) override;

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
		virtual void GetFileMetadata(const char* container, const char* name, ICloudStorageGetFileListener* listener) override;

		/**
		 * Function used to get metadata key of retrieved file.
		 *
		 * Call for this function is allowed inside ICloudStorageGetFileListListener::OnGetFileSuccess() only.
		 *
		 * @param [in] index Index of the metadata key.
		 * @return Metadata key.
		 */
		virtual const char* GetFileMetadataKeyByIndex(uint32_t index) const override;

		/**
		 * Function used to get metadata value of retrieved file.
		 *
		 * Call for this function is allowed inside ICloudStorageGetFileListListener::OnGetFileSuccess() only.
		 *
		 * @param [in] index Index of the metadata value.
		 * @return Metadata value.
		 */
		virtual const char* GetFileMetadataValueByIndex(uint32_t index) const override;

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
		)
#if !GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE_PUTFILE_TIMESTAMP
			override
#endif
			;

		virtual void PutFile(
			const char* container,
			const char* name,
			void* userParam,
			ReadFunc readFunc,
			RewindFunc rewindFunc,
			ICloudStoragePutFileListener* listener,
			const char* const* metadataKeys,
			const char* const* metadataValues,
			uint32_t timeStamp
		)
#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE_PUTFILE_TIMESTAMP
			override
#endif
			;

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
		)
#if !GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE_PUTFILE_TIMESTAMP
			override
#endif
			;

		virtual void PutFile(
			const char* container,
			const char* name,
			const void* buffer,
			uint32_t bufferLength,
			ICloudStoragePutFileListener* listener,
			const char* const* metadataKeys,
			const char* const* metadataValues,
			uint32_t timeStamp
		)
#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE_PUTFILE_TIMESTAMP
			override
#endif
			;

		/**
		 * Delete a file from cloud storage
		 *
		 * This call is asynchronous. Responses come to the ICloudStorageDeleteFileListener.
		 *
		 * @param [in] container The name of the containter.
		 * @param [in] name The name of the file in cloud storage.
		 * @param [in] listener The listener for the specific operation.
		 */

		// Windows.h woes..
#pragma push_macro("DeleteFile")
#undef DeleteFile
		virtual void DeleteFile(const char* container, const char* name, ICloudStorageDeleteFileListener* listener) override;
#pragma pop_macro ("DeleteFile")
	};

	/** @} */
}

#endif
