#include "IniData.hxx"

#include "ConstHash.hxx"
#include "MachineInfo.hxx"

#include <magic_enum/magic_enum.hpp>
#include <Tracer.hxx>

#include <charconv>
#include <chrono>
#include <exception>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string_view>
#include <string>

template <>
struct magic_enum::customize::enum_range<universelan::tracer::Trace::MASK> {
	static constexpr bool is_flags = true;
};

namespace universelan {
	static const uint64_t GalaxyIDMask = 0x00FFFFFFFFFFFFFFULL;

	namespace {
		std::string_view trim(const std::string_view& in) {
			auto left = in.begin();
			for (;; ++left) {
				if (left == in.end())
					return std::string_view();
				if (!isspace(*left))
					break;
			}

			auto right = in.end() - 1;
			for (; right > left && isspace(*right); --right);

			return std::string_view(left, right + 1);
		}

		std::vector<std::string_view> split(const std::string_view str, const char delim = '|')
		{
			std::vector<std::string_view> result;

			int indexCommaToLeftOfColumn = 0;
			int indexCommaToRightOfColumn = -1;

			for (int i = 0; i < static_cast<int>(str.size()); i++)
			{
				if (str[i] == delim)
				{
					indexCommaToLeftOfColumn = indexCommaToRightOfColumn;
					indexCommaToRightOfColumn = i;
					int index = indexCommaToLeftOfColumn + 1;
					int length = indexCommaToRightOfColumn - index;

					// Bounds checking can be omitted as logically, this code can never be invoked 
					// Try it: put a breakpoint here and run the unit tests.
					/*if (index + length >= static_cast<int>(str.size()))
					{
						length--;
					}
					if (length < 0)
					{
						length = 0;
					}*/

					std::string_view column(str.data() + index, length);
					result.push_back(trim(column));
				}
			}

			const std::string_view finalColumn(str.data() + indexCommaToRightOfColumn + 1, str.size() - indexCommaToRightOfColumn - 1);
			result.push_back(trim(finalColumn));
			return result;
		}


		uint64_t parse_flags(const std::string& str) {
			auto result = split(str);

			uint64_t flags = 0;
			for (auto& entry : result) {
				uint64_t flag = magic_enum::enum_cast<tracer::Trace::MASK>(entry).value_or(tracer::Trace::INFORMATIONAL);

				if (flag == tracer::Trace::TRACE_ALL_FLAGS) {
					flags |= std::numeric_limits<decltype(flags)>::max();
				}

				flags |= flag;
			}

			return flags;
		}
	}

	std::string IniData::GetPath(std::string base, const std::string& filename)
	{
		return (std::filesystem::path(base) / filename).string();
	}

	void IniData::LoadIni(CSimpleIniA& ini, const std::string& filename)
	{
		SI_Error rc = ini.LoadFile(filename.c_str());
		if (rc < 0) {
			std::string problem = "Cannot load or parse " + filename + ", error (Return Code / errno): " + std::to_string(rc) + " / " + std::to_string(errno) + "\nWill try to use sane defaults.";
		//	throw std::runtime_error(problem);
#ifdef _WIN32
			MessageBox(NULL, problem.c_str(), "UniverseLAN - Error", 0);
#else
			std::cout << "Exception occurred during init: " << problem << std::endl;
#endif
		}
	}

	IniData::IniData() :
		BootTime{ std::chrono::system_clock::now() }
	{
		CSimpleIniA ini;
		ini.SetUnicode();

		IniData::LoadIni(ini, BootFile);

		GameDataPath = ini.GetValue(StoragePathSection.c_str(), "GameDataPath", "UniverseLANData");
		ServerDataPath = ini.GetValue(StoragePathSection.c_str(), "ServerDataPath", "UniverseLANServerData");
		CallTracing = ini.GetBoolValue(TracingSection.c_str(), "CallTracing", true);
		UnhandledExceptionLogging = ini.GetBoolValue(TracingSection.c_str(), "UnhandledExceptionLogging", true);
		MiniDumpOnUnhandledException = ini.GetBoolValue(TracingSection.c_str(), "MiniDumpOnUnhandledException", true);
		MiniDumpVerbosityLevel = ini.GetLongValue(TracingSection.c_str(), "MiniDumpVerbosityLevel", 2);
		TracingAlwaysFlush = ini.GetBoolValue(TracingSection.c_str(), "AlwaysFlush", true);
		CallTracingFlags = parse_flags(ini.GetValue(TracingSection.c_str(), "CallTracingFlags", "INFORMATIONAL"));
		TraceToConsole = ini.GetBoolValue(TracingSection.c_str(), "TraceToConsole", false);

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

	uint64_t IniData::GetCallTracingFlags() const {
		return CallTracingFlags;
	}

	bool IniData::ShouldTraceToConsole() const {
		return TraceToConsole;
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

		BindAddress = ini.GetValue(ServerSection.c_str(), "BindAddress", "127.0.0.1");
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
			MachineInfo machine_info;

			CSimpleIniA ini;
			ini.SetUnicode();

			IniData::LoadIni(ini, GetPath(ConfigFile));

			Language = ini.GetValue(SettingsSection.c_str(), "Language", "english");
			EnableAllDLC = ini.GetBoolValue(SettingsSection.c_str(), "EnableAllDLC", true);
			SaveUnknownDLCIDs = ini.GetBoolValue(SettingsSection.c_str(), "SaveUnknownDLCIDs", true);
			SaveAchievementsAndStats = ini.GetBoolValue(SettingsSection.c_str(), "SaveAchievementsAndStats", true);
			EnableConsole = ini.GetBoolValue(SettingsSection.c_str(), "EnableConsole", true);

			AllowFileSharingDownload = ini.GetBoolValue(StorageSection.c_str(), "AllowFileSharingDownload", true);
			AllowFileSharingUpload = ini.GetBoolValue(StorageSection.c_str(), "AllowFileSharingUpload", true);

			TelemetryStore = ini.GetBoolValue(TelemetrySection.c_str(), "Store", false);

			ServerAddress = ini.GetValue(ClientSection.c_str(), "ServerAddress", "127.0.0.1");
			Port = (uint16_t)ini.GetLongValue(ClientSection.c_str(), "Port", 19486);

			PersonaNameType = ini.GetValue(UserSection.c_str(), "PersonaNameType", "@Custom");
			CustomPersonaName = ini.GetValue(UserSection.c_str(), "CustomPersonaName", "UnknownPlayerName");
			SuffixPersonaNameTypeResultWithCustomPersonaName = ini.GetBoolValue(UserSection.c_str(), "SuffixPersonaNameTypeResultWithCustomPersonaName", true);

			GalaxyIDType = ini.GetValue(UserSection.c_str(), "GalaxyIDType", "@NetworkAdapterMACHash");
			CustomGalaxyID = ini.GetLongLongValue(UserSection.c_str(), "CustomGalaxyID", 1);

			if (const_hash(ini.GetValue(UserSection.c_str(), "GalaxyIDOffset", "")) != const_hash("@ProcessID")) {
				GalaxyIDOffset = ini.GetLongLongValue(UserSection.c_str(), "GalaxyIDOffset", 0);
			}
			else {
				GalaxyIDOffset = machine_info.GetProcessID();
			}

			Avatar = ini.GetValue(UserSection.c_str(), "Avatar", "me.png");
			SignedIn = ini.GetBoolValue(UserSection.c_str(), "SignedIn", true);

			if (const_hash(PersonaNameType) != const_hash("@Custom")) {

				switch (const_hash(PersonaNameType)) {
				case const_hash("@WindowsAccountName"):
					if (machine_info.GetLocalMachineName().size() < 1) {
						throw std::runtime_error("@WindowsAccountName: No username found");
					}

					CustomPersonaName = machine_info.GetLocalUserName() + (SuffixPersonaNameTypeResultWithCustomPersonaName ? CustomPersonaName : "");
					break;

				case const_hash("@WindowsAccountNameHash"):
					if (machine_info.GetLocalMachineName().size() < 1) {
						throw std::runtime_error("@WindowsAccountNameHash: No username found");
					}

					CustomPersonaName = std::to_string(const_hash64(machine_info.GetLocalUserName())) + (SuffixPersonaNameTypeResultWithCustomPersonaName ? CustomPersonaName : "");
					break;

				case const_hash("@ComputerName"):
					if (machine_info.GetLocalMachineName().size() < 1) {
						throw std::runtime_error("@ComputerName: No machine name found");
					}

					CustomPersonaName = machine_info.GetLocalMachineName() + (SuffixPersonaNameTypeResultWithCustomPersonaName ? CustomPersonaName : "");
					break;

				case const_hash("@ComputerNameHash"):
					if (machine_info.GetLocalMachineName().size() < 1) {
						throw std::runtime_error("@ComputerNameHash: No machine name found");
					}

					CustomPersonaName = std::to_string(const_hash64(machine_info.GetLocalMachineName())) + (SuffixPersonaNameTypeResultWithCustomPersonaName ? CustomPersonaName : "");
					break;

				case const_hash("@NetworkAdapterMACHash"):
					if (machine_info.GetLocalMACs().size() < 1) {
						throw std::runtime_error("@NetworkAdapterMACHash: No MAC adresses found");
					}

					CustomPersonaName = std::to_string(const_hash64(machine_info.GetLocalMACs().front())) + (SuffixPersonaNameTypeResultWithCustomPersonaName ? CustomPersonaName : "");
					break;

				case const_hash("@ProcessID"):
					CustomPersonaName = std::to_string(machine_info.GetProcessID()) + (SuffixPersonaNameTypeResultWithCustomPersonaName ? CustomPersonaName : "");
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
					std::string product_id_str = std::string(entry.pItem);
					uint64_t product_id = 0;
					auto result = std::from_chars(product_id_str.data(), product_id_str.data() + product_id_str.size(), product_id);
					
					switch (result.ec) {
					case std::errc::invalid_argument:
					case std::errc::result_out_of_range:
						std::cerr << "Cannot parse DLC Product ID: " << product_id_str << "\n";
						break;

					default:
						DLCs.emplace(product_id, ini.GetBoolValue(DLCSection.c_str(), entry.pItem, false));
						break;
					}
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
						StatsDataContainer c{ .i = static_cast<int32_t>(ini.GetLongValue(StatsSection.c_str(), entry.pItem, 0)) };
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
		return galaxy::api::FromRealID(galaxy::api::IDType::ID_TYPE_USER, GetCustomGalaxyID());
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

	bool ClientIniData::IsDLCInstalled(uint64_t product_id)
	{
		auto it = DLCs.find(product_id);
		bool result = false;
		if (it != DLCs.end()) {
			result = it->second;
		}
		else {
			result = DLCs.emplace(product_id, false).first->second;

			if (SaveUnknownDLCIDs) {
				SaveStatsAndAchievements();
			}
		}

		return result;
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
				std::string name = std::to_string(dlc.first);
				ini.SetBoolValue(DLCSection.c_str(), name.c_str(), dlc.second);
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
		return IsSelfUserID(galaxy::api::GalaxyID(userID));
	}

	bool ClientIniData::IsSelfUserID(galaxy::api::GalaxyID userID) const
	{
		return
			(userID == 0ULL) ||
			(userID == galaxy::api::FromRealID(galaxy::api::IDType::ID_TYPE_USER, 0ULL)) ||
			(userID == GetCustomGalaxyID()) ||
			(userID == GetApiGalaxyID());
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
