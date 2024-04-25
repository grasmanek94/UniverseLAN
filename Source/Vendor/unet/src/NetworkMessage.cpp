#include <Unet_common.h>
#include <Unet/NetworkMessage.h>

Unet::NetworkMessage::NetworkMessage(size_t size)
{
	m_size = size;
	m_data = (uint8_t*)malloc(size);
}

Unet::NetworkMessage::NetworkMessage(uint8_t* data, size_t size)
	: NetworkMessage(size)
{
	if (m_data != nullptr) {
		memcpy(m_data, data, size);
	}
}

Unet::NetworkMessage::~NetworkMessage()
{
	if (m_data != nullptr) {
		free(m_data);
	}
}

void Unet::NetworkMessage::Append(uint8_t* data, size_t size)
{
	uint8_t* newData = (uint8_t*)realloc(m_data, m_size + size);
	assert(newData != nullptr);
	if (newData == nullptr) {
		return;
	}

	m_data = newData;
	memcpy(m_data + m_size, data, size);
	m_size += size;
}
