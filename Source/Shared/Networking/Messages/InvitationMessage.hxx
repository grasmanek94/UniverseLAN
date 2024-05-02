#pragma once

#include <Networking/SendableEventMessage.hxx>

#include <GalaxyID.h>

#include <string>

namespace universelan {
	class InvitationMessage
	{
	public:
		uint64_t request_id = 0;
		galaxy::api::GalaxyID user_id = 0;
		std::string connection_string = "";

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(request_id
				, user_id
				, connection_string
			);
		}

		UniqueClassId_Declare(InvitationMessage);

		InvitationMessage() {}

		InvitationMessage(uint64_t request_id, galaxy::api::GalaxyID user_id, const std::string& connection_string
		) : request_id{ request_id }
			, user_id{ user_id },
			connection_string{ connection_string }
		{}
	};
}
