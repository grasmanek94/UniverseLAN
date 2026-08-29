#include "MiniDump.hxx"

#include "ReturnAddress.hxx"

#ifdef _WIN32
#include <tchar.h>
#include <windows.h>
#include <dbghelp.h>
#endif

namespace universelan::tracer {
#ifdef _WIN32
	// The following code gets exception pointers using a workaround found in CRT code.
	void GetExceptionPointers(DWORD dwExceptionCode,
		EXCEPTION_POINTERS** ppExceptionPointers)
	{
		// The following code was taken from VC++ 8.0 CRT (invarg.c: line 104)

		EXCEPTION_RECORD ExceptionRecord;
		CONTEXT ContextRecord;
		memset(&ContextRecord, 0, sizeof(CONTEXT));

		/* Need to fill up the Context in IA64 and AMD64. */
		RtlCaptureContext(&ContextRecord);

		ZeroMemory(&ExceptionRecord, sizeof(EXCEPTION_RECORD));

		ExceptionRecord.ExceptionCode = dwExceptionCode;
		ExceptionRecord.ExceptionAddress = _ReturnAddress();

		///

		EXCEPTION_RECORD* pExceptionRecord = new EXCEPTION_RECORD;
		memcpy(pExceptionRecord, &ExceptionRecord, sizeof(EXCEPTION_RECORD));
		CONTEXT* pContextRecord = new CONTEXT;
		memcpy(pContextRecord, &ContextRecord, sizeof(CONTEXT));

		*ppExceptionPointers = new EXCEPTION_POINTERS;
		(*ppExceptionPointers)->ExceptionRecord = pExceptionRecord;
		(*ppExceptionPointers)->ContextRecord = pContextRecord;
	}
#endif

	// This method creates minidump of the process
	void CreateMiniDump(const char* filename, int verbosity)
	{	
#ifdef _WIN32
		// Retrieve exception information
		EXCEPTION_POINTERS* pExcPtrs = NULL;
		GetExceptionPointers(0, &pExcPtrs);

		HMODULE hDbgHelp = NULL;
		HANDLE hFile = NULL;
		MINIDUMP_EXCEPTION_INFORMATION mei;
		MINIDUMP_CALLBACK_INFORMATION mci;

		// Load dbghelp.dll
		hDbgHelp = LoadLibrary(_T("dbghelp.dll"));
		if (hDbgHelp == NULL)
		{
			// Error - couldn't load dbghelp.dll
			return;
		}

		// Create the minidump file
		hFile = CreateFile(
			_T(filename),
			GENERIC_WRITE,
			0,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (hFile == INVALID_HANDLE_VALUE)
		{
			// Couldn't create file
			return;
		}

		// Write minidump to the file
		mei.ThreadId = GetCurrentThreadId();
		mei.ExceptionPointers = pExcPtrs;
		mei.ClientPointers = FALSE;
		mci.CallbackRoutine = NULL;
		mci.CallbackParam = NULL;

		typedef BOOL(WINAPI* LPMINIDUMPWRITEDUMP)(
			HANDLE hProcess,
			DWORD ProcessId,
			HANDLE hFile,
			MINIDUMP_TYPE DumpType,
			CONST PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam,
			CONST PMINIDUMP_USER_STREAM_INFORMATION UserEncoderParam,
			CONST PMINIDUMP_CALLBACK_INFORMATION CallbackParam);

		LPMINIDUMPWRITEDUMP pfnMiniDumpWriteDump =
			(LPMINIDUMPWRITEDUMP)GetProcAddress(hDbgHelp, "MiniDumpWriteDump");
		if (!pfnMiniDumpWriteDump)
		{
			// Bad MiniDumpWriteDump function
			return;
		}

		HANDLE hProcess = GetCurrentProcess();
		DWORD dwProcessId = GetCurrentProcessId();


		MINIDUMP_TYPE Flags{ MiniDumpNormal };

		switch (verbosity) {
		case 0:
			Flags = MiniDumpNormal;
			break;

		case 1:
			Flags = (MINIDUMP_TYPE)(
				MiniDumpWithFullMemory |
				MiniDumpWithFullMemoryInfo |
				MiniDumpWithHandleData |
				MiniDumpWithUnloadedModules |
				MiniDumpWithThreadInfo);
			break;

		default:
			Flags = (MINIDUMP_TYPE)(
				MiniDumpWithDataSegs |
				MiniDumpWithFullMemory |
				MiniDumpWithHandleData |
				MiniDumpWithUnloadedModules |
				MiniDumpWithProcessThreadData |
				MiniDumpWithPrivateReadWriteMemory |
				MiniDumpWithFullMemoryInfo |
				MiniDumpWithThreadInfo |
				MiniDumpWithCodeSegs |
				MiniDumpWithFullAuxiliaryState |
				MiniDumpWithPrivateWriteCopyMemory |
				MiniDumpIgnoreInaccessibleMemory |
				MiniDumpWithTokenInformation |
				MiniDumpWithModuleHeaders |
				MiniDumpWithAvxXStateContext |
				MiniDumpWithIptTrace);
			break;
		};

		BOOL bWriteDump = pfnMiniDumpWriteDump(hProcess, dwProcessId, hFile, Flags, &mei, NULL, &mci);

		if (!bWriteDump)
		{
			// Error writing dump.
			return;
		}

		// Close file
		CloseHandle(hFile);

		// Unload dbghelp.dll
		FreeLibrary(hDbgHelp);
#endif
	}
}
