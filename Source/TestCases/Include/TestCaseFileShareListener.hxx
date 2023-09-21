#pragma once

#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE

#include "TestCaseClientDetails.hxx"

class FileShareListenerImplGlobal : public galaxy::api::GlobalFileShareListener
{
public:
	using on_file_share_success_func_t = std::function<void(const char* fileName, SharedFileID)>;
	using on_file_share_failure_func_t = std::function<void(const char* fileName, FailureReason)>;

private:
	on_file_share_success_func_t on_file_share_success;
	on_file_share_failure_func_t on_file_share_failure;

public:
	FileShareListenerImplGlobal(
		on_file_share_success_func_t on_file_share_success = nullptr,
		on_file_share_failure_func_t on_file_share_failure = nullptr) :
		on_file_share_success{ on_file_share_success },
		on_file_share_failure{ on_file_share_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~FileShareListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnFileShareSuccess(const char* fileName, SharedFileID sharedFileID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"fileName: {} sharedFileID: {}",
			fileName, sharedFileID
		).c_str());


		if (on_file_share_success != nullptr) {
			on_file_share_success(fileName, sharedFileID);
		}
	}

	virtual void OnFileShareFailure(const char* fileName, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"fileName: {} failureReason: {}",
			fileName, magic_enum::enum_name(failureReason)
		).c_str());


		if (on_file_share_failure != nullptr) {
			on_file_share_failure(fileName, failureReason);
		}
	}
};

class FileShareListenerImplLocal : public galaxy::api::IFileShareListener
{
public:
	using on_file_share_success_func_t = std::function<void(const char* fileName, SharedFileID)>;
	using on_file_share_failure_func_t = std::function<void(const char* fileName, FailureReason)>;

private:
	on_file_share_success_func_t on_file_share_success;
	on_file_share_failure_func_t on_file_share_failure;

public:
	FileShareListenerImplLocal(
		on_file_share_success_func_t on_file_share_success = nullptr,
		on_file_share_failure_func_t on_file_share_failure = nullptr) :
		on_file_share_success{ on_file_share_success },
		on_file_share_failure{ on_file_share_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~FileShareListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnFileShareSuccess(const char* fileName, SharedFileID sharedFileID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"fileName: {} sharedFileID: {}",
			fileName, sharedFileID
		).c_str());


		if (on_file_share_success != nullptr) {
			on_file_share_success(fileName, sharedFileID);
		}
	}

	virtual void OnFileShareFailure(const char* fileName, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"fileName: {} failureReason: {}",
			fileName, magic_enum::enum_name(failureReason)
		).c_str());


		if (on_file_share_failure != nullptr) {
			on_file_share_failure(fileName, failureReason);
		}
	}
};

#endif
