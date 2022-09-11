#pragma once

#include <cereal/archives/binary.hpp>
#include <cereal/types/array.hpp>
#include <cereal/types/base_class.hpp>
#include <cereal/types/bitset.hpp>
#include <cereal/types/chrono.hpp>
#include <cereal/types/common.hpp>
#include <cereal/types/complex.hpp>
#include <cereal/types/deque.hpp>
#include <cereal/types/forward_list.hpp>
#include <cereal/types/list.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/queue.hpp>
#include <cereal/types/set.hpp>
#include <cereal/types/stack.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/tuple.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/unordered_set.hpp>
#include <cereal/types/utility.hpp>
#include <cereal/types/valarray.hpp>
#include <cereal/types/vector.hpp>

static_assert(sizeof(uint64_t) == 8, "You cannot compile this application for the chosen architecture");

// compile time FNV-1a
constexpr uint32_t const_hash(const char* str, size_t n, uint32_t basis = UINT32_C(2166136261)) {
	return n == 0 ? basis : const_hash(str + 1, n - 1, (basis ^ str[0]) * UINT32_C(16777619));
}

#define UniqueClassId_Declare(className) static const uint64_t constexpr UniqueClassId() { return const_hash(#className, sizeof(#className)); }
