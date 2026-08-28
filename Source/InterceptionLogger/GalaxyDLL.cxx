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
		// REVIEW: Init/Shutdown/getter exports all access this shared object without
		// synchronization. A getter or ProcessData racing Shutdown can call through
		// a unique_ptr while reset destroys it; serialize lifecycle and API access.
		InterfaceInstances universe_client_api;
	}

	void Init(const InitOptionsModern& initOptions)
	{
		console::Redirector::get()->capture_tee();

#ifdef _WIN32
		{
			TCHAR szFileName[MAX_PATH];
			// REVIEW: GetModuleFileName returns zero on failure and a length on
			// success. This condition is reversed, so the failure path prints an
			// uninitialized buffer while successful calls print nothing.
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

		// REVIEW: If init throws before allocating config (for example bad_alloc),
		// this unconditional dereference crashes while handling the original error.
		// Return or guard when initialization failed before using config.
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

#if GALAXY_BUILD_FEATURE_HAS_SHUTDOWNOPTIONS
	void ShutdownEx(const ShutdownOptions& shutdownOptions) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL };

		// REVIEW: shutdownOptions is accepted at the ABI boundary but ignored.
		// Preserve the SDK option semantics or document the unsupported fields.
		universe_client_api.reset();
	}
#endif

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
		// REVIEW: real_process_data is an empty std::function before a successful
		// Init and after reset(). Calling ProcessData in either state throws
		// std::bad_function_call through the exported ABI; guard the lifecycle or
		// return a documented initialization error.
		universe_client_api.real_process_data();
	}

	IListenerRegistrar* ListenerRegistrar() {
		return universe_client_api.notification.get();
	}

	/*
	* Seems this gets called after each ProcessData call.
	*/
	const IError* GetError() {
		if (!universe_client_api.error || !universe_client_api.error->HasError()) {
			return nullptr;
		}

		return universe_client_api.error.get();
	}

	uint32_t load() {
		// REVIEW: real_load is a shared std::function initialized lazily without
		// synchronization; concurrent load() calls race during assignment. Protect
		// lazy resolution with call_once or equivalent locking.
		if (!universe_client_api.real_load) {
			universe_client_api.real_load = SharedLibUtils::get_func<functional::xt<decltype(universe_client_api.real_load)>::PTR>("load");
		}

		return universe_client_api.real_load();
	}
}
