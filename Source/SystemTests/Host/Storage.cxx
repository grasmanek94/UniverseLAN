#include "Host.hxx"

#include <algorithm>
#include <array>
#include <limits>
#include <string>

namespace universelan::systemtest::host
{
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE
namespace
{
constexpr const char fileShareName[] = "universelan-system-file-share-server-persisted-roundtrip-v1.bin";
constexpr std::array<std::uint8_t, 13> fileSharePayload{{0x75, 0x6e, 0x69, 0x00, 0x76, 0x65, 0x72, 0x73, 0x65, 0x6c, 0x61, 0x6e, 0xa5}};
constexpr uint32_t fileShareOffset = 4;

#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
using FileShareListenerBase = galaxy::api::IFileShareListener;
using SharedFileDownloadListenerBase = galaxy::api::ISharedFileDownloadListener;
#else
using FileShareListenerBase = galaxy::api::GlobalFileShareListener;
using SharedFileDownloadListenerBase = galaxy::api::GlobalSharedFileDownloadListener;
#endif

struct FileShareListener final : FileShareListenerBase
{
    bool completed = false;
    bool succeeded = false;
    bool failedAsExpected = false;
    galaxy::api::SharedFileID sharedFileId = 0;

    void OnFileShareSuccess(const char* name, galaxy::api::SharedFileID id) override
    {
        completed = true;
        succeeded = name != nullptr && std::string(name) == fileShareName && id != 0;
        if (succeeded) sharedFileId = id;
    }

    void OnFileShareFailure(const char* name, FailureReason reason) override
    {
        completed = true;
        failedAsExpected = name != nullptr && std::string(name) == fileShareName
            && reason == IFileShareListener::FAILURE_REASON_UNDEFINED;
    }
};

struct SharedFileDownloadListener final : SharedFileDownloadListenerBase
{
    SharedFileDownloadListener(galaxy::api::SharedFileID expectedId, const char* expectedName)
        : expectedId(expectedId), expectedName(expectedName) {}

    galaxy::api::SharedFileID expectedId;
    const char* expectedName;
    unsigned int successes = 0;
    unsigned int failures = 0;
    bool succeeded = false;
    galaxy::api::SharedFileID failureId = 0;
    galaxy::api::ISharedFileDownloadListener::FailureReason failureReason
        = galaxy::api::ISharedFileDownloadListener::FAILURE_REASON_UNDEFINED;

    void OnSharedFileDownloadSuccess(galaxy::api::SharedFileID id, const char* name) override
    {
        ++successes;
        succeeded = expectedName != nullptr && id == expectedId && name != nullptr && std::string(name) == expectedName;
    }

    void OnSharedFileDownloadFailure(galaxy::api::SharedFileID id, FailureReason reason) override
    {
        ++failures;
        failureId = id;
        failureReason = reason;
    }
};
}

bool fileShareServerPersistedRoundtrip(Api& api, const Arguments& arguments)
{
    galaxy::api::IStorage* storage = api.storage();
    if (storage == nullptr) return false;

    storage->FileWrite(fileShareName, fileSharePayload.data(), static_cast<uint32_t>(fileSharePayload.size()));
    std::array<std::uint8_t, fileSharePayload.size()> localRead{};
    if (!storage->FileExists(fileShareName) || storage->GetFileSize(fileShareName) != fileSharePayload.size()
        || storage->FileRead(fileShareName, localRead.data(), static_cast<uint32_t>(localRead.size())) != localRead.size()
        || localRead != fileSharePayload) return false;

    FileShareListener shareListener;
    storage->FileShare(fileShareName
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
        , &shareListener
#endif
    );
    if (!pumpUntil(api, arguments.timeoutSeconds, [&shareListener] { return shareListener.completed; }) || !shareListener.succeeded) return false;

    storage->SharedFileClose(shareListener.sharedFileId);
    if (storage->GetDownloadedSharedFileCount() != 0) return false;

    SharedFileDownloadListener downloadListener(shareListener.sharedFileId, fileShareName);
    storage->DownloadSharedFile(shareListener.sharedFileId
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
        , &downloadListener
#endif
    );
    if (!pumpUntil(api, arguments.timeoutSeconds, [&downloadListener] { return downloadListener.successes != 0 || downloadListener.failures != 0; })
        || downloadListener.successes != 1 || downloadListener.failures != 0 || !downloadListener.succeeded) return false;
    const char* downloadedName = storage->GetSharedFileName(shareListener.sharedFileId);
    if (storage->GetDownloadedSharedFileCount() != 1 || storage->GetDownloadedSharedFileByIndex(0) != shareListener.sharedFileId
        || downloadedName == nullptr || std::string(downloadedName) != fileShareName
        || storage->GetSharedFileSize(shareListener.sharedFileId) != fileSharePayload.size()) return false;

    std::array<char, 128> copiedName{};
    storage->GetSharedFileNameCopy(shareListener.sharedFileId, copiedName.data(), static_cast<uint32_t>(copiedName.size()));
    std::array<std::uint8_t, fileSharePayload.size()> fullRead{};
    std::array<std::uint8_t, fileSharePayload.size() - fileShareOffset> offsetRead{};
    if (std::string(copiedName.data()) != fileShareName
        || storage->SharedFileRead(shareListener.sharedFileId, fullRead.data(), static_cast<uint32_t>(fullRead.size())) != fullRead.size()
        || fullRead != fileSharePayload
        || storage->SharedFileRead(shareListener.sharedFileId, offsetRead.data(), static_cast<uint32_t>(offsetRead.size()), fileShareOffset) != offsetRead.size()
        || !std::equal(offsetRead.begin(), offsetRead.end(), fileSharePayload.begin() + fileShareOffset)) return false;

    storage->SharedFileClose(shareListener.sharedFileId);
    if (storage->GetDownloadedSharedFileCount() != 0) return false;

    const galaxy::api::SharedFileID invalidId = std::numeric_limits<galaxy::api::SharedFileID>::max();
    SharedFileDownloadListener invalidDownloadListener(invalidId, nullptr);
    storage->DownloadSharedFile(invalidId
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
        , &invalidDownloadListener
#endif
    );
    return pumpUntil(api, arguments.timeoutSeconds, [&invalidDownloadListener] { return invalidDownloadListener.successes != 0 || invalidDownloadListener.failures != 0; })
        && invalidDownloadListener.successes == 0 && invalidDownloadListener.failures == 1 && !invalidDownloadListener.succeeded
        && storage->GetDownloadedSharedFileCount() == 0;
}

bool fileShareServerPolicyDenied(Api& api, const Arguments& arguments)
{
    galaxy::api::IStorage* storage = api.storage();
    if (storage == nullptr) return false;

    storage->FileWrite(fileShareName, fileSharePayload.data(), static_cast<uint32_t>(fileSharePayload.size()));
    std::array<std::uint8_t, fileSharePayload.size()> localRead{};
    if (!storage->FileExists(fileShareName) || storage->GetFileSize(fileShareName) != fileSharePayload.size()
        || storage->FileRead(fileShareName, localRead.data(), static_cast<uint32_t>(localRead.size())) != localRead.size()
        || localRead != fileSharePayload || storage->GetDownloadedSharedFileCount() != 0) return false;

    FileShareListener shareListener;
    storage->FileShare(fileShareName
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
        , &shareListener
#endif
    );
    return pumpUntil(api, arguments.timeoutSeconds, [&shareListener] { return shareListener.completed; })
        && !shareListener.succeeded && shareListener.failedAsExpected && shareListener.sharedFileId == 0
        && storage->GetDownloadedSharedFileCount() == 0;
}

bool fileShareServerDownloadPolicyDenied(Api& api, const Arguments& arguments)
{
    galaxy::api::IStorage* storage = api.storage();
    if (storage == nullptr) return false;

    storage->FileWrite(fileShareName, fileSharePayload.data(), static_cast<uint32_t>(fileSharePayload.size()));
    std::array<std::uint8_t, fileSharePayload.size()> localRead{};
    if (!storage->FileExists(fileShareName) || storage->GetFileSize(fileShareName) != fileSharePayload.size()
        || storage->FileRead(fileShareName, localRead.data(), static_cast<uint32_t>(localRead.size())) != localRead.size()
        || localRead != fileSharePayload || storage->GetDownloadedSharedFileCount() != 0) return false;

    FileShareListener shareListener;
    storage->FileShare(fileShareName
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
        , &shareListener
#endif
    );
    if (!pumpUntil(api, arguments.timeoutSeconds, [&shareListener] { return shareListener.completed; })
        || !shareListener.succeeded || shareListener.sharedFileId == 0) return false;

    storage->SharedFileClose(shareListener.sharedFileId);
    if (storage->GetDownloadedSharedFileCount() != 0) return false;

    SharedFileDownloadListener downloadListener(shareListener.sharedFileId, nullptr);
    storage->DownloadSharedFile(shareListener.sharedFileId
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE_FILESHARELISTENERS
        , &downloadListener
#endif
    );
    const bool receivedTerminalCallback = pumpUntil(api, arguments.timeoutSeconds, [&downloadListener]
    {
        return downloadListener.successes != 0 || downloadListener.failures != 0;
    });
    pumpUntil(api, 1, [] { return false; });
    return receivedTerminalCallback && downloadListener.successes == 0 && downloadListener.failures == 1
        && downloadListener.failureId == shareListener.sharedFileId
        && downloadListener.failureReason == galaxy::api::ISharedFileDownloadListener::FAILURE_REASON_UNDEFINED
        && storage->GetDownloadedSharedFileCount() == 0;
}
#endif
}
