#pragma once

#include "ProxifySingleShotListener.hxx"

#include <IStorage.h>

// REVIEW: The implementation is excluded by GALAXY_BUILD_FEATURE_HAS_ISTORAGE in
// StorageListener.cxx, but these declarations remain visible in feature-off builds. A consumer
// can therefore instantiate a declared listener and reach missing definitions at link time.
// Apply the same feature guard to this header (or provide feature-off definitions).
namespace universelan::client {
	using namespace galaxy::api;

	class FileShareListener : public IFileShareListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(FileShareListener, IFileShareListener);

	public:
		virtual void OnFileShareSuccess(const char* fileName, SharedFileID sharedFileID);
		virtual void OnFileShareFailure(const char* fileName, FailureReason failureReason);
	};

	class SharedFileDownloadListener : public ISharedFileDownloadListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(SharedFileDownloadListener, ISharedFileDownloadListener);

	public:
		virtual void OnSharedFileDownloadSuccess(SharedFileID sharedFileID, const char* fileName);
		virtual void OnSharedFileDownloadFailure(SharedFileID sharedFileID, FailureReason failureReason);
	};
}
