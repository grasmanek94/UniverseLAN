#pragma once

namespace universelan::util {
	template <typename T> class dynamic_return {
	public:
		using type = T;

		static T value_true() { return !T(); }
		static T value_false() { return T(); }
		template <typename U>
		static const T value(const U val) { return (T)val; }
	};

	template <> class dynamic_return<bool> {
	public:
		using type = bool;

		static constexpr type value_true() { return true; }
		static constexpr type value_false() { return false; }
		template<typename U>
		static const type value(const U val) { return (type)val; }
	};

	template <> class dynamic_return<void> {
	public:
		using type = void;

		static constexpr type value_true() { return; }
		static constexpr type value_false() { return; }
		template<typename U>
		static constexpr type value(const U& val) { return; }
	};
}
