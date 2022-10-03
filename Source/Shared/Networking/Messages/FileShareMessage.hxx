#pragma once

#include <Networking/SendableEventMessage.hxx>

namespace universelan {
	class FileShareMessage
	{
	public:
		uint64_t request_id;
		std::string filename;
		std::vector<char> data;

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(request_id, filename, data);
		}

		UniqueClassId_Declare(FileShareMessage);

		FileShareMessage() 
			: request_id{ 0 }, filename {}, data{} {}
		FileShareMessage(uint64_t request_id, const std::string& filename, const std::vector<char>& data) 
			: request_id{ request_id }, filename{filename}, data{data} {}
	};
}
