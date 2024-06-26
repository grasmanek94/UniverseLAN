#pragma once

#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE

#include "ProxifySingleShotListener.hxx"

#include <ICloudStorage.h>

namespace universelan::client {
	using namespace galaxy::api;

	class CloudStorageGetFileListListener : public ICloudStorageGetFileListListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(CloudStorageGetFileListListener, ICloudStorageGetFileListListener);

	public:
		virtual void OnGetFileListSuccess(uint32_t fileCount, uint32_t quota, uint32_t quotaUsed);
		virtual void OnGetFileListFailure(FailureReason failureReason);
	};

	class CloudStorageGetFileListener : public ICloudStorageGetFileListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(CloudStorageGetFileListener, ICloudStorageGetFileListener);

	public:
#if !GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE_SAVEGAME
		virtual void OnGetFileSuccess(const char* container, const char* name, uint32_t fileSize, uint32_t metadataCount);
#else
		virtual void OnGetFileSuccess(const char* container, const char* name, uint32_t fileSize, SavegameType savegameType, const char* savegameID);
#endif

		virtual void OnGetFileFailure(const char* container, const char* name, FailureReason failureReason);
	};

	class CloudStoragePutFileListener : public ICloudStoragePutFileListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(CloudStoragePutFileListener, ICloudStoragePutFileListener);

	public:
		virtual void OnPutFileSuccess(const char* container, const char* name);
		virtual void OnPutFileFailure(const char* container, const char* name, FailureReason failureReason);

	};

	class CloudStorageDeleteFileListener : public ICloudStorageDeleteFileListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(CloudStorageDeleteFileListener, ICloudStorageDeleteFileListener);

	public:
		virtual void OnDeleteFileSuccess(const char* container, const char* name);
		virtual void OnDeleteFileFailure(const char* container, const char* name, FailureReason failureReason);
	};
}

#endif
