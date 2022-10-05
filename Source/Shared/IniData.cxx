#include "IniData.hxx"

#include "ConstHash.hxx"
#include "MachineInfo.hxx"

#include <exception>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>
#include <chrono>

namespace universelan {
	static const uint64_t GalaxyIDMask = 0x00FFFFFFFFFFFFFFULL;

	std::string IniData::GetPath(std::string base, const std::string& filename)
	{
		return (std::filesystem::path(base) / filename).string();
	}

	void IniData::LoadIni(CSimpleIniA& ini, const std::string& filename)
	{
		SI_Error rc = ini.LoadFile(filename.c_str());
		if (rc < 0) {
			throw std::runtime_error("Cannot load or parse " + filename + ", error: " + std::to_string(rc) + " / " + std::to_string(errno));
		}
	}

	IniData::IniData() :
		BootTime{ std::chrono::system_clock::now() }
	{
		CSimpleIniA ini;
		ini.SetUnicode();

		IniData::LoadIni(ini, BootFile);

		GameDataPath = ini.GetValue(StoragePathSection.c_str(), "GameDataPath", "UniverseLAN");
		ServerDataPath = ini.GetValue(StoragePathSection.c_str(), "ServerDataPath", "UniverseLANServer");
		CallTracing = ini.GetBoolValue(TracingSection.c_str(), "CallTracing", true);
		UnhandledExceptionLogging = ini.GetBoolValue(TracingSection.c_str(), "UnhandledExceptionLogging", true);
		MiniDumpOnUnhandledException = ini.GetBoolValue(TracingSection.c_str(), "MiniDumpOnUnhandledException", true);
		MiniDumpVerbosityLevel = ini.GetLongValue(TracingSection.c_str(), "MiniDumpVerbosityLevel", 2);
		TracingAlwaysFlush = ini.GetBoolValue(TracingSection.c_str(), "AlwaysFlush", true);

		AuthenticationKey = ini.GetValue(AuthenticationSection.c_str(), "Key", "9g5tA53SLyiNkBTqsX3BmBgy/PPVTU6VGKWNNw3wUIY5nK1C2MOT4UsZ2pauCb8fm5UQSJRijid+w1t9WpDaKQ==");
	}

	bool IniData::IsCallTracingEnabled() const {
		return CallTracing;
	}

	bool IniData::IsUnhandledExceptionLoggingEnabled() const {
		return UnhandledExceptionLogging;
	}

	bool IniData::CreateMiniDumpOnUnhandledException() const {
		return MiniDumpOnUnhandledException;
	}

	int IniData::GetMiniDumpVerbosityLevel() const {
		return MiniDumpVerbosityLevel;
	}

	bool IniData::ShouldAlwaysFlushTracing() const {
		return TracingAlwaysFlush;
	}

	const std::string& IniData::GetGameDataPath() const
	{
		return GameDataPath;
	}

	const std::string& IniData::GetServerDataPath() const
	{
		return ServerDataPath;
	}

	const std::string& IniData::GetAuthenticationKey() const
	{
		return AuthenticationKey;
	}

	IniData::~IniData()
	{
	}

	std::string ServerIniData::GetPath(const std::string& filename) const {
		return IniData::GetPath(GetServerDataPath(), filename);
	}

	ServerIniData::ServerIniData()
	{
		CSimpleIniA ini;
		ini.SetUnicode();

		IniData::LoadIni(ini, GetPath(ConfigFile));

		AllowFileSharingDownload = ini.GetBoolValue(StoragePathSection.c_str(), "AllowFileSharingDownload", true);
		AllowFileSharingUpload = ini.GetBoolValue(StoragePathSection.c_str(), "AllowFileSharingUpload", true);

		BindAddress = ini.GetValue(ServerSection.c_str(), "BindAddress", "0.0.0.0");
		Port = (uint16_t)ini.GetLongValue(ServerSection.c_str(), "Port", 19486);
		MaxConnections = ini.GetLongValue(ServerSection.c_str(), "MaxConnections", 1024);
		MaxTickRate = ini.GetLongValue(ServerSection.c_str(), "MaxTickRate", 200);
	}

	ServerIniData::~ServerIniData()
	{
	}

	bool ServerIniData::GetAllowFileSharingDownload() const {
		return AllowFileSharingDownload;
	}

	bool ServerIniData::GetAllowFileSharingUpload() const {
		return AllowFileSharingUpload;
	}

	const std::string& ServerIniData::GetBindAddress() const {
		return BindAddress;
	}

	uint16_t ServerIniData::GetPort() const {
		return Port;
	}

	uint32_t ServerIniData::GetMaxConnections() const {
		return MaxConnections;
	}

	uint32_t ServerIniData::GetMaxTickRate() const {
		return MaxTickRate;
	}

	std::string ClientIniData::GetPath(const std::string& filename) const {
		return IniData::GetPath(GetGameDataPath(), filename);
	}

	ClientIniData::ClientIniData()
		: local_user_data{ nullptr }
	{
		// Config
		{
			CSimpleIniA ini;
			ini.SetUnicode();

			IniData::LoadIni(ini, GetPath(ConfigFile));

			Language = ini.GetValue(SettingsSection.c_str(), "Language", "english");
			EnableAllDLC = ini.GetBoolValue(SettingsSection.c_str(), "EnableAllDLC", false);
			SaveUnknownDLCIDs = ini.GetBoolValue(SettingsSection.c_str(), "SaveUnknownDLCIDs", true);
			SaveAchievementsAndStats = ini.GetBoolValue(SettingsSection.c_str(), "SaveAchievementsAndStats", true);
			EnableConsole = ini.GetBoolValue(SettingsSection.c_str(), "EnableConsole", true);

			AllowFileSharingDownload = ini.GetBoolValue(StorageSection.c_str(), "AllowFileSharingDownload", true);
			AllowFileSharingUpload = ini.GetBoolValue(StorageSection.c_str(), "AllowFileSharingUpload", false);

			TelemetryStore = ini.GetBoolValue(TelemetrySection.c_str(), "Store", false);

			ServerAddress = ini.GetValue(ClientSection.c_str(), "ServerAddress", "127.0.0.1");
			Port = (uint16_t)ini.GetLongValue(ClientSection.c_str(), "Port", 19486);

			PersonaNameType = ini.GetValue(UserSection.c_str(), "PersonaNameType", "@Custom");
			CustomPersonaName = ini.GetValue(UserSection.c_str(), "CustomPersonaName", "Player");
			GalaxyIDType = ini.GetValue(UserSection.c_str(), "GalaxyIDType", "@NetworkAdapterMACHash");
			CustomGalaxyID = ini.GetLongLongValue(UserSection.c_str(), "CustomGalaxyID", 1);
			GalaxyIDOffset = ini.GetLongLongValue(UserSection.c_str(), "GalaxyIDOffset", 0);
			Avatar = ini.GetValue(UserSection.c_str(), "Avatar", "me.png");
			SignedIn = ini.GetBoolValue(UserSection.c_str(), "SignedIn", true);

			MachineInfo machine_info;

			if (const_hash(PersonaNameType) != const_hash("@Custom")) {

				switch (const_hash(PersonaNameType)) {
				case const_hash("@WindowsAccountName"):
					if (machine_info.GetLocalMachineName().size() < 1) {
						throw std::runtime_error("@WindowsAccountName: No username found");
					}

					CustomPersonaName = machine_info.GetLocalUserName();
					break;

				case const_hash("@WindowsAccountNameHash"):
					if (machine_info.GetLocalMachineName().size() < 1) {
						throw std::runtime_error("@WindowsAccountNameHash: No username found");
					}

					CustomPersonaName = std::to_string(const_hash64(machine_info.GetLocalUserName()));
					break;

				case const_hash("@ComputerName"):
					if (machine_info.GetLocalMachineName().size() < 1) {
						throw std::runtime_error("@ComputerName: No machine name found");
					}

					CustomPersonaName = machine_info.GetLocalMachineName();
					break;

				case const_hash("@ComputerNameHash"):
					if (machine_info.GetLocalMachineName().size() < 1) {
						throw std::runtime_error("@ComputerNameHash: No machine name found");
					}

					CustomPersonaName = std::to_string(const_hash64(machine_info.GetLocalMachineName()));
					break;

				case const_hash("@NetworkAdapterMACHash"):
					if (machine_info.GetLocalMACs().size() < 1) {
						throw std::runtime_error("@NetworkAdapterMACHash: No MAC adresses found");
					}

					CustomPersonaName = std::to_string(const_hash64(machine_info.GetLocalMACs().front()));
					break;

				default:
					throw std::runtime_error("Incorrect PersonaNameType: " + PersonaNameType);
				}
			}

			if (const_hash(GalaxyIDType) != const_hash("@Custom")) {
				std::string str;

				switch (const_hash(GalaxyIDType)) {
				case const_hash("@WindowsAccountNameHash"):
					if (machine_info.GetLocalMachineName().size() < 1) {
						throw std::runtime_error("@WindowsAccountNameHash: No username found");
					}

					str = machine_info.GetLocalUserName();
					break;

				case const_hash("@ComputerNameHash"):
					if (machine_info.GetLocalMachineName().size() < 1) {
						throw std::runtime_error("@ComputerNameHash: No machine name found");
					}

					str = machine_info.GetLocalMachineName();
					break;

				case const_hash("@NetworkAdapterMACHash"):
					if (machine_info.GetLocalMACs().size() < 1) {
						throw std::runtime_error("@NetworkAdapterMACHash: No MAC adresses found");
					}

					str = machine_info.GetLocalMACs().front();
					break;

				default:
					throw std::runtime_error("Incorrect GalaxyIDType: " + GalaxyIDType);
				}

				CustomGalaxyID = (const_hash64(str) & GalaxyIDMask);
			}
		}

		local_user_data = std::make_shared<GalaxyUserData>(GetApiGalaxyID());

		// Achievements
		{
			CSimpleIniA ini;
			ini.SetUnicode();

			IniData::LoadIni(ini, GetPath(AchievementsFile));

			CSimpleIniA::TNamesDepend sections;
			ini.GetAllSections(sections);

			local_user_data->stats.run_locked_achievements<void>([&](auto& Achievements) {
				for (const auto& entry : sections) {
					if ((entry.pItem != nullptr) && (strlen(entry.pItem) > 0)) {
						AchievementData data;

						data.SetName(entry.pItem);
						data.SetDescription(ini.GetValue(entry.pItem, "Description", ""));
						data.SetUnlocked(ini.GetBoolValue(entry.pItem, "Unlocked", false));
						data.SetUnlockTime(ini.GetLongValue(entry.pItem, "UnlockTime", 0));
						data.SetVisible(ini.GetBoolValue(entry.pItem, "Visible", false));
						data.SetVisibleWhileLocked(ini.GetBoolValue(entry.pItem, "VisibleWhileLocked", false));

						data.ResetDirty();

						Achievements.emplace(data.GetName(), data);
					}
				}
				});
		}

		// DLC
		{
			CSimpleIniA ini;
			ini.SetUnicode();

			IniData::LoadIni(ini, GetPath(DLCFile));

			// get all keys in a section
			CSimpleIniA::TNamesDepend keys;
			ini.GetAllKeys(DLCSection.c_str(), keys);

			for (const auto& entry : keys) {
				if ((entry.pItem != nullptr) && (strlen(entry.pItem) > 0)) {
					DLCs.emplace(std::string(entry.pItem), ini.GetBoolValue(DLCSection.c_str(), entry.pItem, false));
				}
			}
		}

		// Stats
		{
			CSimpleIniA ini;
			ini.SetUnicode();

			IniData::LoadIni(ini, GetPath(StatsFile));

			local_user_data->stats.SetPlayTime(ini.GetLongValue(MetadataSection.c_str(), "PlayTime", 0));

			// get all keys in a section
			CSimpleIniA::TNamesDepend keys;
			ini.GetAllKeys(StatsSection.c_str(), keys);

			local_user_data->stats.run_locked_stats<void>([&](auto& Stats) {
				for (const auto& entry : keys) {
					if ((entry.pItem != nullptr) && (strlen(entry.pItem) > 0)) {
						StatsDataContainer c{ .i = ini.GetLongValue(StatsSection.c_str(), entry.pItem, 0) };
						Stats.emplace(std::string(entry.pItem), c);
					}
				}
				});
		}

		// UserData
		{
			CSimpleIniA ini;
			ini.SetUnicode();

			IniData::LoadIni(ini, GetPath(UserDataFile));

			// get all keys in a section
			CSimpleIniA::TNamesDepend keys;
			ini.GetAllKeys(UserDataSection.c_str(), keys);

			local_user_data->stats.run_locked_userdata<void>([&](auto& UserData) {
				for (const auto& entry : keys) {
					if ((entry.pItem != nullptr) && (strlen(entry.pItem) > 0)) {
						UserData.emplace(std::string(entry.pItem), std::string(ini.GetValue(UserDataSection.c_str(), entry.pItem, "")));
					}
				}
				});
		}
	}

	ClientIniData::~ClientIniData()
	{
	}

	const std::string& ClientIniData::GetLanguage() const
	{
		return Language;
	}

	bool ClientIniData::GetEnableAllDLC() const
	{
		return EnableAllDLC;
	}

	bool ClientIniData::GetSaveUnknownDLCIDs() const
	{
		return SaveUnknownDLCIDs;
	}

	bool ClientIniData::GetSaveAchievementsAndStats() const
	{
		return SaveAchievementsAndStats;
	}

	bool ClientIniData::GetEnableConsole() const
	{
		return EnableConsole;
	}

	bool ClientIniData::GetAllowFileSharingDownload() const
	{
		return AllowFileSharingDownload;
	}

	bool ClientIniData::GetAllowFileSharingUpload() const
	{
		return AllowFileSharingUpload;
	}

	bool ClientIniData::GetTelemetryStore() const
	{
		return TelemetryStore;
	}

	std::string ClientIniData::GetServerAddress() const
	{
		return ServerAddress;
	}

	uint16_t ClientIniData::GetPort() const
	{
		return Port;
	}

	const std::string& ClientIniData::GetPersonaNameType() const
	{
		return PersonaNameType;
	}

	const std::string& ClientIniData::GetCustomPersonaName() const
	{
		return CustomPersonaName;
	}

	const std::string& ClientIniData::GetGalaxyIDType() const
	{
		return GalaxyIDType;
	}

	uint64_t ClientIniData::GetCustomGalaxyID() const
	{
		return CustomGalaxyID + GalaxyIDOffset;
	}

	galaxy::api::GalaxyID ClientIniData::GetApiGalaxyID() const
	{
		return galaxy::api::GalaxyID::FromRealID(galaxy::api::GalaxyID::ID_TYPE_USER, GetCustomGalaxyID());
	}

	uint64_t ClientIniData::GetGalaxyIDOffset() const
	{
		return GalaxyIDOffset;
	}

	const std::string& ClientIniData::GetAvatar() const
	{
		return Avatar;
	}

	bool ClientIniData::GetSignedIn() const
	{
		return SignedIn;
	}

	uint32_t ClientIniData::GetPlayTime() const
	{
		return local_user_data->stats.GetPlayTime();
	}

	bool ClientIniData::IsDLCInstalled(const std::string& name)
	{
		auto it = DLCs.find(name);
		if (it == DLCs.end()) {
			return DLCs.emplace(name, false).first->second;
		}
		return it->second;
	}

	void ClientIniData::SaveStatsAndAchievements()
	{
		// Achievements
		if (SaveAchievementsAndStats)
		{
			CSimpleIniA ini;
			ini.SetUnicode();

			IniData::LoadIni(ini, GetPath(AchievementsFile));

			local_user_data->stats.run_locked_achievements<void>([&](auto& Achievements) {
				for (auto& achievement : Achievements) {
					auto& data = achievement.second;
					if (data.IsDirty()) {
						data.ResetDirty();
						std::string name = data.GetName().c_str();
						ini.SetValue(name.c_str(), "Description", data.GetDescription().c_str());
						ini.SetBoolValue(name.c_str(), "Unlocked", data.GetUnlocked());
						ini.SetLongValue(name.c_str(), "UnlockTime", data.GetUnlockTime());
						ini.SetBoolValue(name.c_str(), "Visible", data.GetVisible());
						ini.SetBoolValue(name.c_str(), "VisibleWhileLocked", data.GetVisibleWhileLocked());
					}
				}
				});

			ini.SaveFile(GetPath(AchievementsFile).c_str());
		}

		// DLC
		if (SaveUnknownDLCIDs)
		{
			CSimpleIniA ini;
			ini.SetUnicode();

			IniData::LoadIni(ini, GetPath(DLCFile));

			for (const auto& dlc : DLCs) {
				std::string name = dlc.first.c_str();
				ini.SetBoolValue(name.c_str(), "Description", dlc.second);
			}

			ini.SaveFile(GetPath(DLCFile).c_str());
		}

		// Stats
		if (SaveAchievementsAndStats)
		{
			CSimpleIniA ini;
			ini.SetUnicode();

			IniData::LoadIni(ini, GetPath(StatsFile));

			ini.SetLongValue(MetadataSection.c_str(), "PlayTime", local_user_data->stats.GetPlayTime());

			local_user_data->stats.run_locked_stats<void>([&](auto& Stats) {
				for (const auto& stat : Stats) {
					ini.SetLongValue(StatsSection.c_str(), stat.first.c_str(), stat.second.i);
				}
				});

			ini.SaveFile(GetPath(StatsFile).c_str());
		}

		// UserData
		if (SaveAchievementsAndStats)
		{
			CSimpleIniA ini;
			ini.SetUnicode();

			IniData::LoadIni(ini, GetPath(UserDataFile));

			local_user_data->stats.run_locked_userdata<void>([&](auto& UserData) {
				for (const auto& user_data : UserData) {
					ini.SetValue(UserDataSection.c_str(), user_data.first.c_str(), user_data.second.c_str());
				}
				});

			ini.SaveFile(GetPath(UserDataFile).c_str());
		}
	}

	bool ClientIniData::IsSelfUserID(uint64_t userID) const
	{
		return (userID == GetCustomGalaxyID()) || (userID == 0);
	}

	bool ClientIniData::IsSelfUserID(galaxy::api::GalaxyID userID) const
	{
		return (userID == GetApiGalaxyID()) || (userID == 0);
	}

	void ClientIniData::ResetStatsAndAchievements()
	{
		local_user_data->stats.run_locked_achievements<void>([&](auto& Achievements) {
			for (auto& entry : Achievements) {
				entry.second.SetUnlocked(false);
				entry.second.SetUnlockTime(0);
			}
			});

		local_user_data->stats.run_locked_stats<void>([&](auto& Stats) {
			for (auto& entry : Stats) {
				entry.second.i = 0;
			}
			});

		SaveStatsAndAchievements();
	}

	const GalaxyUserData::ptr_t& ClientIniData::GetLocalUserData() const
	{
		return local_user_data;
	}
}