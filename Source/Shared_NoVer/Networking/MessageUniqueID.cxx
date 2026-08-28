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
		// REVIEW: Explicit IDs do not advance or coordinate with the atomic
		// counter, so MessageUniqueID(1) can collide with an auto-generated ID.
		// Validate/reserve explicit IDs or separate externally assigned IDs.
		id{ id }
	{ }

	uint64_t MessageUniqueID::get() {
		return unique_message_counter.fetch_add(1);
	}
}