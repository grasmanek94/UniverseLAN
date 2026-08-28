#pragma once

#include <string>
#include <vector>

namespace universelan
{
	class SharedLibUtils {
	private:
		SharedLibUtils();

	public:
		static void* get_func_ptr(const char* name);

		template<typename T>
		static T get_func(const char* name) {
			// REVIEW: Converting a void* from dlsym/GetProcAddress to a function
			// pointer is not portable ISO C++; use the platform's supported
			// function-pointer conversion and keep this API ABI-specific.
			return (T)SharedLibUtils::get_func_ptr(name);
		}

		static const char* get_function_match(const char* search);

		~SharedLibUtils();
	};
}
