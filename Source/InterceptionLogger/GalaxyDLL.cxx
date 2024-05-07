/**
 * @file
 * Includes all other files that are needed to work with the Galaxy library.
 */

#include "CustomConsole.hxx"
#include "UniverseLANInterceptor.hxx"
#include "GalaxyFunctional.hxx"

#include <ConsoleCoutRedirector.hxx>
#include <SharedLibUtils.hxx>
#include <Tracer.hxx>
#include <Version.hxx>

#ifdef _WIN32
#include <Windows.h>
#endif

namespace universelan::client {
	namespace {
		InterfaceInstances universe_client_api;
	}

	void Init(const InitOptionsModern& initOptions)
	{
		console::Redirector::get()->capture_tee();

#ifdef _WIN32
		{
			TCHAR szFileName[MAX_PATH];
			if (GetModuleFileName(NULL, szFileName, MAX_PATH) == ERROR_SUCCESS) {
				std::cout << "Process: " << szFileName << std::endl;
			}
		}
#endif

		try
		{
			universe_client_api.init(initOptions);
		}
		catch (std::exception& ex) {

#ifdef _WIN32
			MessageBox(NULL, ex.what(), "UniverseLAN - Error", 0);
#else
			std::cout << "Exception occurred during init: " << ex.what() << std::endl;
#endif

		}

		tracer::Trace::SetLogToCout(universe_client_api.config->ShouldTraceToConsole());

		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL };

		if (universe_client_api.config->GetEnableConsole()) {
			EnableCustomConsole();
		}

		console::Redirector::get()->release();

		std::cout << " == UniverseLAN Interceptor == " << std::endl;
		std::cout << "Build: " << Version_Number << std::endl;
	}

#if GALAXY_BUILD_FEATURE_HAS_INITOPTIONS
	void Init(const galaxy::api::InitOptions& initOptions) {
		universelan::client::Init(InitOptionsModern{ initOptions });
	}
#endif

	void Shutdown() {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL };

		universe_client_api.reset();
	}

	IUser* User() {
		return universe_client_api.user.get();
	}

	IFriends* Friends() {
		return universe_client_api.friends.get();
	}

#if GALAXY_BUILD_FEATURE_HAS_ICHAT
	IChat* Chat() {
		return universe_client_api.chat.get();
	}
#endif

	IMatchmaking* Matchmaking() {
		return universe_client_api.matchmaking.get();
	}

	INetworking* Networking() {
		return universe_client_api.networking.get();
	}

#if GALAXY_BUILD_FEATURE_HAS_ISERVERNETWORKING
	INetworking* ServerNetworking() {
		return universe_client_api.server_networking.get();
	}
#endif

	IStats* Stats() {
		return universe_client_api.stats.get();
	}

#if GALAXY_BUILD_FEATURE_HAS_IUTILS
	IUtils* Utils() {
		return universe_client_api.utils.get();
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_IAPPS
	IApps* Apps() {
		return universe_client_api.apps.get();
	}

#endif

#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE
	IStorage* Storage() {
		return universe_client_api.storage.get();
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE
	ICloudStorage* CloudStorage() {
		return universe_client_api.cloud_storage.get();
	}
#endif


#if GALAXY_BUILD_FEATURE_HAS_ICUSTOMNETWORKING
	ICustomNetworking* CustomNetworking() {
		return universe_client_api.custom_networking.get();
	}
#endif

	ILogger* Logger() {
		return universe_client_api.logger.get();
	}

#if GALAXY_BUILD_FEATURE_HAS_ITELEMETRY
	ITelemetry* Telemetry() {
		return universe_client_api.telemetry.get();
	}
#endif

	void ProcessData() {
		universe_client_api.real_process_data();
	}

	IListenerRegistrar* ListenerRegistrar() {
		return universe_client_api.notification.get();
	}

	/*
	* Seems this gets called after each ProcessData call.
	*/
	const IError* GetError() {
		return universe_client_api.error.get();
	}

	uint32_t load() {
		if (!universe_client_api.real_load) {
			universe_client_api.real_load = SharedLibUtils::get_func<functional::xt<decltype(universe_client_api.real_load)>::PTR>("load");
		}

		return universe_client_api.real_load();
	}
}
