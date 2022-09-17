#include "Logger.hxx"

#include "UniverseLAN.hxx"

#include <atomic>
#include <cstdarg>
#include <filesystem>
#include <fstream>
#include <string>
#include <thread>
#include <vector>

namespace universelan::client {
	using namespace galaxy::api;
	LoggerImpl::LoggerImpl(InterfaceInstances* intf) :
		intf{ intf }, mtx{}, logfile{}
	{
		static std::atomic_int counter = 0;

		auto t = std::time(nullptr);

#pragma warning( push )
#pragma warning( disable : 4996 )
		auto tm = *std::localtime(&t);
#pragma warning( pop )

		std::ostringstream path;

		int count = counter.fetch_add(1);

		path << (std::filesystem::path(intf->config->GetGameDataPath()) / "Logging" / "L")
			<< std::put_time(&tm, "%Y-%m-%d_%H-%M-%S")
			<< "-" << std::this_thread::get_id() << "-" << count << ".log";

		logfile = std::ofstream{ path.str() };
		if (!logfile) {
			std::cerr << "Error opening for write: " << path.str() << std::endl;
		}
	}

	LoggerImpl::~LoggerImpl()
	{
		if (logfile) {
			lock_t lock(mtx);
			logfile.flush();
		}
	}

#define Log(type) \
			if (logfile) { \
				va_list vaArgs; \
				va_start(vaArgs, format); \
				\
				va_list vaCopy; \
				va_copy(vaCopy, vaArgs); \
				const int iLen = std::vsnprintf(NULL, 0, format, vaCopy); \
				va_end(vaCopy); \
				\
				std::vector<char> zc(iLen + 1); \
				std::vsnprintf(zc.data(), zc.size(), format, vaArgs); \
				va_end(vaArgs); \
				\
				std::string logstr(zc.data(), zc.size()); \
				\
				lock_t lock(mtx); \
				logfile << type << "[" << std::this_thread::get_id() << "] " << logstr << '\n'; \
			}

	void LoggerImpl::Trace(const char* format, ...) {
		Log("[T]");
	}

	void LoggerImpl::Debug(const char* format, ...) {
		Log("[D]");
	}

	void LoggerImpl::Info(const char* format, ...) {
		Log("[I]");
	}

	void LoggerImpl::Warning(const char* format, ...) {
		Log("[W]");
	}

	void LoggerImpl::Error(const char* format, ...) {
		Log("[E]");
	}

	void LoggerImpl::Fatal(const char* format, ...) {
		Log("[F]");
	}

#undef Log
}
