/**
 * @file
 * Includes all other files that are needed to work with the Galaxy library.
 */

#include "CustomConsole.hxx"
#include "UniverseLAN.hxx"

#include <ConsoleCoutRedirector.hxx>
#include <GalaxyID.hxx>

#include <Version.hxx>

#ifdef _WIN32
#include <Windows.h>
#endif

namespace universelan::client {
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
			intf_inst.init(initOptions);
		}
		catch (std::exception& ex) {

#ifdef _WIN32
			MessageBox(NULL, ex.what(), "UniverseLAN - Error", 0);
#else
			std::cout << "Exception occurred during init: " << ex.what() << std::endl;
#endif

		}

		tracer::Trace::SetLogToCout(intf_inst.config->ShouldTraceToConsole());

		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL };

		if (intf_inst.config->GetEnableConsole()) {
			EnableCustomConsole();
		}

		console::Redirector::get()->release();

		std::cout << " == UniverseLAN Client == " << std::endl;
		std::cout << "Build: " << Version_Number << std::endl;
		std::cout << "Using username: " << intf_inst.config->GetCustomPersonaName() << std::endl;
		std::cout << "Using key: " << const_hash64(intf_inst.config->GetAuthenticationKey()) << std::endl;
		std::cout << "Using GalaxyID: " << intf_inst.config->GetCustomGalaxyID() << " (" << intf_inst.config->GetApiGalaxyID().ToUint64() << ")" << std::endl;

		intf_inst.client->Start();
	}

#if GALAXY_BUILD_FEATURE_HAS_INITOPTIONS
	void Init(const galaxy::api::InitOptions& initOptions) {
		universelan::client::Init(InitOptionsModern{ initOptions });
	}
#endif

	void Shutdown() {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL };

		intf_inst.reset();
	}

#if GALAXY_BUILD_FEATURE_HAS_SHUTDOWNOPTIONS
	void ShutdownEx(const ShutdownOptions& shutdownOptions) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL };

		intf_inst.reset();
	}
#endif

	IUser* User() {
		return intf_inst.user.get();
	}

	IFriends* Friends() {
		return intf_inst.friends.get();
	}

#if GALAXY_BUILD_FEATURE_HAS_ICHAT
	IChat* Chat() {
		return intf_inst.chat.get();
	}
#endif

	IMatchmaking* Matchmaking() {
		return intf_inst.matchmaking.get();
	}

	INetworking* Networking() {
		return intf_inst.networking.get();
	}

#if GALAXY_BUILD_FEATURE_HAS_ISERVERNETWORKING
	INetworking* ServerNetworking() {
		return intf_inst.server_networking.get();
	}
#endif

	IStats* Stats() {
		return intf_inst.stats.get();
	}

#if GALAXY_BUILD_FEATURE_HAS_IUTILS
	IUtils* Utils() {
		return intf_inst.utils.get();
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_IAPPS
	IApps* Apps() {
		return intf_inst.apps.get();
	}

#endif

#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE
	IStorage* Storage() {
		return intf_inst.storage.get();
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE
	ICloudStorage* CloudStorage() {
		return intf_inst.cloud_storage.get();
	}
#endif


#if GALAXY_BUILD_FEATURE_HAS_ICUSTOMNETWORKING
	ICustomNetworking* CustomNetworking() {
		return intf_inst.custom_networking.get();
	}
#endif

	ILogger* Logger() {
		return intf_inst.logger.get();
	}

#if GALAXY_BUILD_FEATURE_HAS_ITELEMETRY
	ITelemetry* Telemetry() {
		return intf_inst.telemetry.get();
	}
#endif

	void ProcessData() {
		if (intf_inst.client != nullptr) {
			intf_inst.client->ProcessEvents();
		}

		if (intf_inst.delay_runner != nullptr) {
			intf_inst.delay_runner->Run();
		}
	}

	IListenerRegistrar* ListenerRegistrar() {
		return intf_inst.notification.get();
	}

	/*
	* Seems this gets called after each ProcessData call.
	*/
	const IError* GetError() {
		return nullptr;
	}

	uint32_t load() {
		return 0;
	}
}
