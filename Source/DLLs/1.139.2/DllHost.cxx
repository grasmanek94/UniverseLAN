#include <GalaxyApi.h>

#include <windows.h>

#include <chrono>
#include <thread>

using namespace galaxy::api;
using namespace std::chrono;

class StatsListener : IUserStatsAndAchievementsRetrieveListener {
public:
	virtual void OnUserStatsAndAchievementsRetrieveSuccess(GalaxyID userID) override {
		bool is_unlocked;
		uint32_t unlock_time;
		galaxy::api::Stats()->GetAchievement("test achievement", is_unlocked, unlock_time);
	}

	virtual void OnUserStatsAndAchievementsRetrieveFailure(GalaxyID userID, FailureReason failureReason) override {
		// fail
	}
};

int Run()
{
	InitOptions options("", "");

	Init(options);

	StatsListener stats_listener;
	Stats()->RequestUserStatsAndAchievements();

	while (true)
	{
		ProcessData();
		std::this_thread::sleep_for(milliseconds(5));
	}
	return 0;
}

int
#ifndef _WIN64
__stdcall
#endif
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	return Run();
}
