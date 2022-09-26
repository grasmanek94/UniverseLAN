#include "Tracer.hxx"

#include "Stacker.hxx"

#include <intrin.h>
#include <Windows.h>

#include <atomic>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <mutex>
#include <string>
#include <syncstream>

namespace universelan::tracer {
	namespace fs = std::filesystem;

	class Tracer
	{
	public:
		friend class Trace;

	private:
		Tracer(const char* const log_directory);
		~Tracer();

		void Enter(const char* const func, const void* const return_address);
		void Exit(const char* const func, const void* const return_address);

	public:
		static Tracer* GetInstance();
	};

	namespace {
		class UnhandledExceptionCallback : public IUnhandledExceptionCallback
		{
		public:
			virtual void UnhandledExceptionOccurred(bool unknown_exception, const std::string exception_type, const std::string& exception_message, bool error_occured_during_stack_walk, const CallStackEntries& call_stack) override;
			virtual ~UnhandledExceptionCallback() {}
		};

		std::atomic_bool tracing_enabled;
		std::atomic_bool unhandled_exception_logging;

		UnhandledExceptionCallback tracer_callstack_handler{};
		fs::path trace_log_directory;
		Tracer* tracer{ nullptr };
		std::ofstream global_trace_file;

		void LogUnhandledExceptionOccurred(std::ofstream& file, DWORD thread_id, bool unknown_exception, const std::string exception_type, const std::string& exception_message, bool error_occured_during_stack_walk, const CallStackEntries& call_stack) {
			if (!file) {
				return;
			}
		
			std::osyncstream sync_stream{ file };

			sync_stream 
				<< "\n\n[EXCEPTION]\n"
				<< '[' << std::format("{:08x}", (size_t)thread_id) << "]\n\n";

			if (unknown_exception) {
				sync_stream
					<< "\tType: Unknown exception\n"
					<< "\tMessage: \n";
			}
			else {
				sync_stream
					<< "\tType: " << exception_type << "\n"
					<< "\tMessage: " << exception_message << "\n";
			}

			if (error_occured_during_stack_walk) {
				sync_stream
					<< "\tCallstack might be unreliable (error occurred during stack walk)\n";
			}
			else {
				sync_stream
					<< "\tCallstack should be reliable\n";
			}

			sync_stream
				<< "\t[BACKTRACE]\n";

			size_t counter = 0;

			for (const auto& call_entry : call_stack) {
				++counter;

				sync_stream
					<< "\t\t#" << counter << ' ' 
					<< std::format("{:08x}", (size_t)call_entry.offset) << ' '
					<< call_entry.function << " in "
					<< call_entry.module_name << ' '
					<< call_entry.file.path << " (" << call_entry.file.line_number << ")\n";
			}
		}

		class ThreadTracer {
		private:
			std::ofstream log_file;

		public:
			size_t depth;
			DWORD thread_id;

			ThreadTracer()
				: log_file{}, depth{ 0 }, thread_id{ 0 }
			{
				// Don't run expensive operations on every thread creation unneccessarily
				// Just run it when we really want to do logging, so do init in GetLogFile
			}

			std::ofstream& GetLogFile() {
				if (thread_id == 0) {
					thread_id = GetCurrentThreadId();
					std::string filename = std::format("{:08x}", thread_id);
					std::string path{ (trace_log_directory / (filename + ".trace")).string() };

					log_file = std::ofstream{ path, std::ios::app | std::ios::out };
					if (log_file) {
						log_file << "\n\n\n+";
					}
					else {
						std::osyncstream sync_stream(std::cerr);
						sync_stream << "Error opening tracer for thread " << filename << " for write: " << path << std::endl;
					}
				}

				return log_file;
			}

			~ThreadTracer() {
				if (log_file) {
					log_file << "-\n\n\n";
				}
			}
		};

		static thread_local ThreadTracer thread_tracer{};

		void UnhandledExceptionCallback::UnhandledExceptionOccurred(bool unknown_exception, const std::string exception_type, const std::string& exception_message, bool error_occured_during_stack_walk, const CallStackEntries& call_stack) {
			LogUnhandledExceptionOccurred(thread_tracer.GetLogFile(), thread_tracer.thread_id, unknown_exception, exception_type, exception_message, error_occured_during_stack_walk, call_stack);
			LogUnhandledExceptionOccurred(global_trace_file, thread_tracer.thread_id, unknown_exception, exception_type, exception_message, error_occured_during_stack_walk, call_stack);
		}
	}

	void Trace::SetUnhandledExceptionLogging(bool enabled) {
		unhandled_exception_logging = enabled;

		Stacker::GetInstance()
			->SetUnhandledExceptionCallback(
				unhandled_exception_logging ? 
				&tracer_callstack_handler :
				nullptr
			);
	}

	void Trace::SetTracingEnabled(bool enabled) {
		tracing_enabled = enabled;
	}

	bool Trace::InitTracing(const char* const log_directory, bool in_unhandled_exception_logging, bool in_tracing_enabled) {
		if (tracer != nullptr) {
			return false;
		}

		unhandled_exception_logging = in_unhandled_exception_logging;
		tracing_enabled = in_tracing_enabled;
		tracer = new Tracer(log_directory);
		return true;
	}

	Trace::Trace(const char* const func) :
		enabled{ tracing_enabled}, tracer_ptr{ Tracer::GetInstance() },
		func{ func }, return_address{ nullptr } {
		if (!enabled) {
			return;
		}

		return_address = _ReturnAddress();
		if (tracer_ptr) {
			tracer_ptr->Enter(func, return_address);
		}
	}

	Trace::~Trace() {
		if (!enabled) {
			return;
		}

		if (tracer_ptr) {
			tracer_ptr->Exit(func, return_address);
		}
	}

	Tracer::Tracer(const char* const log_directory) {
		auto t = std::time(nullptr);

#pragma warning( push )
#pragma warning( disable : 4996 )
		auto tm = *std::localtime(&t);
#pragma warning( pop )

		std::ostringstream path;

		path << std::put_time(&tm, "%Y-%m-%d_%H-%M-%S") << "/";

		trace_log_directory = fs::path(log_directory) / path.str();

		if (!fs::create_directories(trace_log_directory)) {
			std::cerr << "Failed to create tracing directory: " << trace_log_directory << std::endl;
			return;
		}

		global_trace_file = std::ofstream{ (trace_log_directory / "all.trace").string(), std::ios::trunc | std::ios::out };
		if (!global_trace_file) {
			std::cerr << "Error opening for write: " << (trace_log_directory / "all.trace") << std::endl;
			return;
		}

		if (unhandled_exception_logging) {
			Stacker::GetInstance()->SetUnhandledExceptionCallback(&tracer_callstack_handler);
		}
	}

	Tracer::~Tracer() {
	}

	void Tracer::Enter(const char* const func, const void* const return_address) {
		auto& log_file = thread_tracer.GetLogFile();
		if (log_file) {
			log_file << std::string(thread_tracer.depth, ' ') << '+' << func << "@" << std::hex << ((size_t)return_address) << '\n';
		}
		++thread_tracer.depth;

		if (global_trace_file) {
			std::osyncstream sync_stream(global_trace_file);
			sync_stream << '[' << thread_tracer.thread_id << "] " << '+' << func << "@" << std::hex << ((size_t)return_address) << '\n';
		}
	}

	void Tracer::Exit(const char* const func, const void* const return_address) {
		--thread_tracer.depth;
		auto& log_file = thread_tracer.GetLogFile();

		if (log_file) {
			log_file << std::string(thread_tracer.depth, ' ') << '-' << func << "@" << std::hex << ((size_t)return_address) << '\n';
		}

		if (global_trace_file) {
			std::osyncstream sync_stream(global_trace_file);
			sync_stream << '[' << thread_tracer.thread_id << "] " << '-' << func << "@" << std::hex << ((size_t)return_address) << '\n';
		}
	}

	Tracer* Tracer::GetInstance() {
		return tracer;
	}
}
