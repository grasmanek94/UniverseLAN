#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE

#include "Storage.hxx"

#include <Tracer.hxx>
#include <GalaxyDLL.hxx>
#include <SafeStringCopy.hxx>

#include <magic_enum/magic_enum.hpp>

#include <format>

namespace universelan::client {
	using namespace galaxy::api;

	StorageImpl::StorageImpl(InterfaceInstances* intf) : intf{ intf }
	{
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };
	}

	StorageImpl::~StorageImpl() {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };
	}

#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_SYNCHRONIZE
	void StorageImpl::Synchronize() {
		listeners->NotifyAll(
			&IStorageSynchronizationListener::OnStorageSynchronizationSuccess);
	}
#endif

	void StorageImpl::FileWrite(const char* fileName, const void* data, uint32_t dataSize) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };
	}

	uint32_t StorageImpl::FileRead(const char* fileName, void* data, uint32_t dataSize) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };
	}

	void StorageImpl::FileDelete(const char* fileName) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };
	}

	bool StorageImpl::FileExists(const char* fileName) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };
	}

	uint32_t StorageImpl::GetFileSize(const char* fileName) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };
	}

	uint32_t StorageImpl::GetFileTimestamp(const char* fileName) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };
	}

	uint32_t StorageImpl::GetFileCount() {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

	}

	const char* StorageImpl::GetFileNameByIndex(uint32_t index) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };
	}

	void StorageImpl::GetFileNameCopyByIndex(uint32_t index, char* buffer, uint32_t bufferLength) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };
	}

	void StorageImpl::FileShare(const char* fileName
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
		, IFileShareListener* const listener
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };
	}

	void StorageImpl::DownloadSharedFile(SharedFileID sharedFileID
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
		, ISharedFileDownloadListener* const listener
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };
	}

	const char* StorageImpl::GetSharedFileName(SharedFileID sharedFileID) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };
	}

	void StorageImpl::GetSharedFileNameCopy(SharedFileID sharedFileID, char* buffer, uint32_t bufferLength) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

	}

	uint32_t StorageImpl::GetSharedFileSize(SharedFileID sharedFileID) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

	}

	GalaxyID StorageImpl::GetSharedFileOwner(SharedFileID sharedFileID) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

	}

	uint32_t StorageImpl::SharedFileRead(SharedFileID sharedFileID, void* data, uint32_t dataSize, uint32_t offset) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

	}

	void StorageImpl::SharedFileClose(SharedFileID sharedFileID) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

	}

	uint32_t StorageImpl::GetDownloadedSharedFileCount() {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

	}

	SharedFileID StorageImpl::GetDownloadedSharedFileByIndex(uint32_t index) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTORAGE };

	}
}

#endif
