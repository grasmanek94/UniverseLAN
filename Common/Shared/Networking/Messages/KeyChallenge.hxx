#pragma once
#include <Networking/SendableEventMessage.hxx>

#include <ConstHash.hxx>

class KeyChallenge
{
public:
	uint64_t encrypted;

	template<class Archive>
	void serialize(Archive & ar)
	{
		ar(encrypted);
	}

	UniqueClassId_Declare(KeyChallenge);

	KeyChallenge() : encrypted{ 0ULL } {}
	inline KeyChallenge& challenge(uint64_t key, uint64_t data) {
		encrypted = key ^ data;
		return *this;
	}

	inline KeyChallenge& response(uint64_t key, uint64_t challenge) {
		uint64_t data = (key ^ challenge);
		encrypted = const_hash64_data((const char*)&data, sizeof(data));
		return *this;
	}
};
