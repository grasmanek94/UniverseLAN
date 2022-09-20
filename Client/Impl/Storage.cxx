#include "Storage.hxx"

#include "UniverseLAN.hxx"

#include <string>

namespace universelan::client {
	using namespace galaxy::api;

	StorageImpl::StorageImpl(InterfaceInstances* intf) :
		intf{ intf }, listeners{ intf->notification.get() },
		file_upload_requests{}, file_download_requests{},
		sfu(intf->config->GetGameDataPath())
	{}

	StorageImpl::~StorageImpl() {}

	void StorageImpl::FileWrite(const char* fileName, const void* data, uint32_t dataSize) {
		if (!sfu.WriteLocal(fileName, (const char*)data, dataSize)) {
			std::cerr << __FUNCTION__ << " fail: " << fileName << "\n";
		}
	}

	uint32_t StorageImpl::FileRead(const char* fileName, void* data, uint32_t dataSize) {
		return sfu.ReadLocal(fileName, (char*)data, dataSize);
	}

	void StorageImpl::FileDelete(const char* fileName) {
		if (!sfu.RemoveLocal(fileName)) {
			std::cerr << __FUNCTION__ << " fail: " << fileName << "\n";
		}
	}

	bool StorageImpl::FileExists(const char* fileName) {
		return sfu.ExistsLocal(fileName);
	}

	uint32_t StorageImpl::GetFileSize(const char* fileName) {
		return sfu.GetSizeLocal(fileName);
	}

	uint32_t StorageImpl::GetFileTimestamp(const char* fileName) {
		return sfu.GetTimestampLocal(fileName);
	}

	uint32_t StorageImpl::GetFileCount() {
		return sfu.GetFileCountLocal();
	}

	const char* StorageImpl::GetFileNameByIndex(uint32_t index) {
		static thread_local char buffer[256];
		GetFileNameCopyByIndex(index, buffer, sizeof(buffer));
		return buffer;
	}

	void StorageImpl::GetFileNameCopyByIndex(uint32_t index, char* buffer, uint32_t bufferLength) {
		std::string path = sfu.GetFileNameByIndexLocal(index);
		std::copy_n(path.c_str(), std::min((size_t)bufferLength, path.length()), buffer);
	}

	void StorageImpl::FileShare(const char* fileName, IFileShareListener* const listener) {
		if (!intf->config->GetAllowFileSharingUpload()) {
			listeners->NotifyAll(listener, &IFileShareListener::OnFileShareFailure, fileName, IFileShareListener::FAILURE_REASON_UNDEFINED);
			return;
		}

		std::string str_file_name{ fileName };

		if (!sfu.OpenLocal(str_file_name, std::ios::in | std::ios::binary)) {
			std::cerr << __FUNCTION__ << " fail: " << fileName << "\n";

			listeners->NotifyAll(listener, &IFileShareListener::OnFileShareFailure, fileName, IFileShareListener::FAILURE_REASON_UNDEFINED);
			return;
		}

		// !!! LEAK !!! (albeit temporary when thread exits)
		std::thread([=] {
			uint64_t request_id = MessageUniqueID::get();

			file_upload_requests.emplace(request_id, listener);
			intf->client->GetConnection().SendAsync(FileShareMessage{ request_id, fileName, sfu.ReadLocal(str_file_name) });
			}).detach();
	}

	void StorageImpl::DownloadSharedFile(SharedFileID sharedFileID, ISharedFileDownloadListener* const listener) {
		if (!intf->config->GetAllowFileSharingDownload()) {
			listeners->NotifyAll(listener, &ISharedFileDownloadListener::OnSharedFileDownloadFailure, sharedFileID, ISharedFileDownloadListener::FAILURE_REASON_UNDEFINED);
			return;
		}

		uint64_t request_id = MessageUniqueID::get();

		file_download_requests.emplace(request_id, listener);
		intf->client->GetConnection().SendAsync(FileRequestMessage{ request_id, sharedFileID });
	}

	const char* StorageImpl::GetSharedFileName(SharedFileID sharedFileID) {
		static thread_local char buffer[256];
		GetSharedFileNameCopy(sharedFileID, buffer, sizeof(buffer));
		return buffer;
	}

	void StorageImpl::GetSharedFileNameCopy(SharedFileID sharedFileID, char* buffer, uint32_t bufferLength) {
		std::string name = sfu.GetSharedFileName(sharedFileID);
		std::copy_n(name.c_str(), std::min((size_t)bufferLength, name.length()), buffer);
	}

	uint32_t StorageImpl::GetSharedFileSize(SharedFileID sharedFileID) {
		return sfu.GetSizeShared(sharedFileID);
	}

	GalaxyID StorageImpl::GetSharedFileOwner(SharedFileID sharedFileID) {
		return intf->config->GetApiGalaxyID();
	}

	uint32_t StorageImpl::SharedFileRead(SharedFileID sharedFileID, void* data, uint32_t dataSize, uint32_t offset) {
		return sfu.ReadShared(sharedFileID, (char*)data, dataSize, offset);
	}

	void StorageImpl::SharedFileClose(SharedFileID sharedFileID) {
		sfu.UnlinkSharedFileStorage(sharedFileID);
	}

	uint32_t StorageImpl::GetDownloadedSharedFileCount() {
		return sfu.GetFileCountShared();
	}

	SharedFileID StorageImpl::GetDownloadedSharedFileByIndex(uint32_t index) {
		return sfu.GetSharedIDByIndex(index);
	}

	void StorageImpl::FileDownloaded(const std::shared_ptr<FileRequestMessage>& data) {
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
