#pragma once

#include <string>

namespace universelan::env_utils
{
	std::string get_env(const std::string& var);
	std::string get_gamedata_path_prefix();
}
