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

class MyStackWalker : public StackWalker
{
public:
	MyStackWalker() : StackWalker() {}
protected:
	virtual void OnOutput(LPCSTR szText) override {}

	virtual void OnCallstackEntry(CallstackEntryType eType, CallstackEntry& entry) override {
		if ((eType != lastEntry) && (entry.offset != 0))
		{
			if (!strcmp("ucrtbased", entry.moduleName) ||
				!strcmp("ntdll", entry.moduleName) ||
				!strcmp("KERNELBASE", entry.moduleName) ||
				!strcmp("VCRUNTIME140_1D", entry.moduleName) ||
				!strcmp("VCRUNTIME140D", entry.moduleName) ||
				!strcmp("KERNEL32", entry.moduleName) ||
				!strcmp("HOOK_CxxThrowException", entry.name) ||
				!strcmp("StackWalker::ShowCallstack", entry.name) ||
				!strcmp("WindowsExceptionHandler", entry.name) ||
				!strcmp("invoke_main", entry.name) ||
				!strcmp("__scrt_common_main_seh", entry.name) ||
				!strcmp("__scrt_common_main", entry.name) ||
				!strcmp("mainCRTStartup", entry.name) ||
				!strcmp("__scrt_unhandled_exception_filter", entry.name) ||
				!strcmp("TTH_CXX_UEH", entry.name)
				) {
				return;
			}

			if (entry.moduleName[0] == 0) {
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
			std::cout << "\n";


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

extern "C" void __stdcall _CxxThrowException(void* pExceptionObject, _ThrowInfo * pThrowInfo);
static void(WINAPI* Real_CxxThrowException)(void* pExceptionObject, _ThrowInfo* pThrowInfo) = _CxxThrowException;

extern "C" void WINAPI HOOK_CxxThrowException(void* pExceptionObject, _ThrowInfo * pThrowInfo)
{
	/* {
		lock_t lock{ mtx };
		std::cout << "[" << std::this_thread::get_id() << "] " << __FUNCTION__ << std::endl;
		MyStackWalker sw;
		if (!sw.ShowCallstack()) {
			std::cout << "ShowCallstack FAIL" << std::endl;
		}
	}*/

	return Real_CxxThrowException(pExceptionObject, pThrowInfo);
}

LPTOP_LEVEL_EXCEPTION_FILTER g_prevlpTopLevelExceptionFilter;

LONG WINAPI WindowsExceptionHandler(LPEXCEPTION_POINTERS ep) {
	{
		lock_t lock{ mtx };
		std::cout << "[" << std::this_thread::get_id() << "] " << __FUNCTION__ << std::endl;
		MyStackWalker sw;
		if (!sw.ShowCallstack()) {
			std::cout << "ShowCallstack FAIL" << std::endl;
		}
	}

	PEXCEPTION_RECORD ExceptionRecord = ep->ExceptionRecord;

	//printf("%s: %x at %p", __FUNCTION__,
	//	ExceptionRecord->ExceptionCode, ExceptionRecord->ExceptionAddress);

	//if (ULONG NumberParameters = ExceptionRecord->NumberParameters)
	//{
	//	printf(" { ");
	//	PULONG_PTR ExceptionInformation = ExceptionRecord->ExceptionInformation;
	//	do
	//	{
	//		printf(" %p", (void*)*ExceptionInformation++);
	//	} while (--NumberParameters);
	//	printf(" } ");
	//}
	//
	//printf("\n");

	if (ExceptionRecord->ExceptionCode == 0xE06D7363) {
		return g_prevlpTopLevelExceptionFilter(ep);
	}


	std::this_thread::sleep_for(std::chrono::milliseconds(50000));

	return EXCEPTION_EXECUTE_HANDLER;
}

#define HANDLE_TTH_CXX_UEH(T) catch(const T& _Xe) { std::cout << #T << " " << _Xe.what() << "\n"; }

void TTH_CXX_UEH() {
	{
		lock_t lock{ mtx };
		std::cout << "[" << std::this_thread::get_id() << "] " << __FUNCTION__ << std::endl;
		MyStackWalker sw;

		if (!sw.ShowCallstack()) {
			std::cout << "ShowCallstack FAIL" << std::endl;
		}

		auto const ex = std::current_exception();

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
			if (ex) { std::rethrow_exception(ex); }
		}
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(50000));
	exit(-1);
}

void SEFunc() {
	//int x, y = 0;
	//x = 5 / y;
}

class SE_Exception
{
private:
	unsigned int nSE;
public:
	SE_Exception() {}
	SE_Exception(unsigned int n) : nSE(n) {}
	~SE_Exception() {}
	unsigned int getSeNumber() { return nSE; }
};

void trans_func(unsigned int u, EXCEPTION_POINTERS* pExp)
{
	{
		lock_t lock{ mtx };
		std::cout << "[" << std::this_thread::get_id() << "] " << __FUNCTION__ << std::endl;
	}

	throw SE_Exception();
}

void doStupidshit(int a) {
	{
		lock_t lock{ mtx };
		std::cout << "[" << std::this_thread::get_id() << "] " << __FUNCTION__ << std::endl;
	}

	set_terminate(TTH_CXX_UEH);

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

	if (a < 5) {
		{
			lock_t lock{ mtx };
			std::cout << "[" << std::this_thread::get_id() << "] SEFunc" << std::endl;
		}
		SEFunc();
	}
	else {
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

	//if (DetourIsHelperProcess()) {
	//	return TRUE;
	//}

	//g_prevlpTopLevelExceptionFilter =
	//	SetUnhandledExceptionFilter(WindowsExceptionHandler);

	// needs to be performed for each thread
	set_terminate(TTH_CXX_UEH);

	_set_se_translator(trans_func);

	//DetourRestoreAfterWith();
	//DetourTransactionBegin();
	//DetourUpdateThread(GetCurrentThread());
	//DetourAttach(&(PVOID&)Real_CxxThrowException, HOOK_CxxThrowException);
	//LONG error = DetourTransactionCommit();
	//
	//if (error == NO_ERROR) {
	//	printf("Detoured _CxxThrowException\n");
	//}
	//else {
	//	printf("Error detouring _CxxThrowException: %ld\n", error);
	//}

	std::thread t1(doStupidshit, 1);
	std::thread t2(doStupidshit, 10);
	std::thread t3(doStupidshit, 2);
	std::thread t4(doStupidshit, 11);
	doStupidshit(1);
	doStupidshit(10);

	t1.join();
	t2.join();
	t3.join();
	t4.join();

	return 0;
}
