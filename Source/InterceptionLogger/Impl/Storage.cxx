#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE

#include "Storage.hxx"

#include "Listeners/StorageListener.hxx"

#include <GalaxyID.hxx>
#include <Tracer.hxx>
#include <SafeStringCopy.hxx>

#include <magic_enum/magic_enum.hpp>

#include <format>

namespace universelan::client {
	using namespace galaxy::api;

	namespace {
		const auto TraceContext = tracer::Trace::ISTORAGE;
	}

	StorageImpl::StorageImpl(FuncT::F intf, IListenerRegistrar* notifications) :
		intf{ intf },
		notifications{ notifications },
		listeners{ notifications } {
		listeners.AddListener<FileShareListener>();
		listeners.AddListener<SharedFileDownloadListener>();
	}

	StorageImpl::~StorageImpl() {
		listeners.UnregisterAllListeners();
	}

#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_SYNCHRONIZE
	void StorageImpl::Synchronize() {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		intf()->Synchronize();
	}
#endif

	void StorageImpl::FileWrite(const char* fileName, const void* data, uint32_t dataSize) {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("fileName: {}", util::safe_fix_null_char_ptr_annotate_ret(fileName)));
			trace.write_all(std::format("data: {}", (void*)data));
			trace.write_all(std::format("dataSize: {}", dataSize));
		}

		intf()->FileWrite(fileName, data, dataSize);
	}

	uint32_t StorageImpl::FileRead(const char* fileName, void* data, uint32_t dataSize) {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("fileName: {}", util::safe_fix_null_char_ptr_annotate_ret(fileName)));
			trace.write_all(std::format("data: {}", (void*)data));
			trace.write_all(std::format("dataSize: {}", dataSize));
		}

		auto result = intf()->FileRead(fileName, data, dataSize);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	void StorageImpl::FileDelete(const char* fileName) {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("fileName: {}", util::safe_fix_null_char_ptr_annotate_ret(fileName)));
		}

		intf()->FileDelete(fileName);
	}

	bool StorageImpl::FileExists(const char* fileName) {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("fileName: {}", util::safe_fix_null_char_ptr_annotate_ret(fileName)));
		}

		auto result = intf()->FileExists(fileName);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	uint32_t StorageImpl::GetFileSize(const char* fileName) {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("fileName: {}", util::safe_fix_null_char_ptr_annotate_ret(fileName)));
		}

		auto result = intf()->GetFileSize(fileName);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	uint32_t StorageImpl::GetFileTimestamp(const char* fileName) {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("fileName: {}", util::safe_fix_null_char_ptr_annotate_ret(fileName)));
		}

		auto result = intf()->GetFileTimestamp(fileName);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	uint32_t StorageImpl::GetFileCount() {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };

		auto result = intf()->GetFileCount();

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	const char* StorageImpl::GetFileNameByIndex(uint32_t index) {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("index: {}", index));
		}

		auto result = intf()->GetFileNameByIndex(index);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", util::safe_fix_null_char_ptr_annotate_ret(result)));
		}

		return result;
	}

	void StorageImpl::GetFileNameCopyByIndex(uint32_t index, char* buffer, uint32_t bufferLength) {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("index: {}", index));
			trace.write_all(std::format("buffer: {}", (void*)buffer));
			trace.write_all(std::format("bufferLength: {}", bufferLength));
		}

		intf()->GetFileNameCopyByIndex(index, buffer, bufferLength);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("buffer: {}", util::safe_fix_null_char_ptr_annotate(buffer, bufferLength)));
		}
	}

	void StorageImpl::FileShare(const char* fileName
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
		, IFileShareListener* const listener
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("fileName: {}", util::safe_fix_null_char_ptr_annotate_ret(fileName)));
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		intf()->FileShare(fileName
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
			, listener
#endif	
		);
	}

	void StorageImpl::DownloadSharedFile(SharedFileID sharedFileID
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
		, ISharedFileDownloadListener* const listener
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("sharedFileID: {}", sharedFileID));
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		intf()->DownloadSharedFile(sharedFileID
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
			, listener
#endif	
		);
	}

	const char* StorageImpl::GetSharedFileName(SharedFileID sharedFileID) {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("sharedFileID: {}", sharedFileID));
		}

		auto result = intf()->GetSharedFileName(sharedFileID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", util::safe_fix_null_char_ptr_annotate_ret(result)));
		}

		return result;
	}

	void StorageImpl::GetSharedFileNameCopy(SharedFileID sharedFileID, char* buffer, uint32_t bufferLength) {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("sharedFileID: {}", sharedFileID));
			trace.write_all(std::format("buffer: {}", (void*)buffer));
			trace.write_all(std::format("bufferLength: {}", bufferLength));
		}

		intf()->GetSharedFileNameCopy(sharedFileID, buffer, bufferLength);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("buffer: {}", util::safe_fix_null_char_ptr_annotate(buffer, bufferLength)));
		}
	}

	uint32_t StorageImpl::GetSharedFileSize(SharedFileID sharedFileID) {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("sharedFileID: {}", sharedFileID));
		}

		auto result = intf()->GetSharedFileSize(sharedFileID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	GalaxyID StorageImpl::GetSharedFileOwner(SharedFileID sharedFileID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("sharedFileID: {}", sharedFileID));
		}

		auto result = intf()->GetSharedFileOwner(sharedFileID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	uint32_t StorageImpl::SharedFileRead(SharedFileID sharedFileID, void* data, uint32_t dataSize, uint32_t offset) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("sharedFileID: {}", sharedFileID));
			trace.write_all(std::format("data: {}", (void*)data));
			trace.write_all(std::format("dataSize: {}", dataSize));
			trace.write_all(std::format("offset: {}", offset));
		}

		auto result = intf()->SharedFileRead(sharedFileID, data, dataSize, offset);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	void StorageImpl::SharedFileClose(SharedFileID sharedFileID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("sharedFileID: {}", sharedFileID));
		}

		intf()->SharedFileClose(sharedFileID);
	}

	uint32_t StorageImpl::GetDownloadedSharedFileCount() {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		auto result = intf()->GetDownloadedSharedFileCount();

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	SharedFileID StorageImpl::GetDownloadedSharedFileByIndex(uint32_t index) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("index: {}", index));
		}

		auto result = intf()->GetDownloadedSharedFileByIndex(index);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}
}

#endif
