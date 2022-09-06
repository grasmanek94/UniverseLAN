#include <ClientCore.h>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch(ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		{
			ClientCore::Initialize();
			break;
		}

		case DLL_PROCESS_DETACH:
		{
			ClientCore::Shutdown();
			break;
		}
	}

	return TRUE;
}
