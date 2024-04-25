#pragma once

#include <Unet_common.h>
#include <Unet/ServiceID.h>

namespace Unet
{
	enum class PacketType
	{
		Unreliable,
		Reliable,
	};

	class NetworkMessage
	{
	public:
		uint8_t m_sequenceId = 0;
		uint32_t m_sequenceSize = 0;
		uint32_t m_sequenceHash = 0;

		ServiceID m_peer;
		int m_channel = 0;

		uint8_t* m_data;
		size_t m_size;

	public:
		NetworkMessage(size_t size);
		NetworkMessage(uint8_t* data, size_t size);
		~NetworkMessage();

		void Append(uint8_t* data, size_t size);
	};

	// A refcounted pointer to a NetworkMessage object.
	typedef std::unique_ptr<NetworkMessage> NetworkMessageRef;
}
