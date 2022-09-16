#pragma once

// Runtime unique ID

#include <cstdint>

class MessageUniqueID
{
public:
	uint64_t id;

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(id);
	}

	/* Thread safe */
	MessageUniqueID();

	/* Thread safe */
	MessageUniqueID(uint64_t id);

	/* Thread safe */
	static uint64_t get();
};
