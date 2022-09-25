#include "Tracer.hxx"

#include <windows.h>
#include <stdio.h>
#include <eh.h>

#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <regex>

#include <detours.h>
#include <StackWalker.h>

using mutex_t = std::recursive_mutex;
using lock_t = std::lock_guard<mutex_t>;

Tracer::Tracer() {
	//SetUnhandledExceptionFilter();
}

mutex_t mtx;

static void MyStrCpy(char* szDest, size_t nMaxDestSize, const char* szSrc)
{
	if (nMaxDestSize <= 0)
		return;
	strncpy_s(szDest, nMaxDestSize, szSrc, _TRUNCATE);
	// INFO: _TRUNCATE will ensure that it is null-terminated;
	// but with older compilers (<1400) it uses "strncpy" and this does not!)
	szDest[nMaxDestSize - 1] = 0;
} // MyStrCpy


class MyStackWalker : public StackWalker
{
public:
	MyStackWalker() : StackWalker() {}
protected:
	virtual void OnOutput(LPCSTR szText) override {}

	virtual void OnCallstackEntry(CallstackEntryType eType, CallstackEntry& entry) override {
		CHAR   buffer[STACKWALK_MAX_NAMELEN];
		size_t maxLen = STACKWALK_MAX_NAMELEN;
#if _MSC_VER >= 1400
		maxLen = _TRUNCATE;
#endif
		if ((eType != lastEntry) && (entry.offset != 0))
		{
			if (entry.name[0] == 0)
				MyStrCpy(entry.name, STACKWALK_MAX_NAMELEN, "(function-name not available)");
			if (entry.undName[0] != 0)
				MyStrCpy(entry.name, STACKWALK_MAX_NAMELEN, entry.undName);
			if (entry.undFullName[0] != 0)
				MyStrCpy(entry.name, STACKWALK_MAX_NAMELEN, entry.undFullName);

			if (!strncmp("ucrtbase", entry.moduleName, strlen("ucrtbase")) ||
				!strcmp("ntdll", entry.moduleName) ||
				!strcmp("KERNELBASE", entry.moduleName) ||
				!strncmp("VCRUNTIME", entry.moduleName, strlen("VCRUNTIME")) ||
				!strcmp("KERNEL32", entry.moduleName) ||
				!strcmp("StackWalker::ShowCallstack", entry.name) ||
				!strcmp("TTH_CXX_UEH", entry.name)
				) {
				return;
			}

			if (entry.lineFileName[0] == 0)
			{
				MyStrCpy(entry.lineFileName, STACKWALK_MAX_NAMELEN, "(filename not available)");
				if (entry.moduleName[0] == 0)
					MyStrCpy(entry.moduleName, STACKWALK_MAX_NAMELEN, "(module-name not available)");
				_snprintf_s(buffer, maxLen, "%p (%s): %s: %s\n", (LPVOID)entry.offset, entry.moduleName,
					entry.lineFileName, entry.name);
			}
			else
				_snprintf_s(buffer, maxLen, "%s (%d): %s\n", entry.lineFileName, entry.lineNumber,
					entry.name);
			buffer[STACKWALK_MAX_NAMELEN - 1] = 0;
			std::cout << buffer;

			/*if (entry.moduleName[0] == 0) {
				std::cout << "?";
			}
			else {
				std::cout << entry.moduleName;
			}

			std::cout << "::";

			if (entry.undFullName[0] != 0) {
				std::cout << entry.undFullName;
			}
			else if (entry.undName[0] != 0) {
				std::cout << entry.undName;
			}
			else if (entry.name[0] != 0) {
				std::cout << entry.name;
			}
			else {
				std::cout << "?";
			}
			std::cout << "\n";*/


			/*if (entry.lineFileName[0] == 0)
			{
				MyStrCpy(entry.lineFileName, STACKWALK_MAX_NAMELEN, "(filename not available)");
				if (entry.moduleName[0] == 0)
					MyStrCpy(entry.moduleName, STACKWALK_MAX_NAMELEN, "(module-name not available)");
				_snprintf_s(buffer, maxLen, "%p (%s): %s: %s\n", (LPVOID)entry.offset, entry.moduleName,
					entry.lineFileName, entry.name);
			}
			else
				_snprintf_s(buffer, maxLen, "%s (%d): %s\n", entry.lineFileName, entry.lineNumber,
					entry.name);
			buffer[STACKWALK_MAX_NAMELEN - 1] = 0;
			OnOutput(buffer);*/
		}
	}
};

#define HANDLE_TTH_CXX_UEH(T) catch(const T& _Xe) { std::cout << #T << " " << _Xe.what() << "\n"; }

void TTH_CXX_UEH() {
	auto const ex = std::current_exception();
	{
		lock_t lock{ mtx };
		std::cout << "[" << std::this_thread::get_id() << "] " << __FUNCTION__ << std::endl;

		try
		{
			if (ex) { std::rethrow_exception(ex); }
		}

		HANDLE_TTH_CXX_UEH(std::bad_array_new_length)
			HANDLE_TTH_CXX_UEH(std::bad_cast)
			HANDLE_TTH_CXX_UEH(std::bad_exception)
			HANDLE_TTH_CXX_UEH(std::bad_function_call)
			HANDLE_TTH_CXX_UEH(std::bad_typeid)
			HANDLE_TTH_CXX_UEH(std::bad_weak_ptr)
			HANDLE_TTH_CXX_UEH(std::domain_error)
			HANDLE_TTH_CXX_UEH(std::future_error)
			HANDLE_TTH_CXX_UEH(std::invalid_argument)
			HANDLE_TTH_CXX_UEH(std::length_error)
			HANDLE_TTH_CXX_UEH(std::out_of_range)
			HANDLE_TTH_CXX_UEH(std::overflow_error)
			HANDLE_TTH_CXX_UEH(std::underflow_error)
			HANDLE_TTH_CXX_UEH(std::range_error)
			HANDLE_TTH_CXX_UEH(std::regex_error)
			HANDLE_TTH_CXX_UEH(std::ios_base::failure)
			HANDLE_TTH_CXX_UEH(std::system_error)
			HANDLE_TTH_CXX_UEH(std::runtime_error)
			HANDLE_TTH_CXX_UEH(std::logic_error)
			HANDLE_TTH_CXX_UEH(std::bad_alloc)
			HANDLE_TTH_CXX_UEH(std::exception)
			catch (...)
		{
			std::cout << "Unknown exception type/message\n";
		}

		MyStackWalker sw;

		if (!sw.ShowCallstack()) {
			std::cout << "ShowCallstack FAIL" << std::endl;
		}
	}
}

static void(__cdecl* Real_terminate)(void) = terminate;
void __cdecl HOOK_terminate() throw() {
	TTH_CXX_UEH();
	Real_terminate();
}

void doStupidshit(int a) {
	{
		lock_t lock{ mtx };
		std::cout << "[" << std::this_thread::get_id() << "] " << __FUNCTION__ << std::endl;
	}

	//set_terminate(TTH_CXX_UEH);

	try {
		throw std::exception();
	}
	catch (...) {
		{
			lock_t lock{ mtx };
			std::cout << "[" << std::this_thread::get_id() << "] catched" << std::endl;
		}
	}

	try {
		throw std::exception();
	}
	catch (...) {
		{
			lock_t lock{ mtx };
			std::cout << "[" << std::this_thread::get_id() << "] catched" << std::endl;
		}
	}

	if (a >= 5) {
		{
			lock_t lock{ mtx };
			std::cout << "[" << std::this_thread::get_id() << "] throw" << std::endl;
		}
		throw std::runtime_error("uu");
	}
}

int main() {
	{
		lock_t lock{ mtx };
		std::cout << "[" << std::this_thread::get_id() << "] " << __FUNCTION__ << std::endl;
	}

	if (DetourIsHelperProcess()) {
		return TRUE;
	}

	DetourRestoreAfterWith();
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)Real_terminate, HOOK_terminate);
	LONG error = DetourTransactionCommit();

	if (error == NO_ERROR) {
		printf("Detoured terminate\n");
	}
	else {
		printf("Error detouring terminate: %ld\n", error);
	}

	std::jthread t1(doStupidshit, 1);
	std::jthread t2(doStupidshit, 10);
	std::jthread t3(doStupidshit, 2);
	std::jthread t4(doStupidshit, 11);
	doStupidshit(1);
	doStupidshit(10);

	return 0;
}
