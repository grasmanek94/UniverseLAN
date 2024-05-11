#pragma once

#include "ProxifySingleShotListener.hxx"

#include <IStorage.h>

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
