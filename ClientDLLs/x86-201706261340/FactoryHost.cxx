#include <GalaxyFactory.h>

#include <windows.h>

#include <chrono>
#include <thread>

using namespace galaxy::api;
using namespace std::chrono;

int Run()
{
	auto galaxy = GalaxyFactory::GetInstance();

	galaxy->Init("","");

	while (true)
	{
		galaxy->ProcessData();
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
