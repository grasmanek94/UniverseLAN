#include "CustomConsole.hxx"

#include <Tracer.hxx>

#ifdef _WIN32
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#endif

#include <fstream>
#include <iostream>

namespace universelan::client {
	static WNDPROC ConsoleWndProc = NULL;
	static HWND	ConsoleWndHandle = NULL;

	void BindStdHandlesToConsole()
	{
		tracer::Trace trace{  };

#ifdef _WIN32
		FILE* fDummy;
		freopen_s(&fDummy, "CONIN$", "r", stdin);
		freopen_s(&fDummy, "CONOUT$", "w", stderr);
		freopen_s(&fDummy, "CONOUT$", "w", stdout);
#endif

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
		tracer::Trace trace{  };

		static bool CustomConsoleEnabled = false;

		if (CustomConsoleEnabled)
		{
			return;
		}

		CustomConsoleEnabled = true;

#ifdef _WIN32
		// allocate a console for this app
		AllocConsole();

		ConsoleWndHandle = GetConsoleWindow();
		ConsoleWndProc = (WNDPROC)GetWindowLongPtrA(ConsoleWndHandle, -4);

		BindStdHandlesToConsole();

		SetConsoleTitleA("UniverseLAN");
#endif
	}
}