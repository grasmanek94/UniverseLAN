#pragma once

#include <string>
#include <type_traits>
#include <vector>

namespace universelan
{
	class SharedLibUtils {
	private:
		static SharedLibUtils* instance();

		SharedLibUtils();

	public:
		static void* get_func_ptr(const char* name);

		template<typename T>
			requires std::is_pointer_v<T> &&
			std::is_function_v<std::remove_pointer_t<T>>
		static T get_func(const char* const name) {
			return reinterpret_cast<T>(SharedLibUtils::get_func_ptr(name));
		}

		static const char* get_function_match(const char* const search);

		~SharedLibUtils();
	};
}
