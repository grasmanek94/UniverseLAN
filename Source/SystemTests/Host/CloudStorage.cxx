#include "Host.hxx"

#include <array>
#include <cstdint>
#include <string>

namespace universelan::systemtest::host
{
#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE
namespace
{
constexpr const char cloudContainer[] = "universelan-system-cloud-storage-local-roundtrip-v1";
constexpr const char cloudName[] = "cloud-storage-local-roundtrip.bin";
constexpr std::array<std::uint8_t, 13> cloudPayload{{0x75, 0x6e, 0x69, 0x00, 0x76, 0x65, 0x72, 0x73, 0x65, 0x6c, 0x61, 0x6e, 0xa5}};
constexpr std::uint32_t cloudTimestamp = 1700000000;
constexpr const char cloudHash[] = "0123456789abcdef0123456789abcdef";

struct PutFileListener final : galaxy::api::ICloudStoragePutFileListener
{
    unsigned int successes = 0;
    bool failed = false;
    bool metadataMatches = false;

    void OnPutFileSuccess(const char* container, const char* name) override
    {
        metadataMatches = container != nullptr && name != nullptr
            && std::string(container) == cloudContainer && std::string(name) == cloudName;
        ++successes;
    }

    void OnPutFileFailure(const char*, const char*, FailureReason) override { failed = true; }
};

struct GetFileListListener final : galaxy::api::ICloudStorageGetFileListListener
{
    explicit GetFileListListener(galaxy::api::ICloudStorage* storage) : storage(storage) {}

    galaxy::api::ICloudStorage* storage;
    unsigned int successes = 0;
    bool failed = false;
    bool metadataMatches = false;

    void OnGetFileListSuccess(const std::uint32_t fileCount, const std::uint32_t, const std::uint32_t) override
    {
        if (storage != nullptr && fileCount == 1)
        {
            const char* name = storage->GetFileNameByIndex(0);
            const char* hash = storage->GetFileHashByIndex(0);
            metadataMatches = name != nullptr && hash != nullptr && std::string(name) == cloudName
                && storage->GetFileSizeByIndex(0) == cloudPayload.size()
                && storage->GetFileTimestampByIndex(0) == cloudTimestamp
                && std::string(hash) == cloudHash;
        }
        ++successes;
    }

    void OnGetFileListFailure(FailureReason) override { failed = true; }
};

struct GetFileListener final : galaxy::api::ICloudStorageGetFileListener
{
    unsigned int successes = 0;
    bool failed = false;
    bool metadataMatches = false;

    void OnGetFileSuccess(const char* container, const char* name, const std::uint32_t fileSize,
        const galaxy::api::SavegameType savegameType, const char* savegameId) override
    {
        metadataMatches = container != nullptr && name != nullptr && savegameId != nullptr
            && std::string(container) == cloudContainer && std::string(name) == cloudName
            && fileSize == cloudPayload.size() && savegameType == galaxy::api::SAVEGAME_TYPE_MANUAL
            && !std::string(savegameId).empty();
        ++successes;
    }

    void OnGetFileFailure(const char*, const char*, FailureReason) override { failed = true; }
};

struct GetFileMetadataListener final : galaxy::api::ICloudStorageGetFileListener
{
    unsigned int successes = 0;
    bool failed = false;
    bool metadataMatches = false;

    void OnGetFileSuccess(const char* container, const char* name, const std::uint32_t fileSize,
        const galaxy::api::SavegameType savegameType, const char* savegameId) override
    {
        metadataMatches = container != nullptr && name != nullptr && savegameId != nullptr
            && std::string(container) == cloudContainer && std::string(name) == cloudName
            && fileSize == 0 && savegameType == galaxy::api::SAVEGAME_TYPE_MANUAL
            && !std::string(savegameId).empty();
        ++successes;
    }

    void OnGetFileFailure(const char*, const char*, FailureReason) override { failed = true; }
};
}

bool cloudStorageLocalRoundtrip(Api& api, const Arguments& arguments)
{
    galaxy::api::ICloudStorage* storage = api.cloudStorage();
    if (storage == nullptr) return false;

    PutFileListener putListener;
    storage->PutFile(cloudContainer, cloudName, cloudPayload.data(), static_cast<std::uint32_t>(cloudPayload.size()), &putListener,
        galaxy::api::SAVEGAME_TYPE_MANUAL, cloudTimestamp, cloudHash);
    if (!pumpUntil(api, arguments.timeoutSeconds, [&putListener] { return putListener.successes != 0 || putListener.failed; })
        || putListener.successes != 1 || putListener.failed || !putListener.metadataMatches) return false;

    GetFileListListener listListener(storage);
    storage->GetFileList(cloudContainer, &listListener);
    if (!pumpUntil(api, arguments.timeoutSeconds, [&listListener] { return listListener.successes != 0 || listListener.failed; })
        || listListener.successes != 1 || listListener.failed || !listListener.metadataMatches) return false;

    GetFileMetadataListener metadataListener;
    storage->GetFileMetadata(cloudContainer, cloudName, &metadataListener);
    if (!pumpUntil(api, arguments.timeoutSeconds, [&metadataListener] { return metadataListener.successes != 0 || metadataListener.failed; })
        || metadataListener.successes != 1 || metadataListener.failed || !metadataListener.metadataMatches) return false;

    std::array<std::uint8_t, cloudPayload.size()> downloadBuffer{};
    GetFileListener getListener;
    storage->GetFile(cloudContainer, cloudName, downloadBuffer.data(), static_cast<std::uint32_t>(downloadBuffer.size()), &getListener);
    return pumpUntil(api, arguments.timeoutSeconds, [&getListener] { return getListener.successes != 0 || getListener.failed; })
        && getListener.successes == 1 && !getListener.failed && getListener.metadataMatches && downloadBuffer == cloudPayload;
}
#endif
}
