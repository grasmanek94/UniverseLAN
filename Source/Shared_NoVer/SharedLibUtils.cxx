#include "SharedLibUtils.hxx"
#include "EnvUtils.hxx"

#ifdef _WIN32
#include <Windows.h>
#include "imagehlp.h"
#else 
#include <dlfcn.h>
#endif

#include <exception>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
	void ListDLLFunctions(const std::string& sADllName, std::vector<std::string>& slListOfDllFunctions)
	{
		slListOfDllFunctions.clear();

#ifdef _WIN32
		DWORD* dNameRVAs = nullptr;
		const IMAGE_EXPORT_DIRECTORY* ImageExportDirectory = nullptr;
		unsigned long cDirSize = 0;
		LOADED_IMAGE LoadedImage{};
		if (MapAndLoad(sADllName.c_str(), nullptr, &LoadedImage, TRUE, TRUE))
		{
			std::exception_ptr ex_ptr = nullptr;
			try
			{
				ImageExportDirectory = (const IMAGE_EXPORT_DIRECTORY*)
					ImageDirectoryEntryToData(LoadedImage.MappedAddress,
						FALSE, IMAGE_DIRECTORY_ENTRY_EXPORT, &cDirSize);
				if (ImageExportDirectory != nullptr)
				{
					dNameRVAs = (DWORD*)ImageRvaToVa(LoadedImage.FileHeader,
						LoadedImage.MappedAddress,
						ImageExportDirectory->AddressOfNames, nullptr);
					if (dNameRVAs != nullptr)
					{
						for (size_t i = 0; i < ImageExportDirectory->NumberOfNames; i++)
						{
							char* sName = (char*)ImageRvaToVa(LoadedImage.FileHeader,
								LoadedImage.MappedAddress,
								dNameRVAs[i], nullptr);
							if (sName != nullptr)
							{
								slListOfDllFunctions.push_back(sName);
							}
						}
					}
				}
			}
			catch (...) 
			{ 
				ex_ptr = std::current_exception();
			}

			(void)UnMapAndLoad(&LoadedImage);

			if (ex_ptr != nullptr)
			{
				std::rethrow_exception(ex_ptr);
			}
		}
#else
#warning SharedLibUtils 'get_function_match' doesn't support non-Windows platforms yet
#endif
	}
}

namespace universelan
{

	namespace {
		using HANDLE_T =
#ifdef _WIN32
			HINSTANCE
#else
			void*
#endif
			;

		HANDLE_T RealGalaxyDLL = nullptr;
		std::string dll_name = "";
		std::vector<std::string> dll_functions;
		const char UNIVERSELAN_INTERCEPTOR_REALDLL_PREFIX[] = "UNIVERSELAN_INTERCEPTOR_REALDLL_PREFIX";
	}

	SharedLibUtils* SharedLibUtils::instance()
	{
		static SharedLibUtils value{};
		return &value;
	}

	SharedLibUtils::SharedLibUtils() {
		dll_functions.clear();

		dll_name = env_utils::get_env(UNIVERSELAN_INTERCEPTOR_REALDLL_PREFIX) +
#ifndef _WIN32
		"lib"
#endif
		"Real"
#if GALAXY_BUILD_FEATURE_HAS_RED_PREFIX
		"RED"
#endif
		"Galaxy"
#if defined(_WIN64) || (defined(_LP64) && _LP64 == 1)
		"64"
#endif
#ifdef _WIN32
		".dll"
#else
		".so"
#endif
			;

		ListDLLFunctions(dll_name, dll_functions);

		RealGalaxyDLL =
#ifdef _WIN32
			LoadLibraryA(dll_name.c_str());
#else
			dlopen(dll_name.c_str(), RTLD_LAZY);
#endif
		if (RealGalaxyDLL == nullptr) {
			throw std::runtime_error(("RealGalaxyDLL: could not locate  '" + dll_name + "'").c_str());
		}
	}

	SharedLibUtils::~SharedLibUtils() {
		if (RealGalaxyDLL != nullptr)
		{
#ifdef _WIN32
			FreeLibrary(RealGalaxyDLL);
#else
			dlclose(RealGalaxyDLL);
#endif
		}
	}

	void* SharedLibUtils::get_func_ptr(const char* const name) {
		if ((name == nullptr) || (name[0] == '\0')) {
			throw std::runtime_error("RealGalaxyDLL: name is null or empty");
		}

		(void)instance();

		void* func = (void*)
#ifdef _WIN32
			GetProcAddress(RealGalaxyDLL, name);
#else	
			dlsym(RealGalaxyDLL, name);
#endif

		if (func == nullptr) {
			throw std::runtime_error(("RealGalaxyDLL: could not locate the function '" + std::string(name) + "'").c_str());
		}

		return func;
	}

	const char* SharedLibUtils::get_function_match(const char* const search) {
		if ((search == nullptr) || (search[0] == '\0')) {
			throw std::runtime_error("RealGalaxyDLL: search is null or empty");
		}

		(void)instance();

		const char* match = nullptr;
		for (auto& func : dll_functions) {
			if (func.find(search) != std::string::npos) {
				if (match != nullptr) {
					throw std::runtime_error(("RealGalaxyDLL: multiple matches found for search '" + std::string(search) + "'").c_str());
				}
				match = func.c_str();
			}
		}

		if (match == nullptr) {
			throw std::runtime_error(("RealGalaxyDLL: no matches found for search '" + std::string(search) + "'").c_str());
		}

		return match;
	}
}
