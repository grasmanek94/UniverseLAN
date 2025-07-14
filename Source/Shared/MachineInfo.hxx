#pragma once

#include <string>
#include <vector>

namespace universelan {
	class MachineInfo
	{
	private:
		std::string machine_name;
		std::string user_name;
		std::string machine_id;

		std::vector<std::string> macs;

	public:
		MachineInfo();

		std::string GetLocalMachineName();
		std::string GetLocalUserName();
		std::string GetInstallationID();
		std::size_t GetProcessID();
		std::vector<std::string> GetLocalMACs();
		int GetDebugID(std::string root_temp_path);
	};
}