#pragma once

class GameStartupManager
{
private:
	static uint32_t *pLandingPage;
	static uint32_t *pStartupFlow;

	static uint32_t originalSettings[2];

public:
	static DWORD WINAPI WorkerThread();
	static bool Setup();
};
