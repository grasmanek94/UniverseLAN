#include "Stacker.hxx"

#include <windows.h>

#include <atomic>
#include <future>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include <detours.h>
#include <StackWalker.h>

#define DETERMINE_EXCEPTION_TYPE(T) catch(const T& _Xe) { data.exception_type = #T; data.exception_message = _Xe.what(); unknown_exception = false; }

namespace universelan::tracer {
	namespace {
		const size_t max_call_stack_depth = 128;

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

					//if (!strncmp("ucrtbase", entry.moduleName, strlen("ucrtbase")) ||
					//	!strcmp("ntdll", entry.moduleName) ||
					//	!strcmp("KERNELBASE", entry.moduleName) ||
					//	!strncmp("VCRUNTIME", entry.moduleName, strlen("VCRUNTIME")) ||
					//	!strcmp("KERNEL32", entry.moduleName) ||
					//	!strcmp("StackWalker::ShowCallstack", entry.name) ||
					//	!strcmp("UnhandledExceptionCallback", entry.name)
					//	) {
					//	return;
					//}

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

		void UnhandledExceptionCallback() {
			IUnhandledExceptionCallback* cb = callback.load();

			if (cb == nullptr) {
				return;
			}

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
			catch (...)
			{
				data.exception_type = "Unknown";
				data.exception_message = "";
			}

			MyStackWalker sw(&data);

			bool error_occurred = !sw.ShowCallstack();

			cb->UnhandledExceptionOccurred(unknown_exception, data.exception_type, data.exception_message, error_occurred, data.call_stack);
		}

		void(__cdecl* Real_terminate)(void) = terminate;

		void __cdecl HOOK_terminate() throw() {
			UnhandledExceptionCallback();
			Real_terminate();
		}
	}

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
		if (DetourIsHelperProcess()) {
			return true;
		}

		DetourRestoreAfterWith();
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)Real_terminate, HOOK_terminate);

		return (DetourTransactionCommit() == NO_ERROR);
	}

	void Stacker::SetUnhandledExceptionCallback(IUnhandledExceptionCallback* target) {
		callback.store(target);
	}
}