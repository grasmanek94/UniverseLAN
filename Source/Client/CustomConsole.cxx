#include "CustomConsole.hxx"

#include <Tracer.hxx>
#include <Version.hxx>

#ifdef _WIN32
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#endif

#include <format>
#include <fstream>
#include <iostream>
#include <string>

namespace universelan::client {
#ifdef _WIN32
	static WNDPROC ConsoleWndProc = NULL;
	static HWND	ConsoleWndHandle = NULL;
#endif

	void BindStdHandlesToConsole()
	{
		tracer::Trace trace { nullptr, __FUNCTION__ };

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
		tracer::Trace trace { nullptr, __FUNCTION__ };

		static bool CustomConsoleEnabled = false;

		if (CustomConsoleEnabled)
		{
			trace.write_all("Custom console already enabled, aborting");
			return;
		}

		CustomConsoleEnabled = true;

#ifdef _WIN32
		// allocate a console for this app
		AllocConsole();

		ConsoleWndHandle = GetConsoleWindow();
		ConsoleWndProc = (WNDPROC)GetWindowLongPtrA(ConsoleWndHandle, -4);

		BindStdHandlesToConsole();

		SetConsoleTitleA(std::format("UniverseLAN Client - Build: {}", universelan::Version_Number).c_str());
#endif
	}
}