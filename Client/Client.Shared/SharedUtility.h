#pragma once

#include <assert.h>
#include <string>
#include <fstream>
#include <sstream>

#include "CriticalSection.h"

namespace SharedUtility
{
#ifdef WIN32
	BOOL WINAPI ReadProcessMemoryEx(_In_ HANDLE hProcess, _In_ LPCVOID lpBaseAddress, _Out_writes_bytes_to_(nSize, *lpNumberOfBytesRead) LPVOID lpBuffer, _In_ SIZE_T nSize, _Out_opt_ SIZE_T * lpNumberOfBytesRead);
	BOOL WINAPI InjectDllW(__in LPCWSTR lpcwszDll, __in DWORD dwProcessId);

	bool GetProcessIdFromProcessName(const wchar_t *pwszProcessName, DWORD * dwProcessId, DWORD dwExceptionProcId = 0xFFFFFFFF);
	bool IsProcessRunning(const wchar_t *pwszProcessName);
	bool KillProcess(const wchar_t *pwszProcessName);

	bool StripPath1(wchar_t *pwszString);
	wchar_t * StripPath2(wchar_t *pwszString);

	bool IsFileExists(const wchar_t *pwszFileName);
	const wchar_t * GetExecutablePath();

	void TemporaryLogFunction(char *pszFormat, ...);
#endif

	unsigned int HashRageString(const char *string);
	unsigned int HashString(const char *string);

	unsigned long GetTime();
	long long GetTime64();
}
