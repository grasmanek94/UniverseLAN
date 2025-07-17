#include "Tracer.hxx"

#include "Stacker.hxx"

#ifdef _WIN32
#include <intrin.h>
#include <Windows.h>
#endif

#include <atomic>
#include <filesystem>
#include <format> // Requires GCC 13 (!) / VS 2019 16.09
#include <fstream>
#include <iostream>
#include <mutex>
#include <string>
#include <syncstream> // Requires GCC 11 (!) / VS 2019 16.10

namespace universelan::tracer {
	namespace fs = std::filesystem;

	class Tracer
	{
	public:
		static void Enter(const char* const func, const char* const extra, const void* const return_address);
		static void Exit(const char* const func, const char* const extra, const void* const return_address);
	};

	fs::path trace_log_directory;

	namespace {
		class UnhandledExceptionCallback : public IUnhandledExceptionCallback
		{
		public:
			virtual void UnhandledExceptionOccurred(bool unknown_exception, const std::string exception_type, const std::string& exception_message, bool error_occured_during_stack_walk, const CallStackEntries& call_stack) override;
			virtual ~UnhandledExceptionCallback() {}
		};

		bool tracing_initialized;
		std::atomic_bool tracing_enabled;
		std::atomic_bool unhandled_exception_logging;
		bool should_always_flush_tracing;
		bool trace_to_console;
		uint64_t enabled_tracing_flags;

		UnhandledExceptionCallback tracer_callstack_handler{};
		std::ofstream global_trace_file;

		void LogUnhandledExceptionOccurred(std::ofstream& file, uint64_t thread_id, bool unknown_exception, const std::string exception_type, const std::string& exception_message, bool error_occured_during_stack_walk, const CallStackEntries& call_stack) {
			if (!file) {
				return;
			}

			{
				std::osyncstream sync_stream{ file };

				sync_stream
					<< "[EXCEPTION]\n"
					<< '[' << std::format("{:08x}", (size_t)thread_id) << "]\n";

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

			file.flush();
		}

		class ThreadTracer {
		private:
			std::ofstream log_file;
			uint64_t thread_id;

		public:
			size_t depth;
			uint64_t GetCachedThreadID() {
				if (thread_id == 0) {
					GetLogFile();
				}

				return thread_id;
			}

			ThreadTracer()
				: log_file{}, depth{ 0 }, thread_id{ 0 }
			{
				// Don't run expensive operations on every thread creation unneccessarily
				// Just run it when we really want to do logging, so do init in GetLogFile
			}

			std::ofstream& GetLogFile() {
				if (thread_id == 0) {
#ifdef _WIN32
					thread_id = GetCurrentThreadId();
#else
					thread_id = (uint64_t)this;
#endif

					std::string filename = std::format("{:08x}", thread_id);
					std::string path{ (trace_log_directory / (filename + ".trace")).string() };

					log_file = std::ofstream{ path, std::ios::app | std::ios::out };
					if (log_file) {
						log_file << "+\n";
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
					log_file << "-\n";
					log_file.flush();
				}
			}
		};

		static thread_local ThreadTracer thread_tracer{};

		void UnhandledExceptionCallback::UnhandledExceptionOccurred(bool unknown_exception, const std::string exception_type, const std::string& exception_message, bool error_occured_during_stack_walk, const CallStackEntries& call_stack) {
			LogUnhandledExceptionOccurred(thread_tracer.GetLogFile(), thread_tracer.GetCachedThreadID(), unknown_exception, exception_type, exception_message, error_occured_during_stack_walk, call_stack);
			LogUnhandledExceptionOccurred(global_trace_file, thread_tracer.GetCachedThreadID(), unknown_exception, exception_type, exception_message, error_occured_during_stack_walk, call_stack);
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

	void Trace::SetLogToCout(bool enabled) {
		trace_to_console = enabled;
	}


	bool Trace::InitTracing(const char* const log_directory,
		bool in_unhandled_exception_logging, bool in_tracing_enabled,
		bool mindump_on_unhandled_exception, int in_minidump_verbosity_level,
		bool in_should_always_flush_tracing, uint64_t mask) {
		if (tracing_initialized) {
			return false;
		}

		auto t = std::time(nullptr);

#pragma warning( push )
#pragma warning( disable : 4996 )
		auto tm = *std::localtime(&t);
#pragma warning( pop )

		std::ostringstream path;

		path << std::put_time(&tm, "%Y-%m-%d_%H-%M-%S");

		trace_log_directory = fs::path(log_directory) / path.str();

		if (!fs::create_directories(trace_log_directory)) {
			std::cerr << "Failed to create tracing directory: " << trace_log_directory << std::endl;
			return false;
		}

		global_trace_file = std::ofstream{ (trace_log_directory / "all.trace").string(), std::ios::trunc | std::ios::out };
		if (!global_trace_file) {
			std::cerr << "Error opening for write: " << (trace_log_directory / "all.trace") << std::endl;
			return false;
		}

		tracing_initialized = true;

		create_minidump_on_unhandles_exception = mindump_on_unhandled_exception;
		minidump_verbosity_level = in_minidump_verbosity_level;
		should_always_flush_tracing = in_should_always_flush_tracing;
		enabled_tracing_flags = mask;

		SetLogToCout(false);
		SetTracingEnabled(in_tracing_enabled);
		SetUnhandledExceptionLogging(in_unhandled_exception_logging);

		return true;
	}

	Trace::Trace(const char* const extra, uint64_t mask, const char* const func, void* override_caller_address) :
		enabled{ tracing_enabled && ((enabled_tracing_flags & mask) == mask) },
		func{ func }, extra{ extra }, return_address{ override_caller_address } {
		if (!enabled) {
			return;
		}

#ifdef _WIN32
		if (return_address == nullptr) {
			return_address = _ReturnAddress();
		}
#endif
		Tracer::Enter(func, extra, return_address);
	}

	// delegate constructors
	Trace::Trace(uint64_t mask, const char* const extra, const char* const func, void* override_caller_address) : Trace{ extra, mask, func,
		override_caller_address
#ifdef _WIN32
		== nullptr ? _ReturnAddress() : override_caller_address
#endif
	} {}
	Trace::Trace(const char* const extra, const char* const func, uint64_t mask, void* override_caller_address) : Trace{ extra, mask, func,
		override_caller_address
#ifdef _WIN32
		== nullptr ? _ReturnAddress() : override_caller_address
#endif
	} {}

	Trace::~Trace() {
		if (!enabled) {
			return;
		}

		Tracer::Exit(func, extra, return_address);
	}

	Trace::operator bool() const {
		return enabled;
	}

	bool Trace::operator!() const {
		return !enabled;
	}

	bool Trace::has_flags(uint64_t mask) const {
		return enabled && ((enabled_tracing_flags & mask) == mask);
	}

	std::ofstream& Trace::thread_logger() {
		auto& log_file = thread_tracer.GetLogFile();
		if (log_file) {
			log_file << std::string(thread_tracer.depth, ' ');
		}
		return log_file;
	}

	std::osyncstream Trace::global_logger() {
		return std::osyncstream(global_trace_file);
	}

	void Trace::write_all(const char* const data) {
		if (!tracing_enabled) {
			return;
		}

		auto& log_file = thread_tracer.GetLogFile();
		if (log_file) {
			log_file << std::string(thread_tracer.depth, ' ') << data << '\n';

			if (should_always_flush_tracing) {
				log_file.flush();
			}
		}

		if (global_trace_file) {
			std::osyncstream sync_stream(global_trace_file);
			sync_stream << '[' << std::format("{:08x}", thread_tracer.GetCachedThreadID()) << "] " << data << '\n';

			if (should_always_flush_tracing) {
				sync_stream.flush();
			}
		}

		if (trace_to_console) {
			std::osyncstream sync_stream(std::cout);
			sync_stream << '[' << std::format("{:08x}", thread_tracer.GetCachedThreadID()) << "] " << data << '\n';

			if (should_always_flush_tracing) {
				sync_stream.flush();
			}
		}
	}

	void Trace::write_all(const std::string& data) {
		write_all(data.c_str());
	}

	void Tracer::Enter(const char* const func, const char* const extra, const void* const return_address) {
		auto& log_file = thread_tracer.GetLogFile();
		if (log_file) {
			log_file << std::string(thread_tracer.depth, ' ') << '+' << func;

			if (extra != nullptr) {
				log_file << extra;
			}

			log_file << "@" << std::hex << ((size_t)return_address) << '\n';
			if (should_always_flush_tracing) {
				log_file.flush();
			}
		}
		++thread_tracer.depth;

		if (global_trace_file) {
			std::osyncstream sync_stream(global_trace_file);
			sync_stream << '[' << std::format("{:08x}", thread_tracer.GetCachedThreadID()) << "] " << '+' << func;

			if (extra != nullptr) {
				sync_stream << extra;
			}

			sync_stream << "@" << std::hex << ((size_t)return_address) << '\n';
			if (should_always_flush_tracing) {
				sync_stream.flush();
			}
		}

		if (trace_to_console) {
			std::osyncstream sync_stream(std::cout);
			sync_stream << '[' << std::format("{:08x}", thread_tracer.GetCachedThreadID()) << "] " << '+' << func;

			if (extra != nullptr) {
				sync_stream << extra;
			}

			sync_stream << "@" << std::hex << ((size_t)return_address) << '\n';
			if (should_always_flush_tracing) {
				sync_stream.flush();
			}
		}
	}

	void Tracer::Exit(const char* const func, const char* const extra, const void* const return_address) {
		--thread_tracer.depth;
		auto& log_file = thread_tracer.GetLogFile();

		if (log_file) {
			log_file << std::string(thread_tracer.depth, ' ') << '-' << func;

			if (extra != nullptr) {
				log_file << extra;
			}

			log_file << "@" << std::hex << ((size_t)return_address) << '\n';
			if (should_always_flush_tracing) {
				log_file.flush();
			}
		}

		if (global_trace_file) {
			std::osyncstream sync_stream(global_trace_file);
			sync_stream << '[' << std::format("{:08x}", thread_tracer.GetCachedThreadID()) << "] " << '-' << func;

			if (extra != nullptr) {
				sync_stream << extra;
			}

			sync_stream << "@" << std::hex << ((size_t)return_address) << '\n';
			if (should_always_flush_tracing) {
				sync_stream.flush();
				global_trace_file.flush();
			}
		}

		if (trace_to_console) {
			std::osyncstream sync_stream(std::cout);
			sync_stream << '[' << std::format("{:08x}", thread_tracer.GetCachedThreadID()) << "] " << '-' << func;
			
			if (extra != nullptr) {
				sync_stream << extra;
			}

			sync_stream << "@" << std::hex << ((size_t)return_address) << '\n';
			if (should_always_flush_tracing) {
				sync_stream.flush();
				global_trace_file.flush();
			}
		}
	}
}
