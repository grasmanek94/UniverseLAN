#pragma once

#include "MessageUniqueID.hxx"

// Runtime unique ID

#include <atomic>

namespace {
	std::atomic_uint64_t unique_message_counter{ 1 };
}

namespace universelan {
	MessageUniqueID::MessageUniqueID() :
		id{ unique_message_counter.fetch_add(1) }
	{ }

	MessageUniqueID::MessageUniqueID(uint64_t id) :
		id{ id }
	{ }

	uint64_t MessageUniqueID::get() {
		return unique_message_counter.fetch_add(1);
	}
}