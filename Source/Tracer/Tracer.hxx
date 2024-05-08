#pragma once

#include <cstdint>

#include <iostream>
#include <source_location>
#include <string>
#include <syncstream>

namespace universelan::tracer {
	static constexpr uint64_t bit(uint64_t N) { return 1ULL << N; }

	class Trace
	{
	private:
		const bool enabled;
		const char* const func;
		const char* const extra;
		const void* return_address;
	public:
		enum MASK : uint64_t {
			INFORMATIONAL = 0,

			TRACE_ALL_FLAGS = bit(0),

			ARGUMENTS = bit(1),
			RETURN_VALUES = bit(2),
			DETAILED = bit(3),
			HIGH_FREQUENCY_CALLS = bit(4),

			NETCLIENT = bit(5),
			GALAXYDLL = bit(6),
			GALAXYDLL_GAMESERVERAPI = bit(7),
			LISTENERREGISTRAR = bit(8),

			ICHAT = bit(9),
			ICUSTOMNETWORKING = bit(10),
			IERROR = bit(11),
			IFRIENDS = bit(12),
			ILOGGER = bit(13),
			IMATCHMAKING = bit(14),
			INETWORKING = bit(15),
			ISTATS = bit(16),
			ISTORAGE = bit(17),
			ITELEMETRY = bit(18),
			IUSER = bit(19),
			IUTILS = bit(20),
			IGAMESERVERAPI = bit(21),
			IGALAXYTHREAD = bit(22),
			IAPPS = bit(23),
			CUSTOMCONSOLE = bit(24),
			ICLOUDSTORAGE = bit(25),

			NOTIFICATION_INVOCATIONS = bit(26),
			SERVER_UNAUTHENTICATED = bit(27)
		};

		static bool InitTracing(const char* const log_directory,
			bool in_unhandled_exception_logging, bool in_tracing_enabled,
			bool in_mindump_on_unhandled_exception, int minidump_verbosity_level,
			bool in_should_always_flush_tracing, uint64_t mask = INFORMATIONAL);

		static void SetUnhandledExceptionLogging(bool enabled);
		static void SetTracingEnabled(bool enabled);
		static void SetLogToCout(bool enabled);

		Trace(const char* const extra = nullptr, uint64_t mask = INFORMATIONAL, const char* const func = std::source_location::current().function_name());
		Trace(uint64_t mask, const char* const extra = nullptr, const char* const func = std::source_location::current().function_name());
		Trace(const char* const extra, const char* const func, uint64_t mask = INFORMATIONAL);

		~Trace();

		explicit operator bool() const;
		bool operator!() const;
		bool has_flags(uint64_t mask) const;

		static std::ofstream& thread_logger();
		static std::osyncstream global_logger();

		static void write_all(const char* const data);
		static void write_all(const std::string& data);
	};
}
