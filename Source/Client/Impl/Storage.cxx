#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE

#include "Storage.hxx"

#include "UniverseLAN.hxx"

#include <SafeStringCopy.hxx>

#include <string>
#include <utility>

namespace universelan::client {
	using namespace galaxy::api;

	StorageImpl::StorageImpl(InterfaceInstances* intf) :
		intf{ intf }, listeners{ intf->notification.get() },
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
		file_upload_requests{}, file_download_requests{},
#endif
		sfu(intf->config->GetGameDataPath())
	{
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };
	}

	StorageImpl::~StorageImpl() {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };
	}

	void StorageImpl::FileWrite(const char* fileName, const void* data, uint32_t dataSize) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		if (!sfu.WriteLocal(fileName, (const char*)data, dataSize)) {
			std::cerr << __FUNCTION__ << " fail: " << fileName << "\n";
		}
	}

	uint32_t StorageImpl::FileRead(const char* fileName, void* data, uint32_t dataSize) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		return sfu.ReadLocal(fileName, (char*)data, dataSize);
	}

	void StorageImpl::FileDelete(const char* fileName) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		if (!sfu.RemoveLocal(fileName)) {
			std::cerr << __FUNCTION__ << " fail: " << fileName << "\n";
		}
	}

	bool StorageImpl::FileExists(const char* fileName) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		return sfu.ExistsLocal(fileName);
	}

	uint32_t StorageImpl::GetFileSize(const char* fileName) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		return sfu.GetSizeLocal(fileName);
	}

	uint32_t StorageImpl::GetFileTimestamp(const char* fileName) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		return sfu.GetTimestampLocal(fileName);
	}

	uint32_t StorageImpl::GetFileCount() {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		return sfu.GetFileCountLocal();
	}

	const char* StorageImpl::GetFileNameByIndex(uint32_t index) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		static thread_local char buffer[256];
		GetFileNameCopyByIndex(index, buffer, sizeof(buffer));
		return buffer;
	}

	void StorageImpl::GetFileNameCopyByIndex(uint32_t index, char* buffer, uint32_t bufferLength) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		std::string path = sfu.GetFileNameByIndexLocal(index).string();
		universelan::util::safe_copy_str_n(path, buffer, bufferLength);
	}

	void StorageImpl::FileShare(const char* fileName
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
		, IFileShareListener* const listener
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		if (!intf->config->GetAllowFileSharingUpload()) {
			listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
				listener, 
#endif
				&IFileShareListener::OnFileShareFailure, fileName, IFileShareListener::FAILURE_REASON_UNDEFINED);
			return;
		}

		std::string str_file_name{ fileName };

		if (!sfu.OpenLocal(str_file_name, std::ios::in | std::ios::binary)) {
			std::cerr << __FUNCTION__ << " fail: " << fileName << "\n";

			listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
				listener, 
#endif
				&IFileShareListener::OnFileShareFailure, fileName, IFileShareListener::FAILURE_REASON_UNDEFINED);
			return;
		}

		// !!! LEAK !!! (albeit temporary when thread exits)
		std::thread([=, this, sfu = std::move(sfu), str_file_name = std::move(str_file_name)] {
			uint64_t request_id = MessageUniqueID::get();

#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
			file_upload_requests.emplace(request_id, listener);
#endif
			intf->client->GetConnection().SendAsync(FileShareMessage{ request_id, str_file_name, sfu.ReadLocal(str_file_name) });
			}).detach(); // due to this detach
	}

	void StorageImpl::DownloadSharedFile(SharedFileID sharedFileID
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
		, ISharedFileDownloadListener* const listener
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		if (!intf->config->GetAllowFileSharingDownload()) {
			listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
				listener,
#endif
				&ISharedFileDownloadListener::OnSharedFileDownloadFailure, sharedFileID, ISharedFileDownloadListener::FAILURE_REASON_UNDEFINED);
			return;
		}

		uint64_t request_id = MessageUniqueID::get();

#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
		file_download_requests.emplace(request_id, listener);
#endif

		intf->client->GetConnection().SendAsync(FileRequestMessage{ request_id, sharedFileID });
	}

	const char* StorageImpl::GetSharedFileName(SharedFileID sharedFileID) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		static thread_local char buffer[256];
		GetSharedFileNameCopy(sharedFileID, buffer, sizeof(buffer));
		return buffer;
	}

	void StorageImpl::GetSharedFileNameCopy(SharedFileID sharedFileID, char* buffer, uint32_t bufferLength) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		std::string name = sfu.GetSharedFileName(sharedFileID).string();
		universelan::util::safe_copy_str_n(name, buffer, bufferLength);
	}

	uint32_t StorageImpl::GetSharedFileSize(SharedFileID sharedFileID) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		return sfu.GetSizeShared(sharedFileID);
	}

	GalaxyID StorageImpl::GetSharedFileOwner(SharedFileID sharedFileID) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		return intf->config->GetApiGalaxyID();
	}

	uint32_t StorageImpl::SharedFileRead(SharedFileID sharedFileID, void* data, uint32_t dataSize, uint32_t offset) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		return sfu.ReadShared(sharedFileID, (char*)data, dataSize, offset);
	}

	void StorageImpl::SharedFileClose(SharedFileID sharedFileID) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		sfu.UnlinkSharedFileStorage(sharedFileID);
	}

	uint32_t StorageImpl::GetDownloadedSharedFileCount() {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		return sfu.GetFileCountShared();
	}

	SharedFileID StorageImpl::GetDownloadedSharedFileByIndex(uint32_t index) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		return sfu.GetSharedIDByIndex(index);
	}

	void StorageImpl::FileDownloaded(const std::shared_ptr<FileRequestMessage>& data) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		if (!intf->config->GetAllowFileSharingDownload()) {
			return;
		}

#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
		ISharedFileDownloadListener* listener = file_download_requests.pop(data->request_id);
#endif

		if (data->data.size() > 0 && sfu.InitSharedFileStorage(data->filename, data->id)) {
			if (!sfu.WriteShared(data->filename, data->data.data(), data->data.size())) {
				std::cerr << "FileDownloaded::WriteShared failed\n";
			}

			listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
				listener, 
#endif
				&ISharedFileDownloadListener::OnSharedFileDownloadSuccess, data->id, data->filename.c_str());
		}
		else {
			listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
				listener, 
#endif
				&ISharedFileDownloadListener::OnSharedFileDownloadFailure, data->id, ISharedFileDownloadListener::FAILURE_REASON_UNDEFINED);
		}
	}

	void StorageImpl::FileUploaded(const std::shared_ptr<FileShareResponseMessage>& data) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		if (!intf->config->GetAllowFileSharingUpload()) {
			return;
		}

#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
		IFileShareListener* listener = file_upload_requests.pop(data->request_id);
#endif

		if (data->id != 0) {
			if (!sfu.InitSharedFileStorage(data->filename, data->id)) {
				std::cerr << "FileUploaded::InitSharedFileStorage failed\n";
			}

			if (!sfu.CopyFromLocalToShared(data->filename)) {
				std::cerr << "FileUploaded::CopyFromLocalToShared failed\n";
			}

			listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
				listener, 
#endif
				&IFileShareListener::OnFileShareSuccess, data->filename.c_str(), data->id);
		}
		else {
			listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
				listener,
#endif
				&IFileShareListener::OnFileShareFailure, data->filename.c_str(), IFileShareListener::FAILURE_REASON_UNDEFINED);
		}
	}
}

#endif
