#pragma once

#include "AchievementsAndStatsContainer.hxx"

#include <GalaxyID.h>
#include <SimpleIni.h>

#include <chrono>
#include <string>
#include <unordered_map>
#include <variant>

namespace universelan {
	class IniData
	{
	private:
		const std::string BootFile = "UniverseLAN.ini";

		const std::string StoragePathSection = "Storage";
		std::string GameDataPath;
		std::string ServerDataPath;

		const std::string TracingSection = "Tracing";
		bool CallTracing;
		bool UnhandledExceptionLogging;
		bool MiniDumpOnUnhandledException;
		int MiniDumpVerbosityLevel;

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

		bool IsCallTracingEnabled() const;
		bool IsUnhandledExceptionLoggingEnabled() const;
		bool CreateMiniDumpOnUnhandledException() const;
		int GetMiniDumpVerbosityLevel() const;

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
		galaxy::api::GalaxyID ApiGalaxyID;
		uint64_t GalaxyIDOffset;
		std::string Avatar;
		bool SignedIn;

		const std::string AchievementsFile = "Achievements.ini";
		AchievementsAndStatsContainer achievements_stats;

		const std::string DLCFile = "DLC.ini";
		const std::string DLCSection = "DLC";
		std::unordered_map<std::string, bool> DLCs;

		const std::string StatsFile = "Stats.ini";
		const std::string MetadataSection = "Metadata";
		uint32_t PlayTime;

		const std::string StatsSection = "Stats";
		// container see achievements_stats

		const std::string UserDataFile = "UserData.ini";
		const std::string UserDataSection = "UserData";
		// container see achievements_stats

		std::string GetPath(const std::string& filename) const;

	public:
		ClientIniData();
		virtual ~ClientIniData();

		const std::string& GetLanguage() const;
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
		galaxy::api::GalaxyID GetApiGalaxyID() const;
		uint64_t GetGalaxyIDOffset() const;
		const std::string& GetAvatar() const;
		bool GetSignedIn() const;
		uint32_t GetPlayTime() const;

		AchievementData* GetAchievementData(const std::string& name);
		bool IsDLCInstalled(const std::string& name);
		const StatsDataContainer& GetStat(const std::string& name);
		void SetStat(const std::string& name, int32_t value);
		void SetStat(const std::string& name, float value);
		const std::string& GetUserData(const std::string& name);
		void SetUserData(const std::string& name, const std::string& data);

		void SaveStatsAndAchievements();

		bool IsSelfUserID(uint64_t userID) const;
		bool IsSelfUserID(galaxy::api::GalaxyID userID) const;

		void ResetStatsAndAchievements();

		const AchievementsAndStatsContainer& GetASUC() const;
	};
}