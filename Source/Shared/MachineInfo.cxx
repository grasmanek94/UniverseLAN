#include "MachineInfo.hxx"

#include <nlohmann/json.hpp>

#ifdef _WIN32
#include <Windows.h>
#include <winsock2.h>
#include <iphlpapi.h>
#include <shlobj.h>
#else
#include <fcntl.h>
#include <unistd.h>
#include <dlfcn.h>
#endif

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <mutex>
#include <sstream>
#include <string>
#include <system_error> 

namespace universelan {
	namespace {
		const std::wstring gog_info_extension(L".info");
		const std::wstring gog_info_prefix(L"goggame-");

		const std::wstring universelan_directory(L"UniverseLAN");

		void GetCurrentLibraryPaths(MachineInfo::KnownPaths& known_paths);
	}

	MachineInfo::MachineInfo() :
		machine_name{ "" }, user_name{ "" }, machine_id{ "" }, macs{}, known_paths{}
	{
		::universelan::GetCurrentLibraryPaths(known_paths);
	}

	static std::string hexStr(const uint8_t* data, int len);
#ifdef _WIN32
	static int RetriveLocalMacAddress(ULONG ulFlags, ULONG ulFamily, unsigned char** pszAddress);
#endif

	std::string MachineInfo::GetLocalMachineName()
	{
#ifdef _WIN32
		if (machine_name.length() == 0) {
			const size_t INFO_BUFFER_SIZE = 32;
			TCHAR  infoBuf[INFO_BUFFER_SIZE];
			DWORD  bufCharCount = INFO_BUFFER_SIZE;

			// Get the computer name.
			if (GetComputerName(infoBuf, &bufCharCount)) {
				if (bufCharCount > 0) {
					machine_name.assign((const char* const)infoBuf, (const size_t)(bufCharCount - 1));
				}
			}
		}
#else
		machine_name = "GetLocalMachineNameNotImplemented";
#endif

		return machine_name;
	}

	std::string MachineInfo::GetLocalUserName()
	{
#ifdef _WIN32
		if (user_name.length() == 0) {
			const size_t INFO_BUFFER_SIZE = 256;
			TCHAR  infoBuf[INFO_BUFFER_SIZE];
			DWORD  bufCharCount = INFO_BUFFER_SIZE;

			// Get the user name.
			if (GetUserName(infoBuf, &bufCharCount)) {
				if (bufCharCount > 0) {
					user_name.assign((const char* const)infoBuf, (const size_t)(bufCharCount - 1));
				}
			}
		}
#else
		user_name = "GetLocalUserNameNotImplemented";
#endif

		return user_name;
	}

	std::string MachineInfo::GetInstallationID()
	{
#ifdef _WIN32
		const std::string subkey = "SOFTWARE\\Microsoft\\Cryptography";
		const std::string valueName = "MachineGuid";
		HKEY hKey = NULL;
		char guid[256];
		DWORD guidSize = sizeof(guid);

		if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, subkey.c_str(), 0, KEY_READ | KEY_WOW64_64KEY, &hKey) == ERROR_SUCCESS) {
			if (RegQueryValueExA(hKey, valueName.c_str(), nullptr, nullptr, reinterpret_cast<LPBYTE>(guid), &guidSize) == ERROR_SUCCESS) {
				machine_id.assign((const char* const)guid, (const size_t)(guidSize - 1));
			}
			RegCloseKey(hKey);
		}

#else
		std::ifstream file("/etc/machine-id");
		if (file.is_open()) {
			std::getline(file, machine_id);
		}
#endif

		return machine_id;
	}

	std::vector<std::string> MachineInfo::GetLocalMACs()
	{
		if (macs.size() == 0) {
#ifdef _WIN32
			unsigned char* pszBuff = NULL;
			int nCount = 0;
			int idx = 0;
			int chPos = 0;
			nCount = RetriveLocalMacAddress(GAA_FLAG_INCLUDE_ALL_COMPARTMENTS, AF_UNSPEC, &pszBuff);

			for (idx = 0; idx < nCount; ++idx)
			{
				chPos = MAX_ADAPTER_ADDRESS_LENGTH * idx;
				std::string str(hexStr((pszBuff + chPos), 6));
				if (str != "000000000000") {
					macs.push_back(str);
				}
			}

			HeapFree(GetProcessHeap(), 0x00, pszBuff);
			pszBuff = NULL;
#else
			macs.push_back("12345678abcd");
#endif
		}

		return macs;
	}

	std::size_t MachineInfo::GetProcessID() {
		std::size_t process_id = 0;

#ifdef _WIN32
		process_id = (std::size_t)GetCurrentProcessId();
#else
		process_id = (std::size_t)::getpid();
#endif

		return process_id;
	}

	static std::string hexStr(const uint8_t* data, int len)
	{
		std::stringstream ss;
		ss << std::hex;

		for (int i(0); i < len; ++i)
			ss << std::setw(2) << std::setfill('0') << (int)data[i];

		return ss.str();
	}

#ifdef _WIN32
	static int RetriveLocalMacAddress(ULONG ulFlags, ULONG ulFamily, unsigned char** pszAddress)
	{
		PIP_ADAPTER_ADDRESSES pCurrAddresses = NULL;
		PIP_ADAPTER_ADDRESSES pAddresses = NULL;

		int nAddressCount = 0;
		DWORD dwRetVal = 0;
		ULONG ulBufLen = sizeof(IP_ADAPTER_ADDRESSES);
		HANDLE hHeap = NULL;

		hHeap = GetProcessHeap();
		pAddresses = (PIP_ADAPTER_ADDRESSES)HeapAlloc(hHeap, 0x00, ulBufLen);
		if (pAddresses == NULL) {
			return 0;
		}

		dwRetVal = GetAdaptersAddresses(ulFamily, ulFlags, NULL, pAddresses, &ulBufLen);
		if (dwRetVal == ERROR_BUFFER_OVERFLOW)
		{
			HeapFree(hHeap, 0x00, pAddresses);
			pAddresses = (PIP_ADAPTER_ADDRESSES)HeapAlloc(hHeap, 0x00, ulBufLen);
		}

		if (pAddresses == NULL) {
			return 0;
		}

		dwRetVal = GetAdaptersAddresses(ulFamily, ulFlags, NULL, pAddresses, &ulBufLen);
		if (dwRetVal == NO_ERROR)
		{
			pCurrAddresses = pAddresses;
			while (pCurrAddresses)
			{
				pCurrAddresses = pCurrAddresses->Next;
				++nAddressCount;
			}

			*pszAddress = (unsigned char*)HeapAlloc(hHeap, 0x00, MAX_ADAPTER_ADDRESS_LENGTH * nAddressCount);
			pCurrAddresses = pAddresses;
			nAddressCount = 0;
			while (pCurrAddresses)
			{
				RtlCopyMemory(*pszAddress + (MAX_ADAPTER_ADDRESS_LENGTH * nAddressCount++),
					pCurrAddresses->PhysicalAddress,
					MAX_ADAPTER_ADDRESS_LENGTH);
				pCurrAddresses = pCurrAddresses->Next;
			}
		}

		if (pAddresses) {
			HeapFree(hHeap, 0x00, pAddresses);
			pAddresses = NULL;
		}
		return nAddressCount;
	}

#else
	bool lock_file(const std::string& filename) {
		int fd = open(filename.c_str(), O_RDWR | O_CREAT, 0666);  // Open or create the file
		if (fd == -1) {
			return false;  // Failed to open the file
		}

		struct flock lock;
		lock.l_type = F_WRLCK;  // Write lock
		lock.l_whence = SEEK_SET;  // Lock the whole file
		lock.l_start = 0;
		lock.l_len = 0;

		// Try to lock the file (F_SETLK for non-blocking operation)
		if (fcntl(fd, F_SETLK, &lock) == -1) {
			close(fd);
			return false;
		}

		// File successfully locked
		return true;
	}
#endif

	namespace {
		const std::string debug_temp_filename = ".universelanclientapimultiprocessdebugcounter.";
		const int max_debug_id = 16;
		int my_debug_id = -1;
		std::mutex debug_id_mtx;

#ifdef _WIN32
		void GetModuleFileNameSafe(const HMODULE module, MachineInfo::KnownPath& known_path) {
			known_path.available = false;

			std::wstring path;
			path.resize(MAX_PATH);

			while (true) {
				const DWORD len = GetModuleFileNameW(module,
					path.data(),
					(DWORD)path.size());

				if (len == 0) {
					break;
				}

				if (len < (path.size() - 1)) {
					// trim to actual content
					path.resize(len);

					known_path.available = true;
					known_path.path = std::filesystem::path(path).parent_path();

					break;
				}

				// grow and retry
				path.resize(path.size() * 2);
			}
		}

		void GetLocalAppDataDirectory(MachineInfo::KnownPath& known_path) {
			known_path.available = false;

			PWSTR local_appdata_path = nullptr;
			const HRESULT hr = SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, nullptr, &local_appdata_path);
			if (SUCCEEDED(hr) && local_appdata_path) {

				known_path.available = true;
				known_path.path = std::filesystem::path(local_appdata_path);

				CoTaskMemFree(local_appdata_path);
			}
			else {
				// TODO: _wdupenv_s
				const wchar_t* const local_appdata_path_env = _wgetenv(L"LOCALAPPDATA");
				if (local_appdata_path_env != nullptr) {
					known_path.available = true;
					known_path.path = std::filesystem::path(local_appdata_path_env);
				}
			}
		}
#endif
		std::optional<uint64_t> TryGetJsonGameID(const nlohmann::json& json, const std::string& entry) {
			try {
				auto game_id = json.find(entry);
				if (game_id != json.end()) {
					if (game_id->is_string()) {
						const std::string& s = game_id->get_ref<const std::string&>();
						return std::stoull(s);
					}
					else {
						return game_id->get<uint64_t>();
					}
				}
			}
			catch (...) {}

			return std::nullopt;
		}

		std::optional<uint64_t> TryGetRootGameID(const std::filesystem::path& path) {
			using json = nlohmann::json;

			std::error_code ec;
			if (!std::filesystem::exists(path, ec) || !std::filesystem::is_regular_file(path, ec)) {
				return std::nullopt;
			}

			constexpr uintmax_t max_reasonable_json_size = 16 * 1024 * 1024;
			uintmax_t size = std::filesystem::file_size(path, ec);
			if (!ec && size > max_reasonable_json_size) {
				return std::nullopt;
			}

			std::ifstream f(path, std::ios::in | std::ios::binary);
			if (!f) {
				return std::nullopt;
			}

			try {
				json data = json::parse(f);

				// Prefer "rootGameId"; fallback to "gameId"
				auto root_game_id = TryGetJsonGameID(data, "rootGameId");
				if (root_game_id) {
					return root_game_id;
				}

				auto game_id = TryGetJsonGameID(data, "gameId");
				if (game_id) {
					return game_id;
				}

			}
			catch (...) {}

			return std::nullopt;
		}

		bool TryGetCurrentGameRootID(bool& has_found_any_info_files, uint64_t& root_game_id, const std::filesystem::path& start_dir) {

			has_found_any_info_files = false;
			for (auto& p : std::filesystem::directory_iterator(start_dir))
			{
				if (p.path().extension() == gog_info_extension &&
					p.path().filename().wstring().starts_with(gog_info_prefix)) {

					has_found_any_info_files = true;

					auto root_game_id = TryGetRootGameID(p.path());
					if (root_game_id) {
						return true;
					}
				}
			}

			return false;
		}

		void GetCurrentGameLocalAppDataDirectory(MachineInfo::KnownPaths& known_paths) {
			known_paths.local_appdata_game_directory.available = false;

			if (!known_paths.executable_directory.available && !known_paths.library_directory.available) {
				return;
			}

			if (!known_paths.local_appdata_directory.available) {
				return;
			}

			std::filesystem::path start_dir =
				known_paths.library_directory.available ? known_paths.library_directory.path : known_paths.executable_directory.path;

			uint64_t game_root_id = 0;
			bool has_found_any_info_files = false;

			while (!has_found_any_info_files && !TryGetCurrentGameRootID(has_found_any_info_files, game_root_id, start_dir)) {
				std::filesystem::path parent = start_dir.parent_path();

				if (parent.empty() || parent == start_dir || start_dir == start_dir.root_path()) {
					break;
				}
				start_dir = parent;
			}

			if (game_root_id == 0) {
				return;
			}

			known_paths.local_appdata_game_directory.available = true;
			known_paths.local_appdata_game_directory.path = known_paths.local_appdata_directory.path / universelan_directory / std::to_wstring(game_root_id);
		}

		void GetCurrentLibraryPaths(MachineInfo::KnownPaths& known_paths) {

			known_paths.executable_directory.available = false;
			known_paths.library_directory.available = false;
			known_paths.working_directory.available = false;
			known_paths.local_appdata_directory.available = false;
			known_paths.local_appdata_game_directory.available = false;

			known_paths.working_directory.path = std::filesystem::current_path();
			known_paths.working_directory.available = true;

#ifdef _WIN32
			HMODULE module_handle = nullptr;

			// The FROM_ADDRESS flag tells Windows we are passing an address within the module
			// UNCHANGED_REFCOUNT avoids changing the module's refcount.
			if (GetModuleHandleExW(
				GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
				GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
				reinterpret_cast<LPCWSTR>(&GetCurrentLibraryPaths),
				&module_handle)) {

				GetModuleFileNameSafe(module_handle, known_paths.library_directory);
			}

			GetModuleFileNameSafe(nullptr, known_paths.executable_directory);

			GetLocalAppDataDirectory(known_paths.local_appdata_directory);

#else
			// POSIX (Linux/macOS): dladdr gives us the shared object file containing the given symbol
			Dl_info info{};
			if (dladdr(reinterpret_cast<const void*>(&GetCurrentLibraryPath), &info) == 0 ||
				info.dli_fname == nullptr) {
				// Fallback: try /proc/self/exe (Linux) or return empty on macOS if not available
#ifdef __linux__
				std::filesystem::path exePath = "/proc/self/exe";
				std::error_code ec;
				auto resolved = std::filesystem::read_symlink(exePath, ec);
				if (ec) return {};
				return resolved.parent_path();
#else
				return {};
#endif
			}

			std::filesystem::path soPath(info.dli_fname);
			return soPath.parent_path();
#endif
		}
	}

	int MachineInfo::GetDebugID(std::string root_temp_path) {
		std::scoped_lock<std::mutex> id_lock{ debug_id_mtx };

		if (my_debug_id != -1) {
			return my_debug_id;
		}

		std::filesystem::path root{ root_temp_path };
		std::error_code ec;

		std::filesystem::create_directories(root, ec);

		for (int id = 0; id < max_debug_id; ++id) {
			std::filesystem::path p = root / (debug_temp_filename + std::to_string(id));

#ifdef _WIN32
			bool lock_success = (CreateFile(p.string().c_str(), GENERIC_READ, 0, NULL, OPEN_ALWAYS, 0, NULL) != INVALID_HANDLE_VALUE);
#else
			bool lock_success = lock_file(p.string());
#endif

			if (lock_success) {
				my_debug_id = id;
				return id;
			}
		}

		return -1;
	}

	std::filesystem::path MachineInfo::GetCurrentLibraryPath() {
		return "";
	}


	std::filesystem::path MachineInfo::GetSettingsStoragePath() {

		return "";
	}
}
