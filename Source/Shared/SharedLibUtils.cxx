#include "SharedLibUtils.hxx"

#ifdef _WIN32
#include <Windows.h>
#include "imagehlp.h"
#else 
#include <dlfcn.h>
#endif

#include <stdlib.h>

#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
	void ListDLLFunctions(std::string sADllName, std::vector<std::string>& slListOfDllFunctions)
	{
#ifdef _WIN32
		DWORD* dNameRVAs(0);
		_IMAGE_EXPORT_DIRECTORY* ImageExportDirectory;
		unsigned long cDirSize;
		_LOADED_IMAGE LoadedImage;
		std::string sName;
		slListOfDllFunctions.clear();
		if (MapAndLoad(sADllName.c_str(), NULL, &LoadedImage, TRUE, TRUE))
		{
			ImageExportDirectory = (_IMAGE_EXPORT_DIRECTORY*)
				ImageDirectoryEntryToData(LoadedImage.MappedAddress,
					false, IMAGE_DIRECTORY_ENTRY_EXPORT, &cDirSize);
			if (ImageExportDirectory != NULL)
			{
				dNameRVAs = (DWORD*)ImageRvaToVa(LoadedImage.FileHeader,
					LoadedImage.MappedAddress,
					ImageExportDirectory->AddressOfNames, NULL);
				for (size_t i = 0; i < ImageExportDirectory->NumberOfNames; i++)
				{
					sName = (char*)ImageRvaToVa(LoadedImage.FileHeader,
						LoadedImage.MappedAddress,
						dNameRVAs[i], NULL);
					slListOfDllFunctions.push_back(sName);
				}
			}
			UnMapAndLoad(&LoadedImage);
		}
#else
		slListOfDllFunctions.clear();
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
		SharedLibUtils* instance = nullptr;
		std::string dll_name = "";
		std::vector<std::string> dll_functions;
		const char UNIVERSELAN_INTERCEPTOR_REALDLL_PREFIX[] = "UNIVERSELAN_INTERCEPTOR_REALDLL_PREFIX";
	}

	SharedLibUtils::SharedLibUtils() {
		dll_functions.clear();

		dll_name = "";

		size_t required = 0;
		getenv_s(&required, NULL, 0, UNIVERSELAN_INTERCEPTOR_REALDLL_PREFIX);

		if (required != 0) {
			std::shared_ptr<char[]> dll_prefix(new char[required]);
			if (getenv_s(&required, dll_prefix.get(), required, UNIVERSELAN_INTERCEPTOR_REALDLL_PREFIX) == 0) {
				dll_name = std::string(dll_prefix.get(), required);
			}
		}	

#ifndef _WIN32
		dll_name += "lib";
#endif
		dll_name += "Real";
#if GALAXY_BUILD_FEATURE_HAS_RED_PREFIX
		dll_name += "RED";
#endif
		dll_name += "Galaxy";
#if defined(_WIN64) || (defined(_LP64) && _LP64 == 1)
		dll_name += "64";
#endif
#ifdef _WIN32
		dll_name += ".dll";
#else
		dll_name += ".so";
#endif

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

	SharedLibUtils::~SharedLibUtils() {}

	void* SharedLibUtils::get_func_ptr(const char* name) {
		if (!instance) {
			instance = new SharedLibUtils();
		}

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

	const char* SharedLibUtils::get_function_match(const char* search) {
		if (!instance) {
			instance = new SharedLibUtils();
		}

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
