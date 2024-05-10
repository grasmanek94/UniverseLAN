#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE

#include "CloudStorage.hxx"

#include "Listeners/CloudStorageListener.hxx"

#include <GalaxyID.hxx>
#include <Tracer.hxx>
#include <SafeStringCopy.hxx>

#include <magic_enum/magic_enum.hpp>

#include <format>

namespace universelan::client {
	using namespace galaxy::api;

	namespace {
		const auto TraceContext = tracer::Trace::ICLOUDSTORAGE;
	}

	CloudStorageImpl::CloudStorageImpl(FuncT::F intf, IListenerRegistrar* notifications) :
		intf{ intf },
		notifications{ notifications },
		listeners{ notifications } {
		listeners.AddListener<CloudStorageGetFileListListener>();
		listeners.AddListener<CloudStorageGetFileListener>();
		listeners.AddListener<CloudStoragePutFileListener>();
		listeners.AddListener<CloudStorageDeleteFileListener>();
	}

	CloudStorageImpl::~CloudStorageImpl() {
		listeners.UnregisterAllListeners();
	}

	void CloudStorageImpl::GetFileList(const char* container, ICloudStorageGetFileListListener* listener) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("container: {}", util::safe_fix_null_char_ptr_annotate_ret(container)));
			trace.write_all(std::format("listener: {}", (void*)listener));
		}

		intf()->GetFileList(container, listener);
	}

	const char* CloudStorageImpl::GetFileNameByIndex(uint32_t index) const {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("index: {}", index));
		}

		auto result = intf()->GetFileNameByIndex(index);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", util::safe_fix_null_char_ptr_annotate_ret(result)));
		}

		return result;
	}

	uint32_t CloudStorageImpl::GetFileSizeByIndex(uint32_t index) const {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("index: {}", index));
		}

		auto result = intf()->GetFileSizeByIndex(index);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	uint32_t CloudStorageImpl::GetFileTimestampByIndex(uint32_t index) const {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("index: {}", index));
		}

		auto result = intf()->GetFileTimestampByIndex(index);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE_GETFILEHASHBYINDEX
	const char* CloudStorageImpl::GetFileHashByIndex(uint32_t index) const
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		auto result = intf()->GetFileHashByIndex(index);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", util::safe_fix_null_char_ptr_annotate_ret(result)));
		}

		return result;
	}
#endif

	void CloudStorageImpl::GetFile(const char* container, const char* name, void* userParam, WriteFunc writeFunc, ICloudStorageGetFileListener* listener) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("container: {}", util::safe_fix_null_char_ptr_annotate_ret(container)));
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("userParam: {}", userParam));
			trace.write_all(std::format("writeFunc: {}", (void*)writeFunc));
			trace.write_all(std::format("listener: {}", (void*)listener));
		}

		intf()->GetFile(container, name, userParam, writeFunc, listener);
	}

	void CloudStorageImpl::GetFile(const char* container, const char* name, void* buffer, uint32_t bufferLength, ICloudStorageGetFileListener* listener) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("container: {}", util::safe_fix_null_char_ptr_annotate_ret(container)));
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("buffer: {}", buffer));
			trace.write_all(std::format("bufferLength: {}", bufferLength));
			trace.write_all(std::format("listener: {}", (void*)listener));
		}

		intf()->GetFile(container, name, buffer, bufferLength, listener);
	}

	void CloudStorageImpl::GetFileMetadata(const char* container, const char* name, ICloudStorageGetFileListener* listener) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("container: {}", util::safe_fix_null_char_ptr_annotate_ret(container)));
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("listener: {}", (void*)listener));
		}

		intf()->GetFileMetadata(container, name, listener);
	}

#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE_METADATAIDX_FUNCS
	const char* CloudStorageImpl::GetFileMetadataKeyByIndex(uint32_t index) const {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("index: {}", index));
		}

		auto result = intf()->GetFileMetadataKeyByIndex(index);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", util::safe_fix_null_char_ptr_annotate_ret(result)));
		}

		return result;
	}

	const char* CloudStorageImpl::GetFileMetadataValueByIndex(uint32_t index) const {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("index: {}", index));
		}

		auto result = intf()->GetFileMetadataValueByIndex(index);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", util::safe_fix_null_char_ptr_annotate_ret(result)));
		}

		return result;
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
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("container: {}", util::safe_fix_null_char_ptr_annotate_ret(container)));
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("userParam: {}", userParam));
			trace.write_all(std::format("readFunc: {}", (void*)readFunc));
			trace.write_all(std::format("rewindFunc: {}", (void*)rewindFunc));
			trace.write_all(std::format("listener: {}", (void*)listener));
			trace.write_all(std::format("metadataKeys: {}", (void*)metadataKeys));
			trace.write_all(std::format("metadataValues: {}", (void*)metadataValues));
			trace.write_all(std::format("timeStamp: {}", timeStamp));

			if (metadataKeys != nullptr && metadataValues != nullptr) {
				int index = 0;
				while (metadataKeys[index] && metadataValues[index]) {
					trace.write_all(std::format("[METADATA] {}: {}",
						util::safe_fix_null_char_ptr_annotate_ret(metadataKeys[index]),
						util::safe_fix_null_char_ptr_annotate_ret(metadataValues[index])
					));
					++index;
				}	
			}
		}

		intf()->PutFile(container, name, userParam, readFunc, rewindFunc, listener, metadataKeys, metadataValues
#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE_PUTFILE_TIMESTAMP
			, timeStamp
#endif
		);
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
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("container: {}", util::safe_fix_null_char_ptr_annotate_ret(container)));
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("buffer: {}", buffer));
			trace.write_all(std::format("bufferLength: {}", bufferLength));
			trace.write_all(std::format("listener: {}", (void*)listener));
			trace.write_all(std::format("metadataKeys: {}", (void*)metadataKeys));
			trace.write_all(std::format("metadataValues: {}", (void*)metadataValues));
			trace.write_all(std::format("timeStamp: {}", timeStamp));

			if (metadataKeys != nullptr && metadataValues != nullptr) {
				int index = 0;
				while (metadataKeys[index] && metadataValues[index]) {
					trace.write_all(std::format("[METADATA] {}: {}",
						util::safe_fix_null_char_ptr_annotate_ret(metadataKeys[index]),
						util::safe_fix_null_char_ptr_annotate_ret(metadataValues[index])
					));
					++index;
				}
			}
		}

		intf()->PutFile(container, name, buffer, bufferLength, listener, metadataKeys, metadataValues
#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE_PUTFILE_TIMESTAMP
			, timeStamp
#endif
		);
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
#endif

#pragma push_macro("DeleteFile")
#undef DeleteFile
	void CloudStorageImpl::DeleteFile(const char* container, const char* name, ICloudStorageDeleteFileListener* listener)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("container: {}", util::safe_fix_null_char_ptr_annotate_ret(container)));
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("listener: {}", (void*)listener));
		}

		intf()->DeleteFile(container, name, listener);
	}
#pragma pop_macro ("DeleteFile")

#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE_SAVEGAME
	void CloudStorageImpl::PutFile(const char* container, const char* name, void* userParam, ReadFunc readFunc, RewindFunc rewindFunc, ICloudStoragePutFileListener* listener, SavegameType savegameType, uint32_t timeStamp)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("container: {}", util::safe_fix_null_char_ptr_annotate_ret(container)));
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("userParam: {}", userParam));
			trace.write_all(std::format("readFunc: {}", (void*)readFunc));
			trace.write_all(std::format("rewindFunc: {}", (void*)rewindFunc));
			trace.write_all(std::format("listener: {}", (void*)listener));
			trace.write_all(std::format("savegameType: {}", magic_enum::enum_name(savegameType)));
			trace.write_all(std::format("timeStamp: {}", timeStamp));
		}

		intf()->PutFile(container, name, userParam, readFunc, rewindFunc, listener, savegameType, timeStamp);
	}

	void CloudStorageImpl::PutFile(const char* container, const char* name, const void* buffer, uint32_t bufferLength, ICloudStoragePutFileListener* listener, SavegameType savegameType, uint32_t timeStamp)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("container: {}", util::safe_fix_null_char_ptr_annotate_ret(container)));
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("buffer: {}", buffer));
			trace.write_all(std::format("bufferLength: {}", bufferLength));
			trace.write_all(std::format("listener: {}", (void*)listener));
			trace.write_all(std::format("savegameType: {}", magic_enum::enum_name(savegameType)));
			trace.write_all(std::format("timeStamp: {}", timeStamp));
		}

		intf()->PutFile(container, name, buffer, bufferLength, listener, savegameType, timeStamp);
	}

	void CloudStorageImpl::OpenSavegame()
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		intf()->OpenSavegame();
	}

	void CloudStorageImpl::CloseSavegame()
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		intf()->CloseSavegame();
	}
#endif
}

#endif
