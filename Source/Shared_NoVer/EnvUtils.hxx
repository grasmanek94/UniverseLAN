#pragma once

#include <string>

namespace universelan::env_utils
{
	std::string get_env(const std::string& var);
#ifdef _WIN32
	std::wstring get_env(const std::wstring& var);
#endif

	std::string get_gamedata_path_prefix();
}
