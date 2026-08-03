#include "EnvUtils.hxx"

#include <cstdlib>
#include <memory>
#include <string>

#ifndef _WIN32
#include <codecvt>
#include <locale>
#endif

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

	std::wstring get_env(const std::wstring& var)
	{
#ifdef _WIN32
		size_t required = 0;
		_wgetenv_s(&required, NULL, 0, var.c_str());

		if (required != 0) {
			std::unique_ptr<wchar_t[]> env_data(new wchar_t[required]);
			if (_wgetenv_s(&required, env_data.get(), required, var.c_str()) == 0) {
				if (required > 0) {
					return std::wstring(env_data.get(), required - 1);
				}
			}
		}

#else
		// POSIX: convert wide env name to UTF‑8, call getenv (narrow), then convert value back to wstring.
		// NOTE: uses std::wstring_convert + codecvt_utf8_utf16 for brevity; replace with your preferred converter if needed.

		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
		const std::string name_utf8 = conv.to_bytes(var);

		if (!name_utf8.empty()) {
			if (const char* env_data = std::getenv(name_utf8.c_str())) {
				return conv.from_bytes(env_data);
			}
		}

#endif

		return L"";
	}
	std::string get_gamedata_path_prefix()
	{
		return get_env(UNIVERSELAN_GAMEDATA_PREFIX);
	}
}
