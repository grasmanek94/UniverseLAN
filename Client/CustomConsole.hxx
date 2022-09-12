#pragma once
#include <Windows.h>

void EnableCustomConsole(void);
extern WNDPROC ConsoleWndProc;
extern HWND ConsoleWndHandle;