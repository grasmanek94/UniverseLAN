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

    template <typename Container>
    auto container_iterator_get_by_index(
        Container& container,
        std::size_t index)
    {
        if (index >= container.size()) {
            return container.end();
        }

        return std::next(container.begin(), index);
    }

    template <typename Map>
    auto map_iterator_get_by_index_with_forced_zero_key(
        Map& map,
        std::size_t index,
        const typename Map::key_type& forced_zero_key)
    {
        if (index >= map.size()) {
            return map.end();
        }

        if (index == 0) {
            return map.find(forced_zero_key);
        }

        std::size_t virtual_index = 1;

        for (auto it = map.begin(); it != map.end(); ++it) {
            if (it->first == forced_zero_key) {
                continue;
            }

            if (virtual_index == index) {
                return it;
            }

            ++virtual_index;
        }

        return map.end();
    }
}
