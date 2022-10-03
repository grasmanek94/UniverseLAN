#pragma once

#include <boost/static_string.hpp>

#include <string>
#include <vector>

namespace universelan::tracer {
	extern bool create_minidump_on_unhandles_exception;
	extern int minidump_verbosity_level;

	struct CallEntryFile {
		boost::static_string<260> path;
		size_t line_number;
	};

	struct CallStackEntry {
		size_t offset;
		boost::static_string<1024> module_name;
		boost::static_string<2048> function;
		CallEntryFile file;
	};

	using CallStackEntries = std::vector<CallStackEntry>;

	class IUnhandledExceptionCallback
	{
	public:
		virtual void UnhandledExceptionOccurred(bool unknown_exception, const std::string exception_type, const std::string& exception_message, bool error_occured_during_stack_walk, const CallStackEntries& call_stack) = 0;
		virtual ~IUnhandledExceptionCallback() {}
	};

	class Stacker
	{
	private:
		Stacker();
		~Stacker();

		bool Init();

	public:
		static Stacker* GetInstance();
		void SetUnhandledExceptionCallback(IUnhandledExceptionCallback* target);
	};
}
