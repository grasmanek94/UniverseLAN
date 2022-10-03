/**
 * @file
 * Includes all other files that are needed to work with the Galaxy library.
 */

#include "CustomConsole.hxx"
#include "UniverseLAN.hxx"

#include <Version.hxx>

namespace galaxy::api {
	using namespace universelan;
	using namespace universelan::client;

	GALAXY_DLL_EXPORT void GALAXY_CALLTYPE Init(const InitOptions& initOptions) {
		{
			TCHAR szFileName[MAX_PATH];
			if (GetModuleFileName(NULL, szFileName, MAX_PATH) == ERROR_SUCCESS) {
				std::cout << "Process: " << szFileName << std::endl;
			}
		}

		try
		{
			intf_inst.init(initOptions);
		}
		catch (std::exception& ex) {
			MessageBox(NULL, ex.what(), "UniverseLAN - Error", 0);
		}

		tracer::Trace trace{ __FUNCTION__ };

		if (intf_inst.config->GetEnableConsole()) {
			EnableCustomConsole();
		}

		std::cout << " == UniverseLAN Client == " << std::endl;
		std::cout << "Version: " << Version_Number << std::endl;
		std::cout << "Using username: " << intf_inst.config->GetCustomPersonaName() << std::endl;
		std::cout << "Using key: " << const_hash64(intf_inst.config->GetAuthenticationKey()) << std::endl;
		std::cout << "Using GalaxyID: " << intf_inst.config->GetCustomGalaxyID() << std::endl;

		intf_inst.client->Start();
	}

	GALAXY_DLL_EXPORT void GALAXY_CALLTYPE Shutdown() {
		tracer::Trace trace{ __FUNCTION__ };

		intf_inst.reset();
	}

	GALAXY_DLL_EXPORT IUser* GALAXY_CALLTYPE User() {
		//tracer::Trace trace{ __FUNCTION__ };

		return intf_inst.user.get();
	}

	GALAXY_DLL_EXPORT IFriends* GALAXY_CALLTYPE Friends() {
		//tracer::Trace trace{ __FUNCTION__ };

		return intf_inst.friends.get();
	}

	GALAXY_DLL_EXPORT IChat* GALAXY_CALLTYPE Chat() {
		//tracer::Trace trace{ __FUNCTION__ };

		return intf_inst.chat.get();
	}

	GALAXY_DLL_EXPORT IMatchmaking* GALAXY_CALLTYPE Matchmaking() {
		//tracer::Trace trace{ __FUNCTION__ };

		return intf_inst.matchmaking.get();
	}

	GALAXY_DLL_EXPORT INetworking* GALAXY_CALLTYPE Networking() {
		//tracer::Trace trace{ __FUNCTION__ };

		return intf_inst.networking.get();
	}

	GALAXY_DLL_EXPORT IStats* GALAXY_CALLTYPE Stats() {
		//tracer::Trace trace{ __FUNCTION__ };

		return intf_inst.stats.get();
	}

	GALAXY_DLL_EXPORT IUtils* GALAXY_CALLTYPE Utils() {
		//tracer::Trace trace{ __FUNCTION__ };

		return intf_inst.utils.get();
	}

	GALAXY_DLL_EXPORT IApps* GALAXY_CALLTYPE Apps() {
		//tracer::Trace trace{ __FUNCTION__ };

		return intf_inst.apps.get();
	}

	GALAXY_DLL_EXPORT IStorage* GALAXY_CALLTYPE Storage() {
		//tracer::Trace trace{ __FUNCTION__ };

		return intf_inst.storage.get();
	}

	GALAXY_DLL_EXPORT ICustomNetworking* GALAXY_CALLTYPE CustomNetworking() {
		//tracer::Trace trace{ __FUNCTION__ };

		return intf_inst.custom_networking.get();
	}

	GALAXY_DLL_EXPORT ILogger* GALAXY_CALLTYPE Logger() {
		//tracer::Trace trace{ __FUNCTION__ };

		return intf_inst.logger.get();
	}

	GALAXY_DLL_EXPORT ITelemetry* GALAXY_CALLTYPE Telemetry() {
		//tracer::Trace trace{ __FUNCTION__ };

		return intf_inst.telemetry.get();
	}

	GALAXY_DLL_EXPORT void GALAXY_CALLTYPE ProcessData() {
		//tracer::Trace trace{ __FUNCTION__ };

		if (intf_inst.client != nullptr) {
			intf_inst.client->ProcessEvents();
		}

		if (intf_inst.delay_runner != nullptr) {
			intf_inst.delay_runner->Run();
		}
	}

	GALAXY_DLL_EXPORT IListenerRegistrar* GALAXY_CALLTYPE ListenerRegistrar() {
		//tracer::Trace trace{ __FUNCTION__ };

		return intf_inst.notification.get();
	}

	/*
	* Seems this gets called after each ProcessData call.
	*/
	GALAXY_DLL_EXPORT const IError* GALAXY_CALLTYPE GetError() {
		//tracer::Trace trace{ __FUNCTION__ };

		return nullptr;
	}
}

extern "C" GALAXY_DLL_EXPORT uint32_t load() {
	universelan::tracer::Trace trace{ __FUNCTION__ };

	return 0;
}

//BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
//
//	if (fdwReason == DLL_PROCESS_ATTACH) {
//		std::cout << "DLL_PROCESS_ATTACH" << std::endl;
//	}
//	else if (fdwReason == DLL_PROCESS_DETACH) {
//		std::cout << "DLL_PROCESS_DETACH" << std::endl;
//	}
//	return TRUE;
//}