#include "Tracer.hxx"

#include <intrin.h>
#include <Windows.h>

#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <mutex>
#include <string>
#include <syncstream>

namespace universelan::tracer {
	namespace fs = std::filesystem;

	namespace {
		fs::path trace_log_directory;
		Tracer* tracer{nullptr};
		std::ofstream global_trace_file;

		class ThreadTracer {
		public:
			std::ofstream log_file;
			size_t depth;
			DWORD thread_id;

			ThreadTracer() 
				: log_file{}, depth{ 0 }, thread_id{ 0 }
			{
				thread_id = GetCurrentThreadId();
				std::string filename = std::format("{:08x}", thread_id);
				std::string path{ (trace_log_directory / (filename + ".trace")).string() };

				log_file = std::ofstream{ path, std::ios::app | std::ios::out};
				if (log_file) {
					log_file << "+\n\n\n";
				}
				else {
					std::osyncstream sync_stream(std::cerr);
					sync_stream << "Error opening tracer for thread " << filename << " for write: " << path << std::endl;
				}
			}
		};

		static thread_local ThreadTracer thread_tracer;
	}

	Trace::Trace(const char* const func) :
		tracer_ptr{ Tracer::GetInstance() }, func{ func }, return_address{ nullptr } {
		return_address = _ReturnAddress();
		if (tracer_ptr) {
			tracer_ptr->Enter(func, return_address);
		}
	}

	Trace::~Trace() {
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
		}
		else {
			global_trace_file = std::ofstream{ (trace_log_directory / "all.trace").string(), std::ios::trunc | std::ios::out};
			if (!global_trace_file) {
				std::cerr << "Error opening for write: " << (trace_log_directory / "all.trace") << std::endl;
			}
		}
	}

	Tracer::~Tracer() {
	}

	void Tracer::Enter(const char* const func, const void* const return_address) {
		if (thread_tracer.log_file) {
			thread_tracer.log_file << std::string(thread_tracer.depth, ' ') << '+' << func << "@" << std::hex << ((size_t)return_address) << '\n';
		}
		++thread_tracer.depth;

		if (global_trace_file) {
			std::osyncstream sync_stream(global_trace_file);
			sync_stream << '[' << thread_tracer.thread_id << "] " << '+' << func << "@" << std::hex << ((size_t)return_address) << '\n';
		}
	}

	void Tracer::Exit(const char* const func, const void* const return_address) {
		--thread_tracer.depth;
		if (thread_tracer.log_file) {
			thread_tracer.log_file << std::string(thread_tracer.depth, ' ') << '-' << func << "@" << std::hex << ((size_t)return_address) << '\n';
		}

		if (global_trace_file) {
			std::osyncstream sync_stream(global_trace_file);
			sync_stream << '[' << thread_tracer.thread_id << "] " << '-' << func << "@" << std::hex << ((size_t)return_address) << '\n';
		}
	}

	Tracer* Tracer::GetInstance() {
		return tracer;
	}

	Tracer* Tracer::InitInstance(const char* const log_directory) {
		if (tracer == nullptr) {
			tracer = new Tracer(log_directory);
		}

		return tracer;
	}

}
