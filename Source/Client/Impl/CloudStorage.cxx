#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE

#include "CloudStorage.hxx"

#include "UniverseLAN.hxx"

#include <SafeStringCopy.hxx>

#include <string>
#include <utility>

namespace universelan::client {
	using namespace galaxy::api;

	CloudStorageImpl::CloudStorageImpl(InterfaceInstances* intf) :
		intf{ intf }, listeners{ intf->notification.get() },
		sfu(intf->config->GetGameDataPath()), last_container{ "" },
		container_file_list{}
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICLOUDSTORAGE };
	}

	CloudStorageImpl::~CloudStorageImpl() {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICLOUDSTORAGE };
	}

	void CloudStorageImpl::GetFileList(const char* container, ICloudStorageGetFileListListener* listener) {
		util::safe_fix_null_char_ptr(container);

		last_container = SharedFileUtils::FilterBadFilenameChars(container);
		container_file_list = sfu.GetDirectoryFileListCloud(last_container);

		listeners->NotifyAll(
			listener,
			&ICloudStorageGetFileListListener::OnGetFileListSuccess,
			(uint32_t)container_file_list.size(),
			sfu.GetTotalDiskSpace(),
			sfu.GetUsedDiskSpace());
	}

	const char* CloudStorageImpl::GetFileNameByIndex(uint32_t index) const {

		if (index >= container_file_list.size()) {
			return nullptr;
		}

		static thread_local char buffer[256];

		std::string name = container_file_list[index].string();
		universelan::util::safe_copy_str_n(name, buffer, sizeof(buffer));

		return buffer;
	}

	uint32_t CloudStorageImpl::GetFileSizeByIndex(uint32_t index) const {
		if (index >= container_file_list.size()) {
			return 0;
		}

		return sfu.GetSizeCloud(last_container, container_file_list[index]);
	}

	uint32_t CloudStorageImpl::GetFileTimestampByIndex(uint32_t index) const {
		if (index >= container_file_list.size()) {
			return 0;
		}

		return sfu.GetTimestampCloud(last_container, container_file_list[index]);
	}

	void CloudStorageImpl::GetFile(const char* container, const char* name, void* userParam, WriteFunc writeFunc, ICloudStorageGetFileListener* listener) {
		if (SharedFileUtils::HasBadFilenameChars(container) || SharedFileUtils::HasBadFilenameChars(name)) {
			listeners->NotifyAll(
				listener,
				&ICloudStorageGetFileListener::OnGetFileFailure, container, name, ICloudStorageGetFileListener::FAILURE_REASON_UNDEFINED);

			return;
		}

		if (writeFunc == nullptr) {
			listeners->NotifyAll(
				listener,
				&ICloudStorageGetFileListener::OnGetFileFailure, container, name, ICloudStorageGetFileListener::FAILURE_REASON_WRITE_FUNC_ERROR);

			return;
		}

		if (!sfu.ExistsCloud(container, name)) {
			listeners->NotifyAll(
				listener,
				&ICloudStorageGetFileListener::OnGetFileFailure, container, name, ICloudStorageGetFileListener::FAILURE_REASON_NOT_FOUND);

			return;
		}

		std::filesystem::path container_str = container;
		std::filesystem::path file_name = name;

		intf->delay_runner->Add([=, this] {
			auto data{ sfu.ReadCloud(container_str, file_name) };
			if (writeFunc(userParam, data.data(), (uint32_t)data.size()) < 0) {
				this->listeners->NotifyAllNow(
					listener,
					&ICloudStorageGetFileListener::OnGetFileFailure, container_str.string().c_str(), file_name.string().c_str(), ICloudStorageGetFileListener::FAILURE_REASON_WRITE_FUNC_ERROR);

				return;
			}

			int metadata_count = 0;
			this->listeners->NotifyAllNow(
				listener,
				&ICloudStorageGetFileListener::OnGetFileSuccess, container_str.string().c_str(), file_name.string().c_str(), (uint32_t)data.size(), metadata_count);
		});
	}

	void CloudStorageImpl::GetFile(const char* container, const char* name, void* buffer, uint32_t bufferLength, ICloudStorageGetFileListener* listener) {
		listeners->NotifyAll(
			listener,
			&ICloudStorageGetFileListener::OnGetFileFailure, container, name, ICloudStorageGetFileListener::FAILURE_REASON_UNDEFINED);
	}

	void CloudStorageImpl::GetFileMetadata(const char* container, const char* name, ICloudStorageGetFileListener* listener) {
		listeners->NotifyAll(
			listener,
			&ICloudStorageGetFileListener::OnGetFileFailure, container, name, ICloudStorageGetFileListener::FAILURE_REASON_UNDEFINED);
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
		listeners->NotifyAll(
			listener,
			&ICloudStoragePutFileListener::OnPutFileFailure, container, name, ICloudStoragePutFileListener::FAILURE_REASON_UNDEFINED);
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
		listeners->NotifyAll(
			listener,
			&ICloudStoragePutFileListener::OnPutFileFailure, container, name, ICloudStoragePutFileListener::FAILURE_REASON_UNDEFINED);
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
