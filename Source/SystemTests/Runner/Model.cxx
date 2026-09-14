#include "Runner.hxx"

#include "Common/Protocol.hxx"

#include <nlohmann/json.hpp>

#include <fstream>
#include <charconv>
#include <map>
#include <set>
#include <stdexcept>

namespace universelan::systemtest::runner
{
namespace
{
using json = nlohmann::json;

[[noreturn]] void invalidManifest() { throw std::runtime_error("Manifest validation failed"); }

void objectHasOnly(const json& value, std::initializer_list<const char*> allowed)
{
    if (!value.is_object()) invalidManifest();
    for (const auto& [key, ignored] : value.items())
    {
        bool known = false;
        for (const char* name : allowed) known = known || key == name;
        if (!known) invalidManifest();
    }
}

const json& required(const json& value, const char* name)
{
    if (!value.contains(name)) invalidManifest();
    return value.at(name);
}

std::string requiredToken(const json& value, const char* name)
{
    const json& field = required(value, name);
    if (!field.is_string() || !common::token(field.get<std::string>())) invalidManifest();
    return field.get<std::string>();
}

int requiredTimeout(const json& value, const char* name)
{
    const json& field = required(value, name);
    if (!field.is_number_integer()) invalidManifest();
    const int timeout = field.get<int>();
    if (timeout < 1 || timeout > 600) invalidManifest();
    return timeout;
}

std::vector<std::string> tokenArray(const json& value)
{
    if (!value.is_array()) invalidManifest();
    std::vector<std::string> result;
    for (const json& item : value)
    {
        if (!item.is_string() || !common::token(item.get<std::string>())) invalidManifest();
        result.push_back(item.get<std::string>());
    }
    return result;
}
}

Scenario parseScenario(const fs::path& manifest)
{
    std::ifstream input(manifest);
    if (!input) invalidManifest();
    json root;
    try { input >> root; }
    catch (...) { invalidManifest(); }
    objectHasOnly(root, {"name", "runtimeProvider", "timeoutSeconds", "server", "websocket", "hosts"});
    Scenario result;
    result.name = requiredToken(root, "name");
    result.provider = requiredToken(root, "runtimeProvider");
    if (result.provider != "universelan" && result.provider != "gog") invalidManifest();
    result.timeoutSeconds = requiredTimeout(root, "timeoutSeconds");
    if (root.contains("server"))
    {
        const json& server = root.at("server");
        objectHasOnly(server, {"enabled", "readyEvent", "configuration"});
        if (!required(server, "enabled").is_boolean()) invalidManifest();
        result.serverEnabled = server.at("enabled").get<bool>();
        if (result.serverEnabled) result.serverReadyEvent = requiredToken(server, "readyEvent");
        if (server.contains("configuration"))
        {
            const json& configuration = server.at("configuration");
            objectHasOnly(configuration, {"maxConnections", "tickRate", "allowFileSharingDownload", "allowFileSharingUpload"});
            for (const auto& [key, setting] : configuration.items())
            {
                if (key == "allowFileSharingDownload" || key == "allowFileSharingUpload")
                {
                    if (!setting.is_boolean()) invalidManifest();
                    if (key == "allowFileSharingDownload") result.serverAllowFileSharingDownload = setting.get<bool>();
                    else result.serverAllowFileSharingUpload = setting.get<bool>();
                    continue;
                }
                if (!setting.is_number_integer() || setting.get<int>() < 1) invalidManifest();
                if (key == "maxConnections") result.serverMaxConnections = setting.get<int>();
                if (key == "tickRate") result.serverMaxTickRate = setting.get<int>();
            }
        }
    }
    if (result.provider == "gog" && result.serverEnabled) invalidManifest();
    if (root.contains("websocket"))
    {
        const json& webSocket = root.at("websocket");
        objectHasOnly(webSocket, {"enabled", "readyEvent"});
        if (!required(webSocket, "enabled").is_boolean()) invalidManifest();
        result.webSocketEnabled = webSocket.at("enabled").get<bool>();
        if (result.webSocketEnabled) result.webSocketReadyEvent = requiredToken(webSocket, "readyEvent");
    }
    const json& hosts = required(root, "hosts");
    if (!hosts.is_array() || hosts.empty()) invalidManifest();
    std::set<std::string> roles;
    std::map<std::uint64_t, std::string> identityGroups;
    std::map<std::string, std::uint64_t> persistenceGroupIdentities;
    std::set<std::string> declaredEvents;
    if (result.serverEnabled) declaredEvents.insert(result.serverReadyEvent);
    if (result.webSocketEnabled && !declaredEvents.insert(result.webSocketReadyEvent).second) invalidManifest();
    for (const json& entry : hosts)
    {
        objectHasOnly(entry, {"role", "scenario", "identity", "persistenceGroup", "saveAchievementsAndStats", "apps", "telemetry", "waitFor", "signals", "actionAfter", "finishAfter", "peerUserIds", "timeoutSeconds"});
        Host host;
        host.role = requiredToken(entry, "role");
        host.scenario = requiredToken(entry, "scenario");
        host.timeoutSeconds = requiredTimeout(entry, "timeoutSeconds");
        if (!roles.insert(host.role).second) invalidManifest();
        if (entry.contains("persistenceGroup"))
        {
            host.persistenceGroup = requiredToken(entry, "persistenceGroup");
            if (host.persistenceGroup.find('.') != std::string::npos) invalidManifest();
        }
        if (entry.contains("saveAchievementsAndStats"))
        {
            const json& value = entry.at("saveAchievementsAndStats");
            if (!value.is_boolean()) invalidManifest();
            host.saveAchievementsAndStats = value.get<bool>();
        }
        if (host.saveAchievementsAndStats != !host.persistenceGroup.empty()) invalidManifest();
        const json& identity = required(entry, "identity");
        objectHasOnly(identity, {"userId", "personaName", "credentialProfile"});
        const json& userId = required(identity, "userId");
        if (!userId.is_number_unsigned() || !common::galaxyRealId(userId.get<std::uint64_t>())) invalidManifest();
        host.userId = userId.get<std::uint64_t>();
        const auto [identityEntry, newIdentity] = identityGroups.emplace(host.userId, host.persistenceGroup);
        if (!newIdentity && (host.persistenceGroup.empty() || identityEntry->second.empty() || identityEntry->second != host.persistenceGroup)) invalidManifest();
        if (!host.persistenceGroup.empty())
        {
            const auto [group, newGroup] = persistenceGroupIdentities.emplace(host.persistenceGroup, host.userId);
            if (!newGroup && group->second != host.userId) invalidManifest();
        }
        if (identity.contains("personaName")) host.personaName = requiredToken(identity, "personaName");
        if (identity.contains("credentialProfile"))
        {
            host.credentialProfile = requiredToken(identity, "credentialProfile");
            if (host.credentialProfile != "user1" && host.credentialProfile != "user2") invalidManifest();
        }
        if (entry.contains("apps"))
        {
            const json& apps = entry.at("apps");
            objectHasOnly(apps, {"language", "languageCode", "enableAllDlc", "saveUnknownDlcIds", "dlc"});
            host.hasAppsConfiguration = true;
            host.appsLanguage = requiredToken(apps, "language");
            host.appsLanguageCode = requiredToken(apps, "languageCode");
            const json& enableAllDlc = required(apps, "enableAllDlc");
            const json& saveUnknownDlcIds = required(apps, "saveUnknownDlcIds");
            const json& dlc = required(apps, "dlc");
            if (!enableAllDlc.is_boolean() || !saveUnknownDlcIds.is_boolean() || !dlc.is_object() || dlc.empty()) invalidManifest();
            host.appsEnableAllDlc = enableAllDlc.get<bool>();
            host.appsSaveUnknownDlcIds = saveUnknownDlcIds.get<bool>();
            std::set<std::uint64_t> uniqueDlcIds;
            for (const auto& [productIdText, installed] : dlc.items())
            {
                std::uint64_t productId = 0;
                const auto [end, error] = std::from_chars(productIdText.data(), productIdText.data() + productIdText.size(), productId);
                if (error != std::errc{} || end != productIdText.data() + productIdText.size() || !common::galaxyRealId(productId) || !installed.is_boolean()
                    || !uniqueDlcIds.insert(productId).second) invalidManifest();
                host.appsDlc.emplace_back(productId, installed.get<bool>());
            }
        }
        if (entry.contains("telemetry"))
        {
            const json& telemetry = entry.at("telemetry");
            objectHasOnly(telemetry, {"store"});
            const json& store = required(telemetry, "store");
            if (!store.is_boolean()) invalidManifest();
            host.hasTelemetryConfiguration = true;
            host.telemetryStore = store.get<bool>();
        }
        if (entry.contains("waitFor")) host.waitFor = tokenArray(entry.at("waitFor"));
        if (entry.contains("signals")) host.signals = tokenArray(entry.at("signals"));
        if (entry.contains("actionAfter")) host.actionAfter = tokenArray(entry.at("actionAfter"));
        if (entry.contains("finishAfter")) host.finishAfter = tokenArray(entry.at("finishAfter"));
        if (entry.contains("peerUserIds"))
        {
            const json& peerUserIds = entry.at("peerUserIds");
            if (!peerUserIds.is_array()) invalidManifest();
            std::set<std::uint64_t> uniquePeerIds;
            for (const json& peerUserId : peerUserIds)
            {
                if (!peerUserId.is_number_unsigned() || !common::galaxyRealId(peerUserId.get<std::uint64_t>())) invalidManifest();
                const std::uint64_t value = peerUserId.get<std::uint64_t>();
                if (!uniquePeerIds.insert(value).second || value == host.userId) invalidManifest();
                host.peerUserIds.push_back(value);
            }
        }
        for (const std::string& signal : host.signals)
            if (!declaredEvents.insert(signal).second) invalidManifest();
        result.hosts.push_back(std::move(host));
    }
    for (const Host& host : result.hosts)
    {
        std::set<std::string> uniqueDependencies;
        for (const std::string& dependency : host.waitFor)
            if (!declaredEvents.contains(dependency) || !uniqueDependencies.insert(dependency).second) invalidManifest();
        uniqueDependencies.clear();
        for (const std::string& dependency : host.actionAfter)
            if (!declaredEvents.contains(dependency) || !uniqueDependencies.insert(dependency).second) invalidManifest();
        uniqueDependencies.clear();
        for (const std::string& dependency : host.finishAfter)
            if (!declaredEvents.contains(dependency) || !uniqueDependencies.insert(dependency).second) invalidManifest();
        for (const std::uint64_t peerUserId : host.peerUserIds)
            if (!identityGroups.contains(peerUserId)) invalidManifest();
    }
    return result;
}

bool readArguments(const int argc, char* argv[], Arguments& arguments)
{
    for (int index = 1; index < argc; ++index)
    {
        const std::string option = argv[index];
        if (++index == argc) return false;
        const std::string value = argv[index];
        if (option == "--manifest") arguments.manifest = fs::u8path(value);
        else if (option == "--host") arguments.host = fs::u8path(value);
        else if (option == "--client-dll") arguments.clientDll = fs::u8path(value);
        else if (option == "--server") arguments.server = fs::u8path(value);
        else if (option == "--gog-runtime-dir") arguments.gogRuntimeDirectory = fs::u8path(value);
        else if (option == "--runtime-name") arguments.runtimeName = value;
        else if (option == "--version") arguments.version = value;
        else if (option == "--arch") arguments.arch = value;
        else return false;
    }
    return !arguments.manifest.empty() && !arguments.host.empty() && !arguments.clientDll.empty() && !arguments.server.empty()
        && !arguments.gogRuntimeDirectory.empty() && common::token(arguments.runtimeName) && common::token(arguments.version)
        && (arguments.arch == "x86" || arguments.arch == "x64");
}
}
