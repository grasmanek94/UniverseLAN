#include <GalaxyFactory.h>

#include <chrono>
#include <thread>

using namespace galaxy::api;
using namespace std::chrono;

int main()
{
	auto galaxy = GalaxyFactory::GetInstance(
		//0, 0
	);

	galaxy->Init("","");

	while (true)
	{
		galaxy->ProcessData();
		std::this_thread::sleep_for(milliseconds(5));
	}

	return 0;
}

#ifdef _WIN32
#include <windows.h>

int 
#ifndef _WIN64
__stdcall 
#endif
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	return main();
}
#endif