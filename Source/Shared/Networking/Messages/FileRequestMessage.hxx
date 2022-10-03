#pragma once

#include <Networking/SendableEventMessage.hxx>

#include <GalaxyApi.h>

#include <string>

namespace universelan {
	class FileRequestMessage
	{
	public:
		uint64_t request_id;
		galaxy::api::SharedFileID id;
		std::string filename;
		std::vector<char> data;

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(request_id, id, filename, data);
		}

		UniqueClassId_Declare(FileRequestMessage);

		FileRequestMessage()
			: request_id{ 0 }, id{ 0 }, filename{}, data{} {}
		FileRequestMessage(uint64_t request_id, galaxy::api::SharedFileID id)
			: request_id{ request_id }, id{ id }, filename{}, data{} {}
		FileRequestMessage(uint64_t request_id, galaxy::api::SharedFileID id, const std::string& filename, const std::vector<char>& data)
			: request_id{ request_id }, id{ id }, filename{ filename }, data{ data } {}
	};
}
