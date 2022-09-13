#include "IniData.hxx"

#include <exception>
#include <filesystem>
#include <stdexcept>
#include <string>
#include <chrono>

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
	AuthenticationKey = ini.GetValue(AuthenticationSection.c_str(), "Key", "9g5tA53SLyiNkBTqsX3BmBgy/PPVTU6VGKWNNw3wUIY5nK1C2MOT4UsZ2pauCb8fm5UQSJRijid+w1t9WpDaKQ==");
}

std::string IniData::GetGameDataPath() const
{
	return GameDataPath;
}

std::string IniData::GetServerDataPath() const
{
	return ServerDataPath;
}

std::string IniData::GetAuthenticationKey() const
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
	Quota = ini.GetLongValue(StoragePathSection.c_str(), "Quota", 0);
	PerUserQuota = ini.GetLongValue(StoragePathSection.c_str(), "PerUserQuota", 0);

	BindAddress = ini.GetBoolValue(ServerSection.c_str(), "AllowFileSharingDownload", true);
	Port = ini.GetBoolValue(ServerSection.c_str(), "AllowFileSharingUpload", true);
	MaxConnections = ini.GetLongValue(ServerSection.c_str(), "Quota", 0);
	MaxTickRate = ini.GetLongValue(ServerSection.c_str(), "PerUserQuota", 0);
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

uint32_t ServerIniData::GetQuota() const {
	return Quota;
}

uint32_t ServerIniData::GetPerUserQuota() const {
	return PerUserQuota;
}

std::string ServerIniData::GetBindAddress() const {
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
{
	// Config
	{
		CSimpleIniA ini;
		ini.SetUnicode();

		IniData::LoadIni(ini, GetPath(ConfigFile));

		Language = ini.GetValue(SettingsSection.c_str(), "Language", "english");
		NATType = (uint16_t)ini.GetLongValue(SettingsSection.c_str(), "NATType", 0);
		EnableAllDLC = ini.GetBoolValue(SettingsSection.c_str(), "EnableAllDLC", false);
		SaveUnknownDLCIDs = ini.GetBoolValue(SettingsSection.c_str(), "SaveUnknownDLCIDs", true);
		SaveAchievementsAndStats = ini.GetBoolValue(SettingsSection.c_str(), "SaveAchievementsAndStats", true);
		EnableConsole = ini.GetBoolValue(SettingsSection.c_str(), "EnableConsole", true);

		AllowFileSharingDownload = ini.GetBoolValue(StorageSection.c_str(), "AllowFileSharingDownload", true);
		AllowFileSharingUpload = ini.GetBoolValue(StorageSection.c_str(), "AllowFileSharingUpload", false);
		Quota = ini.GetLongValue(StorageSection.c_str(), "Quota", 0);

		TelemetryStore = ini.GetBoolValue(TelemetrySection.c_str(), "Store", false);

		ServerAddress = ini.GetValue(ClientSection.c_str(), "ServerAddress", "192.168.1.1");
		Port = (uint16_t)ini.GetLongValue(ClientSection.c_str(), "Port", 19486);

		PersonaNameType = ini.GetValue(UserSection.c_str(), "PersonaNameType", "@Custom");
		CustomPersonaName = ini.GetValue(UserSection.c_str(), "CustomPersonaName", "Player");
		GalaxyIDType = ini.GetValue(UserSection.c_str(), "GalaxyIDType", "@NetworkAdapterMACHash");
		CustomGalaxyID = ini.GetLongLongValue(UserSection.c_str(), "CustomGalaxyID", 1);
		GalaxyIDOffset = ini.GetLongLongValue(UserSection.c_str(), "GalaxyIDOffset", 0);
		Avatar = ini.GetValue(UserSection.c_str(), "Avatar", "me.png");
		SignedIn = ini.GetBoolValue(UserSection.c_str(), "SignedIn", true);
	}

	// Achievements
	{
		CSimpleIniA ini;
		ini.SetUnicode();

		IniData::LoadIni(ini, GetPath(AchievementsFile));

		CSimpleIniA::TNamesDepend sections;
		ini.GetAllSections(sections);

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

		PlayTime = ini.GetLongValue(MetadataSection.c_str(), "PlayTime", 0);

		// get all keys in a section
		CSimpleIniA::TNamesDepend keys;
		ini.GetAllKeys(StatsSection.c_str(), keys);

		for (const auto& entry : keys) {
			if ((entry.pItem != nullptr) && (strlen(entry.pItem) > 0)) {
				Stats.emplace(std::string(entry.pItem), std::string(ini.GetValue(StatsSection.c_str(), entry.pItem, "0")));
			}
		}
	}

	// UserData
	{
		CSimpleIniA ini;
		ini.SetUnicode();

		IniData::LoadIni(ini, GetPath(UserDataFile));

		// get all keys in a section
		CSimpleIniA::TNamesDepend keys;
		ini.GetAllKeys(UserDataSection.c_str(), keys);

		for (const auto& entry : keys) {
			if ((entry.pItem != nullptr) && (strlen(entry.pItem) > 0)) {
				UserData.emplace(std::string(entry.pItem), std::string(ini.GetValue(UserDataSection.c_str(), entry.pItem, "")));
			}
		}
	}
}

ClientIniData::~ClientIniData()
{
}

std::string ClientIniData::GetLanguage() const
{
	return Language;
}

uint16_t ClientIniData::GetNATType() const
{
	return NATType;
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

uint32_t ClientIniData::GetQuota() const
{
	return Quota;
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

std::string ClientIniData::GetPersonaNameType() const
{
	return PersonaNameType;
}

std::string ClientIniData::GetCustomPersonaName() const
{
	return CustomPersonaName;
}

std::string ClientIniData::GetGalaxyIDType() const
{
	return GalaxyIDType;
}

uint64_t ClientIniData::GetCustomGalaxyID() const
{
	return CustomGalaxyID;
}

uint64_t ClientIniData::GetGalaxyIDOffset() const
{
	return GalaxyIDOffset;
}

std::string ClientIniData::GetAvatar() const
{
	return Avatar;
}

bool ClientIniData::GetSignedIn() const
{
	return SignedIn;
}

uint32_t ClientIniData::GetPlayTime() const
{
	// cast the duration into seconds
	const auto seconds = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - BootTime);

	return PlayTime + (uint32_t)seconds.count();
}

AchievementData* ClientIniData::GetAchievementData(const std::string& name)
{
	auto it = Achievements.find(name);
	if (it == Achievements.end()) {
		AchievementData* data = &Achievements.emplace(name, AchievementData()).first->second;
		data->SetName(name);
		return data;
	}
	return &it->second;
}

bool ClientIniData::IsDLCInstalled(const std::string& name)
{
	auto it = DLCs.find(name);
	if (it == DLCs.end()) {
		return DLCs.emplace(name, false).first->second;
	}
	return it->second;
}

std::variant<std::string, int32_t, float>* ClientIniData::GetStat(const std::string& name)
{
	auto it = Stats.find(name);
	if (it == Stats.end()) {
		return &Stats.emplace(name, 0).first->second;
	}
	return &it->second;
}

std::string* ClientIniData::GetUserData(const std::string& name)
{
	auto it = UserData.find(name);
	if (it == UserData.end()) {
		return &UserData.emplace(name, "").first->second;
	}
	return &it->second;
}

void ClientIniData::SaveStatsAndAchievements()
{
	// Achievements
	if (SaveAchievementsAndStats)
	{
		CSimpleIniA ini;
		ini.SetUnicode();

		IniData::LoadIni(ini, GetPath(AchievementsFile));

		for (const auto& achievement : Achievements) {
			const auto data = achievement.second;
			std::string name = data.GetName().c_str();
			ini.SetValue(name.c_str(), "Description", data.GetDescription().c_str());
			ini.SetBoolValue(name.c_str(), "Unlocked", data.GetUnlocked());
			ini.SetLongValue(name.c_str(), "UnlockTime", data.GetUnlockTime());
			ini.SetBoolValue(name.c_str(), "Visible", data.GetVisible());
			ini.SetBoolValue(name.c_str(), "VisibleWhileLocked", data.GetVisibleWhileLocked());
		}

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

		ini.SetLongValue(MetadataSection.c_str(), "PlayTime", GetPlayTime());

		for (const auto& stat : Stats) {
			std::string name = stat.first.c_str();

			switch (stat.second.index()) {
			case 0:
				ini.SetValue(StatsSection.c_str(), name.c_str(), std::get<std::string>(stat.second).c_str());
				break;

			case 1:
				ini.SetLongValue(StatsSection.c_str(), name.c_str(), std::get<int32_t>(stat.second));
				break;

			case 2:
				ini.SetDoubleValue(StatsSection.c_str(), name.c_str(), (double)std::get<float>(stat.second));
				break;
			}
		}

		ini.SaveFile(GetPath(StatsFile).c_str());
	}

	// UserData
	if (SaveAchievementsAndStats)
	{
		CSimpleIniA ini;
		ini.SetUnicode();

		IniData::LoadIni(ini, GetPath(UserDataFile));

		for (const auto& user_data : UserData) {
			ini.SetValue(UserDataSection.c_str(), user_data.first.c_str(), user_data.second.c_str());
		}

		ini.SaveFile(GetPath(UserDataFile).c_str());
	}
}