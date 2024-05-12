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
		sfu(intf->sfu.get())
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };
	}

	StorageImpl::~StorageImpl() {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };
	}

#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_SYNCHRONIZE
	void StorageImpl::Synchronize() {
		listeners->NotifyAll(
			&IStorageSynchronizationListener::OnStorageSynchronizationSuccess);
	}
#endif

	void StorageImpl::FileWrite(const char* fileName, const void* data, uint32_t dataSize) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		if (!sfu->Write(sfu->storage, fileName, (const char*)data, dataSize)) {
			std::cerr << __FUNCTION__ << " fail: " << fileName << "\n";
		}
	}

	uint32_t StorageImpl::FileRead(const char* fileName, void* data, uint32_t dataSize) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		return sfu->Read(sfu->storage, fileName, (char*)data, dataSize);
	}

	void StorageImpl::FileDelete(const char* fileName) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		if (!sfu->Remove(sfu->storage, fileName)) {
			std::cerr << __FUNCTION__ << " fail: " << fileName << "\n";
		}
	}

	bool StorageImpl::FileExists(const char* fileName) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		return sfu->Exists(sfu->storage, fileName);
	}

	uint32_t StorageImpl::GetFileSize(const char* fileName) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		return sfu->GetSize(sfu->storage, fileName);
	}

	uint32_t StorageImpl::GetFileTimestamp(const char* fileName) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		return sfu->GetTimestamp(sfu->storage, fileName);
	}

	uint32_t StorageImpl::GetFileCount() {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		return sfu->GetFileCount(sfu->storage);
	}

	const char* StorageImpl::GetFileNameByIndex(uint32_t index) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		static thread_local char buffer[256];
		GetFileNameCopyByIndex(index, buffer, sizeof(buffer));
		return buffer;
	}

	void StorageImpl::GetFileNameCopyByIndex(uint32_t index, char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		std::string path = sfu->GetFileNameByIndex(sfu->storage, index).string();
		universelan::util::safe_copy_str_n(path, buffer, bufferLength);
	}

	void StorageImpl::FileShare(const char* fileName
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
		, IFileShareListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		if (!intf->config->GetAllowFileSharingUpload() || !fileName) {

			if (!fileName) {
				trace.write_all("null");
			}

			listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
				listener,
#endif
				& IFileShareListener::OnFileShareFailure, fileName, IFileShareListener::FAILURE_REASON_UNDEFINED);
			return;
		}

		std::string str_file_name{ fileName };

		if (!sfu->Exists(sfu->storage, str_file_name.c_str())) {
			std::cerr << __FUNCTION__ << " fail: " << fileName << "\n";

			listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
				listener,
#endif
				& IFileShareListener::OnFileShareFailure, fileName, IFileShareListener::FAILURE_REASON_UNDEFINED);
			return;
		}

		// !!! LEAK !!! (albeit temporary when thread exits)
		std::thread([=, this] {
			uint64_t request_id = MessageUniqueID::get();

#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
			listeners->AddRequestListener(request_id, listener);
#endif
			intf->client->GetConnection().SendAsync(FileShareMessage{ request_id, str_file_name, sfu->Read(sfu->storage, str_file_name.c_str()) });
			}).detach(); // due to this detach
	}

	void StorageImpl::DownloadSharedFile(SharedFileID sharedFileID
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
		, ISharedFileDownloadListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		if (!intf->config->GetAllowFileSharingDownload()) {
			listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
				listener,
#endif
				& ISharedFileDownloadListener::OnSharedFileDownloadFailure, sharedFileID, ISharedFileDownloadListener::FAILURE_REASON_UNDEFINED);
			return;
		}

		uint64_t request_id = MessageUniqueID::get();

#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
		listeners->AddRequestListener(request_id, listener);
#endif

		intf->client->GetConnection().SendAsync(FileRequestMessage{ request_id, sharedFileID });
	}

	const char* StorageImpl::GetSharedFileName(SharedFileID sharedFileID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		static thread_local char buffer[256];
		GetSharedFileNameCopy(sharedFileID, buffer, sizeof(buffer));
		return buffer;
	}

	void StorageImpl::GetSharedFileNameCopy(SharedFileID sharedFileID, char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		std::string name = sfu->GetSharedFileName(sfu->shared, sharedFileID).string();
		universelan::util::safe_copy_str_n(name, buffer, bufferLength);
	}

	uint32_t StorageImpl::GetSharedFileSize(SharedFileID sharedFileID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		return sfu->GetSize(sfu->shared, sharedFileID);
	}

	GalaxyID StorageImpl::GetSharedFileOwner(SharedFileID sharedFileID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		return intf->config->GetApiGalaxyID();
	}

	uint32_t StorageImpl::SharedFileRead(SharedFileID sharedFileID, void* data, uint32_t dataSize, uint32_t offset) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		return sfu->Read(sfu->shared, sharedFileID, (char*)data, dataSize, offset);
	}

	void StorageImpl::SharedFileClose(SharedFileID sharedFileID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		sfu->Remove(sfu->shared, sharedFileID);
	}

	uint32_t StorageImpl::GetDownloadedSharedFileCount() {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		return sfu->GetFileCount(sfu->shared);
	}

	SharedFileID StorageImpl::GetDownloadedSharedFileByIndex(uint32_t index) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		return sfu->GetSharedIDByIndex(sfu->shared, index);
	}

	void StorageImpl::FileDownloaded(const std::shared_ptr<FileRequestMessage>& data) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		if (!intf->config->GetAllowFileSharingDownload()) {
			return;
		}

#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
		ISharedFileDownloadListener* listener = nullptr;
		listeners->PopRequestListener(data->request_id, listener);
#endif

		if (data->data.size() > 0) {
			auto entry = sfu->shared->create_shared(data->filename, data->id);
			if (entry && entry->write(data->data)) {
				listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
					listener,
#endif
					& ISharedFileDownloadListener::OnSharedFileDownloadSuccess, data->id, data->filename.c_str());
				return;
			}
		}

		listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
			listener,
#endif
			& ISharedFileDownloadListener::OnSharedFileDownloadFailure, data->id, ISharedFileDownloadListener::FAILURE_REASON_UNDEFINED);
	}

	void StorageImpl::FileUploaded(const std::shared_ptr<FileShareResponseMessage>& data) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

		if (!intf->config->GetAllowFileSharingUpload()) {
			return;
		}

#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
		IFileShareListener* listener = nullptr;
		listeners->PopRequestListener(data->request_id, listener);
#endif

		if (data->id != 0) {
			if (!sfu->CopyFromLocalToShared(data->filename.c_str(), data->id)) {
				std::cerr << "FileUploaded::CopyFromLocalToShared failed\n";
			}

			listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
				listener,
#endif
				& IFileShareListener::OnFileShareSuccess, data->filename.c_str(), data->id);
		}
		else {
			listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
				listener,
#endif
				& IFileShareListener::OnFileShareFailure, data->filename.c_str(), IFileShareListener::FAILURE_REASON_UNDEFINED);
		}
	}
}

#endif
