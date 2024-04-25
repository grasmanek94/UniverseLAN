#pragma once

#include <Unet_common.h>
#include <Unet/NetworkMessage.h>
#include <Unet/Service.h>

namespace Unet
{
	class Reassembly
	{
	private:
		Internal::Context* m_ctx;

		std::vector<NetworkMessage*> m_staging;
		std::queue<NetworkMessage*> m_ready;

		std::vector<uint8_t> m_tempBuffer;
		uint8_t m_sequenceId = 0;

	public:
		Reassembly(Internal::Context* ctx);
		~Reassembly();

		void HandleMessage(ServiceID peer, int channel, uint8_t* msgData, size_t packetSize);
		NetworkMessage* PopReady();

		void Clear();

		void SplitMessage(uint8_t* data, size_t size, PacketType type, size_t sizeLimit, const std::function<void(uint8_t*, size_t)> &callback);
	};
}
