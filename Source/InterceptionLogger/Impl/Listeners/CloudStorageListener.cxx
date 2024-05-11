#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE

#include "CloudStorageListener.hxx"
#include "ProxifySingleShotListener.hxx"

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

	void CloudStorageGetFileListListener::OnGetFileListSuccess(uint32_t fileCount, uint32_t quota, uint32_t quotaUsed)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("fileCount: {}", fileCount));
			trace.write_all(std::format("quota: {}", quota));
			trace.write_all(std::format("quotaUsed: {}", quotaUsed));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnGetFileListSuccess(fileCount, quota, quotaUsed));
	}

	void CloudStorageGetFileListListener::OnGetFileListFailure(FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC();
	}

	void CloudStorageGetFileListener::OnGetFileSuccess(const char* container, const char* name, uint32_t fileSize, uint32_t metadataCount)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("container: {}", util::safe_fix_null_char_ptr_annotate_ret(container)));
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("fileSize: {}", fileSize));
			trace.write_all(std::format("metadataCount: {}", metadataCount));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnGetFileSuccess(container, name, fileSize, metadataCount));
	}

	void CloudStorageGetFileListener::OnGetFileFailure(const char* container, const char* name, FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("container: {}", util::safe_fix_null_char_ptr_annotate_ret(container)));
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnGetFileFailure(container, name, failureReason));
	}

#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE_SAVEGAME
	void CloudStorageGetFileListener::OnGetFileSuccess(const char* container, const char* name, uint32_t fileSize, SavegameType savegameType, const char* savegameID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("container: {}", util::safe_fix_null_char_ptr_annotate_ret(container)));
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("fileSize: {}", fileSize));
			trace.write_all(std::format("savegameType: {}", magic_enum::enum_name(savegameType)));
			trace.write_all(std::format("savegameID: {}", util::safe_fix_null_char_ptr_annotate_ret(savegameID)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnGetFileSuccess(container, name, fileSize, savegameType, savegameID));
	}
#endif

	void CloudStoragePutFileListener::OnPutFileSuccess(const char* container, const char* name)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("container: {}", util::safe_fix_null_char_ptr_annotate_ret(container)));
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnPutFileSuccess(container, name));
	}

	void CloudStoragePutFileListener::OnPutFileFailure(const char* container, const char* name, FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("container: {}", util::safe_fix_null_char_ptr_annotate_ret(container)));
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnPutFileFailure(container, name, failureReason));
	}

	void CloudStorageDeleteFileListener::OnDeleteFileSuccess(const char* container, const char* name)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("container: {}", util::safe_fix_null_char_ptr_annotate_ret(container)));
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnDeleteFileSuccess(container, name));
	}

	void CloudStorageDeleteFileListener::OnDeleteFileFailure(const char* container, const char* name, FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("container: {}", util::safe_fix_null_char_ptr_annotate_ret(container)));
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnDeleteFileFailure(container, name, failureReason));
	}
}

#endif
