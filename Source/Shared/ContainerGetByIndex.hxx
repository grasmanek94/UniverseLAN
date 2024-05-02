#pragma once

#include <iterator>

namespace universelan {
	template <typename T> auto container_get_by_index(const T& container, size_t index, const typename T::value_type& default_not_found_value = T::value_type()) {
		if (index < container.size()) {
			return *std::next(container.begin(), index);
		}

		return T::value_type
	}
}