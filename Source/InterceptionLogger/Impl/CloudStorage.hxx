#pragma once

#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE

#include "Listeners/CloudStorageListener.hxx"

#include <GalaxyFunctional.hxx>
#include <ListenersContainer.hxx>

#include <GalaxyExport.h>
#include <ICloudStorage.h>
#include <IListenerRegistrar.h>

namespace universelan::client {
	using namespace galaxy::api;

	/**
	 * @addtogroup api
	 * @{
	 */

	 /**
	  * The interface for managing of cloud storage files.
	  */
	class CloudStorageImpl : public ICloudStorage
	{
	public:
		using FuncT = functional::xt<std::function<GALAXY_DLL_EXPORT ICloudStorage* GALAXY_CALLTYPE(void)>>;
		using FuncPtr = typename FuncT::PTR;

	private:
		FuncT::F intf;
		IListenerRegistrar* notifications;
		ListenersContainer listeners;

	public:
		CloudStorageImpl(FuncT::F intf, IListenerRegistrar* notifications);
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

#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE_METADATAIDX_FUNCS
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
#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE_METADATAIDX_FUNCS
			override
#endif
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
#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE_METADATAIDX_FUNCS
			override
#endif
#endif
			;
#endif

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
		virtual void DeleteFile(const char* container, const char* name, ICloudStorageDeleteFileListener* listener
#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE_HASHING
			, const char* expectedHash = NULL
#endif	
		) override;
#pragma pop_macro ("DeleteFile")

#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE_SAVEGAME
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
		 * @param [in] container The name of the containter.
		 * @param [in] name The name of the file in cloud storage.
		 * @param [in] userParam The parameter passed to readFunc on every call.
		 * @param [in] readFunc The function called to obtain data chunks for upload.
		 * @param [in] rewindFunc The function called to rewind read pointer to the begining of the data stream.
		 * @param [in] listener The listener for the specific operation.
		 * @param [in] savegameType The type of the savegame.
		 * @param [in] timeStamp The timestamp of the uploaded object. Current time will be set by default.
		 */
		virtual void PutFile(
			const char* container,
			const char* name,
			void* userParam,
			ReadFunc readFunc,
			RewindFunc rewindFunc,
			ICloudStoragePutFileListener* listener,
			SavegameType savegameType = SAVEGAME_TYPE_UNDEFINED,
			uint32_t timeStamp = 0
#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE_HASHING
			, const char* hash = NULL
#endif
		) override;

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
		 * @param [in] container The name of the containter.
		 * @param [in] name The name of the file in cloud storage.
		 * @param [out] data The buffer for the data to be read.
		 * @param [in] size The size of the buffer for the data.
		 * @param [in] listener The listener for the specific operation.
		 * @param [in] savegameType The type of the savegame.
		 * @param [in] timeStamp The timestamp of the uploaded object. Current time will be set by default.
		 */
		virtual void PutFile(
			const char* container,
			const char* name,
			const void* buffer,
			uint32_t bufferLength,
			ICloudStoragePutFileListener* listener,
			SavegameType savegameType = SAVEGAME_TYPE_UNDEFINED,
			uint32_t timeStamp = 0
#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE_HASHING
			, const char* hash = NULL
#endif
		) override;

		/**
		 * Starts new savegame
		 *
		 * After this call all subsequently stored files will have the same unique savegame ID.
		 */
		virtual void OpenSavegame() override;

		/**
		 * Closes savegame
		 *
		 * After this call all subsequently stored files will have a different unique savegame ID.
		 */
		virtual void CloseSavegame() override;
#endif

#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE_HASHING
		/**
		 * Calculate hash for the specified object.
		 *
		 * This call is synchronous and may be time consuming.
		 *
		 * This version of the CalculateHash method uses (userParam, readFunc) parameters
		 * as an abstraction of a data source for the uploaded data. readFunc will be
		 * called with userParam passed to the method along with the buffer for the data to be read.
		 * rewindFunc will be called on start reading data phase and should set the read pointer at
		 * the begining of the data stream.
		 *
		 * @param [in] userParam The parameter passed to readFunc on every call.
		 * @param [in] readFunc The function called to obtain data chunks for upload.
		 * @param [in] hashBuffer The buffer for calculated hash. Should be at least MIN_HASH_BUFFER_SIZE long.
		 * @param [in, out] hashBufferSize The size of buffer for calculated hash.
		 * @param [in] rewindFunc The function called to rewind read pointer to the begining of the data stream.
		 */
		virtual void CalculateHash(
			void* userParam,
			ReadFunc readFunc,
			RewindFunc rewindFunc,
			char* hashBuffer,
			uint32_t hashBufferSize
		) override;

		/**
		 * Calculate hash for the specified object.
		 *
		 * This call is synchronous and may be time consuming.
		 *
		 * This version of the CalculateHash method uploads the data pointed by the buffer parameter,
		 * where bufferLength indicates the file length.
		 *
		 * @param [in] buffer The buffer for the data to be read.
		 * @param [in] size The size of the buffer for the data.
		 * @param [in, out] hashBuffer The buffer for the calculated hash. Should be at least MIN_HASH_BUFFER_SIZE long.
		 * @param [in] hashBufferSize The size of the buffer for the calculated hash.
		 */
		virtual void CalculateHash(
			const void* buffer,
			uint32_t bufferLength,
			char* hashBuffer,
			uint32_t hashBufferSize
		) override;
#endif

	};

	/** @} */
}

#endif
