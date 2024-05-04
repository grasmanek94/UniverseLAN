#pragma once

#include <functional>

namespace universelan::functional
{
	template<typename> struct xt;

	template <class... ArgTypes>
	struct xt<std::function<ArgTypes...>> {
		using T = ArgTypes...;
		using F = std::function<T>;
		using PTR = T*;
	};
}
