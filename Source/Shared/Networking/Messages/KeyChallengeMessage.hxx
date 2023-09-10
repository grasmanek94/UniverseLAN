#pragma once
#include <Networking/SendableEventMessage.hxx>

#include <ConstHash.hxx>

#include <GalaxyApi.h>

#include <GalaxyIDSerialization.hxx>

namespace universelan {
	/**
	* Challenge works like this:
	*
	* - const_hash64(string) = FNV-1a
	* - const_hash64_data(bytes_ptr, size) = FNV-1a
	* - Both apps have to use uint64_t KEY = const_hash64(UniverseLAN.ini -> Authentication -> Key)
	*
	* == SERVER ==
	* - A client connection is detected
	* - Server constructs a challenge consisting of a RANDOM_NUMBER
	* - The data is sent to the client CHALLENGE = (KEY XOR RANDOM_NUMBER)
	*
	* == CLIENT ==
	* - Client must decode DECODED_RANDOM_NUMBER = (KEY XOR CHALLENGE)
	* - Client then sends to server the CHALLENGE_RESPONSE = const_hash64_data(DECODED_RANDOM_NUMBER)
	*
	* == SERVER ==
	* - Server checks if CHALLENGE_RESPONSE equals to the stored const_hash64_data(RANDOM_NUMBER)
	* - If yes then server sends ConnectionAccepted packet
	*
	* == CLIENT ==
	* - Client receives a disconnect if the challenge failed
	* - Client receives a ConnectionAccepted packet if the challenge was solved
	*
	*
	*                           CLIENT                         SERVER
	*                                     -----------[connect]--------->
	*                                                                     CHALLENGE = KEY ^ RAND_NUMBER
	*                                                                     EXPECTED_RESPONSE = FNV1A_HASH(RAND_NUMBER)
	*                                     <----------[CHALLENGE]--------
	* RAND_NUMBER = KEY ^ CHALLENGE
	* RESPONSE = FNV1A_HASH(RAND_NUMBER)
	*                                     -----------[RESPONSE]-------->
	*                                                                     IF(RESPONSE == EXPECTED_RESPONSE)
	*
	* OK                                  <-----[ConnectionAccepted]----            (TRUE)
	* /
	* FAIL                                X----------[Disconnect]-------            (FALSE)
	*/
	class KeyChallengeMessage
	{
	public:
		uint64_t encrypted;
		galaxy::api::GalaxyID id;

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(encrypted, id);
		}

		UniqueClassId_Declare(KeyChallengeMessage);

		KeyChallengeMessage() : encrypted{ 0ULL }, id{ 0 } {}
		KeyChallengeMessage(galaxy::api::GalaxyID id) : encrypted{ 0ULL }, id{ id } {}

		inline KeyChallengeMessage& challenge(uint64_t key, uint64_t data) {
			encrypted = key ^ data;
			return *this;
		}

		inline KeyChallengeMessage& response(uint64_t key, uint64_t challenge) {
			uint64_t data = (key ^ challenge);
			encrypted = const_hash64_data((const char*)&data, sizeof(data));
			return *this;
		}
	};
}
