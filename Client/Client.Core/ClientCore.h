#pragma once

#include <windows.h>

class ClientCore
{
private:
	static DWORD WINAPI Run();

public:
	static void Initialize();
	static void Shutdown();
};
