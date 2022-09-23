#ifdef WIN32

#define IErrorManager void
#include <GalaxyFactory.h>

#else

#include <GalaxyApi.h>

#endif

#include <windows.h>

#include <chrono>
#include <thread>

using namespace galaxy::api;
using namespace std::chrono;

int Run()
{
#ifdef WIN32
	auto galaxy = GalaxyFactory::GetInstance();

	galaxy->Init("","");

	while (true)
	{
		galaxy->ProcessData();
		std::this_thread::sleep_for(milliseconds(5));
	}
#else
	InitOptions options("", "");

	Init(options);

	while (true)
	{
		ProcessData();
		std::this_thread::sleep_for(milliseconds(5));
	}
#endif
	return 0;
}

int 
#if WIN32
__stdcall 
#endif
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	return Run();
}
