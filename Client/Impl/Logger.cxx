#include "Logger.hxx"

#include "UniverseLAN.hxx"

#include <atomic>
#include <cstdarg>
#include <filesystem>
#include <fstream>
#include <string>
#include <thread>
#include <vector>

namespace galaxy
{
	namespace api
	{
		LoggerImpl::LoggerImpl() :
			logfile{}
		{
			static std::atomic_int counter = 0;

			auto t = std::time(nullptr);
			auto tm = *std::localtime(&t);

			std::ostringstream path;

			int count = counter.fetch_add(1);

			path << (std::filesystem::path(config->GetGameDataPath()) / "Logging" / "L")
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
				logfile.flush();
			}
		}

		void LoggerImpl::Trace(const char* format, ...) {
			if (logfile) {
				const char* const zcFormat = format;

				va_list vaArgs;
				va_start(vaArgs, format);

				va_list vaCopy;
				va_copy(vaCopy, vaArgs);
				const int iLen = std::vsnprintf(NULL, 0, zcFormat, vaCopy);
				va_end(vaCopy);

				std::vector<char> zc(iLen + 1);
				std::vsnprintf(zc.data(), zc.size(), zcFormat, vaArgs);
				va_end(vaArgs);

				std::string logstr(zc.data(), zc.size());
				logfile << "[T] " << logstr << '\n';
			}
		}

		void LoggerImpl::Debug(const char* format, ...) {
			if (logfile) {
				const char* const zcFormat = format;

				va_list vaArgs;
				va_start(vaArgs, format);

				va_list vaCopy;
				va_copy(vaCopy, vaArgs);
				const int iLen = std::vsnprintf(NULL, 0, zcFormat, vaCopy);
				va_end(vaCopy);

				std::vector<char> zc(iLen + 1);
				std::vsnprintf(zc.data(), zc.size(), zcFormat, vaArgs);
				va_end(vaArgs);

				std::string logstr(zc.data(), zc.size());
				logfile << "[D] " << logstr << '\n';
			}
		}

		void LoggerImpl::Info(const char* format, ...) {
			if (logfile) {
				const char* const zcFormat = format;

				va_list vaArgs;
				va_start(vaArgs, format);

				va_list vaCopy;
				va_copy(vaCopy, vaArgs);
				const int iLen = std::vsnprintf(NULL, 0, zcFormat, vaCopy);
				va_end(vaCopy);

				std::vector<char> zc(iLen + 1);
				std::vsnprintf(zc.data(), zc.size(), zcFormat, vaArgs);
				va_end(vaArgs);

				std::string logstr(zc.data(), zc.size());
				logfile << "[I] " << logstr << '\n';
			}
		}

		void LoggerImpl::Warning(const char* format, ...) {
			if (logfile) {
				const char* const zcFormat = format;

				va_list vaArgs;
				va_start(vaArgs, format);

				va_list vaCopy;
				va_copy(vaCopy, vaArgs);
				const int iLen = std::vsnprintf(NULL, 0, zcFormat, vaCopy);
				va_end(vaCopy);

				std::vector<char> zc(iLen + 1);
				std::vsnprintf(zc.data(), zc.size(), zcFormat, vaArgs);
				va_end(vaArgs);

				std::string logstr(zc.data(), zc.size());
				logfile << "[W] " << logstr << '\n';
			}
		}

		void LoggerImpl::Error(const char* format, ...) {
			if (logfile) {
				const char* const zcFormat = format;

				va_list vaArgs;
				va_start(vaArgs, format);

				va_list vaCopy;
				va_copy(vaCopy, vaArgs);
				const int iLen = std::vsnprintf(NULL, 0, zcFormat, vaCopy);
				va_end(vaCopy);

				std::vector<char> zc(iLen + 1);
				std::vsnprintf(zc.data(), zc.size(), zcFormat, vaArgs);
				va_end(vaArgs);

				std::string logstr(zc.data(), zc.size());
				logfile << "[E] " << logstr << '\n';
			}
		}

		void LoggerImpl::Fatal(const char* format, ...) {
			if (logfile) {
				const char* const zcFormat = format;

				va_list vaArgs;
				va_start(vaArgs, format);

				va_list vaCopy;
				va_copy(vaCopy, vaArgs);
				const int iLen = std::vsnprintf(NULL, 0, zcFormat, vaCopy);
				va_end(vaCopy);

				std::vector<char> zc(iLen + 1);
				std::vsnprintf(zc.data(), zc.size(), zcFormat, vaArgs);
				va_end(vaArgs);

				std::string logstr(zc.data(), zc.size());
				logfile << "[F] " << logstr << '\n';
			}
		}
	}
}
