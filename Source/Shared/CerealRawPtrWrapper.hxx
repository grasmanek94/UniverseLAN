#pragma once

#include <cstdint>

namespace universelan {

	template <typename T>
	class CerealRawPtrWrapper
	{
		uint64_t value;
	public:
		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(value);
		}

		CerealRawPtrWrapper() :
			value{ 0ULL }
		{ }

		CerealRawPtrWrapper(T* ptr) :
			value{ (uint64_t)ptr }
		{ }

		T* get() const noexcept {
			return (T*)value;
		}

		explicit operator bool() const noexcept {
			return get() != nullptr;
		}

		T& operator*() const noexcept {
			return *get();
		}

		T* operator->() const noexcept {
			return get();
		}
	};
}
