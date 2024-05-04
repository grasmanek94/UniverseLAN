#include "SharedLibUtils.hxx"

#ifdef _WIN32
#include <Windows.h>
#else 
#include <dlfcn.h>
#endif

#include <stdexcept>
#include <functional>
#include <string>

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
	}

	SharedLibUtils::SharedLibUtils() {
		std::string dll_name{ "" };

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


		RealGalaxyDLL =
#ifdef _WIN32
			LoadLibraryA(dll_name.c_str());
#else
			dlopen(dll_name.c_str(), RTLD_LAZY);
#endif

	}
	SharedLibUtils::~SharedLibUtils() {

	}

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
}
