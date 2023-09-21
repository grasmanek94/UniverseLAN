#pragma once

#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE

#include "TestCaseClientDetails.hxx"

class SharedFileDownloadListenerImplGlobal : public galaxy::api::GlobalSharedFileDownloadListener
{
public:
	using on_shared_file_download_success_func_t = std::function<void(SharedFileID, const char* fileName)>;
	using on_shared_file_download_failure_func_t = std::function<void(SharedFileID, FailureReason)>;

private:
	on_shared_file_download_success_func_t on_shared_file_download_success;
	on_shared_file_download_failure_func_t on_shared_file_download_failure;

public:
	SharedFileDownloadListenerImplGlobal(
		on_shared_file_download_success_func_t on_shared_file_download_success = nullptr,
		on_shared_file_download_failure_func_t on_shared_file_download_failure = nullptr) :
		on_shared_file_download_success{ on_shared_file_download_success },
		on_shared_file_download_failure{ on_shared_file_download_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~SharedFileDownloadListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnSharedFileDownloadSuccess(SharedFileID sharedFileID, const char* fileName) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"sharedFileID: {} fileName: {}",
			sharedFileID, fileName
		).c_str());


		if (on_shared_file_download_success != nullptr) {
			on_shared_file_download_success(sharedFileID, fileName);
		}
	}

	virtual void OnSharedFileDownloadFailure(SharedFileID sharedFileID, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"sharedFileID: {} failureReason: {}",
			sharedFileID, magic_enum::enum_name(failureReason)
		).c_str());


		if (on_shared_file_download_failure != nullptr) {
			on_shared_file_download_failure(sharedFileID, failureReason);
		}
	}
};

class SharedFileDownloadListenerImplLocal : public galaxy::api::ISharedFileDownloadListener
{
public:
	using on_shared_file_download_success_func_t = std::function<void(SharedFileID, const char* fileName)>;
	using on_shared_file_download_failure_func_t = std::function<void(SharedFileID, FailureReason)>;

private:
	on_shared_file_download_success_func_t on_shared_file_download_success;
	on_shared_file_download_failure_func_t on_shared_file_download_failure;

public:
	SharedFileDownloadListenerImplLocal(
		on_shared_file_download_success_func_t on_shared_file_download_success = nullptr,
		on_shared_file_download_failure_func_t on_shared_file_download_failure = nullptr) :
		on_shared_file_download_success{ on_shared_file_download_success },
		on_shared_file_download_failure{ on_shared_file_download_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~SharedFileDownloadListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnSharedFileDownloadSuccess(SharedFileID sharedFileID, const char* fileName) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"sharedFileID: {} fileName: {}",
			sharedFileID, fileName
		).c_str());


		if (on_shared_file_download_success != nullptr) {
			on_shared_file_download_success(sharedFileID, fileName);
		}
	}

	virtual void OnSharedFileDownloadFailure(SharedFileID sharedFileID, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"sharedFileID: {} failureReason: {}",
			sharedFileID, magic_enum::enum_name(failureReason)
		).c_str());


		if (on_shared_file_download_failure != nullptr) {
			on_shared_file_download_failure(sharedFileID, failureReason);
		}
	}
};

#endif
