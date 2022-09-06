#pragma once

enum eGameState
{
	GameStateUnknown = -1,

	GameStatePlaying = 0,
	GameStateIntro = 1,
	GameStateLegalScreen = 3,
	GameStateMainMenu = 5,
	GameStateLoading = 6,
	GameStateRestartStory = 8
};

class GameStateWatcher
{
private:
	static eGameState *pGameState;

public:
	static eGameState GetGameState();

	static DWORD WINAPI WorkerThread();
	static bool Setup();
};
