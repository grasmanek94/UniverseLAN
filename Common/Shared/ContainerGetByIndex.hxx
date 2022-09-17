#pragma once

#include <iterator>

namespace universelan {
	template <typename T> auto container_get_by_index(const T& container, size_t index) {
		auto it = container.begin();
		while (index--) {
			++it;
		}
		return *it;
	}
}