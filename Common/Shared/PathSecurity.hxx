#pragma once

#include <iostream>
#include <filesystem>

namespace universelan {
	inline bool inside_basepath(
		const std::filesystem::path& basepath,
		const std::filesystem::path& relpath) {

		const auto abspath = std::filesystem::weakly_canonical(basepath / relpath);

		const auto index = abspath.string().rfind(basepath.string(), 0);
		if (index != 0) {
			return false;
		}
		return true;
	}
}
