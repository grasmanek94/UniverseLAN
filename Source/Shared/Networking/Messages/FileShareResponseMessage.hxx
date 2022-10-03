#pragma once

#include <Networking/SendableEventMessage.hxx>

#include <GalaxyApi.h>

#include <string>

namespace universelan {
	class FileShareResponseMessage
	{
	public:
		uint64_t request_id;
		galaxy::api::SharedFileID id;
		std::string filename;

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(request_id, id, filename);
		}

		UniqueClassId_Declare(FileShareResponseMessage);

		FileShareResponseMessage()
			: request_id{ 0 }, id{ 0 }, filename{} {}
		FileShareResponseMessage(uint64_t request_id, galaxy::api::SharedFileID id, const std::string& filename)
			: request_id{ request_id }, id{ id }, filename{ filename } {}
	};
}
