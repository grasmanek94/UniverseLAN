#include "Main.h"

static TestThread testThread;

DWORD WINAPI ClientCore::Run()
{
	while(!GameUtility::IsIntroMovieStringAvailable())
	{
		Sleep(50);
	}
	
	GamePatches::SkipIntro();

	if(!InputHook::Initialize())
	{
		OutputDebugString(L"[V+ | Core] Failed to initialize input hook.");
		return 0;
	}

	GameVersion::Check();
	LOG_PRINT("[V+ | Core] Game version: %d", GameVersion::Get());

	if(GameVersion::IsSupported())
	{
		GamePatches::InstallPatches();
		GameHooks::InstallHooks();

		GameAddresses::FindAddresses();

		HWND windowHandle = FindWindow(L"grcWindow", NULL);
		SetWindowText(windowHandle, L"V+");

		GameStateWatcher::Setup();
		GameOverlay::Setup();
		GameStartupManager::Setup();

		if(ScriptEngine::Initialize())
		{
			while(ScriptEngine::IsThreadCollectionEmpty())
			{
				Sleep(100);
			}

			ScriptEngine::CreateThread(&testThread);
		}
	}
	else
	{
		OutputDebugString(L"[V+ | Core] Unsupported game version.");

		ExitProcess(0);
		return 0;
	}

	return 1;
}

void ClientCore::Initialize()
{
	srand((unsigned int)(time(0)));
	hook::set_base();

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Run, NULL, NULL, NULL);
}

void ClientCore::Shutdown()
{
	GameOverlay::Shutdown();
}
