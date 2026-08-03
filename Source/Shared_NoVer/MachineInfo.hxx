#pragma once

#include <string>
#include <vector>
#include <filesystem>

namespace universelan {
	class MachineInfo
	{
	public:
		struct KnownPath {
			bool available = false;
			std::filesystem::path path{};
		};

		struct KnownPaths {
			KnownPath library_directory;
			KnownPath executable_directory;
			KnownPath working_directory;
			KnownPath local_appdata_directory;
			KnownPath local_appdata_game_directory;
			KnownPath temporary_directory;

			KnownPath boot_file_path;
			KnownPath chosen_operating_directory;
		};

	private:
		const std::string BootFile = "UniverseLAN.ini";

		std::string machine_name;
		std::string user_name;
		std::string machine_id;
		std::size_t process_id;

		std::vector<std::string> macs;

		KnownPaths known_paths;

	public:

		MachineInfo();

		std::string GetLocalMachineName() const;
		std::string GetLocalUserName() const;
		std::string GetInstallationID() const;
		std::size_t GetProcessID() const;
		std::vector<std::string> GetLocalMACs() const;
		int GetDebugID(const std::filesystem::path& root_temp_path) const;

		KnownPaths GetKnownPaths() const;
		KnownPath GetOperatingPath() const;
		KnownPath GetBootFile() const;
		std::vector<std::filesystem::path> GetBootFileSearchLocations() const;
	};
}
