#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE

#include "CloudStorage.hxx"

#include "UniverseLAN.hxx"

#include <SafeStringCopy.hxx>

#include <string>
#include <utility>

#ifdef DeleteFile
#undef DeleteFile
#endif

namespace universelan::client {
	using namespace galaxy::api;

	CloudStorageImpl::CloudStorageImpl(InterfaceInstances* intf) :
		intf{ intf }, listeners{ intf->notification.get() }
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };
	}

	CloudStorageImpl::~CloudStorageImpl() {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };
	}

	void CloudStorageImpl::GetFileList(const char* container, ICloudStorageGetFileListListener* listener) {
	
	}

	const char* CloudStorageImpl::GetFileNameByIndex(uint32_t index) const {
		return "";
	}

	uint32_t CloudStorageImpl::GetFileSizeByIndex(uint32_t index) const {
		return 0;
	}

	uint32_t CloudStorageImpl::GetFileTimestampByIndex(uint32_t index) const { 
		return 0;
	}

	void CloudStorageImpl::GetFile(const char* container, const char* name, void* userParam, WriteFunc writeFunc, ICloudStorageGetFileListener* listener) { 
	
	}

	void CloudStorageImpl::GetFile(const char* container, const char* name, void* buffer, uint32_t bufferLength, ICloudStorageGetFileListener* listener) { 
	
	}

	void CloudStorageImpl::GetFileMetadata(const char* container, const char* name, ICloudStorageGetFileListener* listener) { 
	
	}

	const char* CloudStorageImpl::GetFileMetadataKeyByIndex(uint32_t index) const {
		return "";
	}

	const char* CloudStorageImpl::GetFileMetadataValueByIndex(uint32_t index) const {
		return "";
	}

	void CloudStorageImpl::PutFile(
		const char* container,
		const char* name,
		void* userParam,
		ReadFunc readFunc,
		RewindFunc rewindFunc,
		ICloudStoragePutFileListener* listener,
		const char* const* metadataKeys,
		const char* const* metadataValues,
		uint32_t timeStamp
	) {

	}

	void CloudStorageImpl::PutFile(
		const char* container,
		const char* name,
		const void* buffer,
		uint32_t bufferLength,
		ICloudStoragePutFileListener* listener,
		const char* const* metadataKeys,
		const char* const* metadataValues,
		uint32_t timeStamp
	) {

	}

	void CloudStorageImpl::PutFile(
		const char* container,
		const char* name,
		void* userParam,
		ReadFunc readFunc,
		RewindFunc rewindFunc,
		ICloudStoragePutFileListener* listener,
		const char* const* metadataKeys,
		const char* const* metadataValues
	) { 
		PutFile(container, name, userParam, readFunc, rewindFunc, listener, metadataKeys, metadataValues, 0);
	}

	void CloudStorageImpl::PutFile(
		const char* container,
		const char* name,
		const void* buffer,
		uint32_t bufferLength,
		ICloudStoragePutFileListener* listener,
		const char* const* metadataKeys,
		const char* const* metadataValues
	) { 
		PutFile(container, name, buffer, bufferLength, listener, metadataKeys, metadataValues, 0);
	}

#pragma push_macro("DeleteFile")
#undef DeleteFile
	void CloudStorageImpl::DeleteFile(const char* container, const char* name, ICloudStorageDeleteFileListener* listener)
#pragma pop_macro ("DeleteFile")
	{

	}
}

#endif
