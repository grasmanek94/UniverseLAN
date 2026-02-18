#include "IniData.hxx"

#include "ConsoleCoutRedirector.hxx"
#include "ConstHash.hxx"
#include "DefaultConfigFiles.hxx"
#include "EnvUtils.hxx"
#include "MachineInfo.hxx"

#include <boost/algorithm/string/join.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <magic_enum/magic_enum.hpp>
#include <Tracer.hxx>

#include <charconv>
#include <chrono>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string_view>
#include <string>

#include <SimpleIni.h>

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
			uint64_t disable_flags = 0;

			for (auto& entry : result) {
				bool disable = entry.starts_with('~') || entry.starts_with('!');
				if (disable) {
					entry = trim(entry.substr(1));
				}

				uint64_t flag = magic_enum::enum_cast<tracer::Trace::MASK>(entry).value_or(tracer::Trace::INFORMATIONAL);

				if (flag == tracer::Trace::TRACE_ALL_FLAGS) {
					if (disable) {
						return 0ULL;
					}
					else {
						flags = std::numeric_limits<decltype(flags)>::max();
					}
				}
				else {
					if (disable) {
						disable_flags |= flag;
					}
					else {
						flags |= flag;
					}
				}
			}

			if (disable_flags) {
				flags &= ~disable_flags;
			}

			return flags;
		}

		void LoadIni(CSimpleIniA& ini, const std::filesystem::path& filename, bool show_error, const std::vector<std::filesystem::path>& search_locations)
		{
			SI_Error rc = ini.LoadFile(filename.c_str());
			if (rc < 0) {

				auto joined_search_locations = boost::algorithm::join(
					search_locations | boost::adaptors::transformed([](const std::filesystem::path& p) { return p.wstring(); }),
					L"\n"
				); // std::wstring

				std::wstring problem = L"Cannot load or parse '" + filename.wstring() + L"', error (Return Code / errno): " + std::to_wstring(rc) +
					L" / " + std::to_wstring(errno) + L"\nWill try to use sane defaults.\nPlease check if the file exists, is readable and accessible.\nTried searching in:\n" +
					joined_search_locations;

#ifdef _WIN32
				if (show_error) {
					MessageBoxW(NULL, problem.c_str(), L"UniverseLAN - Error", MB_ICONWARNING);
				}
				else {
					std::wcout << "Exception occurred during init: " << problem << std::endl;
				}
#else
				std::wcout << "Exception occurred during init: " << problem << std::endl;
#endif
			}
		}

		void LoadIni(CSimpleIniA& ini, const std::filesystem::path& filename, bool show_error)
		{
			SI_Error rc = ini.LoadFile(filename.c_str());
			if (rc < 0) {
				std::wstring problem = L"Cannot load or parse '" + filename.wstring() + L"', error (Return Code / errno): " + std::to_wstring(rc) +
					L" / " + std::to_wstring(errno) + L"\nWill try to use sane defaults.\nPlease check if the file exists, is readable and accessible.";

#ifdef _WIN32
				if (show_error) {
					MessageBoxW(NULL, problem.c_str(), L"UniverseLAN - Error", MB_ICONWARNING);
				}
				else {
					std::wcout << "Exception occurred during init: " << problem << std::endl;
				}			
#else
				std::wcout << "Exception occurred during init: " << problem << std::endl;
#endif
			}
		}

		void CheckDefaultConfig(const MachineInfo& machine_info, bool show_info = false) {
			/* Local App Data dir has been chosen -- no other UniverseLAN.ini files found */
			if (machine_info.GetOperatingPath().path == machine_info.GetKnownPaths().local_appdata_game_directory.path) {
				std::error_code ec;
				if (!std::filesystem::exists(machine_info.GetBootFile().path)) {
					/* Create a default UniverseLAN.ini file */
					universelan::defaults::create_boot_file(machine_info.GetBootFile().path);

					std::wstring info = L"A new config file has been created: '" + machine_info.GetBootFile().path.wstring() + L"'.\nUniverseLAN will save data there for all games.";
#ifdef _WIN32
					if (show_info) {
						MessageBoxW(NULL, info.c_str(), L"UniverseLAN - Info", MB_ICONINFORMATION);
					}
					else {
						std::wcout << "INFO: " << info << std::endl;
					}
#else
					std::wcout << "INFO: " << info << std::endl;
#endif
				}
			}
		}

		void CheckDefaultClientConfig(const MachineInfo& machine_info, const std::filesystem::path& config_file, bool show_info = false) {
			/* Local App Data dir has been chosen -- no other UniverseLAN.ini files found */
			if (machine_info.GetOperatingPath().path == machine_info.GetKnownPaths().local_appdata_game_directory.path) {
				std::error_code ec;
				if (!std::filesystem::exists(config_file)) {
					/* Create a default UniverseLAN.ini file */
					universelan::defaults::create_client_config_file(config_file);

					std::wstring info = L"A new client config file has been created: '" + config_file.wstring() + L"'.\nUniverseLAN will save data there for this game.";
#ifdef _WIN32
					if (show_info) {
						MessageBoxW(NULL, info.c_str(), L"UniverseLAN - Info", MB_ICONINFORMATION);
					}
					else {
						std::wcout << "INFO: " << info << std::endl;
					}
#else
					std::wcout << "INFO: " << info << std::endl;
#endif
				}
			}
		}

		void CheckDefaultServerConfig(const MachineInfo& machine_info, const std::filesystem::path& config_file, bool show_info = false) {
			/* Local App Data dir has been chosen -- no other UniverseLAN.ini files found */
			if (machine_info.GetOperatingPath().path == machine_info.GetKnownPaths().local_appdata_directory.path) {
				std::error_code ec;
				if (!std::filesystem::exists(config_file)) {
					/* Create a default UniverseLAN.ini file */
					universelan::defaults::create_server_config_file(config_file);

					std::wstring info = L"A new server config file has been created: '" + config_file.wstring() + L"'.\nUniverseLAN will save data there for this game server.";
#ifdef _WIN32
					if (show_info) {
						MessageBoxW(NULL, info.c_str(), L"UniverseLAN - Info", MB_ICONINFORMATION);
					}
					else {
						std::wcout << "INFO: " << info << std::endl;
					}
#else
					std::wcout << "INFO: " << info << std::endl;
#endif
				}
			}
		}
	}

	std::filesystem::path IniData::GetPath(const std::filesystem::path& base, const std::filesystem::path& filename) const
	{
		return MachineInformation.GetOperatingPath().path / base / filename;
	}

	IniData::IniData() :
		GameDataPath{ "UniverseLANData" },
		ServerDataPath{ "UniverseLANServerData" },
		CallTracing{ false },
		UnhandledExceptionLogging{ false },
		MiniDumpOnUnhandledException{ false },
		MiniDumpVerbosityLevel{ 0 },
		TracingAlwaysFlush{ false },
		CallTracingFlags{ 0 },
		TraceToConsole{ false },
		AuthenticationKey{ "" },
		MachineInformation{},
		BootTime{ std::chrono::system_clock::now() }
	{
		CSimpleIniA ini;
		ini.SetUnicode();

		if (!MachineInformation.GetBootFile().available) {
			std::wcerr << L"ERROR: Cannot determine UniverseLAN.ini path! Stuff might break." << std::endl;
		}

		if (!MachineInformation.GetOperatingPath().available) {
			std::wcerr << L"ERROR: Cannot determine data path! Stuff might break." << std::endl;
		}

		std::wcout << L"Opening Global config located at " << MachineInformation.GetBootFile().path << std::endl;

		CheckDefaultConfig(MachineInformation, true);

		LoadIni(ini, MachineInformation.GetBootFile().path, true, MachineInformation.GetBootFileSearchLocations());

		GameDataPath = ini.GetValue(StoragePathSection.c_str(), "GameDataPath", "UniverseLANData");
		ServerDataPath = ini.GetValue(StoragePathSection.c_str(), "ServerDataPath", "UniverseLANServerData");
		CallTracing = ini.GetBoolValue(TracingSection.c_str(), "CallTracing", false);
		UnhandledExceptionLogging = ini.GetBoolValue(TracingSection.c_str(), "UnhandledExceptionLogging", false);
		MiniDumpOnUnhandledException = ini.GetBoolValue(TracingSection.c_str(), "MiniDumpOnUnhandledException", false);
		MiniDumpVerbosityLevel = ini.GetLongValue(TracingSection.c_str(), "MiniDumpVerbosityLevel", 0);
		TracingAlwaysFlush = ini.GetBoolValue(TracingSection.c_str(), "AlwaysFlush", false);
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

	std::filesystem::path IniData::GetGameDataPath() const
	{
		return MachineInformation.GetOperatingPath().path / (env_utils::get_gamedata_path_prefix() + GameDataPath);
	}

	std::filesystem::path IniData::GetServerDataPath() const
	{
		return MachineInformation.GetOperatingPath().path / ServerDataPath;
	}

	const std::string& IniData::GetAuthenticationKey() const
	{
		return AuthenticationKey;
	}

	IniData::~IniData()
	{
	}

	std::filesystem::path ServerIniData::GetPath(const std::filesystem::path& filename) const {
		return IniData::GetPath(GetServerDataPath(), filename);
	}

	ServerIniData::ServerIniData()
	{
		CSimpleIniA ini;
		ini.SetUnicode();

		std::wcout << L"Opening Server config located at " << GetPath(ConfigFile) << std::endl;

		CheckDefaultServerConfig(MachineInformation, GetPath(ConfigFile), false);
		LoadIni(ini, GetPath(ConfigFile), true);

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

	std::filesystem::path ClientIniData::GetPath(const std::filesystem::path& filename) const {
		return IniData::GetPath(GetGameDataPath(), filename);
	}

	ClientIniData::ClientIniData()
		: local_user_data{ nullptr }
	{
		// Config
		{
			auto debug_root_temp_path = GetPath("Temp");
			std::cout << "Opening Client config located at " << std::filesystem::current_path() / GetPath(ConfigFile) << std::endl;

			CSimpleIniA ini;
			ini.SetUnicode();

			CheckDefaultClientConfig(MachineInformation, GetPath(ConfigFile), false);
			LoadIni(ini, GetPath(ConfigFile), true);

			Language = ini.GetValue(SettingsSection.c_str(), "Language", "english");
			LanguageCode = ini.GetValue(SettingsSection.c_str(), "LanguageCode", "en-US");
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

			auto GalaxyIDOffsetString = ini.GetValue(UserSection.c_str(), "GalaxyIDOffset", "");
			switch (const_hash(GalaxyIDOffsetString)) {
			case const_hash("@ProcessID"):
				GalaxyIDOffset = MachineInformation.GetProcessID();
				break;

			case const_hash("@DebugID"):
				GalaxyIDOffset = MachineInformation.GetDebugID(debug_root_temp_path);
				break;

			default:
				GalaxyIDOffset = ini.GetLongLongValue(UserSection.c_str(), "GalaxyIDOffset", 0);
				break;

			}

			Avatar = ini.GetValue(UserSection.c_str(), "Avatar", "me.png");
			SignedIn = ini.GetBoolValue(UserSection.c_str(), "SignedIn", true);
			AutoAcceptGameInvitations = ini.GetBoolValue(UserSection.c_str(), "AutoAcceptGameInvitations", true);

			OverrideInitKeys = ini.GetBoolValue(InterceptorSection.c_str(), "OverrideInitKeys", false);
			OverrideSignIn = ini.GetBoolValue(InterceptorSection.c_str(), "OverrideSignIn", false);

			OverrideInitKeyId = ini.GetValue(InterceptorSection.c_str(), "OverrideInitKeyId", "0");
			OverrideInitKeySecret = ini.GetValue(InterceptorSection.c_str(), "OverrideInitKeySecret", "0");

			OverrideSignInId = ini.GetValue(InterceptorSection.c_str(), "OverrideSignInId", "0");
			OverrideSignInPassword = ini.GetValue(InterceptorSection.c_str(), "OverrideSignInPassword", "0");

			if (const_hash(PersonaNameType) != const_hash("@Custom")) {

				switch (const_hash(PersonaNameType)) {
				case const_hash("@WindowsAccountName"):
					if (MachineInformation.GetLocalMachineName().size() < 1) {
						throw std::runtime_error("@WindowsAccountName: No username found");
					}

					CustomPersonaName = MachineInformation.GetLocalUserName() + (SuffixPersonaNameTypeResultWithCustomPersonaName ? CustomPersonaName : "");
					break;

				case const_hash("@WindowsAccountNameHash"):
					if (MachineInformation.GetLocalMachineName().size() < 1) {
						throw std::runtime_error("@WindowsAccountNameHash: No username found");
					}

					CustomPersonaName = std::to_string(const_hash64(MachineInformation.GetLocalUserName())) + (SuffixPersonaNameTypeResultWithCustomPersonaName ? CustomPersonaName : "");
					break;

				case const_hash("@ComputerName"):
					if (MachineInformation.GetLocalMachineName().size() < 1) {
						throw std::runtime_error("@ComputerName: No machine name found");
					}

					CustomPersonaName = MachineInformation.GetLocalMachineName() + (SuffixPersonaNameTypeResultWithCustomPersonaName ? CustomPersonaName : "");
					break;

				case const_hash("@ComputerNameHash"):
					if (MachineInformation.GetLocalMachineName().size() < 1) {
						throw std::runtime_error("@ComputerNameHash: No machine name found");
					}

					CustomPersonaName = std::to_string(const_hash64(MachineInformation.GetLocalMachineName())) + (SuffixPersonaNameTypeResultWithCustomPersonaName ? CustomPersonaName : "");
					break;

				case const_hash("@MachineID"):
					if (MachineInformation.GetInstallationID().size() < 1) {
						throw std::runtime_error("@MachineID: No Machine ID found");
					}

					CustomPersonaName = MachineInformation.GetInstallationID() + (SuffixPersonaNameTypeResultWithCustomPersonaName ? CustomPersonaName : "");
					break;

				case const_hash("@MachineIDHash"):
					if (MachineInformation.GetInstallationID().size() < 1) {
						throw std::runtime_error("@MachineIDHash: No Machine ID found");
					}

					CustomPersonaName = std::to_string(const_hash64(MachineInformation.GetInstallationID())) + (SuffixPersonaNameTypeResultWithCustomPersonaName ? CustomPersonaName : "");
					break;

				case const_hash("@NetworkAdapterMACHash"):
					if (MachineInformation.GetLocalMACs().size() < 1) {
						throw std::runtime_error("@NetworkAdapterMACHash: No MAC adresses found");
					}

					CustomPersonaName = std::to_string(const_hash64(MachineInformation.GetLocalMACs().front())) + (SuffixPersonaNameTypeResultWithCustomPersonaName ? CustomPersonaName : "");
					break;

				case const_hash("@ProcessID"):
					CustomPersonaName = std::to_string(MachineInformation.GetProcessID()) + (SuffixPersonaNameTypeResultWithCustomPersonaName ? CustomPersonaName : "");
					break;

				case const_hash("@DebugID"):
					CustomPersonaName = std::to_string(MachineInformation.GetDebugID(debug_root_temp_path)) + (SuffixPersonaNameTypeResultWithCustomPersonaName ? CustomPersonaName : "");
					break;

				default:
					throw std::runtime_error("Incorrect PersonaNameType: " + PersonaNameType);
				}
			}

			if (const_hash(GalaxyIDType) != const_hash("@Custom")) {
				std::string str;

				switch (const_hash(GalaxyIDType)) {
				case const_hash("@WindowsAccountNameHash"):
					if (MachineInformation.GetLocalMachineName().size() < 1) {
						throw std::runtime_error("@WindowsAccountNameHash: No username found");
					}

					str = MachineInformation.GetLocalUserName();
					break;

				case const_hash("@ComputerNameHash"):
					if (MachineInformation.GetLocalMachineName().size() < 1) {
						throw std::runtime_error("@ComputerNameHash: No machine name found");
					}

					str = MachineInformation.GetLocalMachineName();
					break;

				case const_hash("@MachineIDHash"):
					if (MachineInformation.GetLocalMachineName().size() < 1) {
						throw std::runtime_error("@MachineIDHash: No Machine ID found");
					}

					str = MachineInformation.GetInstallationID();
					break;

				case const_hash("@NetworkAdapterMACHash"):
					if (MachineInformation.GetLocalMACs().size() < 1) {
						throw std::runtime_error("@NetworkAdapterMACHash: No MAC adresses found");
					}

					str = MachineInformation.GetLocalMACs().front();
					break;

				default:
					throw std::runtime_error("Incorrect GalaxyIDType: " + GalaxyIDType);
				}

				CustomGalaxyID = (const_hash64(str) & GalaxyIDMask);
			}
		}

		local_user_data = std::make_shared<GalaxyUserData>(GetApiGalaxyID());
		local_user_data->nickname = CustomPersonaName;

		// Achievements
		{
			CSimpleIniA ini;
			ini.SetUnicode();

			LoadIni(ini, GetPath(AchievementsFile), false);

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

			LoadIni(ini, GetPath(DLCFile), false);

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

			LoadIni(ini, GetPath(StatsFile), false);

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

			LoadIni(ini, GetPath(UserDataFile), false);

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

	const std::string& ClientIniData::GetLanguageCode() const
	{
		return LanguageCode;
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

			LoadIni(ini, GetPath(AchievementsFile), false);

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

			LoadIni(ini, GetPath(DLCFile), false);

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

			LoadIni(ini, GetPath(StatsFile), false);

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

			LoadIni(ini, GetPath(UserDataFile), false);

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
			(userID.ToUint64() == 0) ||
			(userID == galaxy::api::FromRealID(galaxy::api::IDType::ID_TYPE_USER, 0ULL)) ||
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

	bool ClientIniData::AutoAcceptGameInvitationsEnabled() const
	{
		return AutoAcceptGameInvitations;
	}

	bool ClientIniData::OverrideInitKeysEnabled() const {
		return OverrideInitKeys;
	}

	std::string ClientIniData::GetOverrideInitKeyId() const {
		return OverrideInitKeyId;
	}

	std::string ClientIniData::GetOverrideInitKeySecret() const {
		return OverrideInitKeySecret;
	}

	bool ClientIniData::OverrideSignInEnabled() const {
		return OverrideSignIn;
	}

	std::string ClientIniData::GetOverrideSignInId() const {
		return OverrideSignInId;
	}

	std::string ClientIniData::GetOverrideSignInPassword() const {
		return OverrideSignInPassword;
	}
}
