#include <GalaxyApi.h>

#include <windows.h>

#include <chrono>
#include <thread>

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	galaxy::api::InitOptions options("","");

	galaxy::api::Init(options);

	while (true)
	{
		galaxy::api::ProcessData();
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	return 0;
}
