#include "Stacker.hxx"
#include "MiniDump.hxx"

#ifdef _WIN32
#include <tchar.h>
#include <windows.h>
#include <dbghelp.h>

#include <detours.h>
#include <StackWalker.h>
#endif

#include <atomic>
#include <filesystem>
#include <format>
#include <future>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#define DETERMINE_EXCEPTION_TYPE(T) catch(const T& _Xe) { data.exception_type = #T; data.exception_message = _Xe.what(); unknown_exception = false; }
#define DETERMINE_EXCEPTION_TYPE_VALUE_PTR(T) catch(const T* _Xe) { data.exception_type = #T"*"; data.exception_message = std::format("PTR:{:08x}", (size_t)_Xe); unknown_exception = false; }
#define DETERMINE_EXCEPTION_TYPE_VALUE(T) catch(const T& _Xe) { data.exception_type = #T; data.exception_message = std::to_string(_Xe); unknown_exception = false; }

namespace universelan::tracer {
	namespace fs = std::filesystem;
	extern fs::path trace_log_directory;

	bool create_minidump_on_unhandles_exception{false};
	int minidump_verbosity_level{0};

#ifdef _WIN32
	namespace {
		const size_t max_call_stack_depth{ 128 };
		std::atomic_size_t entered_counter{ 0 };

		struct UECData {
			bool call_is_nested = false;
			std::string exception_type = "Unknown";
			std::string exception_message = "";
			CallStackEntries call_stack{};
		};

		class MyStackWalker : public StackWalker
		{
		private:
			static void MyStrCpy(char* szDest, size_t nMaxDestSize, const char* szSrc)
			{
				if (nMaxDestSize <= 0)
					return;
				strncpy_s(szDest, nMaxDestSize, szSrc, _TRUNCATE);
				// INFO: _TRUNCATE will ensure that it is null-terminated;
				// but with older compilers (<1400) it uses "strncpy" and this does not!)
				szDest[nMaxDestSize - 1] = 0;
			} // MyStrCpy

			UECData* data;
		public:
			MyStackWalker(UECData* data) : StackWalker(), data{ data } {}
		protected:
			virtual void OnOutput(LPCSTR szText) override {}

			virtual void OnCallstackEntry(CallstackEntryType eType, CallstackEntry& entry) override {
				if ((eType != lastEntry) && (entry.offset != 0) && (data->call_stack.size() < max_call_stack_depth)) {
					if (entry.undName[0] != 0) {
						MyStrCpy(entry.name, STACKWALK_MAX_NAMELEN, entry.undName);
					}
					if (entry.undFullName[0] != 0) {
						MyStrCpy(entry.name, STACKWALK_MAX_NAMELEN, entry.undFullName);
					}

					if (!strncmp("ucrtbase", entry.moduleName, strlen("ucrtbase")) ||
						!strcmp("ntdll", entry.moduleName) ||
						!strcmp("KERNELBASE", entry.moduleName) ||
						!strncmp("VCRUNTIME", entry.moduleName, strlen("VCRUNTIME")) ||
						!strcmp("KERNEL32", entry.moduleName) ||
						!strcmp("StackWalker::ShowCallstack", entry.name) ||
						!strncmp("__scrt_", entry.name, strlen("__scrt_")) ||
						!strncmp("universelan::tracer::`anonymous namespace'::", entry.name, strlen("universelan::tracer::`anonymous namespace'::"))
						) {
						return;
					}

					data->call_stack.push_back(CallStackEntry{ (size_t)entry.offset, entry.moduleName, entry.name, CallEntryFile{entry.lineFileName, entry.lineNumber} });
				}
			}
		};

		struct ResetBool {
			bool* var;
			ResetBool(bool* var) : var{ var } {
				*var = true;
			}
			~ResetBool() {
				*var = false;
			}
		};

		std::atomic<IUnhandledExceptionCallback*> callback{ nullptr };

		void UnhandledExceptionCallback(IUnhandledExceptionCallback* cb) {
			const std::exception_ptr exception{ std::current_exception() };
			static thread_local UECData data{};
			if (data.call_is_nested) {
				// means the code below has thrown an exception too..
				return;
			}
			ResetBool rb{ &data.call_is_nested };
			data.call_stack.clear();

			bool unknown_exception = true;
			try
			{
				if (exception) {
					std::rethrow_exception(exception);
				}
			}
			DETERMINE_EXCEPTION_TYPE(std::bad_array_new_length)
			DETERMINE_EXCEPTION_TYPE(std::bad_cast)
			DETERMINE_EXCEPTION_TYPE(std::bad_exception)
			DETERMINE_EXCEPTION_TYPE(std::bad_function_call)
			DETERMINE_EXCEPTION_TYPE(std::bad_typeid)
			DETERMINE_EXCEPTION_TYPE(std::bad_weak_ptr)
			DETERMINE_EXCEPTION_TYPE(std::domain_error)
			DETERMINE_EXCEPTION_TYPE(std::future_error)
			DETERMINE_EXCEPTION_TYPE(std::invalid_argument)
			DETERMINE_EXCEPTION_TYPE(std::length_error)
			DETERMINE_EXCEPTION_TYPE(std::out_of_range)
			DETERMINE_EXCEPTION_TYPE(std::overflow_error)
			DETERMINE_EXCEPTION_TYPE(std::underflow_error)
			DETERMINE_EXCEPTION_TYPE(std::range_error)
			DETERMINE_EXCEPTION_TYPE(std::regex_error)
			DETERMINE_EXCEPTION_TYPE(std::ios_base::failure)
			DETERMINE_EXCEPTION_TYPE(std::system_error)
			DETERMINE_EXCEPTION_TYPE(std::runtime_error)
			DETERMINE_EXCEPTION_TYPE(std::logic_error)
			DETERMINE_EXCEPTION_TYPE(std::bad_alloc)
			DETERMINE_EXCEPTION_TYPE(std::exception)
			DETERMINE_EXCEPTION_TYPE_VALUE_PTR(unsigned int)
			DETERMINE_EXCEPTION_TYPE_VALUE_PTR(int)
			DETERMINE_EXCEPTION_TYPE_VALUE_PTR(unsigned long)
			DETERMINE_EXCEPTION_TYPE_VALUE_PTR(long)
			DETERMINE_EXCEPTION_TYPE_VALUE_PTR(unsigned long long)
			DETERMINE_EXCEPTION_TYPE_VALUE_PTR(long long)
			DETERMINE_EXCEPTION_TYPE_VALUE(unsigned char)
			DETERMINE_EXCEPTION_TYPE_VALUE(char)
			DETERMINE_EXCEPTION_TYPE_VALUE(unsigned int)
			DETERMINE_EXCEPTION_TYPE_VALUE(int)
			DETERMINE_EXCEPTION_TYPE_VALUE(unsigned long)
			DETERMINE_EXCEPTION_TYPE_VALUE(long)
			DETERMINE_EXCEPTION_TYPE_VALUE(unsigned long long)
			DETERMINE_EXCEPTION_TYPE_VALUE(long long)
			DETERMINE_EXCEPTION_TYPE_VALUE_PTR(void)
			catch (...)
			{
				data.exception_type = "Unknown";
				data.exception_message = "";
			}

			MyStackWalker sw(&data);

			bool error_occurred = !sw.ShowCallstack();

			cb->UnhandledExceptionOccurred(unknown_exception, data.exception_type, data.exception_message, error_occurred, data.call_stack);

			if (create_minidump_on_unhandles_exception) {
		
				// Write minidump file
				TCHAR szFileName[MAX_PATH];

				GetModuleFileName(NULL, szFileName, MAX_PATH);

				fs::path path = fs::absolute(trace_log_directory) / fs::path(szFileName).filename();
				CreateMiniDump(path.replace_extension("dmp").string().c_str(), minidump_verbosity_level);
			}
		}

		// void(__cdecl* Real_terminate)(void) = terminate;

		struct KeepCount {
			KeepCount() {
				entered_counter.fetch_add(1);
			}
			~KeepCount() {
				entered_counter.fetch_sub(1);
			}
		};

		// void __cdecl HOOK_terminate() throw() {
		// 	IUnhandledExceptionCallback* cb = callback.load();
		// 	if(cb != nullptr)
		// 	{
		// 		KeepCount keeper{};
		// 		UnhandledExceptionCallback(cb);
		// 	}
		// 
		// 	while (entered_counter.load()) {
		// 		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		// 	}
		// 
		// 	Real_terminate();
		// }

		LPTOP_LEVEL_EXCEPTION_FILTER filter{ nullptr };

		LONG WINAPI OurCrashHandler(EXCEPTION_POINTERS* ExceptionInfo)
		{
			IUnhandledExceptionCallback* cb = callback.load();
			if (cb != nullptr)
			{
				KeepCount keeper{};
				UnhandledExceptionCallback(cb);
			}

			while (entered_counter.load()) {
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}

			return filter != nullptr ? filter(ExceptionInfo) : EXCEPTION_CONTINUE_SEARCH;
		}

	}
#endif

	Stacker::Stacker() {
		if (!Init()) {
			std::cerr << "Stacker cannot detour 'terminate' function" << std::endl;
		}
	}

	Stacker::~Stacker() {}

	Stacker* Stacker::GetInstance() {
		static Stacker* stacker{ new Stacker() };
		return stacker;
	}

	bool Stacker::Init() {
#ifdef _WIN32
		filter = SetUnhandledExceptionFilter(OurCrashHandler);
		return true;
#else
		return false;
#endif

		// if (DetourIsHelperProcess()) {
		// 	return true;
		// }
		// 
		// DetourRestoreAfterWith();
		// DetourTransactionBegin();
		// DetourUpdateThread(GetCurrentThread());
		// DetourAttach(&(PVOID&)Real_terminate, HOOK_terminate);
		// 
		// return (DetourTransactionCommit() == NO_ERROR);
	}

	void Stacker::SetUnhandledExceptionCallback(IUnhandledExceptionCallback* target) {
#ifdef _WIN32
		callback.store(target);
#endif
	}
}
