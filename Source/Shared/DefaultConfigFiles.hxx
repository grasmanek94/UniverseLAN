#pragma once

#include <filesystem>
#include <string>

namespace universelan::defaults {
	void create_boot_file(const std::filesystem::path& filename);
	void create_client_config_file(const std::filesystem::path& filename);
	void create_server_config_file(const std::filesystem::path& filename);
}