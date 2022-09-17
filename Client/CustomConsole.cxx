#include <Windows.h>
#include <io.h>
#include <fcntl.h>

#include <fstream>
#include <iostream>

#include "CustomConsole.hxx"

namespace universelan::client {
	static WNDPROC ConsoleWndProc = NULL;
	static HWND	ConsoleWndHandle = NULL;

	void BindStdHandlesToConsole()
	{
		FILE* fDummy;
		freopen_s(&fDummy, "CONIN$", "r", stdin);
		freopen_s(&fDummy, "CONOUT$", "w", stderr);
		freopen_s(&fDummy, "CONOUT$", "w", stdout);

		//Clear the error state for each of the C++ standard stream objects. We need to do this, as
		//attempts to access the standard streams before they refer to a valid target will cause the
		//iostream objects to enter an error state. In versions of Visual Studio after 2005, this seems
		//to always occur during startup regardless of whether anything has been read from or written to
		//the console or not.
		std::wcout.clear();
		std::cout.clear();
		std::wcerr.clear();
		std::cerr.clear();
		std::wcin.clear();
		std::cin.clear();
	}

	void EnableCustomConsole()
	{
		static bool CustomConsoleEnabled = false;

		if (CustomConsoleEnabled)
		{
			return;
		}

		CustomConsoleEnabled = true;

		// allocate a console for this app
		AllocConsole();

		ConsoleWndHandle = GetConsoleWindow();
		ConsoleWndProc = (WNDPROC)GetWindowLongPtrA(ConsoleWndHandle, -4);

		BindStdHandlesToConsole();

		SetConsoleTitleA("Universe LAN");
	}
}