#include "EnvUtils.hxx"

#include <cstdlib>
#include <memory>
#include <string>

namespace universelan::env_utils
{
	namespace {
		const char UNIVERSELAN_GAMEDATA_PREFIX[] = "UNIVERSELAN_GAMEDATA_PREFIX";
	}

	std::string get_env(const std::string& var)
	{
		size_t required = 0;
		getenv_s(&required, NULL, 0, var.c_str());

		if (required != 0) {
			std::shared_ptr<char[]> env_data(new char[required]);
			if (getenv_s(&required, env_data.get(), required, var.c_str()) == 0) {
				if (required > 0) {
					return std::string(env_data.get(), required - 1);
				}
			}
		}

		return "";
	}

	std::string get_gamedata_path_prefix()
	{
		return get_env(UNIVERSELAN_GAMEDATA_PREFIX);
	}
}
