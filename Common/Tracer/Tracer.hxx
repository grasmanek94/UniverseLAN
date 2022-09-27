#pragma once

namespace universelan::tracer {
	class Tracer;

	enum class TRACE_MASK {

	};

	class Trace
	{
	private:
		Tracer* const tracer_ptr;
		const bool enabled;
		const char* const func;
		const void* return_address;
	public:
		static bool InitTracing(const char* const log_directory, 
			bool in_unhandled_exception_logging, bool in_tracing_enabled, 
			bool in_mindump_on_unhandled_exception, int minidump_verbosity_level,
			bool in_should_always_flush_tracing);

		static void SetUnhandledExceptionLogging(bool enabled);
		static void SetTracingEnabled(bool enabled);

		Trace(const char* const func);
		~Trace();
	};
}
