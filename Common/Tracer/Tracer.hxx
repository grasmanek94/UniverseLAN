#pragma once

namespace universelan::tracer {
	class Trace;
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
		static Tracer* InitInstance(const char* const log_directory);
		static Tracer* GetInstance();
	};

	class Trace
	{
	private:
		Tracer* const tracer_ptr;
		const char* const func;
		const void* return_address;
	public:
		Trace(const char* const func);
		~Trace();
	};
}
