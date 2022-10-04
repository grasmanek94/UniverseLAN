#include "Storage.hxx"

#include "UniverseLAN.hxx"

#include <string>
#include <utility>

namespace universelan::client {
	using namespace galaxy::api;

	StorageImpl::StorageImpl(InterfaceInstances* intf) :
		intf{ intf }, listeners{ intf->notification.get() },
		file_upload_requests{}, file_download_requests{},
		sfu(intf->config->GetGameDataPath())
	{
		tracer::Trace trace{ __FUNCTION__ };
	}

	StorageImpl::~StorageImpl() {
		tracer::Trace trace{ __FUNCTION__ };
	}

	void StorageImpl::FileWrite(const char* fileName, const void* data, uint32_t dataSize) {
		tracer::Trace trace{ __FUNCTION__ };

		if (!sfu.WriteLocal(fileName, (const char*)data, dataSize)) {
			std::cerr << __FUNCTION__ << " fail: " << fileName << "\n";
		}
	}

	uint32_t StorageImpl::FileRead(const char* fileName, void* data, uint32_t dataSize) {
		tracer::Trace trace{ __FUNCTION__ };

		return sfu.ReadLocal(fileName, (char*)data, dataSize);
	}

	void StorageImpl::FileDelete(const char* fileName) {
		tracer::Trace trace{ __FUNCTION__ };

		if (!sfu.RemoveLocal(fileName)) {
			std::cerr << __FUNCTION__ << " fail: " << fileName << "\n";
		}
	}

	bool StorageImpl::FileExists(const char* fileName) {
		tracer::Trace trace{ __FUNCTION__ };

		return sfu.ExistsLocal(fileName);
	}

	uint32_t StorageImpl::GetFileSize(const char* fileName) {
		tracer::Trace trace{ __FUNCTION__ };

		return sfu.GetSizeLocal(fileName);
	}

	uint32_t StorageImpl::GetFileTimestamp(const char* fileName) {
		tracer::Trace trace{ __FUNCTION__ };

		return sfu.GetTimestampLocal(fileName);
	}

	uint32_t StorageImpl::GetFileCount() {
		tracer::Trace trace{ __FUNCTION__ };

		return sfu.GetFileCountLocal();
	}

	const char* StorageImpl::GetFileNameByIndex(uint32_t index) {
		tracer::Trace trace{ __FUNCTION__ };

		static thread_local char buffer[256];
		GetFileNameCopyByIndex(index, buffer, sizeof(buffer));
		return buffer;
	}

	void StorageImpl::GetFileNameCopyByIndex(uint32_t index, char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ __FUNCTION__ };

		std::string path = sfu.GetFileNameByIndexLocal(index);
		std::copy_n(path.c_str(), std::min((size_t)bufferLength, path.length()), buffer);
	}

	void StorageImpl::FileShare(const char* fileName
#if (GALAXY_VERSION) > 112400
		, IFileShareListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		if (!intf->config->GetAllowFileSharingUpload()) {
			listeners->NotifyAll(
#if (GALAXY_VERSION) > 112400
				listener, 
#endif
				&IFileShareListener::OnFileShareFailure, fileName, IFileShareListener::FAILURE_REASON_UNDEFINED);
			return;
		}

		std::string str_file_name{ fileName };

		if (!sfu.OpenLocal(str_file_name, std::ios::in | std::ios::binary)) {
			std::cerr << __FUNCTION__ << " fail: " << fileName << "\n";

			listeners->NotifyAll(
#if (GALAXY_VERSION) > 112400
				listener, 
#endif
				&IFileShareListener::OnFileShareFailure, fileName, IFileShareListener::FAILURE_REASON_UNDEFINED);
			return;
		}

		// !!! LEAK !!! (albeit temporary when thread exits)
		std::thread([=, this, sfu = std::move(sfu), str_file_name = std::move(str_file_name)] {
			uint64_t request_id = MessageUniqueID::get();

#if (GALAXY_VERSION) > 112400
			file_upload_requests.emplace(request_id, listener);
#endif
			intf->client->GetConnection().SendAsync(FileShareMessage{ request_id, str_file_name, sfu.ReadLocal(str_file_name) });
			}).detach();
	}

	void StorageImpl::DownloadSharedFile(SharedFileID sharedFileID
#if (GALAXY_VERSION) > 112400
		, ISharedFileDownloadListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		if (!intf->config->GetAllowFileSharingDownload()) {
			listeners->NotifyAll(
#if (GALAXY_VERSION) > 112400
				listener,
#endif
				&ISharedFileDownloadListener::OnSharedFileDownloadFailure, sharedFileID, ISharedFileDownloadListener::FAILURE_REASON_UNDEFINED);
			return;
		}

		uint64_t request_id = MessageUniqueID::get();

#if (GALAXY_VERSION) > 112400
		file_download_requests.emplace(request_id, listener);
#endif

		intf->client->GetConnection().SendAsync(FileRequestMessage{ request_id, sharedFileID });
	}

	const char* StorageImpl::GetSharedFileName(SharedFileID sharedFileID) {
		tracer::Trace trace{ __FUNCTION__ };

		static thread_local char buffer[256];
		GetSharedFileNameCopy(sharedFileID, buffer, sizeof(buffer));
		return buffer;
	}

	void StorageImpl::GetSharedFileNameCopy(SharedFileID sharedFileID, char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ __FUNCTION__ };

		std::string name = sfu.GetSharedFileName(sharedFileID);
		std::copy_n(name.c_str(), std::min((size_t)bufferLength, name.length()), buffer);
	}

	uint32_t StorageImpl::GetSharedFileSize(SharedFileID sharedFileID) {
		tracer::Trace trace{ __FUNCTION__ };

		return sfu.GetSizeShared(sharedFileID);
	}

	GalaxyID StorageImpl::GetSharedFileOwner(SharedFileID sharedFileID) {
		tracer::Trace trace{ __FUNCTION__ };

		return intf->config->GetApiGalaxyID();
	}

	uint32_t StorageImpl::SharedFileRead(SharedFileID sharedFileID, void* data, uint32_t dataSize, uint32_t offset) {
		tracer::Trace trace{ __FUNCTION__ };

		return sfu.ReadShared(sharedFileID, (char*)data, dataSize, offset);
	}

	void StorageImpl::SharedFileClose(SharedFileID sharedFileID) {
		tracer::Trace trace{ __FUNCTION__ };

		sfu.UnlinkSharedFileStorage(sharedFileID);
	}

	uint32_t StorageImpl::GetDownloadedSharedFileCount() {
		tracer::Trace trace{ __FUNCTION__ };

		return sfu.GetFileCountShared();
	}

	SharedFileID StorageImpl::GetDownloadedSharedFileByIndex(uint32_t index) {
		tracer::Trace trace{ __FUNCTION__ };

		return sfu.GetSharedIDByIndex(index);
	}

	void StorageImpl::FileDownloaded(const std::shared_ptr<FileRequestMessage>& data) {
		tracer::Trace trace{ __FUNCTION__ };

		if (!intf->config->GetAllowFileSharingDownload()) {
			return;
		}

		ISharedFileDownloadListener* listener = file_download_requests.pop(data->request_id);

		if (data->data.size() > 0 && sfu.InitSharedFileStorage(data->filename, data->id)) {
			if (!sfu.WriteShared(data->filename, data->data.data(), data->data.size())) {
				std::cerr << "FileDownloaded::WriteShared failed\n";
			}

			listeners->NotifyAll(listener, &ISharedFileDownloadListener::OnSharedFileDownloadSuccess, data->id, data->filename.c_str());
		}
		else {
			listeners->NotifyAll(listener, &ISharedFileDownloadListener::OnSharedFileDownloadFailure, data->id, ISharedFileDownloadListener::FAILURE_REASON_UNDEFINED);
		}
	}

	void StorageImpl::FileUploaded(const std::shared_ptr<FileShareResponseMessage>& data) {
		tracer::Trace trace{ __FUNCTION__ };

		if (!intf->config->GetAllowFileSharingUpload()) {
			return;
		}

		IFileShareListener* listener = file_upload_requests.pop(data->request_id);

		if (data->id != 0) {
			if (!sfu.InitSharedFileStorage(data->filename, data->id)) {
				std::cerr << "FileUploaded::InitSharedFileStorage failed\n";
			}

			if (!sfu.CopyFromLocalToShared(data->filename)) {
				std::cerr << "FileUploaded::CopyFromLocalToShared failed\n";
			}

			listeners->NotifyAll(listener, &IFileShareListener::OnFileShareSuccess, data->filename.c_str(), data->id);
		}
		else {
			listeners->NotifyAll(listener, &IFileShareListener::OnFileShareFailure, data->filename.c_str(), IFileShareListener::FAILURE_REASON_UNDEFINED);
		}
	}
}
