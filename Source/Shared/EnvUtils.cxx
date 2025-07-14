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
#ifdef _WIN32
		size_t required = 0;
		getenv_s(&required, NULL, 0, var.c_str());

		if (required != 0) {
			std::unique_ptr<char[]> env_data(new char[required]);
			if (getenv_s(&required, env_data.get(), required, var.c_str()) == 0) {
				if (required > 0) {
					return std::string(env_data.get(), required - 1);
				}
			}
		}

#else
		const char* env_data = std::getenv(var.c_str());
		if (env_data != nullptr) {
			return std::string(env_data);
		}
#endif

		return "";
	}

	std::string get_gamedata_path_prefix()
	{
		return get_env(UNIVERSELAN_GAMEDATA_PREFIX);
	}
}
