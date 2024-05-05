#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE

#include "StorageListener.hxx"

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

	void FileShareListener::OnFileShareSuccess(const char* fileName, SharedFileID sharedFileID)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("fileName: {}", util::safe_fix_null_char_ptr_annotate_ret(fileName)));
			trace.write_all(std::format("sharedFileID: {}", sharedFileID));
		}
	}

	void FileShareListener::OnFileShareFailure(const char* fileName, FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("fileName: {}", util::safe_fix_null_char_ptr_annotate_ret(fileName)));
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}
	}

	void SharedFileDownloadListener::OnSharedFileDownloadSuccess(SharedFileID sharedFileID, const char* fileName)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("sharedFileID: {}", sharedFileID));
			trace.write_all(std::format("fileName: {}", util::safe_fix_null_char_ptr_annotate_ret(fileName)));
		}
	}

	void SharedFileDownloadListener::OnSharedFileDownloadFailure(SharedFileID sharedFileID, FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("sharedFileID: {}", sharedFileID));
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}
	}
}

#endif
