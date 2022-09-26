#include "Minidump.hxx"

#include <tchar.h>
#include <windows.h>
#include <dbghelp.h>
#include <intrin.h>

namespace universelan::tracer {
	// The following code gets exception pointers using a workaround found in CRT code.
	void GetExceptionPointers(DWORD dwExceptionCode,
		EXCEPTION_POINTERS** ppExceptionPointers)
	{
		// The following code was taken from VC++ 8.0 CRT (invarg.c: line 104)

		EXCEPTION_RECORD ExceptionRecord;
		CONTEXT ContextRecord;
		memset(&ContextRecord, 0, sizeof(CONTEXT));

#ifdef _X86_

		__asm {
			mov dword ptr[ContextRecord.Eax], eax
			mov dword ptr[ContextRecord.Ecx], ecx
			mov dword ptr[ContextRecord.Edx], edx
			mov dword ptr[ContextRecord.Ebx], ebx
			mov dword ptr[ContextRecord.Esi], esi
			mov dword ptr[ContextRecord.Edi], edi
			mov word ptr[ContextRecord.SegSs], ss
			mov word ptr[ContextRecord.SegCs], cs
			mov word ptr[ContextRecord.SegDs], ds
			mov word ptr[ContextRecord.SegEs], es
			mov word ptr[ContextRecord.SegFs], fs
			mov word ptr[ContextRecord.SegGs], gs
			pushfd
			pop[ContextRecord.EFlags]
		}

		ContextRecord.ContextFlags = CONTEXT_CONTROL;
#pragma warning(push)
#pragma warning(disable:4311)
		ContextRecord.Eip = (ULONG)_ReturnAddress();
		ContextRecord.Esp = (ULONG)_AddressOfReturnAddress();
#pragma warning(pop)
		ContextRecord.Ebp = *((ULONG*)_AddressOfReturnAddress() - 1);


#elif defined (_IA64_) || defined (_AMD64_)

		/* Need to fill up the Context in IA64 and AMD64. */
		RtlCaptureContext(&ContextRecord);

#else  /* defined (_IA64_) || defined (_AMD64_) */

		ZeroMemory(&ContextRecord, sizeof(ContextRecord));

#endif  /* defined (_IA64_) || defined (_AMD64_) */

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

	// This method creates minidump of the process
	void CreateMiniDump(const char* filename, int verbosity)
	{	
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
	}
}