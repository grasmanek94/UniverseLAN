#pragma once

#include <iterator>
#include <optional>

namespace universelan {
	template <typename T> auto container_get_by_index(const T& container, size_t index) {
		if (index < container.size()) {
			return std::optional<typename T::value_type>{*std::next(container.begin(), index)};
		}

		return std::optional<typename T::value_type>{};
	}

	template <typename T> auto container_get_by_index(const T& container, size_t index, const typename T::value_type& default_not_found_value) {
		if (index < container.size()) {
			return *std::next(container.begin(), index);
		}

		return default_not_found_value;
	}
}