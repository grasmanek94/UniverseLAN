#pragma once

#include "AchievementData.hxx"

#include <chrono>
#include <map>
#include <string>
#include <variant>

#include <SimpleIni.h>

class IniData
{
private:
	const std::string BootFile = "UniverseLAN.ini";

	const std::string StoragePathSection = "Storage";
	std::string GameDataPath;
	std::string ServerDataPath;

	const std::string AuthenticationSection = "Authentication";
	std::string AuthenticationKey;

protected:
	static std::string GetPath(std::string base, const std::string& filename);
	static void LoadIni(CSimpleIniA& ini, const std::string& filename);

public:
	IniData();
	virtual ~IniData();

	const std::string& GetGameDataPath() const;
	const std::string& GetServerDataPath() const;
	const std::string& GetAuthenticationKey() const;

	const std::chrono::system_clock::time_point BootTime;
};

class ServerIniData : public IniData
{
private:
	const std::string ConfigFile = "Config.ini";

	const std::string StoragePathSection = "Storage";
	bool AllowFileSharingDownload;
	bool AllowFileSharingUpload;

	const std::string ServerSection = "Server";
	std::string BindAddress;
	uint16_t Port;
	uint32_t MaxConnections;
	uint32_t MaxTickRate;

	std::string GetPath(const std::string& filename) const;

public:
	ServerIniData();
	virtual ~ServerIniData();

	bool GetAllowFileSharingDownload() const;
	bool GetAllowFileSharingUpload() const;

	const std::string& GetBindAddress() const;
	uint16_t GetPort() const;
	uint32_t GetMaxConnections() const;
	uint32_t GetMaxTickRate() const;
};

class ClientIniData : public IniData
{
private:
	const std::string ConfigFile = "Config.ini";

	const std::string SettingsSection = "Settings";
	std::string Language;
	uint16_t NATType;
	bool EnableAllDLC;
	bool SaveUnknownDLCIDs;
	bool SaveAchievementsAndStats;
	bool EnableConsole;

	const std::string StorageSection = "Settings";
	bool AllowFileSharingDownload;
	bool AllowFileSharingUpload;

	const std::string TelemetrySection = "Telemetry";
	bool TelemetryStore;

	const std::string ClientSection = "Client";
	std::string ServerAddress;
	uint16_t Port;

	const std::string UserSection = "User";
	std::string PersonaNameType;
	std::string CustomPersonaName;
	std::string GalaxyIDType;
	uint64_t CustomGalaxyID;
	uint64_t GalaxyIDOffset;
	std::string Avatar;
	bool SignedIn;

	const std::string AchievementsFile = "Achievements.ini";
	std::map<std::string, AchievementData> Achievements;

	const std::string DLCFile = "DLC.ini";
	const std::string DLCSection = "DLC";
	std::map<std::string, bool> DLCs;

	const std::string StatsFile = "Stats.ini";
	const std::string MetadataSection = "Metadata";
	uint32_t PlayTime;

	const std::string StatsSection = "Stats";
	std::map<std::string, std::variant<std::string, int32_t, float>> Stats;
	
	const std::string UserDataFile = "UserData.ini";
	const std::string UserDataSection = "UserData";
	std::map<std::string, std::string> UserData;

	std::string GetPath(const std::string& filename) const;

public:
	ClientIniData();
	virtual ~ClientIniData();

	const std::string& GetLanguage() const;
	uint16_t GetNATType() const;
	bool GetEnableAllDLC() const;
	bool GetSaveUnknownDLCIDs() const;
	bool GetSaveAchievementsAndStats() const;
	bool GetEnableConsole() const;
	bool GetAllowFileSharingDownload() const;
	bool GetAllowFileSharingUpload() const;
	bool GetTelemetryStore() const;
	std::string GetServerAddress() const;
	uint16_t GetPort() const;
	const std::string& GetPersonaNameType() const;
	const std::string& GetCustomPersonaName() const;
	const std::string& GetGalaxyIDType() const;
	uint64_t GetCustomGalaxyID() const;
	uint64_t GetGalaxyIDOffset() const;
	const std::string& GetAvatar() const;
	bool GetSignedIn() const;
	uint32_t GetPlayTime() const;

	AchievementData* GetAchievementData(const std::string& name);
	bool IsDLCInstalled(const std::string& name);
	std::variant<std::string, int32_t, float>* GetStat(const std::string& name);
	std::string* GetUserData(const std::string& name);

	void SaveStatsAndAchievements();
};
